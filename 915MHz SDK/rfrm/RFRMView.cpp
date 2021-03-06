// RFRMView.cpp : implementation of the CRFRMView class
//

#include "stdafx.h"
#include "RFRM.h"

#include "RFRMDoc.h"
#include "RFRMView.h"

#include "MainFrm.h"
#include "RFIDRadioManager.h"
#include "SortClass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TAGINFO_ID				0		
#define TAGINFO_TOTAL_READ		1		

// CRFRMView

IMPLEMENT_DYNCREATE(CRFRMView, CListViewEx)

BEGIN_MESSAGE_MAP(CRFRMView, CListViewEx)
//	ON_WM_CREATE()
	ON_COMMAND(ID_LIST_ICON, &CRFRMView::OnListIcon)
	ON_COMMAND(ID_LIST_LIST, &CRFRMView::OnListList)
	ON_COMMAND(ID_LIST_REPORT, &CRFRMView::OnListReport)
	ON_UPDATE_COMMAND_UI(ID_LIST_ICON, &CRFRMView::OnUpdateListIcon)
	ON_UPDATE_COMMAND_UI(ID_LIST_LIST, &CRFRMView::OnUpdateListList)
	ON_UPDATE_COMMAND_UI(ID_LIST_REPORT, &CRFRMView::OnUpdateListReport)
	ON_COMMAND(ID_LIST_SMALL_ICON, &CRFRMView::OnListSmallIcon)
	ON_UPDATE_COMMAND_UI(ID_LIST_SMALL_ICON, &CRFRMView::OnUpdateListSmallIcon)
//	ON_MESSAGE(WM_RECEIVE_TAG, &CRFRMView::OnReceiveTag)
	ON_MESSAGE(WM_PROCESS_TAG, &CRFRMView::OnProcessTag)
	ON_MESSAGE(WM_STATUS_MSG, &CRFRMView::OnStatusMSg)
	ON_BN_CLICKED(IDC_CLEAR_BUTTON, &CRFRMView::OnClearButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_RFID_SERVERCONNECT, &CRFRMView::OnRfidServerconnect)
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()

// CRFRMView construction/destruction

CRFRMView::CRFRMView()
: m_bItemClick(FALSE)
, m_nItemClick(-1)
{
	// TODO: add construction code here

}

CRFRMView::~CRFRMView()
{
}

BOOL CRFRMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style&=~LVS_TYPEMASK;
	cs.style|= LVS_ICON | LVS_EX_ONECLICKACTIVATE;/*| LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE*/

	return CListViewEx::PreCreateWindow(cs);
}

void CRFRMView::OnInitialUpdate()
{
	CListViewEx::OnInitialUpdate();

 	CListCtrl& listCtrl = (CListCtrl&)GetListCtrl();
	CRect clientRect;

#ifndef _WIN32_WCE
 	listCtrl.SetExtendedStyle( LVS_EX_FULLROWSELECT );
#endif

	SetViewType(LVS_REPORT);
	InitListCtrl();

	WSADATA wsaData;

	WSAStartup(MAKEWORD(2,2), &wsaData);
}


// CRFRMView diagnostics

#ifdef _DEBUG
void CRFRMView::AssertValid() const
{
	CListViewEx::AssertValid();
}
CRFRMDoc* CRFRMView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRFRMDoc)));
	return (CRFRMDoc*)m_pDocument;
}
#endif //_DEBUG

DWORD CRFRMView::GetViewType()
{
	return (GetStyle() & LVS_TYPEMASK); 
}

BOOL CRFRMView::SetViewType(DWORD dwViewType)
{ 
	return (ModifyStyle(LVS_TYPEMASK, dwViewType & LVS_TYPEMASK)); 
} 

void CRFRMView::OnListIcon()
{
	if( GetViewType() != LVS_ICON )
		SetViewType(LVS_ICON);
}

void CRFRMView::OnListSmallIcon()
{
	if( GetViewType() != LVS_SMALLICON )
		SetViewType(LVS_SMALLICON);
}

void CRFRMView::OnListList()
{
	if( GetViewType() != LVS_LIST )
		SetViewType(LVS_LIST);
}

void CRFRMView::OnListReport()
{
	if( GetViewType() != LVS_REPORT )
		SetViewType(LVS_REPORT);
}

