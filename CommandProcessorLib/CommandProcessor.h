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

#include<string>
#include<vector>
#include "Console.h"

using namespace std;


class IExecutionContext
{
public:
	virtual string GetVariable(string pName) = 0;
	virtual void SetVariable(string pName, string pValue) = 0;
};

class ParsedCommandLine
{
private:
	vector<string> _arguments;
	string _command;
	string _originalLine;
	IExecutionContext* _host;
public:
	ParsedCommandLine(string pCommandLine, IExecutionContext* pHost);

	string GetName();
	string GetRaw();
	vector<string> GetArgs();
	IExecutionContext* GetHost();
	ParsedCommandLine GetParametersAsLine();
};

class CommandInfo
{
private:
	string _name;
	string _params;
	string _description;
public:
	CommandInfo(string pName, string pParams, string pDescription);

	string GetName();
	string GetParams();
	string GetDescription();
};


class Command
{
public:
	Command();
	virtual void ProcessCommand(Console* pConsole, ParsedCommandLine* pCommandLine) = 0;
	virtual CommandInfo GetInfo() = 0;
};

class CommandProcessor
{
private:
	vector<Command*>* _commands;

public:
	CommandProcessor(vector<Command*>* pCommands);
	bool ProcessCommandLine(Console* _console, ParsedCommandLine* pLine);
};
