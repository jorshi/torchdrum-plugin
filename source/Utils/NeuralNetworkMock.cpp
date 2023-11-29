#include "NeuralNetworkMock.h"

void NeuralNetwork::loadModel(const std::string& path)
{
    modelLoaded = true;
}

void NeuralNetwork::process(const std::vector<double>& input, std::vector<double>& output)
{
    if (! modelLoaded)
    {
        juce::Logger::outputDebugString("Could not acquire read lock");
        std::fill(output.begin(), output.end(), 0.0);
        return;
    }

    for (int i = 0; i < output.size(); ++i)
    {
        output[i] = 1.0;
    }
}

void NeuralNetwork::_loadModel(const std::string& path)
{
}
