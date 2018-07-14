// EngineeringSetPage.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "EngineeringSetPage.h"

#include "MainFrm.h"
#include "RFIDRadioManager.h"

#include "RFRMDoc.h"

#define SESSION_0	0x01
#define SESSION_1	0x02
#define SESSION_2	0x04
#define SESSION_3	0x08

// CEngineeringSetPage dialog

IMPLEMENT_DYNAMIC(CEngineeringSetPage, CPropertyPage)

CEngineeringSetPage::CEngineeringSetPage(const wchar_t* lpszTitle, HICON hIcon)
	: CPropertyPage(CEngineeringSetPage::IDD)
	, m_nSelectedSession(0)
{
	// Set the title and icon.
	if( NULL != hIcon )
	{
		m_psp.dwFlags |= PSP_USEHICON;
		//			HICON hIconTab = AfxGetApp()->LoadIcon( m_nIconID );
		m_psp.hIcon = hIcon;
	}
}

CEngineeringSetPage::~CEngineeringSetPage()
{
}

void CEngineeringSetPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CHECK_CARRIER_ON_OFF, m_ctrlCheckCarrier);
	DDX_Control(pDX, IDC_CHECK_LEAK_CONT, m_ctrlCheckLeakMode);
	DDX_Radio(pDX, IDC_RADIO_EPC_DISPLAY, m_nDisplayMode);
	DDX_Control(pDX, IDC_RADIO_EPC_DISPLAY, m_ctrlButtonEPCDisplay);
	DDX_Control(pDX, IDC_RADIO_ASCII_DISPLAY, m_ctrlButtonASCIIDisplay);
}


BEGIN_MESSAGE_MAP(CEngineeringSetPage, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT_TRANSFER_TIME, &CEngineeringSetPage::OnEnChangeEditTransferTime)
	ON_EN_CHANGE(IDC_EDIT_MAX_TRIAL_COUNT, &CEngineeringSetPage::OnEnChangeEditMaxTrialCount)
	ON_BN_CLICKED(IDC_CHECK_CARRIER_ON_OFF, &CEngineeringSetPage::OnBnClickedCheckCarrierOnOff)
	ON_BN_CLICKED(IDC_CHECK_LEAK_CONT, &CEngineeringSetPage::OnBnClickedCheckLeakCont)
	ON_BN_CLICKED(IDC_CHECK_SESSION0, &CEngineeringSetPage::OnBnClickedCheckSession0)
	ON_BN_CLICKED(IDC_CHECK_SESSION1, &CEngineeringSetPage::OnBnClickedCheckSession1)
	ON_BN_CLICKED(IDC_CHECK_SESSION2, &CEngineeringSetPage::OnBnClickedCheckSession2)
	ON_BN_CLICKED(IDC_CHECK_SESSION3, &CEngineeringSetPage::OnBnClickedCheckSession3)
	ON_BN_CLICKED(IDC_BUTTON_BEEP_FILE_PATH, &CEngineeringSetPage::OnBnClickedButtonBeepFilePath)
	ON_BN_CLICKED(IDC_RADIO_EPC_DISPLAY, &CEngineeringSetPage::OnBnClickedRadioEpcDisplay)
	ON_BN_CLICKED(IDC_RADIO_ASCII_DISPLAY, &CEngineeringSetPage::OnBnClickedRadioAsciiDisplay)
END_MESSAGE_MAP()


// CEngineeringSetPage message handlers

