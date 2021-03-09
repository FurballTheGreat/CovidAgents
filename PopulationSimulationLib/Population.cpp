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

#include "Population.h"

#include <cstdlib>
#include <thread>

#include "boost/date_time.hpp"
#include "PopulationDistributionDefinition.h"
#include "RandomSource.h"
#include "Person.h"

using namespace boost::gregorian;


Population::Population(PopulationDistributionDefinition* pDefinition): _definition(pDefinition) {
	_people = static_cast<Person*>(malloc(pDefinition->TotalPopulation() * sizeof(Person)));
	_size = 0;
	_maxSize = pDefinition->TotalPopulation();
}

DWORD Population::GetSize() const
{
	return  _size;
}

Person* Population::GetPeople()
{
	return _people;
}

Person* Population::GeneratePeople(RandomSource* pRandom, BiologicalSex pSex, DWORD pMinAge, DWORD pMaxAge,
	boost::gregorian::date pGenerationDate, DWORD pNum)
{
	_section.Enter();
	auto personIndex = _size;
	_size += pNum;
	_section.Leave();
	
	const auto count = _definition->Count();

	auto range = pMaxAge - pMinAge;
	auto result = _people + personIndex;
	std::vector<DWORD> ages;
	for(auto i = pMinAge; i<pMaxAge; i++)
	{
		if (_definition->Get(i,pSex)->Count > 0)
			ages.push_back(i);
	}

	
	while(pNum>0)
	{
		const auto random = (pRandom->Get<DWORD>() % ages.size());
		_section.Enter();
		const auto def = _definition->Get(ages[random],pSex);
		auto hasDef = def->Count > 0;
		_section.Leave();
		
		if(hasDef)
		{
			auto cautionLevel = pRandom->Get<int>() % 10;
			auto birthdate = pGenerationDate - years(def->Age + 1) + days(1);
			new(&_people[personIndex]) Person(personIndex, birthdate + days(pRandom->Get<DWORD>() % 364), ages[random], pSex,cautionLevel);

			_section.Enter();
			if (def->Count > 0) {
				def->Count--;
				pNum--;
				personIndex++;
			}
			_section.Leave();
		}		
	}
		

	return result;
}
const auto processor_count = std::thread::hardware_concurrency();

void Population::UpdateCurrentDate(const boost::gregorian::date& pDate) const
{
	auto numPerThread = _size / processor_count;
	auto size = _size;
	auto people = _people;
	auto f = [numPerThread, size, people, pDate](DWORD j) {
		auto min = (DWORD)(j * numPerThread);
		auto max = j == processor_count - 1 ? size - min : min+numPerThread;

		for (DWORD i = min; i < max; i++)
			people[i].UpdateAge(pDate);
	};

	auto threads = std::vector<std::thread*>();
	for(DWORD n = 0;n < processor_count; n++)
		threads.push_back(new std::thread(f, n));

	for (auto thread : threads)
		thread->join();

}
