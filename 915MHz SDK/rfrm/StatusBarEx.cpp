// This is part of the Professional User Interface Suite library.
// Copyright (C) 2001-2004 FOSS Software, Inc.
// All rights reserved.
//
// http://www.prof-uis.com
// http://www.fossware.com
// mailto:foss@fossware.com

// Warranties and Disclaimers:
// THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND
// INCLUDING, BUT NOT LIMITED TO, WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.o
// IN NO EVENT WILL FOSS SOFTWARE INC. BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES,
// INCLUDING DAMAGES FOR LOSS OF PROFITS, LOSS OR INACCURACY OF DATA,
// INCURRED BY ANY PERSON FROM SUCH PERSON'S USAGE OF THIS SOFTWARE
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.

// ExtStatusControlBar.cpp : implementation file
//

#include "stdafx.h"
#include "StatusBarEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace techwin
{

	CLabel::CLabel()
	{
	}

	CLabel::~CLabel()
	{
	}


	BEGIN_MESSAGE_MAP(CLabel, CStatic)
		//{{AFX_MSG_MAP(CLabel)
		ON_WM_ERASEBKGND()
		ON_WM_PAINT()
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CLabel message handlers


	BOOL CLabel::OnEraseBkgnd(CDC* pDC) 
	{
		pDC;
		return TRUE;
	}

	//////////////////////////////////////////////////////////////////////////

	void CLabel::OnPaint() 
	{
		CPaintDC dc(this); // device context for painting

		CRect rcClient;
		GetClientRect( &rcClient );

		CRgn rgn;
		rgn.CreateRectRgnIndirect(&rcClient);
		dc.SelectClipRgn(&rgn);

		dc.FillSolidRect( &rcClient, GetSysColor(COLOR_3DFACE) );

		//////////////////////////////////////////////////////////////////////////
		// paint text
		//////////////////////////////////////////////////////////////////////////

		CString strText;
		GetWindowText(strText);

		DWORD style = GetStyle();
		DWORD dwFlags = 0;

#ifdef WINCE
		dwFlags = SS_CENTER | DT_WORDBREAK;
#elif WIN32
		switch (style & SS_TYPEMASK)
		{
		case SS_RIGHT: 
			dwFlags = DT_RIGHT | DT_WORDBREAK; 
			break; 
		case SS_CENTER: 
			dwFlags = SS_CENTER | DT_WORDBREAK;
			break;
		case SS_LEFTNOWORDWRAP: 
			dwFlags = DT_LEFT; 
			break;
		default: // treat other types as left
		case SS_LEFT: 
			dwFlags = DT_LEFT | DT_WORDBREAK; 
			break;
		}	
#endif

		// Added to expand tabs...
		if(strText.Find(_T('\t')) != -1)
			dwFlags |= DT_EXPANDTABS;
		// If the text centered make an assumtion that
		// the will want to center verticly as well
		if (style & SS_CENTERIMAGE){
			dwFlags = DT_CENTER;
			// Apply 
			if (strText.Find(_T("\r\n")) == -1){
				dwFlags |= DT_VCENTER;
				// And because DT_VCENTER only works with single lines
				dwFlags |= DT_SINGLELINE; 
			}
		}	
		dwFlags |= (DT_VCENTER|DT_END_ELLIPSIS); 


		COLORREF clrOldText;
		INT nOldBkMode = dc.SetBkMode( TRANSPARENT );

		LOGFONT lf;
		memset(&lf,0,sizeof(LOGFONT));
#ifndef WIN32
		lf.lfQuality = PROOF_QUALITY;
#endif
		lf.lfHeight = 16;
		lf.lfWeight = 600;
		lstrcpy(lf.lfFaceName, _T("Arial"));
		CFont f;
		f.CreateFontIndirect(&lf);
		CFont * pOldFont = dc.SelectObject(&f);

		CRect rc;

		rc = rcClient;
		clrOldText = dc.SetTextColor( GetSysColor( COLOR_3DHILIGHT) );
		rc.top -= 3;
		dc.DrawText(strText,rc,dwFlags);

		rc = rcClient;
		rc.top -= 1;
		rc.left += 2;
		dc.SetTextColor(GetSysColor(COLOR_3DSHADOW));
		dc.DrawText(strText,rc,dwFlags);

		rc = rcClient;
		rc.left += 1;
		rc.top -= 2;
		dc.SetTextColor( RGB(0,0,255) );
		dc.DrawText(strText,rc,dwFlags);

		dc.SelectObject( pOldFont );
		f.DeleteObject();
		dc.SetBkMode( nOldBkMode );
		dc.SetTextColor( clrOldText );
	}

	/////////////////////////////////////////////////////////////////////////////
	// CStatusBarEx

	CStatusBarEx::CStatusBarEx()
	{
	}

	CStatusBarEx::~CStatusBarEx()
	{
		for ( int i = 0; i < m_arrPaneControls.GetSize(); i++ ){
			if( m_arrPaneControls[i]->hWnd && ::IsWindow(m_arrPaneControls[i]->hWnd) ) {
				::ShowWindow(m_arrPaneControls[i]->hWnd, SW_HIDE); 
				if( m_arrPaneControls[i]->bAutoDestroy ) {
					::DestroyWindow(m_arrPaneControls[i]->hWnd);
				}
			}
			_STATUSBAR_PANE_CTRL_ *pPaneCtrl = m_arrPaneControls[i];
			if( pPaneCtrl )
				delete pPaneCtrl;
		}
	}

	BEGIN_MESSAGE_MAP(CStatusBarEx, CStatusBar)
		//{{AFX_MSG_MAP(CStatusBarEx)
		ON_WM_CREATE()
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()


	/////////////////////////////////////////////////////////////////////////////
	// CStatusBarEx message handlers
	//////////////////////////////////////////////////////////////////////////

	int CStatusBarEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
	{
		if( CStatusBar::OnCreate(lpCreateStruct) == -1 )
			return -1;

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	LRESULT CStatusBarEx::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lResult =CStatusBar::WindowProc(message, wParam, lParam);
		if( message == WM_SIZE ){
			RepositionControls();
		}
		return lResult;
	}

	//////////////////////////////////////////////////////////////////////////

	void CStatusBarEx::RepositionControls()
	{
		HDWP _hDWP = ::BeginDeferWindowPos( m_arrPaneControls.GetSize() );

		CRect rcClient;
		GetClientRect(&rcClient);
		for (int i = 0; i < m_arrPaneControls.GetSize(); i++ )
		{
			int   iIndex  = CommandToIndex(m_arrPaneControls[i]->nID);
			HWND hWnd    = m_arrPaneControls[i]->hWnd;

			CRect rcPane;
			GetItemRect(iIndex, &rcPane);

			// CStatusBar::GetItemRect() sometimes returns invalid size 
			// of the last pane - we will re-compute it
			int cx = ::GetSystemMetrics( SM_CXEDGE );
			DWORD dwPaneStyle = GetPaneStyle( iIndex );
			if( iIndex == (m_nCount-1) )
			{
				if( (dwPaneStyle & SBPS_STRETCH ) == 0 )
				{
					UINT nID, nStyle;
					int  cxWidth;
					GetPaneInfo( iIndex, nID, nStyle, cxWidth );
					rcPane.right = rcPane.left + cxWidth + cx*3;
				} // if( (dwPaneStyle & SBPS_STRETCH ) == 0 )
				else
				{
					CRect rcClient;
					GetClientRect( &rcClient );
					rcPane.right = rcClient.right;
					if( (GetStyle() & SBARS_SIZEGRIP) == SBARS_SIZEGRIP )
					{
						int cxSmIcon = ::GetSystemMetrics( SM_CXSMICON );
						rcPane.right -= cxSmIcon + cx;
					} // if( (GetStyle() & SBARS_SIZEGRIP) == SBARS_SIZEGRIP )
				} // else from if( (dwPaneStyle & SBPS_STRETCH ) == 0 )
			} // if( iIndex == (m_nCount-1) )

			if ((GetPaneStyle (iIndex) & SBPS_NOBORDERS) == 0){
				rcPane.DeflateRect(cx,cx);
			}else{
				rcPane.DeflateRect(cx,1,cx,1);
			}

			if (hWnd && ::IsWindow(hWnd)){
				_hDWP = ::DeferWindowPos(
					_hDWP, 
					hWnd, 
					NULL, 
					rcPane.left,
					rcPane.top, 
					rcPane.Width(), 
					rcPane.Height(),
					SWP_NOZORDER|SWP_NOOWNERZORDER|SWP_SHOWWINDOW
					);

				::RedrawWindow(
					hWnd,
					NULL,
					NULL,
					RDW_INVALIDATE|RDW_UPDATENOW
					|RDW_ERASE|RDW_ERASENOW
					);

			} // if (hWnd && ::IsWindow(hWnd)){ 
		}

		// Modified by Youngho Kim 
		// Date : 2007/08/22
		// Description : for Windows CE 5.o
		//	VERIFY( ::EndDeferWindowPos( _hDWP ) );
		::EndDeferWindowPos( _hDWP );
	}

	//////////////////////////////////////////////////////////////////////////

	BOOL CStatusBarEx::AddPane(
		UINT nID,	// ID of the  pane
		int nIndex	// index of the pane
		)
	{
		if (nIndex < 0 || nIndex > m_nCount){
			ASSERT(FALSE);
			return FALSE;
		}

		if (CommandToIndex(nID) != -1){
			ASSERT(FALSE);
			return FALSE;
		}

		CArray<_STATUSBAR_PANE_*,_STATUSBAR_PANE_*> arrPanesTmp;
		int iIndex = 0;
		for (iIndex = 0; iIndex < m_nCount+1; iIndex++)
		{
			_STATUSBAR_PANE_* pNewPane = new _STATUSBAR_PANE_;

			if (iIndex == nIndex){
				pNewPane->nID    = nID;
				pNewPane->nStyle = SBPS_NORMAL;
			}else{
				int idx = iIndex;
				if (iIndex > nIndex) idx--;

				_STATUSBAR_PANE_* pOldPane  = GetPanePtr(idx);
				pNewPane->cxText  = pOldPane->cxText;
				pNewPane->nFlags  = pOldPane->nFlags;
				pNewPane->nID     = pOldPane->nID;
				pNewPane->nStyle  = pOldPane->nStyle;
				pNewPane->strText = pOldPane->strText;
			}
			arrPanesTmp.Add(pNewPane);
		}

		int nPanesCount = arrPanesTmp.GetSize();
		UINT* lpIDArray = new UINT[ nPanesCount ];
		for (iIndex = 0; iIndex < nPanesCount; iIndex++) {
			lpIDArray[iIndex] = arrPanesTmp[iIndex]->nID;
		}

		// set the indicators 
		SetIndicators(lpIDArray, nPanesCount);
		// free memory
		for (iIndex = 0; iIndex < nPanesCount; iIndex++){
			_STATUSBAR_PANE_* pPane = arrPanesTmp[iIndex];
			if (iIndex != nIndex)
				PaneInfoSet(iIndex, pPane);
			if(pPane) 
				delete pPane;
		}

		arrPanesTmp.RemoveAll();
		if(lpIDArray) 
			delete []lpIDArray;

		RepositionControls();

		return TRUE;
	}

	//////////////////////////////////////////////////////////////////////////

	BOOL CStatusBarEx::RemovePane(
		UINT nID	// ID of the pane
		)
	{
		if ( CommandToIndex(nID) == -1 || m_nCount == 1 ){
			ASSERT(FALSE);
			return FALSE;
		}

		CArray<_STATUSBAR_PANE_*,_STATUSBAR_PANE_*> arrPanesTmp;
		int nIndex;
		for (nIndex = 0; nIndex < m_nCount; nIndex++)
		{
			_STATUSBAR_PANE_* pOldPane = GetPanePtr(nIndex);

			if (pOldPane->nID == nID)
				continue;

			_STATUSBAR_PANE_* pNewPane = new _STATUSBAR_PANE_;

			pNewPane->cxText  = pOldPane->cxText;
			pNewPane->nFlags  = pOldPane->nFlags;
			pNewPane->nID     = pOldPane->nID;
			pNewPane->nStyle  = pOldPane->nStyle;
			pNewPane->strText = pOldPane->strText;
			arrPanesTmp.Add(pNewPane);
		}

		UINT* lpIDArray = new UINT[arrPanesTmp.GetSize()];
		for (nIndex = 0; nIndex < arrPanesTmp.GetSize(); nIndex++) {
			lpIDArray[nIndex] = arrPanesTmp[nIndex]->nID;
		}

		// set the indicators
		SetIndicators(lpIDArray, arrPanesTmp.GetSize());
		// free memory
		for (nIndex = 0; nIndex < arrPanesTmp.GetSize(); nIndex++){
			_STATUSBAR_PANE_* pPane = arrPanesTmp[nIndex];
			PaneInfoSet(nIndex, pPane);
			if(pPane) 
				delete pPane;
		}

		for ( int i = 0; i < m_arrPaneControls.GetSize(); i++ ){
			if (m_arrPaneControls[i]->nID == nID){
				if( m_arrPaneControls[i]->hWnd && ::IsWindow(m_arrPaneControls[i]->hWnd) ) {
					::ShowWindow(m_arrPaneControls[i]->hWnd, SW_HIDE); 
					if( m_arrPaneControls[i]->bAutoDestroy ) {
						::DestroyWindow(m_arrPaneControls[i]->hWnd);
					}
				}
				_STATUSBAR_PANE_CTRL_ *pPaneCtrl = m_arrPaneControls[i];
				if( pPaneCtrl )
					delete pPaneCtrl;
				m_arrPaneControls.RemoveAt(i);
				break;
			}
		}

		arrPanesTmp.RemoveAll();
		if(lpIDArray) 
			delete []lpIDArray;

		RepositionControls();

		return TRUE;
	}

	//////////////////////////////////////////////////////////////////////////

	BOOL CStatusBarEx::AddPaneControl(HWND hWnd, UINT nID, BOOL bAutoDestroy)
	{
		if (CommandToIndex (nID) == -1) {
			return FALSE;
		}

		_STATUSBAR_PANE_CTRL_* pPaneCtrl = new _STATUSBAR_PANE_CTRL_;
		pPaneCtrl->nID         = nID;
		pPaneCtrl->hWnd        = hWnd;
		pPaneCtrl->bAutoDestroy = bAutoDestroy;

		m_arrPaneControls.Add(pPaneCtrl);

		RepositionControls();
		return TRUE;
	}

	//////////////////////////////////////////////////////////////////////////

	BOOL CStatusBarEx::PaneInfoGet(int nIndex, _STATUSBAR_PANE_* pPane)
	{
		if( nIndex < m_nCount  && nIndex >= 0 )
		{
			GetPaneInfo( nIndex,  pPane->nID, pPane->nStyle, pPane->cxText );
			CString strPaneText;
			GetPaneText( nIndex , strPaneText );
			pPane->strText = LPCTSTR(strPaneText);
			return TRUE;
		}
		return FALSE;
	}

	//////////////////////////////////////////////////////////////////////////

	BOOL CStatusBarEx::PaneInfoSet(int nIndex, _STATUSBAR_PANE_* pPane)
	{
		if( nIndex < m_nCount  && nIndex >= 0 ){
			SetPaneInfo( nIndex, pPane->nID, pPane->nStyle, pPane->cxText );
			SetPaneText( nIndex, LPCTSTR( pPane->strText) );
			return TRUE;
		}
		return FALSE;
	}

};