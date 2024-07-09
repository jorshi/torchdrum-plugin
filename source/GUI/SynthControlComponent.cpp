#include "SynthControlComponent.h"
#include "../Synth/SynthParameterBase.h"

SynthControlComponent::SynthControlComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor)
{
    knobRow1.setNumKnobs(4);
    knobRow1.setLabelText("Oscillator 1");
    addAndMakeVisible(knobRow1);

    knobRow2.setNumKnobs(4);
    knobRow2.setLabelText("Oscillator 2");
    addAndMakeVisible(knobRow2);

    knobRow3.setNumKnobs(4);
    knobRow3.setLabelText("Filtered Noise");
    addAndMakeVisible(knobRow3);

    knobRow4.setNumKnobs(4);
    knobRow4.setLabelText("Global Controls");
    addAndMakeVisible(knobRow4);

    auto& synthParameters = processor.getSynthParameters();
    knobRow1.addParameter(synthParameters.parameters[0], 0);
    knobRow1.addParameter(synthParameters.parameters[1], 1);
    knobRow1.addParameter(synthParameters.parameters[5], 2);
    knobRow1.addParameter(synthParameters.parameters[10], 3);

    knobRow2.addParameter(synthParameters.parameters[2], 0);
    knobRow2.addParameter(synthParameters.parameters[3], 1);
    knobRow2.addParameter(synthParameters.parameters[6], 2);
    knobRow2.addParameter(synthParameters.parameters[11], 3);

    knobRow3.addParameter(synthParameters.parameters[8], 0);
    knobRow3.addParameter(synthParameters.parameters[9], 1);
    knobRow3.addParameter(synthParameters.parameters[7], 2);
    knobRow3.addParameter(synthParameters.parameters[12], 3);

    knobRow4.addParameter(synthParameters.parameters[4], 1);
    knobRow4.addParameter(synthParameters.parameters[13], 2);
}

void SynthControlComponent::paint(juce::Graphics& g)
{
    // Draw the knob rows
    auto rowHeight = getKnobRowComponentHeight(getWidth());
    auto padding = (int) getKnobRowPadding(rowHeight);
    knobRow1.setBounds(0, 0, getWidth(), rowHeight);
    knobRow2.setBounds(0, rowHeight + padding, getWidth(), rowHeight);
    knobRow3.setBounds(0, (rowHeight + padding) * 2, getWidth(), rowHeight);
    knobRow4.setBounds(0, (rowHeight + padding) * 3, getWidth(), rowHeight);
}
