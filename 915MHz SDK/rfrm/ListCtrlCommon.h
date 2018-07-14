#pragma once

namespace techwin
{
	class CListCtrlCommon : public CListCtrl
	{
		// Construction
	public:
		CListCtrlCommon();
		LV_COLUMN lvc;
		LV_ITEM lvit;
		CRect rcClient;
		CString str[100];
		int m_count;
		int colnum;
		BOOL m_Flag;
		int		m_nSortedCol;				// Sorting the list when user clicks on column header
		BOOL	m_bSortAscending;			//   "

		int		m_TotalFlag; /* Kimys Insert */


		// Attributes
	public:
		BOOL AddItem(int nItem, int nSubItem, LPCWSTR strItem, int mask =LVIF_TEXT | LVIF_STATE);
		BOOL AddColumn(int nItem, LPCWSTR strItem, int width, int nFmt = LVCFMT_CENTER, int nSubItem = -1, 
			int nMask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_SUBITEM);
		//	BOOL ModifyColumn(int nItem, LPCSTR strItem, int width, int nFmt = LVCFMT_CENTER, int nSubItem = -1, 
		//		int nMask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_SUBITEM);
		//	void AutoSize();

		// Operations
	public:

		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CListCtrlCommon)
		//}}AFX_VIRTUAL

		// Implementation
	public:
		virtual ~CListCtrlCommon();

		// Generated message map functions
	protected:
		//{{AFX_MSG(CListCtrlCommon)
		// NOTE - the ClassWizard will add and remove member functions here.
		afx_msg void OnHeaderClicked(NMHDR* pNMHDR, LRESULT* pResult);

		//}}AFX_MSG

	public:
		//	BOOL	SortTextItems(int nCol, BOOL bAscending, int low = 0, int high = -1);
		//	BOOL	SortNumericItems(int nCol, BOOL bAscending, int low = 0, int high = -1);

		//	DECLARE_MESSAGE_MAP()
	};
};