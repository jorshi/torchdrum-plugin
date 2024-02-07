/**
 * NeuralNetowrk.h
 * A NN class for mapping to synthesizer parameters
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_core/juce_core.h>
#include <torch/script.h>

#include <vector>


class NeuralNetwork
{
public:
    NeuralNetwork() = default;
    ~NeuralNetwork() = default;

    void loadModel(const std::string& path);
    void process(const std::vector<double>& input, std::vector<double>& output);
    void getCurrentPatch(std::vector<juce::RangedAudioParameter*> parameters);

    void setInOutFeatures(int in, int out)
    {
        inputFeatures = in;
        outputFeatures = out;
    }

    //const std::unique_ptr<torch::jit::script::Module>& getModel() { return model; }

private:
    void _loadModel(const std::string& path);
    void _testModel();

    torch::jit::script::Module model;
    std::atomic<bool> modelLoaded = false;

    int inputFeatures = 0;
    int outputFeatures = 0;
    std::vector<torch::jit::IValue> inputs;

    std::vector<float> currentPatch;

    // Lock for when we are loading the model
    juce::ReadWriteLock modelLock;
};
