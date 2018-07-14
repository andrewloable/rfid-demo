// AntennaSetPage.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "AntennaSetPage.h"

#include "MainFrm.h"
#include "RFIDRadioManager.h"

#include "AntennaEditDlg.h"

// CAntennaSetPage dialog

IMPLEMENT_DYNAMIC(CAntennaSetPage, CPropertyPage)

CAntennaSetPage::CAntennaSetPage(const wchar_t* lpszTitle, HICON hIcon)
: CPropertyPage(CAntennaSetPage::IDD)
, m_iselectItem(-1)
{
	// Set the title and icon.
	if( NULL != hIcon )
	{
		m_psp.dwFlags |= PSP_USEHICON;
		//			HICON hIconTab = AfxGetApp()->LoadIcon( m_nIconID );
		m_psp.hIcon = hIcon;
	}
}

CAntennaSetPage::~CAntennaSetPage()
{
}

void CAntennaSetPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ANTENNA, m_ctrlAntennaList);
}


BEGIN_MESSAGE_MAP(CAntennaSetPage, CPropertyPage)
//	ON_NOTIFY(NM_CLICK, IDC_LIST_ANTENNA, &CAntennaSetPage::OnNMClickListAntenna)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ANTENNA, &CAntennaSetPage::OnNMDblclkListAntenna)
END_MESSAGE_MAP()


// CAntennaSetPage message handlers

BOOL CAntennaSetPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	theApp.DoWaitCursor(1);

	int antenna_count = 16;
	CRect rect;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Set Image List
	VERIFY(m_smallImageList.Create(IDB_FOLDERS, 16, 1, RGB(255, 255, 255)));
	m_ctrlAntennaList.SetImageList(&m_smallImageList, LVSIL_SMALL);

	// Insert Column to Antenna List Ctrl
	m_ctrlAntennaList.GetClientRect(&rect);
	InsertAntennaColumn(ANTENNA_PORT_NUMBER,	_T("Num"),			(int)(rect.Width() * 0.4));
	InsertAntennaColumn(ANTENNA_PORT_STATUS,	_T("Status"),		(int)(rect.Width() * 0.3));
	InsertAntennaColumn(ANTENNA_SENS_VALUE,		_T("Sens Value"),	(int)(rect.Width() * 0.2));

#ifdef _WIN32_WCE
	antenna_count = 1;	
#endif

	// Insert Antenna Port Status
	for(int i = 0; i < antenna_count; i++)
	{
		CString str;
		RFID_ANTENNA_PORT_STATUS atennaStatus;

		// Get antenna Port Status
		pFrame->GetRFIDRadioManager()->GetRadioAntennaPortStatus(0, i, &atennaStatus);

		int nCount = m_ctrlAntennaList.GetItemCount();

		str.Format(_T("Antenna #%d"), i);
		InsertAntennaItem(nCount, ANTENNA_PORT_NUMBER, str);

		if(atennaStatus.state == RFID_ANTENNA_PORT_STATE_DISABLED)
			str = _T("DISABLE");
		else
			str = _T("ENABLE");

		InsertAntennaItem(nCount, ANTENNA_PORT_STATUS, str);

		str.Format(_T("%u"), atennaStatus.antennaSenseValue);		//Total Read
		InsertAntennaItem(nCount, ANTENNA_SENS_VALUE, str);
	}

	theApp.DoWaitCursor(-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CAntennaSetPage::InsertAntennaItem(int nItem, int nSubItem, LPCWSTR strItem, int mask, int iImage)
{
	LV_ITEM         lvitem;
	CString			szText;

	memset(&lvitem,0,sizeof(LV_ITEM));
	lvitem.mask = mask;
	lvitem.iItem = nItem;
	lvitem.iSubItem = nSubItem;
	lvitem.pszText = szText.GetBuffer(_tcslen(strItem));
	lvitem.iImage = iImage;
	_tcscpy(lvitem.pszText,(LPCTSTR)strItem);

	if (nSubItem == 0)
	{
		if(m_ctrlAntennaList.InsertItem(&lvitem) == -1) // insert new item
			return false; 
	}

	return(m_ctrlAntennaList.SetItem(&lvitem)); // modify existing item (the sub-item text)}
}

BOOL CAntennaSetPage::InsertAntennaColumn(int nItem, LPCWSTR strItem, int width, int nFmt, int nSubItem, int nMask)
{
	return(m_ctrlAntennaList.InsertColumn(nItem, (LPCTSTR)strItem, nFmt, width, nSubItem)!=-1?true:false);
}
/*
void CAntennaSetPage::OnNMClickListAntenna(NMHDR *pNMHDR, LRESULT *pResult)
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;

	m_iselectItem = phdn->iItem;

	*pResult = 0;
}
*/
void CAntennaSetPage::OnNMDblclkListAntenna(NMHDR *pNMHDR, LRESULT *pResult)
{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE>(pNMHDR);
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	m_iselectItem = phdn->iItem;

	// 	CString strStatus;
	// 	strStatus = m_ctrlAntennaList.GetItemText(m_iselectItem, 1);
	// 
	// 	if(strStatus == _T("ENABLE"))
	{
		CAntennaEditDlg dlg(NULL, m_iselectItem);

		if(dlg.DoModal() == IDOK)
		{
			CString str;
			RFID_ANTENNA_PORT_STATUS atennaStatus;

			// Get antenna Port Status
			pFrame->GetRFIDRadioManager()->GetRadioAntennaPortStatus(0, m_iselectItem, &atennaStatus);

			int nCount = m_ctrlAntennaList.GetItemCount();

			if(atennaStatus.state == RFID_ANTENNA_PORT_STATE_DISABLED)
				str = _T("DISABLE");
			else
				str = _T("ENABLE");

			m_ctrlAntennaList.SetItemText(m_iselectItem, ANTENNA_PORT_STATUS, str);

			str.Format(_T("%u"), atennaStatus.antennaSenseValue);		//Total Read
			m_ctrlAntennaList.SetItemText(m_iselectItem, ANTENNA_SENS_VALUE, str);
		}
	}
	*pResult = 0;
}
