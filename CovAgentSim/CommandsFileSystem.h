#pragma once
#include "CommandProcessor.h"

class PwdCommand : public Command {
public:
	PwdCommand();
	void ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine);
	CommandInfo GetInfo();
};

class CdCommand : public Command {
public:
	CdCommand();
	void ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine);
	CommandInfo GetInfo();
};
