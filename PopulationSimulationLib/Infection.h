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

class PopulationSim;
class RandomSource;
class Person;
class Variant;

class Infection
{
private:
	boost::gregorian::date _infectedDate;
	DWORD _dayIndex;
	PopulationSim& _populationSim;
	Variant* _variant;
	std::vector<double> _infectiousnessByDay;
public:
	Infection(RandomSource& pRandom, Variant* pVariant, PopulationSim &pPopulationSim);
	~Infection() = default;

	boost::gregorian::date GetInfectedDate() const;
	DWORD GetDaysInfected() const;
	Variant* GetVariant() const;
	Infection* ProcessContact(RandomSource& pRandom, Person* pSourcePerson, Person* pContact);
	bool CheckIfStillInfectious() const;
	bool IsActiveYet() const;
};

