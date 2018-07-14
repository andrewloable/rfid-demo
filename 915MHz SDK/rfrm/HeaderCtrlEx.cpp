// CJFlatHeaderCtrl.cpp : implementation file
// Copyright ?1998-1999 CodeJock.com, All Rights Reserved.
// See ReadMe.txt for TERMS OF USE.
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HeaderCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace techwin
{
/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx

CHeaderCtrlEx::CHeaderCtrlEx()
{
	m_nSortCol		= -1;
	m_bBoldFont		= FALSE;
	m_nOffset		= 6;
	m_bLBtnDown		= FALSE;
	m_popupMenuID	= 0;
	m_popToolbarID	= 0;
	m_nPos			= 0;
	m_pParentWnd    = NULL;
}

CHeaderCtrlEx::~CHeaderCtrlEx()
{
	// fix potential resource leak - KStowell - 10-22-99.
	m_Font.DeleteObject();
}

BEGIN_MESSAGE_MAP(CHeaderCtrlEx, CHeaderCtrl)
	//{{AFX_MSG_MAP(CHeaderCtrlEx)
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_MEASUREITEM()
	ON_WM_MENUCHAR()
	ON_WM_INITMENUPOPUP()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
//	ON_WM_WINDOWPOSCHANGED()	// PBV
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHeaderCtrlEx message handlers

void CHeaderCtrlEx::InitializeHeader(bool bBoldFont)
{
	m_Font.DeleteObject();

#ifndef _WIN32_WCE
	NONCLIENTMETRICS ncm;
	ncm.cbSize = sizeof(ncm);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0);

	if(bBoldFont)
		ncm.lfMessageFont.lfWeight = 700;
	VERIFY(m_Font.CreateFontIndirect(&ncm.lfMessageFont));
	SetFont(&m_Font);
#endif

	m_bBoldFont = bBoldFont;
}

int CHeaderCtrlEx::SetSortImage(int nCol, BOOL bAsc)
{
	int nPrevCol = m_nSortCol;
	
	m_nSortCol = nCol;
	m_bSortAsc = bAsc;
	
	// Change the item to ownder drawn
	HD_ITEM hditem;
	
	hditem.mask = HDI_BITMAP | HDI_FORMAT;
	GetItem( nCol, &hditem );
	if (hditem.hbm == NULL)
	{
		hditem.fmt |= HDF_OWNERDRAW;
		SetItem( nCol, &hditem );

		// Invalidate header control so that it gets redrawn
		Invalidate();
	}
	
	return nPrevCol;
}

void CHeaderCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct != NULL);

	// define some temporary variables.
	CDC*	pDC			= CDC::FromHandle( lpDrawItemStruct->hDC );
	CRect	rcItem		= lpDrawItemStruct->rcItem;
	CRect	rcIcon		= lpDrawItemStruct->rcItem;
    int 	nState		= lpDrawItemStruct->itemState;
	int		nItemID		= lpDrawItemStruct->itemID;
	int		nSavedDC	= pDC->SaveDC();

	// Paint the background.
	pDC->FillSolidRect(rcItem, afxData.clrBtnFace);
	pDC->SetBkMode(TRANSPARENT);
	
	// Set clipping region to limit drawing within column
	CRgn rgn;
	rgn.CreateRectRgnIndirect( &rcItem );
	pDC->SelectObject( &rgn );
	rgn.DeleteObject();

	// Get the column text and format
	TCHAR buf[256];
	HD_ITEM hditem;
	
	hditem.mask = HDI_TEXT | HDI_FORMAT;
	hditem.pszText = buf;
	hditem.cchTextMax = 255;
	
	GetItem( nItemID, &hditem );
	
	// Determine format for drawing column label
	UINT uFormat = DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP 
		| DT_VCENTER | DT_END_ELLIPSIS ;
	
	if( hditem.fmt & HDF_CENTER) {
		uFormat |= DT_CENTER;
	} else if( hditem.fmt & HDF_RIGHT) {
		uFormat |= DT_RIGHT;
	} else {
		uFormat |= DT_LEFT;
	}
	
	// Adjust the rect if the mouse button is pressed on it
	if( nState == ODS_SELECTED ) {
		rcItem.left++;
		rcItem.top += 2;
		rcItem.right++;
	}
	
	// Adjust the rect further if Sort arrow is to be displayed
	if( nItemID == m_nSortCol ) {
		rcItem.right -= GetSortImageWidth();
	}
	
	rcItem.left += m_nOffset;
	rcItem.right -= m_nOffset;

	// Draw column label
	if( rcItem.left < rcItem.right ) {
		if (m_bBoldFont) {
			CFont* pOldFont = pDC->SelectObject(&m_Font);
			pDC->DrawText(buf,-1,rcItem, uFormat);
			pDC->SelectObject(pOldFont);
		} else {
			pDC->DrawText(buf,-1,rcItem, uFormat);
		}
	}

	// Draw the Sort arrow
	if( nItemID == m_nSortCol )
	{
		// Set up pens to use for drawing the triangle
		CPen penLite(PS_SOLID, 1, afxData.clrBtnHilite);
		CPen penShad(PS_SOLID, 1, afxData.clrBtnShadow);
		CPen *pOldPen = pDC->SelectObject( &penLite );
		
		if( m_bSortAsc )
		{
			// Draw triangle pointing upwards
			pDC->MoveTo( rcIcon.right - 2*m_nOffset, m_nOffset-1);
			pDC->LineTo( rcIcon.right - 3*m_nOffset/2, rcIcon.bottom - m_nOffset );
			pDC->LineTo( rcIcon.right - 5*m_nOffset/2-2, rcIcon.bottom - m_nOffset );
			pDC->MoveTo( rcIcon.right - 5*m_nOffset/2-1, rcIcon.bottom - m_nOffset-1 );
			
			pDC->SelectObject( &penShad );
			pDC->LineTo( rcIcon.right - 2*m_nOffset, m_nOffset-2);
		}
		else
		{
			// Draw triangle pointing downwords
			pDC->MoveTo( rcIcon.right - 3*m_nOffset/2, m_nOffset-1);
			pDC->LineTo( rcIcon.right - 2*m_nOffset-1, rcIcon.bottom - m_nOffset + 1 );
			pDC->MoveTo( rcIcon.right - 2*m_nOffset-1, rcIcon.bottom - m_nOffset );
			
			pDC->SelectObject( &penShad );
			pDC->LineTo( rcIcon.right - 5*m_nOffset/2-1, m_nOffset -1 );
			pDC->LineTo( rcIcon.right - 3*m_nOffset/2, m_nOffset -1);
		}
		
		// Restore the pen
		pDC->SelectObject( pOldPen );

		// fix potential resource leak - KStowell - 10-21-99
		penLite.DeleteObject();
		penShad.DeleteObject();
	}

	// restore the device context
	pDC->RestoreDC(nSavedDC);
}

void CHeaderCtrlEx::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// KStowell - Get the client rect.
	CRect rcClient;
	GetClientRect( &rcClient );

	// KStowell - Create a memory device-context. This is done to help reduce
	// screen flicker, since we will paint the entire control to the
	// off screen device context first.
	CDC memDC;
	CBitmap bitmap;
	memDC.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, rcClient.Width(), rcClient.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(rcClient, afxData.clrBtnFace);
	
	// First let the control do its default drawing.
	CWnd::DefWindowProc( WM_PAINT, (WPARAM)memDC.m_hDC, 0 );

	// KStowell - Repaint the background.
	DrawFlatBorder(&memDC);

	// KStowell - Copy the memory device context back into the original DC via BitBlt().
	dc.BitBlt( rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), &memDC, 
		rcClient.left, rcClient.top, SRCCOPY );

	// KStowell - Cleanup resources.
	memDC.SelectObject(pOldBitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}


