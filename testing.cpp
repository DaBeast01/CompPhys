#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

typedef vector<tuple<float, float>> mesh;
const int N = 4;
mesh pointgen(int n);
vector<float> functcalc(mesh points);

int main() {
    mesh points = pointgen(4);
    vector<float> fmat = functcalc(points);
    for (int i = 0; i < 16; i++) {
        printf("%f\n", fmat[i]);
    }
    return 0;
}

mesh pointgen(int n) {
    mesh nodes;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            nodes.push_back({(float) (2*i)/(n-1) - 1, (float) (2*j)/(n-1) - 1});
        }
    }
    return nodes;
}

vector<float> functcalc(mesh points) {
    vector<float> fmat;
    float x, y;
    for (int i = 0; i < N*N; i++) {
        x = get<0>(points[i]);
        y = get<1>(points[i]);
        //function is e^xy
        fmat.push_back(exp(x*y));
    }
    return fmat;
}
