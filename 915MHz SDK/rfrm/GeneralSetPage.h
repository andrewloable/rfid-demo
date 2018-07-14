#pragma once

//#include "IconPropertyPage.h"

// CGeneralSetPage dialog

class CGeneralSetPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CGeneralSetPage)

public:
	CGeneralSetPage(const wchar_t* lpszTitle, HICON hIcon = NULL);
	virtual ~CGeneralSetPage();

// Dialog Data
	enum { IDD = IDD_DIALOG_GENERAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_ctrlComboRegion;
	CComboBox m_ctrlComboLinkProfile;
	CComboBox m_ctrlComboDataFormat;
	CComboBox m_ctrlComboOperationMode;
	CComboBox m_ctrlComboInventoryAlgorithm;
	CComboBox m_ctrlComboBeepMode;
	afx_msg void OnCbnSelchangeComboOperationMode();
	afx_msg void OnCbnSelchangeComboDataFormat();
	afx_msg void OnCbnSelchangeComboRegion();
	afx_msg void OnCbnSelchangeComboInventoryAlgorithm();
	afx_msg void OnCbnSelchangeComboBeepMode();
};
