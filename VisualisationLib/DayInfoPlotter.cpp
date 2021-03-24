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
#include "DayInfoPlotter.h"

#include <string>

#include "DayStatsCollector.h"

DayInfoPlotter::DayInfoPlotter(DrawingFont& pFont) :
	_font(pFont)
{
}

void DayInfoPlotter::Plot(BLContext& pContext, BLPoint& pOrigin, BLSize& pSize, DayStatsCollector& pStats) const
{
	const std::string infectedText = "Total Infected On Day " + std::to_string(pStats.GetNationalStats().GetInfectedLast24Hrs());
	const std::string rateText = "National 14 Per 100k rate on " + std::to_string(pStats.GetDate().day()) + "/" + std::to_string(pStats.GetDate().month()) + "/" + std::to_string(pStats.GetDate().year()) + " is " + std::to_string(pStats.GetNationalStats().Get14dayInfectedRate());
	const std::string recoveredText = "Total Recovered = " + std::to_string(pStats.GetNationalStats().GetTotalRecovered());
	const std::string totalCurrentlyText = "Total Currently Infected = " + std::to_string(pStats.GetNationalStats().GetCurrentlyInfected());
	const std::string totalPopulation = "Population = " + std::to_string(pStats.GetNationalStats().GetTotalPopulation());

	pContext.setCompOp(BL_COMP_OP_SRC_OVER);
    pContext.setFillStyle(BLRgba32(200,200,255));
    _font.DrawUtf8(pContext, BLPoint(pOrigin.x + 5, pOrigin.y + (_font.GetSize() + 5) * 1),rateText);
    _font.DrawUtf8(pContext, BLPoint(pOrigin.x + 5, pOrigin.y + (_font.GetSize() + 5) * 2), infectedText);
	_font.DrawUtf8(pContext, BLPoint(pOrigin.x + 5, pOrigin.y + (_font.GetSize() + 5) * 3), totalCurrentlyText);
	_font.DrawUtf8(pContext, BLPoint(pOrigin.x + 5, pOrigin.y + (_font.GetSize() + 5) * 4), recoveredText);
  //  pContext.postRotate(90);
	_font.DrawUtf8(pContext, BLPoint(pOrigin.x + 5, pOrigin.y + (_font.GetSize() + 5) * 5), totalPopulation);
}
