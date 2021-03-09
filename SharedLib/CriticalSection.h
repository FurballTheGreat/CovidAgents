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

#ifndef _MSC_VER
#include <pthread.h>
#endif
class CriticalSection
{
private:
#ifdef _MSC_VER
    CRITICAL_SECTION _section;
#else
    pthread_mutex_t _mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
#endif


public:
	CriticalSection();
	~CriticalSection();

	void Enter();
	void Leave();
};

