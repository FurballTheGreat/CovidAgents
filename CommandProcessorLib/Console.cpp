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

#include "Console.h"
#include <stdio.h>
#include <stdarg.h>
#include <wchar.h>
#include <locale>

#include <codecvt>

bool Console::Write(std::string pString)
{
	return Write(static_cast<int>(pString.length()), (BYTE*)pString.c_str());
}


bool Console::WriteLine(std::wstring pString)
{

	return Write(pString + L"\n\r");
}

bool Console::Write(std::wstring pString)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	
	auto converted = converter.to_bytes(pString);
	return Write(static_cast<int>(converted.size()), PBYTE(converted.c_str()));
}
bool Console::WriteLine(const char* pMsg, ...)
{
	char buffer[4096+3];
	va_list arg;
	va_start(arg, pMsg);
	int n = vsnprintf(buffer, 4096, pMsg, arg);
	va_end(arg);
	buffer[n++] = '\n';
	buffer[n++] = '\r';
	buffer[n] = 0;
	return Write(n, reinterpret_cast<BYTE*>(buffer));

}

bool Console::WriteLine(const wchar_t* pMsg, ...)
{
	wchar_t buffer[4096+3];

	va_list arg;
	va_start(arg, pMsg);
	int n = vswprintf(buffer, 4096, pMsg, arg);
	va_end(arg);

	buffer[n] = 0;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	auto converted = converter.to_bytes(buffer);
	
	return Write(static_cast<int>(converted.length()), (PBYTE)(converted.c_str()));

}

bool Console::WriteLine()
{
	return WriteLine("");
}
bool Console::Write(const char* pMsg, ...)
{
	char buffer[4096];
	va_list arg;
	va_start(arg, pMsg);
	int n = vsnprintf(buffer, 4096, pMsg, arg);
	va_end(arg);
	return Write(n, reinterpret_cast<BYTE*>(buffer));
}

bool Console::Write(const wchar_t* pMsg, ...)
{
	wchar_t buffer[4096];

	va_list arg;
	va_start(arg, pMsg);
	int n = vswprintf(buffer, 4096, pMsg, arg);
	va_end(arg);
	buffer[n] = 0;
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	auto converted = converter.to_bytes(buffer);

	return Write(static_cast<int>(converted.length()), (PBYTE)(converted.c_str()));
}

bool Console::Write(char pChar)
{
	return Write(1, reinterpret_cast<BYTE*>(&pChar));
}

bool Console::WriteLine(std::string pString)
{
	auto line = pString + "\n\r";
	Write(static_cast<int>(line.length()), (BYTE*)line.c_str());
	return true;
}

