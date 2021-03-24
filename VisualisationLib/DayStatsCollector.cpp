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

#include <iostream>



#include "County.h"
#include "LocalElectoralArea.h"
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
	DWORD p14dayInfectedRate,
	DWORD pTotalRecovered) :
	_totalPopulation(pTotalPopulation),
	_currentlyInfected(pCurrentlyInfected),
	_14dayInfectedRate(p14dayInfectedRate),
	_infectedLast24Hrs(pInfectedLast24hrs),
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

const DayStats& AreaListStatsGenerator::GetStats()
{
	if (!_calculated) {
		_currentStats = DayStats(
			_totalPopulation, 
			_totalCurrentlyInfected, 
			_totalInfectedLast24hrs, 
			static_cast<DWORD>(static_cast<double>(_totalInfectedInLast14Days) /
				(static_cast<double>(_totalPopulation) / 100000.0)),
			_totalRecovered);
		_calculated = true;
	}
	return _currentStats;
}

DayStatsCollector::DayStatsCollector(PopulationSim& pPopulation) : _population(pPopulation)
{
	_nationalStats = AreaListStatsGenerator([&](SmallArea& pArea)
		{
			return true;
		});

	for(auto* county : *(_population.GetCounties()))
	{
		_countyStats.insert(std::make_pair(county, new AreaListStatsGenerator([county](SmallArea& pArea)
			{
				
				auto result =  pArea.GetElectoralArea()->GetCounty()->GetCode() == county->GetCode();
//				std::wcout << pArea.GetElectoralArea()->GetCounty()->GetCode() << " " << county->GetCode() << " " << result << "\r\n";
				return result;
			})));
	}
}

DayStatsCollector::~DayStatsCollector()
{
	for (auto stat : _countyStats)
		delete stat.second;
}

void DayStatsCollector::Refresh()
{
	_nationalStats.ResetDay();
	for (auto countyStat : _countyStats)
		countyStat.second->ResetDay();
	for (auto* area : *_population.GetSmallAreas()->GetAreas()) {
		_nationalStats.ProcessArea(*area);
		for (auto countyStat : _countyStats)
			countyStat.second->ProcessArea(*area);
	}	
}

const DayStats& DayStatsCollector::GetNationalStats()
{
	return _nationalStats.GetStats();
}

boost::gregorian::date DayStatsCollector::GetDate() const
{
	return _population.GetDate();
}

const DayStats& DayStatsCollector::GetCountyStats(County* pCounty)
{
	return _countyStats.at(pCounty)->GetStats();
}
