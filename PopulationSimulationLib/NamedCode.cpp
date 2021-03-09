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

#include "NamedCode.h"
#include "Common.h"
#include <fstream>
#include <codecvt>
#include <locale>

NamedCode::NamedCode(std::ifstream *pStream)
{
	_code = ReadString(pStream);
	_name = ReadString(pStream);
}

std::wstring NamedCode::GetCode() const 
{
	return _code;
}

std::wstring NamedCode::GetName() const
{
	return _name;
}

std::wstring NamedCode::ReadString(std::ifstream* pStream)
{
	unsigned char len;
	char buf[1024];
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	pStream->read(reinterpret_cast<char*>(&len), 1);
	pStream->read(buf, len);
	buf[len] = 0;
	return converter.from_bytes(buf);
}

LedCommuteMovementDescription::LedCommuteMovementDescription(std::ifstream* pStream)
{
	DWORD type;
	pStream->read(reinterpret_cast<char*>(&type), sizeof(type));
	_type = static_cast<MovementType>(type);
	pStream->read(reinterpret_cast<char*>(&_osiId), sizeof(_osiId));
	pStream->read(reinterpret_cast<char*>(&_count), sizeof(_count));
	pStream->read(reinterpret_cast<char*>(&_distance), sizeof(_distance));
}

DWORD LedCommuteMovementDescription::GetOsiId() const
{
	return _osiId;
}

DWORD LedCommuteMovementDescription::GetCount() const
{
	return _count;
}

double LedCommuteMovementDescription::GetDistance() const
{
	return _distance;
}

MovementType LedCommuteMovementDescription::GetType() const
{
	return _type;
}

LedDescription::LedDescription(std::ifstream* pStream)
{
	_code = 0;
	pStream->read(reinterpret_cast<char*>(&_code), sizeof(_code));
	_name = NamedCode::ReadString(pStream);
	DWORD count = 0;
	pStream->read(reinterpret_cast<char*>(&count), sizeof(count));
	for(DWORD i = 0; i< count; i++)
	{
		LedCommuteMovementDescription desc(pStream);
		_movements.push_back(desc);
	}
}

DWORD LedDescription::GetCode() const
{
	return _code;
}

std::wstring LedDescription::GetName() const
{
	return _name;
}

std::vector<LedCommuteMovementDescription>* LedDescription::GetMovements()
{
	return &_movements;
}
