add_subdirectory(Modules)

target_sources(${BaseTargetName} PRIVATE
        DrumSynth.cpp
        Snare808.cpp)
