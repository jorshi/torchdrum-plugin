/**
 * SinusoidalOscillator.h
 * A sinusoidal oscillator with frequency modulation
*/

#pragma once

class SinusoidalOscillator
{
public:
    // Constructor
    SinusoidalOscillator();

    void prepare(double sr);
    float process();

    void setFrequencyHz(float newValue);
    void setModAmount(float newValue);

    // Destructor
    ~SinusoidalOscillator() {}

private:
    double sampleRate;
    float frequency;
    float modAmount;
    double phase;
    float phaseIncr;
};
