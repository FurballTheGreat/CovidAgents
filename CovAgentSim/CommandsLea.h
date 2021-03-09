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
#include "Console.h"

class PopulationSim;

class LocalElectoralAreasCommand : public Command {
private:
	PopulationSim* _sim;
public:
	LocalElectoralAreasCommand(PopulationSim* pSim);
	void ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine) override;
	CommandInfo GetInfo() override;
};


