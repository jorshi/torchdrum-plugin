/**
 * OnsetDetection
 * Based on method implemented in the FluComa library:
 * https://github.com/flucoma/flucoma-core
 *
 * Uses a slow and fast envelope follower and calculates the different between
 * them to generate an onset detection function.
 */
#pragma once

#include "Biquad.h"
#include "EnvelopeFollower.h"
#include "WaveformFIFO.h"

class OnsetDetection
{
public:
    // Constructor
    OnsetDetection();

    void prepare(double sr);
    bool process(float x);
    float onsetSignal(float x);

    // Parameter Updates
    void updateParameters(float onThresh, float offThresh, int wait);

    // Set the waveform FIFO buffer
    void setWaveformFIFO(WaveformFIFO* wf) { waveformFIFO = wf; }

    // Destructor
    ~OnsetDetection() {}

private:
    double sampleRate;

    EnvelopeFollower fastEnv;
    EnvelopeFollower slowEnv;
    Biquad hipass;

    bool justTriggered;
    int debounce;
    float prevValue;

    float onThreshold;
    float offThreshold;
    int waitSamples;
    float minAmplitude;

    WaveformFIFO* waveformFIFO;
};
