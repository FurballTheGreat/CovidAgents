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

#include "Household.h"

#include "Person.h"


Household::Household(SmallArea* pArea, DWORD _targetSize, PrivateHouseholdsType pType, std::vector<Person*>* pSource): _area(pArea), _targetSize(_targetSize), _type(pType), _source(pSource)
{
}

Person* Household::AddFromSource(RandomSource *pRandom, DWORD pMinAge, DWORD pMaxAge, BiologicalSex*pSex, boost::gregorian::date pCurrentDate)
{
	for(DWORD i = 0; i < _source->size(); i++)
	{
		auto index = pRandom->Get<DWORD>(static_cast<DWORD>(_source->size()));
		auto* result = (*_source)[index];

		if(result->GetHousehold()==nullptr && (pSex==nullptr || result->GetSex()==*pSex))
		{
			auto age = result->GetAge();
			if(age>=pMinAge && age < pMaxAge)
			{
				_source->erase(_source->begin() + index);
				result->SetHousehold(this);
				result->SetArea(_area);
				return result;
			}
		}
		
	}

	return nullptr;
}

void Household::AddCouple(RandomSource* pRandom, DWORD pMinAge, DWORD pMaxAge, boost::gregorian::date pCurrentDate, Person **pPerson1, Person** pPerson2)
{
	auto male = Male;
	auto female = Female;
	*pPerson1 = AddFromSource(pRandom, 18, 101, &male, pCurrentDate);
	if (*pPerson1) _people.push_back(*pPerson1);
	DWORD age = *pPerson1 != nullptr ? (*pPerson1)->GetAge() - 10 : 18;
	if (age < 18) age = 18;
	auto maxAge = age + 20;
	if (maxAge > 101 || *pPerson1 == nullptr) maxAge = 101;
	*pPerson2 = AddFromSource(pRandom, age, maxAge, &female, pCurrentDate);
	if (*pPerson2) _people.push_back(*pPerson2);
}

void Household::Add(Person* pPerson)
{
	_people.push_back(pPerson);
}

void Household::Remove(Person* pPerson)
{
	for (int i = (int)_people.size() - 1; i > 0; i--)
		if (_people[i] == pPerson)
			_people.erase(_people.begin() + i);
}

