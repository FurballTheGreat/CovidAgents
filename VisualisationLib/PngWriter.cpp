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
#include "PngWriter.h"

#include <png.h>

#ifdef __unix
#define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))==NULL
#endif

void PngWriter::CloseFileHandle()
{
	if(_file)
	{
        fclose(_file);
        _file = nullptr;
	}
}

PngWriter::PngWriter(const std::string& pFileName)
{
    fopen_s(&_file, pFileName.c_str(), "wb");
    if (!_file) 
        throw PngWriterException();

    _png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!_png)
    {
        CloseFileHandle();
        throw PngWriterException();
    }

    _info = png_create_info_struct(_png);
    if (!_info) {
        CloseFileHandle();
        throw PngWriterException();
    }
    if (setjmp(png_jmpbuf(_png))) {
        CloseFileHandle();
        throw PngWriterException();
    };

    png_init_io(_png, _file);   
}

PngWriter::~PngWriter()
{
    CloseFileHandle();

    if (_png != nullptr) {
        png_destroy_write_struct(&_png, &_info);
        _png = nullptr;
        _info = nullptr;
    }
}

void PngWriter::SaveFrame(DWORD pLines, DWORD pStride, void* pLinePointers)
{
    png_set_IHDR(
        _png,
        _info,
        pStride, pLines,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );
    png_write_info(_png, _info);

    png_write_image(_png, static_cast<png_bytepp>(pLinePointers));
    png_write_end(_png, nullptr);
}
