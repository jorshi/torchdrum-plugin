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
    triggerThresholdKnob->setBounds(0, 0, 56, 92);
    retriggerThresholdKnob->setBounds(width / 2 - 56 / 2, 0, 56, 92);
    holdTimeKnob->setBounds(width - 56, 0, 56, 92);
}
