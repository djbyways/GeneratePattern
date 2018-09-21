#include "MieDll.h"
#include "MLTypes.h"
#include "Array.h"

extern "C" void AngleFunctions(double Ang, int Nmax)
{
	arrays::Array2d<double> af(2, Nmax);
	Mie::AngleFunctions(Nmax, Ang, af[0], af[1]);

	MathLink::PutFunction("List", 2);
	MathLink::MLPutRealList(af[0], Nmax);
	MathLink::MLPutRealList(af[1], Nmax);
}

extern "C" void AmplitudeCoefficients(double ReX, double ImX, double ReM, double ImM, const double * Theta, long thetaSize)
{
	Mie::Complex x(ReX, ImX), m(ReM, ImM);
	Mie::Complex * S1 = new Mie::Complex[thetaSize];
	Mie::Complex * S2 = new Mie::Complex[thetaSize];

	Mie::ScatteringAmplitudeCoefficients(x, m, Theta, thetaSize, S1, S2);

	MathLink::PutFunction("List", 2);
	
	MathLink::PutFunction("List", thetaSize);
	for(int i = 0; i < thetaSize; i++)
		MathLink::Put(S1[i]);

	MathLink::PutFunction("List", thetaSize);
	for(int i = 0; i < thetaSize; i++)
		MathLink::Put(S2[i]);

	/*
	std::copy(S1, S1 + thetaSize, MathLink::OutputIterator<Mie::Complex>());
	std::copy(S2, S2 + thetaSize, MathLink::OutputIterator<Mie::Complex>());
	*/

	delete[] S1;
	delete[] S2;
}

extern "C" void ScatteringCoefficients(double ReX, double ImX, double ReM, double ImM, int Nmax)
{
	Mie::Complex x(ReX, ImX), m(ReM, ImM);
	arrays::Array2d<Mie::Complex> c(2, Nmax);

	Mie::ScatteringCoefficients(x, m, Nmax, c[0], c[1]);

	MathLink::PutFunction("List", 2);
	
	MathLink::PutFunction("List", c.dim2());
	for(unsigned i = 0; i < c.dim2(); i++)
		MathLink::Put(c[0][i]);

	MathLink::PutFunction("List", c.dim2());
	for(unsigned i = 0; i < c.dim2(); i++)
		MathLink::Put(c[1][i]);
}