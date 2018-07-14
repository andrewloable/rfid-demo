// CeListCtrlEx.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "CeListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace techwin
{
	/////////////////////////////////////////////////////////////////////////////
	// CCeListCtrlEx

	CCeListCtrlEx::CCeListCtrlEx()
	{
	}

	CCeListCtrlEx::~CCeListCtrlEx()
	{
	}

	BEGIN_MESSAGE_MAP(CCeListCtrlEx, CListCtrl)
		//{{AFX_MSG_MAP(CCeListCtrlEx)
		ON_WM_SETFOCUS()
		ON_WM_KILLFOCUS()
		ON_WM_LBUTTONDOWN()
		ON_NOTIFY_REFLECT(NM_RECOGNIZEGESTURE, OnRecognizeGesture)
		ON_WM_CREATE()
		//}}AFX_MSG_MAP
	END_MESSAGE_MAP()

	/////////////////////////////////////////////////////////////////////////////
	// CCeListCtrlEx message handlers

	void CCeListCtrlEx::Init()
	{
		// Change the style of the control
		VERIFY(ModifyStyle(LVS_TYPEMASK       | // this styles are removed
			LVS_SHOWSELALWAYS  |
			LVS_EDITLABELS,
			LVS_REPORT         | // this styles are added
			LVS_OWNERDRAWFIXED |
			LVS_NOCOLUMNHEADER |
			LVS_SINGLESEL));

		// Insert at least one column to the list control
		VERIFY(InsertColumn(0, _T("Column"), LVCFMT_LEFT) == 0);
		SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
	}

	int CCeListCtrlEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
	{
		if (CListCtrl::OnCreate(lpCreateStruct) == -1)
			return -1;

		// TODO: Add your specialized creation code here

		Init();

		return 0;
	}

	void CCeListCtrlEx::PreSubclassWindow()
	{
		// TODO: Add your specialized code here and/or call the base class

		Init();

		CListCtrl::PreSubclassWindow();
	}

	int CCeListCtrlEx::GetCurSelItem() const
	{
		ASSERT(::IsWindow(m_hWnd));

		// Return the index of the item with the focus
		return GetNextItem(-1, LVNI_FOCUSED);
	}

	BOOL CCeListCtrlEx::SetCurSelItem(int nIndex)
	{
		ASSERT(::IsWindow(m_hWnd));

		// Set the focus to the item with the specified index
		return SetItemState(nIndex, LVIS_FOCUSED, LVIS_FOCUSED);
	}

	BOOL CCeListCtrlEx::MoveItem(int nOldIndex, int nNewIndex)
	{
		// Check pre-conditions
		ASSERT(::IsWindow(m_hWnd));
		ASSERT(nOldIndex >= 0 && nOldIndex < GetItemCount());
		ASSERT(nNewIndex >= 0 && nNewIndex < GetItemCount());

		if (nOldIndex < 0 || nOldIndex >= GetItemCount())
			return FALSE;

		if (nNewIndex < 0 || nNewIndex >= GetItemCount())
			return FALSE;

		// Get the properties of the current selected item
		CString strText = GetItemText(nOldIndex, 0);

		LVITEM lvItem;
		memset(&lvItem, 0, sizeof(LVITEM));
		lvItem.mask     = LVIF_IMAGE;
		lvItem.iItem    = nOldIndex;
		lvItem.iSubItem = 0;
		VERIFY(GetItem(&lvItem));

		// Delete the current selected item
		VERIFY(DeleteItem(nOldIndex));

		// Insert the item on the new position
		VERIFY(InsertItem(nNewIndex, strText, lvItem.iImage) == nNewIndex);

		// Select the new item
		VERIFY(SetCurSelItem(nNewIndex));

		return TRUE;
	}

	BOOL CCeListCtrlEx::MoveItemUp(int nIndex)
	{
		// Check pre-conditions
		ASSERT(::IsWindow(m_hWnd));
		// ASSERT(nIndex >= 1 && nIndex < GetItemCount());

		if (nIndex >= 1 && nIndex < GetItemCount())
		{
			// Move the item one position up
			return MoveItem(nIndex, nIndex - 1);
		}

		return FALSE;
	}

	BOOL CCeListCtrlEx::MoveItemDown(int nIndex)
	{
		// Check pre-conditions
		ASSERT(::IsWindow(m_hWnd));
		// ASSERT(nIndex >= 0 && nIndex < GetItemCount() - 1);

		if (nIndex >= 0 && nIndex < GetItemCount() - 1)
		{
			// Move the item one position down
			return MoveItem(nIndex, nIndex + 1);
		}

		return FALSE;
	}

	BOOL CCeListCtrlEx::MoveItemTop(int nIndex)
	{
		// Check pre-conditions
		ASSERT(::IsWindow(m_hWnd));
		// ASSERT(nIndex >= 0 && nIndex < GetItemCount());

		if (nIndex >= 0 && nIndex < GetItemCount())
		{
			// Move the item to the first position
			return MoveItem(nIndex, 0);
		}

		return FALSE;
	}

	BOOL CCeListCtrlEx::MoveItemBottom(int nIndex)
	{
		// Check pre-conditions
		ASSERT(::IsWindow(m_hWnd));
		// ASSERT(nIndex >= 0 && nIndex < GetItemCount());

		if (nIndex >= 0 && nIndex < GetItemCount())
		{
			// Move the item to the last position
			return MoveItem(nIndex, GetItemCount() - 1);
		}

		return FALSE;
	}

	int CCeListCtrlEx::DrawTextEndEllipsis(CDC* pDC, const CString& strText, CRect& rc, UINT uFormat)
	{
		// Check pre-conditions
		ASSERT(::IsWindow(m_hWnd));
		ASSERT(pDC != 0);

		// This function emulates the desktop version of DrawText with DT_END_ELLIPSIS flag set.
		// The original "DrawTextEndEllipsis" function was written by Alexander Shargin and
		// can be found at http://www.pocketpcdn.com/qa/ellipsis_flag.html.

		int nWidth = rc.Width();

		if (pDC->GetTextExtent(strText).cx > nWidth)
		{
			// Text doesn't fit in rect, we have to
			// truncate it and add ellipsis to the end.

			CString strTemp = strText;

			for (int n = strText.GetLength(); n >= 0; n--)
			{
				strTemp = strText.Left(n) + _T("...");

				if (pDC->GetTextExtent(strTemp).cx < nWidth)
				{
					break;
				}
			}

			// Draw the text with the ellipsis at the end
			return pDC->DrawText(strTemp, rc, uFormat);
		}

		// Draw the text without the ellipsis at the end
		return pDC->DrawText(strText, rc, uFormat);
	}

	void CCeListCtrlEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
	{
		// Check pre-conditions
		ASSERT(::IsWindow(m_hWnd));
		ASSERT(lpDrawItemStruct != 0);

		// Some parts of this function are based on the "Selection Highlighting of an Entire Row"
		// article, written by Uwe Keim (http://www.magerquark.de). You can found this article
		// at http://www.codeproject.com/useritems/selectentirerow.asp.

		CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
		CRect rcItem(lpDrawItemStruct->rcItem);
		int nItem = lpDrawItemStruct->itemID;
		CImageList* pImageList;

		// Save dc state
		int nSavedDC = pDC->SaveDC();

		// Get item image and state info
		LV_ITEM lvi;
		lvi.mask = LVIF_IMAGE | LVIF_STATE;
		lvi.iItem = nItem;
		lvi.iSubItem = 0;
		lvi.stateMask = 0xFFFF;     // get all state flags
		GetItem(&lvi);

		// Should the item be highlighted
		BOOL bHighlight = /*((lvi.state & LVIS_DROPHILITED)
						  || ( (lvi.state & LVIS_SELECTED)
						  && ((GetFocus() == this)
						  || (GetStyle() & LVS_SHOWSELALWAYS)
						  )
						  )
						  )*/ lvi.state & LVIS_FOCUSED;

		// Get rectangles for drawing
		CRect rcBounds, rcLabel, rcIcon;
		GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
		GetItemRect(nItem, rcLabel, LVIR_LABEL);
		GetItemRect(nItem, rcIcon, LVIR_ICON);
		CRect rcCol(rcBounds);

		CString sLabel = GetItemText(nItem, 0);

		// Labels are offset by a certain amount
		// This offset is related to the width of a space character
		int offset = pDC->GetTextExtent(_T(" "), 1).cx * 2;

		CRect rcHighlight;
		/*CRect rcWnd;
		int nExt;
		switch( m_nHighlight )
		{
		case 0:
		nExt = pDC->GetOutputTextExtent(sLabel).cx + offset;
		rcHighlight = rcLabel;
		if( rcLabel.left + nExt < rcLabel.right )
		rcHighlight.right = rcLabel.left + nExt;
		break;
		case 1:
		rcHighlight = rcBounds;
		rcHighlight.left = rcLabel.left;
		break;
		case 2:
		GetClientRect(&rcWnd);*/
		rcHighlight = rcBounds;
		rcHighlight.left = rcLabel.left;
		/*rcHighlight.right = rcWnd.right;
		break;
		default:
		rcHighlight = rcLabel;
		}*/

		// Draw the background color
		if (bHighlight)
		{
			pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
			pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));

			pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
		}
		else
			pDC->FillRect(rcHighlight, &CBrush(::GetSysColor(COLOR_WINDOW)));

		// Set clip region
		rcCol.right = rcCol.left + GetColumnWidth(0);
		CRgn rgn;
		rgn.CreateRectRgnIndirect(&rcCol);
		pDC->SelectClipRgn(&rgn);
		rgn.DeleteObject();

		// Draw state icon
		if (lvi.state & LVIS_STATEIMAGEMASK)
		{
			int nImage = ((lvi.state & LVIS_STATEIMAGEMASK) >> 12) - 1;
			pImageList = GetImageList(LVSIL_STATE);
			if (pImageList)
			{
				pImageList->Draw(pDC, nImage,
					CPoint(rcCol.left, rcCol.top), ILD_TRANSPARENT);
			}
		}

		// Draw normal and overlay icon
		pImageList = GetImageList(LVSIL_SMALL);
		if (pImageList)
		{
			UINT nOvlImageMask = lvi.state & LVIS_OVERLAYMASK;
			pImageList->Draw(pDC, lvi.iImage,
				CPoint(rcIcon.left, rcIcon.top),
				(bHighlight ? ILD_BLEND50 : 0) | ILD_TRANSPARENT | nOvlImageMask);
		}

		// Draw item label - Column 0
		rcLabel.left += offset / 2;
		rcLabel.right -= offset;

		/*pDC->DrawText(sLabel,-1,rcLabel,DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP
		| DT_VCENTER | DT_END_ELLIPSIS);*/

		DrawTextEndEllipsis(pDC, sLabel, rcLabel, DT_LEFT | DT_SINGLELINE |
			DT_NOPREFIX | DT_NOCLIP | DT_VCENTER /*| DT_END_ELLIPSIS*/);

		// Draw labels for remaining columns
		LV_COLUMN lvc;
		lvc.mask = LVCF_FMT | LVCF_WIDTH;

		/*if( m_nHighlight == 0 )     // Highlight only first column
		{
		pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
		pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
		}*/

		rcBounds.right = rcHighlight.right > rcBounds.right ? rcHighlight.right : rcBounds.right;
		rgn.CreateRectRgnIndirect(&rcBounds);
		pDC->SelectClipRgn(&rgn);

		for (int nColumn = 1; GetColumn(nColumn, &lvc); nColumn++)
		{
			rcCol.left = rcCol.right;
			rcCol.right += lvc.cx;

			// Draw the background if needed
			/*if( m_nHighlight == HIGHLIGHT_NORMAL )
			pDC->FillRect(rcCol, &CBrush(::GetSysColor(COLOR_WINDOW)));*/

			sLabel = GetItemText(nItem, nColumn);
			if (sLabel.GetLength() == 0)
				continue;

			// Get the text justification
			UINT nJustify = DT_LEFT;
			switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
			{
			case LVCFMT_RIGHT:
				nJustify = DT_RIGHT;
				break;
			case LVCFMT_CENTER:
				nJustify = DT_CENTER;
				break;
			default:
				break;
			}

			rcLabel = rcCol;
			rcLabel.left += offset;
			rcLabel.right -= offset;

			/*pDC->DrawText(sLabel, -1, rcLabel, nJustify | DT_SINGLELINE |
			DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);*/

			DrawTextEndEllipsis(pDC, sLabel, rcLabel, nJustify | DT_SINGLELINE |
				DT_NOPREFIX | DT_VCENTER /*| DT_END_ELLIPSIS*/);
		}

		// Draw focus rectangle if item has focus
		if (lvi.state & LVIS_FOCUSED && (GetFocus() == this))
			pDC->DrawFocusRect(rcHighlight);

		// Restore dc
		pDC->RestoreDC(nSavedDC);
	}

	void CCeListCtrlEx::RepaintSelectedItems()
	{
		CRect rcBounds, rcLabel;

		// Invalidate focused item so it can repaint
		int nItem = GetNextItem(-1, LVNI_FOCUSED);

		if(nItem != -1)
		{
			GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
			GetItemRect(nItem, rcLabel, LVIR_LABEL);
			rcBounds.left = rcLabel.left;

			InvalidateRect(rcBounds, FALSE);
		}

		// Invalidate selected items depending on LVS_SHOWSELALWAYS
		if(!(GetStyle() & LVS_SHOWSELALWAYS))
		{
			for(nItem = GetNextItem(-1, LVNI_SELECTED);
				nItem != -1; nItem = GetNextItem(nItem, LVNI_SELECTED))
			{
				GetItemRect(nItem, rcBounds, LVIR_BOUNDS);
				GetItemRect(nItem, rcLabel, LVIR_LABEL);
				rcBounds.left = rcLabel.left;

				InvalidateRect(rcBounds, FALSE);
			}
		}
#ifdef _DEBUG
		else
			ASSERT(FALSE);
#endif

		UpdateWindow();
	}

	void CCeListCtrlEx::OnSetFocus(CWnd* pOldWnd)
	{
		CListCtrl::OnSetFocus(pOldWnd);

		// TODO: Add your message handler code here

		// check if we are getting focus from label edit box
		if (pOldWnd != NULL && pOldWnd->GetParent() == this)
			return;

		// repaint items that should change appearance
		if ((GetStyle() & LVS_TYPEMASK) == LVS_REPORT)
			RepaintSelectedItems();
#ifdef _DEBUG
		else
			ASSERT(FALSE);
#endif
	}

	void CCeListCtrlEx::OnKillFocus(CWnd* pNewWnd)
	{
		CListCtrl::OnKillFocus(pNewWnd);

		// TODO: Add your message handler code here

		// check if we are losing focus to label edit box
		if (pNewWnd != NULL && pNewWnd->GetParent() == this)
			return;

		// repaint items that should change appearance
		if ((GetStyle() & LVS_TYPEMASK) == LVS_REPORT)
			RepaintSelectedItems();
#ifdef _DEBUG
		else
			ASSERT(FALSE);
#endif
	}

	void CCeListCtrlEx::OnLButtonDown(UINT nFlags, CPoint point)
	{
		Default(); // call default message handler
	}

	void CCeListCtrlEx::OnRecognizeGesture(NMHDR* pNMHDR, LRESULT* pResult)
	{
		*pResult = TRUE; // cancel the red dot animation
	}

	BOOL CCeListCtrlEx::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: Add your specialized code here and/or call the base class

		return CListCtrl::PreCreateWindow(cs);
	}
};