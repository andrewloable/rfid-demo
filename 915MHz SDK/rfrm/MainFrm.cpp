// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "RFRM.h"

#include "MainFrm.h"

#include "RFRMDoc.h"
#include "RFRMView.h"
#include "MessageView.h"

#include "SplashWnd.h"

#include "RFIDRadioManager.h"

#include "ReaderSetSheet.h"
#include "GeneralSetPage.h"
#include "AntennaSetPage.h"
#include "SelectCriteriaSetPage.h"
#include "AlgorithmSetPage.h"
#include "PostSingulationSetPage.h"
#include "EngineeringSetPage.h"
#include "FrequencyBandPage.h"

#include "ReadTagAccessDlg.h"
#include "WriteTagAccessDlg.h"
#include "LockTagAccessDlg.h"
#include "KillTagAccessDlg.h"

#include "InterfaceDlg.h"
#include "FirmwareUpdateOptionDlg.h"
#include "FirmwareUpdateStatusDlg.h"

#include "Util.h"

#ifdef LARGE_COUNT
#include "CountDlg.h"
#endif

#ifdef _WIN32_WCE
#include <pkfuncs.h> //전원관리
#include <msgqueue.h>		// 메시지 큐 관련
#include <pm.h>				// 전원관리 관련
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef WIN32_PLATFORM_PSPC
#define TOOLBAR_HEIGHT 24
#endif // WIN32_PLATFORM_PSPC

#ifdef _WIN32_WCE
#define QUEUE_ENTRIES   3
#define MAX_NAMELEN     200
#define QUEUE_SIZE      (QUEUE_ENTRIES * (sizeof(POWER_BROADCAST) + MAX_NAMELEN))

const DWORD dwAdornmentFlags = 0; // exit button

#endif
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
#ifdef WINCE
	ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, &CMainFrame::OnToolbarDropDown)
#elif WIN32
	ON_NOTIFY(TBN_DROPDOWN, AFX_IDW_TOOLBAR, &CMainFrame::OnToolbarDropDown)
#endif
	ON_WM_NCDESTROY()
	ON_CBN_SELCHANGE(ID_LEAK_TIME, &CMainFrame::OnCbnSelchangeLeakTime)
	ON_CBN_EDITCHANGE(ID_LEAK_TIME, &CMainFrame::OnCbnEditchangeLeakTime)
	ON_BN_CLICKED(ID_LEAK_CHECK, &CMainFrame::OnBnClickedLeakEnable)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_RADIO_RESET, &CMainFrame::OnReset)
	ON_MESSAGE(WM_TAG_ACCESS, &CMainFrame::OnTagAccess)
	ON_COMMAND(ID_RFID_CONNECTION, &CMainFrame::OnRfidConnection)
	ON_COMMAND(ID_RFID_DISCONNECTION, &CMainFrame::OnRfidDisconnection)
	ON_COMMAND(ID_RFID_RUN_INVENTORY, &CMainFrame::OnRfidRunInventory)
	ON_COMMAND(ID_RFID_STOP_INVENTORY, &CMainFrame::OnRfidStopInventory)
	ON_COMMAND(ID_RFID_MACVERSION, &CMainFrame::OnRfidMacversion)
	ON_COMMAND(ID_VIEW_LIST, &CMainFrame::OnViewList)
	ON_COMMAND(ID_RFID_POWER_ON_OFF, &CMainFrame::OnRfidPowerOnOff)
	ON_COMMAND(ID_RFID_READER_SET, &CMainFrame::OnRfidReaderSet)
	ON_COMMAND(ID_RFID_RESET, &CMainFrame::OnRfidReset)
	ON_COMMAND(ID_RFID_INTERFACECONFIGURATION, &CMainFrame::OnRfidInterfaceconfiguration)
	ON_COMMAND(ID_RFID_INVENTORY_ONCE, &CMainFrame::OnRfidInventoryOnce)
	ON_COMMAND(ID_FIRMWARE_UPDATEOPTION, &CMainFrame::OnFirmwareUpdateoption)
	ON_COMMAND(ID_FIRMWARE_UPDATE, &CMainFrame::OnFirmwareUpdate)
	ON_COMMAND(ID_TAG_READ, &CMainFrame::OnTagRead)
	ON_COMMAND(ID_TAG_WRITE, &CMainFrame::OnTagWrite)
	ON_COMMAND(ID_TAG_LOCK, &CMainFrame::OnTagLock)
	ON_COMMAND(ID_TAG_KILL, &CMainFrame::OnTagKill)
	ON_UPDATE_COMMAND_UI(ID_RFID_CONNECTION, &CMainFrame::OnUpdateRfidConnection)
	ON_UPDATE_COMMAND_UI(ID_RFID_DISCONNECTION, &CMainFrame::OnUpdateRfidDisconnection)
	ON_UPDATE_COMMAND_UI(ID_RFID_RUN_INVENTORY, &CMainFrame::OnUpdateRfidRunInventory)
	ON_UPDATE_COMMAND_UI(ID_RFID_STOP_INVENTORY, &CMainFrame::OnUpdateRfidStopInventory)
	ON_UPDATE_COMMAND_UI(ID_RFID_POWER_ON_OFF, &CMainFrame::OnUpdateRfidPowerOnOff)
	ON_UPDATE_COMMAND_UI(ID_RFID_RESET, &CMainFrame::OnUpdateRfidReset)
	ON_UPDATE_COMMAND_UI(ID_RFID_INTERFACECONFIGURATION, &CMainFrame::OnUpdateRfidInterfaceconfiguration)
	ON_UPDATE_COMMAND_UI(ID_RFID_INVENTORY_ONCE, &CMainFrame::OnUpdateRfidInventoryOnce)
	ON_UPDATE_COMMAND_UI(ID_FIRMWARE_UPDATE, &CMainFrame::OnUpdateFirmwareUpdate)
	ON_UPDATE_COMMAND_UI(ID_TAG_LOCK, &CMainFrame::OnUpdateTagLock)
	ON_UPDATE_COMMAND_UI(ID_TAG_KILL, &CMainFrame::OnUpdateTagKill)
	ON_UPDATE_COMMAND_UI(ID_TAG_READ, &CMainFrame::OnUpdateTagRead)
	ON_UPDATE_COMMAND_UI(ID_TAG_WRITE, &CMainFrame::OnUpdateTagWrite)
	ON_UPDATE_COMMAND_UI(ID_RFID_READER_SET, &CMainFrame::OnUpdateRfidReaderSet)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
: m_pRFIDRadioManager(NULL)
, m_bPowerState(FALSE)
, m_pWndEdit(NULL)
, m_pWndSliderCtrl(NULL)
, m_pWndButton(NULL)
, m_pWndProgressCtrl(NULL)
, m_pFirmwareStatusDlg(NULL)
{
	CSplashWnd::ShowSplashScreen(1500, IDB_BITMAP_SPLASH, this);

	m_pRFIDRadioManager = new CRFIDRadioManager();
}

CMainFrame::~CMainFrame()
{
	m_pRFIDRadioManager->Disconnect();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CString strClear;

#ifdef WIN32_PLATFORM_PSPC
	if (!m_wndCommandBar.Create(this) ||
	    !m_wndCommandBar.InsertMenuBar(IDR_MAINFRAME) ||
	    !m_wndCommandBar.AddAdornments(dwAdornmentFlags) ||
	    !m_wndCommandBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create CommandBar\n");
		return -1;      // fail to create
	}

	m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() | CBRS_SIZE_FIXED);
