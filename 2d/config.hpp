#pragma once

// The number of nodes on the side of the square mesh (mesh is NxN)
const int N = 20;

// Total number of nodes in the mesh
const int B = (2*N - 1)*(N - 1) + N;

// Unit distance of the mesh (for the bounds from -1 to 1).
// If you change the bounds of the mesh, just put the length of the side of the square in the numerator
const float h = 2/((float)N - 1);

// Area of a triangle in the mesh
const float A = (0.5F)*(h)*(h/2.0F);
