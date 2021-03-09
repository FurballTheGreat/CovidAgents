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
#include <boost/date_time/gregorian/greg_date.hpp>

#include "Common.h"

class Person;
class Region;
class SubRegion;
class County;
class LocalElectoralArea;
class Population;
class SmallAreas;
class RandomSource;

class PopulationSim
{
private:
	boost::gregorian::date _currentDate;

	Population* _population;
	SmallAreas* _smallAreas;
	std::vector<LocalElectoralArea*> _electoralAreas;
	std::vector<County*> _counties;
	std::vector<SubRegion*> _subRegions;
	std::vector<Region*> _regions;
	DWORD _dayIndex;

public:
	void BuildCommuters(RandomSource* pRandom);
	PopulationSim(RandomSource* pRandom, Population* pPopulation, SmallAreas* pSmallAreas, boost::gregorian::date pCurrentDate);
	SmallAreas* GetSmallAreas() const;
	std::vector<LocalElectoralArea*>* GetElectoralAreas();
	std::vector<County*>* GetCounties();
	std::vector<SubRegion*>* GetSubRegions();
	std::vector<Region*>* GetRegions();
	boost::gregorian::date GetDate()  const;
	void AddDay();
	Population& GetPopulation() const;
	DWORD GetDayIndex() const;
};

