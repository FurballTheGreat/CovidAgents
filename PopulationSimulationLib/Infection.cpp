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
#include "Infection.h"

#include "Person.h"
#include "PopulationSim.h"
#include "RandomSource.h"
#include "Variant.h"
#include "boost/date_time.hpp"

Infection::Infection(RandomSource& pRandom, Variant* pVariant,PopulationSim &pPopulationSim): _populationSim(pPopulationSim) {
	_infectiousnessByDay = pVariant->GetInfectiousnessByDay(pRandom);
	_variant = pVariant;
	_infectedDate = _populationSim.GetDate();
	_dayIndex = _populationSim.GetDayIndex();
}

boost::gregorian::date Infection::GetInfectedDate() const
{
	return _infectedDate;
}

DWORD Infection::GetDaysInfected() const
{
	const DWORD daysInfected =_populationSim.GetDayIndex()-  _dayIndex ;
	return daysInfected;
}

Variant* Infection::GetVariant() const
{
	return _variant;
}


Infection* Infection::ProcessContact(RandomSource& pRandom, Person* pSourcePerson, Person* pContact)
{
	if (pSourcePerson->GetInfection() == nullptr) return nullptr;
	const DWORD daysInfected = pSourcePerson->GetInfection()->GetDaysInfected();
	if(pContact->IsImmune(pSourcePerson->GetInfection()->GetVariant()))
		return nullptr;
	if (daysInfected < _infectiousnessByDay.size()) {
		auto random = pRandom.Get<DWORD>( 1000);
		if (random<= _infectiousnessByDay[daysInfected]*10 && pContact->GetInfection() == nullptr)
		{
			auto* infection = new Infection(pRandom, _variant, _populationSim);
			pContact->SetInfection(infection);
			return infection;
		}
	}

	return nullptr;
}

bool Infection::CheckIfStillInfectious( ) const
{
	
	const DWORD daysInfected = GetDaysInfected();
	if (daysInfected < _infectiousnessByDay.size())
		return true;
	return false;
}

bool Infection::IsActiveYet() const
{
	return _dayIndex < _populationSim.GetDayIndex();
}

