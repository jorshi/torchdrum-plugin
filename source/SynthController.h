/**
 * Class that takes as input an audio stream and extracts onset features, which
 * are then used to control a drum synthesizer
*/
#pragma once

#include "OnsetDetection.h"
#include <juce_audio_utils/juce_audio_utils.h>

class SynthController
{
public:
    SynthController();
    ~SynthController() {}

    // Prepare the contoller with sample rate and block size
    void prepare(double sr, int samplesPerBlock);

    // Process the next audio sample
    void process(float x);

private:
    double sampleRate;

    OnsetDetection onsetDetection;
};