BOOL CEngineeringSetPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CRFRMDoc* pDoc = (CRFRMDoc*)pFrame->GetActiveDocument();
	INT32U	transferTime, trialCount;

	pFrame->GetRFIDRadioManager()->GetRadioTransferTime(0, &transferTime);
	pFrame->GetRFIDRadioManager()->GetRadioTrialCount(0, &trialCount);
	
	if(m_ctrlCheckCarrier.GetCheck())
		pFrame->GetRFIDRadioManager()->RadioCarrierWaveOn();
	else
		pFrame->GetRFIDRadioManager()->RadioCarrierWaveOff();

	SetDlgItemInt(IDC_EDIT_TRANSFER_TIME, transferTime);
	SetDlgItemInt(IDC_EDIT_MAX_TRIAL_COUNT, trialCount);

	if(pDoc->GetLeakMode())
		m_ctrlCheckLeakMode.SetCheck(TRUE);
	else
		m_ctrlCheckLeakMode.SetCheck(FALSE);

	/////////////////////////////////////////////////////////////////////////////////
	// Display Mode
	m_nDisplayMode = AfxGetApp()->GetProfileInt(_T("Engineering"),_T("Display"), 0);

	/////////////////////////////////////////////////////////////////////////////////
	// Beep File Path
	CString Path = AfxGetApp()->GetProfileString(TEXT("WaveBox"), TEXT("Path"));

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_BEEP_FILE_PATH);
	pEdit->SetWindowText(Path);
	/////////////////////////////////////////////////////////////////////////////////

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEngineeringSetPage::OnEnChangeEditTransferTime()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	INT32U	transferTime;

	transferTime = GetDlgItemInt(IDC_EDIT_TRANSFER_TIME);

	pFrame->GetRFIDRadioManager()->SetRadioTransferTime(0, transferTime);
}

void CEngineeringSetPage::OnEnChangeEditMaxTrialCount()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	INT32U	trialCount;

	trialCount = GetDlgItemInt(IDC_EDIT_MAX_TRIAL_COUNT);

	pFrame->GetRFIDRadioManager()->SetRadioTrialCount(0, trialCount);
}

void CEngineeringSetPage::OnBnClickedCheckCarrierOnOff()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	if(m_ctrlCheckCarrier.GetCheck())
		pFrame->GetRFIDRadioManager()->RadioCarrierWaveOn();
	else
		pFrame->GetRFIDRadioManager()->RadioCarrierWaveOff();
}

void CEngineeringSetPage::OnBnClickedCheckLeakCont()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CRFRMDoc* pDoc = (CRFRMDoc*)pFrame->GetActiveDocument();
	
	if(BST_CHECKED == m_ctrlCheckLeakMode.GetCheck())
		pDoc->SetLeakMode(TRUE);
	else
		pDoc->SetLeakMode(FALSE);
}

void CEngineeringSetPage::OnBnClickedCheckSession0()
{
	m_nSelectedSession = m_nSelectedSession ^ SESSION_0;
}

void CEngineeringSetPage::OnBnClickedCheckSession1()
{
	m_nSelectedSession = m_nSelectedSession ^ SESSION_1;
}

void CEngineeringSetPage::OnBnClickedCheckSession2()
{
	m_nSelectedSession = m_nSelectedSession ^ SESSION_2;
}

void CEngineeringSetPage::OnBnClickedCheckSession3()
{
	m_nSelectedSession = m_nSelectedSession ^ SESSION_3;
}

void CEngineeringSetPage::OnBnClickedButtonBeepFilePath()
{
	CString l_strFileName;
	CFileDialog l_WaveFileDlg(TRUE, NULL, NULL, 
		OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, 
		TEXT("Firmware Update Files (*.wav)|*.wav|"), this);

	int iRet = l_WaveFileDlg.DoModal();
	l_strFileName = l_WaveFileDlg.GetPathName();

	if(iRet == IDOK && l_strFileName.GetLength() > 0)
	{
		try
		{
			CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
			pFrame->GetRFIDRadioManager()->SetWaveBox(l_strFileName);

			/////////////////////////////////////////////////////////////////////////////////
			// Beep File Path
			CString Path = AfxGetApp()->GetProfileString(TEXT("WaveBox"), TEXT("Path"));

			CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_BEEP_FILE_PATH);
			pEdit->SetWindowText(Path);
			/////////////////////////////////////////////////////////////////////////////////
		}
		catch (CException* e)
		{
			TRACE(TEXT("Set Wabe Box Error : %ld"), GetLastError());
			e->ReportError();
		}
	}
}

void CEngineeringSetPage::OnBnClickedRadioEpcDisplay()
{
	AfxGetApp()->WriteProfileInt(_T("Engineering"),_T("Display"), RFID_TAG_DISPLAY_MODE_EPC);
}

void CEngineeringSetPage::OnBnClickedRadioAsciiDisplay()
{
	AfxGetApp()->WriteProfileInt(_T("Engineering"),_T("Display"), RFID_TAG_DISPLAY_MODE_ASCII);
}
