#!/usr/bin/env sh

g++ -o main -I../ext -I/home/nick/miniforge3/envs/CompPhys/bin/  -std=c++17 -O3 -fopenmp *.cpp -g