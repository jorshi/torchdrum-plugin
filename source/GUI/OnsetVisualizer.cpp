#include "OnsetVisualizer.h"
#include "TorchDrumStyle.h"
#include <algorithm>

OnsetVisualizer::OnsetVisualizer(TorchDrumProcessor& p) : drumProcessor(p)
{
    drawableSignal.resize(drawSeconds * drawResoluationHz);
    std::fill(drawableSignal.begin(), drawableSignal.end(), 0.0f);

    startTimerHz(30);
}

void OnsetVisualizer::paint(juce::Graphics& g)
{
    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 1);
    g.fillPath(onsetPath);
}

void OnsetVisualizer::resized() {}

void OnsetVisualizer::updateOnsetPath()
{
    // Create a new path
    juce::Path p;
    p.startNewSubPath(0, getHeight());

    // Draw the onset signal
    // We want to start the drawing from the write index and wrap around
    int start = writeIndex;
    for (int i = 0; i < drawableSignal.size(); ++i)
    {
        float x = i * getWidth() / drawableSignal.size();
        float y = drawableSignal[start];
        start = (start + 1) % drawableSignal.size();

        y = getHeight() - y * getHeight();
        p.lineTo(x, y);
    }
    p.lineTo(getWidth(), getHeight());
    p.closeSubPath();

    onsetPath = p;
}

void OnsetVisualizer::timerCallback()
{
    // If the onset signal is ready, update the visualizer
    auto& onsetFIFO = drumProcessor.getWaveformFIFO();
    if (! onsetFIFO.isBufferReady())
        return;

    const std::vector<float>& onsetSignal = onsetFIFO.getReadBuffer();
    const int rate = (int) drumProcessor.getSampleRate() / drawResoluationHz;

    // Push new samples onto the drawing buffer
    for (size_t i = 0; i < onsetSignal.size(); i += (size_t) rate)
    {
        if (writeIndex >= drawableSignal.size())
            writeIndex = 0;

        float value = std::max(std::min(onsetSignal[i], 40.0f), 0.0f) / 40.0f;
        drawableSignal[writeIndex++] = value;
    }

    // Update the onset path
    onsetFIFO.markBufferRead();
    updateOnsetPath();
    repaint();
}
