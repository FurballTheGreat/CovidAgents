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

#include "StandardVariant.h"
#include <random>
#include "RandomSource.h"

StandardVariant::StandardVariant()
	: Variant("StandardVariant")
{
}

std::vector<double> StandardVariant::GetInfectiousnessByDay(RandomSource& pRandom)
{
	auto byDay = std::vector<double>();

	auto engine = std::mt19937{ pRandom.Get<DWORD>() };

	std::gamma_distribution<double>  distribution(1.813, 2.199);
	auto length = (int)distribution(engine)+1;
	for (auto i = 0; i < length; i++) {
		double val = 0.35;
		byDay.push_back(val);
	}
	return byDay;
}
