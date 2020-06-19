#include "../include/network.hpp"
#include "../include/functions.hpp"

#include <fstream>
#include <sstream>
#include <random>
#include <iomanip>
#include <vector>
#include <string>

#include <iostream>


Network::Network(const std::string& file, const double& learningRate) : learning_rate(learningRate) {

    std::ifstream ifstr;
    ifstr.open(file);

    std::string sizes;
    std::getline(ifstr, sizes);
    std::istringstream sstream(sizes);
    std::vector<size_t> layerSizes;
    size_t layerSize;
    while(sstream >> layerSize) {
        layerSizes.push_back(layerSize);
    }

    activations.push_back(Vector(layerSizes.front()));
    size_t totalNumberOfLayers(layerSizes.size());
    numberOfNeuronLayers = totalNumberOfLayers - 1;
    for (size_t l(1); l < totalNumberOfLayers; ++l) {
        size_t m(layerSizes[l]);
        size_t n(layerSizes[l-1]);

        WeightMatrix weightMatrix(m, Vector(n));
        for (Vector& rowVector : weightMatrix) {
            for (double& value : rowVector) {
                ifstr >> value;
            }
        }

        Vector bias(m);
        for (double& value : bias) {
            ifstr >> value;
        }

        weightMatrices.push_back(weightMatrix);
        biases.push_back(bias);
        activations.push_back(Vector(m));
        activationsPrime.push_back(Vector(m));
    }

    ifstr.close();
}

Network::~Network() {}

const Vector& Network::predict(const Vector& x) {
    activations.front() = x;
    for (size_t l(0); l < numberOfNeuronLayers; ++l) {
        Vector z(weightMatrices[l] * activations[l] + biases[l]);
        Vector sigmoidZ(sigmoid(z));
        activations[l+1] = sigmoidZ;
        activationsPrime[l] = primeOfSigmoid(sigmoidZ);
    }
    return activations.back();
}

void Network::train(const Vector& x, const Vector& y) {

    std::vector<Vector> deltas(numberOfNeuronLayers);
    deltas.back() = elementMult(predict(x) - y, activationsPrime.back());
    for (size_t l(numberOfNeuronLayers - 1); l > 0; --l) {
        deltas[l-1] = elementMult(transposeMult(weightMatrices[l], deltas[l]), activationsPrime[l-1]);
    }

    for (size_t l(0); l < numberOfNeuronLayers; ++l) {
        adjustWeights(weightMatrices[l], deltas[l], activations[l], learning_rate);
        adjustWeights(biases[l], deltas[l], learning_rate);
    }
}

void Network::getFile(const std::string& file) const {
    std::ofstream ofstr;
    ofstr.open(file);

    for (const Vector& activation : activations) {
        ofstr << activation.size() << ' ';
    }

    ofstr << std::setprecision(10) << std::fixed;

    for (size_t l(0); l < numberOfNeuronLayers; ++l) {
        for (const Vector& rowVector : weightMatrices[l]) {
            for (const double& value : rowVector) {
                ofstr << std::endl << value;
            }
        }
        for (const double& bias : biases[l]) {
            ofstr << std::endl << bias;
        }
    }

    ofstr.close();
}

void createRandomFile(const std::string& file, const std::vector<size_t>& layerSizes, unsigned int seed) {
    std::ofstream ofstr;
    ofstr.open(file);

    for (auto size : layerSizes) {
        ofstr << size << ' ';
    }

    std::default_random_engine engine(seed);
    int max(engine.max());

    ofstr << std::setprecision(10) << std::fixed;

    size_t numberOfLayers(layerSizes.size());
    for (size_t i(1); i < numberOfLayers; ++i) {
        size_t layerSize(layerSizes[i]);
        size_t prevLayerAndBiasSize(layerSizes[i - 1] + 1);
        for (size_t j(0); j < layerSize; ++j) {
            for (size_t k(0); k < prevLayerAndBiasSize; ++k) {
                ofstr << std::endl << (double) engine() / max * 2 - 1;
            }
        }
    }

    ofstr.close();
}
