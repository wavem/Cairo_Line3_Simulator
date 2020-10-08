
// Cairo_Line3_Simulator.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCairo_Line3_SimulatorApp:
// See Cairo_Line3_Simulator.cpp for the implementation of this class
//

class CCairo_Line3_SimulatorApp : public CWinApp
{
public:
	CCairo_Line3_SimulatorApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCairo_Line3_SimulatorApp theApp;