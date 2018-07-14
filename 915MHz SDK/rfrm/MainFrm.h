// MainFrm.h : interface of the CMainFrame class
//


#pragma once

#include "FlatSplitterWnd.h"

class CFlatSplitter_DemoView;
class CRFIDRadioManager;
class CFirmwareUpdateStatusDlg;
class CMessageView;
#ifdef LARGE_COUNT
class CCountDlg;
#endif

//class CSTWToolBar;
class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

#ifdef LARGE_COUNT
	CCountDlg* m_wndCountDlg;
#endif
	CFirmwareUpdateStatusDlg* m_pFirmwareStatusDlg;

// Attributes
protected:  // control bar embedded members
#ifdef WINCE
	CCommandBar		m_wndCommandBar;	// Command Bar
#endif
	CStatusBarEx	m_wndStatusBar;		// Status Bar
	CToolBar		m_wndToolBar;		// Toolbar
	CSTWToolBar		m_wndInfoToolBar;		// Toolbar
	CToolBar		m_wndTagAccessToolBar;		// Toolbar

//	CEdit			m_wndEditLeakTime;
	CEdit			m_wndTotalReadCount;
	CComboBox		m_wndComboLeakTime;
//	CEdit			m_wndEdit;
	CButton			m_wndLeakCheckButton;

	CReBar			m_wndReBar;

	CStatusBarEdit			*m_pWndEdit;
	CStatusBarSliderCtrl	*m_pWndSliderCtrl;
	CStatusBarButton		*m_pWndButton;
	CStatusBarProgressCtrl	*m_pWndProgressCtrl;
	CStatusBarLabel			*m_pWndLabel;
	CRFIDRadioManager		*m_pRFIDRadioManager;
	//CSplitterWndEx m_wndSplitter;
	CFlatSplitterWnd		m_wndSplitter;

#ifdef WINCE
public:
	BOOL			m_bOneExcuteThread;
#endif

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
#ifdef WINCE
	afx_msg void OnToolbarDropDown(NMTOOLBAR* pnmh, LRESULT* plRes);
#elif WIN32
	afx_msg void OnToolbarDropDown(NMHDR* pnmh, LRESULT* plRes);
#endif
	afx_msg void OnRfidMacversion();
	afx_msg void OnViewList();
	
	DECLARE_MESSAGE_MAP()
public:
	static DWORD WINAPI WakeUpThreadFunc(LPVOID pParam);
	// RFID Radio Enumeration
//	RFID_RADIO_ENUM* m_pRFIDRadioEnum;
//	CPtrList<RFID_RADIO_HANDLE, RFID_RADIO_HANDLE*> m_listHandleRadio;
	BOOL m_bPowerState;
	void SetStatusBar(int nPaneID, CString strMessage);
	afx_msg void OnClose();

	void AddStatusBarPane(int nPosition, int nPaneType, int width, int nID);
	void UpdateTagCount(ULONG count);
	void UpdateTagReadCount(ULONG count);
	void AddTagReadCount(ULONG count);
	CRFIDRadioManager* GetRFIDRadioManager();
	LRESULT OnReset(WPARAM wParam = NULL, LPARAM lParam = NULL);
	LRESULT OnTagAccess(WPARAM wParam = 0, LPARAM lParam = 0);

	afx_msg void OnRfidReaderSet();
	afx_msg void OnUpdateRfidReaderSet(CCmdUI *pCmdUI);
	afx_msg void OnRfidPowerOnOff();
	afx_msg void OnUpdateRfidPowerOnOff(CCmdUI *pCmdUI);
	afx_msg void OnRfidReset();
	afx_msg void OnUpdateRfidReset(CCmdUI *pCmdUI);
	afx_msg void OnTagRead();
	afx_msg void OnTagWrite();
	afx_msg void OnNcDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRfidInterfaceconfiguration();
	afx_msg void OnUpdateRfidInterfaceconfiguration(CCmdUI *pCmdUI);
	afx_msg void OnRfidInventoryOnce();
	afx_msg void OnUpdateRfidInventoryOnce(CCmdUI *pCmdUI);
	afx_msg void OnFirmwareUpdateoption();
	afx_msg void OnFirmwareUpdate();
	afx_msg void OnUpdateFirmwareUpdate(CCmdUI *pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTagLock();
	afx_msg void OnUpdateTagLock(CCmdUI *pCmdUI);
	afx_msg void OnTagKill();
	afx_msg void OnUpdateTagKill(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTagRead(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTagWrite(CCmdUI *pCmdUI);
	afx_msg void OnRfidConnection();
	afx_msg void OnUpdateRfidConnection(CCmdUI *pCmdUI);
	afx_msg void OnRfidDisconnection();
	afx_msg void OnUpdateRfidDisconnection(CCmdUI *pCmdUI);
	afx_msg void OnRfidRunInventory();
	afx_msg void OnUpdateRfidRunInventory(CCmdUI *pCmdUI);
	afx_msg void OnRfidStopInventory();
	afx_msg void OnUpdateRfidStopInventory(CCmdUI *pCmdUI);
	afx_msg void OnCbnSelchangeLeakTime();
	afx_msg void OnCbnEditchangeLeakTime();
	afx_msg void OnBnClickedLeakEnable();

public:
	CMessageView* GetMessageView(void);
};


