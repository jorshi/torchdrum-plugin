// Animate features extracted at onsets
#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class FeatureCircle : public juce::Component
{
public:
    FeatureCircle();
    ~FeatureCircle() override {}

    void paint(juce::Graphics& g) override;
    void setNumPoints(int numPoints);

private:
    std::vector<juce::Point<float>> points;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FeatureCircle)
};

class FeatureVisualizer : public juce::Component
{
public:
    FeatureVisualizer();
    ~FeatureVisualizer() override {}

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    FeatureCircle featureCircle;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FeatureVisualizer)
};
