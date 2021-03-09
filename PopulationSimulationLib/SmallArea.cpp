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
#include "SmallArea.h"
#include <fstream>

#include "County.h"
#include "Exceptions.h"
#include "Population.h"
#include "Person.h"
#include "Household.h"
#include "LocalElectoralArea.h"
#include "NamedCode.h"
#include "RandomSource.h"
#include "SubRegion.h"
#include "Region.h"


void SmallArea::AllocateForAgeRange(RandomSource* pRandom, Population* pPopulation, boost::gregorian::date pCurrentDate,
                                    BiologicalSex pSex, DWORD pMinAge,  DWORD pMaxAge, DWORD pNum)
{
	if (!pNum) return;
	Person* people = pPopulation->GeneratePeople(pRandom, pSex, pMinAge, pMaxAge, pCurrentDate, pNum);
	for (DWORD i = 0; i < pNum; i++, people++) {
		people->SetArea(this);
		_people.push_back(people);
	}
}



void SmallArea::CalculateMinMaxHouseSize(PrivateHouseholdsType pType, DWORD* pMin, DWORD* pMax)
{
	switch (static_cast<PrivateHouseholdsType>(pType))
	{
	case PrivateHouseholdsType::OnePersonHouseholds:
		*pMin = 1;
		*pMax = 1;
		break;
	case PrivateHouseholdsType::MarriedCoupleHouseholds:
	case PrivateHouseholdsType::CohabitingCoupleHouseholds:
		*pMin = 2;
		*pMax = 2;
		break;
	case PrivateHouseholdsType::MarriedCoupleWithChildrenHouseholds:
	case PrivateHouseholdsType::CohabitingCoupleWithChildrenHouseholds:
	case PrivateHouseholdsType::TwoOrMoreFamilyUnitsHouseholds:
	case PrivateHouseholdsType::NonfamilyHouseholdsAndRelationsHouseholds:
	case PrivateHouseholdsType::TwoOrMoreNonrelatedPersonsHouseholds:
		*pMin = 2;
		*pMax = 8;
		break;
	case PrivateHouseholdsType::OneParentFamilyFatherWithChildrenHouseholds:
	case PrivateHouseholdsType::OneParentFamilyMotherAndChildrenHouseholds:
		*pMin = 1;
		*pMax = 8;
		break;

	case PrivateHouseholdsType::CoupleAndOthersHouseholds:
	case PrivateHouseholdsType::OneParentFamilyFatherWithChildrenAndOthersHouseholds:
	case PrivateHouseholdsType::OneParentFamilyMotherWithChildrenAndOthersHouseholds:
		*pMin = 3;
		*pMax = 8;
		break;
	case PrivateHouseholdsType::CoupleWithChildrenAndOthersHouseholds:
		*pMin = 4;
		*pMax = 8;
		break;
	default:
		throw InvalidCodeException();		
	}
}



SmallArea::SmallArea(
	DWORD pId, NamedCode* pRegion, NamedCode* pSubRegion, NamedCode* pCounty,
	LedDescription* pElectoralDistrict, double pShapeArea, std::ifstream* pStream) : BasePopulationContainer(std::to_wstring(pId)),
		_id(pId),
		_region(pRegion),
		_subRegion(pSubRegion),
		_county(pCounty),
		_electoralDistrict(pElectoralDistrict),
		_shapeArea(pShapeArea)
{
	_definition = static_cast<SmallPopulationAreaDefinition*>(malloc(sizeof(SmallPopulationAreaDefinition)));
	if (!pStream->read(reinterpret_cast<char*>(_definition), sizeof(SmallPopulationAreaDefinition)))
		throw InvalidCensusSapsFileSizeException();
	DWORD polygonCount;
	if (!pStream->read(reinterpret_cast<char*>(&polygonCount), sizeof(DWORD)))
		throw InvalidCensusSapsFileSizeException();
	for(DWORD i = 0; i < polygonCount;i++)
	{
		_polygons.push_back(SmallAreaPolygon(pStream));
	}
}