#elif WIN32_PLATFORM_WFSP
	if (!m_wndCommandBar.Create(this) ||
	    !m_wndCommandBar.InsertMenuBar(IDR_MAINFRAME) ||
	    !m_wndCommandBar.AddAdornments(dwAdornmentFlags)||
		!m_wndCommandBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create CommandBar\n");
		return -1;      // fail to create
	}

	m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() | CBRS_SIZE_FIXED);

	CWnd* pWnd = CWnd::FromHandlePermanent(m_wndCommandBar.m_hWnd);

	RECT rect, rectDesktop;
	pWnd->GetWindowRect(&rect);
	pWnd->GetDesktopWindow()->GetWindowRect(&rectDesktop);

	int cx = rectDesktop.right - rectDesktop.left;
	int cy = (rectDesktop.bottom - rectDesktop.top) - (rect.bottom - rect.top);
	this->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE | SWP_NOZORDER);
#elif defined(WINCE) && !defined(WIN32_PLATFORM_PSPC) && !defined(WIN32_PLATFORM_WFSP)

	if (!m_wndCommandBar.Create(this) ||
	    !m_wndCommandBar.InsertMenuBar(IDR_MAINFRAME) ||
		!m_wndCommandBar.AddAdornments(dwAdornmentFlags))
	{
		TRACE0("Failed to create CommandBar\n");
		return -1;      // fail to create
	}
	m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_FIXED);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Toolbar Setting
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// 이미지리스트 구성
	CBitmap bmpHot, bmpCold;
	CImageList imgHot, imgCold;

	bmpHot.LoadBitmap(IDB_BITMAP_TOOLBAR_COLOR_16);
	imgHot.Create(16, 16, ILC_COLOR24 |ILC_MASK, 6, 0);    // 8개 단추
	imgHot.Add(&bmpHot, RGB(255,255,255));
	m_wndToolBar.GetToolBarCtrl().SetImageList(&imgHot);
	imgHot.Detach();    // 반드시 분리한다
	bmpHot.Detach();

	bmpCold.LoadBitmap(IDB_BITMAP_TOOLBAR_GRAY_16);
	imgCold.Create(16, 16, ILC_COLOR24 |ILC_MASK, 6, 0);    // 8개 단추
	imgCold.Add(&bmpCold, RGB(255,255,255));
	m_wndToolBar.GetToolBarCtrl().SetDisabledImageList(&imgCold);
	imgCold.Detach();    // 반드시 분리한다
	bmpCold.Detach();

	CRect temp;
	m_wndToolBar.GetItemRect(0,&temp);
	m_wndToolBar.SetSizes(CSize(temp.Width(), temp.Height()), CSize(16,16));


	DWORD dwStyle = m_wndToolBar.GetButtonStyle(m_wndToolBar.CommandToIndex(ID_VIEW_LIST));
	dwStyle |= TBSTYLE_DROPDOWN;
	m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(ID_VIEW_LIST), dwStyle);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Toolbar Setting
	if (!m_wndInfoToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndInfoToolBar.LoadToolBar(IDR_INFO_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// 이미지리스트 구성
	CBitmap bmpHot2, bmpCold2;
	CImageList imgHot2, imgCold2;

	bmpHot2.LoadBitmap(IDB_BITMAP_INFO_TOOLBAR_COLOR_16);
	imgHot2.Create(16, 16, ILC_COLOR24 |ILC_MASK, 2, 0);    // 8개 단추
	imgHot2.Add(&bmpHot2, RGB(255,255,255));
	m_wndInfoToolBar.GetToolBarCtrl().SetImageList(&imgHot2);
	imgHot2.Detach();    // 반드시 분리한다
	bmpHot2.Detach();

	bmpCold2.LoadBitmap(IDB_BITMAP_INFO_TOOLBAR_GRAY_16);
	imgCold2.Create(16, 16, ILC_COLOR24 |ILC_MASK, 2, 0);    // 8개 단추
	imgCold2.Add(&bmpCold2, RGB(255,255,255));
	m_wndInfoToolBar.GetToolBarCtrl().SetDisabledImageList(&imgCold2);
	imgCold2.Detach();    // 반드시 분리한다
	bmpCold2.Detach();

	m_wndInfoToolBar.GetItemRect(0,&temp);
	m_wndInfoToolBar.SetSizes(CSize(temp.Width(), temp.Height()), CSize(16,16));

	if(!m_wndInfoToolBar.CreateEdit(m_wndTotalReadCount, 
		4, 
		ID_READ_TOTAL_COUNT, 50))
	{
		TRACE0("Failed to create Info toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndInfoToolBar.CreateCheckButton(m_wndLeakCheckButton, 5, ID_LEAK_CHECK, 30))
	{
		TRACE0("Failed to create toolbar's combo box\n");
		return -1;      // fail to create
	}

	if (!m_wndInfoToolBar.CreateComboBox(m_wndComboLeakTime, 6, ID_LEAK_TIME, 40, 50))
	{
		TRACE0("Failed to create toolbar's combo box\n");
		return -1;      // fail to create
	}

	m_wndComboLeakTime.AddString(_T("1"));
	m_wndComboLeakTime.AddString(_T("2"));
	m_wndComboLeakTime.AddString(_T("3"));
	m_wndComboLeakTime.AddString(_T("4"));
	m_wndComboLeakTime.AddString(_T("5"));
	m_wndComboLeakTime.AddString(_T("6"));
	m_wndComboLeakTime.AddString(_T("7"));
	m_wndComboLeakTime.AddString(_T("8"));
	m_wndComboLeakTime.AddString(_T("9"));
	m_wndComboLeakTime.AddString(_T("10"));

	m_wndTotalReadCount.SetWindowText(_T("0"));

	m_wndComboLeakTime.SetCurSel(0);
	m_wndComboLeakTime.EnableWindow(FALSE);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if(!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndInfoToolBar))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_bOneExcuteThread) 
	{
		DWORD ThreadID;
		HANDLE hThread = CreateThread(NULL, 0, WakeUpThreadFunc, this, 0, &ThreadID);
		CloseHandle(hThread);

		m_bOneExcuteThread = TRUE;
	} 

#elif WIN32
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// 이미지리스트 구성
	CBitmap bmpHot, bmpCold;
	CImageList imgHot, imgCold;

	bmpHot.LoadBitmap(IDB_BITMAP_TOOLBAR_COLOR_32);
	imgHot.Create(32, 32, ILC_COLOR24 |ILC_MASK, 7, 0);    // 8개 단추
	imgHot.Add(&bmpHot, RGB(255,255,255));
	m_wndToolBar.GetToolBarCtrl().SetImageList(&imgHot);
	imgHot.Detach();    // 반드시 분리한다
	bmpHot.Detach();

	bmpCold.LoadBitmap(IDB_BITMAP_TOOLBAR_GRAY_32);
	imgCold.Create(32, 32, ILC_COLOR24 |ILC_MASK, 7, 0);    // 8개 단추
	imgCold.Add(&bmpCold, RGB(255,255,255));
	m_wndToolBar.GetToolBarCtrl().SetDisabledImageList(&imgCold);
	imgCold.Detach();    // 반드시 분리한다
	bmpCold.Detach();

	CRect temp;
	m_wndToolBar.GetItemRect(0,&temp);
	m_wndToolBar.SetSizes(CSize(temp.Width(), temp.Height()), CSize(32,32));

	DWORD dwStyle = m_wndToolBar.GetButtonStyle(m_wndToolBar.CommandToIndex(ID_VIEW_LIST));
	dwStyle |= TBSTYLE_DROPDOWN;
	m_wndToolBar.SetButtonStyle(m_wndToolBar.CommandToIndex(ID_VIEW_LIST), dwStyle);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Toolbar Setting
	if (!m_wndInfoToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndInfoToolBar.LoadToolBar(IDR_INFO_TOOLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// 이미지리스트 구성
	CBitmap bmpHot2, bmpCold2;
	CImageList imgHot2, imgCold2;

	bmpHot2.LoadBitmap(IDB_BITMAP_INFO_TOOLBAR_COLOR_32);
	imgHot2.Create(32, 32, ILC_COLOR24 |ILC_MASK, 3, 0);    // 8개 단추
	imgHot2.Add(&bmpHot2, RGB(255,255,255));
	m_wndInfoToolBar.GetToolBarCtrl().SetImageList(&imgHot2);
	imgHot2.Detach();    // 반드시 분리한다
	bmpHot2.Detach();

	bmpCold2.LoadBitmap(IDB_BITMAP_INFO_TOOLBAR_GRAY_32);
	imgCold2.Create(32, 32, ILC_COLOR24 |ILC_MASK, 3, 0);    // 8개 단추
	imgCold2.Add(&bmpCold2, RGB(255,255,255));
	m_wndInfoToolBar.GetToolBarCtrl().SetDisabledImageList(&imgCold2);
	imgCold2.Detach();    // 반드시 분리한다
	bmpCold2.Detach();

	m_wndInfoToolBar.GetItemRect(0,&temp);
	m_wndInfoToolBar.SetSizes(CSize(temp.Width(), temp.Height()), CSize(32,32));

	if(!m_wndInfoToolBar.CreateEdit(m_wndTotalReadCount, 
		5, 
		ID_READ_TOTAL_COUNT, 100))
	{
		TRACE0("Failed to create Info toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndInfoToolBar.CreateCheckButton(m_wndLeakCheckButton, 6, ID_LEAK_CHECK, 30))
	{
		TRACE0("Failed to create toolbar's combo box\n");
		return -1;      // fail to create
	}

	if (!m_wndInfoToolBar.CreateComboBox(m_wndComboLeakTime, 7, ID_LEAK_TIME, 40, 50))
	{
		TRACE0("Failed to create toolbar's combo box\n");
		return -1;      // fail to create
	}

	m_wndComboLeakTime.AddString(_T("1"));
	m_wndComboLeakTime.AddString(_T("2"));
	m_wndComboLeakTime.AddString(_T("3"));
	m_wndComboLeakTime.AddString(_T("4"));
	m_wndComboLeakTime.AddString(_T("5"));
	m_wndComboLeakTime.AddString(_T("6"));
	m_wndComboLeakTime.AddString(_T("7"));
	m_wndComboLeakTime.AddString(_T("8"));
	m_wndComboLeakTime.AddString(_T("9"));
	m_wndComboLeakTime.AddString(_T("10"));

	m_wndTotalReadCount.SetWindowText(_T("0"));

	m_wndComboLeakTime.SetCurSel(0);
	m_wndComboLeakTime.EnableWindow(FALSE);
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}


	if (!m_wndTagAccessToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndTagAccessToolBar.LoadToolBar(IDR_TOOLBAR_TAGACCESS))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// 이미지리스트 구성
	CBitmap bmpHot3, bmpCold3;
	CImageList imgHot3, imgCold3;

	bmpHot3.LoadBitmap(IDB_BITMAP_TAG_ACCESS_COLOR_32);
	imgHot3.Create(32, 32, ILC_COLOR24 |ILC_MASK, 4, 0);    // 3개 단추
	imgHot3.Add(&bmpHot3, RGB(255,255,255));
	m_wndTagAccessToolBar.GetToolBarCtrl().SetImageList(&imgHot3);
	imgHot3.Detach();    // 반드시 분리한다
	bmpHot3.Detach();

	bmpCold3.LoadBitmap(IDB_BITMAP_TAG_ACCESS_GRAY_32);
	imgCold3.Create(32, 32, ILC_COLOR24 |ILC_MASK, 4, 0);    // 3개 단추
	imgCold3.Add(&bmpCold3, RGB(255,255,255));
	m_wndTagAccessToolBar.GetToolBarCtrl().SetDisabledImageList(&imgCold3);
	imgCold3.Detach();    // 반드시 분리한다
	bmpCold3.Detach();

	m_wndTagAccessToolBar.GetItemRect(0,&temp);
	m_wndTagAccessToolBar.SetSizes(CSize(temp.Width(), temp.Height()), CSize(32,32));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndInfoToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndTagAccessToolBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_wndInfoToolBar);
	DockControlBar(&m_wndTagAccessToolBar);

	HCURSOR crsArrow = ::LoadCursor(0, IDC_ARROW);
	CString classLeft =		AfxRegisterWndClass(CS_DBLCLKS, crsArrow, (HBRUSH)CBrush(RGB(255,255,255)), 0);
	const int vert_splitter_sizes[4] = { 70, 10 };

/*
	m_wndSplitterVert.Create(this);
	m_wndSplitterVert.SetPaneSizes(vert_splitter_sizes);
	m_wndSplitterVert.CreatePane(0, GetActiveView(), 0, WS_EX_CLIENTEDGE, classLeft);
*/

#ifdef LARGE_COUNT
	m_wndCountDlg = new CCountDlg(this);
	m_wndCountDlg->Create(CCountDlg::IDD, GetDesktopWindow());
	m_wndCountDlg->ShowWindow(SW_SHOW);
#endif

#endif

	m_wndStatusBar.GetStatusBarCtrl().SetMinHeight(23);

	///////////////////////////////////////////////////////////////////////////////////
	// Set Pane width
	// disable for windows ce
	//	m_wndStatusBar.SetPaneWidth(0,100);	

	strClear.LoadString(IDS_CLEAR_BUTTON);

	AddStatusBarPane(1, 4, 50, ID_INDICATOR_CLEAR);
	m_pWndButton->SetWindowText(strClear);
	UpdateData(0);

	AddStatusBarPane(2, 0, 50, ID_INDICATOR_COUNT);
	UpdateData(0);

	AddStatusBarPane(3, 1, 25, ID_INDICATOR_COUNT_EDIT);
	UpdateData(0);

	return 0;
}

#ifdef _WIN32_WCE
DWORD WINAPI CMainFrame::WakeUpThreadFunc(LPVOID pParam)
{
//	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	CMainFrame*	pFrame = (CMainFrame*) pParam;

	MSGQUEUEOPTIONS	lm_Options;
	HANDLE			lm_hPMMQ, lm_hPMNoti;
	DWORD			lm_dwErrCode, lm_dwPri = 251, lm_dwCount = 0;
	CString			lm_szErr;
	UCHAR			lm_ucBuf[QUEUE_SIZE];
	DWORD			lm_dwReadSize = 0, lm_dwFlags;
	BOOL			lm_bResult;
	DWORD			lm_dwWaitReturn = 0;

	lm_Options.dwSize			= sizeof (MSGQUEUEOPTIONS);
	lm_Options.dwFlags			= MSGQUEUE_ALLOW_BROKEN;
	lm_Options.dwMaxMessages	= 10;							// 메시지큐에 들어가는 최대 메시지 갯수
	lm_Options.cbMaxMessage		= QUEUE_SIZE;					// 메시지 하나당 최대 사이즈
	lm_Options.bReadAccess		= TRUE;

	lm_hPMMQ = CreateMsgQueue (NULL, &lm_Options);				// 메시지 큐 생성
	if (lm_hPMMQ == NULL)
	{
		lm_dwErrCode = GetLastError();
		lm_szErr.Format (TEXT("CreateMsgQueue ERROR:%d\n"), lm_dwErrCode);
		AfxMessageBox (lm_szErr);
		goto _Exit;
	}

	//RESUME시에 알림 요청을 등록합니다.
	lm_hPMNoti = RequestPowerNotifications (lm_hPMMQ, PBT_RESUME);//PBT_TRANSITION);
	if (lm_hPMNoti == NULL)
	{
		lm_dwErrCode = GetLastError();
		lm_szErr.Format (TEXT("RequestPowerNotifications ERROR:%d\n"), lm_dwErrCode);
		AfxMessageBox (lm_szErr);
		goto _Exit;
	}

	while (1)
	{
		memset (&lm_ucBuf, 0, QUEUE_SIZE);

		lm_dwWaitReturn = WaitForSingleObject (lm_hPMMQ, 100);

		if (lm_dwWaitReturn == WAIT_TIMEOUT)
		{
			continue;
		}

		lm_bResult = ReadMsgQueue (lm_hPMMQ, &lm_ucBuf, sizeof (POWER_BROADCAST), &lm_dwReadSize, INFINITE, &lm_dwFlags);

		if(lm_bResult)
		{
			if (lm_dwReadSize >= sizeof(POWER_BROADCAST))
			{
				PPOWER_BROADCAST	pB = (PPOWER_BROADCAST)&lm_ucBuf;
				if(pB->Message == PBT_RESUME)
				{
					pFrame->SetStatusBar(0, TEXT("Power On"));

					if(::GetControlState(RFID_POWER) != TRUE)
					{
						::SetControlState(RFID_POWER, TRUE);

						Sleep(1200);
						
						if(::GetControlState(RFID_GREEN_LED) != TRUE)
							::SetControlState(RFID_GREEN_LED, TRUE);
					}

					if(pFrame->GetRFIDRadioManager()->IsConnect())
					{
						pFrame->GetRFIDRadioManager()->Connect();
					}
					else
					{
						pFrame->GetRFIDRadioManager()->Disconnect();
					}

					pFrame->SetStatusBar(0, TEXT("WakeUp Complete"));
				}

				if(pB->Message == PBT_POWERINFOCHANGE)
				{
					pFrame->SetStatusBar(0, TEXT("Power Off"));
				}
			}
		}
		else
		{
			lm_dwErrCode = GetLastError ();
			lm_szErr.Format (_T("ReadMsgQueue : %d"), lm_dwErrCode);
			AfxMessageBox (lm_szErr);
			goto _Exit;
		}
	}

_Exit:
	StopPowerNotifications (lm_hPMNoti);
	CloseMsgQueue (lm_hPMMQ);

	//*** 조정후 : Thread Function이 중첩 실행의 가능성이 있어 한번만 실행시키게 만들기 위한 Flag 추가 적용시켰습니다.
	pFrame->m_bOneExcuteThread = FALSE;

//	CoUninitialize();

	return 0;
}
#endif

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}


void CMainFrame::OnNcDestroy()
{
	CFrameWnd::OnNcDestroy();

//	OnRfidPowerOnOff();
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}
#endif //_DEBUG

// CMainFrame message handlers


void CMainFrame::OnRfidConnection()
{
	m_pRFIDRadioManager->SetParent(GetActiveView());

	if(m_pRFIDRadioManager->Connect() != RFID_STATUS_OK)
	{
		SetStatusBar(0, _T("RFID Handle Create Fail"));
	}

	SetStatusBar(0, _T("Connection"));
}

void CMainFrame::OnRfidDisconnection()
{
	if(m_pRFIDRadioManager->Disconnect() == RFID_STATUS_OK)
	{
		SetStatusBar(0, _T("Disconnection"));
	}
	else
	{
		SetStatusBar(0, _T("Disconnection Fail"));
	}
}

void CMainFrame::OnRfidMacversion()
{
/*
	for(int i = 0; i < m_pRFIDRadio->GetRadioCount(); i++)
	{
		RFID_VERSION* macVersion;

		macVersion = m_pRFIDRadio->GetRadioMacVersion(i);
		CString str;

		str.Format(_T("MAC Version:\nMajor: %u\nMinor: %u\nPatch: %u\n"),
			macVersion->major,
			macVersion->minor,
			macVersion->patch);
	
		AfxMessageBox(str);
	}
*/
}
#ifdef WINCE
void CMainFrame::OnToolbarDropDown(NMTOOLBAR* pnmtbwce, LRESULT *plr)
#elif WIN32
void CMainFrame::OnToolbarDropDown(NMHDR* pnmtbw32, LRESULT* plr)
#endif
{
	CWnd *pWnd;
	UINT nID;

#ifdef WINCE
	NMTOOLBAR* pnmtb = (NMTOOLBAR*)pnmtbwce;
#elif WIN32
	NMTOOLBAR* pnmtb = (NMTOOLBAR*)pnmtbw32;
#endif

	// Switch on button command id's.
	switch (pnmtb->iItem)
	{
	case ID_VIEW_LIST:
		pWnd = &m_wndToolBar;
		nID  = IDR_MENU_LIST;
		break;
	default:
		return;
	}
	
	// load and display popup menu
	CMenu menu;
	menu.LoadMenu(nID);
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup);
	
	CRect rc;
	pWnd->SendMessage(TB_GETRECT, pnmtb->iItem, (LPARAM)&rc);
	pWnd->ClientToScreen(&rc);
	
	// Popup Menu
	pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_VERTICAL,
		rc.left, rc.bottom, this, &rc);
}

