#pragma once


// CAlgorithmSetPage dialog

class CAlgorithmSetPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CAlgorithmSetPage)

public:
	CAlgorithmSetPage(const wchar_t* lpszTitle, HICON hIcon);
	virtual ~CAlgorithmSetPage();

// Attribute
public:
	// dialog size as you see in the resource view (original size)
	CRect	m_rcOriginalRect;


	// actual scroll position
	int		m_nScrollPos;
	// actual dialog height
	int		m_nCurHeight;


// Dialog Data
	enum { IDD = IDD_DIALOG_ALGORITHM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_ctrlComboAlgorithm;
	CComboBox m_ctrlComboSelectState;
	CComboBox m_ctrlComboSelectSession;
	CComboBox m_ctrlComboSelectSessionTarget;
	CComboBox m_ctrlComboRepeatUntilNoTags;
	CComboBox m_ctrlComboToggleTarget;

	CSpinButtonCtrl	m_ctrlSpinButtonCtrlStartQ;
	CSpinButtonCtrl	m_ctrlSpinButtonCtrlMinQ;
	CSpinButtonCtrl	m_ctrlSpinButtonCtrlMaxQ;
	CSpinButtonCtrl	m_ctrlSpinButtonCtrlRetryCount;
	CSpinButtonCtrl	m_ctrlSpinButtonCtrlMaxQueryReps;
	CSpinButtonCtrl	m_ctrlSpinButtonCtrlQValue;
	CSpinButtonCtrl	m_ctrlSpinButtonCtrlThresholdMultiplier;


	CScrollBar	m_ctrlScrollAlgorithm;
	afx_msg void OnCbnSelchangeComboAlgorithm();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void		Control_VScroll(int interval) ;
		
	afx_msg void OnCbnSelchangeComboSelectState();
	afx_msg void OnCbnSelchangeComboSession();
	afx_msg void OnCbnSelchangeComboSessionTarget();
	afx_msg void OnEnChangeEditStartQ();
	afx_msg void OnEnChangeEditMinQ();
	afx_msg void OnEnChangeEditMaxQ();
	afx_msg void OnEnChangeEditRetryCount();
	afx_msg void OnCbnSelchangeComboToggleTarget();
	afx_msg void OnEnChangeEditQValue();
	afx_msg void OnEnChangeEditMaxQueryReps();
	afx_msg void OnEnChangeEditThresholdMultiplier();
	afx_msg void OnCbnSelchangeComboRepeteUntileNoTags();
};
