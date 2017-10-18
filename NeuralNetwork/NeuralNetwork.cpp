#include "stdafx.h"
#include "NeuralNetwork.h"
#include "PropertiesParser.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//int CountNumberOfLinesInFile(std::string filename)
//{
//	int numberOfLines = 0;
//	// filename = path + "/" + filename;
//	std::string dataline = "";
//	std::ifstream in(filename.c_str());
//	if (in.is_open())
//	{
//		while (std::getline(in, dataline))
//			numberOfLines++;
//		in.close();
//	}
//	return numberOfLines;
//}

NeuralNetwork::NeuralNetwork(std::string nnConfigFilename) : target(-1.0)
{
	PropertiesParser pp(nnConfigFilename);
	numberOfIntermediateHiddenLayers = pp.GetPropertyAsInt("numberOfIntermediateHiddenLayers");
	numberOfNeuronsPerLayer = pp.GetPropertyAsInt("numberOfNeuronsPerLayer");
	numberOfInputs = pp.GetPropertyAsInt("numberOfInputs");
	learningRate = pp.GetPropertyAsDouble("learningRate");
	activationFuncTypeHiddenLayers = pp.GetPropertyAsInt("activationFuncTypeHiddenLayers");
	activationFuncTypeOuputLayer = pp.GetPropertyAsInt("activationFuncTypeOuputLayer");
	numOfLayers = numberOfIntermediateHiddenLayers + 2;
}

NeuralNetwork::~NeuralNetwork()
{
	if (!layers.empty())
	{
		for (size_t i = 0; i < layers.size(); i++)
			delete layers[i];
		layers.clear();
	}
}

void NeuralNetwork::Build()
{
	// First hidden layer
	Layer* layerPtr = new Layer(numberOfNeuronsPerLayer, numberOfInputs + 1, activationFuncTypeHiddenLayers);
	layers.push_back(layerPtr);

	// Intermediate hidden layers
	for (size_t i = 0; i < numberOfIntermediateHiddenLayers; i++)
	{
		Layer* layerPtr = new Layer(numberOfNeuronsPerLayer, numberOfNeuronsPerLayer + 1, activationFuncTypeHiddenLayers);
		layers.push_back(layerPtr);
	}

	// Output layer
	Layer* outputlayerPtr = new Layer(1, numberOfNeuronsPerLayer + 1, activationFuncTypeOuputLayer);
	layers.push_back(outputlayerPtr);

	//PrintWeights();
	//std::cout << std::endl;
	//std::cout << std::endl;
}

Layer* NeuralNetwork::GetLayer(int layer_id)
{
	if (layer_id >= 0 && layer_id < numOfLayers)
		return layers[layer_id];
	else
		return nullptr;
}

double NeuralNetwork::ComputeDelta(int layer_id, int neuron_id, int weight_id)
{
	double delta = -1.0;
	if (layer_id == (numOfLayers - 1))	// for output neurons
	{
		double output = GetLayer(layer_id)->GetNeuron(neuron_id)->GetOutput();
		delta = (output - static_cast<double>(target)) * output * (1 - output);
	}
	else // for hidden neurons
	{
		delta = 0.0;
		auto neurons = GetLayer(layer_id + 1)->GetNeurons();
		for (size_t i = 0; i < neurons->size(); i++)
			delta += ComputeDelta(layer_id + 1, i, weight_id) * neurons->at(i)->GetWeight(weight_id);
	}
	return delta;
}

double NeuralNetwork::ComputeWeightUpdate(int layer_id, int neuron_id, int weight_id)
{
	double delta = ComputeDelta(layer_id, neuron_id, weight_id);
	double input = GetLayer(layer_id)->GetNeuron(neuron_id)->GetInput(weight_id);
	double weightUpdate = (-1.0) * learningRate * input * delta;
	return weightUpdate;
}

