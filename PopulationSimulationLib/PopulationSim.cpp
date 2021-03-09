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

#include "PopulationSim.h"

#include <iostream>
#include <thread>
#include "SmallArea.h"
#include "SmallAreas.h"
#include "Person.h"
#include "Population.h"
#include "LocalElectoralArea.h"
#include "County.h"
#include "Region.h"
#include "SubRegion.h"
#include "RandomSource.h"
#include "NamedCode.h"
#include "Commuter.h"

void PopulationSim::BuildCommuters(RandomSource* pRandom)
{
	auto processor_count = std::thread::hardware_concurrency() / 2;
	if (processor_count == 0) processor_count = 1;
	auto numPerThread = _electoralAreas.size() / processor_count;
	auto size = _electoralAreas.size();
	auto areas = _electoralAreas;
	auto floating = std::vector<std::vector<std::tuple<LocalElectoralArea *, LocalElectoralAreaMovement* >>*>();
	auto smallAreas = _smallAreas;
	auto f = [numPerThread, size, areas,smallAreas, &floating, processor_count](DWORD threadNum) {
		auto min = (DWORD)(threadNum * numPerThread);
		auto max = threadNum == processor_count - 1 ? size : min + numPerThread;
		auto random = RandomSource();
		std::string msg = "\r\nThread=" + std::to_string(threadNum) + " Range=" + std::to_string(min) + "-" + std::to_string(max) + " floatingsize=" + std::to_string(floating[threadNum]->size()) + "\r\n";
		std::cout << msg;
	
		for (auto i = min; i <max; i++)
		{
			auto* desc = (*smallAreas->GetElectoralDistrictNames())[i];
			auto movementToAllocate = std::vector <LocalElectoralArea*>();
			auto  personsToAllocate = std::vector <Person*>();
			for (auto movement : (*desc->GetMovements()))
			{
				LocalElectoralArea* area = nullptr;
				switch (movement.GetType())
				{
				case MovementToEd:
					area = *std::find_if(
						areas.begin(), areas.end(),
						[&](const LocalElectoralArea* x) { return x->GetCode() == movement.GetOsiId(); });

					areas[i]->GetMovements()->push_back(
						LocalElectoralAreaMovement(movement.GetType(), area, movement.GetCount(), movement.GetDistance()));
					floating[threadNum]->push_back(std::tuple<LocalElectoralArea*, LocalElectoralAreaMovement*>(area, (new LocalElectoralAreaMovement(movement.GetType(), areas[i], movement.GetCount(), movement.GetDistance()))));


					for (DWORD j = 0; j < movement.GetCount(); j++)
						movementToAllocate.push_back(area);
					break;
				case MovementNotFixed:
					areas[i]->GetMovements()->push_back(
						LocalElectoralAreaMovement(movement.GetType(), nullptr, movement.GetCount(), movement.GetDistance()));

					for (DWORD j = 0; j < movement.GetCount(); j++)
						movementToAllocate.push_back(areas[i]);
					break;
				case MovementNone:
					areas[i]->GetMovements()->push_back(
						LocalElectoralAreaMovement(movement.GetType(), nullptr, movement.GetCount(), movement.GetDistance()));

					for (DWORD j = 0; j < movement.GetCount(); j++)
						movementToAllocate.push_back(areas[i]);

					break;
				}
			}
			for (auto* person : *areas[i]->GetPeople())
				personsToAllocate.push_back(person);

			if (!personsToAllocate.empty() && movementToAllocate.empty())
			{
				for (auto inward : (*areas[i]->GetInwardMovements()))
				{
					for (DWORD c = 0; c < inward.GetCount(); c++)
						movementToAllocate.push_back(inward.GetOther());
				}
			}
			
			auto movementToAllocateCopy = std::vector <LocalElectoralArea*>();
			for (auto movement : movementToAllocate)
				movementToAllocateCopy.push_back(movement);

			
			while (!personsToAllocate.empty() && !movementToAllocate.empty())
			{
				auto personIndex = random.Get<DWORD>(static_cast<DWORD>(personsToAllocate.size()));
				auto movementIndex = random.Get<DWORD>(static_cast<DWORD>(movementToAllocate.size()));
				auto commuter = new Commuter(personsToAllocate[personIndex], movementToAllocate[movementIndex]);
				areas[i]->GetOutwardCommuters().push_back(commuter);
				personsToAllocate[personIndex]->SetCommuter(commuter);
				personsToAllocate.erase(personsToAllocate.begin() + personIndex);
				movementToAllocate.erase(movementToAllocate.begin() + movementIndex);
			}

			

			while (!personsToAllocate.empty() && !movementToAllocateCopy.empty())
			{
				auto personIndex = random.Get<DWORD>(static_cast<DWORD>(personsToAllocate.size()));
				auto movementIndex = random.Get<DWORD>(static_cast<DWORD>(movementToAllocateCopy.size()));
				auto commuter = new Commuter(personsToAllocate[personIndex], movementToAllocateCopy[movementIndex]);
				areas[i]->GetOutwardCommuters().push_back(commuter);
				personsToAllocate[personIndex]->SetCommuter(commuter);
				personsToAllocate.erase(personsToAllocate.begin() + personIndex);
			}
		}
		
	};

	auto threads = std::vector<std::thread*>();
	for (DWORD n = 0; n < processor_count; n++) {
		floating.push_back(new std::vector<std::tuple<LocalElectoralArea*, LocalElectoralAreaMovement* >>());
		threads.push_back(new std::thread(f, n));
	}

	for (DWORD n = 0; n < processor_count; n++)
	{
		threads[n]->join();
		for (auto commuter : *floating[n])
			std::get<0>(commuter)->GetInwardMovements()->push_back(*std::get<1>(commuter));
		delete threads[n];
		delete floating[n];

	}

	for (auto area : _electoralAreas)
		for (auto commuter : area->GetOutwardCommuters())
			commuter->GetDestination()->GetInwardCommuters().push_back(commuter);
	
	
}

