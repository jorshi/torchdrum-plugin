#include "PluginProcessor.h"
#include "PluginEditor.h"

TorchDrumProcessor::TorchDrumProcessor() { parameters.add(*this); }

void TorchDrumProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    onsetDetection.prepare(sampleRate);
    synthController.prepare(sampleRate, samplesPerBlock);
    juce::ignoreUnused(samplesPerBlock);
}

void TorchDrumProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                      juce::MidiBuffer& midiMessages)

{
    juce::ignoreUnused(midiMessages);

    if (parameters.enable->get())
        buffer.applyGain(parameters.gain->get());
    else
        buffer.clear();

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        // Process input audio for the controller -- mix to mono
        // TODO: Is mixing to mono the right way to go? Or will this mess
        // with phase / transients?
        float inputSample = 0.0f;
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            auto* channelData = buffer.getReadPointer(channel);
            inputSample += channelData[sample];
        }

        inputSample /= static_cast<float>(buffer.getNumChannels());
        bool trigger = onsetDetection.process(inputSample);

        // Process the controller
        synthController.process(inputSample);
    }
}

juce::AudioProcessorEditor* TorchDrumProcessor::createEditor()
{
    return new TorchDrumEditor(*this);
}

void TorchDrumProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    // Serializes your parameters, and any other potential data into an XML:

    juce::ValueTree params("Params");

    for (auto& param : getParameters())
    {
        juce::ValueTree paramTree(PluginHelpers::getParamID(param));
        paramTree.setProperty("Value", param->getValue(), nullptr);
        params.appendChild(paramTree, nullptr);
    }

    juce::ValueTree pluginPreset("TorchDrum");
    pluginPreset.appendChild(params, nullptr);
    // This a good place to add any non-parameters to your preset

    copyXmlToBinary(*pluginPreset.createXml(), destData);
}

void TorchDrumProcessor::setStateInformation(const void* data,
                                             int sizeInBytes)
{
    // Loads your parameters, and any other potential data from an XML:

    auto xml = getXmlFromBinary(data, sizeInBytes);

    if (xml != nullptr)
    {
        auto preset = juce::ValueTree::fromXml(*xml);
        auto params = preset.getChildWithName("Params");

        for (auto& param : getParameters())
        {
            auto paramTree =
                params.getChildWithName(PluginHelpers::getParamID(param));

            if (paramTree.isValid())
                param->setValueNotifyingHost(paramTree["Value"]);
        }

        // Load your non-parameter data now
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TorchDrumProcessor();
}
