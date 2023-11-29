#include "NeuralNetwork.h"

void NeuralNetwork::loadModel(const std::string& path)
{
    // Obtain the write lock - this will block until the lock is acquired
    const juce::ScopedWriteLock writeLock(modelLock);

    // Load the model
    modelLoaded = false;
    _loadModel(path);

    // Create the input tensor
    inputs.push_back(torch::ones({ 1, 3 }));
}

void NeuralNetwork::process(const std::vector<double>& input, std::vector<double>& output)
{
    const juce::ScopedTryReadLock readLock(modelLock);
    if (! modelLoaded || ! readLock.isLocked())
    {
        juce::Logger::outputDebugString("Could not acquire read lock");
        std::fill(output.begin(), output.end(), 0.0);
        return;
    }

    // Run prediction with model
    auto& inputTensor = inputs[0].toTensor();
    for (int i = 0; i < input.size(); ++i)
    {
        inputTensor[0][i] = input[i];
    }

    auto outputTensor = model.forward(inputs).toTensor();
    jassert(outputTensor.sizes().size() == 2);
    jassert(outputTensor.sizes()[1] == output.size());

    for (int i = 0; i < output.size(); ++i)
    {
        output[i] = outputTensor[0][i].item<double>();
    }
}

void NeuralNetwork::_loadModel(const std::string& path)
{
    try
    {
        // Deserialize the ScriptModule from a file using torch::jit::load().
        model = torch::jit::load(path);
        modelLoaded = true;
    }
    catch (const c10::Error& e)
    {
        juce::Logger::outputDebugString("Error loading the model");
    }
}
