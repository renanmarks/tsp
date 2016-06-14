#!/bin/sh

cd ..
mkdir tsp-build-release
cd tsp-build-release
cmake ../tsp -DCMAKE_BUILD_TYPE=Release
