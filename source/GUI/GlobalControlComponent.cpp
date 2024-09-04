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

    dryWetKnob =
        std::make_unique<DualKnobComponent>(parameters.parameters[4],
                                            parameters.guiRanges[4],
                                            DualKnobComponent::KnobType::SingleLarge);
    addAndMakeVisible(dryWetKnob.get());
}

void GlobalControlComponent::resized()
{
    neuralKnob->setBounds(globalKnob2Bounds);
    dryWetKnob->setBounds(globalKnob1Bounds);
}
