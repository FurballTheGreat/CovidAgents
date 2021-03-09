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
#include "PopulationDistributionDefinition.h"

#include <fstream>

#include "Exceptions.h"

#define MAGIC 0xBAADBEEF

PopulationDistributionDefinition::PopulationDistributionDefinition(const std::string pFileName)
{
	std::ifstream input(pFileName, std::ios::binary);
	if (!input)
		throw InvalidPopulationDistributionFileSizeException();
	DWORD magic;
	DWORD count;
	input.read(reinterpret_cast<char*>(&magic), sizeof(DWORD));
	if(!input)
		throw InvalidPopulationDistributionFileSizeException();
	input.read(reinterpret_cast<char*>(&count), sizeof(DWORD));
	if (!input)
		throw InvalidPopulationDistributionFileSizeException();
	if (magic != MAGIC)
		throw InvalidPopulationDistributionFileMagicException();

	DWORD i;
	for(i=0; i<count && !input.eof();i++)
	{
		PopulationAgeSexDefinition entry;
		input.read(reinterpret_cast<char*>(&entry), sizeof(PopulationAgeSexDefinition));
		_bands.push_back(entry);
	}
	if (i < count)
		throw InvalidPopulationDistributionFileSizeException();
	
}

PopulationDistributionDefinition::~PopulationDistributionDefinition()
{
}

DWORD PopulationDistributionDefinition::Count() const
{
	return static_cast<DWORD>(_bands.size());
}

DWORD PopulationDistributionDefinition::TotalPopulation() const
{
	DWORD result = 0;
	for (auto band : _bands)
		result += band.Count;
	return result;
}

PopulationAgeSexDefinition* PopulationDistributionDefinition::Get(DWORD pAge, BiologicalSex pSex)
{
	for (DWORD i = 0; i<_bands.size();i++)
		if (_bands[i].Age == pAge && _bands[i].Sex == pSex)
			return &_bands[i];
	return nullptr;
}
