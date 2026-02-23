#include "femfunctions.hpp"
#include "config.hpp"
#include <vector>
#include <iostream>
#include <NumCpp.hpp>
#include <fstream>
#include <cmath>
#include <array>
#include <map>

using namespace std;

basis sparseMat() {
    basis sparse;
    sparse.fill({0});
    for (int i = 0; i < B; i++) {
        int a = i % (2*N-1);
        sparse[i][i] = 1;
        // middle corners
        if (i > N - 1 && i < (N - 1)*(2*N - 1) && a > 0 && a < N - 1) {
            sparse[i][i - N] = 1;
            sparse[i][i - N - 1] = 1;
            sparse[i][i + (2*N - 1)] = 1;
            sparse[i][i - (2*N - 1)] = 1;
            sparse[i][i + N - 1] = 1;
            sparse[i][i + N] = 1;
            sparse[i][i + 1] = 1;
            sparse[i][i - 1] = 1;
        }
        // middle centers
        else if (i > N - 1 && i < (N-1)*(2*N - 1) && a > N - 1 && a < 2*N - 1) {
            sparse[i][i - N] = 1;
            sparse[i][i + N] = 1;
            sparse[i][i + (N - 1)] = 1;
            sparse[i][i - (N - 1)] = 1;
        }
        // top edge
        else if (i > 0 && i < N - 1) {
            sparse[i][i - 1] = 1;
            sparse[i][i + 1] = 1;
            sparse[i][i + N] = 1;
            sparse[i][i + N - 1] = 1;
            sparse[i][i + (2*N - 1)] = 1;
        }
        // left edge
        else if (i > (2*N - 1) && i < ((N - 1) * (2 *N - 1)) && a == 0) {
            sparse[i][i + (2*N - 1)] = 1;
            sparse[i][i - (2*N - 1)] = 1;
            sparse[i][i + 1] = 1;
            sparse[i][i - N + 1] = 1;
            sparse[i][i + N] = 1;
        }
        // right edge
        else if (i > (2*N - 1) && i < B - 1 && a == N - 1) {
            sparse[i][i + (2*N - 1)] = 1;
            sparse[i][i - (2*N - 1)] = 1;
            sparse[i][i - 1] = 1;
            sparse[i][i - N] = 1;
            sparse[i][i + N - 1] = 1;
        }
        // bottom edge
        else if (i > (N - 1) * (2*N - 1) && i < 2*N*(N - 1)) {
            sparse[i][i - 1] = 1;
            sparse[i][i + 1] = 1;
            sparse[i][i - (N - 1)] = 1;
            sparse[i][i - N] = 1;
            sparse[i][i - (2*N - 1)] = 1;
        }
        // top left
        else if (i == 0) {
            sparse[i][i + 1] = 1;
            sparse[i][i + N] = 1;
            sparse[i][2*N - 1] = 1;
        }
        // top right
        else if (i == N - 1) {
            sparse[i][i - 1] = 1;
            sparse[i][i + N - 1] = 1;
            sparse[i][i + (2*N - 1)] = 1;
        }
        // bottom left
        else if (i == (N - 1)*(2*N - 1)) {
            sparse[i][i - (N - 1)] = 1;
            sparse[i][i - (2*N - 1)] = 1;
            sparse[i][i + 1] = 1;
        }
        // bottom right
        else if (i == B - 1) {
            sparse[i][i - 1] = 1;
            sparse[i][i - N] = 1;
            sparse[i][i - (2*N - 1)] = 1;
        }
    }
    return sparse;
}

map<map<int, float>> basisHash() {
    map<map<int, float>> a;
    
}
