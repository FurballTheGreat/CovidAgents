/*
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "FFMpegH264Writer.h"

#include <blend2d.h>
#include <iostream>

FFMpegWriterException::FFMpegWriterException(int pAvError) : _avError(pAvError)
{
	char buf[1024];
	av_make_error_string(buf, sizeof(buf), pAvError);
	std::cout << buf << "\r\n";
}

FFMpegH264Writer::FFMpegH264Writer(const std::string& pFileName, const BLSize& pSize, const DWORD pFrameRate, const DWORD pBitRate)
{
	
	avformat_alloc_output_context2(&_outputFormatContext, nullptr, nullptr, pFileName.c_str());
	if (!_outputFormatContext)
		throw FFMpegWriterException(AVERROR_UNKNOWN);
	
	_outputStream = avformat_new_stream(_outputFormatContext, nullptr);
	int err;
	if (!(_outputFormatContext->oformat->flags & AVFMT_NOFILE))
		if ((err = avio_open(&_outputFormatContext->pb, pFileName.c_str(), AVIO_FLAG_WRITE)) < 0)
			throw FFMpegWriterException(err);
	
	_codec = avcodec_find_encoder_by_name("libx264");
	_context = avcodec_alloc_context3(_codec);
	av_opt_set(_context->priv_data, "preset", "veryslow", 0);
	av_opt_set(_context->priv_data, "x264-params", "keyint=60:min-keyint=60:scenecut=0:force-cfr=1", 0);
	_context->width = static_cast<int>(pSize.w);
	_context->height = static_cast<int>(pSize.h);
	//_context->sample_aspect_ratio.num = _context->width;
	//_context->sample_aspect_ratio.den = _context->height;
	_context->gop_size = 10;
	_context->max_b_frames = 1;
	_context->ticks_per_frame = 1;
	if (_codec->pix_fmts)
		_context->pix_fmt = _codec->pix_fmts[0];
	else
		_context->pix_fmt = AV_PIX_FMT_YUV420P;

	//_context->bit_rate = pBitRate;
	//_context->rc_buffer_size = pBitRate * 2;
	//_context->rc_max_rate = pBitRate;
	//_context->rc_min_rate = 0;
	
	_context->time_base = { 1, (int)pFrameRate };
	_context->framerate = {  (int)pFrameRate,1 };
	_outputStream->time_base = _context->time_base;
	_outputFormatContext->streams[0]->time_base = _context->time_base;
	_resampledFrame = av_frame_alloc();
	_resampledFrame->format = _context->pix_fmt;
	_resampledFrame->width = _context->width;
	_resampledFrame->height = _context->height;

	_sourceFrame = av_frame_alloc();
	_sourceFrame->format = AV_PIX_FMT_BGR32;
	_sourceFrame->width = _context->width;
	_sourceFrame->height = _context->height;

	_swsContext = sws_getContext(_context->width, _context->height, AV_PIX_FMT_BGR32, _context->width, _context->height, AV_PIX_FMT_YUV420P, SWS_BILINEAR, nullptr, nullptr, nullptr);
	
	av_opt_set(_context->priv_data, "tune", "zerolatency", 0);

	
	if ((err = av_frame_get_buffer(_resampledFrame, 32)) < 0)
		throw FFMpegWriterException(err);
	if ((err = av_frame_get_buffer(_sourceFrame, 32)) < 0)
		throw FFMpegWriterException(err);
	
	if ((err = avcodec_open2(_context, _codec, nullptr)) < 0)
		throw FFMpegWriterException(err);
	if((err = avcodec_parameters_from_context(_outputStream->codecpar, _context)) < 0)
		throw FFMpegWriterException(err);

	if((err = avformat_write_header(_outputFormatContext, nullptr))<0)
		throw FFMpegWriterException(err);
}

FFMpegH264Writer::~FFMpegH264Writer()
{
	av_write_trailer(_outputFormatContext);

	av_frame_free(&_sourceFrame);
	av_frame_free(&_resampledFrame);
	av_packet_free(&_packet);
	avcodec_close(_context);
	av_free(_context);
//	av_free(_outputStream);
	avformat_free_context(_outputFormatContext);
}

void FFMpegH264Writer::SaveFrame(DWORD pLines, DWORD pStride, void* pLinePointers)
{
	
	auto result = sws_scale(_swsContext, (PBYTE*)pLinePointers, _sourceFrame->linesize, 0, pLines, _resampledFrame->data, _resampledFrame->linesize);
	AVPacket* output_packet = av_packet_alloc();
	_resampledFrame->pts = _pts;
	_resampledFrame->pkt_dts = _pts;
	_pts+= av_rescale_q(1, _context->time_base, _outputStream->time_base);
	
	int response = avcodec_send_frame(_context, _resampledFrame);
	while (response >= 0) {
		response = avcodec_receive_packet(_context, output_packet);
		if (response == AVERROR(EAGAIN) || response == AVERROR_EOF)
			break;
		if (response < 0)
			throw FFMpegWriterException(response);

		//output_packet->stream_index = 0;
		output_packet->duration = _outputStream->time_base.den / _outputStream->time_base.num;
		
	//	output_packet->pts = -1;
		//av_packet_rescale_ts(output_packet, decoder->video_avs->time_base, encoder->video_avs->time_base);

		response = av_interleaved_write_frame(_outputFormatContext, output_packet);
		if (response != 0) throw FFMpegWriterException(response);
	}
	
	av_packet_unref(output_packet);
	av_packet_free(&output_packet);
}
