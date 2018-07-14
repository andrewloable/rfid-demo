// RFRM.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RFRM.h"
#include "MainFrm.h"

#include "RFRMDoc.h"
#include "RFRMView.h"
#include "SplashWnd.h"

#include "RFIDRadioManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRFRMApp

BEGIN_MESSAGE_MAP(CRFRMApp, CWinApp)
#ifndef WIN32_PLATFORM_WFSP
	ON_COMMAND(ID_APP_ABOUT, &CRFRMApp::OnAppAbout)
#endif // !WIN32_PLATFORM_WFSP
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()



// CRFRMApp construction
CRFRMApp::CRFRMApp()
: CWinApp()
{
	switch (GetSystemDefaultUILanguage()) 
	{ 
	case 0x0412: 
		{
//			m_hInstDLL = ::LoadLibrary(TEXT("resource_kr.dll"));
			break; 
		}
 	case 0x0409: 
		{
//	 		m_hInstDLL = ::LoadLibrary(TEXT("resource_en.dll"));
	  		break; 
		}
	case 0x0411: 
		{
			m_hInstDLL = ::LoadLibrary(TEXT("resource_jp.dll"));
			break; 
		}
	default:
			m_hInstDLL = NULL;
	} 
	
//	m_hInstDLL = ::LoadLibrary(TEXT("resource_jp.dll"));
}


// The one and only CRFRMApp object
CRFRMApp theApp;

// CRFRMApp initialization

BOOL CRFRMApp::InitInstance()
{
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);

#if defined(WIN32_PLATFORM_PSPC) || defined(WIN32_PLATFORM_WFSP)
    // SHInitExtraControls should be called once during your application's initialization to initialize any
    // of the Windows Mobile specific controls such as CAPEDIT and SIPPREF.
    SHInitExtraControls();
#endif // WIN32_PLATFORM_PSPC || WIN32_PLATFORM_WFSP


	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need

	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Samsung"));

//	m_pMainWnd = &dlg;
//	dlg.DestroyWindow();
	if (m_hInstDLL) 
		AfxSetResourceHandle(m_hInstDLL); 


	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CRFRMDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CRFRMView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}


#ifndef WIN32_PLATFORM_WFSP
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
#ifdef _DEVICE_RESOLUTION_AWARE
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CMainFrame* pFrame = static_cast<CMainFrame*>(AfxGetMainWnd());
	CString strVersion;
	CStatic* pProductVersionStatic = (CStatic*)GetDlgItem(IDC_STATIC_PRODUCT_VERSION);
	CStatic* pMacVersionStatic = (CStatic*)GetDlgItem(IDC_STATIC_MAC_VERSION);

	// Is rfid connection status?
	if(pFrame->GetRFIDRadioManager()->IsConnect())
	{
		// get firmware version information
		RFID_VERSION version;

		if(RFID_STATUS_OK ==
			(pFrame->GetRFIDRadioManager()->GetRadioFirmwareVersion(0, &version)))
		{
			strVersion.Format(TEXT("%u.%u.%u"), version.major, version.minor, version.patch);
			pMacVersionStatic->SetWindowText(strVersion);
		}
	}
	else
	{
		CString strVersion;

		strVersion.Format(TEXT("connection mode only"));
		pMacVersionStatic->SetWindowText(strVersion);
	}

	return TRUE;	// return TRUE unless you set the focus to a control
			// EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
#ifdef _DEVICE_RESOLUTION_AWARE
	ON_WM_SIZE()
#endif
END_MESSAGE_MAP()

#ifdef _DEVICE_RESOLUTION_AWARE
void CAboutDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
    	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? MAKEINTRESOURCE(IDD_ABOUTBOX_WIDE) : MAKEINTRESOURCE(IDD_ABOUTBOX));
	}
}
#endif

// App command to run the dialog
void CRFRMApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
#endif // !WIN32_PLATFORM_WFSP

BOOL CRFRMApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();

	if(pMain->GetRFIDRadioManager()->IsConnect())
	{
		if(pMsg->message==WM_KEYDOWN)
		{
			switch(pMsg->wParam)
			{
			case VK_F23:
			case VK_SPACE:
				{
					if(!pMain->GetRFIDRadioManager()->IsInventory())
						pMain->OnRfidRunInventory();
				}
				break;
			
			default:
				break;
			}
		}
		if(pMsg->message == WM_KEYUP)
		{
			switch(pMsg->wParam)
			{
			case VK_F23:
			case VK_SPACE:
				{
					if(pMain->GetRFIDRadioManager()->IsInventory())
						pMain->OnRfidStopInventory();
				}
				break;
			}
		}
	}

	return CWinApp::PreTranslateMessage(pMsg);
}
