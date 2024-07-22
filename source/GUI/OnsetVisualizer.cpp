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

    g.fillPath(onsetPath);
}

void OnsetVisualizer::resized() {}

void OnsetVisualizer::timerCallback()
{
    // If the onset signal is ready, update the visualizer
    auto& onsetFIFO = drumProcessor.getWaveformFIFO();
    if (! onsetFIFO.isBufferReady())
        return;

    const std::vector<float>& onsetSignal = onsetFIFO.getReadBuffer();
    const int hop = onsetSignal.size() / 10;

    // Create a new path
    juce::Path p;
    p.startNewSubPath(0, getHeight());

    // Normalize the onset signal (min-max normalization)
    auto minmax = std::minmax_element(onsetSignal.begin(), onsetSignal.end());
    float norm = *minmax.second - *minmax.first;

    // Draw the onset signal
    for (int i = 0; i < onsetSignal.size(); i += hop)
    {
        float x = i * getWidth() / onsetSignal.size();
        float y = (onsetSignal[i] - *minmax.first);
        if (norm > 0.0001f)
            y /= norm;

        y = getHeight() - y * getHeight();
        p.lineTo(x, y);
    }
    p.lineTo(getWidth(), getHeight());
    p.closeSubPath();

    onsetPath = p;
    repaint();

    onsetFIFO.markBufferRead();
}
