#include "ButtonLookAndFeel.h"
#include "BinaryData.h"
#include "TorchDrumStyle.h"

ButtonLookAndFeel::ButtonLookAndFeel()
{
    // Load the background image
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::buttonBG2x_png,
                                                      BinaryData::buttonBG2x_pngSize);

    fontOptions = getRegularPluginFont();
}

void ButtonLookAndFeel::drawButtonBackground(
    juce::Graphics& g,
    juce::Button& button,
    [[maybe_unused]] const juce::Colour& backgroundColour,
    bool isMouseOverButton,
    bool isButtonDown)
{
    auto buttonArea = button.getLocalBounds();

    // Draw background image
    auto backgroundImageScaled =
        backgroundImage.rescaled(buttonArea.getWidth(), buttonArea.getHeight());
    g.drawImageAt(backgroundImageScaled, buttonArea.getX(), buttonArea.getY());

    juce::Point<float> top(buttonArea.getX(), buttonArea.getY());
    juce::Point<float> bottom(buttonArea.getX(),
                              buttonArea.getY() + buttonArea.getHeight());
    juce::ColourGradient gradient;
    auto toggleState = button.getToggleState();

    // The background gradient colours depend on the button state
    if (isButtonDown || toggleState)
    {
        gradient = juce::ColourGradient(
            buttonDownGradientColourB, top, buttonDownGradientColourA, bottom, false);
    }
    else if (isMouseOverButton)
    {
        gradient = juce::ColourGradient(
            buttonOverGradientColourB, top, buttonOverGradientColourA, bottom, false);
    }
    else
    {
        gradient = juce::ColourGradient(
            buttonGradientColourB, top, buttonGradientColourA, bottom, false);
    }

    g.setGradientFill(gradient);
    g.fillRect(buttonArea);

    // Draw the border -- two rectangles on either side
    g.setColour(borderColourTransparent);
    g.fillRect(buttonArea.removeFromLeft(2));
    g.fillRect(buttonArea.removeFromRight(2));
}

void ButtonLookAndFeel::drawButtonText(juce::Graphics& g,
                                       juce::TextButton& button,
                                       [[maybe_unused]] bool isMouseOverButton,
                                       [[maybe_unused]] bool isButtonDown)
{
    juce::Font font = fontOptions;
    font.setHeight(defaultTextHeight);
    g.setColour(juce::Colours::black);
    g.setFont(font);
    g.drawText(button.getButtonText(),
               button.getLocalBounds(),
               juce::Justification::centred,
               true);
}
