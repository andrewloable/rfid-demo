// CJFlatHeaderCtrl.h : header file
// Copyright ?1998-1999 CodeJock.com, All Rights Reserved.
// See ReadMe.txt for TERMS OF USE.
//
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

#ifndef __CJFLATHEADERCTRL_H__
#define __CJFLATHEADERCTRL_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MenuEx.h"        // CCJMenu class declaration

namespace techwin
{
// CHeaderCtrlEx is a CHeaderCtrl derived class which is simular
// to the listbox flat header controls seen in Visual Studio and Outlook.
class CHeaderCtrlEx : public CHeaderCtrl
{

public:
	
	// Default constructor
	//
	CHeaderCtrlEx();

	// Virtual destructor
	//
	virtual ~CHeaderCtrlEx();

protected:
	UINT	m_popToolbarID;	// popup menu toolbar resource id, associates 
							// toolbar icons with the popup menu.
	
	UINT	m_popupMenuID;	// popup menu resource id
#ifndef _WIN32_WCE
	CMenuEx	m_popupMenu;	// popup menu
#endif
	int		m_nPos;			// index of the pop-up menu contained in the menu
	BOOL	m_bBoldFont;	// true for bold fonts see SetFontBold(...)
	BOOL	m_bLBtnDown;	// true if left mouse button is pressed
	BOOL	m_bSortAsc;		// used when column is pressed to draw sort arrow.
	CFont	m_Font;			// font the header will use
	int		m_nOffset;		// ammount to offset the sort arrow.
	int		m_nSortCol;		// last column pressed during sort.
	CWnd*	m_pParentWnd;	// holds a pointer to the parent window.
	CRect   m_rcOldSize;

public:

	// this member function is called to associate a menu and toolbar
	// resource with the context menu.
	//
	virtual void SetMenuID(UINT popupMenuID, UINT popToolbarID=0, int nPos=0);

	// this member function returns the menu resource associated with
	// the tab control.
	//
	virtual UINT GetMenuID();

	// this member function must be called after creation to initialize the
	// font the header will use.
	//
	virtual void InitializeHeader(bool bBoldFont);

	// this member function can be used to toggle the font from bold to
	// normal.
	//
	virtual void SetFontBold(BOOL bBoldFont = TRUE);
	
	// this member function is called by the header during sort
	// operations
	//
	virtual int SetSortImage( int nCol, BOOL bAsc );

	virtual int GetSortImageWidth(void) const
					{ return 3 * m_nOffset; }

protected:

	// this member function is called by the header during paint
	// operations.
	//
	virtual void DrawFlatBorder(CDC* pDC);
// Changes in code by Paulo Breda Vieira 1999-11-19
//	virtual void ResizeWindow();

#ifdef _VC_VERSION_5
	// this member function was added for vc5 support. It returns the number
	// of columns currently in the header.
	//
	virtual int CHeaderCtrlEx::GetItemCount() const;
	virtual BOOL GetOrderArray(LPINT piArray, int iCount= -1);
#endif

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHeaderCtrlEx)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CHeaderCtrlEx)
	afx_msg void OnPaint();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

// Changes in code by Paulo Breda Vieira 1999-11-19
//	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//	Inline Functions
/////////////////////////////////////////////////////////////////////////////

inline void CHeaderCtrlEx::SetMenuID(UINT popupMenuID, UINT popToolbarID, int nPos)
	{ ASSERT(::IsWindow(m_hWnd)); m_popupMenuID=popupMenuID; m_popToolbarID=popToolbarID; m_nPos=nPos; }

inline UINT CHeaderCtrlEx::GetMenuID()
	{ ASSERT(::IsWindow(m_hWnd)); return m_popupMenuID; }

inline void CHeaderCtrlEx::SetFontBold(BOOL bBoldFont)
	{ ASSERT(::IsWindow(m_hWnd)); m_bBoldFont = bBoldFont; }

#ifdef _VC_VERSION_5
inline int CHeaderCtrlEx::GetItemCount() const
	{ ASSERT(::IsWindow(m_hWnd)); return (int) ::SendMessage(m_hWnd, HDM_GETITEMCOUNT, 0, 0L); }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
};
#endif // __CJFLATHEADERCTRL_H__
