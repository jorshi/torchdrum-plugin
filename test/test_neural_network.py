import json
from json import JSONEncoder

import torch
from torch.utils.data import Dataset


class EncodeTensor(JSONEncoder, Dataset):
    def default(self, obj):
        if isinstance(obj, torch.Tensor):
            return obj.cpu().detach().numpy().tolist()
        return super(json.NpEncoder, self).default(obj)


def test_neural_network_init(torchdrum):
    nn = torchdrum.NeuralNetwork()
    assert isinstance(nn, torchdrum.NeuralNetwork)


def test_neural_network_load_model(torchdrum, tmp_path):
    nn = torchdrum.NeuralNetwork()
    assert isinstance(nn, torchdrum.NeuralNetwork)
