/**
 * NeuralNetowrk.h
 * A NN class for mapping to synthesizer parameters
*/

#pragma once

#include <torch/script.h>

class NeuralNetwork
{
public:
    NeuralNetwork() = default;
    ~NeuralNetwork() = default;

    void loadModel(const std::string& path);
    void process(const std::vector<double>& input, std::vector<double>& output);

    const std::unique_ptr<torch::jit::script::Module>& getModel() { return model; }

private:
    std::unique_ptr<torch::jit::script::Module> model;
};
