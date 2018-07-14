#pragma once

#include "SpinButtonCtrlEx.h"

using namespace techwin;
// CAntennaEditDlg dialog

class CAntennaEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CAntennaEditDlg)

public:
//	CAntennaEditDlg(CWnd* pParent = NULL);   // standard constructor
	CAntennaEditDlg(CWnd* pParent = NULL, int antennaNumber = 0);   // standard constructor
	virtual ~CAntennaEditDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_ANTENNA_EDIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int m_iAntennaNumber;
	CComboBox m_ctrlComboAntennaState;

	// Edit box for Spin buddy
	int				m_nEditPowerLevel;
	int			m_nEditPhyTxPort;
	int			m_nEditDWellTime;
	int m_nEditNumberInventoryCycles;

	// Spin Ctrl
	CSpinButtonCtrlEx m_ctrlSpinPowerLevel;
	CSpinButtonCtrlEx m_ctrlSpinPhyTxPort;
	CSpinButtonCtrlEx m_ctrlSpinDWellTime;
	CSpinButtonCtrlEx m_ctrlSpinNumberInventoryCycles;

	afx_msg void OnBnClickedOk();
};
