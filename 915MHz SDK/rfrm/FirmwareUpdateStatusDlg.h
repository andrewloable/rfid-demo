#pragma once


// CFirmwareUpdateStatusDlg dialog

class CFirmwareUpdateStatusDlg : public CDialog
{
	DECLARE_DYNAMIC(CFirmwareUpdateStatusDlg)

public:
	CFirmwareUpdateStatusDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFirmwareUpdateStatusDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_FIRMWARE_STATUS };
	CProgressCtrl	m_progress;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

// Attribute
protected:
	CWinThread *m_pThread;
	INT32U		m_nSecond;
public:
	afx_msg void OnNcDestroy();

	static DWORD WINAPI ThreadProc(LPVOID pParam);

	BOOL GetThreadStatus();
	BOOL Start();
	BOOL End();

	LRESULT OnFirmwareMessage(WPARAM wParam, LPARAM lParam);

	LRESULT OnFirmwareUpdateStart(WPARAM wParam = NULL, LPARAM lParam = NULL);
	LRESULT OnFirmwareUpdateEnd(WPARAM wParam = NULL, LPARAM lParam = NULL);

	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
