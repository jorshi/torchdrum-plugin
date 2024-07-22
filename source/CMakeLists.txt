add_subdirectory(FeatureExtraction)
add_subdirectory(Synth)
add_subdirectory(GUI)

target_sources(${BaseTargetName} PRIVATE
        PluginProcessor.cpp
        PluginEditor.cpp
        Biquad.cpp
        NeuralNetwork.cpp
        OnsetDetection.cpp
        SynthController.cpp
        WaveformFIFO.cpp)
