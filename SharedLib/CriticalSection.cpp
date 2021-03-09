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
#include "CriticalSection.h"

CriticalSection::CriticalSection()
{
#ifdef _MSC_VER
    InitializeCriticalSection(&_section);
#endif
	
}

CriticalSection::~CriticalSection()
{
#ifdef _MSC_VER
    DeleteCriticalSection(&_section);
#endif

}

void CriticalSection::Enter()
{
#ifdef _MSC_VER
    EnterCriticalSection(&_section);
#else
    pthread_mutex_lock(&_mutex);
#endif

}

void CriticalSection::Leave()
{
#ifdef _MSC_VER
    LeaveCriticalSection(&_section);
#else
    pthread_mutex_unlock(&_mutex);
#endif
	
}
