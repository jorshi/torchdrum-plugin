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
    addAndMakeVisible(buttonControlComponent);
    addAndMakeVisible(globalControlComponent);
    addAndMakeVisible(onsetControlComponent);
    addAndMakeVisible(synthControlComponent);
    addAndMakeVisible(visualizerComponent);
}

TorchDrumInterface::~TorchDrumInterface() {}

void TorchDrumInterface::resized()
{
    buttonControlComponent.setBounds(getButtonControlComponentBounds(getWidth()));
    globalControlComponent.setBounds(globalControlComponentBounds);
    onsetControlComponent.setBounds(getOnsetControlComponentBounds(getWidth()));
    synthControlComponent.setBounds(getSynthControlComponentBounds(getWidth()));
    visualizerComponent.setBounds(getVisualizerBounds(getWidth()));
}
