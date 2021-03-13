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
#include "DayStatsCollector.h"
#include "Person.h"
#include "SmallArea.h"
#include "SmallAreas.h"

DayStats::DayStats()
{
}

DayStats::DayStats(
	DWORD pTotalPopulation,
	DWORD pCurrentlyInfected, 
	DWORD pInfectedLast24hrs, 
	DWORD pTotalInfected, 
	DWORD p14dayInfectedRate,
	DWORD pTotalRecovered) :
	_currentlyInfected(pCurrentlyInfected),	
	_totalInfected(pTotalInfected),
	_totalPopulation(pTotalPopulation),
	_infectedLast24Hrs(pInfectedLast24hrs),
	_14dayInfectedRate(p14dayInfectedRate),
	_totalRecovered(pTotalRecovered)
{
}

DWORD DayStats::GetTotalPopulation() const
{
	return _totalPopulation;
}

DWORD DayStats::GetCurrentlyInfected() const
{
	return _currentlyInfected;
}

DWORD DayStats::GetInfectedLast24Hrs() const
{
	return _infectedLast24Hrs;
}

DWORD DayStats::GetTotalInfected() const
{
	return _totalInfected;
}

DWORD DayStats::Get14dayInfectedRate() const
{
	return _14dayInfectedRate;
}

DWORD DayStats::GetTotalRecovered() const
{
	return _totalRecovered;
}

AreaListStatsGenerator::AreaListStatsGenerator(std::function<bool(SmallArea& pArea)> pinclude): _include(std::move(pinclude)) {
}

void AreaListStatsGenerator::ProcessArea(SmallArea& pArea)
{
	if (!_include(pArea)) return;
	
	for (auto* person : *(pArea.GetPeople()))
	{
		_totalPopulation++;
		if (person->GetInfection() != nullptr)
		{
			_totalCurrentlyInfected++;
			_totalEverInfected++;
			if (person->GetInfection()->GetDaysInfected() <= 14)
				_totalInfectedInLast14Days++;
			if (person->GetInfection()->GetDaysInfected() <= 1)
				_totalInfectedLast24hrs++;
		}
		else if (person->IsImmune(nullptr))
			_totalRecovered++;
	}	
}

void AreaListStatsGenerator::ResetDay()
{
	_totalInfectedInLast14Days = 0;
	_totalInfectedLast24hrs = 0;
	_totalCurrentlyInfected = 0;
	_totalRecovered = 0;
	_totalPopulation = 0;
	_calculated = false;
}

DayStats& AreaListStatsGenerator::GetStats()
{
	if (!_calculated) {
		_currentStats = DayStats(
			_totalPopulation, 
			_totalCurrentlyInfected, 
			_totalInfectedLast24hrs, 
			_totalEverInfected, 
			static_cast<DWORD>(static_cast<double>(_totalInfectedInLast14Days) /
				(static_cast<double>(_totalPopulation) / 100000.0)),
			_totalRecovered);
		_calculated = true;
	}
	return _currentStats;
}

DayStatsCollector::DayStatsCollector(const PopulationSim& pPopulation) : _population(pPopulation)
{
	_nationalStats = AreaListStatsGenerator([&](SmallArea& pArea)
		{
			return true;
		});
}

void DayStatsCollector::Refresh()
{
	_nationalStats.ResetDay();
    for (auto* area : *_population.GetSmallAreas()->GetAreas())
	    _nationalStats.ProcessArea(*area);
	
}

DayStats& DayStatsCollector::GetNationalStats()
{
	return _nationalStats.GetStats();
}

boost::gregorian::date DayStatsCollector::GetDate() const
{
	return _population.GetDate();
}
