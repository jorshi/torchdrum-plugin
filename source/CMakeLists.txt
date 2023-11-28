add_subdirectory(Synth)

target_sources(${BaseTargetName} PRIVATE
        PluginProcessor.cpp
        PluginEditor.cpp
        Biquad.cpp
        FeatureExtraction.cpp
        OnsetDetection.cpp
        SynthController.cpp)
