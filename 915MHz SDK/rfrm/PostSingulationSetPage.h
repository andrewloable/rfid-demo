#pragma once


// CPostSingulationSetPage dialog

class CPostSingulationSetPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CPostSingulationSetPage)

public:
	CPostSingulationSetPage(const wchar_t* lpszTitle, HICON hIcon = NULL);
	virtual ~CPostSingulationSetPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_POST_SINGULATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
