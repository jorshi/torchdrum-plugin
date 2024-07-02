cmake_minimum_required(VERSION 3.16)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum OS X deployment target")
set(CMAKE_CXX_STANDARD 17)
project(TorchDrum VERSION 0.0.5)

# Adding submodules
add_subdirectory(modules)

# Adding LibTorch
find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

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

# Adding source code
add_subdirectory(source)

# Adding binary data
add_subdirectory(assets)

target_compile_definitions(${BaseTargetName}
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
        DONT_SET_USING_JUCE_NAMESPACE=1)

target_link_libraries(${BaseTargetName} PRIVATE
        torchdrum_binary_data
        shared_plugin_helpers
        juce_dsp
        juce_recommended_config_flags
        juce_recommended_lto_flags
        juce_recommended_warning_flags)

target_link_libraries(${BaseTargetName} PUBLIC "${TORCH_LIBRARIES}")

# we need these flags for notarization on MacOS
option(MACOS_RELEASE "Set build flags for MacOS Release" OFF)
if(MACOS_RELEASE)
    message(STATUS "Setting MacOS release flags...")
    set_target_properties(${BaseTargetName}_Standalone PROPERTIES
        XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME YES)
endif()

# Option to build dynamic library
if (BUILD_TORCHDRUM_LIB)
    set(BaseTargetLibName ${BaseTargetName}Lib)

    add_library(${BaseTargetLibName} SHARED source/TorchDrumLib.cpp)
    set_target_properties(${BaseTargetLibName} PROPERTIES JUCE_TARGET_KIND_STRING "App")

    target_compile_definitions(${BaseTargetLibName}
        PRIVATE
            JUCE_STANDALONE_APPLICATION=1
            JUCE_WEB_BROWSER=0
            JUCE_USE_CURL=0
            TORCHDRUMLIB_BUILD=1)

    target_link_libraries(${BaseTargetLibName}
        PRIVATE
            juce::juce_audio_utils
            juce::juce_dsp
            "${TORCH_LIBRARIES}"
        PUBLIC
            juce_recommended_config_flags
            juce_recommended_lto_flags
            juce_recommended_warning_flags)

    target_include_directories(${BaseTargetLibName}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/modules/RTNeural)

    _juce_initialise_target(${BaseTargetLibName}  VERSION 1.0.0)
endif()
