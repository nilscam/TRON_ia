#!/bin/bash

rm -rf build
mkdir build
cd build
rm -rf ma_super_ia.cpp

declare -a arr=(
"Cell.h"
"Cell.cpp"
"Map.h"
"Map.cpp"
"Snake.h"
"Snake.cpp"

"main.cpp"
)

for filename in "${arr[@]}"
do
    filename="../$filename"
    echo $filename
    cat $filename >> ma_super_ia.cpp
done

sed -i '/#include ".*"/d' ma_super_ia.cpp
