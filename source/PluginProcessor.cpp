#include "PluginProcessor.h"
#include "PluginEditor.h"

TorchDrumProcessor::TorchDrumProcessor() : synthController(snare808, parameters)
{
    // Add synthesizer parameters
    //drumSynth.getParameters().add(*this);
    snare808.getParameters().add(*this);

    // Add controller parameters
    parameters.add(*this);
}

void TorchDrumProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    //drumSynth.prepare(sampleRate, samplesPerBlock);
    snare808.prepare(sampleRate, samplesPerBlock);
    synthController.prepare(sampleRate, samplesPerBlock);
    juce::ignoreUnused(samplesPerBlock);
}

void TorchDrumProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                      juce::MidiBuffer& midiMessages)

{
    juce::ignoreUnused(midiMessages);

    // Parameters to update once per block
    auto& onsetDetection = synthController.getOnsetDetection();
    onsetDetection.updateParameters(parameters.onThreshold->get(),
                                    parameters.offThreshold->get(),
                                    parameters.waitSamples->get());

    // Square Root 3dB Dry/Wet Mix
    auto drywet = parameters.drywet->get();
    float dry = std::sqrt(1.0f - drywet);
    float wet = std::sqrt(drywet);

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

        // Process the controller
        synthController.process(inputSample);

        // Process the synthesizer
        float synthSample = snare808.process();
        for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            auto* channelData = buffer.getWritePointer(channel);
            channelData[sample] = synthSample * wet + channelData[sample] * dry;
        }
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

    // Save model path and feature normalizers
    juce::ValueTree modelPath("ModelPath");
    modelPath.setProperty(
        "Path", juce::String(synthController.getModelPath()), nullptr);
    pluginPreset.appendChild(modelPath, nullptr);

    copyXmlToBinary(*pluginPreset.createXml(), destData);
}

void TorchDrumProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    // Loads your parameters, and any other potential data from an XML:

    auto xml = getXmlFromBinary(data, sizeInBytes);

    if (xml != nullptr)
    {
        auto preset = juce::ValueTree::fromXml(*xml);
        auto params = preset.getChildWithName("Params");

        for (auto& param : getParameters())
        {
            auto paramTree = params.getChildWithName(PluginHelpers::getParamID(param));

            if (paramTree.isValid())
                param->setValueNotifyingHost(paramTree["Value"]);
        }

        // Load your non-parameter data now
        auto modelPath = preset.getChildWithName("ModelPath");
        if (modelPath.isValid())
        {
            // Load the model, but don't overwrite the parameters
            std::string path = modelPath["Path"].toString().toStdString();
            synthController.updateModel(path, false);
        }
    }
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TorchDrumProcessor();
}
