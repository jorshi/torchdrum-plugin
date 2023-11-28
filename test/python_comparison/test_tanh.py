import torch
from torchdrum.synth import Tanh

sample_rate = 44100


def test_tanh(torchdrum):
    cpp_tanh = torchdrum.Tanh()
    py_tanh = Tanh(sample_rate)

    batch_size = 10
    num_samples = 1024
    params = torch.linspace(0.0, 1.0, batch_size).unsqueeze(-1)
    db_params = py_tanh.normalizers["in_gain"].from_0to1(params)

    # Generate random input
    x = torch.rand(batch_size, num_samples) * 2.0 - 1.0

    py_out = py_tanh(x, params)
    cpp_out = torch.zeros_like(py_out)

    for i in range(batch_size):
        cpp_tanh.setGainDecibels(db_params[i].item())
        for j in range(num_samples):
            cpp_out[i, j] = cpp_tanh.process(x[i, j].item())

    assert torch.allclose(py_out, cpp_out)
