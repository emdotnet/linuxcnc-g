#!/bin/bash
set -e

rm -r build
mkdir -p build
cd build
cmake ..
make -j2
