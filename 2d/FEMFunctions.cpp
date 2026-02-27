#include "femfunctions.hpp"
#include "config.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
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
        else if (i > (2*N - 2) && i < ((N - 1) * (2 *N - 1)) && a == 0) {
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

basisMap basisHash() {
    basisMap hash;

    // Possible basis partials as I dont want to do them out everytime
    // nhs - negative h sqrt; phs - positive h sqrt; nh - negative h; ph - positive h
    float nhs = -(1/(h*sqrt(2)));
    float phs = (1/(h*sqrt(2)));
    float nh = -1/h;
    float ph = 1/h;

    for (int i = 0; i < B; i++) {

        // Which node in the row it is (index 0)
        int a = i % ((2*N)-1);
        // Which row we are in (index 0)
        int b = i / ((2*N)-1);

        // middle corners
        if (i > N - 1 && i < (N - 1)*(2*N - 1) && a > 0 && a < N - 1) {
            hash[i][(4*(N-1)*b)+(4*a)+1]['x'] = nhs;
            hash[i][(4*(N-1)*b)+(4*a)+1]['y'] = phs;

            hash[i][(4*(N-1)*b)+(4*a)+4]['x'] = nhs;
            hash[i][(4*(N-1)*b)+(4*a)+4]['y'] = phs;

            hash[i][(4*(N-1)*b)+(4*a)-2]['x'] = phs;
            hash[i][(4*(N-1)*b)+(4*a)-2]['y'] = phs;

            hash[i][(4*(N-1)*b)+(4*a)-3]['x'] = phs;
            hash[i][(4*(N-1)*b)+(4*a)-3]['y'] = phs;

            hash[i][(4*(N-1)*(b-1))+(4*a)-1]['x'] = phs;
            hash[i][(4*(N-1)*(b-1))+(4*a)-1]['y'] = nhs;

            hash[i][(4*(N-1)*(b-1))+(4*a)-2]['x'] = phs;
            hash[i][(4*(N-1)*(b-1))+(4*a)-2]['y'] = nhs;
            
            hash[i][(4*(N-1)*(b-1))+(4*a)+3]['x'] = nhs;
            hash[i][(4*(N-1)*(b-1))+(4*a)+3]['y'] = nhs;            

            hash[i][(4*(N-1)*(b-1))+(4*a)+4]['x'] = nhs;
            hash[i][(4*(N-1)*(b-1))+(4*a)+4]['y'] = nhs;            
        }

        // middle corners
        else if (i > N - 1 && i < (N-1)*(2*N - 1) && a > N - 1 && a < 2*N - 1) {
            hash[i][(4*(N-1)*(b-1))+(4*(a-N))+1]['x'] = 0;
            hash[i][(4*(N-1)*(b-1))+(4*(a-N))+1]['y'] = nh;

            hash[i][(4*(N-1)*(b-1))+(4*(a-N))+2]['x'] = nh;
            hash[i][(4*(N-1)*(b-1))+(4*(a-N))+2]['y'] = 0;

            hash[i][(4*(N-1)*(b-1))+(4*(a-N))+3]['x'] = 0;
            hash[i][(4*(N-1)*(b-1))+(4*(a-N))+3]['y'] = ph;

            hash[i][(4*(N-1)*(b-1))+(4*(a-N))+4]['x'] = ph;
            hash[i][(4*(N-1)*(b-1))+(4*(a-N))+4]['y'] = 0;
        }

        // top edge
        else if (i > 0 && i < N - 1) {
            hash[i][4*i-3]['x'] = phs;
            hash[i][4*i-3]['y'] = phs;

            hash[i][4*i-2]['x'] = phs;
            hash[i][4*i-2]['y'] = phs;

            hash[i][4*i+1]['x'] = nhs;
            hash[i][4*i+1]['y'] = phs;

            hash[i][4*i+4]['x'] = nhs;
            hash[i][4*i+4]['y'] = phs;
        }

        // left edge
        else if (i > (2*N - 2) && i < ((N - 1) * (2 *N - 1)) && a == 0) {
            hash[i][4*(N-1)*(b-1)+3]['x'] = nhs;
            hash[i][4*(N-1)*(b-1)+3]['y'] = nhs;

            hash[i][4*(N-1)*(b-1)+4]['x'] = nhs;
            hash[i][4*(N-1)*(b-1)+4]['y'] = nhs;

            hash[i][(4*(N-1)*b)+1]['x'] = nhs;
            hash[i][(4*(N-1)*b)+1]['y'] = phs;
            
            hash[i][(4*(N-1)*b)+4]['x'] = nhs;
            hash[i][(4*(N-1)*b)+4]['y'] = phs;
        }

        // right edge
        else if (i > (2*N - 1) && i < B - 1 && a == N - 1) {
            hash[i][(4*(N-1)*(b+1))-2]['x'] = phs;
            hash[i][(4*(N-1)*(b+1))-2]['y'] = phs;

            hash[i][(4*(N-1)*(b+1))-3]['x'] = phs;
            hash[i][(4*(N-1)*(b+1))-3]['y'] = phs;

            hash[i][(4*(N-1)*(b))-1]['x'] = phs;
            hash[i][(4*(N-1)*(b))-1]['y'] = nhs;

            hash[i][(4*(N-1)*(b))-2]['x'] = phs;
            hash[i][(4*(N-1)*(b))-2]['y'] = nhs;
        }

        // bottom edge
        else if (i > (N - 1) * (2*N - 1) && i < 2*N*(N - 1)) {
            hash[i][(4*(N-1)*(N-2))+(4*a)-1]['x'] = phs;
            hash[i][(4*(N-1)*(N-2))+(4*a)-1]['y'] = nhs;

            hash[i][(4*(N-1)*(N-2))+(4*a)-2]['x'] = phs;
            hash[i][(4*(N-1)*(N-2))+(4*a)-2]['y'] = nhs;

            hash[i][(4*(N-1)*(N-2))+(4*a)+3]['x'] = nhs;
            hash[i][(4*(N-1)*(N-2))+(4*a)+3]['y'] = nhs;

            hash[i][(4*(N-1)*(N-2))+(4*a)+4]['x'] = nhs;
            hash[i][(4*(N-1)*(N-2))+(4*a)+4]['y'] = nhs;
        }

        // top left
        else if (i == 0) {
            hash[i][1]['x'] = nhs;
            hash[i][1]['y'] = phs;

            hash[i][4]['x'] = nhs;
            hash[i][4]['y'] = phs;
        }

        // top right
        else if (i == N - 1) {
            hash[i][(4*(N-1))-2]['x'] = phs;
            hash[i][(4*(N-1))-2]['y'] = phs;

            hash[i][(4*(N-1))-3]['x'] = phs;
            hash[i][(4*(N-1))-3]['y'] = phs;
        }

        // bottom left
        else if (i == (N - 1)*(2*N - 1)) {
            hash[i][(4*(N-1)*(N-2))+3]['x'] = nhs;
            hash[i][(4*(N-1)*(N-2))+3]['y'] = nhs;

            hash[i][(4*(N-1)*(N-2))+4]['x'] = nhs;
            hash[i][(4*(N-1)*(N-2))+4]['y'] = nhs;
        }

        // bottom right
        else if (i == B - 1) {
            hash[i][(4*(N-1)*(N-1))-1]['x'] = phs;
            hash[i][(4*(N-1)*(N-1))-1]['y'] = nhs;

            hash[i][(4*(N-1)*(N-1))-2]['x'] = phs;
            hash[i][(4*(N-1)*(N-1))-2]['y'] = nhs;
        }
    }
    return hash;
}
