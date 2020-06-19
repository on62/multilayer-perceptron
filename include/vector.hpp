#ifndef VECTOR
#define VECTOR

#include <vector>

typedef std::vector<double> Vector;

double operator*(const Vector& u, const Vector& v);
Vector operator+(const Vector& u, const Vector& v);
Vector operator-(const Vector& u, const Vector& v);
void adjustWeights(Vector& u, const Vector& v, const double& learningRate);
Vector elementMult(const Vector& u, const Vector& v);

#endif
