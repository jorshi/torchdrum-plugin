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

    for (size_t i = 1; i < points.size(); i++)
        p.lineTo(points[i] * radius * magnitude[i]);

    p.closeSubPath();
    g.setColour(onsetVisualizerColour);
    g.fillPath(p);

    // Now draw circles at each point
    g.setColour(borderColour);
    for (size_t i = 0; i < points.size(); i++)
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
    float startAngle = 3.5f * twoPi / 16.0f;
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

    for (size_t i = 0; i < points.size(); i++)
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

    for (auto i = 0; i < numFeatures; ++i)
    {
        featureLabels[i].setText(labelText[i],
                                 juce::NotificationType::dontSendNotification);
        featureLabels[i].setColour(juce::Label::textColourId, juce::Colours::black);
        featureLabels[i].setMinimumHorizontalScale(1.0);
        addAndMakeVisible(featureLabels[i]);
    }

    // Load custom font
    fontOptions = getPluginFont();

    // Add the action listener to the SynthController
    drumProcessor.getSynthController().getBroadcaster().addActionListener(this);
}

FeatureVisualizer::~FeatureVisualizer()
{
    drumProcessor.getSynthController().getBroadcaster().removeActionListener(this);
}

void FeatureVisualizer::paint([[maybe_unused]] juce::Graphics& g) {}

void FeatureVisualizer::resized()
{
    featureCircle.setBounds(featureVizCircleBounds);
    auto points = featureCircle.getPoints();

    // Update points to be relative to parent
    auto circleMiddleX = featureCircle.getWidth() / 2;
    auto circleMiddleY = featureCircle.getHeight() / 2;

    // Load font
    juce::Font font(fontOptions);
    font = font.withHeight(16);
    for (size_t i = 0; i < points.size(); ++i)
    {
        // Determine what quadrant of the circle the point lies in
        // This will be used to position the label
        bool left = points[i].getX() < circleMiddleX;
        bool upper = points[i].getY() < circleMiddleY;

        // Update the point X & Y coords to be relative to container
        points[i].addXY(featureCircle.getX(), featureCircle.getY());

        // Position label
        float labelX = left ? points[i].getX() - 65.0f : points[i].getX() + 5.0f;
        float labelY = upper ? points[i].getY() - 16.0f : points[i].getY();
        auto justification =
            left ? juce::Justification::centredRight : juce::Justification::centredLeft;

        featureLabels[i].setBounds((int) labelX, (int) labelY, 60, 16);
        featureLabels[i].setJustificationType(justification);
        featureLabels[i].setBorderSize(juce::BorderSize<int>(0));
        featureLabels[i].setFont(font);
    }
}

void FeatureVisualizer::actionListenerCallback(const juce::String& message)
{
    if (message == "trigger")
    {
        auto& results = drumProcessor.getSynthController().getFeatures();
        featureCircle.setMagnitude(2, results.rmsMean.getNormalized());
        featureCircle.setMagnitude(0, results.spectralCentroidMean.getNormalized());
        featureCircle.setMagnitude(1, results.spectralFlatnessMean.getNormalized());
        featureCircle.repaint();
    }
}
