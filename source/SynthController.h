/**
 * Class that takes as input an audio stream and extracts onset features, which
 * are then used to control a drum synthesizer
*/
#pragma once

#include "FeatureExtraction/FeatureExtraction.h"
#if TORCHDRUMLIB_BUILD
#include "Utils/NeuralNetworkMock.h"
#else
#include "NeuralNetwork.h"
#endif
#include "OnsetDetection.h"
#include "Synth/SynthBase.h"
#include <juce_audio_utils/juce_audio_utils.h>

// Buffer size for the circular audio buffer
const int ONSET_BUFFER_SIZE = 2048;
const int ONSET_WINDOW_SIZE = 256;

class SynthController
{
public:
    SynthController() = delete;
    SynthController(SynthBase& synth);
    ~SynthController() {}

    // Prepare the contoller with sample rate and block size
    void prepare(double sr, int samplesPerBlock);

    // Process the next audio sample
    void process(float x);

    // Update the neural network model
    void updateModel(const std::string& path);

    // Getters for audio buffers
    const juce::AudioBuffer<float>& getBuffer() const { return buffer; }
    const juce::AudioBuffer<float>& getFeatureBuffer() const { return featureBuffer; }

    // Indicate whether we're in the period after an detected onset but
    // before triggering the synthesizer
    bool getIsOnset() const { return isOnset; }

private:
    // Add a sample to the circular audio buffer
    void addSampleToBuffer(float x);

    double sampleRate;
    SynthBase& synth;

    OnsetDetection onsetDetection;
    bool isOnset = false;
    int elapsedSamples = 0;

    // Circular audio buffer to store incoming audio
    juce::AudioBuffer<float> buffer;
    int currentSample = 0;

    FeatureExtraction featureExtraction;
    FeatureExtractionResults featureExtractionResults;
    juce::AudioBuffer<float> featureBuffer;

    // Neural network for mapping features to synthesizer parameters
    NeuralNetwork neuralMapper;
    std::vector<double> neuralInput;
    std::vector<double> neuralOutput;
    juce::Random random;
};
