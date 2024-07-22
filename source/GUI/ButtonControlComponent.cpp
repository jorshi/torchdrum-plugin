#include "ButtonControlComponent.h"
#include "TorchDrumStyle.h"

ButtonControlComponent::ButtonControlComponent(TorchDrumProcessor& processor)
    : drumProcessor(processor)
{
    loadButton.setButtonText("Load");
    saveButton.setButtonText("Save");
    fineTuneButton.setButtonText("Fine Tune");
    aboutButton.setButtonText("About");

    fineTuneButton.setToggleable(true);
    fineTuneButton.setClickingTogglesState(true);

    addAndMakeVisible(loadButton);
    addAndMakeVisible(saveButton);
    addAndMakeVisible(fineTuneButton);
    addAndMakeVisible(aboutButton);
}

void ButtonControlComponent::resized()
{
    loadButton.setBounds(buttonContol1Bounds);
    saveButton.setBounds(buttonContol2Bounds);
    fineTuneButton.setBounds(buttonContol3Bounds);
    aboutButton.setBounds(buttonContol4Bounds);
}
