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

#include "CommandsGeneral.h"


#include <iomanip>
#include <iostream>



#include "LocalElectoralArea.h"
#include "County.h"
#include "Region.h"
#include "SubRegion.h"
#include "PopulationSim.h"
#include "SmallArea.h"

HelpCommand::HelpCommand(vector<Command*>* pCommands): _commands(pCommands) {
	
}

void HelpCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	std::cout << "The following commands are available" << "\r\n";
	std::cout << "\r\n";
	std::cout << std::left << std::setw(20) << "Command";
	std::cout << std::left << std::setw(100) << "Description" << "\r\n";
	for(auto* command : (*_commands))
	{
		std::cout << std::left << std::setw(20) << command->GetInfo().GetName();
		std::cout << std::left << std::setw(100) << command->GetInfo().GetDescription() << "\r\n";
	}
}

CommandInfo HelpCommand::GetInfo()
{
	return CommandInfo("help", "", "Shows this screen");
}







RegionsCommand::RegionsCommand(PopulationSim* pSim): _sim(pSim) {
}

void RegionsCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	std::cout << std::right << std::setw(7) << "Id" << "  ";
	std::cout << std::left << std::setw(30) << "Region Name";
	std::cout << std::right << std::setw(12) << "Households";
	std::cout << std::right << std::setw(12) << "People" ;
	std::cout << std::right << std::setw(12) << "Sub Reg" << "\r\n";
	DWORD id = 0;
	for (auto* area : (*_sim->GetRegions()))
	{
		std::wcout << std::right << std::setw(7) << id << "  ";
		std::wcout << std::left << std::setw(30) << area->GetName();
		std::wcout << std::right << std::setw(12) << area->GetHouseholds()->size();
		std::wcout << std::right << std::setw(12) << area->GetPeople()->size() ;
		std::wcout << std::right << std::setw(12) << area->GetSubRegions()->size() << "\r\n";
		id++;
	}
}

CommandInfo RegionsCommand::GetInfo()
{
	return CommandInfo("regions", "", "Lists regions");
}

SubRegionsCommand::SubRegionsCommand(PopulationSim* pSim): _sim(pSim) {
}

void SubRegionsCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	std::cout << std::right << std::setw(7)  << "Id" << "  ";
	std::cout << std::left  << std::setw(30) << "Region Name";
	std::cout << std::left  << std::setw(30) << "Sub-region Name";
	std::cout << std::right << std::setw(12) << "Households";
	std::cout << std::right << std::setw(12) << "People";
	std::cout << std::right << std::setw(12) << "Counties" << "\r\n";
	DWORD id = 0;
	for (auto* area : (*_sim->GetSubRegions()))
	{
		std::wcout << std::right << std::setw(7)  << id << "  ";
		std::wcout << std::left  << std::setw(30) << area->GetRegion()->GetName();
		std::wcout << std::left  << std::setw(30) << area->GetName();
		std::wcout << std::right << std::setw(12) << area->GetHouseholds()->size();
		std::wcout << std::right << std::setw(12) << area->GetPeople()->size() ;
		std::wcout << std::right << std::setw(12) << area->GetCounties()->size() << "\r\n";
		id++;
	}
}

CommandInfo SubRegionsCommand::GetInfo()
{
	return CommandInfo("subregions", "", "Lists sub-regions");
}
