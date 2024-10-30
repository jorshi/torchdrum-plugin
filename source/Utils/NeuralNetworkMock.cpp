#include "NeuralNetworkMock.h"

bool NeuralNetwork::loadModel(const std::string& path)
{
    (void) path; // Unused in mock
    modelLoaded = true;
    return modelLoaded;
}

void NeuralNetwork::process(const std::vector<double>& input,
                            std::vector<double>& output)
{
    (void) input; // Unused in mock
    std::fill(output.begin(), output.end(), 0.0);
}

void NeuralNetwork::_loadModel(const std::string& path)
{
    (void) path; // Unused in mock
}
