// CJListView.cpp : implementation file
// Copyright ?1998-1999 CodeJock.com, All Rights Reserved.
// See ReadMe.txt for TERMS OF USE.
//
// Based on the CListView articles from http://www.codeguru.com/listview
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ListViewEx.h"
#include "HeaderCtrlEx.h"
#include "Resource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef HDF_SORTUP
	#define HDF_SORTUP              0x0400
	#define HDF_SORTDOWN            0x0200
#endif

namespace techwin
{
/////////////////////////////////////////////////////////////////////////////
// CListViewEx

IMPLEMENT_DYNCREATE(CListViewEx, CListView)

CListViewEx::CListViewEx()
{
	m_nMinSize		= 0;
	m_nMinColWidth	= 50;
	m_nMaxColWidth	= 500;
	m_nSortedCol	= -1;
	m_bAscending	= true;
	m_bAutoSave		= false;	
	m_bNoColSizing	= false;
	m_pHeaderCtrl	= NULL;
	m_pListCtrl		= NULL;
	m_clrText		= CLR_DEFAULT;
	m_clrTextBk 	= CLR_DEFAULT;
}
	

CListViewEx::~CListViewEx()
{
	delete( m_pHeaderCtrl );
}

BEGIN_MESSAGE_MAP(CListViewEx, CListView)
	//{{AFX_MSG_MAP(CListViewEx)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, OnCustomDraw)
	ON_WM_DESTROY()
	ON_MESSAGE(LVM_DELETECOLUMN, OnDeleteColumn)
	ON_MESSAGE(LVM_INSERTCOLUMN, OnInsertColumn)
	ON_MESSAGE(LVM_SETCOLUMNWIDTH, OnSetColumnWidth)
	ON_NOTIFY_EX(HDN_BEGINTRACKA, 0, OnHeaderBeginResize)
	ON_NOTIFY_EX(HDN_BEGINTRACKW, 0, OnHeaderBeginResize)
	ON_NOTIFY_EX(HDN_ENDDRAG, 0, OnHeaderEndDrag)
	ON_NOTIFY_EX(HDN_DIVIDERDBLCLICKA, 0, OnHeaderDividerDblClick)
	ON_NOTIFY_EX(HDN_DIVIDERDBLCLICKW, 0, OnHeaderDividerDblClick)
	ON_WM_CONTEXTMENU()	// OnContextMenu
	ON_WM_KEYDOWN()		// OnKeyDown
//	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListViewEx drawing

void CListViewEx::OnDraw( CDC* pDC )
{
	UNUSED_ALWAYS( pDC );
}

/////////////////////////////////////////////////////////////////////////////
// CListViewEx diagnostics

#ifdef _DEBUG
void CListViewEx::AssertValid() const
{
	CListView::AssertValid();
}

#ifndef _WIN32_WCE
void CListViewEx::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif // _WIN32_WCE
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListViewEx message handlers

void CListViewEx::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// Set a pointer to the list control.
	m_pListCtrl = &GetListCtrl();
	m_pHeaderCtrl = (CHeaderCtrlEx*)m_pListCtrl->GetHeaderCtrl();

#ifdef _WIN32_WCE
	CFont* listfont;
	LOGFONT lfont;

	listfont = m_pListCtrl->GetFont(); // m_ListCtrl is control variable of your list control 
	listfont->GetLogFont(&lfont);

	lfont.lfHeight=13;  // change height or other parameters for more see LOGFONT struct

	listfont->CreateFontIndirect(&lfont);
	m_pListCtrl->SetFont(listfont); 
#endif

}

// Taken from: Copying/Moving Rows in CListCtrl by James Spibey [spib@bigfoot.com]. 
// http://www.codeguru.com/listview/moving_rows.html
bool CListViewEx::MoveRow(int nFrom, int nTo)
{
	//Can't move to the same place, or from or to a negative index
	if(nFrom == nTo || nFrom < 0 || nTo < 0)
		return false;
	
	//First Copy the row to the new location
	if(CopyRow(nFrom, nTo))
	{
		//If we have just inserted a row before
		//this one in the list, we need to increment
		//our index.
		if(nFrom > nTo)
			m_pListCtrl->DeleteItem(nFrom + 1);
		else
			m_pListCtrl->DeleteItem(nFrom);
		
		return true;
	}
	else
		return false;
}