void CRFRMView::OnUpdateListIcon(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetViewType() == LVS_ICON);
}

void CRFRMView::OnUpdateListSmallIcon(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetViewType() == LVS_SMALLICON);
}

void CRFRMView::OnUpdateListList(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetViewType() == LVS_LIST);
}

void CRFRMView::OnUpdateListReport(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetViewType() == LVS_REPORT);
}

//Tag 통계부분
LRESULT CRFRMView::OnProcessTag(WPARAM wParam, LPARAM lParam)
{
	LPCWSTR	pString = reinterpret_cast<LPCWSTR>(wParam);
	CTagInfo* lpTagInfo = (CTagInfo*)pString;

	CRFRMDoc* pDoc = GetDocument();
	CPtrList* tagList = pDoc->GetTagList();
	
//	POSITION pos;
	BOOL bFindFlag = FALSE;

	if(!tagList->IsEmpty())
	{
		//		pos = tagList->GetHeadPosition();
		for(__int32 index= 0 ; index < tagList->GetSize(); index++)
		{
//			pos = tagList->FindIndex(index);
			CTagInfo* lpTagInfoExist = (CTagInfo*)tagList->GetAt(tagList->FindIndex(index));

			if(lpTagInfoExist->GetTagString() == lpTagInfo->GetTagString())
			{
				lpTagInfoExist->AddReadCount(lpTagInfo->GetTagReadCount());
				lpTagInfoExist->SetTagReadCount(lpTagInfo->GetTagReadCount());
				lpTagInfoExist->SetTagTrialCount(lpTagInfo->GetTagTrialCount());
				lpTagInfoExist->SetTagAntenna(lpTagInfo->GetTagAntenna());
				lpTagInfoExist->SetTagChannel(lpTagInfo->GetTagChannel());
				lpTagInfoExist->SetTagRSSI(lpTagInfo->GetTagRSSI());
				lpTagInfoExist->SetTagLNAGain(lpTagInfo->GetTagLNAGain());
				lpTagInfoExist->SetTagReveiveTime(lpTagInfo->GetTagReceiveTime());

				// Tag 정보 List 추가
				tagList->SetAt(tagList->FindIndex(index), lpTagInfoExist);	// 새로운 Tag정보를 기존정보 위치에 넣고

				
				//			if(lpTagInfoExist != NULL)
				//				delete lpTagInfoExist;

				// List Ctrl Update
				UpdateTagData(lpTagInfoExist);//ListCtrl 변경
				
				bFindFlag = TRUE;
				break;
			}
		}
	}

	if(!bFindFlag) 
	{
		// 새로운 정보이면 추가
		CTagInfo* newTagInfo = new CTagInfo();

		// Tag 정보 Copy
		newTagInfo->SetTagPC(lpTagInfo->GetTagPC());
		newTagInfo->SetTagEPC(lpTagInfo->GetTagEPC()); // = lpTagInfo->strTagId;
		newTagInfo->AddReadCount(lpTagInfo->GetTagReadCount());// = lpTagInfo->read_count;
		newTagInfo->SetTagReadCount(lpTagInfo->GetTagReadCount());// = lpTagInfo->read_count;
		newTagInfo->SetTagTrialCount(lpTagInfo->GetTagTrialCount());
		newTagInfo->SetTagAntenna(lpTagInfo->GetTagAntenna());
		newTagInfo->SetTagChannel(lpTagInfo->GetTagChannel());
		newTagInfo->SetTagRSSI(lpTagInfo->GetTagRSSI());
		newTagInfo->SetTagLNAGain(lpTagInfo->GetTagLNAGain());
		newTagInfo->SetTagReveiveTime(lpTagInfo->GetTagReceiveTime());

		// Tag 정보 List 추가
		tagList->AddTail(newTagInfo);

		//fwrite(prp->readPkt.buffer, 1, prp->readPkt.count, m_hFile);

//		m_pSocket.SendData(lpTagInfo->GetTagString());

		// List Control에 정보 display
		InsertTagData(newTagInfo);
	}

	delete lpTagInfo;

	return 0;
}

LRESULT CRFRMView::OnStatusMSg(WPARAM wParam, LPARAM lParam)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	BOOL bInvalide = (BOOL)lParam;

	pFrame->SetStatusBar(0, (CString)(LPCTSTR)wParam);

	return TRUE;
}

