#!/bin/sh
docker build -t libgit2_builder libgit2_builder
docker run --name libgit2_container libgit2_builder
id=$(docker ps -a -q -f name=libgit2_container)
docker cp $id:/var/tmp/lib.tar.gz .
tar -xzf lib.tar.gz --strip-components=1
rm lib.tar.gz
