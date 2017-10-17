#include "stdafx.h"
#include "NeuralNetwork.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main()
{
	std::string nnConfigFilename = "C:\\Users\\thana\\Desktop\\nn.properties";
	std::string trainDataFilename = "C:\\Users\\thana\\Desktop\\wine_train.csv";
	std::string testDataFilename = "C:\\Users\\thana\\Desktop\\wine_test.csv";
	srand(time(NULL));
	NeuralNetwork MLP(nnConfigFilename);
	MLP.Build();
	MLP.Train(trainDataFilename);
	//MLP.PrintWeights();
	MLP.Run(testDataFilename);
	return 0;
}