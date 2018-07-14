// HighColorPropertySheet.cpp : implementation file
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IconPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace techwin
{
	/////////////////////////////////////////////////////////////////////////////
	// CIconPropertySheet

	IMPLEMENT_DYNAMIC(CIconPropertySheet, CPropertySheet)

	CIconPropertySheet::CIconPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
		: CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
	{
	}

	CIconPropertySheet::CIconPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
		: CPropertySheet(pszCaption, pParentWnd, iSelectPage)
	{
	}

	CIconPropertySheet::~CIconPropertySheet()
	{
	}


	BEGIN_MESSAGE_MAP(CIconPropertySheet, CPropertySheet)
		//{{AFX_MSG_MAP(CIconPropertySheet)
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CIconPropertySheet message handlers
};
