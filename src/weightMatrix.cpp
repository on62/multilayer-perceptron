#include "weightMatrix.hpp"

Vector operator*(const WeightMatrix &m, const Vector &v)
{
	Vector result;
	for (const Vector &rowVector : m)
	{
		result.push_back(rowVector * v);
	}
	return result;
}

Vector transposeMult(const WeightMatrix &m, const Vector &v)
{
	size_t mSize(m.size());
	size_t nSize(m.front().size());
	Vector result(nSize);
	for (size_t j(0); j < nSize; ++j)
	{
		for (size_t i(0); i < mSize; ++i)
		{
			result[j] = m[i][j] * v[i];
		}
	}
	return result;
}

void adjustWeights(WeightMatrix &m, const Vector &delta, const Vector &activation, const double &learningRate)
{
	size_t mSize(delta.size());
	size_t nSize(activation.size());
	for (size_t i(0); i < mSize; ++i)
	{
		for (size_t j(0); j < nSize; ++j)
		{
			m[i][j] -= delta[i] * activation[j] * learningRate;
		}
	}
}
