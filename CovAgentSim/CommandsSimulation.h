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
#include "CommandProcessor.h"
#include "SimpleInfectionSimulator.h"

class PopulationSim;

class SimpleSimulationCommand : public Command {
private:
	PopulationSim* _sim;
	SimpleInfectionSimulator* _simulation;
public:
	SimpleSimulationCommand(PopulationSim* pSim, SimpleInfectionSimulator* pSimulation);
	void ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine);
	CommandInfo GetInfo();
};

class SeedCasesCommand : public Command {
private:
	PopulationSim* _sim;
	SimpleInfectionSimulator* _simulation;
	Variant* _variant;
public:
	SeedCasesCommand(PopulationSim* pSim, SimpleInfectionSimulator* pSimulation, Variant* pVariant);
	void ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine);
	CommandInfo GetInfo();
};