void CRFRMView::PostNcDestroy()
{
	CListViewEx::PostNcDestroy();
}

void CRFRMView::InitListCtrl(void)
{
	CString strColumn;
	CRect rect;
	CListCtrl& listCtrl = GetListCtrl();
	CBitmap bmpSmallImage, bmpNormalImage;

	bmpSmallImage.LoadBitmap(IDB_BITMAP_16);
	bmpNormalImage.LoadBitmap(IDB_BITMAP_24);

	// Create a image list and assign it to the list control
	VERIFY(m_smallImageList.Create(16, 16, ILC_COLOR24 |ILC_MASK, 1, 0));
	VERIFY(m_largeImageList.Create(24, 24, ILC_COLOR24 |ILC_MASK, 1, 0));

	m_smallImageList.Add(&bmpSmallImage, RGB(255,255,255));
	m_largeImageList.Add(&bmpNormalImage, RGB(255,255,255));

	listCtrl.SetImageList(&m_smallImageList, LVSIL_SMALL);
	listCtrl.SetImageList(&m_largeImageList, LVSIL_NORMAL);

	// 반드시 분리한다
	m_largeImageList.Detach();
	bmpSmallImage.Detach();    
	m_largeImageList.Detach();
	bmpNormalImage.Detach();

	GetClientRect(&rect);



#ifdef _WIN32_WCE
	if(strColumn.LoadString(IDS_LC_ID))
		AddColumn(strColumn, 190);

	if(strColumn.LoadString(IDS_LC_PC))
	{
		AddColumn(strColumn, 40);
		this->ShowColumn(1, false);
	}

	if(strColumn.LoadString(IDS_LC_TOTALCOUNT))
		AddColumn(strColumn, 35);

	if(strColumn.LoadString(IDS_LC_READCOUNT))
	{
		AddColumn(strColumn, 100);
		this->ShowColumn(3, false);
	}

	if(strColumn.LoadString(IDS_LC_TRIALCOUNT))
	{
		AddColumn(strColumn, 80);
		this->ShowColumn(4, false);
	}

	if(strColumn.LoadString(IDS_LC_ANTENNA))
	{
		AddColumn(strColumn, 80);
		this->ShowColumn(5, false);
	}

	if(strColumn.LoadString(IDS_LC_CHANNEL))
	{
		AddColumn(strColumn, 80);
		this->ShowColumn(6, false);
	}

	if(strColumn.LoadString(IDS_LC_RSSI))
	{
		AddColumn(strColumn, 80);
		this->ShowColumn(7, false);
	}

	if(strColumn.LoadString(IDS_LC_LNAGAIN))
	{
		AddColumn(strColumn, 80);
		this->ShowColumn(8, false);
	}

	if(strColumn.LoadString(IDS_LC_RECEIVETIME))
	{
		AddColumn(strColumn, 100);
		this->ShowColumn(9, false);
	}
#else
	if(strColumn.LoadString(IDS_LC_ID))
		AddColumn(strColumn, 200);

	if(strColumn.LoadString(IDS_LC_PC))
	{
		AddColumn(strColumn, 60);
		this->ShowColumn(1, false);
	}

	if(strColumn.LoadString(IDS_LC_TOTALCOUNT))
		AddColumn(strColumn,		100);

	if(strColumn.LoadString(IDS_LC_READCOUNT))
		AddColumn(strColumn,		100);

	if(strColumn.LoadString(IDS_LC_TRIALCOUNT))
		AddColumn(strColumn,		80);

	if(strColumn.LoadString(IDS_LC_ANTENNA))
		AddColumn(strColumn,			80);
	
	if(strColumn.LoadString(IDS_LC_CHANNEL))
		AddColumn(strColumn,			80);
	
	if(strColumn.LoadString(IDS_LC_RSSI))
		AddColumn(strColumn,			80);
	
	if(strColumn.LoadString(IDS_LC_LNAGAIN))
		AddColumn(strColumn,			80);
	
	if(strColumn.LoadString(IDS_LC_RECEIVETIME))
		AddColumn(strColumn,		100);

#endif

//	listCtrl.SetHeadings( _T("Tag ID,120;Total Count,90;Read Count,50,Trial Count, 50, Antenna, 50, Channel, 50, Receive Time, 100 ") );

}

