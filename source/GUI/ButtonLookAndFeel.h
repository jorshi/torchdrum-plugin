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

    void setUseBackgroundImage(bool newValue) { useBackgroundImage = newValue; }
    void setUseBorder(bool newValue) { useBorder = newValue; }

private:
    juce::Image backgroundImage;
    juce::FontOptions fontOptions;
    bool useBackgroundImage = true;
    bool useBorder = true;
};
