// MieScatteringCoefficients.h : main header file for the MieScatteringCoefficients DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CMieScatteringCoefficientsApp
// See MieScatteringCoefficients.cpp for the implementation of this class
//

class CMieScatteringCoefficientsApp : public CWinApp
{
public:
	CMieScatteringCoefficientsApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
