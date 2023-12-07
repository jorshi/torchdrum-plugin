import torch

SR = 48000


def test_spectral_extractor_init(torchdrum):
    extractor = torchdrum.SpectralExtractor()
    assert isinstance(extractor, torchdrum.SpectralExtractor)


def test_spectral_extractor_prepare(torchdrum):
    extractor = torchdrum.SpectralExtractor()

    fft_size = 256
    extractor.prepare(SR, fft_size)

    assert extractor.getSampleRate() == SR

    fft = extractor.getFFT()
    assert fft.getSize() == fft_size
    assert extractor.getFFTBuffer().size() == fft_size

    # Confirm the window function is set
    window = extractor.getFFTWindow()
    assert window.size() == fft_size

    # Compare to the window from torch
    torch_window = torch.hann_window(fft_size, periodic=False)
    window = torch.tensor(window)
    assert torch.allclose(window, torch_window, atol=1e-4)
