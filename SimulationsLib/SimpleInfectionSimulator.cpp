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
#include "SimpleInfectionSimulator.h"
#include <iostream>
#include "Common.h"
#include "Commuter.h"
#include "County.h"
#include "Household.h"
#include "LocalElectoralArea.h"
#include "Population.h"
#include "PopulationSim.h"
#include "RandomSource.h"
#include "Person.h"
#include "Variant.h"
#include "VectorTaskThreader.h"


SimpleInfectionSimulator::SimpleInfectionSimulator(PopulationSim& pPopulation): _population(pPopulation) {
}

void SimpleInfectionSimulator::Seed(RandomSource& pRandomSource, Variant* pVariant, DWORD pCount)
{
	Person* people = _population.GetPopulation().GetPeople();
	for (DWORD i = 0; i < pCount; i++)
	{
		DWORD index;
		for (index = pRandomSource.Get<DWORD>(static_cast<DWORD>(_population.GetPopulation().GetSize()));
			people[index].GetInfection()!=nullptr;
			index = pRandomSource.Get<DWORD>(static_cast<DWORD>(_population.GetPopulation().GetSize())));

		InfectPerson(pRandomSource, &people[index], pVariant);
	}
}

void SimpleInfectionSimulator::Seed(RandomSource& pRandomSource, Variant *pVariant, County* pCounty, DWORD pCount)
{
	auto* people = pCounty->GetPeople();
	for (DWORD i = 0; i < pCount; i++)
	{
		DWORD index;
		for (index = pRandomSource.Get<DWORD>(static_cast<DWORD>(people->size()));
			(*people)[index]->GetInfection() != nullptr ;
			index = pRandomSource.Get<DWORD>(static_cast<DWORD>(people->size())));

		InfectPerson(pRandomSource, (*people)[index], pVariant);
	}
}

void SimpleInfectionSimulator::InfectPerson(RandomSource& pRandom, Person* pPerson, Variant* pVariant)
{
	auto infection = new Infection(pRandom,pVariant,_population);
	_infected.insert(pPerson);
	pPerson->SetInfection(infection);
}

class SimpleInfectSimThreadResult
{
public:
	std::vector<Person*> newInfections;
	std::vector<std::tuple<Person *,Infection *>> removeInfections;
};

void SimpleInfectionSimulator::ProceedDay(
	RandomSource& pR, 
	DWORD pMinJobContacts, 
	DWORD pMaxJobContacts,
	DWORD pMinLocalContact,
	DWORD pMaxLocalContacts)
{
	_population.AddDay();
	

	VectorTaskThreader threader;

	threader.Process<std::set<Person*>, SimpleInfectSimThreadResult>(
		&_infected,
		[&](std::set<Person*>* pItems, DWORD pMin, DWORD pMax, SimpleInfectSimThreadResult* pResults)
		{
			RandomSource randomSource;
			auto it = pItems->begin();
			std::advance(it, (int)pMin);
			for (DWORD i = 0; i < pMax-pMin; i++, ++it)
			{
				auto infected = *it;
				if (infected->GetInfection() != nullptr && !infected->GetInfection()->IsActiveYet()) continue;
				if (infected->GetInfection() == nullptr || !infected->GetInfection()->CheckIfStillInfectious())
				{
					auto* infect = infected->GetInfection();
					if (infect != nullptr) {
						infected->SetInfection(nullptr);
						pResults->removeInfections.emplace_back(infected,infect);
					}
					else
					{
						std::cout << "Null Infection\r\n";
					}
				}
				else
				{
					for (auto* other : (*infected->GetHousehold()->GetMembers()))
						if (other != infected && other->GetInfection() == nullptr && !other->IsImmune(infected->GetInfection()->GetVariant())) {
							auto* const infection = infected->GetInfection()->ProcessContact(
								randomSource,
								infected,
								other);
							if (infection != nullptr) pResults->newInfections.push_back(other);
						}

					if (infected->GetCommuter() != nullptr)
					{

						const auto numJobContact = randomSource.Get<DWORD>(pMinJobContacts, pMaxJobContacts);

						auto const otherPeople = infected->GetCommuter()->GetDestination()->GetInwardCommuters();

						for (DWORD i = 0; i < numJobContact && infected->GetCommuter()->GetDestination()->GetInfectedPeopleSize() < otherPeople.size(); i++)
						{

							auto otherIndex = randomSource.Get<DWORD>(static_cast<DWORD>(otherPeople.size()));
							while ((otherPeople)[otherIndex]->GetPerson()->GetInfection() != nullptr)
								otherIndex = randomSource.Get<DWORD>(static_cast<DWORD>(otherPeople.size()));
							auto* other = (otherPeople)[otherIndex];
							auto* const infection = infected->GetInfection()->ProcessContact(
								randomSource,
								infected,
								other->GetPerson()
							);
							if (infection != nullptr) pResults->newInfections.push_back(other->GetPerson());
						}
					}

					const auto numLocalContact =randomSource.Get<DWORD>(pMinLocalContact, pMaxLocalContacts);
					auto* const otherPeople = infected->GetArea()->GetElectoralArea()->GetPeople();
					for (DWORD i = 0; i < numLocalContact && infected->GetArea()->GetElectoralArea()->GetPeople()->size() > infected->GetArea()->GetElectoralArea()->GetInfectedPeopleSize(); i++)
					{

						auto otherIndex = randomSource.Get<DWORD>(static_cast<DWORD>(otherPeople->size()));
						while ((*otherPeople)[otherIndex]->GetInfection() != nullptr)
							otherIndex = randomSource.Get<DWORD>(static_cast<DWORD>(otherPeople->size()));
						auto* other = (*otherPeople)[otherIndex];
						auto* const infection = infected->GetInfection()->ProcessContact(
							randomSource,
							infected,
							other);
						if (infection != nullptr) pResults->newInfections.push_back(other);
					}
				}
			}
		},
		[&](std::vector<SimpleInfectSimThreadResult*>* pAllResults)
		{
			for(auto threadResults : *pAllResults)
			{
				for (std::tuple<Person *,Infection*> removeInfection : threadResults->removeInfections)
				{
					delete std::get<1>(removeInfection);
					_infected.erase(std::get<0>(removeInfection));
					
				}

				for (auto* newInfection : threadResults->newInfections)
					_infected.insert(newInfection);
			}
			
		}
		);


	
	
	

	
		
	
	
}

DWORD SimpleInfectionSimulator::GetTotalCurrentlyInfected() const
{
	return static_cast<DWORD>(_infected.size());
}

PopulationSim& SimpleInfectionSimulator::GetPopulation() const
{
	return _population;
}
