#ifndef MATHFUNC_H
#define MATHFUNC_H

namespace mfnc
{
	// Constants
	constexpr double alpha = 1e-08;

	// Functions
	double Sigmoid(const double& x);
	double SigmoidDeriv(const double& x);

	double TanhDeriv(const double& x);

	double Relu(const double& x);	// rectifier linear unit
	double ReluDeriv(const double& x);

	double Identity(const double& x);
	double IdentityDeriv(const double& x);

	double CreateRandomNumber(const double& dMin, const double& dMax);
}

#endif // !MATHFUNC_H

