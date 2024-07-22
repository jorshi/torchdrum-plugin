#include "OnsetVisualizer.h"
#include "TorchDrumStyle.h"

OnsetVisualizer::OnsetVisualizer(TorchDrumProcessor& p) : drumProcessor(p)
{
    startTimerHz(30);
}

void OnsetVisualizer::paint(juce::Graphics& g)
{
    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 1);
}

void OnsetVisualizer::resized() {}

void OnsetVisualizer::timerCallback()
{
    auto& waveformFIFO = drumProcessor.getWaveformFIFO();
}
