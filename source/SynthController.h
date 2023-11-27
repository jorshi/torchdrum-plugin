/**
 * Class that takes as input an audio stream and extracts onset features, which
 * are then used to control a drum synthesizer
*/
#pragma once

#include "OnsetDetection.h"
#include <juce_audio_utils/juce_audio_utils.h>

// Buffer size for the circular audio buffer
const int ONSET_BUFFER_SIZE = 2048;

class SynthController
{
public:
    SynthController();
    ~SynthController() {}

    // Prepare the contoller with sample rate and block size
    void prepare(double sr, int samplesPerBlock);

    // Process the next audio sample
    void process(float x);

    // Get the audio buffer
    const juce::AudioBuffer<float>& getBuffer() const { return buffer; }

private:
    double sampleRate;

    OnsetDetection onsetDetection;

    // Circular audio buffer to store incoming audio
    juce::AudioBuffer<float> buffer;
    int currentSample = 0;
};