// Taken from: Copying/Moving Rows in CListCtrl by James Spibey [spib@bigfoot.com]. 
// http://www.codeguru.com/listview/moving_rows.html
bool CListViewEx::CopyRow(int nFrom, int nTo)
{
	//Can't move to the same place, or from or to a negative index
	if(nFrom == nTo || nFrom < 0 || nTo < 0)
		return false;

	//Copy the row to the new index
	m_pListCtrl->InsertItem(nTo, m_pListCtrl->GetItemText(nFrom, 0));

	//If row has been inserted before original
	//increment the original
	if(nFrom > nTo)
		nFrom++;

	//Loop through subitems
	for(int i = 1; i < GetColumnCount(); i++)
	{
		m_pListCtrl->SetItemText(nTo, i, m_pListCtrl->GetItemText(nFrom, i));
	}

	return true;
}

// Taken from: Getting the number of columns in report view by Zafir Anjum.
// http://www.codeguru.com/listview/num_cols.shtml
int CListViewEx::GetColumnCount() const
{
	CHeaderCtrl* pHeader = (CHeaderCtrl*)m_pListCtrl->GetDlgItem(0);
	return pHeader->GetItemCount();
}

// Taken from: Simpler way to do this (using new version of Comctl32.dll) by Vidas [vibal@lrtc.lt].
// http://www.codeguru.com/mfc/comments/6432.shtml
void CListViewEx::OnCustomDraw(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMLVCUSTOMDRAW lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;
	
    switch(lplvcd->nmcd.dwDrawStage)
	{
	case CDDS_PREPAINT:
		// Request prepaint notifications for each item.
		*pResult = CDRF_NOTIFYITEMDRAW;
		break;
		
    case CDDS_ITEMPREPAINT: // Requested notification
		if(lplvcd->nmcd.dwItemSpec >= 0)		// Was dwItemSpec % 2 before!
		{										// AJM 11.9.2000 [andy.metcalfe@lineone.net]
			lplvcd->clrText   = m_clrText;

			// Only change the background colour if the window is enabled
			// Otherwise, use the system default
			// AJM 11.9.2000 [andy.metcalfe@lineone.net]
			if (IsWindowEnabled() )
			{
				lplvcd->clrTextBk = m_clrTextBk;
			}
		}
		*pResult = CDRF_DODEFAULT;
		break;
	}
}

BOOL CListViewEx::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	HD_NOTIFY *pHDNotify = (HD_NOTIFY*)lParam;

	switch( pHDNotify->hdr.code )
	{
	// Sorting the list when user clicks on column header by Zafir Anjum.
	// http://www.codeguru.com/listview/sort_on_col_click.shtml
	case HDN_ITEMCLICKA:
	case HDN_ITEMCLICKW:
		{
			if( pHDNotify->iButton == 0 )
			{
				bool bAscending = m_bAscending;

				// set the sort order.
				if( pHDNotify->iItem == m_nSortedCol )
					bAscending = !bAscending;
				else
					bAscending = true;

				// virtual call to sort list.
				SortList(pHDNotify->iItem, bAscending );

				// set the sort image in the header control.
				// Moved to SortList() AJM 3.3.2001
				//if( m_pHeaderCtrl && m_pHeaderCtrl->GetSafeHwnd( ))
				//	m_pHeaderCtrl->SetSortImage( m_nSortedCol, m_bAscending );
			}
		}
		break;

	// How to force a minimum column width Cees Mechielsen.
	// http://www.codeguru.com/mfc/comments/866.shtml
	case HDN_ITEMCHANGINGA:
	case HDN_ITEMCHANGINGW:
	case HDN_ENDTRACK:
		{
			if( pHDNotify->pitem->mask & HDI_WIDTH &&
				pHDNotify->pitem->cxy < m_nMinSize &&
				pHDNotify->pitem->cxy >= 0 )
			{
				pHDNotify->pitem->cxy = m_nMinSize;	// Set the column width
			}
		}
		break;

	// Prevent CListCtrl column resizing by Zafir Anjum.
	// http://www.codeguru.com/listview/no_col_resize.shtml
	case HDN_DIVIDERDBLCLICKA:
	case HDN_DIVIDERDBLCLICKW:
	case HDN_BEGINTRACKW:
	case HDN_BEGINTRACKA:
		{
			if(m_bNoColSizing)
			{
				*pResult = TRUE;                // disable tracking
				return TRUE;                    // Processed message
			}
			break;
		}
	}

	return CListView::OnNotify(wParam, lParam, pResult);
}

