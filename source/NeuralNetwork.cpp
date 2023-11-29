#include "NeuralNetwork.h"

void NeuralNetwork::loadModel(const std::string& path)
{
    std::ifstream jsonStream(path, std::ifstream::binary);
    model = RTNeural::json_parser::parseJson<double>(jsonStream);
    model->reset();
}

void NeuralNetwork::process(const std::vector<double>& input, std::vector<double>& output)
{
    if (model == nullptr)
        return;

    model->forward(input.data());
    auto* outs = model->getOutputs();

    for (int i = 0; i < model->getOutSize(); ++i)
        output[i] = outs[i];
}
