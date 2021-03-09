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
#include "SmallAreaPolygon.h"
#include <fstream>
#include "Common.h"

#include "Exceptions.h"
struct LatLon
{
	double Lon;
	double Lat;

};

SmallAreaPolygon::SmallAreaPolygon(std::ifstream* pStream)
{
	DWORD num;

	if (!pStream->read(reinterpret_cast<char*>(&num), sizeof(DWORD)))
		throw InvalidCensusSapsFileSizeException();
	GeoCoords c;
	for(DWORD i = 0; i < num; i++)
	{
		LatLon item;
		if (!pStream->read(reinterpret_cast<char*>(&item), sizeof(item)))
			throw InvalidCensusSapsFileSizeException();
		_coordinates.push_back(GeoCoords(item.Lat, item.Lon));
	}
}

std::vector<GeoCoords>* SmallAreaPolygon::GetCoordinates()
{
	return &_coordinates;
}
