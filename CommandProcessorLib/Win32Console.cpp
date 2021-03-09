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

#include "Win32Console.h"

Win32Console::Win32Console()
{
	/*auto iStdIn = GetStdHandle(STD_INPUT_HANDLE);
    auto iStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD inConsoleMode,
          outConsoleMode;
        if (!GetConsoleMode(iStdIn,&inConsoleMode ))
    {
        WriteLine("failed to get input console mode");
        return;
    }
    if (!GetConsoleMode(iStdOut, &outConsoleMode))
    {
        WriteLine("failed to get output console mode");
        return;
    }

    inConsoleMode |= ENABLE_VIRTUAL_TERMINAL_INPUT;
    outConsoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;


    if (!SetConsoleMode(iStdIn, inConsoleMode))
    {
        WriteLine("failed to set input console mode");
        return;
    }
    if (!SetConsoleMode(iStdOut, outConsoleMode))
    {
        WriteLine("failed to set output console mode");
        return;
    }*/
}
