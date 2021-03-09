# CovidAgents
A simulation engine for mapping disease transmission behaviors using a network &amp; compartment based model. 



cmake -G "Ninja"  -DCMAKE_BUILD_TYPE:STRING="RelWithDebInfo" -DCMAKE_INSTALL_PREFIX:PATH="build/" -DCMAKE_C_FLAGS:STRING="" -DCMAKE_CXX_FLAGS:STRING="-std=c++14" -DCMAKE_CXX_FLAGS_RELEASE:STRING="-O3 -DNDEBUG -std=c++14"  CMakeLists.txt;