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
#include "Common.h"
#include <functional>
#include <blend2d.h>
class ICanvasWriter;

class DrawingCanvas
{
	DWORD _width;
	DWORD _height;
	BLImage _img;
	
public:
	DrawingCanvas(DWORD pWidth, DWORD pHeight);

	BLSize GetSize() const;
	void Render(BLPoint pOrigin, BLSize pSize, std::function<void(BLContext&,BLPoint,BLSize)> pRender);
	void Render(std::function<void(BLContext&, BLPoint, BLSize)> pRender);

	void WriteTo(ICanvasWriter& pTarget) const;	
};

