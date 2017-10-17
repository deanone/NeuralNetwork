#ifndef MATHFUNC_H
#define MATHFUNC_H

namespace mfnc
{
	constexpr double alpha = 1e-08;

	double Sigmoid(const double& x);
	double SigmoidDeriv(const double& x);
	double TanhDeriv(const double& x);
	// rectifier linear unit
	double Relu(const double& x);
	double ReluDeriv(const double& x);
	double CreateRandomNumber(const double& dMin, const double& dMax);
}

#endif // !MATHFUNC_H

