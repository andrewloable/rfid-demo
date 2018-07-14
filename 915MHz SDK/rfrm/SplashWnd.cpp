// SplashWnd.cpp : implementation file
//
// ?998-2001 Codejock Software, All Rights Reserved.
// Based on the Visual C++ splash screen component.
//
// support@codejock.com
// http://www.codejock.com
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SplashWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

namespace techwin
{
	/////////////////////////////////////////////////////////////////////////////
	//   Splash Screen class

	BOOL        CSplashWnd::m_bShowSplashWnd;
	CSplashWnd* CSplashWnd::m_pSplashWnd;

	CSplashWnd::CSplashWnd()
	{
	}

	CSplashWnd::~CSplashWnd()
	{
		// Clear the static window pointer.
		ASSERT(m_pSplashWnd == this);
		m_pSplashWnd = NULL;
	}

	BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
		//{{AFX_MSG_MAP(CSplashWnd)
		ON_WM_PAINT()
		ON_WM_TIMER()
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

	void CSplashWnd::EnableSplashScreen(BOOL bEnable /*= TRUE*/)
	{
/*
#ifdef WINCE
		CIOControl ioControl;

		if(!ioControl.GetControlState(RFID_POWER))
			ioControl.SetControlState(RFID_POWER, TRUE);
#endif // WINCE	
*/
		m_bShowSplashWnd = bEnable;
	}

	BOOL CSplashWnd::ShowSplashScreen(UINT uTimeOut, UINT uBitmapID, CWnd* pParentWnd /*= NULL*/)
	{
		ASSERT(uTimeOut && uBitmapID);

		if (!m_bShowSplashWnd || m_pSplashWnd != NULL) {
			return FALSE;
		}

		// Allocate a new splash screen, and create the window.
		m_pSplashWnd = new CSplashWnd;

		if (!m_pSplashWnd->m_bitmap.LoadBitmap(uBitmapID)) {
			return FALSE;
		}

		BITMAP bm;
		m_pSplashWnd->m_bitmap.GetBitmap(&bm);

		CString strWndClass = AfxRegisterWndClass(0,
			AfxGetApp()->LoadStandardCursor(IDC_ARROW));

		if (!m_pSplashWnd->CreateEx(0, strWndClass, NULL, WS_POPUP | WS_VISIBLE,
			0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL))
		{
			TRACE0("Failed to create splash screen.\n");
			delete m_pSplashWnd;
			return FALSE;
		}

		// Center the window.
		m_pSplashWnd->CenterWindow();
		m_pSplashWnd->UpdateWindow();
/*
#ifdef WINCE
		// Power Reset
		CIOControl ioControl;

		if(ioControl.GetControlState(RFID_POWER))
		{
			ioControl.SetControlState(RFID_RESET, TRUE);
			Sleep(20);
			ioControl.SetControlState(RFID_RESET, FALSE);

			// Waiting Firmware Operation
			Sleep(uTimeOut);
		}
		else
		{
			AfxMessageBox(_T("Error : Power Input Fail"));
		}
#endif // WINCE
*/
		// Set a timer to destroy the splash screen.
		m_pSplashWnd->SetTimer(1, uTimeOut, NULL);

		return TRUE;
	}

	BOOL CSplashWnd::PreTranslateAppMessage(MSG* pMsg)
	{
		if (m_pSplashWnd == NULL)
			return FALSE;

		// If we get a keyboard or mouse message, hide the splash screen.
		if (pMsg->message == WM_KEYDOWN ||
			pMsg->message == WM_SYSKEYDOWN ||
			pMsg->message == WM_LBUTTONDOWN ||
			pMsg->message == WM_RBUTTONDOWN)
		{
			m_pSplashWnd->HideSplashScreen();
			return TRUE;	// message handled here
		}

		return FALSE;	// message not handled
	}

	void CSplashWnd::HideSplashScreen()
	{
		// Destroy the window, and update the mainframe.
		DestroyWindow();
//		AfxGetMainWnd()->UpdateWindow();
//		KillTimer(1);
	}

	void CSplashWnd::PostNcDestroy()
	{
		// Free the C++ class.
		delete this;
	}

	void CSplashWnd::OnPaint()
	{
		CPaintDC dc(this);

		CDC dcImage;
		if (dcImage.CreateCompatibleDC(&dc))
		{
			BITMAP bm;
			m_bitmap.GetBitmap(&bm);

			// Paint the image.
			CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
			dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
			dcImage.SelectObject(pOldBitmap);
		}
	}

	void CSplashWnd::OnTimer(UINT_PTR nIDEvent)
	{
		// Destroy the splash screen window.
		HideSplashScreen();

//		KillTimer(1);
	}

};