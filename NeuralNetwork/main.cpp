#include "stdafx.h"
#include "NeuralNetwork.h"
#include "GenericFunc.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main()
{
	std::string nnConfigFilename = gnfnc::GetExecutablePathAndMatchItWithFilename("nn.properties");
	std::string trainDataFilename = gnfnc::GetExecutablePathAndMatchItWithFilename("train.csv");
	std::string testDataFilename = gnfnc::GetExecutablePathAndMatchItWithFilename("test.csv");
	srand(time(NULL));
	NeuralNetwork MLP(nnConfigFilename);
	MLP.Build();
	MLP.Train(trainDataFilename);
	//MLP.PrintWeights();
	MLP.Run(testDataFilename);
	return 0;
}