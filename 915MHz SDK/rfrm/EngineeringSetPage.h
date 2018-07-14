#pragma once


// CEngineeringSetPage dialog

class CEngineeringSetPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CEngineeringSetPage)

public:
	CEngineeringSetPage(const wchar_t* lpszTitle, HICON hIcon = NULL);
	virtual ~CEngineeringSetPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_ENGINEERING };

protected:
	INT32U	m_nSelectedSession;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CButton m_ctrlButtonEPCDisplay;
	CButton m_ctrlButtonASCIIDisplay;

	int		m_nDisplayMode;

	DECLARE_MESSAGE_MAP()
public:
	CButton		m_ctrlCheckCarrier;
	CButton		m_ctrlCheckLeakMode;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditTransferTime();
	afx_msg void OnEnChangeEditMaxTrialCount();
	afx_msg void OnBnClickedCheckCarrierOnOff();
	afx_msg void OnBnClickedCheckLeakCont();
	afx_msg void OnBnClickedCheckSession0();
	afx_msg void OnBnClickedCheckSession1();
	afx_msg void OnBnClickedCheckSession2();
	afx_msg void OnBnClickedCheckSession3();
	afx_msg void OnBnClickedButtonBeepFilePath();
	afx_msg void OnBnClickedRadioEpcDisplay();
	afx_msg void OnBnClickedRadioAsciiDisplay();
};
