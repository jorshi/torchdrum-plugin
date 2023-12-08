add_subdirectory(FeatureExtraction)
add_subdirectory(Synth)

target_sources(${BaseTargetName} PRIVATE
        PluginProcessor.cpp
        PluginEditor.cpp
        Biquad.cpp
        NeuralNetwork.cpp
        OnsetDetection.cpp
        SynthController.cpp)
