#pragma once
#include "ICanvasWriter.h"
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
#include <png.h>

class PngWriterException : public std::exception
{
};

class PngWriter : public ICanvasWriter 
{
	FILE* _file = nullptr;
	png_structp _png = nullptr;
	png_infop _info = nullptr;
	void CloseFileHandle();
public:
	PngWriter(const std::string& pFileName);
	~PngWriter() override;
	void SaveFrame(DWORD pLines, DWORD pStride, void* pLinePointers) override;
	
};

