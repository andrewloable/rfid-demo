#pragma once


// CServerIPDlg dialog

class CServerIPDlg : public CDialog
{
	DECLARE_DYNAMIC(CServerIPDlg)

public:
	CServerIPDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CServerIPDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_SERVER_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


	DECLARE_MESSAGE_MAP()
public:
	CString m_strIPAddress;
	afx_msg void OnBnClickedOk();

};
