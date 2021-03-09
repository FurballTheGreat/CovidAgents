#!/bin/bash
cmake -G "Ninja"  -DCMAKE_BUILD_TYPE:STRING="RelWithDebInfo" -DCMAKE_INSTALL_PREFIX:PATH="./build/"  -DCMAKE_CXX_FLAGS_RELEASE:STRING="-O3 -DNDEBUG -std=c++14"  CMakeLists.txt;
cmake --build .