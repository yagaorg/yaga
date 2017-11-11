# yaga

yaga (Yet Another Git App) aims to be an open source, performant and cross-platform git client with a user-friendly graphical interface.

## Building

### Prerequisites

  * Docker (optional, used for building `libgit2`)

### Build steps

  1. Optionally build `libgit2` ( https://wwww.github.com/libgit2/libgit2 ). If you would like to avoid polluting your system with the libraries necessary to build `libgit2`, you can use the attached shell script that builds it in a Docker container. Otherwise you can run the commands from the `Dockerfile` manually.

    cd lib/libgit2
    ./build.sh
