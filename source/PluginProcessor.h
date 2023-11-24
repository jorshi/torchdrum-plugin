#pragma once

#include "OnsetDetection.h"
#include "Parameters.h"

class TorchDrumProcessor : public PluginHelpers::ProcessorBase
{
public:
    TorchDrumProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    juce::AudioProcessorEditor* createEditor() override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:
    Parameters parameters;
    OnsetDetection onsetDetection;
};