void CRFRMView::InsertTagData(CTagInfo* pTagInfo)
{
	CString strData;
	ULONG	dTotalRead = 0;
	CListCtrl& listCtrl = GetListCtrl();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CRFRMDoc* pDoc = GetDocument();

	CString temp; 

	int nCount = listCtrl.GetItemCount();

	// Display Searching

	RFID_TAG_DISPLAY_MODE mode = AfxGetApp()->GetProfileInt(_T("Engineering"),_T("Display"), 0);
	switch(mode)
	{
	case RFID_TAG_DISPLAY_MODE_EPC:
		{
			InsertTagItem(nCount, TAGINFO_EPC, pTagInfo->GetTagString());
			temp =  pTagInfo->GetTagString();
			temp += _T(",");
		}
		break;

	case RFID_TAG_DISPLAY_MODE_ASCII:
		{
			InsertTagItem(nCount, TAGINFO_EPC, pTagInfo->GetTagAsciiString());
			temp =  pTagInfo->GetTagAsciiString();
			temp += _T(",");
		}
		break;
	}

	InsertTagItem(nCount, TAGINFO_PC, pTagInfo->GetTagPCString());
	temp =  pTagInfo->GetTagPCString();
	temp += _T(",");


//	int nCnt = atoi(1);
//	for (int n = 0; n < 1 ; n++)

//	m_pSocket.SendData(pTagInfo->GetTagString());
	m_pSocket.SendData((PBYTE)pTagInfo->GetTagEPC(), 12);

	dTotalRead = (ULONG)(pTagInfo->GetTagTotalReadCount());
	strData.Format(_T("%u"), dTotalRead);		//Total Read

	temp += strData;
	temp += _T(",");
	InsertTagItem(nCount, TAGINFO_TOTAL_COUNT, strData);

	dTotalRead = (ULONG)(pTagInfo->GetTagReadCount());
	strData.Format(_T("%u"), dTotalRead);		//Total Read
	temp += strData;
	temp += _T(",");

	InsertTagItem(nCount, TAGINFO_READ_COUNT, strData);

	if(pFrame)
		pFrame->AddTagReadCount(dTotalRead);

	dTotalRead = (ULONG)(pTagInfo->GetTagTrialCount());
	strData.Format(_T("%u"), dTotalRead);		//Total Read
	temp += strData;
	temp += _T(",");

	InsertTagItem(nCount, TAGINFO_TRIAL_COUNT, strData);

	dTotalRead = (ULONG)(pTagInfo->GetTagAntenna());
	strData.Format(_T("%u"), dTotalRead);		// Antenna Number
	temp += strData;
	temp += _T(",");

	InsertTagItem(nCount, TAGINFO_ANTENNA_NUMBER, strData);

	dTotalRead = (ULONG)(pTagInfo->GetTagChannel());
	strData.Format(_T("%u"), dTotalRead);		// Channel Number
	temp += strData;
	temp += _T(",");

	InsertTagItem(nCount, TAGINFO_CHANNEL_NUMBER, strData);

	strData.Format(_T("%2.2f dB"), (0.8 * pTagInfo->GetTagNarrowBandRSSI()));		// Narrow Band RSSI
	temp += strData;
	temp += _T(",");

	InsertTagItem(nCount, TAGINFO_RSSI, strData);

	INT8U lna = pTagInfo->GetTagLNAGain() & 0x0030;
	int	lna_gain;
	switch(lna)
	{
	case 0:
	lna_gain = 24;
	break;
	case 1:
	lna_gain = 18;
	break;
	case 3:
	lna_gain = 12;
	break;
	default:
	lna_gain = 0;
	}

	strData.Format(_T("%u dB"), lna_gain);		// Tag LNA Gain
	temp += strData;
	temp += _T(",");

	InsertTagItem(nCount, TAGINFO_LNA, strData);

	temp += pTagInfo->GetTagReceiveTime().Format(_T("%H:%M:%S"));
	temp += _T("\n");

	InsertTagItem(nCount, TAGINFO_RECEIVE_TIME, pTagInfo->GetTagReceiveTime().Format(_T("%H:%M:%S")));

	if(pFrame)
		pFrame->UpdateTagCount(listCtrl.GetItemCount());
}

