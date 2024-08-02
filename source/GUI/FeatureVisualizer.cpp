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
        p.startNewSubPath(points[0] * radius);
        for (auto i = 1; i < points.size(); i++)
            p.lineTo(points[i] * radius);

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
    for (auto i = 0; i < numPoints; i++)
    {
        float angle = startAngle + shiftAngle * i;
        points.emplace_back(std::sinf(angle), -std::cosf(angle));
    }
}

FeatureVisualizer::FeatureVisualizer()
{
    featureCircle.setNumPoints(3);
    addAndMakeVisible(featureCircle);
}

void FeatureVisualizer::paint(juce::Graphics& g) {}

void FeatureVisualizer::resized() { featureCircle.setBounds(featureVizCircleBounds); }
