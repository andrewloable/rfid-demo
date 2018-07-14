#pragma once

// CCountDlg dialog

#ifdef LARGE_COUNT

class CCountDlg : public CDialog
{
	DECLARE_DYNAMIC(CCountDlg)

public:
	CCountDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCountDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_COUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void SetCount(LPCTSTR count);
	CFont _traceLogfont;
//	CEdit m_pEditBox;
protected:
	virtual void PostNcDestroy();
};

#endif