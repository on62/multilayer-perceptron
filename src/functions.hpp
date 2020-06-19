#ifndef NETWORK_FUNCTIONS
#define NETWORK_FUNCTIONS

#include "vector.hpp"

double sigmoid(const double &x);
Vector sigmoid(const Vector &v);
Vector primeOfSigmoid(const Vector &v);

#endif