void CMainFrame::OnViewList()
{
	CPoint   pt;   
	CWnd *pWnd = &m_wndToolBar;
	UINT nID = IDR_MENU_LIST;

	// load and display popup menu
	CMenu menu;
	menu.LoadMenu(nID);
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup);
	
	CRect rc;
	GetCursorPos(&pt);   	
	pWnd->SendMessage(TB_GETRECT, ID_VIEW_LIST, (LPARAM)&rc);
	pWnd->ClientToScreen(&rc);
	
	pPopup->TrackPopupMenu( TPM_LEFTALIGN | TPM_VERTICAL,
		rc.left, rc.bottom, this, &rc);
}

void CMainFrame::SetStatusBar(int nPaneID, CString strMessage)
{
	int index = 0;

	switch(nPaneID)
	{
	case 0:
		index = m_wndStatusBar.CommandToIndex(ID_SEPARATOR); //지시자항목의 순서 번호를 얻는다.
		break;
	case 1:
		index = m_wndStatusBar.CommandToIndex(ID_INDICATOR_CAPS); //지시자항목의 순서 번호를 얻는다.
		break;
	case 2:
		index = m_wndStatusBar.CommandToIndex(ID_INDICATOR_NUM); //지시자항목의 순서 번호를 얻는다.
		break;

	default:
		break;
	}

	m_wndStatusBar.SetPaneText(index, strMessage); // 문자를 넣는다.
//	m_wndStatusBar.SetPaneText(nPaneID, strMessage);
}

