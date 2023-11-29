"""
Define a pytest fixture to load the TorchDrumLib library.
"""
import os
import re
from itertools import zip_longest

import cppyy
import pytest

CONFIG = os.getenv("CONFIG", "Debug")

# Ignore the python_comparison tests if torchdrum is not installed
collect_ignore = []
try:
    import torchdrum as td  # noqa: F401
except ImportError:
    collect_ignore.append("python_comparison")


# Helper functions and fixture to load the TorchDrumLib library
def __get_juce_defs(defs_path: str) -> str:
    """
    From https://github.com/kunitoki/popsicle
    """
    with open(defs_path, "r") as f:
        defs = [iter(re.split("\x1f|\x1e|\\s", f.read()))] * 2
        defs = zip_longest(*defs, fillvalue=None)
        defs = list(filter(lambda v: v[0] == "MODULE_DEFINITIONS", defs))[0]
        defs = list(
            map(lambda d: "#define {} {}".format(*d.split("=")), defs[1].split(";"))
        )

    return "\n".join(defs)


@pytest.fixture
def torchdrum():
    """
    Load the TorchDrumLib library and return the global namespace.
    """
    cppyy.add_include_path("modules/JUCE/modules/")
    cppyy.add_include_path("modules/RTNeural/")
    cppyy.add_include_path("modules/RTNeural/modules/Eigen")
    cppyy.load_library(f"build/TorchDrumLib_artefacts/{CONFIG}/libTorchDrumLib")
    defines = __get_juce_defs(
        f"build/TorchDrumLib_artefacts/JuceLibraryCode/{CONFIG}/Defs.txt"
    )
    cppyy.cppdef(defines)
    cppyy.include("source/TorchDrumLib.h")
    return cppyy.gbl
