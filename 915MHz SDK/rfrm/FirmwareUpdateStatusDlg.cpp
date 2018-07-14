// ../FirmwareUpdateStatusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
//#include "../FirmwareUpdateStatusDlg.h"
#include "FirmwareUpdateStatusDlg.h"

#include "MainFrm.h"

#include "afxmt.h"

CEvent g_eventStart;
CEvent g_eventKill;

// CFirmwareUpdateStatusDlg dialog

IMPLEMENT_DYNAMIC(CFirmwareUpdateStatusDlg, CDialog)

CFirmwareUpdateStatusDlg::CFirmwareUpdateStatusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFirmwareUpdateStatusDlg::IDD, pParent)
	, m_pThread(NULL)
	, m_nSecond(0)
{

}

CFirmwareUpdateStatusDlg::~CFirmwareUpdateStatusDlg()
{
}

void CFirmwareUpdateStatusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROGRESS1, m_progress);

}


BEGIN_MESSAGE_MAP(CFirmwareUpdateStatusDlg, CDialog)
	ON_WM_NCDESTROY()
	ON_MESSAGE(WM_FIRMWARE_MSG, &CFirmwareUpdateStatusDlg::OnFirmwareMessage)
	ON_MESSAGE(WM_FIRMWARE_UPDATE_START, &CFirmwareUpdateStatusDlg::OnFirmwareUpdateStart)
	ON_MESSAGE(WM_FIRMWARE_UPDATE_END, &CFirmwareUpdateStatusDlg::OnFirmwareUpdateEnd)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CFirmwareUpdateStatusDlg message handlers

void CFirmwareUpdateStatusDlg::OnNcDestroy()
{
	CDialog::OnNcDestroy();

//	::WaitForSingleObject(m_pThread, INFINITE);
	delete this;
//	((CMainFrame*)GetParent())->m_pFirmwareStatusDlg = NULL;
}

BOOL CFirmwareUpdateStatusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rectFrame, rectDlg;

	AfxGetMainWnd()->GetClientRect(rectFrame);
	AfxGetMainWnd()->ClientToScreen(rectFrame);
	GetWindowRect(rectDlg);

	int nXPos = rectFrame.left + (rectFrame.Width() / 2) 
		- (rectDlg.Width() / 2);
	int nYPos = rectFrame.top + (rectFrame.Height() / 2) 
		- (rectDlg.Height() / 2);

	//When setting window's position, we make 
	//it the TOP Window. Making it the TOPMOST may
	//not be such a good idea and may annoy some people!!
	//The most important thing to keep in mind here 
	//is to specify SWP_NOCOPYBITS as the 
	//the window sizing and positioning flag, 
	//otherwise all valid contents of the client area
	//of the previous window position are copied 
	//into the client area after the window is 
	//sized or repositioned.

	::SetWindowPos(m_hWnd, HWND_TOP, nXPos, nYPos, 
		rectDlg.Width(), rectDlg.Height(), 
#ifdef _WIN32_WCE
		SWP_NOMOVE
#else
		SWP_NOCOPYBITS
#endif
		);


	m_progress.SetRange(0, 100);
	m_progress.SetPos(0);

	// 쓰래드를 시작한다.
	m_pThread = AfxBeginThread((AFX_THREADPROC)ThreadProc, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, 0);

	// if not create Thread 
	if( !m_pThread )
	{
		TRACE( TEXT("Cannot start Firmware Update thread!\n") );
		return FALSE;
	}

//	m_pThread->m_bAutoDelete = FALSE;
	m_pThread->ResumeThread();


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

DWORD WINAPI CFirmwareUpdateStatusDlg::ThreadProc(LPVOID pParam)
{
	int i = 0;
	CFirmwareUpdateStatusDlg* dlg = (CFirmwareUpdateStatusDlg*)pParam;
	//-------------------------------------------------------------
	// start 이벤트가 Signaled될 때까지 기다린다.
	::WaitForSingleObject(g_eventStart.m_hObject, INFINITE);

	while(TRUE)
	{
		dlg->m_progress.SetPos(i);

		Sleep(100);
		i++;

		if( i > 100)
			i = 0;
		///////////////////////
		//-------------------------------------------------------------
		// Kill 이벤트가 설정되면 루프를 빠져나간다.
		if( ::WaitForSingleObject(g_eventKill.m_hObject, 0)==WAIT_OBJECT_0)
			break;
	}
	
//	::PostMessage( dlg->GetSafeHwnd(), WM_DESTROY, 0 , 0);
	dlg->DestroyWindow();
	
	return 0L;
}

BOOL CFirmwareUpdateStatusDlg::Start()
{
	// start 이벤트를 설정(Signal) 한다.
	// 이순간부터 위의 worker Thread가 실제적으로
	// 루프를 돌게된다.

	return g_eventStart.SetEvent();
}

BOOL CFirmwareUpdateStatusDlg::End()
{
	// Kill 이벤트를 설정한다.
	return g_eventKill.SetEvent();
}

BOOL CFirmwareUpdateStatusDlg::GetThreadStatus()
{
	// check is the thread still active
	DWORD dwExitCode = 0;
	GetExitCodeThread(m_pThread, &dwExitCode);
	return(dwExitCode == STILL_ACTIVE);
}

LRESULT CFirmwareUpdateStatusDlg::OnFirmwareMessage(WPARAM wParam, LPARAM lParam)
{
	CString	strStatus((LPCTSTR)wParam), strResult((LPCTSTR) lParam);

	CStatic* pStaticStatus = (CStatic*)GetDlgItem(IDC_STATIC_STATUS);
	CStatic* pStaticResult = (CStatic*)GetDlgItem(IDC_STATIC_RESULT);

	pStaticStatus->SetWindowText(strStatus);
	pStaticResult->SetWindowText(strResult);

//	Sleep(1200);

	return S_OK;
}

LRESULT CFirmwareUpdateStatusDlg::OnFirmwareUpdateStart(WPARAM wParam, LPARAM lParam)
{
	Start();

	SetTimer(0, 1000, NULL);

	return 1;
}

LRESULT CFirmwareUpdateStatusDlg::OnFirmwareUpdateEnd(WPARAM wParam, LPARAM lParam)
{
	End();

	KillTimer(0);

	CDialog::OnOK();

	return 1;
}

void CFirmwareUpdateStatusDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString strTimer;

	switch(nIDEvent)
	{
	case 0:
		strTimer.Format(TEXT("%u sec"), m_nSecond);
		CStatic* pStaticStatus = (CStatic*)GetDlgItem(IDC_STATIC_TIMER);
		m_nSecond++;
		pStaticStatus->SetWindowText(strTimer);
		break;
	}

	CDialog::OnTimer(nIDEvent);
}
