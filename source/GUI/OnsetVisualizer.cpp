#include "OnsetVisualizer.h"
#include "TorchDrumStyle.h"
#include <algorithm>

OnsetVisualizer::OnsetVisualizer(TorchDrumProcessor& p)
    : drumProcessor(p), parameters(p.getGlobalParameters())
{
    drawableSignal.resize((size_t) (drawSeconds * drawResoluationHz));
    std::fill(drawableSignal.begin(), drawableSignal.end(), 0.0f);

    fontOptions = getPluginFont();
    font = fontOptions;
    font.setHeight(12.0f);

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

    // Draw the meter on the left side
    g.setColour(onsetVisMeterColour);
    g.fillRect(0, 0, 28, getHeight());

    g.setColour(borderColour);
    g.drawRect(0, 0, 28, getHeight(), 1);

    // TODO(js) this seems to be causing issues
    // juce::Font font = fontOptions;
    g.setFont(font);

    for (int i = 1; i < 6; ++i)
    {
        int y = (int) (getHeight() - i * getHeight() / 6.0f);
        g.drawRect(20, y, 8, 1, 1);

        g.drawText(std::to_string(i * 10),
                   0,
                   y - 6,
                   18,
                   12,
                   juce::Justification::centredRight);
    }

    // Draw the values of the parameters
    float triggerThreshold = parameters.parameters[0]->getValue();
    triggerThreshold = parameters.parameters[0]->convertFrom0to1(triggerThreshold);
    triggerThreshold /= maxValue;

    float releaseThreshold = parameters.parameters[1]->getValue();
    releaseThreshold = parameters.parameters[1]->convertFrom0to1(releaseThreshold);
    releaseThreshold /= maxValue;

    int triggerThresholdY = (int) (getHeight() - (getHeight() * triggerThreshold));
    int releaseThresholdY = (int) (getHeight() - (getHeight() * releaseThreshold));

    g.drawRect(28, triggerThresholdY, getWidth() - 28, 1, 1);
    g.drawRect(28, releaseThresholdY, getWidth() - 28, 1, 1);
}

void OnsetVisualizer::resized() {}

void OnsetVisualizer::updateOnsetPath()
{
    // Create a new path
    juce::Path p;
    p.startNewSubPath(0, getHeight());

    // Draw the onset signal
    // We want to start the drawing from the write index and wrap around
    size_t start = writeIndex;
    for (size_t i = 0; i < drawableSignal.size(); ++i)
    {
        float x = i * (float) getWidth() / drawableSignal.size();
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
        const int rate = (int) (drumProcessor.getSampleRate() / drawResoluationHz);

        // Push new samples onto the drawing buffer
        while (readIndex < onsetSignal.size())
        {
            if (writeIndex >= drawableSignal.size())
                writeIndex = 0;

            float value =
                std::max(std::min(onsetSignal[readIndex], maxValue), minValue);
            value = juce::jmap(value, minValue, maxValue, 0.0f, 1.0f);
            drawableSignal[writeIndex++] = value;
            readIndex += (size_t) rate;
        }

        jassert(readIndex >= onsetSignal.size());
        readIndex -= std::max(onsetSignal.size(), (size_t) 0);

        // Update the onset path
        onsetFIFO.markBufferRead();

        // Update the timer interval to match the new rate -- this is the rate that
        // we expect the onset signal buffer to be filled, we'll run slightly faster
        startTimerHz((int) (drumProcessor.getSampleRate() / onsetSignal.size()) + 1);
    }

    updateOnsetPath();
    repaint();
}
