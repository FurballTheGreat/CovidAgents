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
#include "Console.h"


enum AnsiRenditionParameters
{
	Reset = 0,
	Bold = 1,
	Italic = 3,
	Underline = 4,
	Blink = 5,
	Inverse = 7,
	PrimaryFont = 10,
	SecondaryFont1 = 11,
	SecondaryFont2 = 12,
	SecondaryFont3 = 13,
	SecondaryFont4 = 14,
	SecondaryFont5 = 15,
	SecondaryFont6 = 16,
	SecondaryFont7 = 17,
	SecondaryFont8 = 18,
	SecondaryFont9 = 19,
	NonBold = 22,
	NonItalic = 23,
	BlinkOff = 25,
	NonInverse = 27,
	Reveal = 28,
	ForegroundBlack = 30,
	ForegroundRed = 31,
	ForegroundGreen = 32,
	ForegroundYellow = 33,
	ForegroundBlue = 34,
	ForegroundMagenta = 35,
	ForegroundCyan = 36,
	ForegroundWhite = 37,
	ForegroundExtended = 38,
	ForegroundDefault = 39,
	BackgroundBlack = 40,
	BackgroundRed = 41,
	BackgroundGreen = 42,
	BackgroundYellow = 43,
	BackgroundBlue = 44,
	BackgroundMagenta = 45,
	BackgroundCyan = 46,
	BackgroundWhite = 47,
	BackgroundExtended = 48,
	BackgroundDefault = 49,
	Framed = 50,
	Encircled = 52,
	Overlined = 53,
	NonFramed = 54,
	NonOverlined = 55


};


class TerminalConsole : public Console
{
private:
	ConsoleCharStyle _style;
public:
	TerminalConsole();
	void SetCursorPosition(int pCol, int pRow) override;
	void MoveCursor(int pRelCol, int pRelRow) override;
	void Clear() override;
	void EraseToEndL() override;
	void SetMouseReporting(bool pOn);
	void SendRenditionParam(AnsiRenditionParameters pParameter);
	void SetForeground(Color pColor) override;
	void SetBackground(Color pColor) override;
	void SetBold(bool pBold) override;
	void ResetStyle() override;
	void ShowCursor() override;
	void HideCursor() override;




	ConsoleKey ReadKey() override;
	std::string ReadLine() override;
	char ReadChar() override;

	bool WaitForEnter() override;
	bool Write(int pBytes, BYTE *data) override;
};

