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
#include <functional>
#include <string>
#include <vector>
#include <blend2d.h>
#include <boost/date_time/gregorian/greg_date.hpp>
class DrawingFont;
class SmallArea;

class MapPlotter
{
private:
	std::vector<SmallArea*>* _areas;
    double _minNorthing = 0;
	double _maxNorthing = 0;
    double _minEasting = 0;
	double _maxEasting = 0;
public:
	MapPlotter(std::vector<SmallArea*>* pAreas);

	void PlotMap(BLContext& pContext, BLPoint pOrigin, BLSize pSize, boost::gregorian::date pDate, std::function<void(SmallArea&, BLContext&)> pApplyAreaStyle) const;
};