void CMainFrame::OnClose()
{
	if(m_pRFIDRadioManager->IsInventory())
		m_pRFIDRadioManager->StopInventory();
	
	if(m_pRFIDRadioManager->IsConnect())
		m_pRFIDRadioManager->Disconnect();

	OnRfidPowerOnOff();

	CFrameWnd::OnClose();
}

void CMainFrame::OnRfidStopInventory()
{
	CString strTemp;

	if(RFID_STATUS_OK !=
		m_pRFIDRadioManager->StopInventory(0))
	{
		strTemp.LoadString(IDS_STRING_RFID_STOP_FAIL);
	}

	strTemp.LoadString(IDS_STRING_RFID_STOP_SUCCESS);
	SetStatusBar(0, strTemp);
}

void CMainFrame::OnRfidRunInventory()
{
	CRFRMDoc* pDoc = (CRFRMDoc*)GetActiveDocument();
	CString strTemp;

	m_pRFIDRadioManager->RunInventory(0, -1);

	// Set to Leak Timer
	if(pDoc->m_bLeakEnable)
		SetTimer(1, pDoc->m_nLeakTime * 1000, NULL);

	strTemp.LoadString(IDS_STRING_INVENTORY);
	SetStatusBar(0, strTemp);

	if (!m_wndSplitter.IsPaneHidden(Bottom))
	{
		m_wndSplitter.ShowPane(Bottom, FALSE);
	}
}

