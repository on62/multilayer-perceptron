#ifndef MATRIX
#define MATRIX

#include "vector.hpp"
#include <vector>

typedef std::vector<Vector> WeightMatrix;

Vector operator*(const WeightMatrix &m, const Vector &v);
Vector transposeMult(const WeightMatrix &m, const Vector &v);
void adjustWeights(WeightMatrix &m, const Vector &delta, const Vector &activation, const double &learningRate);

#endif
