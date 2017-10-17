#include "stdafx.h"
#include "Layer.h"


Layer::Layer(int numOfNeurons_, int numOfWeights_, int activationFuncType_) : numOfNeurons(numOfNeurons_)
{
	for (int i = 0; i < numOfNeurons; i++)
	{
		Neuron* ptr(new Neuron(numOfWeights_, activationFuncType_));
		neurons.push_back(ptr);
	}
}

Layer::~Layer()
{
	if (!neurons.empty())
	{
		for (size_t i = 0; i < neurons.size(); i++)
			delete neurons[i];
		neurons.clear();
	}
}

void Layer::ForwardPass(std::vector<double>& input)
{
	std::vector<double> output;
	output.push_back(1.0);	// for bias
	for (size_t i = 0; i < neurons.size(); i++)
	{
		neurons[i]->SetInput(input);
		neurons[i]->ComputeActivation();
		neurons[i]->ComputeOutput();
		neurons[i]->ComputeOutputDeriv();
		output.push_back(neurons[i]->GetOutput());
	}

	input.clear();
	for (size_t i = 0; i < output.size(); i++)
		input.push_back(output[i]);
	output.clear();
}

Neuron* Layer::GetNeuron(int neuron_id)
{
	if (neuron_id >= 0 && neuron_id < numOfNeurons)
		return neurons[neuron_id];
	else
		return nullptr;
}	