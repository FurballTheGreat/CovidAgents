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

#include "BasePopulationContainer.h"

BasePopulationContainer::BasePopulationContainer(std::wstring pName)
{
	_name = pName;
}

std::wstring BasePopulationContainer::GetName() const
{
	return _name;
}

std::vector<Person*>* BasePopulationContainer::GetPeople()
{
	return &_people;
}

std::vector<Household*>* BasePopulationContainer::GetHouseholds()
{
	return &_households;
}

void BasePopulationContainer::AddInfectedPerson(Person* pPerson)
{
	_section.Enter();
	_infectedPeople.insert(pPerson);
	_section.Leave();
}

void BasePopulationContainer::RemoveInfectedPerson(Person* pPerson)
{
	_section.Enter();
	_infectedPeople.erase(pPerson);
	_section.Leave();
}

DWORD BasePopulationContainer::GetInfectedPeopleSize()
{
	_section.Enter();
	auto result = _infectedPeople.size();
	_section.Leave();
	return static_cast<DWORD>(result);
}