void CMainFrame::OnUpdateRfidDisconnection(CCmdUI *pCmdUI)
{
#ifdef WINCE
	if(m_pRFIDRadioManager->GetControlState(RFID_POWER))
	{
#endif
		if(m_pRFIDRadioManager->IsConnect() && !m_pRFIDRadioManager->IsInventory(0))
			pCmdUI->Enable(1);
		else
			pCmdUI->Enable(0);
#ifdef WINCE
	}
	else
	{
		pCmdUI->Enable(0);
	}
#endif
}

void CMainFrame::OnUpdateRfidRunInventory(CCmdUI *pCmdUI)
{
	if(m_pRFIDRadioManager->GetControlState(RFID_POWER) && m_pRFIDRadioManager->IsConnect() && !m_pRFIDRadioManager->IsInventory(0))
	{
		pCmdUI->Enable(1);
	}
	else
	{
		pCmdUI->Enable(0);
	}
}

void CMainFrame::OnUpdateRfidStopInventory(CCmdUI *pCmdUI)
{
	if(m_pRFIDRadioManager->IsConnect() && m_pRFIDRadioManager->IsInventory(0))
	{
		pCmdUI->Enable(1);
	}
	else
	{
		pCmdUI->Enable(0);
	}
}

void CMainFrame::OnUpdateRfidConnection(CCmdUI *pCmdUI)
{
#ifdef WINCE
	if(m_pRFIDRadioManager->GetControlState(RFID_POWER))
	{
#endif	// WINCE
		if(m_pRFIDRadioManager->IsConnect())
			pCmdUI->Enable(0);
		else
			pCmdUI->Enable(1);
#ifdef WINCE
	}
	else
	{
		pCmdUI->Enable(0);
	}
#endif	// WINCE
}

void CMainFrame::AddStatusBarPane(int nPosition, int nPaneType, int width, int nID)
{
	UpdateData();

	if( nPosition < 0 || nPosition > 20 )
		return;

	switch( nPaneType ) 
	{
	case 0: // text
		{
			BOOL bRet = m_wndStatusBar.AddPane(nID,nPosition);
			if(!bRet){
				AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
				return;
			}
		}
		break;

	case 1: // edit
		{
			m_pWndEdit = new CStatusBarEdit;
			if (!m_pWndEdit->Create(
				WS_CHILD|WS_VISIBLE|WS_TABSTOP, 
				CRect(0,0,0,0), 
				&m_wndStatusBar, 
				0))
			{
				TRACE(_T("Failed to create edit control.\n"));
				return;
			}

			m_pWndEdit->SetFont(
				CFont::FromHandle(
				(HFONT)::GetStockObject(DEFAULT_GUI_FONT)
				)
				);

			m_pWndEdit->SetWindowText(_T("0"));

			BOOL bRet = m_wndStatusBar.AddPane(nID,nPosition);
			if(!bRet){
				AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
				return;
			}

			int nIndex = m_wndStatusBar.CommandToIndex(nID);
			if (nIndex == -1)
				return;

			m_wndStatusBar.SetPaneWidth(nIndex, width);
			m_wndStatusBar.AddPaneControl(m_pWndEdit, nID, true);
		}
		break;

	case 2: // progress ctrl
		{
			m_pWndProgressCtrl = new CStatusBarProgressCtrl;
			if (!m_pWndProgressCtrl->Create(
				WS_CHILD|WS_VISIBLE|WS_TABSTOP, //|PBS_SMOOTH
				CRect(0,0,0,0), 
				&m_wndStatusBar, 
				0))
			{
				TRACE(_T("Failed to create progress control.\n"));
				return;
			}

			m_pWndProgressCtrl->ModifyStyleEx(WS_EX_STATICEDGE,0,SWP_FRAMECHANGED);

			m_pWndProgressCtrl->SetRange(0,300);
			m_pWndProgressCtrl->SetPos(0);
			m_pWndProgressCtrl->SetStep(1);

			BOOL bRet = m_wndStatusBar.AddPane(nID, nPosition);
			if(!bRet){
				AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
				return;
			}

			int nIndex = m_wndStatusBar.CommandToIndex(nID);
			if (nIndex == -1)
				return;

			m_wndStatusBar.SetPaneWidth(nIndex, width);
			m_wndStatusBar.AddPaneControl(m_pWndProgressCtrl, nID, true);

			m_pWndProgressCtrl->SetTimer(0,1,NULL);
		}
		break;

	case 3: // slider ctrl
		{
			m_pWndSliderCtrl = new CStatusBarSliderCtrl;
			if (!m_pWndSliderCtrl->Create(
				WS_CHILD|WS_VISIBLE|WS_TABSTOP|TBS_HORZ, 
				CRect(0,0,0,0), 
				&m_wndStatusBar, 
				0))
			{
				TRACE(_T("Failed to create slider control.\n"));
				return;
			}

			BOOL bRet = m_wndStatusBar.AddPane(nID, nPosition);
			if(!bRet){
				AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
				return;
			}

			int nIndex = m_wndStatusBar.CommandToIndex(nID);
			if (nIndex == -1)
				return;

			m_wndStatusBar.SetPaneWidth(nIndex, width);
			m_wndStatusBar.AddPaneControl(m_pWndSliderCtrl, nID, true);
		}
		break;

	case 4: // button
		{
			m_pWndButton = new CStatusBarButton;
			if (!m_pWndButton->Create(
				_T(""),
				WS_CHILD|WS_VISIBLE|WS_TABSTOP,
				CRect(0,0,0,0), 
				&m_wndStatusBar, 
				IDC_CLEAR_BUTTON))
			{
				TRACE(_T("Failed to create button control.\n"));
				return;
			}
			m_pWndButton->SetFont(
				CFont::FromHandle(
				(HFONT)::GetStockObject(DEFAULT_GUI_FONT)
				)
				);

			BOOL bRet = m_wndStatusBar.AddPane(nID, nPosition);
			if(!bRet){
				AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
				return;
			}

			int nIndex = m_wndStatusBar.CommandToIndex(nID);
			if (nIndex == -1)
				return;

			m_wndStatusBar.SetPaneWidth(nIndex, width);
			m_wndStatusBar.AddPaneControl(m_pWndButton, nID, true);
		}
		break;

	case 5: // label
		{
			m_pWndLabel = new CStatusBarLabel;
			if (!m_pWndLabel->Create(
				_T("Company Logo"),
				WS_CHILD|WS_VISIBLE|WS_TABSTOP|SS_CENTER,
				CRect(0,0,0,0), 
				&m_wndStatusBar, 
				0))
			{
				TRACE(_T("Failed to create label control.\n"));
				return;
			}

			m_pWndLabel->SetFont(
				CFont::FromHandle(
				(HFONT)::GetStockObject(DEFAULT_GUI_FONT)
				)
				);

			BOOL bRet = m_wndStatusBar.AddPane(nID, nPosition);
			if(!bRet){
				AfxMessageBox(_T("Pane index out of range\nor pane with same ID already exists in the status bar"), MB_ICONERROR);
				return;
			}

			int nIndex = m_wndStatusBar.CommandToIndex(nID);
			if (nIndex == -1)
				return;

			m_wndStatusBar.SetPaneWidth(nIndex, width);
			m_wndStatusBar.AddPaneControl(m_pWndLabel, nID, true);
		}
		break;
	}
}

void CMainFrame::UpdateTagCount(ULONG count)
{
	CString temp;
	temp.Format(_T("%u"), count);

	m_pWndEdit->SetWindowText(temp);

#ifdef LARGE_COUNT
//	m_wndCountDlg->SetCount(temp);
#endif


}

void CMainFrame::UpdateTagReadCount(ULONG count)
{
	CString temp;
	temp.Format(_T("%u"), count);

	m_wndTotalReadCount.SetWindowText(temp);
}

