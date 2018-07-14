// MessageView.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "MessageView.h"


// CMessageView

IMPLEMENT_DYNCREATE(CMessageView, CView)

CMessageView::CMessageView()
{

}

CMessageView::~CMessageView()
{
}

BEGIN_MESSAGE_MAP(CMessageView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMessageView diagnostics

#ifdef _DEBUG
void CMessageView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMessageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMessageView message handlers

/////////////////////////////////////////////////////////////////////////////
// CRightView drawing

void CMessageView::OnDraw(CDC* pDC)
{
	CRect rect,rcClient;
	GetClientRect(rcClient);

	COLORREF crLight = GetSysColor(COLOR_BTNHIGHLIGHT);
	COLORREF crShadow = GetSysColor(COLOR_BTNSHADOW);
	COLORREF crFrame = GetSysColor(COLOR_WINDOWFRAME);
	COLORREF crBtnFace = GetSysColor(COLOR_BTNFACE);

	pDC->SetBkMode(TRANSPARENT);
#ifdef _WIN32_WCE
	CGdiObject *pOldFont = pDC->SelectStockObject(SYSTEM_FONT);
#else
	CGdiObject *pOldFont = pDC->SelectStockObject(ANSI_VAR_FONT);
#endif

	rect = rcClient;

	// title rect
	rect.bottom = rect.top + 22;
	pDC->FillSolidRect(rect,crBtnFace);
	pDC->Draw3dRect(rect,crLight,crShadow);
	pDC->DrawText(TEXT("   Radio Result :"),rect,DT_SINGLELINE|DT_VCENTER);

	// rect that makes the edit control look even more sunken (windoze default)
	rect.top = rect.bottom;
	rect.bottom = rcClient.bottom;
	pDC->Draw3dRect(rect,crFrame,crBtnFace);

	pDC->SelectObject(pOldFont);

}


/////////////////////////////////////////////////////////////////////////////
// CRightView message handlers

int CMessageView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_wndEdit.Create(WS_VISIBLE|WS_CHILD|ES_MULTILINE|WS_VSCROLL|ES_AUTOVSCROLL,CRect(0,0,0,0),this,0);

	CFont font;

#ifdef _WIN32_WCE
	font.CreateStockObject(SYSTEM_FONT);
#else
	font.CreateStockObject(ANSI_FIXED_FONT);
#endif

	m_wndEdit.SetFont(&font);

	return 0;
}

void CMessageView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	m_wndEdit.MoveWindow(1,23,cx-2,cy-24);
}
 
CEdit* CMessageView::GetEditCtrl()
{
	return &m_wndEdit;
}

void CMessageView::TextOut(LPCTSTR lpszText)
{
	CString strTemp, strNext = lpszText;

	m_wndEdit.GetWindowText(strTemp);

	strTemp += strNext + TEXT("\r\n") ;
	
	m_wndEdit.SetWindowText(strTemp);

	m_wndEdit.SetSel(0,-1);   
}