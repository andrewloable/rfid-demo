#pragma once
#include "afxwin.h"


// CWriteTagAccessDlg dialog

class CWriteTagAccessDlg : public CDialog
{
	DECLARE_DYNAMIC(CWriteTagAccessDlg)

public:
	CWriteTagAccessDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWriteTagAccessDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_TAG_ACCESS_WRITE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	// Selected Tag Information
	CTagInfo*	m_tagInfo;
	CEdit		m_editEPC;
	CEdit		m_editWriteData;
	CComboBox	m_comboMBank;
	CComboBox	m_comboOffset;
	CComboBox	m_comboCount;

public:
	int			m_nComboMBank;
	int			m_nComboOffset;
	int			m_nComboCount;
	CString		m_strEPC;
	CString		m_strData;

	void SetSelectedTag(CTagInfo* pTag);
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeComboOffset();
	afx_msg void OnBnClickedOk();
/*	afx_msg void OnCbnSelchangeComboCount();*/
};
