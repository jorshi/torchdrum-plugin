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

    bool loadModel(const std::string& path);
    void process(const std::vector<double>& input, std::vector<double>& output);
    void getCurrentPatch(std::vector<juce::RangedAudioParameter*> parameters)
    {
        (void) parameters; // Unused in mock
    }

    void setInOutFeatures(int in, int out)
    {
        inputFeatures = in;
        outputFeatures = out;
    }

private:
    void _loadModel(const std::string& path);
    std::atomic<bool> modelLoaded = false;
    int inputFeatures = 0;
    int outputFeatures = 0;
};
