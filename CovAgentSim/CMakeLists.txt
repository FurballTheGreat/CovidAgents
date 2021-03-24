# CMakeList.txt : CMake project for CMakeAgents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (
	CovAgentSim
	"CommandsGeneral.cpp" 
	"CommandsGeneral.h"
	"CommandsCounty.cpp" 
	"CommandsCounty.h"
	"CommandsLea.cpp" 
	"CommandsLea.h"
	"CommandsFileSystem.cpp" 
	"CommandsFileSystem.h"
	"CommandsSimulation.cpp" 
	"CommandsSimulation.h"
	"CovAgentSim.cpp" )

if (MSVC)
    target_link_libraries (CovAgentSim 
					   bcrypt 
					   libpng16
					   blend2d
					   Geographic_d
					   SharedLib
                       CommandProcessorLib
					   PopulationSimulationLib
					   SimulationsLib
					   VisualisationLib)
endif (MSVC)

if (UNIX)
    target_link_libraries (CovAgentSim 
	${Boost_LIBRARIES} 
	blend2d
	pthread
	${PNG_LIBRARIES}
	PkgConfig::LIBAV
	${GeographicLib_LIBRARIES}
	SharedLib 
	CommandProcessorLib 
	PopulationSimulationLib 
	SimulationsLib 
	VisualisationLib)
endif (UNIX)
	
# TODO: Add tests and install targets if needed.