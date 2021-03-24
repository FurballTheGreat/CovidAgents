# CMakeList.txt : CMake project for CMakeAgents, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (
	VisualisationLib STATIC
	"DayInfoPlotter.h" 
	"DayInfoPlotter.cpp"
	"DayStatsCollector.h" 
	"DayStatsCollector.cpp"
	"CSVDayStatsWriter.h" 
	"CSVDayStatsWriter.cpp"
	"DrawingCanvas.h" 
	"DrawingCanvas.cpp"
	"DrawingFont.h" 
	"DrawingFont.cpp"
	"FFMpegH264Writer.h" 
	"FFMpegH264Writer.cpp"
	"ICanvasWriter.h" 
	"MapPlotter.h" 
	"MapPlotter.cpp" 
	"PngWriter.h" 
	"PngWriter.cpp")
