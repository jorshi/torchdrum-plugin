#include "FeatureVisualizer.h"
#include "TorchDrumStyle.h"

FeatureCircle::FeatureCircle() {}

void FeatureCircle::paint(juce::Graphics& g)
{
    auto circeBounds = getLocalBounds().reduced(featureVizTrianglePointsRadius);

    g.setColour(juce::Colours::white);
    g.fillEllipse(circeBounds.toFloat());

    if (points.size() < 1)
        return;

    // Draw the triangle with each corner
    juce::Point<int> centre(getWidth() / 2, getWidth() / 2);
    g.setOrigin(centre);

    juce::Path p;
    int radius = circeBounds.getWidth() / 2;
    p.startNewSubPath(points[0] * radius * magnitude[0]);

    for (auto i = 1; i < points.size(); i++)
        p.lineTo(points[i] * radius * magnitude[i]);

    p.closeSubPath();
    g.setColour(onsetVisualizerColour);
    g.fillPath(p);

    // Now draw circles at each point
    float circleRadius = (float) featureVizTrianglePointsRadius;
    g.setColour(borderColour);
    for (auto i = 0; i < points.size(); i++)
    {
        auto outside = points[i] * radius;
        g.fillEllipse(outside.getX() - featureVizTrianglePointsRadius,
                      outside.getY() - featureVizTrianglePointsRadius,
                      featureVizTrianglePointsRadius * 2.0f,
                      featureVizTrianglePointsRadius * 2.0f);
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
    magnitude[index] = juce::jmap(newValue, 0.1f, 0.95f);
}

std::vector<juce::Point<float>> FeatureCircle::getPoints()
{
    juce::Point<int> centre(getWidth() / 2, getWidth() / 2);
    auto circeBounds = getLocalBounds().reduced(featureVizTrianglePointsRadius);
    int radius = circeBounds.getWidth() / 2;
    std::vector<juce::Point<float>> trianglePoints;

    for (auto i = 0; i < points.size(); i++)
    {
        auto outside = points[i] * radius;
        outside = outside + centre.toFloat();
        trianglePoints.push_back(outside);
    }

    return trianglePoints;
}

//==============================================================================

FeatureVisualizer::FeatureVisualizer(TorchDrumProcessor& p) : drumProcessor(p)
{
    featureCircle.setNumPoints(numFeatures);
    addAndMakeVisible(featureCircle);

    // Add the action listener to the SynthController
    drumProcessor.getSynthController().getBroadcaster().addActionListener(this);
}

FeatureVisualizer::~FeatureVisualizer()
{
    drumProcessor.getSynthController().getBroadcaster().removeActionListener(this);
}

void FeatureVisualizer::paint(juce::Graphics& g) {}

void FeatureVisualizer::resized()
{
    featureCircle.setBounds(featureVizCircleBounds);
    auto points = featureCircle.getPoints();

    // Update points to be relative to parent
    auto circleMiddle = featureCircle.getWidth() / 2;
    for (auto i = 0; i < points.size(); ++i)
    {
        bool left = points[i].getX() < circleMiddle;
        points[i].addXY(getX(), getY());
        if (left)
        {
        }
    }
}

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
