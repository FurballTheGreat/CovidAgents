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
#include <thread>

#include "Common.h"
#include<vector>
#include<functional>

class VectorTaskThreader
{
public:
	template<typename VectorType, typename ResultType> void Process(
		VectorType* pItems,  
		std::function<void(VectorType*, DWORD, DWORD, ResultType*)>  pProcessBlock,
		std::function<void(std::vector < ResultType*>*)> pProcessResults
		);
};



template<typename VectorType, typename ResultType> void VectorTaskThreader::Process(
	VectorType* pItems,
	std::function<void(VectorType*, DWORD, DWORD, ResultType*)>  pProcessBlock,
	std::function<void(std::vector < ResultType*>*)> pProcessResults)
{
	auto processor_count = std::thread::hardware_concurrency() / 2;
	if (processor_count == 0) processor_count = 1;
	auto numPerThread = pItems->size() / processor_count;
	std::vector<ResultType*> floating = std::vector<ResultType*>();

	auto f = [numPerThread, pItems,pProcessBlock, &floating, processor_count](DWORD j) {
		auto min = (DWORD)(j * numPerThread);
		auto max = j == processor_count - 1 ? pItems->size() : min + numPerThread;
		
		pProcessBlock(pItems, min, static_cast<DWORD>(max), floating[j]);
	};

	auto threads = std::vector<std::thread*>();
	for (DWORD n = 0; n < processor_count; n++) {
		floating.push_back(new ResultType());
		threads.push_back(new std::thread(f, n));
	}

	for (DWORD n = 0; n < processor_count; n++)
		threads[n]->join();

	pProcessResults(&floating);
	for (DWORD n = 0; n < processor_count; n++)
	{
		delete threads[n];
		delete floating[n];
	}
}

