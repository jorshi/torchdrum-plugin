def test_faeture_extraction_init(torchdrum):
    fe = torchdrum.FeatureExtraction()
    assert isinstance(fe, torchdrum.FeatureExtraction)
