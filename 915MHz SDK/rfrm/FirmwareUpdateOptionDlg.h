#pragma once


// CFirmwareUpdateOptionDlg dialog

class CFirmwareUpdateOptionDlg : public CDialog
{
	DECLARE_DYNAMIC(CFirmwareUpdateOptionDlg)

public:
	CFirmwareUpdateOptionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFirmwareUpdateOptionDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_FIRMWARE_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void LoadState();
	void SaveState(int mode);
	inline int GetFirmwareUpdateMode();
protected:
	virtual void OnOK();

	int mode;
	CButton	m_ctrlRadioUpdateAll;
public:
	afx_msg void OnBnClickedRadioUpdateAll();
	afx_msg void OnBnClickedRadioTestModeOnly();
	afx_msg void OnBnClickedRadioSkipTestMode();
};

inline int CFirmwareUpdateOptionDlg::GetFirmwareUpdateMode()
{
	return mode;
}