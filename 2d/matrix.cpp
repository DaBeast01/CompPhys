#include <vector>
#include <iostream>
#include "Eigen/Dense"
#include <fstream>
#include <cmath>
#include <map>
#include "femfunctions.hpp"
#include <algorithm>

using namespace std;
using namespace Eigen;

mesh pointgen(int n);
vector<float> functcalc(mesh points);
basis sparseMat();
vector<int> basisCompare(int a, int b, basisMap info);

int main() {
    mesh points = pointgen(N);
    vector<float> fcmat = functcalc(points);
    basisMap basisInfo = basisHash();
    vector<int> matching;
    float value;
    MatrixXf kmat = MatrixXf::Zero(B, B);
    VectorXf umat = VectorXf::Zero(B);
    VectorXf fmat = Eigen::Map<VectorXf>(fcmat.data(), fcmat.size());


    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
            value = 0;
            matching = basisCompare(i, j, basisInfo);
            for (int k : matching) {
                value += (A*((basisInfo[i][k]['x'] * basisInfo[j][k]['x']) + (basisInfo[i][k]['y'] * basisInfo[j][k]['y'])));
            }
            kmat(i, j) = value;
        }
    }
    umat = kmat.lu().solve(fmat);
    for (float x : umat) {
        cout << x << endl;
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

vector<int> basisCompare(int a, int b, basisMap info) {
    vector<int> basis1, basis2, matching;

    // const b/c not editing (faster) and auto& b/c weird data type
    // Putting all the basis numbers from the first basis in a vector
    for (const auto& [key, _] : info[a]) {
        basis1.push_back(key);
    }

    for (const auto& [key, _] : info[b]) {
        basis2.push_back(key);
    }

    // sort keys for algorithm
    sort(basis1.begin(), basis1.end());
    sort(basis2.begin(), basis2.end());

    int i = 0, j = 0;
    while(i < basis1.size() && j < basis2.size()) {
        if (basis1[i] < basis2[j]) {
            i++;
        }
        else if (basis2[j] < basis1[i]) {
            j++;
        }
        else {
            matching.push_back(basis1[i]);
            i++;
            j++;
        }
    }
    return matching;
}