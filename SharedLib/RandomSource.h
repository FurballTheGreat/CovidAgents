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

#include "Common.h"

#define RANDOM_BUFFER_SIZE 0X10000

namespace std {
	class mutex;
}

class RandomSource
{
private:
	PUCHAR _buffer;
	DWORD _size = 0;
	DWORD _offset = 0;


	void FillRandomBuffer();
public:
	RandomSource();
	~RandomSource();
	template<typename T> T Get();
	template<typename T> T Get(T pMin, T pMax);
	template<typename T> T Get(T pMax);
};


template <typename T> T RandomSource::Get()
{
	if (_size - _offset < sizeof(T))
		FillRandomBuffer();

	auto result = *reinterpret_cast<T*>(_buffer + _offset);
	_offset += sizeof(T);
	return result;
}

template <typename T> T RandomSource::Get(T pMax)
{
	if (_size - _offset < sizeof(T))
		FillRandomBuffer();

	auto result = *reinterpret_cast<T*>(_buffer + _offset);
	_offset += sizeof(T);
	return result % pMax;
}


template <typename T> T RandomSource::Get(T pMin, T pMax)
{
	if (_size - _offset < sizeof(T))
		FillRandomBuffer();

	auto result = *reinterpret_cast<T*>(_buffer + _offset);
	_offset += sizeof(T);
	return pMin+(result % (pMax-pMin));
}

