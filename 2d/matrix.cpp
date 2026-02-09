#include <iostream>
#include <cmath>
#include "Eigen/Dense"
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;
using namespace Eigen;

// ONLY WORKS FOR Ns THAT ARE MULTIPLES OF 2 GREATER THAN 4
const int N = 12;

MatrixXf integration(VectorXf basis);
VectorXf base(int n);

int main() {
    VectorXf basis(N) = base(N);
    MatrixXf kmat(N, N) = integration(basis);
}

MatrixXf integration(VectorXf basis) {

    return;
}

VectorXf base(int n) {
    
    return;
}