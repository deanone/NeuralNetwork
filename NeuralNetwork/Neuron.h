#ifndef NEURON_H
#define NEURON_H

#include <vector>
#include <numeric>

class Neuron
{
	//int id;
	std::vector<double> input;
	std::vector<double> weights;
	std::vector<double> weightsUpdates;
	double activation;
	double output;
	double outputDeriv;
	int numOfWeights;
	int activationFuncType;
public:
	Neuron(int numOfWeights_, int activationFuncType_);
	~Neuron();
	//int GetId() const { return id; }
	void SetInput(const std::vector<double>& input_);
	void ComputeActivation();
	void ComputeOutput();
	void ComputeOutputDeriv();
	double GetOutput() const { return output; }
	double GetWeight(int weight_id);
	double GetInput(int input_id);
	double GetNumOfWeights() const { return numOfWeights; }
	void AddWeightUpdate(int weight_id, double weightUpdate);
	void UpdateWeights();
	void Clear();
	void PrintWeights();
};

#endif // !NEURON_H