void CRFRMView::UpdateTagData(CTagInfo* pTagInfo)
{
	CString strData;
	ULONG	dTotalRead = 0;
	CListCtrl& listCtrl = GetListCtrl();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CRFRMDoc* pDoc = GetDocument();

	int nCount = listCtrl.GetItemCount();

	RFID_TAG_DISPLAY_MODE mode = AfxGetApp()->GetProfileInt(_T("Engineering"),_T("Display"), 0);

	for(int Pos=0; Pos < nCount; Pos++)
	{
		switch(mode)
		{
		case RFID_TAG_DISPLAY_MODE_EPC:
			{
				if(pTagInfo->GetTagString() == listCtrl.GetItemText(Pos, 0))
				{
					strData.Format(_T("%s"), pTagInfo->GetTagPCString());	//TotalRead
					listCtrl.SetItemText(Pos, TAGINFO_PC, strData);

					strData.Format(_T("%u"), pTagInfo->GetTagTotalReadCount());	//TotalRead
					listCtrl.SetItemText(Pos, TAGINFO_TOTAL_COUNT, strData);

					strData.Format(_T("%u"), pTagInfo->GetTagReadCount());	//TotalRead
					listCtrl.SetItemText(Pos, TAGINFO_READ_COUNT, strData);

					if(pFrame)
						pFrame->AddTagReadCount(pTagInfo->GetTagReadCount());

					strData.Format(_T("%u"),pTagInfo->GetTagTrialCount());	//TotalRead
					listCtrl.SetItemText(Pos, TAGINFO_TRIAL_COUNT, strData);

					strData.Format(_T("%u"), pTagInfo->GetTagAntenna());		//Total Read
					listCtrl.SetItemText(Pos, TAGINFO_ANTENNA_NUMBER, strData);

					strData.Format(_T("%u"), pTagInfo->GetTagChannel());		//Total Read
					listCtrl.SetItemText(Pos, TAGINFO_CHANNEL_NUMBER, strData);

					strData.Format(_T("%2.2f dB"), (0.8 * pTagInfo->GetTagNarrowBandRSSI()));		//Total Read
					listCtrl.SetItemText(Pos, TAGINFO_RSSI, strData);

					INT8U lna = pTagInfo->GetTagLNAGain() & 0x0030;
					int	lna_gain;
					switch(lna)
					{
					case 0:
						lna_gain = 24;
						break;
					case 1:
						lna_gain = 18;
						break;
					case 3:
						lna_gain = 12;
						break;
					default:
						lna_gain = 0;
					}

					strData.Format(_T("%u dB"), lna_gain);		// 
					listCtrl.SetItemText(Pos, TAGINFO_LNA, strData);

					listCtrl.SetItemText(Pos, TAGINFO_RECEIVE_TIME, pTagInfo->GetTagReceiveTime().Format(_T("%H:%M:%S")));	
				}
				break;
			}
		case RFID_TAG_DISPLAY_MODE_ASCII:
			{
				if(pTagInfo->GetTagAsciiString() == listCtrl.GetItemText(Pos, 0))
				{
					strData.Format(_T("%s"),pTagInfo->GetTagPCString());	//TotalRead
					listCtrl.SetItemText(Pos, TAGINFO_PC, strData);

					strData.Format(_T("%u"),pTagInfo->GetTagTotalReadCount());	//TotalRead
					listCtrl.SetItemText(Pos, TAGINFO_TOTAL_COUNT, strData);

					strData.Format(_T("%u"),pTagInfo->GetTagReadCount());	//TotalRead
					listCtrl.SetItemText(Pos, TAGINFO_READ_COUNT, strData);

					if(pFrame)
						pFrame->AddTagReadCount(pTagInfo->GetTagReadCount());

					strData.Format(_T("%u"),pTagInfo->GetTagTrialCount());	//TotalRead
					listCtrl.SetItemText(Pos, TAGINFO_TRIAL_COUNT, strData);

					strData.Format(_T("%u"), pTagInfo->GetTagAntenna());		//Total Read
					listCtrl.SetItemText(Pos, TAGINFO_ANTENNA_NUMBER, strData);

					strData.Format(_T("%u"), pTagInfo->GetTagChannel());		//Total Read
					listCtrl.SetItemText(Pos, TAGINFO_CHANNEL_NUMBER, strData);

					strData.Format(_T("%2.2f dB"), (0.8 * pTagInfo->GetTagNarrowBandRSSI()));		//Total Read
					listCtrl.SetItemText(Pos, TAGINFO_RSSI, strData);

					INT8U lna = pTagInfo->GetTagLNAGain() & 0x0030;
					int	lna_gain;
					switch(lna)
					{
					case 0:
						lna_gain = 24;
						break;
					case 1:
						lna_gain = 18;
						break;
					case 3:
						lna_gain = 12;
						break;
					default:
						lna_gain = 0;
					}

					strData.Format(_T("%u dB"), lna_gain);		// 
					listCtrl.SetItemText(Pos, TAGINFO_LNA, strData);

					listCtrl.SetItemText(Pos, TAGINFO_RECEIVE_TIME, pTagInfo->GetTagReceiveTime().Format(_T("%H:%M:%S")));	
				}
				break;
			}
		}
	}
}

