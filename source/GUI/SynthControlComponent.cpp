#include "SynthControlComponent.h"
#include "../Synth/SynthParameterBase.h"

SynthControlComponent::SynthControlComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor)
{
    std::vector<std::vector<int>> knobRowConnections = {
        { 0, 1, 5, 10 }, { 2, 3, 6, 11 }, { 8, 9, 7, 12 }, { -1, 4, 13, -1 }
    };

    std::vector<std::string> labels = {
        "Oscillator 1", "Oscillator 2", "Filtered Noise", "Global Controls"
    };

    connectParameters(knobRowConnections, labels);

    // Add action listener
    // TODO: Probably don't need this any more
    drumProcessor.getSynthController().getBroadcaster().addActionListener(this);
}

SynthControlComponent::~SynthControlComponent()
{
    drumProcessor.getSynthController().getBroadcaster().removeActionListener(this);
    auto& synthParameters = drumProcessor.getSynthParameters();
    synthParameters.removeAllGUICallbacks();
}

void SynthControlComponent::resized()
{
    int rowHeight = (int) getKnobRowComponentHeight(getWidth());
    int padding = (int) getKnobRowPadding(rowHeight);
    for (size_t i = 0; i < knobRows.size(); ++i)
        knobRows[i]->setBounds(
            0, (rowHeight + padding) * (int) i, getWidth(), rowHeight);
}

void SynthControlComponent::actionListenerCallback(const juce::String& message)
{
    if (message == "trigger")
    {
        repaint();
    }
}

void SynthControlComponent::connectParameters(
    std::vector<std::vector<int>>& connections,
    std::vector<std::string>& labels)
{
    jassert(connections.size() == labels.size()); // Rows and labels must match!

    auto& synthParameters = drumProcessor.getSynthParameters();
    knobRows.clear();
    for (size_t i = 0; i < connections.size(); ++i)
    {
        knobRows.emplace_back(std::make_unique<SynthControlKnobRow>());
        knobRows[i]->setNumKnobs((int) connections[i].size());
        knobRows[i]->setLabelText(labels[i]);
        addAndMakeVisible(*knobRows[i]);

        for (size_t j = 0; j < connections[i].size(); ++j)
        {
            if (connections[i][j] < 0)
                continue;

            knobRows[i]->addParameter(
                synthParameters.parameters[(size_t) connections[i][j]],
                synthParameters.guiRanges[(size_t) connections[i][j]],
                (int) j);
            synthParameters.addGUICallback(
                (size_t) connections[i][j],
                [i, j, this](float value)
                { knobRows[i]->getKnobs()[j]->setModulatedValue(value); });
        }
    }
}
