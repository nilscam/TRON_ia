#!/bin/bash

mkdir build
cd build
cmake ..
make
cp toto ..
cd ..
rm -rf build
