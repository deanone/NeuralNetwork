#ifndef NEURAL_NETWORK_H

#include <map>
#include <vector>
#include "Layer.h"

class NeuralNetwork
{
	int numOfLayers;
	int numberOfIntermediateHiddenLayers;
	int	numberOfNeuronsPerLayer;
	int	numberOfInputs;
	int activationFuncTypeHiddenLayers;
	int activationFuncTypeOuputLayer;
	double learningRate;
	std::vector<Layer*> layers;
	double target;
public:
	NeuralNetwork(std::string nnConfigFilename);
	~NeuralNetwork();

	Layer* GetLayer(int layer_id);
	double ComputeDelta(int layer_id, int neuron_id, int weight_id);
	double ComputeWeightUpdate(int layer_id, int neuron_id, int weight_id);
	void Build();
	void Train(std::string trainDataFilename);
	void Run(std::string testDataFilename);
	void PrintWeights();
};
#endif	// NEURAL_NETWORK_H
