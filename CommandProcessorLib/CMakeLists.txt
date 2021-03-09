# CMakeList.txt : CMake project for CMakeAgents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (
	CommandProcessorLib STATIC
	"Console.cpp" 
	"Console.h"
	"CommandProcessor.cpp" 
	"CommandProcessor.h"
	"TerminalConsole.h"
	"TerminalConsole.cpp"
	"Win32Console.h"
	"Win32Console.cpp" )
