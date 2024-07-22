#include "GlobalControlComponent.h"
#include "TorchDrumStyle.h"

GlobalControlComponent::GlobalControlComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor)
{
    auto& parameters = drumProcessor.getGlobalParameters();

    neuralKnob =
        std::make_unique<DualKnobComponent>(parameters.parameters[3],
                                            parameters.guiRanges[3],
                                            DualKnobComponent::KnobType::SingleLarge);
    addAndMakeVisible(neuralKnob.get());
}

void GlobalControlComponent::paint(juce::Graphics& g) {}

void GlobalControlComponent::resized()
{
    auto width = getWidth();
    auto height = getHeight();

    neuralKnob->setBounds(globalKnob2Bounds);
}
