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

    // triggerThresholdKnob =
    //     std::make_unique<DualKnobComponent>(parameters.parameters[0],
    //                                         parameters.guiRanges[0],
    //                                         DualKnobComponent::KnobType::SingleSmall);
}

void GlobalControlComponent::paint(juce::Graphics& g)
{
    // g.setColour(vizualizerGradientColourB);
    // g.fillRect(getLocalBounds());
    // g.setColour(borderColour);
    // g.drawRect(getLocalBounds(), 1);
}

void GlobalControlComponent::resized()
{
    auto width = getWidth();
    auto height = getHeight();

    neuralKnob->setBounds(globalKnob1Bounds);
    // triggerThresholdKnob->setBounds(0, 0, width, height);
}
