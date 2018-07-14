// ..\SelectCriteriaSetPage.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "SelectCriteriaSetPage.h"


// CSelectCriteriaSetPage dialog

IMPLEMENT_DYNAMIC(CSelectCriteriaSetPage, CPropertyPage)

CSelectCriteriaSetPage::CSelectCriteriaSetPage(const wchar_t* lpszTitle, HICON hIcon)
	: CPropertyPage(CSelectCriteriaSetPage::IDD)
{
	// Set the title and icon.
	if( NULL != hIcon )
	{
		m_psp.dwFlags |= PSP_USEHICON;
		//			HICON hIconTab = AfxGetApp()->LoadIcon( m_nIconID );
		m_psp.hIcon = hIcon;
	}
}

CSelectCriteriaSetPage::~CSelectCriteriaSetPage()
{
}

void CSelectCriteriaSetPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectCriteriaSetPage, CPropertyPage)
END_MESSAGE_MAP()


// CSelectCriteriaSetPage message handlers
