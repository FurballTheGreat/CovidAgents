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
#include "DrawingCanvas.h"

#include "ICanvasWriter.h"

DrawingCanvas::DrawingCanvas(DWORD pWidth, DWORD pHeight) : _width(pWidth), _height(pHeight)
{
   _img = BLImage(static_cast<int>(pWidth), static_cast<int>(pHeight), BL_FORMAT_PRGB32);   
}

BLSize DrawingCanvas::GetSize() const
{
	return BLSize(_width, _height);
}

void DrawingCanvas::Render(BLPoint pOrigin, 
						   BLSize pSize,
                           const std::function<void(BLContext&, BLPoint, BLSize)> pRender)
{
	BLContext ctx(_img);
	ctx.setCompOp(BL_COMP_OP_SRC_COPY);
	ctx.fillAll();
	pRender(ctx, pOrigin, pSize );
	ctx.end();
}


void DrawingCanvas::Render(const std::function<void(BLContext&, BLPoint, BLSize)> pRender)
{
	Render(BLPoint(0, 0), GetSize(), pRender);
}

void DrawingCanvas::WriteTo(ICanvasWriter& pTarget) const
{
	BLImageData data{};
	_img.getData(&data);

	auto* rows = static_cast<void**>(malloc(sizeof(void*) * data.size.h));
	auto* dataPointer = static_cast<char*>(data.pixelData);
	for (auto i = 0; i < data.size.h; i++, dataPointer += data.stride)
		rows[i] = dataPointer;
	pTarget.SaveFrame(_height, _width, rows);	
	free(rows);
}



