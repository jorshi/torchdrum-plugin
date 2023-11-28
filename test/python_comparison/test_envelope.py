import torch
from torchdrum.synth import ExpDecayEnvelope

sample_rate = 44100


def test_exponential_decay(torchdrum):
    # Generate some decay envelopes with PyTorch version
    py_decay = ExpDecayEnvelope(sample_rate)
    decay_ms = torch.tensor([50.0, 200.0, 500.0, 1000.0]).unsqueeze(-1)
    decay_raw = py_decay.normalizers["decay"].to_0to1(decay_ms)
    py_env = py_decay(sample_rate, decay_raw)

    cpp_decay = torchdrum.ExpDecayEnvelope()
    for i in range(decay_ms.shape[0]):
        # Reset the envelope and update the decay time
        cpp_decay.prepare(sample_rate)
        cpp_decay.setDecayMs(decay_ms[i].item())

        # Generate the envelope
        cpp_env = []
        cpp_decay.trigger()
        for _ in range(sample_rate):
            cpp_env.append(cpp_decay.process())

        cpp_env = torch.tensor(cpp_env)
        assert torch.allclose(py_env[i], cpp_env, atol=0.0001)
