#include "NeuralNetwork.h"

bool NeuralNetwork::loadModel(const std::string& path)
{
    // Obtain the write lock - this will block until the lock is acquired
    const juce::ScopedWriteLock writeLock(modelLock);

    // Load the model
    modelLoaded = false;
    _loadModel(path);
    if (modelLoaded)
    {
        _testModel();
    }

    // Return the model loaded status
    return modelLoaded;
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

void NeuralNetwork::getCurrentPatch(std::vector<juce::RangedAudioParameter*> parameters)
{
    const juce::ScopedTryReadLock readLock(modelLock);
    if (! modelLoaded || ! readLock.isLocked())
    {
        juce::Logger::outputDebugString("Couldn't get patch: model isn't loaded");
        return;
    }

    jassert(currentPatch.size() == parameters.size());
    for (int i = 0; i < parameters.size(); ++i)
    {
        parameters[i]->setValueNotifyingHost(currentPatch[i]);
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
    juce::Logger::outputDebugString("Successfully loaded model");
}

void NeuralNetwork::_testModel()
{
    try
    {
        inputs.clear();
        inputs.push_back(torch::ones({ 1, inputFeatures }));
        auto output = model.forward(inputs).toTensor();

        // Confirm the model output is the correct size
        if (output.sizes().size() != 2)
            throw std::runtime_error("output.sizes().size() != 2");

        if (output.sizes()[0] != 2)
            throw std::runtime_error("output.sizes()[0] != 2");

        if (output.sizes()[1] != outputFeatures)
            throw std::runtime_error("output.sizes()[1] != outputFeatures");

        // Update the current patch from network output
        currentPatch.clear();
        currentPatch.resize(outputFeatures);
        for (int i = 0; i < outputFeatures; ++i)
        {
            currentPatch[i] = output[1][i].item<double>();
        }
    }
    catch (const c10::Error& e)
    {
        juce::Logger::outputDebugString("Error running model" + std::string(e.what()));

        // Reset the model
        modelLoaded = false;
    }
    catch (const std::runtime_error& e)
    {
        juce::Logger::outputDebugString("Unexpected output size from model" + std::string(e.what()));

        // Reset the model
        modelLoaded = false;
    }
    juce::Logger::outputDebugString("Successfully tested model");
}
