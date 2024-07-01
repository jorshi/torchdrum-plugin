#include "NeuralNetworkMock.h"

bool NeuralNetwork::loadModel(const std::string& path)
{
    modelLoaded = true;
    return modelLoaded;
}

void NeuralNetwork::process(const std::vector<double>& input, std::vector<double>& output)
{
    std::fill(output.begin(), output.end(), 0.0);
}

void NeuralNetwork::_loadModel(const std::string& path)
{
}
