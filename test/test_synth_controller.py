import numpy as np


def test_synth_controller_init(torchdrum):
    sc = torchdrum.SynthController()
    assert isinstance(sc, torchdrum.SynthController)


def test_synth_controller_process(torchdrum):
    sc = torchdrum.SynthController()
    sc.prepare(44100.0, 512)

    # Run random samples through the synth controller
    x = np.random.rand(512)
    for i in range(len(x)):
        sc.process(x[i])


def test_synth_controller_buffer(torchdrum):
    sc = torchdrum.SynthController()
    sc.prepare(44100.0, 512)

    buffer_size = torchdrum.ONSET_BUFFER_SIZE
    silence = np.zeros(buffer_size)

    # Verify that the buffer is the correct size and initialized to zeros
    buffer = sc.getBuffer()
    assert buffer.getNumSamples() == buffer_size

    x = buffer.getReadPointer(0, 0)
    for i in range(buffer_size):
        assert x[i] == 0.0

    # Run zeros through the controller and verify that the buffer is still zeros
    for i in range(buffer_size):
        sc.process(silence[i])

    for i in range(buffer_size):
        assert x[i] == 0.0

    # Now run some random samples through the controller
    random = np.random.rand(buffer_size)
    for i in range(buffer_size):
        sc.process(float(random[i]))

    # Verify that the buffer contains the random samples
    for i in range(buffer_size):
        assert np.isclose(x[i], float(random[i]))
