import pytest


@pytest.fixture
def drumsynth(torchdrum):
    synth = torchdrum.DrumSynth()
    yield synth
    synth.getParameters().freeParameters()


def test_drum_synth_init(drumsynth, torchdrum):
    assert isinstance(drumsynth, torchdrum.DrumSynth)
