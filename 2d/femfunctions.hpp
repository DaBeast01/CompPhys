#pragma once
#include "config.hpp"
#include <vector>
#include <iostream>
#include <NumCpp.hpp>
#include <fstream>
#include <cmath>
#include <array>
#include <map>

using namespace std;

using basis = array<array<int, B>, B>;
using mesh = vector<tuple<float, float>>;

basis sparseMat();
map<map<int, float>> basisHash(int h);
