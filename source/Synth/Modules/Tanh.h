/**
 * Tanh.h
 * A Tanh waveshaper with input gain control
*/

#pragma once

#include <cmath>

class Tanh
{
public:
    Tanh() : gain(1.0f) {}
    ~Tanh() = default;

    float process(float input)
    {
        return tanh(input * gain);
    }

    void setGainDecibels(float newValue)
    {
        gain = pow(10.0f, newValue / 20.0f);
    }

private:
    float gain;
};
