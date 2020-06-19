#include "vector.hpp"

double operator*(const Vector &u, const Vector &v)
{
	double result(0);
	size_t size(u.size());
	for (size_t i(0); i < size; ++i)
	{
		result += u[i] * v[i];
	}
	return result;
}

Vector operator+(const Vector &u, const Vector &v)
{
	Vector result;
	size_t size(u.size());
	for (size_t i(0); i < size; ++i)
	{
		result.push_back(u[i] + v[i]);
	}
	return result;
}

Vector operator-(const Vector &u, const Vector &v)
{
	Vector result;
	size_t size(u.size());
	for (size_t i(0); i < size; ++i)
	{
		result.push_back(u[i] - v[i]);
	}
	return result;
}

void adjustWeights(Vector &u, const Vector &v, const double &learningRate)
{
	size_t size(u.size());
	for (size_t i(0); i < size; ++i)
	{
		u[i] -= v[i] * learningRate;
	}
}

Vector elementMult(const Vector &u, const Vector &v)
{
	Vector result;
	size_t size(u.size());
	for (size_t i(0); i < size; ++i)
	{
		result.push_back(u[i] * v[i]);
	}
	return result;
}
