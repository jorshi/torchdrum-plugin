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
