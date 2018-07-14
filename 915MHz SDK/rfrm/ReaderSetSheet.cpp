// ReaderSetSheet.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "ReaderSetSheet.h"


// CReaderSetSheet

IMPLEMENT_DYNAMIC(CReaderSetSheet, CIconPropertySheet)

CReaderSetSheet::CReaderSetSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CIconPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CReaderSetSheet::CReaderSetSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CIconPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CReaderSetSheet::~CReaderSetSheet()
{
}


BEGIN_MESSAGE_MAP(CReaderSetSheet, CIconPropertySheet)
END_MESSAGE_MAP()


// CReaderSetSheet message handlers

BOOL CReaderSetSheet::OnInitDialog()
{
	BOOL bResult = CIconPropertySheet::OnInitDialog();

// 	// width
// 	int cx = GetSystemMetrics(SM_CXSCREEN);
// 	// height
// 	int cy = GetSystemMetrics(SM_CYSCREEN);
// 
// 	CRect rect;
// 	GetWindowRect(&rect);
// 
// 	MoveWindow(0, 0, rect.Width(), rect.Height());
// 
// 	SetWindowPos(&wndTopMost, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE | SWP_NOSIZE);

	return bResult;
}
