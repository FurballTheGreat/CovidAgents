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
#include <set>
#include <string>
#include <vector>
#include "Common.h"
#include "CriticalSection.h"

class SmallArea;
class Person;
class Household;
class BasePopulationContainer
{
private:
	std::wstring _name;	
	std::set<Person*> _infectedPeople;
	CriticalSection _section;
protected:
	std::vector<Person*> _people;
	std::vector<Household*> _households;
public:
	BasePopulationContainer(std::wstring pName);
	std::wstring GetName() const;
	std::vector<Person*>* GetPeople();
	std::vector<Household*>* GetHouseholds();
	virtual void AddInfectedPerson(Person* pPerson);
	virtual void RemoveInfectedPerson(Person* pPerson);
	DWORD GetInfectedPeopleSize() ;
};

