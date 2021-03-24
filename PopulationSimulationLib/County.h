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
#include <string>
#include <vector>
#include "BasePopulationContainer.h"

class SmallArea;
class Person;
class LocalElectoralArea;
class Region;
class SubRegion;
class County : public BasePopulationContainer
{
private:
	std::vector<LocalElectoralArea*> _area;
	Region* _region;
	SubRegion* _subRegion;
	std::wstring _code;
public:
	County(std::wstring pName, std::wstring pCode);
	Region* GetRegion() const;
	SubRegion* GetSubRegion() const;
	void SetRegion(Region* pRegion);
	void SetSubRegion(SubRegion* pSubRegion);
	std::vector<LocalElectoralArea*>* GetAreas();
	std::vector<SmallArea*> GetSmallAreas();
	DWORD GetImmune() ;
	std::wstring GetCode() const;
};