void SmallArea::BuildPeople(RandomSource *pRandom, Population* pPopulation, boost::gregorian::date pCurrentDate, std::vector<Person*>* pFloatingPeople)
{
	auto ageDist = _definition->PopulationAged019BySexAndYearOfAgePersonsAged20YearsAndOverBySexAndAgeGroup;
    	
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 0, 1, ageDist.Age0Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 1, 2, ageDist.Age1Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 2, 3, ageDist.Age2Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 3, 4, ageDist.Age3Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 4, 5, ageDist.Age4Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 5, 6, ageDist.Age5Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 6, 7, ageDist.Age6Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 7, 8, ageDist.Age7Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 8, 9, ageDist.Age8Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 9, 10, ageDist.Age9Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 10, 11, ageDist.Age10Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 11, 12, ageDist.Age11Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 12, 13, ageDist.Age12Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 13, 14, ageDist.Age13Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 14, 15, ageDist.Age14Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 15, 16, ageDist.Age15Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 16, 17, ageDist.Age16Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 17, 18, ageDist.Age17Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 18, 19, ageDist.Age18Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 19, 20, ageDist.Age19Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 20, 25, ageDist.Age20To24Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 25, 30, ageDist.Age25To29Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 30, 35, ageDist.Age30To34Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 35, 40, ageDist.Age35To39Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 40, 45, ageDist.Age40To44Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 45, 50, ageDist.Age45To49Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 50, 55, ageDist.Age50To54Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 55, 60, ageDist.Age55To59Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 60, 65, ageDist.Age60To64Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 65, 70, ageDist.Age65To69Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 70, 75, ageDist.Age70To74Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 75, 80, ageDist.Age75To79Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 80, 85, ageDist.Age80To84Males);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Male, 85, 101, ageDist.Age85AndOverMales);
	
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 0, 1, ageDist.Age0Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 1, 2, ageDist.Age1Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 2, 3, ageDist.Age2Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 3, 4, ageDist.Age3Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 4, 5, ageDist.Age4Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 5, 6, ageDist.Age5Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 6, 7, ageDist.Age6Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 7, 8, ageDist.Age7Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 8, 9, ageDist.Age8Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 9, 10, ageDist.Age9Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 10, 11, ageDist.Age10Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 11, 12, ageDist.Age11Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 12, 13, ageDist.Age12Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 13, 14, ageDist.Age13Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 14, 15, ageDist.Age14Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 15, 16, ageDist.Age15Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 16, 17, ageDist.Age16Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 17, 18, ageDist.Age17Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 18, 19, ageDist.Age18Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 19, 20, ageDist.Age19Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 20, 25, ageDist.Age20To24Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 25, 30, ageDist.Age25To29Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 30, 35, ageDist.Age30To34Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 35, 40, ageDist.Age35To39Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 40, 45, ageDist.Age40To44Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 45, 50, ageDist.Age45To49Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 50, 55, ageDist.Age50To54Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 55, 60, ageDist.Age55To59Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 60, 65, ageDist.Age60To64Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 65, 70, ageDist.Age65To69Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 70, 75, ageDist.Age70To74Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 75, 80, ageDist.Age75To79Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 80, 85, ageDist.Age80To84Females);
	AllocateForAgeRange(pRandom, pPopulation, pCurrentDate, Female, 85, 101, ageDist.Age85AndOverFemales);


	
	std::vector<Person*> people;
	for (auto* person : _people)
		people.push_back(person);
	auto householdsBySize = _definition->PrivateHouseholdsBySize;
	auto householdsByType = _definition->PrivateHouseholdsByType;
	auto units = _definition->FamilyUnitsWithChildrenBySizeAndAgeOfChildren;

	
	for (DWORD i = 0; i < householdsByType.TotalHouseholdsNoOfHouseholds && people.size()>0; i++)
	{

		std::vector<DWORD> availTypes;
		for (DWORD type = 0; type < 14; type++)
			if (householdsByType.NoOfHouseholds[type] > 0)
				availTypes.push_back(type);
		if (availTypes.size() == 0) break;
		auto houseHoldType = availTypes[pRandom->Get<DWORD>(static_cast<DWORD>(availTypes.size()))];
		
		DWORD minHouseSize = 0, maxHouseSize = 0;
		
		CalculateMinMaxHouseSize(static_cast<PrivateHouseholdsType>(houseHoldType), &minHouseSize, &maxHouseSize);
		std::vector<DWORD> sizes;
		for (DWORD size = minHouseSize-1; size<maxHouseSize; size++)
			if (householdsBySize.NoOfHouseholds[size] > 0)
				sizes.push_back(size);

		auto householdSize = sizes[pRandom->Get<DWORD>(static_cast<DWORD>(sizes.size()))]+1;

		auto houseHold = new Household(this, householdSize, static_cast<PrivateHouseholdsType>(houseHoldType), &people);
		houseHold->Build(pRandom, pCurrentDate);
		auto size = houseHold->GetSize();
		if (size > 0) {
			AddHouseholdInternal(houseHold);
			
			householdsByType.NoOfHouseholds[houseHoldType]--;


		} 
		else {
			for (auto* member : *houseHold->GetMembers())
				people.push_back(member);
			delete houseHold;
			householdsByType.NoOfHouseholds[houseHoldType] = 0;
		}
	}



	
	for(auto house : _households)
		while(house->GetTargetSize()>house->GetSize() && !people.empty())
		{
			auto i = pRandom->Get<DWORD>(static_cast<DWORD>(people.size()));
			house->Add(people[i]);
			people[i]->SetHousehold(house);
			people[i]->SetArea(this);
			people.erase(people.begin() + i);
		}

	if (_definition->PersonsInCommunalEstablishments.NumberOfEstablishments > 0) {
		auto perEstablishment = _definition->PersonsInCommunalEstablishments.NumberOfPersons / _definition->PersonsInCommunalEstablishments.NumberOfEstablishments - 3;
		for (DWORD inst = 0; people.size() > 0 && inst < _definition->PersonsInCommunalEstablishments.NumberOfEstablishments; inst++)
		{
			auto house = new Household(this, 3, PrivateHouseholdsType::TwoOrMoreNonrelatedPersonsHouseholds, &people);

			for (DWORD j = 0; !people.empty() && j < static_cast<DWORD>(inst + 1 == _definition->PersonsInCommunalEstablishments.NumberOfEstablishments) ?
				                  _definition->PersonsInCommunalEstablishments.NumberOfPersons - (inst * perEstablishment) :
				                  perEstablishment; j++)
			{
				if (people.empty()) break;
				auto i = pRandom->Get<DWORD>(static_cast<DWORD>(people.size()));
				house->Add(people[i]);				
				people.erase(people.begin() + i);
			}

			if (house->GetSize() > 0)
				AddHouseholdInternal(house);
			else {
				for (auto* member : *house->GetMembers())
					people.push_back(member);
				delete house;
			}
		}
	}
	


	for(int i = 0; people.size()>0 &&  i < static_cast<int>(_definition->PrivateHouseholdsBySize.TotalHouseholdsNoOfHouseholds) - static_cast<int>(_households.size());i++)
	{
		auto household = new Household(this, 0, PrivateHouseholdsType::TwoOrMoreNonrelatedPersonsHouseholds, &people);
		auto size = pRandom->Get<DWORD>(1, 4);
		
		for(int j = 0; people.size()>0 && j < static_cast<int>(size); j++)
		{
			if (people.empty()) break;
			auto k = pRandom->Get<DWORD>(static_cast<DWORD>(people.size()));
			household->Add(people[k]);
			people.erase(people.begin() + k);
		}
		
		if (household->GetSize()>0)
			AddHouseholdInternal(household);
		else {
			for (auto* member : *household->GetMembers())
				people.push_back(member);
			delete household;
		}
	}
	_notCounted += static_cast<DWORD>(people.size());

	for (auto* floating : people) {
		pFloatingPeople->push_back(floating);
		_people.erase(std::remove(_people.begin(), _people.end(), floating), _people.end());
	}
	
	for (auto* household : _households)
		if (household->GetTargetSize() > household->GetSize())
			_missing += household->GetTargetSize() - household->GetSize();

	//DWORD numWithoutHouseHold = 0;
	//for (auto person : _people) {
	//	auto found = false;
	//	for (auto remainingPeople : people)
	//		if (person == remainingPeople)
	//		{
	//			found = true;
	//			break;
	//		}
	//	if (found) continue;
	//	if (person->GetHousehold() == nullptr)
	//	{
	//		numWithoutHouseHold++;

	//	}
	//}
	//std::cout << numWithoutHouseHold << "\r\n";

}

