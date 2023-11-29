/**
 * NeuralNetowrkMock.h
 * A mock NN class to help with unit testing with python
 * LibTorch doesn't work with the the Python Unit Testing
*/

#pragma once

#include <juce_core/juce_core.h>

class NeuralNetwork
{
public:
    NeuralNetwork() = default;
    ~NeuralNetwork() = default;

    void loadModel(const std::string& path);
    void process(const std::vector<double>& input, std::vector<double>& output);

private:
    void _loadModel(const std::string& path);
    std::atomic<bool> modelLoaded = false;
};
