// MieScatteringCoefficients.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "MieScatteringCoefficients.h"

#include "../OriginDll/MieDll.h"

#include <matrix.h>
#include <boost/scoped_array.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CMieScatteringCoefficientsApp

BEGIN_MESSAGE_MAP(CMieScatteringCoefficientsApp, CWinApp)
END_MESSAGE_MAP()


// CMieScatteringCoefficientsApp construction

CMieScatteringCoefficientsApp::CMieScatteringCoefficientsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CMieScatteringCoefficientsApp object

CMieScatteringCoefficientsApp theApp;


// CMieScatteringCoefficientsApp initialization

BOOL CMieScatteringCoefficientsApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

// Input:
// prhs[0] == x
// prhs[1] == m
// prhs[2] == NMax
//
// Output:
// plhs[0] == a
// plhs[1] == b
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, 
				 const mxArray *prhs[])
{
	assert(nrhs >= 2 && nrhs <= 3);
	assert(nlhs == 2);

	/*
	void ScatteringCoefficients(Complex x, Complex m, unsigned Nmax,
		Complex a[], Complex b[]);
	*/

	const mxArray * mx_x = prhs[0], * mx_m = prhs[1];

	const double * pxr = mxGetPr(mx_x), * pxi = mxGetPi(mx_x);
	assert(pxr);
	Mie::Complex x(*pxr, pxi ? *pxi : 0);

	const double * pmr = mxGetPr(mx_m), * pmi = mxGetPi(mx_m);
	assert(pmr);
	Mie::Complex m(*pmr, pmi ? *pmi : 0);

	const size_t n_max = nrhs > 2 ? (size_t)mxGetScalar(prhs[2]) : Mie::NumberOfTerms(x);
	
	boost::scoped_array<Mie::Complex> a(new Mie::Complex[n_max]), b(new Mie::Complex[n_max]);
	Mie::ScatteringCoefficients(x, m, n_max, a.get(), b.get());

	mxArray * mx_a = mxCreateDoubleMatrix(1, n_max, mxCOMPLEX);
	mxArray * mx_b = mxCreateDoubleMatrix(1, n_max, mxCOMPLEX);

	double * par = mxGetPr(mx_a), * pai = mxGetPi(mx_a), 
		* pbr = mxGetPr(mx_b), * pbi = mxGetPi(mx_b);

	for(size_t i = 0; i < n_max; i++)
	{
		par[i] = a[i].real();
		pai[i] = a[i].imag();
		pbr[i] = b[i].real();
		pbi[i] = b[i].imag();
	}

	plhs[0] = mx_a;
	plhs[1] = mx_b;
}