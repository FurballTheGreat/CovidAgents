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
#include "SmallAreas.h"
#include "SmallArea.h"
#include "NamedCode.h"
#include <fstream>
#include <iostream>
#include <thread>


#include "Exceptions.h"
#include "Household.h"
#include "Person.h"
#include "VectorTaskThreader.h"

#define MAGIC 0xBAADBE1F

SmallAreas::SmallAreas(const std::string pFileName)
{
	std::ifstream input(pFileName, std::ios::binary);
	if (!input)
		throw InvalidCensusSapsFileSizeException();
	DWORD magic;
	DWORD count;
	if(!input.read(reinterpret_cast<char*>(&magic), sizeof(DWORD)))
		throw InvalidCensusSapsFileSizeException();
	
	if (magic != MAGIC)
		throw InvalidCensusSapsFileMagicException();

	if (!input.read(reinterpret_cast<char*>(&count), sizeof(DWORD)))
		throw InvalidCensusSapsFileSizeException();
	for(DWORD i = 0; i < count; i++)
	    _regions.push_back(new NamedCode(&input));

	if (!input.read(reinterpret_cast<char*>(&count), sizeof(DWORD)))
		throw InvalidCensusSapsFileSizeException();
	for (DWORD i = 0; i < count; i++)
		_subRegions.push_back(new NamedCode(&input));

	if (!input.read(reinterpret_cast<char*>(&count), sizeof(DWORD)))
		throw InvalidCensusSapsFileSizeException();
	for (DWORD i = 0; i < count; i++)
		_counties.push_back(new NamedCode(&input));

	if (!input.read(reinterpret_cast<char*>(&count), sizeof(DWORD)))
		throw InvalidCensusSapsFileSizeException();
	for (DWORD i = 0; i < count; i++) {
		_electoralDistricts.push_back(new LedDescription(&input));
	}
	
	if (!input.read(reinterpret_cast<char*>(&count), sizeof(DWORD)))
		throw InvalidCensusSapsFileSizeException();

	for(DWORD i = 0; i < count;i++)
	{
		DWORD objectID;
		DWORD region;
		DWORD subRegion;
		DWORD county;
		DWORD electoralDistrict;
		double shapeArea;
		if (!input.read(reinterpret_cast<char*>(&objectID), sizeof(DWORD)))
			throw InvalidCensusSapsFileSizeException();
		if (!input.read(reinterpret_cast<char*>(&region), sizeof(DWORD)))
			throw InvalidCensusSapsFileSizeException();
		if (!input.read(reinterpret_cast<char*>(&subRegion), sizeof(DWORD)))
			throw InvalidCensusSapsFileSizeException();
		if (!input.read(reinterpret_cast<char*>(&county), sizeof(DWORD)))
			throw InvalidCensusSapsFileSizeException();
		if (!input.read(reinterpret_cast<char*>(&electoralDistrict), sizeof(DWORD)))
			throw InvalidCensusSapsFileSizeException();
		if (!input.read(reinterpret_cast<char*>(&shapeArea), sizeof(shapeArea)))
			throw InvalidCensusSapsFileSizeException();
		if (shapeArea < 100)
			shapeArea *= 1000;
		_areas.push_back(new SmallArea(
			objectID,
			_regions[region],
			_subRegions[subRegion],
			_counties[county],
			_electoralDistricts[electoralDistrict],
			shapeArea,
			&input));
	}
	

}

void SmallAreas::BuildPeople(RandomSource* pRandom, Population* pPopulation, boost::gregorian::date pCurrentDate, std::vector<Person*>* pFloatingPeople)
{
	VectorTaskThreader().Process<std::vector<SmallArea*>, std::vector<Person*>>(
		&_areas,
		[&](std::vector<SmallArea*>* pItems, DWORD pMin, DWORD pMax, std::vector<Person*>* pResults)
		{
			RandomSource random;
			std::string msg = "\r\n Range=" + std::to_string(pMin) + "-" + std::to_string(pMax) + " floatingsize=" + std::to_string(pResults->size()) + "\r\n";
			std::cout << msg;
			for (DWORD i = pMin; i < pMax; i++) {
				_areas[i]->BuildPeople(&random, pPopulation, pCurrentDate, pResults);
			}
		},
		[&](std::vector<std::vector<Person*>*>* pAllResults)
		{
			for(auto* threadResult : *pAllResults)
				for (auto* person : *threadResult)
					pFloatingPeople->push_back(person);
		});
}

void SmallAreas::DistributeFloating(RandomSource* pRandom, std::vector<Person*>* pFloatingPeople)
{
	for (auto* area : _areas)
		area->DistributeFloating(pRandom, pFloatingPeople);
}

void SmallAreas::DistributeRemainingFloatingPeople(RandomSource* pRandom, std::vector<Person*>* pFloatingPeople)
{
	for (int i = 0; !pFloatingPeople->empty(); i++)
	{
		const auto area = pRandom->Get<DWORD>(static_cast<DWORD>(_areas.size()));
		auto* household = new Household(
			_areas[area], 0, 
			PrivateHouseholdsType::TwoOrMoreNonrelatedPersonsHouseholds, 
			pFloatingPeople);
		const auto size = pRandom->Get<DWORD>(1, 4);

		for (int j = 0; !pFloatingPeople->empty() && j < static_cast<int>(size); j++)
		{
			if (pFloatingPeople->empty()) break;
			auto k = pRandom->Get<DWORD>(static_cast<DWORD>(pFloatingPeople->size()));
			household->Add((*pFloatingPeople)[k]);
			pFloatingPeople->erase(pFloatingPeople->begin() + k);
		}

		
		if (household->GetSize())
			_areas[area]->AddHousehold(household);
		else
			delete household;
	}
}

DWORD SmallAreas::GetHouseholdCount() const
{
	DWORD result = 0;
	for(auto *area : _areas)
		result += area->GetHouseholdCount();
	return result;
}

DWORD SmallAreas::GetPopulationCount() const
{
	DWORD result = 0;
	for (auto* area : _areas)
		result += area->GetPopulationCount();
	return result;
}

std::vector<NamedCode*>* SmallAreas::GetRegionCodes()
{
	return &_regions;
}

std::vector<NamedCode*>* SmallAreas::GetSubRegionCodes()
{
	return &_subRegions;
}

std::vector<NamedCode*>* SmallAreas::GetCountyCodes()
{
	return &_counties;
}

std::vector<LedDescription*>* SmallAreas::GetElectoralDistrictNames()
{
	return &_electoralDistricts;
}

std::vector<SmallArea*>* SmallAreas::GetAreas()
{
	return &_areas;
}
