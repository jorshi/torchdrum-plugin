#include "ButtonLookAndFeel.h"
#include "BinaryData.h"
#include "TorchDrumStyle.h"

ButtonLookAndFeel::ButtonLookAndFeel()
{
    // Load the background image
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::buttonBG2x_png,
                                                      BinaryData::buttonBG2x_pngSize);
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

    // Draw rectangle
    float x1 = buttonArea.getX();
    float y1 = buttonArea.getY();
    float y2 = buttonArea.getY() + buttonArea.getHeight();
    auto gradient = juce::ColourGradient(
        buttonGradientColourB, x1, y1, buttonGradientColourA, x1, y2, false);

    g.setGradientFill(gradient);
    g.fillRect(buttonArea);
}
