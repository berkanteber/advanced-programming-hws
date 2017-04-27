
// berkanteber_Teber_Berkan_HW8.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cberkanteber_Teber_Berkan_HW8App:
// See berkanteber_Teber_Berkan_HW8.cpp for the implementation of this class
//

class Cberkanteber_Teber_Berkan_HW8App : public CWinApp
{
public:
	Cberkanteber_Teber_Berkan_HW8App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cberkanteber_Teber_Berkan_HW8App theApp;