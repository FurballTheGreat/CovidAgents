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
#pragma once
#include "ICanvasWriter.h"

#include <blend2d.h>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}
class FFMpegWriterException : public std::exception
{
	int _avError;
	
public:
	FFMpegWriterException(int pAvError);
};

class FFMpegH264Writer : public ICanvasWriter
{
	AVFormatContext* _outputFormatContext = nullptr;
	AVStream* _outputStream;
	AVCodec* _codec;
	AVCodecContext* _context;
	AVFrame* _sourceFrame;
	AVFrame* _resampledFrame;
	AVPacket* _packet;
	SwsContext* _swsContext;
	int64_t _pts = 0;
public:
	FFMpegH264Writer(const std::string& pFileName, const BLSize& pSize, const DWORD pFrameRate, const DWORD pBitRate);
	~FFMpegH264Writer() override;
	void SaveFrame(DWORD pLines, DWORD pStride, void* pLinePointers) override;
};

