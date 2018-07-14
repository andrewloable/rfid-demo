#pragma once


// CKillTagAccessDlg dialog

class CKillTagAccessDlg : public CDialog
{
	DECLARE_DYNAMIC(CKillTagAccessDlg)

public:
	CKillTagAccessDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CKillTagAccessDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_TAG_ACCESS_KILL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CTagInfo*	m_tagInfo;
	CEdit							m_editEPC;
	CEdit							m_editAccessPassword;
	CEdit							m_editKillPassword;

public:
	void SetSelectedTag(CTagInfo* pTag);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString							m_strEPC;
};
