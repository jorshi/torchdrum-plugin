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
