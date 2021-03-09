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

#include <string>
#include <vector>

#include "Common.h"


class Person;
class RandomSource;

namespace boost {
	namespace gregorian {
		class date;
	}
}

class Population;
class SmallArea;
class NamedCode;
class LedDescription;

class SmallAreas
{
private:
	std::vector<NamedCode*> _regions;
	std::vector<NamedCode*> _subRegions;
	std::vector<NamedCode*> _counties;
	std::vector<LedDescription*> _electoralDistricts;
	std::vector<SmallArea*> _areas;

public:
	SmallAreas(const std::string pFileName);

	void BuildPeople(RandomSource* pRandom, Population* pPopulation, boost::gregorian::date pCurrentDate, std::vector<Person*>* pFloatingPeople);
	void DistributeFloating(RandomSource* pRandom, std::vector<Person*>* pFloatingPeople);
	void DistributeRemainingFloatingPeople(RandomSource* pRandom, std::vector<Person*>* pFloatingPeople);
	DWORD GetHouseholdCount() const;
	DWORD GetPopulationCount() const;

	std::vector<NamedCode*>* GetRegionCodes();
	std::vector<NamedCode*>* GetSubRegionCodes();;
	std::vector<NamedCode*>* GetCountyCodes();
	std::vector<LedDescription*>* GetElectoralDistrictNames();
	std::vector<SmallArea*>* GetAreas();

	
		
	
};

