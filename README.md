brew install cmake
brew install automake
brew install autoconf
brew install libtool

SDL:
cd ../external/SDL
mkdir "build"
cmake ..
cmake -S . -B build -DCMAKE_OSX_ARCHITECTURES="x86_64;arm64" && cmake --build build && cmake --install build
