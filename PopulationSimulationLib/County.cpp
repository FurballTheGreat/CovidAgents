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

#include "County.h"

#include "LocalElectoralArea.h"
#include "Person.h"
#include "SmallArea.h"

County::County(std::wstring pName, std::wstring pCode) : BasePopulationContainer(pName), _code(std::move(pCode))
{
}

Region* County::GetRegion() const
{
	return _region;
}

SubRegion* County::GetSubRegion() const
{
	return _subRegion;
}

void County::SetRegion(Region* pRegion)
{
	_region = pRegion;
}

void County::SetSubRegion(SubRegion* pSubRegion)
{
	_subRegion = pSubRegion;
}

std::vector<LocalElectoralArea*>* County::GetAreas()
{
	return &_area;
}

std::vector<SmallArea*> County::GetSmallAreas()
{
	std::vector<SmallArea*> smallArea;
	
	for(auto* lea : _area)
		for(auto* area : *(lea->GetAreas()))
		{
			smallArea.push_back(area);
		}
	return smallArea;
}

DWORD County::GetImmune() 
{
	DWORD result = 0;
	for (auto* person : (*GetPeople()))
		if (person->IsImmune(nullptr))
			result++;
	return result;
}

std::wstring County::GetCode() const
{
	return _code;
}
