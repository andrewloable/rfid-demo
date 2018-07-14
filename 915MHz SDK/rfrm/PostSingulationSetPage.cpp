// ..\PostSingulationSetPage.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "PostSingulationSetPage.h"


// CPostSingulationSetPage dialog

IMPLEMENT_DYNAMIC(CPostSingulationSetPage, CPropertyPage)

CPostSingulationSetPage::CPostSingulationSetPage(const wchar_t* lpszTitle, HICON hIcon)
	: CPropertyPage(CPostSingulationSetPage::IDD)
{
	// Set the title and icon.
	if( NULL != hIcon )
	{
		m_psp.dwFlags |= PSP_USEHICON;
		//			HICON hIconTab = AfxGetApp()->LoadIcon( m_nIconID );
		m_psp.hIcon = hIcon;
	}
}

CPostSingulationSetPage::~CPostSingulationSetPage()
{
}

void CPostSingulationSetPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPostSingulationSetPage, CPropertyPage)
END_MESSAGE_MAP()


// CPostSingulationSetPage message handlers
