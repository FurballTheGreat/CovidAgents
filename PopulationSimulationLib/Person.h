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
#include <boost/date_time/gregorian/greg_date.hpp>


#include "CriticalSection.h"
#include "Enums.h"
#include "Infection.h"
#include "SmallArea.h"


class Commuter;
class Household;



class Person
{
private:
	DWORD _id;
	Household* _household;
	boost::gregorian::date _dateOfBirth;
	BiologicalSex _sex;
	int _cautionLevel = 0;
	DWORD _age;
	Infection* _infection = nullptr;
	SmallArea* _smallArea = nullptr;
	Commuter* _commuter = nullptr;
	std::vector<Variant*> _immuneTo;
	CriticalSection _infectionCriticalSection;
	bool _isImmune = false;
public:
	Person(DWORD pId, boost::gregorian::date pDateOfBirth, DWORD pAge, BiologicalSex pSex, int pCautionLevel);

	Infection* GetInfection() const;
	void SetInfection(Infection* pInfection);
	BiologicalSex GetSex() const;
	DWORD GetAge() const;
	void UpdateAge(boost::gregorian::date pCurrentDate);
	SmallArea* GetArea() const;
	void SetArea(SmallArea* pArea);

	Household* GetHousehold() const;
	void SetHousehold(Household* pHousehold);

	Commuter* GetCommuter() const;
	void SetCommuter(Commuter* pCommuter);

	bool IsImmune(Variant* pVariant);
};




