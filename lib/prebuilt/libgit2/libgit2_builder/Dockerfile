FROM ubuntu
MAINTAINER yagaorg

# Install dependencies. Install python if tests are also needed.
RUN apt-get update
RUN apt-get install -y cmake libcurl4-openssl-dev libhttp-parser-dev libssh2-1-dev libssl-dev pkg-config zlibc
RUN apt-get install wget
# RUN apt-get install python

# Download libgit2 in a temp folder.
WORKDIR /var/tmp
RUN ["mkdir", "libgit2"]
RUN ["wget", "-O", "libgit2.tar.gz", "https://github.com/libgit2/libgit2/archive/v0.26.0.tar.gz"]
RUN ["tar", "-xzf", "libgit2.tar.gz", "--strip-components=1", "--directory", "libgit2"]
WORKDIR libgit2

# Create a build directory, then build libgit2.
CMD mkdir build
WORKDIR build
RUN ["cmake", "-DBUILD_SHARED_LIBS=OFF", "-DBUILD_CLAR=OFF", ".."]
RUN ["cmake", "--build", "."]

# Create a compressed file from the result.
WORKDIR ../..
RUN ["mkdir", "-p", "lib/include"]
RUN cp -R libgit2/include/* lib/include
RUN cp libgit2/build/libgit2.a lib
RUN ["tar", "-czf", "lib.tar.gz", "lib"]
