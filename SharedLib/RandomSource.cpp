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
#include "RandomSource.h"

#include<fstream>
#include <cstdlib>
#ifdef _MSC_VER
#include <bcrypt.h>
#else
#endif


#include <mutex>

#include "Exceptions.h"

RandomSource::RandomSource()
{


	_buffer = static_cast<PUCHAR>(malloc(RANDOM_BUFFER_SIZE));
	_size = RANDOM_BUFFER_SIZE;
	FillRandomBuffer();
}

RandomSource::~RandomSource()
{
	free(_buffer);
}

void RandomSource::FillRandomBuffer()
{
#ifdef _MSC_VER
	if (BCryptGenRandom(nullptr, _buffer, _size, BCRYPT_USE_SYSTEM_PREFERRED_RNG) != STATUS_SUCCESS)
		throw RandomNumberGenerationException();
#else
	std::ifstream input("/dev/urandom", std::ios::binary);
	input.read(reinterpret_cast<char*>(_buffer), RANDOM_BUFFER_SIZE);
	if (!input)
		throw RandomNumberGenerationException();
#endif
	
	_offset = 0;
	
}


