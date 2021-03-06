#include "stdafx.h"
#include "MathFunc.h"

double mfnc::Sigmoid(const double& x)
{
	double expValue = exp(-alpha * x);
	double sig = 1 / (1 + expValue);
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
	double rel = max(0.0, x);
	return rel;
}

double mfnc::ReluDeriv(const double& x)
{
	return (x < 0.0) ? 0.0 : 1.0;
}

double mfnc::Identity(const double& x)
{
	return x;
}
double mfnc::IdentityDeriv(const double& x)
{
	return 1.0;
}

/* Random double number generator using the old C++ way */
double mfnc::CreateRandomNumber(const double& dMin, const double& dMax)
{
	double f = (double)rand() / RAND_MAX;
	return f * (dMax - dMin) + dMin;
}