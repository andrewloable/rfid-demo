// ../FrequencyBandPage.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "FrequencyBandPage.h"

#include "MainFrm.h"
#include "RFIDRadioManager.h"
#include "FrequencyBand.h"
#include "SortClass.h"

// CFrequencyBandPage dialog

IMPLEMENT_DYNAMIC(CFrequencyBandPage, CPropertyPage)

CFrequencyBandPage::CFrequencyBandPage(const wchar_t* lpszTitle, HICON hIcon)
	: CPropertyPage(CFrequencyBandPage::IDD)
{
	// Set the title and icon.
	if( NULL != hIcon )
	{
		m_psp.dwFlags |= PSP_USEHICON;
		//			HICON hIconTab = AfxGetApp()->LoadIcon( m_nIconID );
		m_psp.hIcon = hIcon;
	}
}

CFrequencyBandPage::~CFrequencyBandPage()
{
}

void CFrequencyBandPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_FREQUENCY_BAND, m_FrequencyListCtrl);
}


BEGIN_MESSAGE_MAP(CFrequencyBandPage, CPropertyPage)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CFrequencyBandPage::OnHdnItemclickListFrequencyBand)
END_MESSAGE_MAP()


// CFrequencyBandPage message handlers

BOOL CFrequencyBandPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

// 	if( (m_FrequencyListCtrl.GetStyle() & LVS_TYPEMASK) != LVS_REPORT)
// 	{
// 		m_FrequencyListCtrl.SetExtendedStyle(m_FrequencyListCtrl.GetStyle() | LVS_REPORT);
// 	}

	AfxGetApp()->DoWaitCursor(1);

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	pFrame->GetRFIDRadioManager()->GetFrequencyBand(0, &m_FrequencyBandList);

	CString list[3] = {TEXT("No."), TEXT("Frequency"), TEXT("State")};

	m_FrequencyListCtrl.AddColumn(list[0].GetBuffer(list[0].GetLength()+1), 35);
	m_FrequencyListCtrl.AddColumn(list[1].GetBuffer(list[1].GetLength()+1), 80);
	m_FrequencyListCtrl.AddColumn(list[2].GetBuffer(list[2].GetLength()+1), 50);

// 	colum2.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
// 	colum2.pszText = TEXT("Frequency");
// 	colum2.
// 

//	m_FrequencyListCtrl.InsertColumn(1, &colum2);

	POSITION nPos = m_FrequencyBandList.GetHeadPosition();
	int i = 0;

	while( nPos != NULL)
	{
		CFrequencyBand* band = (CFrequencyBand*)m_FrequencyBandList.GetNext(nPos);

		CString strIndex, strFrequency, strState;

		strIndex.Format(TEXT("%u"), i);
		strFrequency.Format(TEXT("%.2lf"), band->Frequency());
		strState.Format(TEXT("%s"), band->GetBandState() ? TEXT("ENABLE") : TEXT("DISABLE"));

		LVITEM item;
		::ZeroMemory(&item, sizeof(LVITEM));
// 
// 		// Insert item for col 0
// 		lvi.mask = LVIF_TEXT;
// 		lvi.pszText = strIndex.GetBuffer(strIndex.GetLength()+1); 
// 		m_FrequencyListCtrl.InsertItem(&lvi);
// 
// 		// Insert subitem for col 1
// 		lvi.pszText = strFrequency.GetBuffer(strFrequency.GetLength()+1); ;
// 		lvi.iSubItem = 1;
// 		m_FrequencyListCtrl.SetColumn(1 ));

		// Insert band number
		item.mask           = LVIF_TEXT;
		item.iItem          = i;
		item.iSubItem		= 0;
		item.iSubItem		= 0;
		item.pszText		= strIndex.GetBuffer(strIndex.GetLength()+1);
		m_FrequencyListCtrl.InsertItem(&item);            // Use InsertItem here

		// Insert frequency band
		item.mask           = LVIF_TEXT;
		item.iItem          = i;
		item.iSubItem		= 1;
		item.pszText		= strFrequency.GetBuffer(strFrequency.GetLength()+1);
		m_FrequencyListCtrl.SetItem(&item);                  // For extra columns, use SetItem

		// Insert band state
		item.mask			= LVIF_TEXT;
		item.iItem			= i;
		item.iSubItem		= 2;
		item.pszText		= strState.GetBuffer(strState.GetLength()+1);
		m_FrequencyListCtrl.SetItem(&item);                  // For extra columns, use SetItem

		i++;
	}

//	SortList(1, true);

	AfxGetApp()->DoWaitCursor(-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

bool CFrequencyBandPage::SortList(int nColumn, bool bAscending)
{
	m_nSortedCol	= nColumn;
	
	// Resort contents if sorted before
	if (m_nSortedCol >= 0)
	{
		m_FrequencyListCtrl.SortList(nColumn, bAscending);

		CSortClass csc(&m_FrequencyListCtrl, m_nSortedCol);

		switch(m_nSortedCol)
		{
		case 0:
			csc.Sort(bAscending, DT_STRING);
			break;
		case 1:
			csc.Sort(bAscending, DT_STRING);
			break;
// 		case 2:
// 			csc.Sort(bAscending, DT_DEC);
// 			break;
// 		case 3:
// 			csc.Sort(bAscending, DT_DEC);
// 			break;
// 		case 4:
// 			csc.Sort(bAscending, DT_DEC);
// 			break;
// 		case 5:
// 			csc.Sort(bAscending, DT_INT);
// 			break;
// 		case 6:
// 			csc.Sort(bAscending, DT_INT);
// 			break;
// 		case 7:
// 			csc.Sort(bAscending, DT_STRING);
// 			break;
// 		case 8:
// 			csc.Sort(bAscending, DT_STRING);
// 			break;
// 		case 9:
// 			csc.Sort(bAscending, DT_DATETIME);
		}

		m_FrequencyListCtrl.SetRedraw(TRUE);

		return true;
	}

	return false;
}

void CFrequencyBandPage::OnHdnItemclickListFrequencyBand(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here

	if(phdr->hdr.code == HDN_ITEMCLICKA ||
		phdr->hdr.code == HDN_ITEMCLICKW)
	{
//		if (phdr->iItem == m_FrequencyListCtrl.m_nSortedCol)
//			SortList(phdr->iItem, !m_FrequencyListCtrl.m_bAscending);
//		else
			SortList(phdr->iItem, true);
	}

	*pResult = 0;
}
