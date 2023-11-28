/**
 * Gain.h
 * Gain module with decibel control parameter
*/

#pragma once

#include <cmath>

class Gain
{
public:
    Gain() : gain(1.0f) {}
    ~Gain() = default;

    float process(float input)
    {
        return input * gain;
    }

    void setGainDecibels(float newValue)
    {
        gain = pow(10.0f, newValue / 20.0f);
    }

private:
    float gain;
};
