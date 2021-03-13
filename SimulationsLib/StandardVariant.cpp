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
	auto length = pRandom.Get( 20)+4;
	auto engine = std::default_random_engine(pRandom.Get<DWORD>());

	const std::gamma_distribution<>  distribution(1.813, 2.199);
	
	for(auto i = 0; i< length;i++)
		byDay.push_back(distribution(engine));
	return byDay;
}
