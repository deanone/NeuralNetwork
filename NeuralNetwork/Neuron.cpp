#include "stdafx.h"
#include "Neuron.h"
#include "MathFunc.h"

#include <stdlib.h>     /* srand, rand */
#include <iostream>

Neuron::Neuron(int numOfWeights_, int activationFuncType_) : numOfWeights(numOfWeights_), activation(-1.0), output(-1.0), outputDeriv(-1.0), activationFuncType(activationFuncType_)
{
	weights.assign(numOfWeights, mfnc::CreateRandomNumber(0, 1));	// the initial value of the weights is the same for all the weights
	weightsUpdates.assign(numOfWeights, 0.0);
	input.assign(numOfWeights, 0.0);
}

Neuron::~Neuron() 
{
	if (!weights.empty()) weights.clear();
	if (!weightsUpdates.empty()) weightsUpdates.clear();
	if (!input.empty()) input.clear();
}

void Neuron::SetInput(const std::vector<double>& input_)
{
	for (size_t i = 0; i < input_.size(); i++)
		input[i] = input_[i];
}

void Neuron::ComputeActivation()
{
	activation = std::inner_product(std::begin(weights), std::end(weights), std::begin(input), 0.0);
}

void Neuron::ComputeOutput()
{ 
	switch (activationFuncType)
	{
		case 1:
			output = mfnc::Sigmoid(activation);
			break;
		case 2:
			output = tanh(activation);
			break;
		case 3:
			output = mfnc::Relu(activation);
			break;
		default:
			break;
	}
}

void Neuron::ComputeOutputDeriv()
{
	switch (activationFuncType)
	{
		case 1:
			outputDeriv = mfnc::SigmoidDeriv(activation);
			break;
		case 2:
			outputDeriv = mfnc::TanhDeriv(activation);
			break;
		case 3:
			outputDeriv = mfnc::ReluDeriv(activation);
			break;
		default:
			break;
	}
}

double Neuron::GetWeight(int weight_id)
{
	if (weight_id >= 0 && weight_id < numOfWeights)
		return weights[weight_id];
	else
		return -1.0;
}

double Neuron::GetInput(int input_id)
{
	if (input_id >= 0 && input_id < numOfWeights)
		return input[input_id];
	else
		return -1.0;
}

void Neuron::AddWeightUpdate(int weight_id, double weightUpdate)
{
	if (weight_id >= 0 && weight_id < numOfWeights)
		weightsUpdates[weight_id] = weightUpdate;
}

void Neuron::UpdateWeights()
{
	for (size_t weight_id = 0; weight_id < numOfWeights; weight_id++)
		weights[weight_id] += weightsUpdates[weight_id];
}

void Neuron::Clear()
{
	for (size_t weight_id = 0; weight_id < numOfWeights; weight_id++)
	{
		weightsUpdates[weight_id] = 0.0;
		input[weight_id] = 0.0;
	}

	activation = -1.0;
	output = -1.0;
	outputDeriv = -1.0;
}

void Neuron::PrintWeights()
{
	size_t weight_id = 0;
	for (; weight_id < numOfWeights; weight_id++)
	{
		std::cout << weights[weight_id];
		if (weight_id != (numOfWeights - 1))
			std::cout << ",";
	}
	std::cout << std::endl;
}