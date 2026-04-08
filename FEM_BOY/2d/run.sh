#!/usr/bin/env sh

g++ -o main -I../ext -I/home/nick/miniforge3/envs/CompPhys/bin/  -std=c++17 -O3 -fopenmp *.cpp -g
./main 
status=$?

if [ $status -eq 0 ]; then 
   python3 visual.py
fi