void CMainFrame::AddTagReadCount(ULONG count)
{
	CString temp;
	wchar_t* endptr;

	m_wndTotalReadCount.GetWindowText(temp);

	ULONG ulNum   = wcstoul( (LPWSTR)(LPCWSTR)temp ,&endptr ,10 );

	UpdateTagReadCount(ulNum + count);

#ifdef LARGE_COUNT
 	m_wndCountDlg->SetCount(temp);
 #endif
// 
//	temp.Format(_T("%u"), ulVer + count);

//	m_wndTotalReadCount.SetWindowText(temp);
}


//void CMainFrame::DoDataExchange(CDataExchange* pDX)
//{
//	// TODO: Add your specialized code here and/or call the base class
//	
//	CFrameWnd::DoDataExchange(pDX);
//}

void CMainFrame::OnRfidReaderSet()
{
	// Declear Image list variance
	CImageList smallImageList;

	// Create a image list and assign it to the list control
	VERIFY(smallImageList.Create(IDB_BITMAP_TAB_16, 16, 2, RGB(255, 255, 255)));

//	int   nCount = smallImageList.GetImageCount();

	// Create PropertySheet
	CReaderSetSheet sheet(_T("Reader Setting"));

	// Set Image list at each Property Page
	CGeneralSetPage				page1(TEXT("General"), smallImageList.ExtractIcon(0));
	CAntennaSetPage				page2(TEXT("Antenna"), smallImageList.ExtractIcon(1));
	CSelectCriteriaSetPage		page3(TEXT("Select Criteria"), smallImageList.ExtractIcon(1));
	CAlgorithmSetPage			page4(TEXT("Algorithm"), smallImageList.ExtractIcon(1));
	CPostSingulationSetPage		page5(TEXT("Post Singulation"), smallImageList.ExtractIcon(1));
	CFrequencyBandPage			page6(TEXT("Frequency Band"), smallImageList.ExtractIcon(1));
	CEngineeringSetPage			page7(TEXT("Engineering"), smallImageList.ExtractIcon(2));


	// Image List Detach
	smallImageList.Detach();

	// Add Page to PropertySheet
	sheet.AddPage(&page1);
	sheet.AddPage(&page2);
//	sheet.AddPage(&page3);
	sheet.AddPage(&page4);
//	sheet.AddPage(&page5);
	sheet.AddPage(&page6);
	sheet.AddPage(&page7);

	sheet.DoModal();

}

void CMainFrame::OnUpdateRfidReaderSet(CCmdUI *pCmdUI)
{
	if(m_pRFIDRadioManager->GetControlState(RFID_POWER) && m_pRFIDRadioManager->IsConnect() && !m_pRFIDRadioManager->IsInventory())
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
}

void CMainFrame::OnRfidPowerOnOff()
{
#ifdef _WIN32_WCE

	m_pRFIDRadioManager->StopInventory();
	m_pRFIDRadioManager->Disconnect();


	CString strTemp;
	// Power 
	if(GetControlState(RFID_POWER) != TRUE)
	{
		::SetControlState(RFID_POWER, TRUE);
		::SetControlState(RFID_GREEN_LED, TRUE);

		Sleep(1200);

		strTemp.LoadString(IDS_STRING_RFID_POWER_ON);
		SetStatusBar(0, strTemp);
	}
	else
	{
		::SetControlState(RFID_POWER, FALSE);
		::SetControlState(RFID_GREEN_LED, FALSE);

		strTemp.LoadString(IDS_STRING_RFID_POWER_OFF);
		SetStatusBar(0, strTemp);
	}
#endif
}

void CMainFrame::OnUpdateRfidPowerOnOff(CCmdUI *pCmdUI)
{
	CString str;

	if(::GetControlState(RFID_POWER))
	{
		str.LoadString(IDS_STRING_POWER_OFF);

		pCmdUI->SetCheck(1);
		pCmdUI->SetText(str);
//		pCmdUI->Enable(0);
	}
	else
	{
		str.LoadString(IDS_STRING_POWER_ON);

		pCmdUI->SetCheck(0);
		pCmdUI->SetText(str);
//		pCmdUI->Enable(1);		
	}
}

void CMainFrame::OnRfidReset()
{
	RFID_STATUS status;

	theApp.DoWaitCursor(1);

#ifdef _WIN32_WCE
	if(m_pRFIDRadioManager->GetControlState(RFID_POWER))
	{
		if(GetRFIDRadioManager()->IsConnect())
		{
			if(RFID_STATUS_OK !=
				(status = m_pRFIDRadioManager->Reset()))
			{
				AfxMessageBox(_T("Fail to MacReset"));
			}

			// Sleep Reboot Process
			Sleep(2000);

			GetRFIDRadioManager()->Disconnect();

			if(m_pRFIDRadioManager->Connect() != RFID_STATUS_OK)
			{
				SetStatusBar(0, _T("RFID Handle Create Fail"));
			}

			SetStatusBar(0, _T("Reset Success"));
		}
		else
		{
			GetRFIDRadioManager()->Disconnect();

			if(m_pRFIDRadioManager->Connect() != RFID_STATUS_OK)
			{
				SetStatusBar(0, _T("RFID Handle Create Fail"));
			}

			SetStatusBar(0, _T("Connection"));
		}
	}
	else
	{
		AfxMessageBox(_T("Error : Power Input Fail"));
	}
#else
	if(GetRFIDRadioManager()->IsConnect())
	{
		if(RFID_STATUS_OK !=
			(status = m_pRFIDRadioManager->Reset()))
		{
			AfxMessageBox(_T("Fail to MacReset"));
		}

		Sleep(2000);

		GetRFIDRadioManager()->Disconnect();

		if(m_pRFIDRadioManager->Connect() != RFID_STATUS_OK)
		{
			SetStatusBar(0, _T("RFID Handle Create Fail"));
		}

		SetStatusBar(0, _T("Reset Success"));

	}
	else
	{
		GetRFIDRadioManager()->Disconnect();

		if(m_pRFIDRadioManager->Connect() != RFID_STATUS_OK)
		{
			SetStatusBar(0, _T("RFID Handle Create Fail"));
		}

		SetStatusBar(0, _T("Connection"));
	}
#endif

	theApp.DoWaitCursor(-1);
}

void CMainFrame::OnUpdateRfidReset(CCmdUI *pCmdUI)
{
#ifdef WINCE
	if(m_pRFIDRadioManager->GetControlState(RFID_POWER) && GetRFIDRadioManager()->IsConnect())
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
#else 
	if(GetRFIDRadioManager()->IsConnect())
		pCmdUI->Enable(1);
	else
		pCmdUI->Enable(0);
#endif

}

CRFIDRadioManager* CMainFrame::GetRFIDRadioManager()
{
	return m_pRFIDRadioManager;
}

// Tag Read
void CMainFrame::OnTagRead()
{
	CRFRMDoc* pDoc = (CRFRMDoc*)GetActiveDocument();	
	CReadTagAccessDlg dlg(this);

	if(m_pRFIDRadioManager->IsInventory())
		OnRfidStopInventory();


	if(pDoc->GetSelectedTag() != NULL)
		dlg.SetSelectedTag(pDoc->GetSelectedTag());

	if(dlg.DoModal() == IDOK)
	{
		// Show Result View 
		if (m_wndSplitter.IsPaneHidden(Bottom))
		{
			m_wndSplitter.ShowPane(Bottom, TRUE);
		}

		if(/*dlg.m_nComboOffset != 0 && dlg.m_nComboOffset != 1 && */dlg.m_nComboCount != 0)
		{
			if(dlg.m_strEPC == TEXT(""))
				m_pRFIDRadioManager->TagRead(0, NULL, dlg.m_nComboMBank, dlg.m_nComboOffset, dlg.m_nComboCount);
			else
				m_pRFIDRadioManager->TagRead(0, (INT32U*)pDoc->GetSelectedTag()->GetTagEPC(), dlg.m_nComboMBank, dlg.m_nComboOffset, dlg.m_nComboCount);
		}
		else
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd, _T("Input parameter does not right!"), _T("Error"), MB_ICONERROR);
 		}
	}
}

