// MieAngleFunctions.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"

#include "../OriginDll/MieDll.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

// Input:
// prhs[0] == angles
// prhs[1] = NMax
//
// Output:
// plhs[0] == pi
// plhs[1] == tau
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, 
				 const mxArray *prhs[])
{
	/*
	void AngleFunctions(unsigned Nmax, double Ang, double * pi,
	double * tau);
	*/

	assert(nlhs == 2);
	assert(nrhs == 2);

	const mxArray * mx_theta = prhs[0], * mx_nmax = prhs[1];
	
	const double * theta = mxGetPr(mx_theta);
	assert(theta);

	const unsigned n_max = (unsigned)mxGetScalar(mx_nmax);
	const int n_theta = mxGetN(mx_theta);

	mxArray * mx_pi = mxCreateDoubleMatrix(n_theta, n_max, mxREAL);
	mxArray * mx_tau = mxCreateDoubleMatrix(n_theta, n_max, mxREAL);

	typedef boost::multi_array_ref<double, 2> double_matrix;
	typedef double_matrix::index_range range;

	double_matrix pi(mxGetPr(mx_pi), boost::extents[n_theta][n_max], boost::fortran_storage_order()),
		tau(mxGetPr(mx_tau), boost::extents[n_theta][n_max], boost::fortran_storage_order());

	boost::scoped_array<double> p(new double[n_max]), t(new double[n_max]);
	for(int i = 0; i < n_theta; i++)
	{
		Mie::AngleFunctions(n_max, theta[i], p.get(), t.get());
		boost::copy_n(p.get(), n_max, pi[i].begin());
		boost::copy_n(t.get(), n_max, tau[i].begin());
	}

	plhs[0] = mx_pi;
	plhs[1] = mx_tau;
}