void SmallArea::DistributeFloating(RandomSource* pRandom, std::vector<Person*>* pFloatingPeople)
{
	if(_missing > 0) 
		for (auto house : _households)
			while (house->GetTargetSize() > house->GetSize() && !pFloatingPeople->empty())
			{
				auto i = pRandom->Get<DWORD>(static_cast<DWORD>(pFloatingPeople->size()));
				house->Add((*pFloatingPeople)[i]);
				(*pFloatingPeople)[i]->SetHousehold(house);
				if ((*pFloatingPeople)[i]->GetArea() != this)
				{
					(*pFloatingPeople)[i]->SetArea(this);
					_people.push_back((*pFloatingPeople)[i]);
				}
				pFloatingPeople->erase(pFloatingPeople->begin() + i);
			}
}

DWORD SmallArea::GetId()
{
	return _id;
}

int SmallArea::GetPopDelta()
{
	DWORD totalInHouses = _definition->PersonsInCommunalEstablishments.NumberOfPersons;
	for (auto household : _households)
		totalInHouses += household->GetTargetSize();

	return (int)totalInHouses - (int)_people.size();
}

SmallArea::~SmallArea()
{
}

void SmallArea::AddHousehold(Household* pHousehold)
{
	_households.push_back(pHousehold);
	for (auto* member : *pHousehold->GetMembers()) {
		member->SetHousehold(pHousehold);
		member->SetArea(this);
		_people.push_back(member);
		
	}
}

