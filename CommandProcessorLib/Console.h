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
#include "Common.h"

enum Color
{
	Black = 0,
	Red = 1,
	Green = 2,
	Yellow = 3,
	Blue = 4,
	Magenta = 5,
	Cyan = 6,
	White = 7,
};


typedef struct
{
	bool Bold;
	bool Underline;
	bool Inverse;
	Color Foreground;
	Color Background;
} ConsoleCharStyle;

typedef struct
{
	wchar_t Char;
	ConsoleCharStyle Style;
} ConsoleChar;

enum ConsoleKeyType
{
	Char,
	F1 = 11,
	F2 = 12,
	F3 = 13,
	F4 = 14,
	F5 = 15,
	F6 = 17,
	F7 = 18,
	F8 = 19,
	F9 = 20,
	F10 = 21,
	F11 = 23,
	F12 = 24,
	Home = 1,
	End = 4,
	Insert = 2,
	Delete = 3,
	Up = 40,
	Down = 41,
	Left = 42,
	Right = 43,
	Enter = 44,
	Backspace = 45,
	PageUp = 5,
	PageDown = 6
};

typedef struct
{
	ConsoleKeyType Type;
	char Char;
	bool Alt;
	bool Ctrl;
} ConsoleKey;


class Console
{
public:
	virtual ~Console() {}
	virtual void SetCursorPosition(int pCol, int pRow) = 0;
	virtual void MoveCursor(int pRelCol, int pRelRow) = 0;
	virtual void Clear() = 0;
	virtual void EraseToEndL() = 0;
	virtual void SetForeground(Color pColor) = 0;
	virtual void SetBackground(Color pColor) = 0;
	virtual void SetBold(bool pBold) = 0;
	virtual void ResetStyle() = 0;
	virtual void ShowCursor() = 0;
	virtual void HideCursor() = 0;

	virtual ConsoleKey ReadKey() = 0;
	virtual std::string ReadLine() = 0;
	virtual char ReadChar() = 0;

	virtual bool WaitForEnter() = 0;
	bool WriteLine(std::string pString);
	virtual bool Write(int pBytes, PBYTE data) = 0;
	bool Write(std::string pString);

	bool Write(std::wstring pString);
	bool WriteLine(std::wstring pString);
	bool WriteLine(const char* pMsg, ...);
	bool WriteLine(const wchar_t* pMsg, ...);
	bool WriteLine();
	bool Write(const char* pMsg, ...);
	bool Write(const wchar_t* pMsg, ...);
	bool Write(char pChar);
};

