#pragma once

#include "FrequencyBandList.h"
#include "ListCtrlEx.h"
// CFrequencyBandPage dialog

class CFrequencyBandPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CFrequencyBandPage)

public:
	CFrequencyBandPage(const wchar_t* lpszTitle, HICON hIcon = NULL);
	virtual ~CFrequencyBandPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_FREQUENCY_BAND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CFrequencyBandList	m_FrequencyBandList;
	CListCtrlEx			m_FrequencyListCtrl;

	int					m_nSortedCol;		// index of currently selected column

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnHdnItemclickListFrequencyBand(NMHDR *pNMHDR, LRESULT *pResult);
	bool SortList(int nColumn, bool bAscending);
};
