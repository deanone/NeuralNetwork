#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include "Neuron.h"

class Layer
{
	//int id;
	std::vector<Neuron*> neurons;
	int numOfNeurons;
	int activationFuncType;
public:
	Layer(int numOfNeurons_, int numOfWeights_, int activationFuncType_);
	~Layer();
	//int GetId() const { return id; }
	int GetNumOfNeurons() const { return numOfNeurons; }
	Neuron* GetNeuron(int neuron_id);
	auto GetNeurons() { return &neurons; }
	void ForwardPass(std::vector<double>& input);
};

#endif // !LAYER_H



