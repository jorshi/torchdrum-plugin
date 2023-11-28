import torch
from torchdrum.synth import SinusoidalOscillator

sample_rate = 44100


def test_sinusoidal_osc(torchdrum):
    # Generate oscillations with PyTorch version
    py_osc = SinusoidalOscillator(sample_rate)
    freq_hz = torch.tensor([50.0, 100.0, 1000.0]).unsqueeze(-1)
    freq_raw = py_osc.normalizers["freq"].to_0to1(freq_hz)
    mod_amount = torch.zeros_like(freq_raw)
    mod_raw = py_osc.normalizers["mod"].to_0to1(mod_amount)

    # Zero mod_env
    num_samples = 1024
    mod_env = torch.zeros(1, num_samples)

    py_out = py_osc(num_samples, freq_raw, mod_env, mod_raw)

    # Test the plugin version
    cpp_osc = torchdrum.SinusoidalOscillator()
    for i, f in enumerate(freq_hz):
        cpp_osc.prepare(sample_rate)
        cpp_osc.setFrequencyHz(f.item())
        cpp_out = []
        for _ in range(num_samples):
            cpp_out.append(cpp_osc.process())

        cpp_out = torch.tensor(cpp_out)
        torch.testing.assert_close(py_out[i], cpp_out)
