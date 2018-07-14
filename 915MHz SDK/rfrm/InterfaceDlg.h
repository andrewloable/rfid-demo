#pragma once


// CInterfaceDlg dialog

class CInterfaceDlg : public CDialog
{
	DECLARE_DYNAMIC(CInterfaceDlg)

public:
	CInterfaceDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInterfaceDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_INTERFACE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox	m_ctrlComboInterface;
	CEdit		m_ctrlEditPort;
	CEdit		m_ctrlEditAddress;
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboInterface();
	afx_msg void OnBnClickedOk();
};
