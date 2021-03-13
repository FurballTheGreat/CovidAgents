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

#include "MapPlotter.h"

#include <blend2d.h>
#include <iostream>
#include <GeographicLib/GeoCoords.hpp>

#include "DrawingFont.h"
#include "SmallArea.h"
#include "LocalElectoralArea.h"

#define MIN_EASTING 340118

MapPlotter::MapPlotter(std::vector<SmallArea*>* pAreas): _areas(pAreas)
{
    for (auto* area : *_areas)
        for (auto poly : *area->GetPolygons())
	        for (auto cord : *poly.GetCoordinates())
	        {
                if (cord.Easting() < MIN_EASTING) continue;
		        if (_maxNorthing < 1 || _maxEasting < 1)
		        {
			        _minNorthing = _maxNorthing = cord.Northing();
			        _minEasting = _maxEasting = cord.Easting();
		        }

		        if (cord.Northing() < _minNorthing) _minNorthing = cord.Northing();
		        if (cord.Northing() > _maxNorthing) _maxNorthing = cord.Northing();
		        if (cord.Easting() < _minEasting) _minEasting = cord.Easting();
		        if (cord.Easting() > _maxEasting) _maxEasting = cord.Easting();
	        }
}

void MapPlotter::PlotMap(BLContext& pContext, BLPoint pOrigin, BLSize pSize, boost::gregorian::date pDate, std::function<void(SmallArea&, BLContext&)> pApplyAreaStyle) const
{
	const auto rawWidth = _maxEasting - _minEasting;
	const auto rawHeight = _maxNorthing - _minNorthing;
	const auto scale = rawWidth/pSize.w > rawHeight/pSize.h ? rawWidth / pSize.w : rawHeight / pSize.h;
    const auto height = rawHeight / scale;


	const BLRgba32 color(245, 193, 137);
    pContext.setFillStyle(color);
    pContext.fillRect(pOrigin.x, pOrigin.y, pSize.w, pSize.h);

    for (auto* area : (*_areas))
    {
        for (auto poly : *(area->GetPolygons()))
        {
            BLArray<BLPoint> coords;
        	
            auto foundBad = false;
            for (auto cord : *(poly.GetCoordinates()))
            {
                if (cord.Easting() < MIN_EASTING) {
                    std::cout<< " " << std::to_string(cord.Easting())<< " " <<  std::to_string(_minEasting+scale*100);
                    foundBad = true;
                }
            	coords.append(BLPoint((cord.Easting() - _minEasting) / scale + pOrigin.x, height - (cord.Northing() - _minNorthing) / scale + pOrigin.y));
            }

            if (!foundBad) {
                
                pContext.setCompOp(BL_COMP_OP_SRC_OVER);
                pApplyAreaStyle(*area, pContext);
                
                pContext.fillPolygon(coords.view());
            }
        }
    }
}
