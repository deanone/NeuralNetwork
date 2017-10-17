#include "stdafx.h"
#include "MathFunc.h"

#include <math.h>
#include <algorithm>
#include <iostream>

double mfnc::Sigmoid(const double& x)
{
	double expValue = exp(-alpha * x);
	double sig = 1 / (1 + expValue);
	//std::cout << sig << std::endl;
	return sig;
}

double mfnc::SigmoidDeriv(const double& x)
{
	double sig = Sigmoid(x);
	return alpha * sig * (1 - sig);
}

double mfnc::TanhDeriv(const double& x)
{
	double t = tanh(x);
	return 1 - pow(t, 2);
}

double mfnc::Relu(const double& x)
{
	double rel = std::max(0.0, x);
	//std::cout << rel << std::endl;
	return rel;
}

double mfnc::ReluDeriv(const double& x)
{
	if (x < 0.0)
		return 0.0;
	else
		return 1.0;
}

/* Random double number generator using the old C++ way */
double mfnc::CreateRandomNumber(const double& dMin, const double& dMax)
{
	double f = (double)rand() / RAND_MAX;
	return f * (dMax - dMin) + dMin;
}