// Changes in code by Paulo Breda Vieira 1999-11-19
void CHeaderCtrlEx::DrawFlatBorder(CDC* pDC)
{
	CRect rci;
	GetWindowRect(&rci);
	ScreenToClient(&rci);

	// Draw flat style border around entire header.
	rci.InflateRect(0,0,1,0);	// Breda
	pDC->Draw3dRect(rci, afxData.clrBtnHilite, afxData.clrBtnShadow);

	// Cover up thick 3D border.
//	pDC->Draw3dRect(rci, afxData.clrBtnFace, afxData.clrBtnFace);	// Breda
	rci.DeflateRect(1,1,0,1);	// Breda
	pDC->Draw3dRect(rci, afxData.clrBtnFace, afxData.clrBtnFace);
	
	// Create the pens for further cover-up.
	CPen penLite(PS_SOLID, 1, afxData.clrBtnHilite);
	CPen penShad(PS_SOLID, 1, afxData.clrBtnShadow);
	CPen penFace(PS_SOLID, 1, afxData.clrBtnFace);
	CPen *pOldPen = pDC->SelectObject( &penLite );
	
	// Set up the header item struct.
	HD_ITEM hdi;
	memset (&hdi, 0, sizeof(HD_ITEM));
	hdi.fmt  = HDF_STRING | HDF_LEFT | HDF_OWNERDRAW;
	hdi.mask = HDI_WIDTH | HDI_TEXT | HDI_FORMAT | HDI_ORDER; // Yiannhs :1999-10-19
	int cx = 0;
	
    long j = GetItemCount();    //Yiannhs
    long i = 0;                 //Yiannhs
	
    long * ItemOrders = new long[j];    //Yiannhs :1999-10-19
    for( i=0; i<j; i++ ) {				//Yiannhs :1999-10-19
		GetItem(i, &hdi);				//Yiannhs :1999-10-19
		ItemOrders[hdi.iOrder] = i;     //Yiannhs :1999-10-19
    }
	
	hdi.fmt  = HDF_STRING | HDF_LEFT | HDF_OWNERDRAW;   //Yiannhs :1999-10-19
	hdi.mask = HDI_WIDTH | HDI_TEXT | HDI_FORMAT;       //Yiannhs :1999-10-19

	// For each header item found, do further cover up.
	for (i = 0; i < j; ++i)
	{
		GetItem( ItemOrders[i], &hdi);
		cx += hdi.cxy;
		
		pDC->SelectObject(&penShad);
		pDC->MoveTo(cx, 2);
		pDC->LineTo(cx, rci.bottom-1);		// Breda
		
		pDC->SelectObject(&penLite);
		pDC->MoveTo(cx+1, 2);
		pDC->LineTo(cx+1, rci.bottom-1);	// Breda
		
		pDC->SelectObject(&penFace);
		pDC->MoveTo(cx-1, 2);
		pDC->LineTo(cx-1, rci.bottom-1);	// Breda
		
		pDC->SelectObject(&penFace);
		pDC->MoveTo(cx-2, 2);
		pDC->LineTo(cx-2, rci.bottom-1);	// Breda
	}
	
	delete [] ItemOrders; //Yiannhs :1999-10-19
	
	// Restore the pen and release device context.
	pDC->SelectObject( pOldPen );

	// fix potential resource leak - KStowell - 10-21-99
	penLite.DeleteObject();
	penShad.DeleteObject();
	penFace.DeleteObject();
}

void CHeaderCtrlEx::OnRButtonDown(UINT /*nFlags*/, CPoint point) 
{
	// No menu was defined...
	if (!m_popupMenuID) {
		TRACE0( "Warning: No menu resource was associated with CCJTabCtrl.\n" ); 
		return;
	}

#ifndef _WIN32_WCE
	// Since we are using the main window as the
	// parent, we need to convert the point to screen
	// coordinates...
	CPoint pt = point;
	ClientToScreen(&pt);

	// Load the popup menu.
	VERIFY(m_popupMenu.LoadMenu(m_popupMenuID));
	CMenuEx* pPopup = (CMenuEx*)m_popupMenu.GetSubMenu(m_nPos);
	ASSERT(pPopup != NULL);
	
	// Load toolbar resource if any for menu icons.
	if (m_popToolbarID) {
		pPopup->LoadToolbar(m_popToolbarID);
	}
	
	// Display the popup menu, use the main window as its parent.
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		pt.x, pt.y, AfxGetMainWnd());
	
	m_popupMenu.DestroyMenu();
