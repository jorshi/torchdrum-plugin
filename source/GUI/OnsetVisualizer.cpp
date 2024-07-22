#include "OnsetVisualizer.h"
#include "TorchDrumStyle.h"
#include <algorithm>

OnsetVisualizer::OnsetVisualizer(TorchDrumProcessor& p) : drumProcessor(p)
{
    drawableSignal.resize(drawSeconds * drawResoluationHz);
    std::fill(drawableSignal.begin(), drawableSignal.end(), 0.0f);

    readIndex = 0;
    writeIndex = 0;
    drawIndex = 0;
    startTimerHz(timerHz);
}

void OnsetVisualizer::paint(juce::Graphics& g)
{
    g.setColour(onsetVisualizerColour2);
    g.fillPath(onsetPath);

    g.setColour(borderColour);
    g.drawRect(getLocalBounds(), 1);
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

    if (onsetFIFO.isBufferReady())
    {
        const std::vector<float>& onsetSignal = onsetFIFO.getReadBuffer();
        const int rate = (int) drumProcessor.getSampleRate() / drawResoluationHz;

        // Push new samples onto the drawing buffer
        while (readIndex < onsetSignal.size())
        {
            if (writeIndex >= drawableSignal.size())
                writeIndex = 0;

            float value =
                std::max(std::min(onsetSignal[readIndex], maxValue), minValue);
            value = juce::jmap(value, minValue, maxValue, 0.0f, 1.0f);
            drawableSignal[writeIndex++] = value;
            readIndex += rate;
        }

        jassert(readIndex >= onsetSignal.size());
        readIndex -= std::max(onsetSignal.size(), (size_t) 0);

        // Update the onset path
        onsetFIFO.markBufferRead();

        // Update the timer interval to match the new rate
        startTimerHz(drumProcessor.getSampleRate() / onsetSignal.size() + 1);
    }

    updateOnsetPath();
    repaint();
}
