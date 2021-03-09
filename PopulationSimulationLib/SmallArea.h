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
#include <vector>

#include "Enums.h"
#include "CensusSAPS.h"
#include "SmallAreaPolygon.h"
#include <boost/date_time/gregorian/greg_date.hpp>

#include "BasePopulationContainer.h"

class LedDescription;
class Household;
class RandomSource;
class Population;
class Person;
class NamedCode;
class LocalElectoralArea;

class SmallArea : public BasePopulationContainer
{
private:
	DWORD _id;
	NamedCode* _region;
	NamedCode* _subRegion;
	NamedCode* _county;
	double _shapeArea;
	DWORD _notCounted = 0;
	DWORD _missing = 0;
	LedDescription* _electoralDistrict;
	SmallPopulationAreaDefinition* _definition;
	std::vector<SmallAreaPolygon> _polygons;
	LocalElectoralArea* _area;


	void AllocateForAgeRange(RandomSource* pRandom, Population* pPopulation, boost::gregorian::date pCurrentDate, BiologicalSex pSex, DWORD pMinAge, DWORD pMaxAge, DWORD pNum);
	static void CalculateMinMaxHouseSize(PrivateHouseholdsType pType, DWORD* pMin, DWORD* pMax);
	void AddHouseholdInternal(Household* pHousehold);
public:
	
	SmallArea(DWORD pId, NamedCode* pRegion, NamedCode* pSubRegion, NamedCode* pCounty, LedDescription* pElectoralDistrict, double pShapeArea, std::ifstream *pStream);
	void BuildPeople(RandomSource* pRandom, Population* pPopulation, boost::gregorian::date pCurrentDate, std::vector<Person*> *pFloatingPeople);
	void DistributeFloating(RandomSource* pRandom, std::vector<Person*>* pFloatingPeople);
	DWORD GetId();
	int GetPopDelta();
	~SmallArea();
	void AddHousehold(Household* pHousehold);
	DWORD GetHouseholdCount() const;
	DWORD GetPopulationCount() const;
	NamedCode* GetRegionCode() const;
	NamedCode* GetSubRegionCode() const;
	NamedCode* GetCountyCode() const;
	LedDescription* GetElectoralDistrictDesc() const;
	LocalElectoralArea* GetElectoralArea() const;
	void SetElectoralArea(LocalElectoralArea* pArea);
	std::vector<SmallAreaPolygon>* GetPolygons();
	double GetShapeArea() const;
	double GetPopulationDensity() const;
	void AddInfectedPerson(Person* pPerson) override;
	void RemoveInfectedPerson(Person* pPerson) override;

};