void NeuralNetwork::Train(std::string trainDataFilename) 
{
	std::string dataline = "";
	std::ifstream in(trainDataFilename);
	if (in.is_open())
	{
		//std::cout << "Training the neural network...\n";
		while (std::getline(in, dataline))	// for each observation
		{
			//std::cout << "Constructing training vector...\n";
			// Read line
			std::istringstream ss(dataline);
			std::string item;
			std::vector<std::string> items;
			while (std::getline(ss, item, ','))
				items.push_back(item);

			// Transform string line to double training vector
			std::vector<double> trainingVector;
			trainingVector.push_back(1.0);	// bias input
			for (size_t i = 0; i < (items.size() - 1); i++)
				trainingVector.push_back(stod(items[i]));
			target = stod(items[items.size() - 1]);
			items.clear();

//############################################################################# Training ###############################################################################################

			// forward pass
			//std::cout << "Forward pass...\n";
			int layer_id = 0;
			size_t neuron_id = -1;
			size_t weight_id = -1;
			for (; layer_id < numOfLayers; layer_id++)
				layers[layer_id]->ForwardPass(trainingVector);

			// backwards pass
			//std::cout << "Backwards pass...\n";
			layer_id = (numOfLayers - 1);
			for (; layer_id >= 0; layer_id--)
			{
				neuron_id = 0;
				Layer* layer = GetLayer(layer_id);
				int numOfNeuronsInLayer = layer->GetNumOfNeurons();
				for (; neuron_id < numOfNeuronsInLayer; neuron_id++)
				{
					weight_id = 0;
					Neuron* neuron = layer->GetNeuron(neuron_id);
					int numOfWeights = neuron->GetNumOfWeights();
					for (; weight_id < numOfWeights; weight_id++)
					{
						double weightUpdate = ComputeWeightUpdate(layer_id, neuron_id, weight_id);
						neuron->AddWeightUpdate(weight_id, weightUpdate);
					}
				}
			}

			// update weights and clear input and weightsUpdates vectors to be ready for the next observation
			//std::cout << "Updating weights...\n";
			layer_id = 0;
			for (; layer_id < numOfLayers; layer_id++)
			{
				Layer* layer = GetLayer(layer_id);
				int numOfNeuronsInLayer = layer->GetNumOfNeurons();
				neuron_id = 0;
				for (; neuron_id < numOfNeuronsInLayer; neuron_id++)
				{
					Neuron* neuron = layer->GetNeuron(neuron_id);
					neuron->UpdateWeights();
					neuron->Clear();
				}
			}

//############################################################################# End of Training ###############################################################################################
		}
		in.close();
		//std::cout << "Neural network trained.\n";
	}
}

void NeuralNetwork::PrintWeights()
{
	int layer_id = 0;
	int neuron_id = -1;
	int weight_id = -1;
	for (; layer_id < numOfLayers; layer_id++)
	{
		Layer* layer = GetLayer(layer_id);
		int numOfNeuronsInLayer = layer->GetNumOfNeurons();
		neuron_id = 0;
		for (; neuron_id < numOfNeuronsInLayer; neuron_id++)
		{
			std::cout << layer_id << "," << neuron_id << ",";
			Neuron* neuron = layer->GetNeuron(neuron_id);
			neuron->PrintWeights();
		}
	}

}

void NeuralNetwork::Run(std::string testDataFilename)
{
	std::string dataline = "";
	std::ifstream in(testDataFilename);
	if (in.is_open())
	{
		//std::cout << "Predicting...\n";
		while (std::getline(in, dataline))	// for each observation
		{
			// Read line
			std::istringstream ss(dataline);
			std::string item;
			std::vector<std::string> items;
			while (std::getline(ss, item, ','))
				items.push_back(item);

			// Transform string line to double test vector
			std::vector<double> testVector;
			testVector.push_back(1.0);
			for (size_t i = 0; i < (items.size() - 1); i++)
				testVector.push_back(stod(items[i]));
			target = stod(items[items.size() - 1]);
			items.clear();

			int layer_id = 0;
			for (; layer_id < numOfLayers; layer_id++)
				layers[layer_id]->ForwardPass(testVector);

			double output = GetLayer(numOfLayers - 1)->GetNeuron(0)->GetOutput();
			
			std::cout << target << " " << output << std::endl;

		}
		in.close();
	}
}