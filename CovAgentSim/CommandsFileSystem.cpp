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