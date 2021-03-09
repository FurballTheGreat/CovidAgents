
# CovidAgents
A simulation engine for mapping disease transmission behaviors using a network &amp; compartment based model. 

## Debian/Ubuntu build instructions

First you need to install the following packages. It is assumed you have a functional GCC/G++ environment already installed:

    apt install libpng-dev cmake libgeographic-dev libboost-date-time-dev git

There are scripts included to simplify the build process each needs to be granted execute access.

    chmod a+x ./build-blend2d
    chmod a+x ./build-full
    chmod a+x ./build
    
Next build Blend2d by running the script provided.

    ./build-blend2d.sh

Finally build the application itself.

    ./build-full

## Visual Studio

Clone the source code to the application and the Blend2d library using the following commands:

    mkdir blend2d
    cd blend2d
    git clone https://github.com/asmjit/asmjit
    git clone https://github.com/blend2d/blend2d
    cd...
    git clone https://github.com/FurballTheGreat/CovidAgents.git
   
Use the batch files provided to build the 64bit projects for Blend2d and asmjit. Build both using visual studio in  in Release & Debug x64 configurations.

Finally you can load the solution file for the application ensuring that you select either Debug or Release in x64 mode.
    
