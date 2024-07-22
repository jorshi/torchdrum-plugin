#include "OnsetControlComponent.h"
#include "../Parameters.h"
#include "TorchDrumStyle.h"

OnsetControlComponent::OnsetControlComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor)
{
    auto& parameters = drumProcessor.getGlobalParameters();
    triggerThresholdKnob =
        std::make_unique<DualKnobComponent>(parameters.parameters[0],
                                            parameters.guiRanges[0],
                                            DualKnobComponent::KnobType::SingleSmall);
    retriggerThresholdKnob =
        std::make_unique<DualKnobComponent>(parameters.parameters[1],
                                            parameters.guiRanges[1],
                                            DualKnobComponent::KnobType::SingleSmall);
    holdTimeKnob =
        std::make_unique<DualKnobComponent>(parameters.parameters[2],
                                            parameters.guiRanges[2],
                                            DualKnobComponent::KnobType::SingleSmall);

    addAndMakeVisible(triggerThresholdKnob.get());
    addAndMakeVisible(retriggerThresholdKnob.get());
    addAndMakeVisible(holdTimeKnob.get());
}

void OnsetControlComponent::paint(juce::Graphics& g) {}

void OnsetControlComponent::resized()
{
    auto width = getWidth();
    auto height = getHeight();
    auto singleKnobWidth = width / 3;

    triggerThresholdKnob->setBounds(0, 0, singleKnobWidth, height);
    retriggerThresholdKnob->setBounds(singleKnobWidth, 0, singleKnobWidth, height);
    holdTimeKnob->setBounds(singleKnobWidth * 2, 0, singleKnobWidth, height);

    // Add a border to the hold time knob to push onto two lines
    holdTimeKnob->setTextBoxBorderSize(juce::BorderSize<int>(0, 10, 0, 10));
}
