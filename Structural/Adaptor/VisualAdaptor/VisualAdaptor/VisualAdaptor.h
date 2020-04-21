
// VisualAdaptor.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CVisualAdaptorApp:
// See VisualAdaptor.cpp for the implementation of this class
//

class CVisualAdaptorApp : public CWinApp
{
public:
	CVisualAdaptorApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CVisualAdaptorApp theApp;