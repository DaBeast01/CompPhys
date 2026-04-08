#include <cmath>
#include <iostream>
#include "Eigen/Dense"
#include <cstdlib>
#include <fstream>

using namespace std;
using namespace Eigen;

const int N = 100;
int i;
int j;
float h = 1.0f / N;

MatrixXf kmat = MatrixXf::Zero(N, N);
VectorXf fmat = VectorXf::Zero(N);
VectorXf umat = VectorXf::Zero(N);

int main() {
    for (int i = 0; i < N; i++) {
        kmat(i, i) = 2/h;
        for (int j = 0; j < N; j++) {
            if (i == j + 1 || i == j - 1) {
                kmat(i, j) = -1/h;
                kmat(j, i) = -1/h;
            }
        }
    }

    fmat(0) = 1.0f;
    // fmat(N-1) = 1.0f;

    umat = kmat.lu().solve(fmat);

    for (int i = 0; i < N; i++) {
        printf("%f ", umat(i));
        printf("%f\n", fmat(i));
    }
    printf("\n");
    return 0;
}