bool CListViewEx::SortList(int nCol, bool bAscending)
{
#ifdef _DEBUG
	//TRACE2("Column sort on column index %d, ascending=%d\n", nCol, bAscending);
#endif
	// Set the sort image in the header control.
	// AJM 3.3.2001
	SetSortImage( nCol, bAscending );

	return true;
}


// Taken from: Adding a column by Zafir Anjum.
// http://www.codeguru.com/listview/add_column.shtml

// AddColumn      - adds column after the right most column
// Returns        - the index of the new column if successful or -1 otherwise.
// lpszColHeading - the column's heading
// nWidth         - Width of the column, in pixels. If this parameter is -1, 
//                  the column width is the same as previous column
// nFormat        - the alignment of the column. Can be LVCFMT_LEFT,
//                  LVCFMT_RIGHT, or LVCFMT_CENTER.
int CListViewEx::AddColumn(LPCTSTR lpszColHeading, int nWidth/*=-1*/, int nFormat/*=LVCFMT_LEFT*/)
{
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();
	
	if( nWidth == -1 )
	{
		// The line below return zero for ICON views
		//nWidth = GetColumnWidth( nColumnCount - 1 );
		
		// Get the column width of the previous column from header control
		HD_ITEM hd_item;
		hd_item.mask = HDI_WIDTH;               //indicate that we want the width
		pHeader->GetItem( nColumnCount - 1, &hd_item );
		nWidth = hd_item.cxy;
	}

	return m_pListCtrl->InsertColumn( nColumnCount, lpszColHeading, nFormat, nWidth, nColumnCount );
}

bool CListViewEx::BuildColumns(int nCols, int* nWidth, int* nColString)
{
	for( int i = 0; i < nCols; ++i ) {
		CString	strTemp; strTemp.LoadString( nColString[i] );
		if(AddColumn(strTemp, nWidth[i])==-1)
			return false;
	}

	return true;
}

bool CListViewEx::BuildColumns(int nCols, int* nWidth, CString* strColString)
{
	for( int i = 0; i < nCols; ++i ) {
		if(AddColumn(strColString[i], nWidth[i])==-1)
			return false;
	}

	return true;
}

// Taken from: Detecting column index of the item clicked by Zafir Anjum.
// http://www.codeguru.com/listview/col_index.shtml

