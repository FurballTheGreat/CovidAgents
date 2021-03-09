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
#include "Common.h"

#include "BasePopulationContainer.h"
#include "Enums.h"

class Commuter;
class LedDescription;
class SmallArea;
class Person;
class County;
class Region;
class SubRegion;


class LocalElectoralArea;


class LocalElectoralAreaMovement
{
private:
	LocalElectoralArea* _other;
	DWORD _count;
	double _distance;
	MovementType _type;
public:
	LocalElectoralAreaMovement(MovementType pType, LocalElectoralArea* pOther, DWORD pCount, double pDistance);

	LocalElectoralArea* GetOther() const;
	DWORD GetCount() const ;
	double GetDistance() const;
	MovementType GetType() const;
	
};


class LocalElectoralArea : public BasePopulationContainer
{
private:
	std::vector<SmallArea*> _area;
	std::vector<LocalElectoralAreaMovement> _movements;
	std::vector<LocalElectoralAreaMovement> _inwardMovements;
	std::vector<Commuter*> _outwardCommuters;
	std::vector<Commuter*> _inwardCommuters;
	County* _county = nullptr;
	Region* _region = nullptr;
	SubRegion* _subRegion = nullptr;
	
	DWORD _code = 0;
public:
	LocalElectoralArea(LedDescription* pName);
	
	County* GetCounty() const;
	Region* GetRegion() const;
	SubRegion* GetSubRegion() const;
	DWORD GetCode() const;
	void SetCounty(County* pCounty);
	void SetRegion(Region* pRegion);
	void SetSubRegion(SubRegion* pSubRegion);
	std::vector<SmallArea*>* GetAreas();
	std::vector<LocalElectoralAreaMovement>* GetMovements();
	std::vector<LocalElectoralAreaMovement>* GetInwardMovements();
	std::vector<Commuter*>& GetOutwardCommuters();
	std::vector<Commuter*>& GetInwardCommuters();
	double GetTotalOutwardMovements();
	double GetTotalInwardMovements(double pMinDistance);
	double GetInfectedPer100k();
};