BOOL CRFRMView::InsertTagItem(int nItem, int nSubItem, LPCWSTR strItem, int mask, int iImage)
{
	LV_ITEM         lvitem;
	CString			szText;
	CListCtrl& listCtrl = GetListCtrl();


	memset(&lvitem,0,sizeof(LV_ITEM));
	lvitem.mask = mask;
	lvitem.iItem = nItem;
	lvitem.iSubItem = nSubItem;
	lvitem.pszText = szText.GetBuffer(wcslen(strItem));
	lvitem.iImage = iImage;

	wcscpy (lvitem.pszText, strItem);

	if (nSubItem == 0)
	{
		if(listCtrl.InsertItem(&lvitem) == -1) // insert new item
			return false; 
	}

	return(listCtrl.SetItem(&lvitem)); // modify existing item (the sub-item text)}
}

void CRFRMView::OnClearButton()
{
	CRFRMDoc* pDoc = GetDocument();
	CListCtrl& listCtrl = GetListCtrl();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	CPtrList* pTagList = (CPtrList*) pDoc->GetTagList();
	POSITION pos = pTagList->GetHeadPosition();

	while(pos)
	{
		CTagInfo* pTagInfo = (CTagInfo*)pTagList->GetNext(pos);

		delete pTagInfo;
		pTagInfo = NULL;
	}

	pTagList->RemoveAll();
	
	listCtrl.DeleteAllItems();

	if(pFrame)
	{
		pFrame->UpdateTagCount(0);
		pFrame->UpdateTagReadCount(0);
	}
}

void CRFRMView::OnLButtonDown(UINT nFlags, CPoint point)
{
	UINT			uFlags;
	CListCtrl& listCtrl = GetListCtrl();

	CPoint pt = point;
	ClientToScreen(&pt);

	// List Control Hit Test
	if( ( m_nItemClick = listCtrl.HitTest( point, &uFlags )) != -1 )
	{
		// Set focus to selected item
		listCtrl.SetItemState( m_nItemClick, LVIS_SELECTED | LVIS_FOCUSED ,
			LVIS_SELECTED | LVIS_FOCUSED);


		// comparing of hit test between flag and result of hit test  
		if(uFlags & LVHT_ONITEMLABEL || uFlags & LVHT_ONITEMICON)
		{
			POSITION pos;
			CTagInfo* selectedTag;

			m_bItemClick = TRUE;
			CString strEPC = listCtrl.GetItemText(m_nItemClick, 0);

			CRFRMDoc* pDoc = GetDocument();
			CPtrList* tagList = pDoc->GetTagList();

			for(__int32 index= 0 ; index < tagList->GetCount(); index++)
			{
				pos = tagList->FindIndex(index);
				selectedTag = (CTagInfo*)tagList->GetAt(pos);

				if(selectedTag->GetTagString() == strEPC)
				{
					pDoc->SetSelectedTag(selectedTag);
				}
			}
		}
	}
	else
	{
		m_bItemClick = FALSE;

		CRFRMDoc* pDoc = GetDocument();
		pDoc->SetSelectedTag(NULL);
	}

	CListViewEx::OnLButtonDown(nFlags, point);
}
/*
void CRFRMView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu; 
	VERIFY( menu.LoadMenu( IDR_MENU_TAG_ACCESS ) ); 
	CMenu* popup = menu.GetSubMenu(0); 

	ASSERT( popup != NULL ); 

	popup->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd()); 
}
*/
void CRFRMView::OnRButtonDown(UINT nFlags, CPoint point)
{
	UINT			uFlags;
	CListCtrl& listCtrl = GetListCtrl();

	CPoint pt = point;
	ClientToScreen(&pt);

	// List Control Hit Test
	if( ( m_nItemClick = listCtrl.HitTest( point, &uFlags )) != -1 )
	{
		// Set focus to selected item
		listCtrl.SetItemState( m_nItemClick, LVIS_SELECTED | LVIS_FOCUSED ,
			LVIS_SELECTED | LVIS_FOCUSED);


		// comparing of hit test between flag and result of hit test  
		if(uFlags & LVHT_ONITEMLABEL || uFlags & LVHT_ONITEMICON)
		{
			POSITION pos;
			CTagInfo* selectedTag;

			m_bItemClick = TRUE;
			CString strEPC = listCtrl.GetItemText(m_nItemClick, 0);

			CRFRMDoc* pDoc = GetDocument();
			CPtrList* tagList = pDoc->GetTagList();

			for(__int32 index= 0 ; index < tagList->GetCount(); index++)
			{
				pos = tagList->FindIndex(index);
				selectedTag = (CTagInfo*)tagList->GetAt(pos);

				if(selectedTag->GetTagString() == strEPC)
				{
					pDoc->SetSelectedTag(selectedTag);
				}
			}
		}
	}
	else
	{
		m_bItemClick = FALSE;

		CRFRMDoc* pDoc = GetDocument();
		pDoc->SetSelectedTag(NULL);
	}


	CListViewEx::OnRButtonDown(nFlags, point);
}

