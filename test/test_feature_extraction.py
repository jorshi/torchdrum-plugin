import numpy as np
import pytest


@pytest.fixture
def controller(torchdrum):
    synth = torchdrum.DrumSynth()
    sc = torchdrum.SynthController(synth)
    yield sc
    synth.getParameters().freeParameters()


SR = 48000


def test_feature_extraction_init(torchdrum):
    fe = torchdrum.FeatureExtraction()
    assert isinstance(fe, torchdrum.FeatureExtraction)


def test_feature_extraction_prepare(torchdrum):
    fe = torchdrum.FeatureExtraction()
    fe.prepare(SR, 512, 256)
    assert fe.getSampleRate() == SR
    assert fe.getFrameSize() == 512
    assert fe.getHopSize() == 256


def test_feature_extraction_process(torchdrum, controller):
    buffer = controller.getFeatureBuffer()
    buffer.setSize(1, 512)

    results = torchdrum.FeatureExtractionResults()

    extractor = torchdrum.FeatureExtraction()
    extractor.prepare(SR, 512, 256)

    # Set the buffer to all zeros
    for i in range(buffer.getNumSamples()):
        buffer.setSample(0, i, 0.0)

    extractor.process(buffer, results)
    assert results.rmsMean == -80.0

    # Set the buffer to all ones
    for i in range(buffer.getNumSamples()):
        buffer.setSample(0, i, 1.0)

    extractor.process(buffer, results)
    assert np.isclose(results.rmsMean, -0.0, atol=1e-6)
