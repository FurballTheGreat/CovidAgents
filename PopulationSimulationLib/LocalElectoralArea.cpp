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

#include "LocalElectoralArea.h"
#include "NamedCode.h"
#include "Commuter.h"
#include "Person.h"

LocalElectoralAreaMovement::LocalElectoralAreaMovement(MovementType pType, LocalElectoralArea* pOther, DWORD pCount, double pDistance): _other(pOther), _count(pCount), _distance(pDistance), _type(pType)
{
}

LocalElectoralArea* LocalElectoralAreaMovement::GetOther() const
{
	return _other;
}

DWORD LocalElectoralAreaMovement::GetCount() const
{
	return _count;
}

double LocalElectoralAreaMovement::GetDistance() const
{
	return _distance;
}

MovementType LocalElectoralAreaMovement::GetType() const
{
	return _type;
}

LocalElectoralArea::LocalElectoralArea(LedDescription*  pName) : BasePopulationContainer(pName->GetName())
{
	_code = pName->GetCode();
	
}

County* LocalElectoralArea::GetCounty() const
{
	return _county;
}

Region* LocalElectoralArea::GetRegion() const
{
	return _region;
}

SubRegion* LocalElectoralArea::GetSubRegion() const
{
	return _subRegion;
}

DWORD LocalElectoralArea::GetCode() const
{
	return _code;
}

void LocalElectoralArea::SetCounty(County* pCounty)
{
	_county = pCounty;
}

void LocalElectoralArea::SetRegion(Region* pRegion)
{
	_region = pRegion;
}

void LocalElectoralArea::SetSubRegion(SubRegion* pSubRegion)
{
	_subRegion = pSubRegion;
}

std::vector<SmallArea*>* LocalElectoralArea::GetAreas()
{
	return &_area;
}

std::vector<LocalElectoralAreaMovement>* LocalElectoralArea::GetMovements()
{
	return &_movements;
}

std::vector<LocalElectoralAreaMovement>* LocalElectoralArea::GetInwardMovements()
{
	return &_inwardMovements;
}

std::vector<Commuter*>& LocalElectoralArea::GetOutwardCommuters()
{
	return _outwardCommuters;
}

std::vector<Commuter*>& LocalElectoralArea::GetInwardCommuters()
{
	return _inwardCommuters;
}

double LocalElectoralArea::GetTotalOutwardMovements()
{
	double result = 0;
	for (auto movement : _movements)
		if (movement.GetType() == MovementToEd && movement.GetOther() != this)
			result+=movement.GetCount();
	return result;
}

double LocalElectoralArea::GetTotalInwardMovements(double pMinDistance)
{
	double result = 0;
	for (auto movement : _inwardMovements)
		if (movement.GetType() == MovementToEd && movement.GetOther() != this && movement.GetDistance()> pMinDistance)
			result += movement.GetCount();
	return  result;
}

double LocalElectoralArea::GetInfectedPer100k()
{
	return (double)GetInfectedPeopleSize() * (100000/(double)GetPeople()->size());
}
