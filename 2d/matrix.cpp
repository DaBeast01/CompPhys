#include <vector>
#include <iostream>
#include <NumCpp.hpp>
#include <fstream>
#include <cmath>
#include <array>
#include <map>
#include "femfunctions.hpp"

using namespace std;
using namespace nc;

mesh pointgen(int n);
vector<float> functcalc(mesh points);
basis sparseMat();

int main() {
    mesh points = pointgen(N);
    vector<float> fmat = functcalc(points);
    basis kmat = sparseMat();
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
            printf("%i, ", kmat[i][j]);
        }
        printf("\n");
        //printf("%f\n", fmat[i]);
    }
    return 0;
}

mesh pointgen(int n) {
    mesh nodes;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            nodes.push_back({(float) (2*j)/(n-1) - 1, (float) (2*i)/(n-1) - 1});
        }

        for (int j = 0; j < n - 1; j++) {
            nodes.push_back({(float)(2*j + 1)/(n-1) - 1, (float) (2*i - 1)/(n-1) - 1});
        }
    }
    for (int i = 0; i < n; i++) {
        nodes.push_back({(float) (2*i)/(n-1) - 1, (float) -1});
    }
    return nodes;
}

vector<float> functcalc(mesh points) {
    vector<float> fmat;
    float x, y;
    for (int i = 0; i < B; i++) {
        x = get<0>(points[i]);
        y = get<1>(points[i]);
        //printf("(%f, %f)\n", x, y);
        //function is e^xy
        fmat.push_back(exp(x*y));
    }
    return fmat;
}