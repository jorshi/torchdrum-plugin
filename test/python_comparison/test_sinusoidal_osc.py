import torch
from einops import repeat
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


def test_sinusoidal_osc_with_modulation(torchdrum):
    # Generate oscillations with PyTorch version
    py_osc = SinusoidalOscillator(sample_rate)

    freq_hz = torch.tensor([50.0, 100.0, 1000.0]).unsqueeze(-1)
    freq_raw = py_osc.normalizers["freq"].to_0to1(freq_hz)

    mod_amount = torch.tensor([-0.5, 2.0, 1.0]).unsqueeze(-1)
    mod_raw = py_osc.normalizers["mod"].to_0to1(mod_amount)

    # Linear mod_env
    num_samples = 1024
    mod_env = torch.linspace(0.0, 1.0, num_samples)
    mod_env = repeat(mod_env, "n -> b n", b=freq_hz.shape[0])

    py_out = py_osc(num_samples, freq_raw, mod_env, mod_raw)

    # Compare against the plugin
    cpp_osc = torchdrum.SinusoidalOscillator()
    cpp_out = torch.zeros_like(py_out)
    for i, f in enumerate(freq_hz):
        cpp_osc.prepare(sample_rate)
        cpp_osc.setFrequencyHz(f.item())
        cpp_osc.setModAmount(mod_amount[i].item())

        for j in range(num_samples):
            y = cpp_osc.process(mod_env[i, j].item())
            cpp_out[i, j] = y

    # Need to use a slightly higher tolerance here
    # (seems to more prone to numerical errors)
    torch.testing.assert_close(py_out, cpp_out, atol=1e-4, rtol=1e-4)
