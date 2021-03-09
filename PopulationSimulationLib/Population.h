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
#include "CriticalSection.h"
#include "Enums.h"
#include <boost/date_time/gregorian/greg_date.hpp>

class RandomSource;
class PopulationDistributionDefinition;
class Household;
class Person;


class Population
{
private:
	CriticalSection _section = CriticalSection();
	Person* _people;
	DWORD _size;
	DWORD _maxSize;
	PopulationDistributionDefinition* _definition;
	
public:
	Population(PopulationDistributionDefinition *pDefinition);
	DWORD GetSize() const;
	Person* GetPeople();
	Person* GeneratePeople(RandomSource* pRandom, BiologicalSex pSex,DWORD pMinAge, DWORD pMaxAge, boost::gregorian::date pGenerationDate, DWORD pNum);
	void UpdateCurrentDate(const boost::gregorian::date& pDate) const;
};