// HitTestEx	- Determine the row index and column index for a point
// Returns		- the row index or -1 if point is not over a row
// point		- point to be tested.
// nCol			- to hold the column index
int CListViewEx::HitTestEx(CPoint& point, int* nCol) const
{
	int colnum = 0;
	int row = m_pListCtrl->HitTest( point, NULL );
	
	if( nCol ) *nCol = 0;

	// Make sure that the ListView is in LVS_REPORT
	if( (GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT )
		return row;

	// Get the top and bottom row visible
	row = m_pListCtrl->GetTopIndex();
	int bottom = row + m_pListCtrl->GetCountPerPage();
	if( bottom > m_pListCtrl->GetItemCount() )
		bottom = m_pListCtrl->GetItemCount();
	
	// Get the number of columns
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();

	// Loop through the visible rows
	for( ;row <= bottom;row++)
	{
		// Get bounding rect of item and check whether point falls in it.
		CRect rect;
		m_pListCtrl->GetItemRect( row, &rect, LVIR_BOUNDS );
		if( rect.PtInRect(point) )
		{
			// Now find the column
			for( colnum = 0; colnum < nColumnCount; colnum++ )
			{
				int colwidth = m_pListCtrl->GetColumnWidth(colnum);
				if( point.x >= rect.left 
					&& point.x <= (rect.left + colwidth ) )
				{
					if( nCol ) *nCol = colnum;
					return row;
				}
				rect.left += colwidth;
			}
		}
	}
	return -1;
}



void CListViewEx::SetThemeHelper(CThemeHelperEx* pTheme)
{
	m_pTheme = pTheme;
}


int CListViewEx::SetSortImage(int nCol, bool bAsc)
{
	int nPrevCol = m_nSortedCol;

	m_nSortedCol	= nCol;
	m_bAscending	= bAsc;

	if (NULL != m_pHeaderCtrl)
	{
		return m_pHeaderCtrl->SetSortImage( m_nSortedCol, m_bAscending );
	}

	// Set the sort image
	HWND hWnd = GetDlgItem(0)->GetSafeHwnd();
	ASSERT(NULL != hWnd);

	HDITEM hditem;

	// Remove the sort image from the previous column (if any)
	if (nPrevCol >= 0)
	{
		hditem.mask = HDI_FORMAT;
		VERIFY( Header_GetItem(hWnd, nPrevCol, &hditem) );

		hditem.fmt = hditem.fmt & ~HDF_SORTDOWN & ~HDF_SORTUP;

		Header_SetItem(hWnd, nPrevCol, &hditem);
	}

	// Now set the sort image on the new column
	hditem.mask = HDI_FORMAT;
	VERIFY( Header_GetItem(hWnd, m_nSortedCol, &hditem) );

	hditem.fmt = hditem.fmt & ~HDF_SORTDOWN & ~HDF_SORTUP;

	hditem.fmt |= m_bAscending ? HDF_SORTUP : HDF_SORTDOWN;

	Header_SetItem(hWnd, m_nSortedCol, &hditem);

	return nPrevCol;
}


bool CListViewEx::SubclassHeader(bool bBoldFont/*=false*/)
{
	// allocate memory for the flat header.
	m_pHeaderCtrl = new CHeaderCtrlEx;
	ASSERT( m_pHeaderCtrl );

	// get the window handle to the existing header
	// control.
	HWND hWnd = GetDlgItem(0)->GetSafeHwnd();
	ASSERT( hWnd );

	// subclass the flat header control.
	if( !m_pHeaderCtrl->SubclassWindow( hWnd ))
		return false;

	// finish header initialization.
	m_pHeaderCtrl->InitializeHeader( bBoldFont );
	
	return true;
}

void CListViewEx::AutoSaveColumns(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault)
{
	m_bAutoSave = true;

	// initialize registry strings.
	if( lpszSection == NULL ) m_strSection = _T("Settings");
	else m_strSection = lpszSection;

	if( lpszEntry == NULL ) m_strEntry = _T("Column Info");
	else m_strEntry = lpszEntry;

	if( lpszDefault == NULL ) m_strDefault = _T("");
	else m_strDefault = lpszDefault;

	LoadColumnWidths();
}

void CListViewEx::SaveColumnWidths()
{
	// get a pointer to the header control.
	CHeaderCtrl* pHeader = DYNAMIC_DOWNCAST(CHeaderCtrl, GetDlgItem(0));
	ASSERT_KINDOF( CHeaderCtrl, pHeader );

	CString strValue;
	for( int i = 0; i < pHeader->GetItemCount(); ++i )
	{
		CString strTemp;
		strTemp.Format(_T("%d,"), m_pListCtrl->GetColumnWidth( i ));
		strValue += strTemp;
	}

	AfxGetApp()->WriteProfileString( m_strSection, m_strEntry, strValue );
}

void CListViewEx::LoadColumnWidths()
{
	// get a pointer to the header control.
	CHeaderCtrl* pHeader = DYNAMIC_DOWNCAST(CHeaderCtrl, GetDlgItem(0));
	ASSERT_KINDOF( CHeaderCtrl, pHeader );

	for( int i = 0; i < pHeader->GetItemCount(); ++i )
		SetColumnWidth(i);
}

void CListViewEx::SetColumnWidth(int nCol)
{
	int nWidth = GetStoredWidth( nCol );
	if( nWidth > m_nMinColWidth )
		m_pListCtrl->SetColumnWidth( nCol, nWidth );
	else
		AutoSizeColumn( nCol );
}

int CListViewEx::GetStoredWidth(int nCol)
{
	// get the value from the registry.
	CString strValue = AfxGetApp()->GetProfileString(
		m_strSection, m_strEntry, m_strDefault );

	// extract the sub string to get the column width.
	CString strSubString;
	AfxExtractSubString( strSubString, strValue, nCol, _T(','));

	// return the width from the registry.
	return _ttoi( strSubString );
}

void CListViewEx::OnDestroy() 
{
	if( m_bAutoSave ) SaveColumnWidths();
	CListView::OnDestroy();
}

// Taken from: Autosize a column to fit its content by Roger Onslow.
// http://www.codeguru.com/listview/autosize_col.shtml
// If you don't supply a column number, it will resize all columns.
void CListViewEx::AutoSizeColumn(int nCol/*=-1*/)
{
	// Call this after your list control is filled
	SetRedraw( false );
	
	int nMinCol = nCol < 0 ? 0 : nCol;
	int nMaxCol = nCol < 0 ? GetColumnCount()-1 : nCol;
	
	for (nCol = nMaxCol; nCol >= nMinCol; nCol--)
	{
		m_pListCtrl->SetColumnWidth( nCol, LVSCW_AUTOSIZE );
		int wc1 = m_pListCtrl->GetColumnWidth( nCol );
		
		m_pListCtrl->SetColumnWidth( nCol, LVSCW_AUTOSIZE_USEHEADER );
		int wc2 = m_pListCtrl->GetColumnWidth( nCol );

		if ( (NULL != m_pHeaderCtrl) && (m_nSortedCol == nCol) )
		{
			wc2 += m_pHeaderCtrl->GetSortImageWidth();
		}

		int wc = max( m_nMinColWidth, max( wc1, wc2 ));
	
		if( wc > m_nMaxColWidth )
			wc = m_nMaxColWidth;
		
		// set the column width.
		m_pListCtrl->SetColumnWidth( nCol,wc );
	}
	
	SetRedraw();
}

BOOL CListViewEx::OnEraseBkgnd(CDC* pDC) 
{
	CRect rectClient;
	GetClientRect( &rectClient );
	pDC->ExcludeClipRect( &rectClient );
	return CListView::OnEraseBkgnd(pDC);
}

int CListViewEx::GetFirstVisibleColumn()
{
	int nColCount = m_pListCtrl->GetHeaderCtrl()->GetItemCount();
	for(int i = 0; i < nColCount; ++i)
	{
		int nCol = m_pListCtrl->GetHeaderCtrl()->OrderToIndex(i);
		if (IsColumnVisible(nCol))
		{
			return nCol;
		}
	}
	return -1;
}

BOOL CListViewEx::ShowColumn(int nCol, bool bShow)
{
	SetRedraw(FALSE);

	ColumnState& columnState = GetColumnState(nCol);

	int nColCount = m_pListCtrl->GetHeaderCtrl()->GetItemCount();
	int* pOrderArray = new int[nColCount];
	VERIFY( m_pListCtrl->GetColumnOrderArray(pOrderArray, nColCount) );
	if (bShow)
	{
		// Restore the position of the column
		int nCurIndex = -1;
		for(int i = 0; i < nColCount ; ++i)
		{
			if (pOrderArray[i]==nCol)
				nCurIndex = i;
			else
				if (nCurIndex!=-1)
				{
					// We want to move it to the original position,
					// and after the last hidden column
					if ( (i <= columnState.m_OrgPosition)
						|| !IsColumnVisible(pOrderArray[i])
						)
					{
						pOrderArray[nCurIndex] = pOrderArray[i];
						pOrderArray[i] = nCol;
						nCurIndex = i;
					}
				}
		}
	}
	else
	{
		// Move the column to the front of the display order list
		int nCurIndex(-1);
		for(int i = nColCount-1; i >=0 ; --i)
		{
			if (pOrderArray[i]==nCol)
			{
				// Backup the current position of the column
				columnState.m_OrgPosition = i;
				nCurIndex = i;
			}
			else
				if (nCurIndex!=-1)
				{
					pOrderArray[nCurIndex] = pOrderArray[i];
					pOrderArray[i] = nCol;
					nCurIndex = i;
				}
		}
	}

	VERIFY( m_pListCtrl->SetColumnOrderArray(nColCount, pOrderArray) );
	delete [] pOrderArray;

	if (bShow)
	{
		// Restore the column width
		columnState.m_Visible = true;
		VERIFY( m_pListCtrl->SetColumnWidth(nCol, columnState.m_OrgWidth) );
	}
	else
	{
		// Backup the column width
		int orgWidth = m_pListCtrl->GetColumnWidth(nCol);
		VERIFY( m_pListCtrl->SetColumnWidth(nCol, 0) );
		columnState.m_Visible = false;
		columnState.m_OrgWidth = orgWidth;
	}
	SetRedraw(TRUE);
	Invalidate(FALSE);
	return TRUE;
}

BOOL CListViewEx::SetColumnWidthAuto(int nCol, bool includeHeader)
{
	if (nCol == -1)
	{
		for(int i = 0; i < m_pListCtrl->GetHeaderCtrl()->GetItemCount() ; ++i)
		{
			SetColumnWidthAuto(i, includeHeader);
		}
		return TRUE;
	}
	else
	{
		if (includeHeader)
			return m_pListCtrl->SetColumnWidth(nCol, LVSCW_AUTOSIZE_USEHEADER);
		else
			return m_pListCtrl->SetColumnWidth(nCol, LVSCW_AUTOSIZE);
	}
}

CListViewEx::ColumnState& CListViewEx::GetColumnState(int nCol)
{
	VERIFY( nCol >=0 && nCol < m_ColumnStates.GetSize() );
	return m_ColumnStates[nCol];
}

bool CListViewEx::IsColumnVisible(int nCol)
{
	return GetColumnState(nCol).m_Visible;
}

int CListViewEx::GetColumnStateCount()
{
	return m_ColumnStates.GetSize();
}

void CListViewEx::InsertColumnState(int nCol, bool bVisible, int nOrgWidth)
{
	VERIFY( nCol >=0 && nCol <= m_ColumnStates.GetSize() );

	ColumnState columnState;
	columnState.m_OrgWidth = nOrgWidth;
	columnState.m_Visible = bVisible;

	if (nCol == m_ColumnStates.GetSize())
	{
		// Append column picker to the end of the array
		m_ColumnStates.Add(columnState);
	}
	else
	{
		// Insert column in the middle of the array
		CSimpleArray<ColumnState> newArray;
		for(int i=0 ; i < m_ColumnStates.GetSize(); ++i)
		{
			if (i == nCol)
				newArray.Add(columnState);
			newArray.Add(m_ColumnStates[i]);
		}
		m_ColumnStates = newArray;
	}
}

void CListViewEx::DeleteColumnState(int nCol)
{
	VERIFY( nCol >=0 && nCol < m_ColumnStates.GetSize() );
	m_ColumnStates.RemoveAt(nCol);
}

void CListViewEx::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if (point.x==-1 && point.y==-1)
	{
		// OBS! point is initialized to (-1,-1) if using SHIFT+F10 or VK_APPS
	}
	else
	{
		CPoint pt = point;
		ScreenToClient(&pt);

#ifndef _WIN32_WCE
		CRect headerRect;
		m_pListCtrl->GetHeaderCtrl()->GetClientRect(&headerRect);
		if (headerRect.PtInRect(pt))
#endif
		{
			// Show context-menu with the option to show hide columns
			CMenu menu;
			if (menu.CreatePopupMenu())
			{
				for( int i = 0 ; i < GetColumnStateCount(); i++)
				{
					UINT uFlags = MF_BYPOSITION | MF_STRING;

					// Put check-box on context-menu
					if (IsColumnVisible(i))
						uFlags |= MF_CHECKED;
					else
						uFlags |= MF_UNCHECKED;

					// Retrieve column-title
					LVCOLUMN lvc = {0};
					lvc.mask = LVCF_TEXT;
					TCHAR sColText[256];
					lvc.pszText = sColText;
					lvc.cchTextMax = sizeof(sColText)-1;
					VERIFY( m_pListCtrl->GetColumn(i, &lvc) );

					menu.InsertMenu(0, uFlags, i, lvc.pszText);
				}

				menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this, 0);
			}
		}
		ClientToScreen(&pt);
	}
}

