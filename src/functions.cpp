#include "../include/functions.hpp"

#include <cmath>

double sigmoid(const double& x) {
    return 1.0 / (1.0 + exp(-x));
}

Vector sigmoid(const Vector& v) {
    Vector result;
    for (const double& value : v) {
        result.push_back(sigmoid(value));
    }
    return result;
}

Vector primeOfSigmoid(const Vector& v) {
    Vector one(v.size(), 1);
    return elementMult(v, one - v);
}
