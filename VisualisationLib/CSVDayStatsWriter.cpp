#include "CSVDayStatsWriter.h"

#include <codecvt>
#include <locale>

#include "County.h"
#include "DayStatsCollector.h"

CSVDayStatsWriter::CSVDayStatsWriter(PopulationSim& pPopulation, const std::string& pFileName) : _population(pPopulation)
{
	_file.open(pFileName, std::ios::out | std::ios::trunc);
	WriteHeaders(true, "National");
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	for(auto* county : *_population.GetCounties())
		WriteHeaders(false, converter.to_bytes(county->GetCode()));
	_file << "\r\n";
}

CSVDayStatsWriter::~CSVDayStatsWriter()
{
	try {
		_file.close();
	} catch(std::exception&)
	{
		
	}
}


void CSVDayStatsWriter::WriteHeaders(bool pFirst, const std::string& pPrefix)
{
	if (!pFirst) _file << ",";
	_file << pPrefix << "Population";
	_file << "," << pPrefix << "CurrentlyInfected";
	_file << "," << pPrefix << "14DayRate";
	_file << "," << pPrefix << "Last24Hours";
	_file << "," << pPrefix << "TotalRecovered";	
}

void CSVDayStatsWriter::WriteStats(bool pFirst, const DayStats& pStats)
{
	if (!pFirst) _file << ",";
	_file << std::to_string(pStats.GetTotalPopulation());
	_file << ","  << std::to_string(pStats.GetCurrentlyInfected());
	_file << "," << std::to_string(pStats.Get14dayInfectedRate());
	_file << "," << std::to_string(pStats.GetInfectedLast24Hrs());
	_file << ","  << std::to_string(pStats.GetTotalRecovered());
	
}


void CSVDayStatsWriter::WriteDay(DayStatsCollector& pStats)
{
	WriteStats(true, pStats.GetNationalStats());

	for (auto* county : *_population.GetCounties())
		WriteStats(false, pStats.GetCountyStats(county));
	_file << "\r\n";
}
