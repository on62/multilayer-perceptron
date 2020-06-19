#ifndef NETWORK
#define NETWORK

#include "weightMatrix.hpp"
#include "vector.hpp"

#include <vector>
#include <string>

class Network
{
protected:
	std::vector<WeightMatrix> weightMatrices;
	std::vector<Vector> biases;
	std::vector<Vector> activations;
	std::vector<Vector> activationsPrime;
	size_t numberOfNeuronLayers;
	double learning_rate;

public:
	Network(const std::string &file, const double &learningRate);
	const Vector &predict(const Vector &x);
	void train(const Vector &x, const Vector &y);
	void getFile(const std::string &file) const;
};

void createRandomFile(const std::string &file, const std::vector<size_t> &layerSizes, unsigned int seed = 0);

#endif
