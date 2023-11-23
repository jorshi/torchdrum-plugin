# torchdrum-plugin
Differentiable drum synthesizer plugin

## Building

Clone project and pull submodules. Includes JUCE and RTNeural.
```
git clone --recurse-submodules https://github.com/jorshi/torchdrum-plugin.git
```

Build with cmake
```
cmake -Bbuild
cmake --build build --config Release
```
