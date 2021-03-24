# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("CovidAgents")


if (MSVC)
    include_directories ("packages/boost.1.72.0.0/lib/native/include")
    include_directories ("../blend2d/blend2d/src")
    include_directories ("../geographiclib-code/include")
    include_directories ("packages/libpng-v142.1.6.37.2/build/native/include")

    include_directories(${WinSDK} ${)
    link_directories ("packages/boost_date_time-vc142.1.72.0.0/lib/native")
    link_directories ("packages/libpng-v142.1.6.37.2/build/native/lib/x64/v142/Debug")
    link_directories ("../blend2d/blend2d/build_vs2019_x64/Debug")
    link_directories ("../geographiclib-code/windows/Debug64")
endif (MSVC)

if (UNIX)
    set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
    set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
    set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
    set(Boost_USE_MULTITHREADED      ON)
    set(Boost_USE_STATIC_RUNTIME    OFF)
    find_package(PNG REQUIRED)
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)
    find_package(GeographicLib REQUIRED)
    find_package(Python3 REQUIRED)
    find_package(Boost 1.66.0 REQUIRED COMPONENTS date_time filesystem python3)
    
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
    libavfilter
    libavformat
    libavcodec
    libswresample
    libswscale
    libavutil
)

    include_directories(${Boost_INCLUDE_DIRS} ${GeographicLib_INCLUDE_DIRS} ${FFMPEG_INCLUDE_DIRS} ${Python3_INCLUDE_DIRS}) 
    include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/blend2d/blend2d/src")
    link_directories (${Boost_LIBRARY_DIRS} ${GeographicLib_LIBRARY_DIRS} ${PNG_LIBRARY_DIRS} ${Python3_LIBRARY_DIRS} "blend2d/blend2d/build")
endif (UNIX)

include_directories ("Common")
include_directories ("SharedLib")
include_directories ("PopulationSimulationLib")
include_directories ("CommandProcessorLib")
include_directories ("SimulationsLib")
include_directories ("VisualisationLib")

add_subdirectory ("CommandProcessorLib")
add_subdirectory ("SharedLib")
add_subdirectory ("PopulationSimulationLib")
add_subdirectory ("SimulationsLib")
add_subdirectory ("VisualisationLib")
add_subdirectory ("CovAgentSim")
