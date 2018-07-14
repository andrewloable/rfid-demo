// RFRM.h : main header file for the RFRM application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif
#ifdef POCKETPC2003_UI_MODEL
#include "resourceppc.h"
#endif 
#ifdef SMARTPHONE2003_UI_MODEL
#include "resourcesp.h"
#endif

// CRFRMApp:
// See RFRM.cpp for the implementation of this class
//

class CRFRMApp : public CWinApp
{
public:
	CRFRMApp();
	inline HINSTANCE GetResourceInstance();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
public:
#ifndef WIN32_PLATFORM_WFSP
	afx_msg void OnAppAbout();
#endif // !WIN32_PLATFORM_WFSP

// Attribute
protected:
	HINSTANCE m_hInstDLL;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CRFRMApp theApp;

inline HINSTANCE CRFRMApp::GetResourceInstance()
{
	return m_hInstDLL;
}