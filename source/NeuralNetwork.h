/**
 * NeuralNetowrk.h
 * A NN class for mapping to synthesizer parameters
*/

#pragma once

#include <torch/torch.h>

class NeuralNetwork
{
public:
    NeuralNetwork() = default;
    ~NeuralNetwork() = default;

    void loadModel(const std::string& path);
    void process(const std::vector<double>& input, std::vector<double>& output);

private:
};