#endif
}

void CHeaderCtrlEx::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
#ifndef _WIN32_WCE
	if (lpMeasureItemStruct->CtlType == ODT_MENU) 
	{
		if (IsMenu((HMENU)lpMeasureItemStruct->itemID)) {
			CMenu* pMenu = CMenu::FromHandle((HMENU)lpMeasureItemStruct->itemID);
			
			if (m_popupMenu.IsMenu(pMenu)) {
				m_popupMenu.MeasureItem(lpMeasureItemStruct);
				return;
			}
		}
	}
#endif
	CHeaderCtrl::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

LRESULT CHeaderCtrlEx::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
#ifndef _WIN32_WCE
	if (m_popupMenu.IsMenu(pMenu)) {
		return CMenuEx::FindKeyboardShortcut(nChar, nFlags, pMenu);
	}
#endif
	return CHeaderCtrl::OnMenuChar(nChar, nFlags, pMenu);
}

void CHeaderCtrlEx::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CHeaderCtrl::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

#ifndef _WIN32_WCE
	if(!bSysMenu) {
		if (m_popupMenu.IsMenu(pPopupMenu)) {
			CMenuEx::UpdateMenu(pPopupMenu);
		}
	}
#endif
}

#ifdef _VC_VERSION_5
BOOL CHeaderCtrlEx::GetOrderArray(LPINT piArray, int iCount /* = -1 */)
{
	ASSERT(::IsWindow(m_hWnd));

	// if -1 was passed, find the count ourselves

	int nCount = iCount;
	if (nCount == -1)
	{
		nCount = GetItemCount();

		if (nCount == -1)
			return FALSE;
	}

	ASSERT(AfxIsValidAddress(piArray, iCount * sizeof(int)));

	return (BOOL) ::SendMessage(m_hWnd, HDM_GETORDERARRAY,
		(WPARAM) iCount, (LPARAM) piArray);
}
#endif // _VC_VERSION_5

void CHeaderCtrlEx::PreSubclassWindow() 
{
	CHeaderCtrl::PreSubclassWindow();

	m_pParentWnd = GetParent();
	ASSERT(m_pParentWnd);

// Changes in code by Paulo Breda Vieira 1999-11-19
//	ResizeWindow();
}

int CHeaderCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CHeaderCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pParentWnd = CWnd::FromHandle(lpCreateStruct->hwndParent);
	ASSERT(m_pParentWnd);

// Changes in code by Paulo Breda Vieira 1999-11-19
//	ResizeWindow();
	return 0;
}

// Changes in code by Paulo Breda Vieira 1999-11-19
//void CHeaderCtrlEx::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
//{
//	CHeaderCtrl::OnWindowPosChanged(lpwndpos);
//	ResizeWindow();
//}
	
// Changes in code by Paulo Breda Vieira 1999-11-19
//void CHeaderCtrlEx::ResizeWindow()
//{
//	ASSERT_VALID(this);
//	ASSERT_VALID(m_pParentWnd);
//
//	// Get the client size of the parent window, this will give us the
//	// actual width of the header we are looking for.
//	CRect rcParent;
//	m_pParentWnd->GetClientRect(&rcParent);
//
//	// Get the size of the header control, we will need this for the
//	// height of the header.
//	CRect rcWnd;
//	GetWindowRect(&rcWnd);
//
//	// Now, resize the window.
//	SetWindowPos(NULL, 0, 0, rcParent.Width(), rcWnd.Height(),
//		SWP_NOMOVE/*|SWP_FRAMECHANGED*/);
//}

BOOL CHeaderCtrlEx::OnEraseBkgnd(CDC* pDC) 
{
	// KStowell - overridden for flicker-free drawing.
	UNUSED_ALWAYS(pDC);
	return TRUE;
}

};