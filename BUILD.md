# Build Instructions

## Quick Start

```bash
mkdir build
cd build
cmake ..
make
./bin/scicalc
```

## Prerequisites

### Linux (Ubuntu/Debian)
```bash
sudo apt-get install cmake gcc make libm
```

### macOS
```bash
brew install cmake gcc
```

### Windows
- Download CMake from https://cmake.org/download/
- Install Visual Studio with C++ tools

## Building with Different Compilers

### GCC
```bash
mkdir build && cd build
cmake -DCMAKE_C_COMPILER=gcc ..
make
```

### Clang
```bash
mkdir build && cd build
cmake -DCMAKE_C_COMPILER=clang ..
make
```

### MSVC (Windows)
```bash
mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release
```

## Release Build

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./bin/scicalc
```

## Debug Build

```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
./bin/scicalc
```

## Running Tests

```bash
cd build
ctest --output-on-failure
```

## Installation

```bash
mkdir build && cd build
cmake ..
make
sudo make install

# Now run from anywhere
scicalc
```

## Uninstallation

```bash
cd build
sudo xargs rm < install_manifest.txt
```

## Cleaning Build

```bash
rm -rf build
```
