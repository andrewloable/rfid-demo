#pragma once

//#include "IconPropertyPage.h"
// CAntennaSetPage dialog

#include "ListCtrlEx.h"

#define ANTENNA_PORT_NUMBER	0
#define ANTENNA_PORT_STATUS	1
#define ANTENNA_SENS_VALUE	2



class CAntennaSetPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CAntennaSetPage)

public:
	CAntennaSetPage(const wchar_t* lpszTitle, HICON hIcon = NULL);
	virtual ~CAntennaSetPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_ANTENNA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrlEx m_ctrlAntennaList;
	CImageList m_smallImageList;
	int			m_iselectItem;

	// -- InsertItem --
	BOOL InsertAntennaItem(int nItem, int nSubItem, LPCWSTR strItem, int mask =LVIF_TEXT | LVIF_STATE, int iImage = 0);
	// -- InsertColumn
	//
	BOOL InsertAntennaColumn(int nItem, LPCWSTR strItem, int width, int nFmt = LVCFMT_CENTER, int nSubItem = -1, 
		int nMask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_SUBITEM);


//	afx_msg void OnNMClickListAntenna(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnBnClickedButtonEditAntenna();
	afx_msg void OnNMDblclkListAntenna(NMHDR *pNMHDR, LRESULT *pResult);
};