// Tag Write
void CMainFrame::OnTagWrite()
{
	CRFRMDoc* pDoc = (CRFRMDoc*)GetActiveDocument();	
	CWriteTagAccessDlg dlg(this);

	// Stop Inventory
	
	if(m_pRFIDRadioManager->IsInventory())
		OnRfidStopInventory();


	if(pDoc->GetSelectedTag() != NULL)
		dlg.SetSelectedTag(pDoc->GetSelectedTag());

	if(dlg.DoModal() == IDOK)
	{
		if (m_wndSplitter.IsPaneHidden(Bottom))
		{
			m_wndSplitter.ShowPane(Bottom, TRUE);
		}


		if(/*dlg.m_nComboOffset != 0 && dlg.m_nComboOffset != 1 && */dlg.m_nComboCount != 0)
		{	
			CUtil util;
			CString sBuffer = dlg.m_strData;
			int nLength, i;	
			INT16U* pData;// = new INT16U;

			// Check to data Format for Tag Write 
			nLength = sBuffer.GetLength() / 4;
			pData = (INT16U*) malloc(sizeof(INT16U) * nLength);

			for (i=0; i < nLength; i++)
			{
				CString strWord = TEXT("");
				strWord = sBuffer.Mid(i * 4, 4);

				TRACE(strWord);

				pData[i] = static_cast<INT16U>(util.StrToWord(sBuffer.Mid(i * 4, 4)));//util.StrToINT16U(strWord);
			}

			if(dlg.m_strEPC == TEXT(""))
			{
				m_pRFIDRadioManager->TagWrite(0, NULL, dlg.m_nComboMBank, dlg.m_nComboOffset, dlg.m_nComboCount, pData);
			}
			else
			{
				m_pRFIDRadioManager->TagWrite(0, (INT32U*)pDoc->GetSelectedTag()->GetTagEPC(), dlg.m_nComboMBank, dlg.m_nComboOffset, dlg.m_nComboCount, pData);
			}
		}
		else
		{
			::MessageBox(AfxGetMainWnd()->m_hWnd, _T("Input parameter does not right!"), _T("Error"), MB_ICONERROR);
		}
	}
}

// Tag Lock
void CMainFrame::OnTagLock()
{
	CRFRMDoc* pDoc = (CRFRMDoc*)GetActiveDocument();	
	CLockTagAccessDlg dlg(this);

	if(m_pRFIDRadioManager->IsInventory())
		OnRfidStopInventory();

	if(pDoc->GetSelectedTag() != NULL)
		dlg.SetSelectedTag(pDoc->GetSelectedTag());

	if(dlg.DoModal() == IDOK)
	{
		if (m_wndSplitter.IsPaneHidden(Bottom))
		{
			m_wndSplitter.ShowPane(Bottom, TRUE);
		}


		RFID_18K6C_TAG_PERM				m_lockPermission;
		INT32U							m_AccessPassword;

		m_lockPermission.killPasswordPermissions = theApp.GetProfileInt(TEXT("TagAccess"), TEXT("KillPasswordPermission"), 0);
		m_lockPermission.accessPasswordPermissions = theApp.GetProfileInt(TEXT("TagAccess"), TEXT("AccessPasswordPermission"), 0);
		m_lockPermission.epcMemoryBankPermissions = theApp.GetProfileInt(TEXT("TagAccess"), TEXT("EPCMemoryBankPermission"), 0);
		m_lockPermission.tidMemoryBankPermissions = theApp.GetProfileInt(TEXT("TagAccess"), TEXT("TIDMemoryBankPermission"), 0);
		m_lockPermission.userMemoryBankPermissions = theApp.GetProfileInt(TEXT("TagAccess"), TEXT("UserMemoryBankPermission"), 0);

		m_AccessPassword = theApp.GetProfileInt(TEXT("TagAccess"), TEXT("AccessPassword"), 0);

		if(dlg.m_strEPC == TEXT(""))
			m_pRFIDRadioManager->TagLock(0, NULL, m_lockPermission, m_AccessPassword);
		else
			m_pRFIDRadioManager->TagLock(0, (INT32U*)pDoc->GetSelectedTag()->GetTagEPC(), m_lockPermission, m_AccessPassword);
	}
}

// Tag Kill 
void CMainFrame::OnTagKill()
{
	CRFRMDoc* pDoc = (CRFRMDoc*)GetActiveDocument();	
	CKillTagAccessDlg dlg(this);

	if(m_pRFIDRadioManager->IsInventory())
		OnRfidStopInventory();

	if(pDoc->GetSelectedTag() != NULL)
		dlg.SetSelectedTag(pDoc->GetSelectedTag());

	if(dlg.DoModal() == IDOK)
	{
		if (m_wndSplitter.IsPaneHidden(Bottom))
		{
			m_wndSplitter.ShowPane(Bottom, TRUE);
		}

		INT32U							m_AccessPassword;
		INT32U							m_KillPassword;

		m_AccessPassword = theApp.GetProfileInt(TEXT("TagAccess"), TEXT("AccessPassword"), 0);
		m_KillPassword = theApp.GetProfileInt(TEXT("TagAccess"), TEXT("KillPassword"), 0);

		if(dlg.m_strEPC == TEXT(""))
			m_pRFIDRadioManager->TagKill(0, NULL, m_AccessPassword, m_KillPassword);
		else
			m_pRFIDRadioManager->TagKill(0, (INT32U*)pDoc->GetSelectedTag()->GetTagEPC(), m_AccessPassword, m_KillPassword);	}
}

void CMainFrame::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default


	CFrameWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMainFrame::OnUpdateTagRead(CCmdUI *pCmdUI)
{
	if(GetRFIDRadioManager()->IsConnect())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CMainFrame::OnUpdateTagWrite(CCmdUI *pCmdUI)
{
	if(GetRFIDRadioManager()->IsConnect())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);

}

