#include "FeatureVisualizer.h"
#include "TorchDrumStyle.h"

FeatureCircle::FeatureCircle() {}

void FeatureCircle::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::white);
    g.fillEllipse(0.0f, 0.0f, (float) getWidth(), (float) getHeight());

    // Draw the triangle
    if (points.size() > 0)
    {
        int radius = getWidth() / 2;
        juce::Point<int> centre(radius, radius);
        g.setOrigin(centre);

        juce::Path p;
        p.startNewSubPath(points[0] * radius * magnitude[0]);
        for (auto i = 1; i < points.size(); i++)
            p.lineTo(points[i] * radius * magnitude[i]);

        p.closeSubPath();
        g.setColour(onsetVisualizerColour);
        g.fillPath(p);
    }
}

void FeatureCircle::setNumPoints(int numPoints)
{
    // Calculate locations of feature points
    auto twoPi = juce::MathConstants<float>::twoPi;
    float startAngle = twoPi / 4.0f;
    float shiftAngle = twoPi / numPoints;

    points.clear();
    magnitude.clear();
    for (auto i = 0; i < numPoints; i++)
    {
        float angle = startAngle + shiftAngle * i;
        points.emplace_back(std::sinf(angle), -std::cosf(angle));
        magnitude.push_back(1.0f);
    }
}

void FeatureCircle::setMagnitude(size_t index, float newValue)
{
    jassert(index < magnitude.size());
    magnitude[index] = newValue;
}

//==============================================================================

FeatureVisualizer::FeatureVisualizer(TorchDrumProcessor& p) : drumProcessor(p)
{
    featureCircle.setNumPoints(3);
    addAndMakeVisible(featureCircle);

    // Add the action listener to the SynthController
    drumProcessor.getSynthController().getBroadcaster().addActionListener(this);
}

FeatureVisualizer::~FeatureVisualizer()
{
    drumProcessor.getSynthController().getBroadcaster().removeActionListener(this);
}

void FeatureVisualizer::paint(juce::Graphics& g) {}

void FeatureVisualizer::resized() { featureCircle.setBounds(featureVizCircleBounds); }

void FeatureVisualizer::actionListenerCallback(const juce::String& message)
{
    if (message == "trigger")
    {
        auto& results = drumProcessor.getSynthController().getFeatures();
        featureCircle.setMagnitude(0, results.rmsMean.getNormalized());
        featureCircle.setMagnitude(1, results.spectralCentroidMean.getNormalized());
        featureCircle.setMagnitude(2, results.spectralFlatnessMean.getNormalized());
        featureCircle.repaint();
    }
}
