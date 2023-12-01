import numpy as np


def test_feature_value_init_double(torchdrum):
    fv = torchdrum.FeatureValue["double"]()
    assert isinstance(fv, torchdrum.FeatureValue["double"])


def test_feature_value_init_float(torchdrum):
    fv = torchdrum.FeatureValue["float"]()
    assert isinstance(fv, torchdrum.FeatureValue["float"])


def test_feature_value_set_once_get_normalized_no_update(torchdrum):
    fv = torchdrum.FeatureValue["float"]()
    fv.set(10.0)

    # Getting the normalized value without updating the minmax range
    # will return a value of 0.5
    assert fv.getNormalized() == 0.5


def test_feature_value_set_get_normalized(torchdrum):
    fv = torchdrum.FeatureValue["float"]()
    fv.set(10.0, True)

    # Getting the normalized value after an initial set will return
    # a value of 0.5 since there is only one value in the minmax range
    assert fv.getNormalized() == 0.5

    # A second value means that the minmax range will now have two values for norm
    fv.set(5.0, True)
    assert fv.getNormalized() == 0.0

    fv.set(20.0, True)
    assert fv.getNormalized() == 1.0

    fv.set(10.0, True)
    assert np.isclose(fv.getNormalized(), (10.0 - 5.0) / (20.0 - 5.0))

    fv.set(-10.0, True)
    assert fv.getNormalized() == 0.0

    fv.set(5.0, True)
    assert fv.getNormalized() == (5.0 - -10.0) / (20.0 - -10.0)


def test_feature_value_set_get_normalized_no_update(torchdrum):
    fv = torchdrum.FeatureValue["float"]()

    # The first value will set minmax and will return 0.5
    fv.set(25.0, True)
    assert fv.getNormalized() == 0.5

    fv.set(10.0, True)
    assert fv.getNormalized() == 0.0

    # Now that the minmax range is set, calling getNormalized without updating
    # will use the stored minmax range and a value outside of the range will
    # be clamped to 0.0 or 1.0
    fv.set(30.0)
    assert fv.getNormalized() == 1.0

    fv.set(5.0)
    assert fv.getNormalized() == 0.0

    fv.set(15.0)
    assert np.isclose(fv.getNormalized(), (15.0 - 10.0) / (25.0 - 10.0))


def test_feature_value_reset(torchdrum):
    fv = torchdrum.FeatureValue["float"]()

    # The first value will set minmax and will return 0.5
    fv.set(20.0, True)
    assert fv.getNormalized() == 0.5

    fv.set(10.0, True)
    assert fv.getNormalized() == 0.0

    # Reset
    fv.reset()
    fv.set(10.0)
    assert fv.getNormalized() == 0.5

    fv.set(20.0)
    assert fv.getNormalized() == 0.5


def test_feature_value_set_min_max(torchdrum):
    fv = torchdrum.FeatureValue["float"]()

    fv.setMinMax(100.0, 200.0)

    fv.set(110.0)
    assert np.isclose(fv.getNormalized(), 0.1)

    fv.set(120.0)
    assert np.isclose(fv.getNormalized(), 0.2)


def test_feature_get_min_max_double(torchdrum):
    fv = torchdrum.FeatureValue["float"]()

    x = fv.getMinMax()
    assert x[0] == np.finfo(np.float32).max
    assert x[1] == np.finfo(np.float32).min

    fv.set(-10.0, True)
    x = fv.getMinMax()
    assert x[0] == -10.0
    assert x[1] == -10.0

    fv.set(20.0, True)
    x = fv.getMinMax()
    assert x[0] == -10.0
    assert x[1] == 20.0