PopulationSim::PopulationSim(RandomSource* pRandom, Population* pPopulation, SmallAreas* pSmallAreas, boost::gregorian::date pCurrentDate) : _population(pPopulation), _smallAreas(pSmallAreas), _currentDate(pCurrentDate)
{
	std::vector<Person*> floatingPeople;
	_smallAreas->BuildPeople(pRandom, pPopulation, pCurrentDate, &floatingPeople);
	std::cout << "Distributing remaining people\r\n";
	_smallAreas->DistributeFloating(pRandom, &floatingPeople);
	_smallAreas->DistributeRemainingFloatingPeople(pRandom, &floatingPeople);
	if (floatingPeople.size() > 0) std::cout << "Still got " << std::to_string(floatingPeople.size()) << "\r\n";
	std::cout << "Splitting people into electoral areas, counties, sub-regions and regions\r\n";
	for (auto* const lea : (*_smallAreas->GetElectoralDistrictNames()))
		_electoralAreas.push_back(new LocalElectoralArea(lea));

	


	for (auto* county : (*_smallAreas->GetCountyCodes()))
		_counties.push_back(new County(county->GetName()));

	for (auto* region : (*_smallAreas->GetRegionCodes()))
		_regions.push_back(new Region(region->GetName()));

	for (auto* subRegion : (*_smallAreas->GetSubRegionCodes()))
		_subRegions.push_back(new SubRegion(subRegion->GetName()));
	for(auto area : (*_smallAreas->GetAreas()))
	{
		if (area->GetId() % 1000 == 0)
			std::cout << area->GetId() << "\r\n";
		DWORD index = 0;
		LocalElectoralArea* lea = nullptr;
		for(auto ed : (*_smallAreas->GetElectoralDistrictNames()))
		{
			if(ed== area->GetElectoralDistrictDesc())
			{
				lea = _electoralAreas[index];				
				break;
			}
			index++;
		}
		index = 0;
		County* county  = nullptr;
		for (auto cy : (*_smallAreas->GetCountyCodes()))
		{
			if (cy == area->GetCountyCode())
			{
				county = _counties[index];
				break;
			}
			index++;
		}

		index = 0;
		Region* region = nullptr;
		for (auto reg : (*_smallAreas->GetRegionCodes()))
		{
			if (reg == area->GetRegionCode())
			{
				region = _regions[index];
				break;
			}
			index++;
		}

		index = 0;
		SubRegion* subRegion = nullptr;
		for (auto sub : (*_smallAreas->GetSubRegionCodes()))
		{
			if (sub == area->GetSubRegionCode())
			{
				subRegion = _subRegions[index];
				break;
			}
			index++;
		}

		area->SetElectoralArea(lea);
		lea->SetCounty(county);
		lea->SetRegion(region);
		lea->SetSubRegion(subRegion);
		lea->GetAreas()->push_back(area);
		county->SetRegion(region);
		county->SetSubRegion(subRegion);
		if (!std::count(county->GetAreas()->begin(), county->GetAreas()->end(), lea))
			county->GetAreas()->push_back(lea);
		subRegion->SetRegion(region);
		if (!std::count(subRegion->GetCounties()->begin(), subRegion->GetCounties()->end(), county))
			subRegion->GetCounties()->push_back(county);
		if (!std::count(region->GetSubRegions()->begin(), region->GetSubRegions()->end(), subRegion))
			region->GetSubRegions()->push_back(subRegion);
		for(auto* person : (*area->GetPeople()))
		{
			lea->GetPeople()->push_back(person);
			county->GetPeople()->push_back(person);
			subRegion->GetPeople()->push_back(person);
			region->GetPeople()->push_back(person);
		}

		for(auto* household : (*area->GetHouseholds()))
		{
			lea->GetHouseholds()->push_back(household);
			county->GetHouseholds()->push_back(household);
			subRegion->GetHouseholds()->push_back(household);
			region->GetHouseholds()->push_back(household);
		}
		

	}


	
	BuildCommuters(pRandom);


	
	std::sort(_counties.begin(), _counties.end(),
		[](const County* a, const County* b) -> bool
		{
			return a->GetName() < b->GetName();
		});

	std::sort(_electoralAreas.begin(), _electoralAreas.end(),
		[](const LocalElectoralArea* a, const LocalElectoralArea* b) -> bool
		{
			return a->GetName() < b->GetName();
		});
}

SmallAreas* PopulationSim::GetSmallAreas() const
{
	return _smallAreas;
}


std::vector<LocalElectoralArea*>* PopulationSim::GetElectoralAreas()
{
	return &_electoralAreas;
}

std::vector<County*>* PopulationSim::GetCounties()
{
	return &_counties;
}

std::vector<SubRegion*>* PopulationSim::GetSubRegions()
{
	return &_subRegions;
}

std::vector<Region*>* PopulationSim::GetRegions()
{
	return &_regions;
}

boost::gregorian::date PopulationSim::GetDate() const
{
	return _currentDate;
}

void PopulationSim::AddDay()
{
	_currentDate = _currentDate + boost::gregorian::days(1);
	_population->UpdateCurrentDate(_currentDate);
	_dayIndex++;
}

Population& PopulationSim::GetPopulation() const
{
	return *_population;
}

DWORD PopulationSim::GetDayIndex() const
{
	return _dayIndex;
}