// Handle context-menu event for showing / hiding columns
BOOL CListViewEx::OnCommand(WPARAM wParam, LPARAM lParam)
{
	if (HIWORD(wParam) == 0)
	{
		int nCol = LOWORD(wParam);
		ShowColumn(nCol, !IsColumnVisible(nCol));
	}
	return TRUE;
}

void CListViewEx::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(nChar)
	{
	case VK_ADD:	// CTRL + NumPlus (Auto size all columns)
		{
			if (GetKeyState(VK_CONTROL) < 0)
			{
				// Special handling to avoid showing "hidden" columns
				SetColumnWidthAuto(-1);
				return;
			}
		} break;
	}
	CListView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CListViewEx::OnHeaderBeginResize(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	// Check that column is allowed to be resized
	NMHEADER* pNMH = (NMHEADER*)pNMHDR;
	int nCol = (int)pNMH->iItem;
	if (!IsColumnVisible(nCol))
	{
		*pResult = TRUE;	// Block resize
		return TRUE;		// Block event
	}
	return FALSE;
}

LRESULT CListViewEx::OnSetColumnWidth(WPARAM wParam, LPARAM lParam)
{
	// Check that column is allowed to be resized
	int nCol = (int)wParam;
	if (!IsColumnVisible(nCol))
	{
		return FALSE;
	}
	// Let the CListCtrl handle the event
	return DefWindowProc(LVM_SETCOLUMNWIDTH, wParam, lParam);
}