void SmallArea::AddHouseholdInternal(Household* pHousehold)
{
	_households.push_back(pHousehold);
	for (auto* member : *pHousehold->GetMembers()) {
		member->SetHousehold(pHousehold);
		member->SetArea(this);
	}
}

DWORD SmallArea::GetHouseholdCount() const
{
	return static_cast<DWORD>(_households.size());
}

DWORD SmallArea::GetPopulationCount() const
{
	return static_cast<DWORD>(_people.size());
}

NamedCode* SmallArea::GetRegionCode() const
{
	return _region;
}

NamedCode* SmallArea::GetSubRegionCode() const
{
	return _subRegion;
}

NamedCode* SmallArea::GetCountyCode() const
{
	return _county;
}

LedDescription* SmallArea::GetElectoralDistrictDesc() const
{
	return _electoralDistrict;
}

LocalElectoralArea* SmallArea::GetElectoralArea() const
{
	return _area;
}

void SmallArea::SetElectoralArea(LocalElectoralArea* pArea)
{
	_area = pArea;
}

std::vector<SmallAreaPolygon>* SmallArea::GetPolygons()
{
	return &_polygons;
}

double SmallArea::GetShapeArea() const
{
	return _shapeArea;
}

double SmallArea::GetPopulationDensity() const
{
	
	return static_cast<double>(_people.size()) / (_shapeArea/100);
}

void SmallArea::AddInfectedPerson(Person* pPerson)
{
	BasePopulationContainer::AddInfectedPerson(pPerson);
	_area->AddInfectedPerson(pPerson);
	_area->GetCounty()->AddInfectedPerson(pPerson);
	_area->GetCounty()->GetSubRegion()->AddInfectedPerson(pPerson);
	_area->GetCounty()->GetRegion()->AddInfectedPerson(pPerson);
}

void SmallArea::RemoveInfectedPerson(Person* pPerson)
{
	BasePopulationContainer::RemoveInfectedPerson(pPerson);
	_area->RemoveInfectedPerson(pPerson);
	_area->GetCounty()->RemoveInfectedPerson(pPerson);
	_area->GetCounty()->GetSubRegion()->RemoveInfectedPerson(pPerson);
	_area->GetCounty()->GetRegion()->RemoveInfectedPerson(pPerson);
}
