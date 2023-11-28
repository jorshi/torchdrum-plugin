import torch
from torchdrum.synth import Gain

sample_rate = 44100


def test_gain(torchdrum):
    py_gain = Gain(sample_rate)
    cpp_gain = torchdrum.Gain()

    batch_size = 10
    num_samples = 1024

    params = torch.linspace(0.0, 1.0, batch_size).unsqueeze(-1)
    db_params = py_gain.normalizers["gain"].from_0to1(params)

    # Generate random input
    x = torch.rand(batch_size, num_samples) * 2.0 - 1.0

    py_out = py_gain(x, params)
    cpp_out = torch.zeros_like(py_out)
    for i in range(batch_size):
        cpp_gain.setGainDecibels(db_params[i].item())
        for j in range(num_samples):
            cpp_out[i, j] = cpp_gain.process(x[i, j].item())

    assert torch.allclose(py_out, cpp_out)
