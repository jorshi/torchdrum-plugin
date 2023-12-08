import numpy as np
import pytest


@pytest.fixture
def controller(torchdrum):
    synth = torchdrum.DrumSynth()
    parameters = torchdrum.Parameters()
    sc = torchdrum.SynthController(synth, parameters)
    yield sc
    synth.getParameters().freeParameters()
    parameters.freeParameters()
    sc.__destruct__()


def test_synth_controller_init(controller, torchdrum):
    assert isinstance(controller, torchdrum.SynthController)


def test_synth_controller_process(controller):
    controller.prepare(44100.0, 512)

    # Run random samples through the synth controller
    x = np.random.rand(512)
    for i in range(len(x)):
        controller.process(x[i])


def test_synth_controller_buffer(controller, torchdrum):
    controller.prepare(44100.0, 512)

    buffer_size = torchdrum.ONSET_BUFFER_SIZE
    silence = np.zeros(buffer_size)

    # Verify that the buffer is the correct size and initialized to zeros
    buffer = controller.getBuffer()
    assert buffer.getNumSamples() == buffer_size

    x = buffer.getReadPointer(0, 0)
    for i in range(buffer_size):
        assert x[i] == 0.0

    # Run zeros through the controller and verify that the buffer is still zeros
    for i in range(buffer_size):
        controller.process(silence[i])

    for i in range(buffer_size):
        assert x[i] == 0.0

    # Now run some random samples through the controller
    random = np.random.rand(buffer_size)
    for i in range(buffer_size):
        controller.process(float(random[i]))

    # Verify that the buffer contains the random samples
    for i in range(buffer_size):
        assert np.isclose(x[i], float(random[i]))


def test_controller_onset_trigger(controller, torchdrum):
    controller.prepare(44100.0, 512)

    # Create a signal with silence and then an onset
    silence = np.zeros(100)
    w0 = 1000.0 * 2.0 * np.pi / 44100.0
    sin = np.sin(w0 * np.arange(1000))

    # Confirm that there is no onset for the silence
    for i in range(len(silence)):
        controller.process(silence[i])
        assert not controller.getIsOnset()

    # Confirm that we get an onset within a few samples of the sine wave
    # and that the onset flag is false after ONSET_WINDOW_SIZE samples
    for i in range(5):
        controller.process(sin[i])
        if controller.getIsOnset():
            start = i + 1
            break

    assert controller.getIsOnset()

    for i in range(start, start + torchdrum.ONSET_WINDOW_SIZE + 1):
        controller.process(sin[i])

    assert not controller.getIsOnset()
