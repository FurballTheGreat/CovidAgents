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
#include "Common.h"
#include "Enums.h"

class NamedCode
{
private:
	std::wstring _code;
	std::wstring _name;

public:
	NamedCode(std::ifstream *pStream);

	std::wstring GetCode() const;
	std::wstring GetName() const;
	
	static std::wstring ReadString(std::ifstream* pStream);
};


class LedCommuteMovementDescription
{
private:
	MovementType _type = MovementToEd;
	DWORD _osiId = 0;
	DWORD _count = 0;
	double _distance = 0;
public:
	LedCommuteMovementDescription(std::ifstream* pStream);
	DWORD GetOsiId() const;
	DWORD GetCount() const;
	double GetDistance() const;
	MovementType GetType() const;
};

class LedDescription
{
private:
	DWORD _code;
	std::wstring _name;
	std::vector<LedCommuteMovementDescription> _movements;
public:
	LedDescription(std::ifstream* pStream);

	DWORD GetCode() const;
	std::wstring GetName() const;
	std::vector<LedCommuteMovementDescription>* GetMovements();
};