void CMainFrame::OnUpdateTagLock(CCmdUI *pCmdUI)
{
	if(GetRFIDRadioManager()->IsConnect())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

void CMainFrame::OnUpdateTagKill(CCmdUI *pCmdUI)
{
	if(GetRFIDRadioManager()->IsConnect())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}


void CMainFrame::OnCbnEditchangeLeakTime()
{
	CString strLeakTime;

	CRFRMDoc* pDoc = (CRFRMDoc*)GetActiveDocument();
	CRFRMView* pView = (CRFRMView*)GetActiveView();

	m_wndComboLeakTime.GetWindowText(strLeakTime);
	pDoc->m_nLeakTime = atoi((LPSTR)(LPCTSTR)strLeakTime);
	
	pView->KillTimer(1);

	if(pDoc->m_bLeakEnable)
	{
		if(pDoc->m_nLeakTime > 0)
			pView->SetTimer(1, pDoc->m_nLeakTime * 1000, NULL);
	}
}

void CMainFrame::OnCbnSelchangeLeakTime()
{
	CString strLeakTime;

	CRFRMDoc* pDoc = (CRFRMDoc*)GetActiveDocument();

	pDoc->m_nLeakTime = m_wndComboLeakTime.GetCurSel() + 1;

	KillTimer(1);

	if(pDoc->m_bLeakEnable)
	{
		if(pDoc->m_nLeakTime > 0)
			SetTimer(1, pDoc->m_nLeakTime * 1000, NULL);
	}
}

void CMainFrame::OnBnClickedLeakEnable()
{
	CRFRMDoc* pDoc = (CRFRMDoc*)GetActiveDocument();

	pDoc->m_bLeakEnable = !pDoc->m_bLeakEnable;

	if(pDoc->m_bLeakEnable)
	{
		m_wndLeakCheckButton.SetCheck(TRUE);
		m_wndComboLeakTime.EnableWindow(pDoc->m_bLeakEnable);
	}
	else
	{
		m_wndLeakCheckButton.SetCheck(FALSE);
		m_wndComboLeakTime.EnableWindow(pDoc->m_bLeakEnable);

 		KillTimer(1);
	}
}
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	CRFRMDoc* pDoc = (CRFRMDoc*)GetActiveDocument();
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case 1:
		{
			if(!pDoc->GetLeakMode())
			{
				//////////////////////////////////////////////////
				// This loop is Leak non-continuous mode

				m_pRFIDRadioManager->StopInventory();

				 KillTimer(1);
				// Timer Kill and Leak mode disable and inventory stop
//				m_wndLeakCheckButton.SetCheck(FALSE);
//				m_wndComboLeakTime.EnableWindow(pDoc->m_bLeakEnable);
			}
			else if(m_pRFIDRadioManager->IsInventory() && pDoc->GetLeakMode())		
			{
				//////////////////////////////////////////////////
				// This loop is Leak continuous mode

				m_wndTotalReadCount.SetWindowText(_T("0"));
				m_pWndEdit->SetWindowText(_T("0"));

				// remove all tag data from document
				CPtrList* tagList = pDoc->GetTagList();

				if(!tagList->IsEmpty())
				{
					POSITION pos = tagList->GetHeadPosition();
/*
					while(pos)
					{
						CTagInfo* lpTagInfoExist = (CTagInfo*)tagList->GetAt(pos);

						if(lpTagInfoExist != NULL)
							delete lpTagInfoExist;

						tagList->RemoveAt(pos);
					}
*/
					tagList->RemoveAll();
				}

				CRFRMView* pView = (CRFRMView*)GetActiveView();

				CListCtrl& listCtrl = pView->GetListCtrl();
				listCtrl.DeleteAllItems();
			}
			break;
		}
	default:
		break;
	}

	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnRfidInterfaceconfiguration()
{
#ifndef _WIN32_WCE
	CInterfaceDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		if(IDOK == MessageBox(TEXT("This machine have to Exit\nbecause Interface configuration \nhave to change."), TEXT("Warning"), MB_OK ))
		{
			PostQuitMessage(0);
		}
	}
#else
	MessageBox(TEXT("This Option don't\noperation on Windows CE"), TEXT("Warning"), MB_OK);
#endif
}

void CMainFrame::OnUpdateRfidInterfaceconfiguration(CCmdUI *pCmdUI)
{
#ifdef _WIN32_WCE
	pCmdUI->Enable(FALSE);
#endif
}

void CMainFrame::OnRfidInventoryOnce()
{
	CRFRMDoc* pDoc = (CRFRMDoc*)GetActiveDocument();
	int radioCount = m_pRFIDRadioManager->GetRadioCount();
	CString strTemp;
//	for(int i = 0; i < radioCount; i++)
//		m_pRFIDRadioManager->RunInventory(0, 0);

	if(RFID_STATUS_OK !=
		m_pRFIDRadioManager->RunInventory(0, 0))
	{
		strTemp.LoadString(IDS_STRING_RFID_STOP_FAIL);
	}

	strTemp.LoadString(IDS_STRING_RFID_STOP_SUCCESS);
	SetStatusBar(0, strTemp);

	if(pDoc->m_bLeakEnable)
		SetTimer(1, pDoc->m_nLeakTime * 1000, NULL);

	if (!m_wndSplitter.IsPaneHidden(Bottom))
	{
		m_wndSplitter.ShowPane(Bottom, FALSE);
	}
}

void CMainFrame::OnUpdateRfidInventoryOnce(CCmdUI *pCmdUI)
{
	if(m_pRFIDRadioManager->GetControlState(RFID_POWER) && m_pRFIDRadioManager->IsConnect() && !m_pRFIDRadioManager->IsInventory())
	{
		pCmdUI->Enable(1);
	}
	else
	{
		pCmdUI->Enable(0);
	}
}

void CMainFrame::OnFirmwareUpdateoption()
{
	CFirmwareUpdateOptionDlg dlg;

	dlg.DoModal();
}

void CMainFrame::OnFirmwareUpdate()
{    
	CString l_strFileName;
	CFileDialog l_FirmwareUpdateDlg(TRUE, NULL, NULL, 
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, 
		TEXT("Firmware Update Files (*.xml)|*.xml|"), this);

	int iRet = l_FirmwareUpdateDlg.DoModal();
	l_strFileName = l_FirmwareUpdateDlg.GetPathName();

	if(iRet == IDOK && l_strFileName.GetLength() > 0)
	{
		try
		{
			RFID_RADIO_FIRMWARE_MODE mode = AfxGetApp()->GetProfileInt(_T("Update"),_T("Option"), 0);

			m_pFirmwareStatusDlg = new CFirmwareUpdateStatusDlg(this);
			m_pFirmwareStatusDlg->Create(CFirmwareUpdateStatusDlg::IDD);
			m_pFirmwareStatusDlg->ShowWindow(SW_SHOW);	

			m_pRFIDRadioManager->RadioFirmwareUpdate(0, l_strFileName, mode, m_pFirmwareStatusDlg);

			theApp.DoWaitCursor(1);
		}
		catch (CException* e)
		{
			TRACE(TEXT("Thread Start Error : %ld"), GetLastError());
			e->ReportError();
		}
	}
}

LRESULT CMainFrame::OnReset(WPARAM wParam, LPARAM lParam)
{
	theApp.DoWaitCursor(-1);

	if(IDOK == MessageBox(TEXT("This machine have to Restart\nbacause Firmware Update Complete."), TEXT("Warning"), MB_OK ))
	{
		PostQuitMessage(0);
//		OnRfidReset();
	}

	return S_OK;
}
void CMainFrame::OnUpdateFirmwareUpdate(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pRFIDRadioManager->IsConnect() && !m_pRFIDRadioManager->IsInventory());
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	if (!m_wndSplitter.Create(this, pContext, Horizontal))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	CRect cr; 
	GetClientRect( &cr);
	ScreenToClient(&cr);

	if (!m_wndSplitter.AddView(Top, RUNTIME_CLASS(CRFRMView), CSize(0, 0), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	if (!m_wndSplitter.AddView(Bottom, RUNTIME_CLASS(CMessageView), CSize(0, 50), pContext))
	{
		TRACE0("Failed to create second pane\n");
		return FALSE;
	}

	if (!m_wndSplitter.IsPaneHidden(Bottom))
	{
		m_wndSplitter.ShowPane(Bottom, FALSE);
	}

/*
	if (!m_wndSplitter.CreateStatic(this, 2, 1))
	{
		TRACE0("Failed to CreateStaticSplitter\n");
		return FALSE;
	}

	CRect cr; 
	GetClientRect( &cr);
	ScreenToClient(&cr);

	if (!m_wndSplitter.AddView(0, 0, RUNTIME_CLASS(CRFRMView), CSize(0, cr.Height() * 0.7), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	if (!m_wndSplitter.AddView(1, 0, RUNTIME_CLASS(CMessageView), CSize(0, 50), pContext))
	{
		TRACE0("Failed to create first pane\n");
		return FALSE;
	}

	m_wndSplitter.SetColumnInfo(0, 200, 0);
//	m_wndSplitter.HideView(1, 0);
*/
	return TRUE;
//	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

CMessageView* CMainFrame::GetMessageView(void)
{
	return (CMessageView*)m_wndSplitter.GetPane(1, 0);
}

LRESULT CMainFrame::OnTagAccess(WPARAM wParam, LPARAM lParam)
{
	CString pTagAccess = (LPCTSTR)wParam;

	GetMessageView()->TextOut(pTagAccess);

	return 0;
}

