#pragma once
//#include "afxwin.h"


// CReadTagAccessDlg dialog

class CReadTagAccessDlg : public CDialog
{
	DECLARE_DYNAMIC(CReadTagAccessDlg)

public:
	CReadTagAccessDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CReadTagAccessDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_TAG_ACCESS_READ };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CTagInfo*	m_tagInfo;
	CEdit		m_editEPC;
	CComboBox m_comboMBank;
	CComboBox m_comboOffset;
	CComboBox m_comboCount;

public:
	int			m_nComboMBank;
	int			m_nComboOffset;
	int			m_nComboCount;
	CString		m_strEPC;

	void SetSelectedTag(CTagInfo* pTag);
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboOffset();
	afx_msg void OnBnClickedOk();
};
