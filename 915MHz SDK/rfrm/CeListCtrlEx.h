// CeListCtrlEx.h : header file
//
#if !defined(AFX_CELISTCTRLEX_H__3BCE6295_516B_4715_A125_E1A03E26DF40__INCLUDED_)
#define AFX_CELISTCTRLEX_H__3BCE6295_516B_4715_A125_E1A03E26DF40__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

namespace techwin
{
	/////////////////////////////////////////////////////////////////////////////
	// CCeListCtrlEx window

	class CCeListCtrlEx : public CListCtrl
	{
		// Construction
	public:
		CCeListCtrlEx();

		// Attributes
	public:

		// Operations
	public:
		int  GetCurSelItem() const;
		BOOL SetCurSelItem(int nIndex);
		BOOL MoveItem(int nOldIndex, int nNewIndex);
		BOOL MoveItemUp(int nIndex);
		BOOL MoveItemDown(int nIndex);
		BOOL MoveItemTop(int nIndex);
		BOOL MoveItemBottom(int nIndex);

	protected:
		int DrawTextEndEllipsis(CDC* pDC, const CString& strText, CRect& rc, UINT uFormat);
		void RepaintSelectedItems();

		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CCeListCtrlEx)
	protected:
		virtual void PreSubclassWindow();
		//}}AFX_VIRTUAL
		virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

		// Implementation
	public:
		virtual ~CCeListCtrlEx();

		// Generated message map functions
	protected:
		//{{AFX_MSG(CCeListCtrlEx)
		afx_msg void OnSetFocus(CWnd* pOldWnd);
		afx_msg void OnKillFocus(CWnd* pNewWnd);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnRecognizeGesture(NMHDR* pNMHDR, LRESULT* pResult);
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()

	private:
		void Init();
	protected:
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	};

	/////////////////////////////////////////////////////////////////////////////

	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
};
#endif // !defined(AFX_CELISTCTRLEX_H__3BCE6295_516B_4715_A125_E1A03E26DF40__INCLUDED_)
