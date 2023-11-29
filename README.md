# torchdrum-plugin
Differentiable drum synthesizer plugin

## Building

Clone project and pull submodules. Includes JUCE and RTNeural.
```
git clone --recurse-submodules https://github.com/jorshi/torchdrum-plugin.git
cd torchdrum-plugin
```

TorchLib path installed with python
```
export TORCHLIB_PATH=`python3 -c 'import torch;print(torch.utils.cmake_prefix_path)'`
```

Build with cmake
```
cmake -Bbuild
cmake --build build --config Release
```
