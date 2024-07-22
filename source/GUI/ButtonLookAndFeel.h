#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

class ButtonLookAndFeel : public juce::LookAndFeel_V4
{
public:
    ButtonLookAndFeel();

    void drawButtonBackground(juce::Graphics& g,
                              juce::Button& button,
                              const juce::Colour& backgroundColour,
                              bool isMouseOverButton,
                              bool isButtonDown) override;

    void drawButtonText(juce::Graphics& g,
                        juce::TextButton& button,
                        bool isMouseOverButton,
                        bool isButtonDown) override;

private:
    juce::Image backgroundImage;
    juce::FontOptions fontOptions;
};
