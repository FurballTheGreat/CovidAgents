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
#include "Common.h"

class Variant;
class Infection;
class RandomSource;
class County;
class Person;
class PopulationSim;

class SimpleInfectionSimulator
{
private:
	PopulationSim& _population;
	std::set<Person*> _infected;

	void InfectPerson(RandomSource& pRandom, Person* pPerson, Variant* pVariant);
public:
	SimpleInfectionSimulator(PopulationSim& pPopulation);

	void Seed(RandomSource &pRandomSource, Variant* pVariant, DWORD pCount);
	void Seed(RandomSource& pRandomSource, Variant* pVariant, County* pCounty, DWORD pCount);

	void ProceedDay(
		RandomSource& pRandomSource, 
		DWORD pMinJobContacts,
		DWORD pMaxJobContacts,
		DWORD pMinLocalContact,
		DWORD pMaxLocalContacts);

	DWORD GetTotalCurrentlyInfected() const;

	PopulationSim& GetPopulation() const;
};

