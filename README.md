# TorchDrum Plugin

torchdrum is an audio plugin that has audio input and output. It is a real-time drum synthesizer that receives audio as input, which is used to trigger and control the synthesizer.

The development of torchdrum is based on research on [Real-time Timbre Remapping with Differentiable DSP](https://arxiv.org/abs/2407.04547). For more information on this research please visit the [accompanying website](https://jordieshier.com/projects/nime2024/), which includes links code for training new mapping models that can be played within this plug-in.

## Building from Source

Clone project and pull submodules. Includes JUCE.
```
git clone --recurse-submodules git@github.com:jorshi/torchdrum-plugin.git
cd torchdrum-plugin
```

Install TorchLib dependency. We recommend doing Python. Recommended to
create a new virtual environment. Instructions below use pyenv:

First, [install pyenv](https://github.com/pyenv/pyenv?tab=readme-ov-file#installation)

Install python 3.10:
```bash
pyenv install 3.10
pyenv shell 3.10
```

Install python dependencies:
```bash
python -m venv venv
source venv/bin/activate
python -m pip install --upgrade pip
python -m pip install torch==2.1.1 --index-url https://download.pytorch.org/whl/cpu
python -m pip install "numpy<2.0"
```

Save the TORCHLIB_PATH from Python
```bash
export TORCHLIB_PATH=`python3 -c 'import torch;print(torch.utils.cmake_prefix_path)'`
```

Build with cmake
```bash
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=$TORCHLIB_PATH
cmake --build build --config Release --parallel 4
```

There is a warning, please ignore:
```
CMake Warning at venv/lib/python3.9/site-packages/torch/share/cmake/Torch/TorchConfig.cmake:22 (message):
  static library kineto_LIBRARY-NOTFOUND not found.
Call Stack (most recent call first):
  venv/lib/python3.9/site-packages/torch/share/cmake/Torch/TorchConfig.cmake:127 (append_torchlib_if_found)
  CMakeLists.txt:10 (find_package)
```

If it builds correctly, expect to see:
```
[  a%] Built target juce_vst3_helper
[  b%] Built target TorchDrum
[  c%] Built target TorchDrum_Standalone
[  d%] Built target TorchDrum_VST3
[100%] Built target TorchDrum_AU
```

It will replace any existing version in user audio plugin folders.

## Future Development Ideas

- [x] dry/wet
- [ ] info on model
- [x] feedback for onset detection
- [ ] visualization of the decaying frequencies
