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

#include "CommandsFileSystem.h"

#include <iostream>
#include <boost/filesystem.hpp>

PwdCommand::PwdCommand() {

}

void PwdCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	std::cout << boost::filesystem::current_path() << "\r\n";	
}

CommandInfo PwdCommand::GetInfo()
{
	return CommandInfo("pwd", "", "Prints the current working directory");
}


CdCommand::CdCommand() {

}

void CdCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	auto args = pCmdLine->GetArgs();
	if (args.size() < 2)
		cout << "SYNTAX: cd [path]" << "\r\n";
	try
	{
		boost::filesystem::current_path(args[1]);
		std::cout << boost::filesystem::current_path() << "\r\n";		
	} catch(boost::filesystem::filesystem_error& err)
	{
		cout << "Error: " << err.what() << "\r\n";
	}
}

CommandInfo CdCommand::GetInfo()
{
	return CommandInfo("cd", "", "Change the current working directory");
}