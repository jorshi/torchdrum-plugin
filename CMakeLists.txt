cmake_minimum_required(VERSION 3.16)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment target")
set(CMAKE_CXX_STANDARD 17)
project(TorchDrum VERSION 0.0.1)

# Adding submodules
add_subdirectory(modules)

# Application formats to build
if(IOS)
    set(JUCE_FORMATS Standalone AUv3)
else()
    set(JUCE_FORMATS AU VST3 Standalone)
endif()

# Build LV2 only on Linux
if(UNIX AND NOT APPLE)
    message(STATUS "Building LV2 plugin format")
    list(APPEND JUCE_FORMATS LV2)
endif()

set(BaseTargetName TorchDrum)

juce_add_plugin("${BaseTargetName}"
        # VERSION ...                               # Set this if the plugin version is different to the project version
        # ICON_BIG ...                              # ICON_* arguments specify a path to an image file to use as an icon for the Standalone
        # ICON_SMALL ...
        COMPANY_NAME "C4DM"
        IS_SYNTH FALSE
        NEEDS_MIDI_INPUT TRUE
        NEEDS_MIDI_OUTPUT FALSE
        IS_MIDI_EFFECT FALSE
        EDITOR_WANTS_KEYBOARD_FOCUS TRUE
        COPY_PLUGIN_AFTER_BUILD TRUE
        PLUGIN_MANUFACTURER_CODE C4dM
        PLUGIN_CODE c4td
        FORMATS ${JUCE_FORMATS}
        PRODUCT_NAME "TorchDrum"
        LV2URI https://github.com/jorshi/torchdrum-plugin)

# create JUCE header
juce_generate_juce_header(${BaseTargetName})

# Adding source code
add_subdirectory(source)

target_compile_definitions(${BaseTargetName}
        PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        DONT_SET_USING_JUCE_NAMESPACE=1)

target_link_libraries(${BaseTargetName} PRIVATE
        shared_plugin_helpers
        juce_dsp
        juce_recommended_config_flags
        juce_recommended_lto_flags
        juce_recommended_warning_flags)

target_link_libraries(${BaseTargetName} LINK_PUBLIC RTNeural)
