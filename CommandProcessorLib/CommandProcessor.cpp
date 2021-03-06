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

#include "CommandProcessor.h"
#include "Console.h"

#include<vector>
using namespace std;

ParsedCommandLine::ParsedCommandLine(string pCommandLine, IExecutionContext* pHost) {
	size_t pos = 0;
	_arguments = vector<string>();
	_host = pHost;
	_originalLine = "";
	while (pos < pCommandLine.length()) {
		_originalLine += pCommandLine.substr(pos, pCommandLine.find_first_of('%', pos) - pos);
		if (pCommandLine.find_first_of('%', pos) == string::npos) {
			break;
		}
		auto start = pCommandLine.find_first_of('%', pos) + 1;
		if (pCommandLine.find_first_of('%', start) == string::npos) {
			_originalLine += "%";
			pos = start;
			continue;
		}
		auto end = pCommandLine.find_first_of('%', start) - 1;

		if (end < start)

			_originalLine += "%";
		else {
			string varName = pCommandLine.substr(start, end - start + 1);
			_originalLine += pHost->GetVariable(varName);
		}

		pos = end + 2;
	}

	pos = 0;

	for (;;) {
		bool skip = false;
		while (pCommandLine[pos] == ' ')
			pos++;
		if (pCommandLine[pos] == '"') {
			if (pCommandLine[pos + 1] == '"')
			{
				pos++;
			}
			else {
				auto nextq = pCommandLine.find('"', pos + 1);
				if (nextq == string::npos) {
					if (pos < pCommandLine.length())
					{
						string expr(pCommandLine.substr(pos + 1, pCommandLine.length()));
						_arguments.push_back(expr);
					}
					skip = true;
					break;
				}
				auto expr(pCommandLine.substr(pos + 1, nextq - pos - 1));
				_arguments.push_back(expr);
				pos = nextq + 1;
				skip = true;
			}
		}

		if (!skip) {
			auto next = pCommandLine.find(' ', pos);
			if (next == string::npos) {
				if (pos < pCommandLine.length())
				{
					string expr(pCommandLine.substr(pos, pCommandLine.length()));
					_arguments.push_back(expr);
				}
				break;
			}
			string expr(pCommandLine.substr(pos, next - pos));
			_arguments.push_back(expr);
			pos = next + 1;
		}
	}
	if (_arguments.size() > 0)
		_command = _arguments.front();
}

string ParsedCommandLine::GetName() {
	return _command;
}

string ParsedCommandLine::GetRaw() {
	return _originalLine;
}

ParsedCommandLine ParsedCommandLine::GetParametersAsLine() {
	if (_arguments.size() <= 1)
		return ParsedCommandLine(_originalLine, _host);

	return ParsedCommandLine(_originalLine.substr(_command.length() + 1, string::npos), _host);
}

vector<string> ParsedCommandLine::GetArgs() {
	return _arguments;
}

IExecutionContext* ParsedCommandLine::GetHost() {
	return _host;
}

Command::Command() {
}

CommandProcessor::CommandProcessor(vector<Command*>* pCommands) {
	_commands = pCommands;

}



bool CommandProcessor::ProcessCommandLine(Console* pConsole, ParsedCommandLine* pLine) {
	string cmd = pLine->GetName();
	bool done = false;
	for (auto it = _commands->begin(); it != _commands->end(); ++it)
		if ((*it)->GetInfo().GetName() == cmd) {
			(*it)->ProcessCommand(pConsole, pLine);
			done = true;
			break;
		}
	return done;
}


CommandInfo::CommandInfo(string pName, string pParams, string pDescription)
{
	_name = pName;
	_params = pParams;
	_description = pDescription;
}

string CommandInfo::GetName()
{
	return _name;
}
string CommandInfo::GetParams()
{
	return _params;
}
string CommandInfo::GetDescription()
{
	return _description;
}

