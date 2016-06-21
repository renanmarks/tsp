#!/bin/sh

ln -s libkdtree/kdtree++/ .
cd ..
mkdir tsp-build-release
cd tsp-build-release
cmake ../tsp -DCMAKE_BUILD_TYPE=Release
make
