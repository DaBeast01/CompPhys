#pragma once
#include "config.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <map>

using namespace std;

using basis = array<array<int, B>, B>;
using mesh = vector<tuple<float, float>>;
using basisMap = map<int, map<int, map<char, float>>>;

basis sparseMat();
basisMap basisHash();
