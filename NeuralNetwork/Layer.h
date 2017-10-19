#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include "Neuron.h"

class Layer
{
	std::vector<Neuron*> neurons;	// at this point I use raw pointers and manage memory myself. In future versions, I will use smart pointers.
	int numOfNeurons;
	int activationFuncType;

public:
	Layer(int numOfNeurons_, int numOfWeights_, int activationFuncType_);
	~Layer();

	int GetNumOfNeurons() const { return numOfNeurons; }
	Neuron* GetNeuron(int neuronId);
	auto GetNeurons() { return &neurons; }
	void ForwardPass(std::vector<double>& input);
};

#endif // !LAYER_H



