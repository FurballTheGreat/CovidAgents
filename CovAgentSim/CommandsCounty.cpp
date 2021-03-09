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

#include "CommandsCounty.h"

#include <iomanip>
#include <iostream>

#include "LocalElectoralArea.h"
#include "County.h"
#include "Region.h"
#include "SubRegion.h"
#include "PopulationSim.h"

CountiesCommand::CountiesCommand(PopulationSim* pSim) : _sim(pSim) {
}

void CountiesCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	std::cout << std::right << std::setw(7)  << "Id" << "  ";
	std::cout << std::left  << std::setw(30) << "County Name";
	std::cout << std::left  << std::setw(20) << "Sub Region Name";
	
	std::cout << std::right << std::setw(12) << "Households";
	std::cout << std::right << std::setw(12) << "People" ;
	std::cout << std::right << std::setw(12) << "Immune";
	std::cout << std::right << std::setw(12) << "Districts" << "\r\n";
	DWORD id = 0;
	for (auto* area : (*_sim->GetCounties()))
	{
		std::wcout << std::right << std::setw(7)  << id << "  ";
		std::wcout << std::left  << std::setw(30) << area->GetName();
		std::wcout << std::left  << std::setw(20) << area->GetSubRegion()->GetName();		
		std::wcout << std::right << std::setw(12) << area->GetHouseholds()->size();
		std::wcout << std::right << std::setw(12) << area->GetPeople()->size();
		std::wcout << std::right << std::setw(12) << area->GetImmune();
		std::wcout << std::right << std::setw(12) << area->GetAreas()->size() << "\r\n";
		id++;
	}
}

CommandInfo CountiesCommand::GetInfo()
{
	return CommandInfo("counties", "", "Lists counties");
}

CountyStatusCommand::CountyStatusCommand(PopulationSim* pSim) : _sim(pSim) {
}

void CountyStatusCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	auto args = pCmdLine->GetArgs();
	if (args.size() < 2)
		return;

	auto id = atoi(args[1].c_str());
	if (id >= static_cast<int>(_sim->GetCounties()->size()))
		return;
	
	auto area = (*_sim->GetCounties())[id];

	wcout << "Name: " << area->GetName() << "\r\n";
	wcout << "Region: " << area->GetRegion()->GetName() << "\r\n";
	wcout << "Sub-Region: " << area->GetSubRegion()->GetName() << "\r\n";
	wcout << "Population: " << area->GetPeople()->size() << "\r\n";
	wcout << "Households: " << area->GetHouseholds()->size() << "\r\n";
	wcout << "Electoral Districts: " << area->GetAreas()->size() << "\r\n";
	
}

CommandInfo CountyStatusCommand::GetInfo()
{
	return CommandInfo("county", "", "Displays County Status");
}