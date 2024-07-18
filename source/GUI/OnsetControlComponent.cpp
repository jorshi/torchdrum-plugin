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
    addAndMakeVisible(triggerThresholdKnob.get());
}

void OnsetControlComponent::paint(juce::Graphics& g) {}

void OnsetControlComponent::resized()
{
    auto width = getWidth() / 3;
    auto height = getHeight();
    triggerThresholdKnob->setBounds(0, 0, width, height);
}
