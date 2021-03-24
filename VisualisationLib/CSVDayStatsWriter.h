#pragma once
#include <fstream>

class PopulationSim;
class DayStats;
class DayStatsCollector;

class CSVDayStatsWriter
{
	PopulationSim& _population;
	std::ofstream _file;
	void WriteHeaders(bool pFirst, const std::string& pPrefix);
	void WriteStats(bool pFirst, const DayStats& pStats) ;
public:
	CSVDayStatsWriter(PopulationSim& pPopulation, const std::string& pFileName);
	~CSVDayStatsWriter();

	void WriteDay(DayStatsCollector& pStats);
};

