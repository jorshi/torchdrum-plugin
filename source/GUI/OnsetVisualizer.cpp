#include "OnsetVisualizer.h"

OnsetVisualizer::OnsetVisualizer(TorchDrumProcessor& p) : drumProcessor(p)
{
    startTimerHz(30);
}

void OnsetVisualizer::paint(juce::Graphics& g) {}

void OnsetVisualizer::resized() {}

void OnsetVisualizer::timerCallback()
{
    auto& waveformFIFO = drumProcessor.getWaveformFIFO();
}
