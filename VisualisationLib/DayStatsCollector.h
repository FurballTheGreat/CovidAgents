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
#include "PopulationSim.h"
#include <boost/date_time/gregorian/greg_date.hpp>
class SmallArea;

class DayStats
{
	DWORD _totalPopulation = 0;
	DWORD _currentlyInfected = 0;
	DWORD _totalInfected = 0;
	DWORD _14dayInfectedRate = 0;
	DWORD _infectedLast24Hrs = 0;
	DWORD _totalRecovered = 0;

public:
	DayStats();
	DayStats(
		DWORD pTotalPopulation,
		DWORD pCurrentlyInfected,
		DWORD pInfectedLast24hrs,
		DWORD pTotalInfected,
		DWORD p14dayInfectedRate,
		DWORD pTotalRecovered);
	DWORD GetTotalPopulation() const;
	DWORD GetCurrentlyInfected() const;
	DWORD GetInfectedLast24Hrs() const;
	DWORD GetTotalInfected() const;
	DWORD Get14dayInfectedRate() const;
	DWORD GetTotalRecovered() const;
};

class AreaListStatsGenerator
{
	std::function<bool(SmallArea& pArea)> _include;
	DWORD _totalInfectedInLast14Days = 0;
	DWORD _totalCurrentlyInfected = 0;
	DWORD _totalRecovered = 0;
	DWORD _totalPopulation = 0;
	DWORD _totalInfectedLast24hrs = 0;
	DWORD _totalEverInfected = 0;
	bool _calculated = false;
	DayStats _currentStats = {};
public:
	AreaListStatsGenerator() = default;
	AreaListStatsGenerator(std::function<bool(SmallArea& pArea)> pinclude);
	void ProcessArea(SmallArea& pArea);
	void ResetDay();
	
	DayStats& GetStats();	
};

class DayStatsCollector
{
	AreaListStatsGenerator _nationalStats ;
	const PopulationSim& _population;
public:
	DayStatsCollector(const PopulationSim& pPopulation);

	void Refresh();

	DayStats& GetNationalStats();
	boost::gregorian::date GetDate() const;
};

