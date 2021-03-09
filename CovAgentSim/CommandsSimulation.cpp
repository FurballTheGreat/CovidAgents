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
#include <blend2d/rgba.h>
#include "boost/date_time/gregorian/gregorian.hpp"


#include "County.h"
#include "LocalElectoralArea.h"
#include "MapPlotter.h"
#include "PopulationSim.h"
#include "RandomSource.h"
#include "SimpleInfectionSimulator.h"
#include "SmallArea.h"
#include "StandardVariant.h"

SimpleSimulationCommand::SimpleSimulationCommand(PopulationSim* pSim) : _sim(pSim) {
}

void SimpleSimulationCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	auto args = pCmdLine->GetArgs();
	if (args.size() < 2)
		return;

	auto id = atoi(args[1].c_str());
	if (id >= static_cast<int>(_sim->GetCounties()->size()))
		return;

	
	
	auto* area = (*_sim->GetCounties())[id];
	auto areas = area->GetSmallAreas();
	auto plotter2 = MapPlotter(&areas);
	SimpleInfectionSimulator simulator(*_sim);

	auto random = RandomSource();
	auto variant = StandardVariant();
	simulator.Seed(random, &variant, (*_sim->GetCounties())[6], 5);
	for (DWORD day = 0; day < 365; day++)
	{

		std::string fileName = "c:\\personal\\" + std::to_string(day) + ".png";

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
		simulator.ProceedDay(random, 0, 5, 0, 4);
		end = clock();
		time_spent = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
		std::cout << _sim->GetDate() << " processed in " << time_spent << "s, a total of " << simulator.GetTotalCurrentlyInfected() << " people are currently infected \r\n";
	}
}

CommandInfo SimpleSimulationCommand::GetInfo()
{
	return CommandInfo("simplesim", "", "Displays County Status");
}