// PageIcon.cpp : implementation file
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IconPropertyPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace techwin
{
	/////////////////////////////////////////////////////////////////////////////
	// CIconPropertyPage property page

	IMPLEMENT_DYNAMIC(CIconPropertyPage, CPropertyPage)
/*
		CIconPropertyPage::CIconPropertyPage(LPCWSTR lpszTitle, UINT nIconID)
		: CPropertyPage(CIconPropertyPage::IDD),
		m_nIconID(nIconID),
		m_hIcon(NULL)
	{
		//{{AFX_DATA_INIT(CIconPropertyPage)
		//}}AFX_DATA_INIT

		// Set the title and icon.
		if( NULL != m_nIconID )
		{
			m_psp.dwFlags |= PSP_USEHICON;
			HICON hIconTab = AfxGetApp()->LoadIcon( m_nIconID );
			m_psp.hIcon = hIconTab;
		}
	}
*/
	CIconPropertyPage::CIconPropertyPage(LPCWSTR lpszTitle, HICON hIcon)
		: CPropertyPage(CIconPropertyPage::IDD)
		, m_hIcon(hIcon)
	{
		//{{AFX_DATA_INIT(CIconPropertyPage)
		//}}AFX_DATA_INIT

		// Set the title and icon.
		if( NULL != hIcon )
		{
			m_psp.dwFlags |= PSP_USEHICON;
//			HICON hIconTab = AfxGetApp()->LoadIcon( m_nIconID );
			m_psp.hIcon = hIcon;
		}
	}

	CIconPropertyPage::~CIconPropertyPage()
	{
	}

	BEGIN_MESSAGE_MAP(CIconPropertyPage, CPropertyPage)
		//{{AFX_MSG_MAP(CIconPropertyPage)
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CIconPropertyPage message handlers
};