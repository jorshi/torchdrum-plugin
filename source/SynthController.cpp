#include "SynthController.h"

SynthController::SynthController(SynthBase& synth) : synth(synth)
{
}

void SynthController::prepare(double sr, int samplesPerBlock)
{
    sampleRate = sr;
    juce::ignoreUnused(samplesPerBlock);

    // Initialize the circular audio buffer
    buffer.clear();
    buffer.setSize(1, ONSET_BUFFER_SIZE);

    // Prepate onset detection and state
    onsetDetection.prepare(sampleRate);
    isOnset = false;
    elapsedSamples = 0;

    // Prepare feature extraction
    featureExtraction.prepare(sampleRate, ONSET_WINDOW_SIZE, ONSET_WINDOW_SIZE / 4);
    featureBuffer.clear();
    featureBuffer.setSize(1, ONSET_WINDOW_SIZE);

    // Prepare input and output features for NN
    size_t numSynthParams = synth.getParameters().parameters.size();
    neuralInput.resize(12);
    neuralOutput.resize(numSynthParams);

    // Load the neural network model
    neuralMapper.setInOutFeatures(12, numSynthParams);

    // Update synth parameters with the current patch
    neuralMapper.getCurrentPatch(synth.getParameters().parameters);
    synth.getParameters().updateAllParameters();
}

void SynthController::process(float x)
{
    addSampleToBuffer(x);

    // If we just triggered, reset the elapsed samples
    bool detected = onsetDetection.process(x);
    if (detected && ! isOnset)
    {
        isOnset = true;
        elapsedSamples = 0;
    }

    // If we are in an onset and we've accumulated enough samples,
    // perform audio feature extraction, calculate synth parameters,
    // and trigger the synth.
    if (isOnset && elapsedSamples++ > ONSET_WINDOW_SIZE)
    {
        isOnset = false;

        // TODO: Create a featureBuffer to transfer the create number of samples to
        // from the cicular buffer and pass that to featureExtraction.process()
        copySamplesToFeatureBuffer();
        featureExtraction.process(featureBuffer, features);

        // TODO: map features to neural network input -- for now, just use random values
        for (int i = 0; i < neuralInput.size(); ++i)
            neuralInput[i] = features.rmsMean.getNormalized();

        neuralMapper.process(neuralInput, neuralOutput);

        // TODO: calculate synth parameters, and trigger synth
        synth.getParameters().updateAllParametersWithModulation(neuralOutput);
        synth.trigger();
    }
}

void SynthController::updateModel(const std::string& path)
{
    neuralMapper.loadModel(path);
    neuralMapper.getCurrentPatch(synth.getParameters().parameters);
    synth.getParameters().updateAllParameters();
}

void SynthController::addSampleToBuffer(float x)
{
    buffer.setSample(0, currentSample, x);
    currentSample = (currentSample + 1) % buffer.getNumSamples();
    jassert(currentSample < buffer.getNumSamples());
}

void SynthController::copySamplesToFeatureBuffer()
{
    int samplePtr = currentSample - ONSET_WINDOW_SIZE;
    if (samplePtr < 0)
        samplePtr += buffer.getNumSamples();

    for (int i = 0; i < ONSET_WINDOW_SIZE; ++i)
    {
        featureBuffer.setSample(0, i, buffer.getSample(0, samplePtr++));
        if (samplePtr >= buffer.getNumSamples())
            samplePtr = 0;
    }
}
