# yaga

yaga (Yet Another Git App) aims to be an open source, performant and cross-platform git client with a user-friendly graphical interface.

## Building

### Prerequisites

So far the project has been built and tested on Linux systems only. Other prerequisites are as follows.

  * CMake >= 3.5
  * Qt >= 5.6

### Build steps

  1. Initialize submodules (or clone using the `--recursive` flag: `git clone --recursive`).

    git submodule init
    git submodule update

  2. Create a directory named build and run CMake.

    mkdir build
    cd build
    cmake ..

  3. Build the project.

    cmake --build .
