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

#include "TerminalConsole.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>

TerminalConsole::TerminalConsole()
{
	memset(&_style, 0, sizeof(ConsoleCharStyle));
}

void TerminalConsole::SetCursorPosition(int pCol, int pRow)
{
	std::cout << "\x1b[" << pCol << ";" << pRow << "H";	
}

void TerminalConsole::MoveCursor(int pRelCol, int pRelRow)
{
	if (pRelCol > 0)
		std::cout << "\x1b[" << pRelCol << "C";
	else if (pRelCol < 0)
		std::cout << "\x1b[" << pRelCol << "D";

	if (pRelRow > 0)
		std::cout << "\x1b[" << pRelRow  << "B";
	else if (pRelRow < 0)
		std::cout << "\x1b[" << pRelRow << "A";
}
void TerminalConsole::Clear()
{
	auto* clear = "\x1b[2J";
	puts(clear);

}
void TerminalConsole::EraseToEndL()
{
	auto clear = "\x1b[K";
	puts(clear);
}

void TerminalConsole::ShowCursor()
{
	auto clear = "\x1b[?25h";
	puts(clear);
}
void TerminalConsole::HideCursor()
{
	auto clear = "\x1b[?25l";
	puts(clear);
}

void TerminalConsole::SetMouseReporting(bool pOn)
{
	if (pOn) {
		auto clear = "\x1b[?1002h";
		puts(clear);
	}
	else
	{
		auto clear = "\x1b[?1002l";
		puts(clear);
	}
}

void TerminalConsole::SendRenditionParam(AnsiRenditionParameters pParameter)
{
	std::cout << "\x1b[" << static_cast<int>(pParameter) << "m";
	
	switch (pParameter)
	{
	case Reset:
		memset(&_style, 0, sizeof(ConsoleCharStyle));
		break;

	case Bold:
		_style.Bold = true;
		break;
	case Italic:
		break;
	case Underline:
		_style.Underline = true;
		break;
	case Blink:
		break;
	case Inverse:
		_style.Inverse = true;
		break;
	case NonBold:
		_style.Bold = false;
		break;
	case NonItalic: break;
	case BlinkOff: break;
	case NonInverse:
		_style.Inverse = false;
		break;
	case Reveal: break;
	case ForegroundBlack:
	case ForegroundRed:
	case ForegroundGreen:
	case ForegroundYellow:
	case ForegroundBlue:
	case ForegroundMagenta:
	case ForegroundCyan:
	case ForegroundWhite:
	case ForegroundExtended:
	case ForegroundDefault:
		_style.Foreground = static_cast<Color>(pParameter - ForegroundBlack);
		break;

	case BackgroundBlack:
	case BackgroundRed:
	case BackgroundGreen:
	case BackgroundYellow:
	case BackgroundBlue:
	case BackgroundMagenta:
	case BackgroundCyan:
	case BackgroundWhite:
	case BackgroundExtended:
	case BackgroundDefault:
		_style.Background = static_cast<Color>(pParameter - BackgroundBlack);
		break;
	default: break;
	}
}
void TerminalConsole::SetForeground(Color pColor)
{
	SendRenditionParam(static_cast<AnsiRenditionParameters>(pColor + ForegroundBlack));
}
void TerminalConsole::SetBackground(Color pColor)
{
	SendRenditionParam(static_cast<AnsiRenditionParameters>(pColor + BackgroundBlack));
}
void TerminalConsole::SetBold(bool pBold)
{
	if (pBold)
		SendRenditionParam(Bold);
	else
		SendRenditionParam(NonBold);
}

void TerminalConsole::ResetStyle()
{
	SendRenditionParam(Reset);
}

ConsoleKey TerminalConsole::ReadKey()
{
	ConsoleKey result;
	char key;
	auto processArrowKey = [&]() {
		switch (key)
		{
		case 'A':
			result.Type = Up;
			result.Ctrl = true;
			return true;
		case 'B':
			result.Type = Down;
			result.Ctrl = true;
			return true;
		case 'D':
			result.Type = Left;
			result.Ctrl = true;
			return true;
		case 'C':
			result.Type = Right;
			result.Ctrl = true;
			return true;
		}
		return false;
	};

	auto processKeyEscape = [&]() {
		switch (key)
		{
		case '[':
			key = getc(stdin);
			if (processArrowKey())
				return true;

			if (key >= '0' && key <= '9')
			{
				std::string val = "";
				while (key != '~')
				{
					val = val + key;
					key = getc(stdin);
				}
				result.Type = static_cast<ConsoleKeyType>(atoi(val.c_str()));
				return true;
			}
			break;
		case 'O':
			key = getc(stdin);
			return processArrowKey();
		}
		return false;
	};

	while (true) {
		result.Alt = false;
		result.Ctrl = false;
		result.Char = 0;

		key = getc(stdin);

		if (key == 27)
		{
			key = getc(stdin);
			bool complete = false;
			switch (key)
			{
			case 27:
				result.Alt = true;
				key = getc(stdin);
				complete = processKeyEscape();
				break;
			case '[':
			case 'O':
				complete = processKeyEscape();
				break;
			}

			if (complete) break;
		}
		else
		{
			result.Type = key == 127 ? Backspace : key == 13 ? Enter : Char;
			result.Char = key;
			break;
		}
	}
	return result;
}

std::string TerminalConsole::ReadLine()
{
	std::string line;
	std::getline(std::cin, line);
	return line;
	
}

char TerminalConsole::ReadChar()
{
	while (true)
	{
		auto key = ReadKey();
		switch (key.Type)
		{
		case Char:
		case Enter:
			return key.Char;
		default: break;
		}
	}
}

bool TerminalConsole::WaitForEnter()
{
	for (auto key = ReadKey(); key.Char == 13; key = ReadKey()) {}

	return true;
}


bool TerminalConsole::Write(int pBytes, BYTE* pData)
{
	fwrite((void*)pData, pBytes, 1, stdout);
	return true;
}



