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

#include "CommandsSimulation.h"

#include <iostream>
#include <blend2d.h>
#include "boost/date_time/gregorian/gregorian.hpp"


#include "County.h"
#include "DayInfoPlotter.h"
#include "DayStatsCollector.h"
#include "DrawingCanvas.h"
#include "DrawingFont.h"
#include "FFMpegH264Writer.h"
#include "LocalElectoralArea.h"
#include "MapPlotter.h"
#include "PngWriter.h"
#include "PopulationSim.h"
#include "RandomSource.h"
#include "SimpleInfectionSimulator.h"
#include "SmallArea.h"
#include "SmallAreas.h"
#include "StandardVariant.h"

BLRgba32 HSVtoRGB(float pHue, float pSaturation, float pBrightness) {
	//if (pHue > 360 || pHue < 0 || pSaturation>100 || pSaturation < 0 || pBrightness>100 || pBrightness < 0) {
	//	cout << "The givem HSV values are not in valid range" << endl;
	//	return;
	//}
	float s = pSaturation / 100;
	float v = pBrightness / 100;
	float C = s * v;
	float X = C * (1 - abs(fmod(pHue / 60.0, 2) - 1));
	float m = v - C;
	float r, g, b;
	if (pHue >= 0 && pHue < 60) {
		r = C, g = X, b = 0;
	}
	else if (pHue >= 60 && pHue < 120) {
		r = X, g = C, b = 0;
	}
	else if (pHue >= 120 && pHue < 180) {
		r = 0, g = C, b = X;
	}
	else if (pHue >= 180 && pHue < 240) {
		r = 0, g = X, b = C;
	}
	else if (pHue >= 240 && pHue < 300) {
		r = X, g = 0, b = C;
	}
	else {
		r = C, g = 0, b = X;
	}
	int R = (r + m) * 255;
	int G = (g + m) * 255;
	int B = (b + m) * 255;

	 BLRgba32 color(B, G, R);
	 return color;

}

SimpleSimulationCommand::SimpleSimulationCommand(PopulationSim* pSim, SimpleInfectionSimulator* pSimulation) : _sim(pSim), _simulation(pSimulation) {
}

void SimpleSimulationCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	auto args = pCmdLine->GetArgs();

	int days;
	auto random = RandomSource();
	

	if(args.size()==2)
	{
		days = atoi(args[1].c_str());
		if (days < 1) {
			cout << "You must run at least one day\r\b";
			return;
		}
	} else
	{
		pConsole->WriteLine("SYNTAX: simplesim days_to_run number_to_seed [countyNumber]");
		return;
	}
	
	auto canvas = DrawingCanvas(1920, 1080);
	auto font = DrawingFont("Kosugi-Regular.ttf", 30);

	auto plotter = MapPlotter(_sim->GetSmallAreas()->GetAreas());
	auto infoPlotter = DayInfoPlotter(font);
	auto dayStats = DayStatsCollector(_simulation->GetPopulation());
	auto h264Writer = new FFMpegH264Writer("out.mp4", canvas.GetSize(), 30, 2000000);
	for (DWORD day = 0; day < static_cast<DWORD>(days); day++)
	{
		auto begin = clock();
		auto fileName = std::to_string(day) + ".png";
		//auto writer = PngWriter(fileName);
		
		canvas.Render([&](BLContext& pContext, BLPoint pOrigin, BLSize pSize)
			{
				BLSize splitSize(pSize.w / 2, pSize.h);
				BLPoint infoOrigin(pOrigin.x + splitSize.w, pOrigin.y);
				plotter.PlotMap(
					pContext,
					pOrigin,
					splitSize,
					_sim->GetDate(),
					[&](SmallArea& pArea, BLContext& pContext)
					{
						auto per100k = pArea.GetElectoralArea()->GetInfectedPer100k();
						auto intensity = 0;
						if (per100k > 1000)
							intensity = 255;
						if (per100k > 750)
							intensity = 230;
						if (per100k > 500)
							intensity = 210;
						if (per100k > 250)
							intensity = 190;
						if (per100k > 150)
							intensity = 180;
						if (per100k > 25)
							intensity = 150;
						if (per100k >= 1)
							intensity = 80;
						else
							intensity = 0;

						
						const BLRgba32 color =  BLRgba32(20, (255 - intensity) / 4, intensity);

						pContext.setFillStyle(color);
						pContext.setStrokeStyle(color);
						pContext.setStrokeWidth(10);
					});

				dayStats.Refresh();
				infoPlotter.Plot(pContext, infoOrigin, splitSize, dayStats);

			});
	//	canvas.WriteTo(writer);
		for(DWORD x = 0; x < 10; x++)
			canvas.WriteTo(*h264Writer);
	
		auto end = clock();
		auto time_spent = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Saved " << fileName << " in " << time_spent << "s\r\n";

		begin = clock();
		_simulation->ProceedDay(random, 0, 5, 0, 4);
		end = clock();
		time_spent = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
		std::cout << _sim->GetDate() << " processed in " << time_spent << "s, a total of " << _simulation->GetTotalCurrentlyInfected() << " people are currently infected \r\n";
	}

	delete h264Writer;
}

CommandInfo SimpleSimulationCommand::GetInfo()
{
	return CommandInfo("simplesim", "", "Displays County Status");
}


SeedCasesCommand::SeedCasesCommand(PopulationSim* pSim, SimpleInfectionSimulator* pSimulation, Variant *pVariant) : _sim(pSim), _simulation(pSimulation), _variant(pVariant)
{
}

void SeedCasesCommand::ProcessCommand(Console* pConsole, ParsedCommandLine* pCmdLine)
{
	auto args = pCmdLine->GetArgs();
	
	auto random = RandomSource();
	
	int numToSeed = 0;
	int id = 0;
	switch (args.size())
	{
	case 2:
		numToSeed = atoi(args[1].c_str());
		if (numToSeed < 1) {
			cout << "You must seed at least one case\r\b";
			return;
		}
		_simulation->Seed(random, _variant,  numToSeed);
		break;
	case 3:
		id = atoi(args[2].c_str());
		if (id >= static_cast<int>(_sim->GetCounties()->size())) {
			cout << "Invalid County Index\r\b";
			return;
		}

		numToSeed = atoi(args[1].c_str());
		if (numToSeed < 1) {
			cout << "You must seed at least one case\r\b";
			return;
		}

		_simulation->Seed(random, _variant, (*_sim->GetCounties())[id], numToSeed);
		break;
	default:
		pConsole->WriteLine("SYNTAX: seed number_to_seed [countyNumber]");
		break;
	}
}

CommandInfo SeedCasesCommand::GetInfo()
{
	return CommandInfo("seed", "", "Seeds some new cases");
}