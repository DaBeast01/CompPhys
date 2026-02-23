#!/usr/bin/env sh

g++ -o matrix -I"$CONDA_PREFIX/include" -std=c++17 *.cpp