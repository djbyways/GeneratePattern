#ifndef MIEDLL_H_INCLUDED
#define MIEDLL_H_INCLUDED

#include <complex>

namespace Mie
{
	typedef std::complex<double> Complex;

	// Compute scattering amplitude coefficients S1 and S2 
	// (Bohren & Huffman, (4.74)).
	// Input: x -- refraction parameter (x=ka, where k is a wavenumber, 
	// a is a sphere radius);
	// m -- complex refractive index;
	// And -- "Theta" angle.
	// Output:
	// S1, S2 -- scattering amplitude coefficients.
	void ScatteringAmplitudeCoefficients(Complex x, Complex m,double Ang,
										Complex& S1, Complex& S2);
	void ScatteringAmplitudeCoefficients(Complex x, Complex m, const double * Theta, 
		size_t thetaSize,
		Complex S1[], Complex S2[]);

	// Compute first Nmax angle-dependent functions pi and tau for 
	// given angle Ang. Computed values are put
	// into the [0..Nmax-1] elements of arrays pi, tau, respectively.
	void AngleFunctions(unsigned Nmax, double Ang, double * pi,
				double * tau);

	// Compute Nmax coefficients in spherical
	// harmonics decomposition of scattered field for given 
	// difraction coefficient x and relative refractive index m.
	// Result is put into [0..Nmax-1] elements of arrays a and b.
	void ScatteringCoefficients(Complex x, Complex m, unsigned Nmax,
		Complex a[], Complex b[]);

	// Returns number of terms sufficient to compute scattered field
	// for given difraction parameter.
	unsigned NumberOfTerms(Complex difraction_parameter);
}

#endif 