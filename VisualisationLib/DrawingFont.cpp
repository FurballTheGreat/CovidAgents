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
#include "DrawingFont.h"

DrawingFont::DrawingFont(std::string pFontFileName, double pSize): _size(pSize) {
	BLResult err = _fontData.createFromFile(pFontFileName.c_str());
	err = _fontFace.createFromData(_fontData, 0);
	_font.createFromFace(_fontFace, static_cast<float>(pSize));
}

void DrawingFont::DrawUtf8(BLContext& pContext, BLPoint pWhere, std::string pText) const
{
	pContext.fillUtf8Text(BLPoint(pWhere.x, pWhere.y), _font, pText.c_str());
}

double DrawingFont::GetSize() const
{
	return _size;
}
