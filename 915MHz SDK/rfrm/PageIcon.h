// PageIcon.h : header file
//
///////////////////////////////////////////////////////////////////////////////

#ifndef WBL_PAGEICON_H__INCLUDED_
#define WBL_PAGEICON_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace techwin
{
	/////////////////////////////////////////////////////////////////////////////
	// CPageIcon dialog

	class CPageIcon
		: public CPropertyPage
	{
		DECLARE_DYNAMIC(CPageIcon)

		// Construction
	public:
		CPageIcon(const char* lpszTitle, UINT nIconID);
		~CPageIcon();

		// Dialog Data
		//{{AFX_DATA(CPageIcon)
		enum { IDD };
		CStatic	m_staticIcon;
		//}}AFX_DATA


		// Overrides
		// ClassWizard generate virtual function overrides
		//{{AFX_VIRTUAL(CPageIcon)
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
		//}}AFX_VIRTUAL

		// Implementation
	protected:
		// Generated message map functions
		//{{AFX_MSG(CPageIcon)
//		virtual BOOL OnInitDialog();
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()

		// Members
	private:
		UINT m_nIconID;
		HICON m_hIcon;
	};

	//{{AFX_INSERT_LOCATION}}
	// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
};
#endif // WBL_PAGEICON_H__INCLUDED_
