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
#include "Person.h"


#include <iostream>
#include <boost/date_time/gregorian/gregorian_types.hpp>

using namespace boost::gregorian;


template<typename Iterator, typename Date>
struct date_count : public std::pair<unsigned, Date> {
	typedef std::pair<unsigned, Date> p;
	operator unsigned() { return p::first; }
	operator Date() { return p::second; }
	date_count(Date begin, Date end) : p(0, begin) {
		Iterator b{ begin };
		while (*++b <= end)
			++p::first;
		p::second = *--b;
	}
};


Person::Person(DWORD pId, boost::gregorian::date pDateOfBirth, DWORD pAge, BiologicalSex pSex, int pCautionLevel): _age(pAge) {
	_id = pId;
	_dateOfBirth = pDateOfBirth;
	_sex = pSex;
	_cautionLevel = pCautionLevel;
	_household = nullptr;
	_infectionCriticalSection = CriticalSection();
}

Infection* Person::GetInfection() const
{
	return _infection;
}

void Person::SetInfection(Infection* pInfection)
{
	_infectionCriticalSection.Enter();
	
	if (pInfection)
		_smallArea->AddInfectedPerson(this);
	else {
		if(_infection!=nullptr)
		{

			_isImmune = true;
			//_immuneTo.push_back(_infection->GetVariant());
		}
		_smallArea->RemoveInfectedPerson(this);
	}
	_infection = pInfection;
	
	_infectionCriticalSection.Leave();
}

BiologicalSex Person::GetSex() const
{
	return _sex;
}

DWORD Person::GetAge() const
{
	return _age;
}

void Person::UpdateAge(boost::gregorian::date pCurrentDate)
{
	//date_count<year_iterator, date> years(_dateOfBirth, pCurrentDate);
	//_age = years;
}

SmallArea* Person::GetArea() const
{
	return _smallArea;
}

void Person::SetArea(SmallArea* pArea)
{
	_smallArea = pArea;
}

Household* Person::GetHousehold() const
{
	return _household;
}

void Person::SetHousehold(Household* pHousehold)
{
	if (pHousehold == nullptr)
		std::cout << "Null Household Set" << "\r\n";
	_household = pHousehold;
}

Commuter* Person::GetCommuter() const
{
	return _commuter;
}

void Person::SetCommuter(Commuter* pCommuter)
{
	_commuter = pCommuter;
}

bool Person::IsImmune(Variant* pVariant)
{
	/*for (auto variant : _immuneTo)
		if (variant == pVariant)
			return true;*/
	return _isImmune;// false;
}
