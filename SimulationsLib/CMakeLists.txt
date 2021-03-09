# CMakeList.txt : CMake project for CMakeAgents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (
	SimulationsLib STATIC
	"SimpleInfectionSimulator.h" 
	"SimpleInfectionSimulator.cpp" 
	"StandardVariant.h" 
	"StandardVariant.cpp" )


target_link_libraries(SimulationsLib PopulationSimulationLib)
