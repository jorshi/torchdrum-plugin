#include "TorchDrumInterface.h"
#include "TorchDrumStyle.h"

TorchDrumInterface::TorchDrumInterface(TorchDrumProcessor& p)
    : drumProcessor(p),
      buttonControlComponent(p),
      globalControlComponent(p),
      onsetControlComponent(p),
      synthControlComponent(p),
      visualizerComponent(p)
{
    buttonControlComponent.setLookAndFeel(&buttonLookAndFeel);
    resetButtonLookAndFeel.setUseBackgroundImage(false);
    resetButtonLookAndFeel.setUseBorder(false);
    visualizerComponent.setLookAndFeel(&resetButtonLookAndFeel);
    addAndMakeVisible(buttonControlComponent);
    addAndMakeVisible(globalControlComponent);
    addAndMakeVisible(onsetControlComponent);
    addAndMakeVisible(synthControlComponent);
    addAndMakeVisible(visualizerComponent);
}

void TorchDrumInterface::resized()
{
    jassert(getWidth() == 960); // The interface should always be a constant size
    buttonControlComponent.setBounds(buttonControlComponentBounds);
    globalControlComponent.setBounds(globalControlComponentBounds);
    onsetControlComponent.setBounds(getOnsetControlComponentBounds(getWidth()));
    synthControlComponent.setBounds(getSynthControlComponentBounds(getWidth()));
    visualizerComponent.setBounds(visualizerBounds);
}
