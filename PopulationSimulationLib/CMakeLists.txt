# CMakeList.txt : CMake project for CMakeAgents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (
	PopulationSimulationLib STATIC
	"BasePopulationContainer.cpp" 
	"BasePopulationContainer.h" 
	"CensusSAPS.h"  
	"Commuter.h"
	"Commuter.cpp" 
	"County.h"
	"County.cpp" 
	"Enums.h" 
	"Household.h"
	"Household.cpp" 
	"Infection.h"
	"Infection.cpp" 
	"LocalElectoralArea.cpp"
	"LocalElectoralArea.h" 
	"NamedCode.cpp"
	"NamedCode.h" 
	"Person.cpp"
	"Person.h" 
	"Population.h"
	"Population.cpp" 
	"PopulationDistributionDefinition.h"
	"PopulationDistributionDefinition.cpp" 
	"PopulationSim.h"
	"PopulationSim.cpp" 
	"Region.h"
	"Region.cpp"
	"SmallArea.h"
	"SmallArea.cpp"
	"SmallAreaPolygon.h"
	"SmallAreaPolygon.cpp"
	"SmallAreas.h"
	"SmallAreas.cpp"
	"SubRegion.h"
	"SubRegion.cpp"
	"Variant.h"
	"Variant.cpp" )