BOOL CListViewEx::OnHeaderEndDrag(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	NMHEADER* pNMH = (NMHEADER*)pNMHDR;
	if (pNMH->pitem->mask & HDI_ORDER)
	{
		// Correct iOrder so it is just after the last hidden column
		int nColCount = m_pListCtrl->GetHeaderCtrl()->GetItemCount();
		int* pOrderArray = new int[nColCount];
		VERIFY( m_pListCtrl->GetColumnOrderArray(pOrderArray, nColCount) );

		for(int i = 0; i < nColCount ; ++i)
		{
			if (IsColumnVisible(pOrderArray[i]))
			{
				pNMH->pitem->iOrder = max(pNMH->pitem->iOrder,i);
				break;
			}
		}
		delete [] pOrderArray;
	}
	return FALSE;
}

BOOL CListViewEx::OnHeaderDividerDblClick(UINT, NMHDR* pNMHDR, LRESULT* pResult)
{
	NMHEADER* pNMH = (NMHEADER*)pNMHDR;
	SetColumnWidthAuto(pNMH->iItem);
	return TRUE;	// Don't let parent handle the event
}

LRESULT CListViewEx::OnDeleteColumn(WPARAM wParam, LPARAM lParam)
{
	// Let the CListCtrl handle the event
	LRESULT lRet = DefWindowProc(LVM_DELETECOLUMN, wParam, lParam);
	if (lRet == FALSE)
		return FALSE;

	// Book keeping of columns
	DeleteColumnState((int)wParam);
	return lRet;
}

