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
#include <iostream>
#include "boost/date_time/gregorian/gregorian.hpp"

#include "Population.h"
#include "PopulationDistributionDefinition.h"
#include "RandomSource.h"
#include "SmallAreas.h"
#include "CommandProcessor.h"
#include "CommandsGeneral.h"
#include "CommandsCounty.h"
#include "CommandsFileSystem.h"
#include "CommandsLea.h"
#include "CommandsSimulation.h"
#include "Console.h"
#include "County.h"
#include "LocalElectoralArea.h"
#include "MapPlotter.h"
#include "Win32Console.h"
#include "PopulationSim.h"

#include "SimpleInfectionSimulator.h"
#include "SmallArea.h"
#include "StandardVariant.h"
#include "Variant.h"

using namespace boost::gregorian;

using namespace GeographicLib;


class ExecutionContext : public IExecutionContext
{

public:
	ExecutionContext() {

	}
	string GetVariable(string pName) {
		return "";
	}
	void SetVariable(string pName, string pValue) {
	}
};

int main(int argc, char** argv)
{
    auto popDist = PopulationDistributionDefinition(argv[1]);
    auto smallAreas = SmallAreas(argv[2]);

	if(argc<3)
	{
		cout << "SYNTAX: CovAgentSim census2016.popdistbyage output.smallareas" << "\r\n";
		return 1;
	}
	auto random = RandomSource();
	std::string ds("2020/02/25");
	date currentDate(from_string(ds));

	clock_t begin = clock();
	
	auto population = Population(&popDist);
	clock_t end = clock();

	auto time_spent = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Loaded Data: " << time_spent << "s\r\n";
	std::cout << "Building Population...\r\n";
	begin = clock();
	PopulationSim popSim(&random, &population, &smallAreas, currentDate);
	end = clock();
	time_spent = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Built Population in " << time_spent << "s\r\n" << "Generated " << smallAreas.GetPopulationCount() << " people into "<<  smallAreas.GetHouseholdCount()  <<" households\r\n";
	
	SimpleInfectionSimulator simulation(popSim);
	StandardVariant variant;
	
	auto console = Win32Console();
	auto executionContext = ExecutionContext();
	
	std::vector<Command*> commands = {
		new HelpCommand(&commands),
		new RegionsCommand(&popSim),
		new SubRegionsCommand(&popSim),
		new CountiesCommand(&popSim),
		new CountyStatusCommand(&popSim),
		new LocalElectoralAreasCommand(&popSim),
		new SimpleSimulationCommand(&popSim, &simulation),
		new SeedCasesCommand(&popSim, &simulation, &variant),
		new CdCommand(),
		new PwdCommand()
	};
	auto cmdProc = CommandProcessor(&commands);

	while (true) {
		cout << popSim.GetDate() << "> ";
		auto line = console.ReadLine();
		auto cmdLine = ParsedCommandLine(line, reinterpret_cast<IExecutionContext*>(&executionContext));
		cmdProc.ProcessCommandLine(&console, &cmdLine);
	}
}
