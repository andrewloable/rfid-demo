#include "stdafx.h"
#include "ToolBarEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace techwin
{
/////////////////////////////////////////////////////////////////////////////
// CToolBarWithCombo

BEGIN_MESSAGE_MAP(CSTWToolBar, CToolBar)
	//{{AFX_MSG_MAP(CSTWToolBar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSTWToolBar::CreateComboBox(CComboBox& comboBox, UINT nIndex, UINT nID, 
								int nWidth, int nDropHeight)
{
	// Create the combo box
	SetButtonInfo(nIndex, nID, TBBS_SEPARATOR, nWidth);

	CRect rect;
	GetItemRect(nIndex, &rect);
	rect.top = 1;
	rect.left += 5;
	rect.right = rect.left + nWidth;
	rect.bottom = rect.top + nDropHeight;
	if (!comboBox.Create( CBS_DROPDOWN | WS_VISIBLE | WS_TABSTOP | WS_VSCROLL,
			rect, this, nID))
	{
		TRACE(_T("Failed to create combo-box\n"));
		return FALSE;
	}

	return TRUE;
}

BOOL CSTWToolBar::CreateEdit(CEdit& edit, UINT nIndex, UINT nID, 
								 int nWidth)
{
//	UINT style = GetButtonStyle(nIndex);
//	SetButtonStyle(nIndex, style);
	// Create the combo box
	SetButtonInfo(nIndex, nID, TBBS_SEPARATOR, nWidth);

	CRect rect;
	GetItemRect(nIndex, &rect);
	rect.top = 1;
	rect.bottom = nWidth;
	if (!edit.Create( ES_RIGHT | WS_VISIBLE | WS_TABSTOP,
		rect, this, nID))
	{
		TRACE(_T("Failed to create edit-box\n"));
		return FALSE;
	}

	return TRUE;
}

BOOL CSTWToolBar::CreateCheckButton(CButton& button, UINT nIndex, UINT nID, 
							 int nWidth)
{
	//	UINT style = GetButtonStyle(nIndex);
	//	SetButtonStyle(nIndex, style);
	// Create the combo box
	SetButtonInfo(nIndex, nID, TBBS_SEPARATOR, nWidth);

	CRect rect, safe_rect;
	GetItemRect(nIndex, &rect);
	rect.left +=10; 
	rect.top = 2;
//	rect.bottom=rect.top + 10;
	if (!button.Create(NULL, BS_CHECKBOX | WS_VISIBLE | WS_TABSTOP,
		rect, this, nID))
	{
		TRACE(_T("Failed to create edit-box\n"));
		return FALSE;
	}

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
};