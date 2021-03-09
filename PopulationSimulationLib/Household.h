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
#include <vector>
#include "CensusSAPS.h"

#include "Common.h"
#include "Enums.h"
#include "RandomSource.h"

namespace boost {
	namespace gregorian {
		class date;
	}
}

class Person;
class SmallArea;

class Household
{
private:
	SmallArea* _area;
	DWORD _targetSize;
	std::vector<Person*> _people;
	PrivateHouseholdsType _type;
	std::vector<Person*>* _source;

	Person* AddFromSource(RandomSource* pRandom, DWORD pMinAge, DWORD pMaxAge, BiologicalSex *pSex, boost::gregorian::date pCurrentDate);
	void AddCouple(RandomSource* pRandom, DWORD pMinAge, DWORD  pMaxAge, boost::gregorian::date pCurrentDate, Person** pPerson1, Person** pPerson2);
public:
	Household(SmallArea* pArea, DWORD _targetSize,PrivateHouseholdsType pType, std::vector<Person*> *pSource);

	void Add(Person* pPerson);
	void Remove(Person* pPerson);

	void Build(RandomSource* pRandom, boost::gregorian::date pCurrentDate);

	DWORD GetTargetSize() const;
	DWORD GetSize() const;

	std::vector<Person*>* GetMembers();
};

