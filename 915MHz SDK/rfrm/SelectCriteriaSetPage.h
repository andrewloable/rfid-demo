#pragma once


// CSelectCriteriaSetPage dialog

class CSelectCriteriaSetPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSelectCriteriaSetPage)

public:
	CSelectCriteriaSetPage(const wchar_t* lpszTitle, HICON hIcon = NULL);
	virtual ~CSelectCriteriaSetPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_SELECT_CRITERIA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
