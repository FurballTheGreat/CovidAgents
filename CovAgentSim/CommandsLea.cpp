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

#include "CommandsLea.h"
#include <iomanip>
#include <iostream>
#include "Enums.h"
#include "County.h"
#include "LocalElectoralArea.h"
#include "PopulationSim.h"
#include "Region.h"
#include "SubRegion.h"
#include "SmallArea.h"

LocalElectoralAreasCommand::LocalElectoralAreasCommand(PopulationSim* pSim) : _sim(pSim) {
}

void LocalElectoralAreasCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	auto args = pCmdLine->GetArgs();
	County* county = nullptr;
	LocalElectoralArea* area = nullptr;
	if (args.size() > 1)
	{
		if (args[1] == "bycounty")
		{
			auto id = atoi(args[2].c_str());
			if (id < static_cast<int>(_sim->GetCounties()->size()))
			{
				county = (*_sim->GetCounties())[id];
			}
		}
		else
		{
			auto id = std::atoi(args[1].c_str());
			area = *std::find_if(
				_sim->GetElectoralAreas()->begin(), _sim->GetElectoralAreas()->end(),
				[&](const LocalElectoralArea* x) { return x->GetCode() == id; });
			if (area == nullptr)
			{
				cout << "Not found" << "\r\n";
				return;
			}

		}
	}
	if (area == nullptr) {
		std::cout << std::right << std::setw(7) << "OSI Id" << "  ";
		std::cout << std::left << std::setw(40) << "LEA Name";
		std::cout << std::left << std::setw(27) << "County Name";
		std::cout << std::right << std::setw(12) << "Households";
		std::cout << std::right << std::setw(12) << "People";
		std::cout << std::right << std::setw(12) << "Sml Areas" << "\r\n";
		DWORD index = 0;
		for (auto* area : (*_sim->GetElectoralAreas()))
		{

			if (county != nullptr && county != area->GetCounty()) {
				index++;
				continue;
			}

			std::cout << std::right << std::setw(7) << std::to_string(area->GetCode()) << "  ";


			std::wcout << std::left << std::setw(40) << area->GetName();
			std::wcout << std::left << std::setw(27) << area->GetCounty()->GetName();
			std::wcout << std::right << std::setw(12) << area->GetHouseholds()->size();
			std::wcout << std::right << std::setw(12) << area->GetPeople()->size();
			std::wcout << std::right << std::setw(12) << area->GetAreas()->size() << "\r\n";
			index++;
		}
		return;
	}

	std::wcout << "Code: " << std::to_wstring(area->GetCode()) << "\r\n";
	std::wcout << "Name: " << area->GetName() << "\r\n";
	std::wcout << "County: " << area->GetCounty()->GetName() << "\r\n";
	std::wcout << "Sub-Region: " << area->GetSubRegion()->GetName() << "\r\n";
	std::wcout << "Region: " << area->GetRegion()->GetName() << "\r\n";
	std::wcout << "\r\n";
	std::cout << std::right << std::setw(7) << "Id" << "  ";
	std::cout << std::right << std::setw(12) << "Households";
	std::cout << std::right << std::setw(12) << "People" << "\r\n";
	DWORD index = 0;




	std::cout << "\r\n" << std::right << std::setw(12) << "Small Areas" << "\r\n";
	index = 0;

	for (auto* smallArea : (*area->GetAreas()))
	{


		std::wcout << std::right << std::setw(7) << smallArea->GetId() << "  ";
		std::wcout << std::right << std::setw(12) << smallArea->GetHouseholdCount();
		std::wcout << std::right << std::setw(12) << smallArea->GetPopulationCount() << "\r\n";
		index++;
	}

	std::cout << "\r\n" << std::right << std::setw(12) << "Outward Movements" << "\r\n";
	std::cout << std::right << std::setw(7) << "Index" << "  ";
	std::cout << std::right << std::setw(7) << "Code" << "  ";
	std::cout << std::left << std::setw(30) << "Going To";
	std::cout << std::right << std::setw(12) << "People";
	std::cout << std::right << std::setw(12) << "Distance" << "\r\n";
	DWORD count = 0;
	for (auto movement : (*area->GetMovements()))
	{
		std::wcout << std::right << std::setw(7) << index++ << "  ";
		count += movement.GetCount();
		switch (movement.GetType())
		{
		case MovementToEd:
			std::wcout << std::right << std::setw(7) << movement.GetOther()->GetCode() << "  ";
			std::wcout << std::left << std::setw(30) << movement.GetOther()->GetName();
			std::wcout << std::right << std::setw(12) << movement.GetCount();
			std::wcout << std::right << std::setw(12) << movement.GetDistance() << "\r\n";
			break;
		case MovementNotFixed:
			std::wcout << std::right << std::setw(7) << "-" << "  ";
			std::wcout << std::left << std::setw(30) << "Not Fixed";
			std::wcout << std::right << std::setw(12) << movement.GetCount();
			std::wcout << std::right << std::setw(12) << movement.GetDistance() << "\r\n";
			break;
		case MovementNone:
			std::wcout << std::right << std::setw(7) << "-" << "  ";
			std::wcout << std::left << std::setw(30) << "At Home";
			std::wcout << std::right << std::setw(12) << movement.GetCount();
			std::wcout << std::right << std::setw(12) << movement.GetDistance() << "\r\n";
			break;
		default:;
		}

	}
	std::cout << "Total" << std::left << std::setw(30) << count << "\r\n";

	std::cout << "\r\n" << std::right << std::setw(12) << "Inward Movements" << "\r\n";
	std::cout << std::right << std::setw(7) << "Code" << "  ";
	std::cout << std::left << std::setw(30) << "From";
	std::cout << std::right << std::setw(12) << "People";
	std::cout << std::right << std::setw(12) << "Distance" << "\r\n";
	count = 0;
	for (auto movement : (*area->GetInwardMovements()))
	{
		std::wcout << std::right << std::setw(7) << movement.GetOther()->GetCode() << "  ";
		count += movement.GetCount();
		switch (movement.GetType())
		{
		case MovementToEd:
			std::wcout << std::left << std::setw(30) << movement.GetOther()->GetName();
			std::wcout << std::right << std::setw(12) << movement.GetCount();
			std::wcout << std::right << std::setw(12) << movement.GetDistance() << "\r\n";
			break;

		default:;
		}

	}

	std::cout << "Total" << std::left << std::setw(30) << count << "\r\n";
	return;

}

CommandInfo LocalElectoralAreasCommand::GetInfo()
{
	return CommandInfo("lea", "", "List LEAs");
}