LRESULT CListViewEx::OnInsertColumn(WPARAM wParam, LPARAM lParam)
{
	// Let the CListCtrl handle the event
	LRESULT lRet = DefWindowProc(LVM_INSERTCOLUMN, wParam, lParam);
	if (lRet == -1)
		return -1;

	int nCol = (int)lRet;

	// Book keeping of columns
	if (GetColumnStateCount() < m_pListCtrl->GetHeaderCtrl()->GetItemCount())
		InsertColumnState((int)nCol, true);	// Insert as visible

	return lRet;
}




/*
namespace 
{
	LRESULT EnableWindowTheme(HWND hwnd, LPCWSTR classList, LPCWSTR subApp, LPCWSTR idlist)
	{
		HMODULE hinstDll;
		HRESULT (__stdcall *pSetWindowTheme)(HWND hwnd, LPCWSTR pszSubAppName, LPCWSTR pszSubIdList);
		HANDLE (__stdcall *pOpenThemeData)(HWND hwnd, LPCWSTR pszClassList);
		HRESULT (__stdcall *pCloseThemeData)(HANDLE hTheme);

		hinstDll = ::LoadLibrary(TEXT("UxTheme.dll"));
		if (hinstDll)
		{
			(FARPROC&)pOpenThemeData = ::GetProcAddress(hinstDll, TEXT("OpenThemeData"));
			(FARPROC&)pCloseThemeData = ::GetProcAddress(hinstDll, TEXT("CloseThemeData"));
			(FARPROC&)pSetWindowTheme = ::GetProcAddress(hinstDll, TEXT("SetWindowTheme"));
			::FreeLibrary(hinstDll);
			if (pSetWindowTheme && pOpenThemeData && pCloseThemeData)
			{
				HANDLE theme = pOpenThemeData(hwnd,classList);
				if (theme!=NULL)
				{
					VERIFY(pCloseThemeData(theme)==S_OK);
					return pSetWindowTheme(hwnd, subApp, idlist);
				}
			}
		}
		return S_FALSE;
	}
}

void CListViewEx::PreSubclassWindow()
{
	CListViewEx::PreSubclassWindow();

	// Focus retangle is not painted properly without double-buffering
#if (_WIN32_WINNT >= 0x501)
	SetExtendedStyle(LVS_EX_DOUBLEBUFFER | GetExtendedStyle());
#endif
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_HEADERDRAGDROP);
	SetExtendedStyle(GetExtendedStyle() | LVS_EX_GRIDLINES);

	// Enable Vista-look if possible
	EnableWindowTheme(GetSafeHwnd(), L"ListView", L"Explorer", NULL);
}
*/
};