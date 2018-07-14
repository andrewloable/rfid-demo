// HighColorPropertySheet.h : header file
//
///////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HIGHCOLORPROPERTYSHEET_H__2A258268_3ED7_40AD_886D_19B9B1A24B3A__INCLUDED_)
#define AFX_HIGHCOLORPROPERTYSHEET_H__2A258268_3ED7_40AD_886D_19B9B1A24B3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace techwin
{
	/////////////////////////////////////////////////////////////////////////////
	// CPropertySheetEx

	class CPropertySheetEx : public CPropertySheet
	{
		DECLARE_DYNAMIC(CPropertySheetEx)

		// Construction
	public:
		CPropertySheetEx(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
		CPropertySheetEx(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

		// Attributes
	public:

		// Operations
	public:

		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CPropertySheetEx)
	public:
		virtual BOOL OnInitDialog();
		//}}AFX_VIRTUAL

		// Implementation
	public:
		virtual ~CPropertySheetEx();

		// Generated message map functions
	protected:
		//{{AFX_MSG(CPropertySheetEx)
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};

	/////////////////////////////////////////////////////////////////////////////

	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
};
#endif // !defined(AFX_HIGHCOLORPROPERTYSHEET_H__2A258268_3ED7_40AD_886D_19B9B1A24B3A__INCLUDED_)
