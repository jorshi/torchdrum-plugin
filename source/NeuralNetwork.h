/**
 * NeuralNetowrk.h
 * A NN class for mapping to synthesizer parameters
*/

#pragma once

#include <juce_core/juce_core.h>
#include <torch/script.h>

class NeuralNetwork
{
public:
    NeuralNetwork() = default;
    ~NeuralNetwork() = default;

    void loadModel(const std::string& path);
    void process(const std::vector<double>& input, std::vector<double>& output);

    //const std::unique_ptr<torch::jit::script::Module>& getModel() { return model; }

private:
    void _loadModel(const std::string& path);

    torch::jit::script::Module model;
    std::atomic<bool> modelLoaded = false;

    std::vector<torch::jit::IValue> inputs;

    // Lock for when we are loading the model
    juce::ReadWriteLock modelLock;
};
