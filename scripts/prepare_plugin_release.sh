#!/bin/bash

# exit on failure
set -e

rm -rf build

# Build plugin
cmake -Bbuild -GXcode -DMACOS_RELEASE=ON \
    -DCMAKE_PREFIX_PATH=/Users/jordanm/anaconda3/envs/torchdrum/lib/python3.10/site-packages/torch/share/cmake \
    -DCMAKE_XCODE_ATTRIBUTE_CODE_SIGN_STYLE="Manual" \
    -DCMAKE_XCODE_ATTRIBUTE_CODE_SIGN_INJECT_BASE_ENTITLEMENTS=NO \
    -DCMAKE_XCODE_ATTRIBUTE_OTHER_CODE_SIGN_FLAGS="--timestamp"

cmake --build build --config Release -j12

# Copy the release plugin and create a signature
rm -rf SignedPlugins
cp -r build/TorchDrum_artefacts/Release/VST3/ SignedPlugins/

# Copy libtorch
mkdir -p SignedPlugins/TorchDrum.vst3/Contents/Frameworks
cp /Users/jordanm/anaconda3/envs/torchdrum/lib/python3.10/site-packages/torch/lib/libtorch.dylib SignedPlugins/TorchDrum.vst3/Contents/Frameworks/
cp /Users/jordanm/anaconda3/envs/torchdrum/lib/python3.10/site-packages/torch/lib/libtorch_cpu.dylib SignedPlugins/TorchDrum.vst3/Contents/Frameworks/
cp /Users/jordanm/anaconda3/envs/torchdrum/lib/python3.10/site-packages/torch/lib/libc10.dylib SignedPlugins/TorchDrum.vst3/Contents/Frameworks/
cp /Users/jordanm/anaconda3/envs/torchdrum/lib/python3.10/site-packages/torch/lib/libtorch_global_deps.dylib SignedPlugins/TorchDrum.vst3/Contents/Frameworks/

# Update the links to libtorch
install_name_tool -change @rpath/libtorch.dylib @loader_path/../Frameworks/libtorch.dylib SignedPlugins/TorchDrum.vst3/Contents/MacOS/TorchDrum
install_name_tool -change @rpath/libtorch_cpu.dylib @loader_path/../Frameworks/libtorch_cpu.dylib SignedPlugins/TorchDrum.vst3/Contents/MacOS/TorchDrum
install_name_tool -change @rpath/libc10.dylib @loader_path/../Frameworks/libc10.dylib SignedPlugins/TorchDrum.vst3/Contents/MacOS/TorchDrum
install_name_tool -change @rpath/libtorch_global_deps.dylib @loader_path/../Frameworks/libtorch_global_deps.dylib SignedPlugins/TorchDrum.vst3/Contents/MacOS/TorchDrum

cd SignedPlugins
codesign --deep --force --options runtime --timestamp -s $APPLE_DEVELOPER_ID -v TorchDrum.vst3

codesign --display --verbose TorchDrum.vst3
codesign -vvv --deep --strict TorchDrum.vst3

# Notarization
ditto -c -k --keepParent TorchDrum.vst3 TorchDrum.zip
xcrun notarytool submit TorchDrum.zip --keychain-profile "notarytool-password" --wait
xcrun stapler staple TorchDrum.vst3

# Install plugin for testing
sudo rm -rf /Library/Audio/Plug-Ins/VST3/TorchDrum.vst3
rm -rf ~/Library/Audio/Plug-Ins/VST3/TorchDrum.vst3

sudo cp -r TorchDrum.vst3 /Library/Audio/Plug-Ins/VST3/
