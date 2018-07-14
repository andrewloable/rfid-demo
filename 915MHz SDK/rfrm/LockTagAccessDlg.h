#pragma once


// CLockTagAccessDlg dialog

class CLockTagAccessDlg : public CDialog
{
	DECLARE_DYNAMIC(CLockTagAccessDlg)

public:
	CLockTagAccessDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CLockTagAccessDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_TAG_ACCESS_LOCK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CTagInfo*						m_tagInfo;
	RFID_18K6C_TAG_PERM				m_lockPermission;
	CEdit							m_editEPC;
	CEdit							m_editAccessPassword;
	CComboBox						m_comboKillPasswordPermission;
	CComboBox						m_comboAccessPasswordPermission;
	CComboBox						m_comboEPCBankPermission;
	CComboBox						m_comboTIDBankPermission;
	CComboBox						m_comboUserBankPermission;

public:
	void SetSelectedTag(CTagInfo* pTag);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString							m_strEPC;
};
