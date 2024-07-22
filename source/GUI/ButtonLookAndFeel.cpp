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

void ButtonLookAndFeel::drawButtonBackground(juce::Graphics& g,
                                             juce::Button& button,
                                             const juce::Colour& backgroundColour,
                                             bool isMouseOverButton,
                                             bool isButtonDown)
{
    auto buttonArea = button.getLocalBounds();

    // Draw background image
    auto backgroundImageScaled =
        backgroundImage.rescaled(buttonArea.getWidth(), buttonArea.getHeight());
    g.drawImageAt(backgroundImageScaled, buttonArea.getX(), buttonArea.getY());

    float x1 = buttonArea.getX();
    float y1 = buttonArea.getY();
    float y2 = buttonArea.getY() + buttonArea.getHeight();
    juce::ColourGradient gradient;
    auto toggleState = button.getToggleState();

    // The background gradient colours depend on the button state
    if (isButtonDown || toggleState)
    {
        gradient = juce::ColourGradient(buttonDownGradientColourB,
                                        x1,
                                        y1,
                                        buttonDownGradientColourA,
                                        x1,
                                        y2,
                                        false);
    }
    else if (isMouseOverButton)
    {
        gradient = juce::ColourGradient(buttonOverGradientColourB,
                                        x1,
                                        y1,
                                        buttonOverGradientColourA,
                                        x1,
                                        y2,
                                        false);
    }
    else
    {
        gradient = juce::ColourGradient(
            buttonGradientColourB, x1, y1, buttonGradientColourA, x1, y2, false);
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
                                       bool isMouseOverButton,
                                       bool isButtonDown)
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
