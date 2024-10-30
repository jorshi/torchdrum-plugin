// Animate features extracted at onsets
#pragma once

#include "../PluginProcessor.h"
#include <juce_gui_basics/juce_gui_basics.h>

class FeatureCircle : public juce::Component
{
public:
    FeatureCircle();
    ~FeatureCircle() override {}

    void paint(juce::Graphics& g) override;
    void setNumPoints(int numPoints);
    void setMagnitude(size_t index, float newValue);

    // Return points of the triangle relative to the top left corner of this component
    std::vector<juce::Point<float>> getPoints();

private:
    std::vector<juce::Point<float>> points;
    std::vector<float> magnitude;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FeatureCircle)
};

class FeatureVisualizer : public juce::Component, juce::ActionListener
{
public:
    FeatureVisualizer() = delete;
    FeatureVisualizer(TorchDrumProcessor& p);
    ~FeatureVisualizer() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    // Callback for action listener
    void actionListenerCallback(const juce::String& message) override;

private:
    TorchDrumProcessor& drumProcessor;
    FeatureCircle featureCircle;

    const static int numFeatures = 3;
    const std::string labelText[numFeatures] = { "Brightness", "Noise", "Amplitude" };
    juce::Label featureLabels[numFeatures];
    juce::FontOptions fontOptions;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FeatureVisualizer)
};
