#! /bin/bash
set -e 

cmake -B build
cmake --build build -j 12