void Household::Build(RandomSource* pRandom, boost::gregorian::date pCurrentDate)
{
	auto male = Male;
	auto female = Female;
	Person* spouse1Person;
	Person* spouse2Person;
	Person* singlePerson = nullptr;
	Person* child;
	switch(_type)
	{
	case PrivateHouseholdsType::OnePersonHouseholds:
		singlePerson = AddFromSource(pRandom,18, 101, nullptr, pCurrentDate);
		if(singlePerson) _people.push_back(singlePerson);
		break;
	case PrivateHouseholdsType::MarriedCoupleHouseholds:		
		AddCouple(pRandom, 18, 101, pCurrentDate, &spouse1Person, &spouse2Person);
		break;
	case PrivateHouseholdsType::CohabitingCoupleHouseholds: 
		AddCouple(pRandom, 18, 101, pCurrentDate, &spouse1Person, &spouse2Person);
		break;
	case PrivateHouseholdsType::MarriedCoupleWithChildrenHouseholds: 
		AddCouple(pRandom, 18, 70, pCurrentDate, &spouse1Person, &spouse2Person);
		for(DWORD i = 2; i < _targetSize;i++)
		{
			child = AddFromSource(pRandom, 0, 20, nullptr, pCurrentDate);
			if (child) _people.push_back(child);
		}
		break;
	case PrivateHouseholdsType::CohabitingCoupleWithChildrenHouseholds: 
		AddCouple(pRandom, 18, 70, pCurrentDate, &spouse1Person, &spouse2Person);
		for (DWORD i = 2; i < _targetSize; i++)
		{
			child = AddFromSource(pRandom, 0, 20, nullptr, pCurrentDate);
			if (child) _people.push_back(child);
		}
		break;
	case PrivateHouseholdsType::OneParentFamilyFatherWithChildrenHouseholds: 
		singlePerson = AddFromSource(pRandom, 18, 70, &male, pCurrentDate);
		if (singlePerson) _people.push_back(singlePerson);
		for (DWORD i = 2; i < _targetSize; i++)
		{
			child = AddFromSource(pRandom, 0, 20, nullptr, pCurrentDate);
			if (child) _people.push_back(child);
		}
		break;
	case PrivateHouseholdsType::OneParentFamilyMotherAndChildrenHouseholds: 
		singlePerson = AddFromSource(pRandom, 18, 70, &female, pCurrentDate);
		if (singlePerson) _people.push_back(singlePerson);
		for (DWORD i = 2; i < _targetSize; i++)
		{
			child = AddFromSource(pRandom, 0, 20, nullptr, pCurrentDate);
			if (child) _people.push_back(child);
		}
		break;
	case PrivateHouseholdsType::CoupleAndOthersHouseholds: 
		AddCouple(pRandom, 18, 101, pCurrentDate, &spouse1Person, &spouse2Person);
		for (DWORD i = 2; i < _targetSize; i++)
		{
			child = AddFromSource(pRandom, 0, 101, nullptr, pCurrentDate);
			if (child) _people.push_back(child);
		}
		break;
	case PrivateHouseholdsType::CoupleWithChildrenAndOthersHouseholds: 
		AddCouple(pRandom, 18, 101, pCurrentDate, &spouse1Person, &spouse2Person);
		for (DWORD i = 2; i < _targetSize; i++)
		{
			child = AddFromSource(pRandom, 0, 101, nullptr, pCurrentDate);
			if (child) _people.push_back(child);
		}
		break;
	case PrivateHouseholdsType::OneParentFamilyFatherWithChildrenAndOthersHouseholds:
		singlePerson = AddFromSource(pRandom, 18, 70, &male, pCurrentDate);
		if (singlePerson) _people.push_back(singlePerson);
		for (DWORD i = 21; i < _targetSize; i++)
		{
			child = AddFromSource(pRandom, 0, 101, nullptr, pCurrentDate);
			if (child) _people.push_back(child);
		}
		break;
	case PrivateHouseholdsType::OneParentFamilyMotherWithChildrenAndOthersHouseholds:
		singlePerson = AddFromSource(pRandom, 18, 70, &female, pCurrentDate);
		if (singlePerson) _people.push_back(singlePerson);
		for (DWORD i = 1; i < _targetSize; i++)
		{
			child = AddFromSource(pRandom, 0, 101, nullptr, pCurrentDate);
			if (child) _people.push_back(child);
		}
		break;
		break;
	case PrivateHouseholdsType::TwoOrMoreFamilyUnitsHouseholds: 
		for (DWORD i = 0; i < _targetSize; i++)
		{
			child = AddFromSource(pRandom, 0, 101, nullptr, pCurrentDate);
			if (child) _people.push_back(child);
		}
		break;
	case PrivateHouseholdsType::NonfamilyHouseholdsAndRelationsHouseholds: 
		for (DWORD i = 0; i < _targetSize; i++)
		{
			child = AddFromSource(pRandom, 0, 101, nullptr, pCurrentDate);
			if (child) _people.push_back(child);
		}
		break;		
	case PrivateHouseholdsType::TwoOrMoreNonrelatedPersonsHouseholds: 
		for (DWORD i = 0; i < _targetSize; i++)
		{
			child = AddFromSource(pRandom, 0, 101, nullptr, pCurrentDate);
			if (child) _people.push_back(child);
		}
		break;
	default: ;
	}


}

DWORD Household::GetTargetSize() const
{
	return _targetSize;
}

DWORD Household::GetSize() const
{
	return static_cast<DWORD>(_people.size());
}

std::vector<Person*>* Household::GetMembers()
{
	return &_people;
}
