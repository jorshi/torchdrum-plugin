# torchdrum-plugin
Differentiable drum synthesizer plugin


# Use Python3 within the shell:
```
pyenv install 3.9
pyenv shell 3.9.16
```

## Building from Source

Clone project and pull submodules. Includes JUCE.
```
git clone --recurse-submodules git@github.com:jorshi/torchdrum-plugin.git
cd torchdrum-plugin
```

Install TorchLib dependency. One easy way to do this is via Python. Recommended to
create a new virtual environment or anaconda environment to do this.
```
python -m venv venv
source venv/bin/activate
python -m pip install --upgrade pip
python -m pip install torch==2.1.1 --index-url https://download.pytorch.org/whl/cpu
python -m pip install numpy
```

Save the TORCHLIB_PATH from Python
```
export TORCHLIB_PATH=`python3 -c 'import torch;print(torch.utils.cmake_prefix_path)'`
```

Build with cmake
```
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=$TORCHLIB_PATH
cmake --build build --config Release --parallel 4
```

There is a warning, please ignore:
CMake Warning at venv/lib/python3.9/site-packages/torch/share/cmake/Torch/TorchConfig.cmake:22 (message):
  static library kineto_LIBRARY-NOTFOUND not found.
Call Stack (most recent call first):
  venv/lib/python3.9/site-packages/torch/share/cmake/Torch/TorchConfig.cmake:127 (append_torchlib_if_found)
  CMakeLists.txt:10 (find_package)


If it builds correctly, expect to see:
[  a%] Built target juce_vst3_helper
[  b%] Built target TorchDrum
[  c%] Built target TorchDrum_Standalone
[  d%] Built target TorchDrum_VST3
[100%] Built target TorchDrum_AU

It will replace any existing version.

How to use:

This is an audio plugin, so it has audio input and output.
It is a real-time drum synthensizer than takes audio as input.


Ideas:
dry/wet

info on Model

Feedback for onset detection

Visualisation of the decaying frequencies