#include "ServerIPDlg.h"

void CRFRMView::OnRfidServerconnect()
{
	CServerIPDlg dlg;

	if(dlg.DoModal() == IDOK)
	{
		m_pSocket.Init(dlg.m_strIPAddress, 999, m_hWnd);
	}

}

bool CRFRMView::SortList(int nColumn, bool bAscending)
{
	m_nSortedCol	= nColumn;
	m_bAscending	= bAscending;

	// Resort contents if sorted before
	if (m_nSortedCol >= 0)
	{
		CListCtrl& listctrl = GetListCtrl();
		CListViewEx::SortList(nColumn, bAscending);

		CSortClass csc(&listctrl,m_nSortedCol);

		switch(m_nSortedCol)
		{
		case 0:
			csc.Sort(bAscending, DT_STRING);
			break;
		case 1:
			csc.Sort(bAscending, DT_STRING);
			break;
		case 2:
			csc.Sort(bAscending, DT_DEC);
			break;
		case 3:
			csc.Sort(bAscending, DT_DEC);
			break;
		case 4:
			csc.Sort(bAscending, DT_DEC);
			break;
		case 5:
			csc.Sort(bAscending, DT_INT);
			break;
		case 6:
			csc.Sort(bAscending, DT_INT);
			break;
		case 7:
			csc.Sort(bAscending, DT_STRING);
			break;
		case 8:
			csc.Sort(bAscending, DT_STRING);
			break;
		case 9:
			csc.Sort(bAscending, DT_DATETIME);
		}
		
		GetListCtrl().SetRedraw(TRUE);

		return true;
	}

	return false;
}

BOOL CRFRMView::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	HD_NOTIFY *pHDNotify = (HD_NOTIFY*)lParam;
	if(pHDNotify->hdr.code == HDN_ITEMCLICKA ||
		pHDNotify->hdr.code == HDN_ITEMCLICKW)
	{
		m_bAscending = !m_bAscending;
		
		if (pHDNotify->iItem == m_nSortedCol)
			SortList(pHDNotify->iItem, !m_bAscending);
		else
			SortList(pHDNotify->iItem, !m_bAscending);
	}
	return CListViewEx::OnNotify(wParam, lParam, pResult);
}

void CRFRMView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if(m_bItemClick)
	{
		CPoint pt = point;
		ClientToScreen(&pt);

		CMenu menu; 
		VERIFY( menu.LoadMenu( IDR_MENU_TAG_ACCESS ) ); 
		CMenu* popup = menu.GetSubMenu(0); 

		ASSERT( popup != NULL ); 

		popup->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd()); 
	}
	else
	{
		CListViewEx::OnContextMenu(pWnd, point);
	}
}
