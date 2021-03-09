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

#include "CommandsSimulation.h"

#include <iostream>
#include <blend2d.h>
#include "boost/date_time/gregorian/gregorian.hpp"


#include "County.h"
#include "LocalElectoralArea.h"
#include "MapPlotter.h"
#include "PopulationSim.h"
#include "RandomSource.h"
#include "SimpleInfectionSimulator.h"
#include "SmallArea.h"
#include "SmallAreas.h"
#include "StandardVariant.h"

SimpleSimulationCommand::SimpleSimulationCommand(PopulationSim* pSim, SimpleInfectionSimulator* pSimulation) : _sim(pSim), _simulation(pSimulation) {
}

void SimpleSimulationCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	auto args = pCmdLine->GetArgs();

	int days;
	auto random = RandomSource();
	

	if(args.size()==2)
	{
		days = atoi(args[1].c_str());
		if (days < 1) {
			cout << "You must run at least one day\r\b";
			return;
		}
	} else
	{
		pConsole->WriteLine("SYNTAX: simplesim days_to_run number_to_seed [countyNumber]");
		return;
	}
	

	auto plotter2 = MapPlotter(_sim->GetSmallAreas()->GetAreas());

	for (DWORD day = 0; day < static_cast<DWORD>(days); day++)
	{

		std::string fileName = std::to_string(day) + ".png";

		auto begin = clock();
		plotter2.PlotMap(
			fileName,
			_sim->GetDate(),
			[&](SmallArea& pArea, BLContext& pContext)
			{
				auto per100k = pArea.GetElectoralArea()->GetInfectedPer100k();
				auto intensity = 0;
				if (per100k > 1000)
					intensity = 255;
				if (per100k > 750)
					intensity = 225;
				if (per100k > 500)
					intensity = 200;
				if (per100k > 250)
					intensity = 175;
				if (per100k > 150)
					intensity = 150;
				if (per100k > 25)
					intensity = 110;
				if (per100k >= 1)
					intensity = 100;
				else
					intensity = 0;


				BLRgba32 color(20, (255 - intensity) / 4, intensity);

				pContext.setFillStyle(color);
				pContext.setStrokeStyle(color);
				pContext.setStrokeWidth(10);
			});
		auto end = clock();
		auto time_spent = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Saved " << fileName << " in " << time_spent << "s\r\n";

		begin = clock();
		_simulation->ProceedDay(random, 0, 5, 0, 4);
		end = clock();
		time_spent = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
		std::cout << _sim->GetDate() << " processed in " << time_spent << "s, a total of " << _simulation->GetTotalCurrentlyInfected() << " people are currently infected \r\n";
	}
}

CommandInfo SimpleSimulationCommand::GetInfo()
{
	return CommandInfo("simplesim", "", "Displays County Status");
}


SeedCasesCommand::SeedCasesCommand(PopulationSim* pSim, SimpleInfectionSimulator* pSimulation, Variant *pVariant) : _sim(pSim), _simulation(pSimulation), _variant(pVariant)
{
}

void SeedCasesCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	auto args = pCmdLine->GetArgs();
	
	auto random = RandomSource();
	
	int numToSeed = 0;
	int id = 0;
	switch (args.size())
	{
	case 2:
		numToSeed = atoi(args[1].c_str());
		if (numToSeed < 1) {
			cout << "You must seed at least one case\r\b";
			return;
		}
		_simulation->Seed(random, _variant,  5);
		break;
	case 3:
		id = atoi(args[2].c_str());
		if (id >= static_cast<int>(_sim->GetCounties()->size())) {
			cout << "Invalid County Index\r\b";
			return;
		}

		numToSeed = atoi(args[1].c_str());
		if (numToSeed < 1) {
			cout << "You must seed at least one case\r\b";
			return;
		}

		_simulation->Seed(random, _variant, (*_sim->GetCounties())[id], 5);
		break;
	default:
		pConsole->WriteLine("SYNTAX: seed number_to_seed [countyNumber]");
		break;
	}
}

CommandInfo SeedCasesCommand::GetInfo()
{
	return CommandInfo("seed", "", "Seeds some new cases");
}