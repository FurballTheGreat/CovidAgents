#/bin/bash

pushd .
mkdir blend2d
cd blend2d

git clone https://github.com/asmjit/asmjit
git clone https://github.com/blend2d/blend2d

mkdir blend2d/build
cd blend2d/build


cmake .. -DCMAKE_BUILD_TYPE=Release -DBLEND2D_TEST=TRUE

cmake --build

cmake --build . --config Release

popd
