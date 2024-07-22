/**
 * GUI wrapper class that contains all the GUI components.
 */
#pragma once

#include "../PluginProcessor.h"
#include "ButtonControlComponent.h"
#include "GlobalControlComponent.h"
#include "OnsetControlComponent.h"
#include "SynthControlComponent.h"
#include "VisualizerComponent.h"
#include <juce_gui_basics/juce_gui_basics.h>

class TorchDrumInterface : public juce::Component
{
public:
    TorchDrumInterface() = delete;
    TorchDrumInterface(TorchDrumProcessor& p);
    ~TorchDrumInterface() override;

    void paint([[maybe_unused]] juce::Graphics& g) override {};
    void resized() override;

private:
    TorchDrumProcessor& drumProcessor;

    // GUI Components
    ButtonControlComponent buttonControlComponent;
    GlobalControlComponent globalControlComponent;
    OnsetControlComponent onsetControlComponent;
    SynthControlComponent synthControlComponent;
    VisualizerComponent visualizerComponent;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TorchDrumInterface)
};
