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

    # Create a simple model
    class Model(torch.nn.Module):
        def __init__(self):
            super().__init__()
            self.linear = torch.nn.Linear(8, 2)

        def forward(self, x):
            return self.linear(x)

    model = Model()

    model_json = {
        "in_shape": [None, None, 1],
        "layers": [
            {
                "type": "dense",
                # "activation": "tanh",
                "shape": [None, None, 2],
                "weights": [
                    [
                        [
                            0.5,
                            0.5,
                        ]
                    ],
                    [0.0, 0.0],
                ],
            }
        ],
    }

    print(model.state_dict())

    # Save the model to JSON
    save_path = tmp_path / "model.json"
    with open(save_path, "w") as json_file:
        json.dump(model_json, json_file)

    # Load the model from JSON
    nn.loadModel(str(save_path))

    cpp_model = nn.getModel()
    print(cpp_model.getOutSize())

    in_data = torchdrum.std.vector["double"]([0.25])
    out_data = torchdrum.std.vector["double"]([0.0, 0.0])
    print(out_data)
    nn.process(in_data, out_data)

    print(out_data)
