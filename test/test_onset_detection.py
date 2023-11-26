import numpy as np

def test_onset_detection_init(torchdrum):
    od = torchdrum.OnsetDetection()
    od.prepare(44100)

def test_onset_detection_envelope(torchdrum):
    sr = 44100
    od = torchdrum.OnsetDetection()
    od.prepare(sr)

    # Confirm that the onset signal starts at 0.0
    # and stays at zero for a silent signal
    silence = np.zeros(1000)
    for i in range(len(silence)):
        y = od.onsetSignal(silence[i])
        assert y == 0.0

    # Now, create a sinusoidal signal above 600Hz and confirm
    # that the onset signal changes
    w0 = 2 * np.pi * 1000.0 / sr
    t = np.arange(100)
    x = np.sin(w0 * t)

    for i in range(len(x)):
        y = od.onsetSignal(x[i])
        if i == 0:
            assert y == 0.0
        else:
            assert y > 0.0

def test_onset_detection_process(torchdrum):
    sr = 44100
    od = torchdrum.OnsetDetection()
    od.prepare(sr)
    od.updateParameters(16.0, 4.66, 1000)
