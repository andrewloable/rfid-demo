// GeneralSetPage.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "GeneralSetPage.h"

#include "MainFrm.h"
#include "RFIDRadioManager.h"


// CGeneralSetPage dialog

IMPLEMENT_DYNAMIC(CGeneralSetPage, CPropertyPage)

CGeneralSetPage::CGeneralSetPage(const wchar_t* lpszTitle, HICON hIcon)
: CPropertyPage(CGeneralSetPage::IDD)
{
	// Set the title and icon.
	if( NULL != hIcon )
	{
		m_psp.dwFlags |= PSP_USEHICON;
		//			HICON hIconTab = AfxGetApp()->LoadIcon( m_nIconID );
		m_psp.hIcon = hIcon;
	}
}

CGeneralSetPage::~CGeneralSetPage()
{
}

void CGeneralSetPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_REGION, m_ctrlComboRegion);
	DDX_Control(pDX, IDC_COMBO_LINK_PROFILE, m_ctrlComboLinkProfile);
	DDX_Control(pDX, IDC_COMBO_DATA_FORMAT, m_ctrlComboDataFormat);
	DDX_Control(pDX, IDC_COMBO_OPERATION_MODE, m_ctrlComboOperationMode);
	DDX_Control(pDX, IDC_COMBO_INVENTORY_ALGORITHM, m_ctrlComboInventoryAlgorithm);
	DDX_Control(pDX, IDC_COMBO_BEEP_MODE, m_ctrlComboBeepMode);
}


BEGIN_MESSAGE_MAP(CGeneralSetPage, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_OPERATION_MODE, &CGeneralSetPage::OnCbnSelchangeComboOperationMode)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA_FORMAT, &CGeneralSetPage::OnCbnSelchangeComboDataFormat)
	ON_CBN_SELCHANGE(IDC_COMBO_REGION, &CGeneralSetPage::OnCbnSelchangeComboRegion)
	ON_CBN_SELCHANGE(IDC_COMBO_INVENTORY_ALGORITHM, &CGeneralSetPage::OnCbnSelchangeComboInventoryAlgorithm)
	ON_CBN_SELCHANGE(IDC_COMBO_BEEP_MODE, &CGeneralSetPage::OnCbnSelchangeComboBeepMode)
END_MESSAGE_MAP()


// CGeneralSetPage message handlers

BOOL CGeneralSetPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// Region
//	m_ctrlComboRegion.AddString(_T("0 : FCC (USA)"));
//	m_ctrlComboRegion.AddString(_T("1 : ETSI (LBT)"));
//	m_ctrlComboRegion.AddString(RFID_MAC_REGION_NEWETSI_GENERIC
//	m_ctrlComboRegion.AddString(_T("2 : MIC (Korea)"));
//	m_ctrlComboRegion.AddString(_T("3 : UNKNOWN"));

	// Link Profile
// 	m_ctrlComboLinkProfile.AddString(_T("0 : DSB_ASK / M0 / 10 Khz"));
// 	m_ctrlComboLinkProfile.AddString(_T("1 : DSB_ASK / M1 / 160 Khz"));
// 	m_ctrlComboLinkProfile.AddString(_T("2 : PR_ASK / M2 / 250 Khz"));
// 	m_ctrlComboLinkProfile.AddString(_T("3 : PR_ASK / M2 / 300 Khz"));
// 	m_ctrlComboLinkProfile.AddString(_T("4 : DSB_ASK / M0 / 400 Khz"));
// 	m_ctrlComboLinkProfile.AddString(_T("5 : PR_ASK / M1 / 250 Khz"));

	// Data Format
// 	m_ctrlComboDataFormat.AddString(_T("COMPACT"));
// 	m_ctrlComboDataFormat.AddString(_T("NORMAL"));
// 	m_ctrlComboDataFormat.AddString(_T("EXTENDED"));

	// Operation Mode
// 	m_ctrlComboOperationMode.AddString(_T("NONCONTINOUS"));
// 	m_ctrlComboOperationMode.AddString(_T("CONTINOUS"));
// 	m_ctrlComboOperationMode.AddString(_T("UNKNOWN"));

	// Inventory Algorithm
// 	m_ctrlComboInventoryAlgorithm.AddString(_T("FixedQ"));
// 	m_ctrlComboInventoryAlgorithm.AddString(_T("DynamicQ"));
// 	m_ctrlComboInventoryAlgorithm.AddString(_T("DynamicQ Adjust"));
// 	m_ctrlComboInventoryAlgorithm.AddString(_T("DynamicQ Thresh"));
// 	m_ctrlComboInventoryAlgorithm.AddString(_T("UNKNOWN"));

// 	m_ctrlComboBeepMode.AddString(_T("DISABLE"));
// 	m_ctrlComboBeepMode.AddString(_T("ENABLE"));
// 	m_ctrlComboBeepMode.AddString(_T("UNKNOWN"));

	// Default Cursor Select
	theApp.DoWaitCursor(1);
	/////////////////////////////////////////////////////////////////////////////
	// Region
	/////////////////////////////////////////////////////////////////////////////
	RFID_MAC_REGION region;
	pFrame->GetRFIDRadioManager()->GetRadioMacRegion(0, &region);

	if (region == RFID_MAC_REGION_FCC_GENERIC)
		m_ctrlComboRegion.SetCurSel(0);
	else if(region == RFID_MAC_REGION_ETSI_GENERIC)
		m_ctrlComboRegion.SetCurSel(1);
	else if(region == RFID_MAC_REGION_KOREA_FHSS)
		m_ctrlComboRegion.SetCurSel(2);
	else
		m_ctrlComboRegion.SetCurSel(3);


	/////////////////////////////////////////////////////////////////////////////
	// Link Profile
	/////////////////////////////////////////////////////////////////////////////

	m_ctrlComboLinkProfile.SetCurSel(2);

	/////////////////////////////////////////////////////////////////////////////
	// Response Mode
	/////////////////////////////////////////////////////////////////////////////
	RFID_RESPONSE_MODE respnseDataMode;
	pFrame->GetRFIDRadioManager()->GetRadioResponseDataMode(0, &respnseDataMode);

	if(respnseDataMode == RFID_RESPONSE_MODE_COMPACT)
		m_ctrlComboDataFormat.SetCurSel(0);
	else if(respnseDataMode == RFID_RESPONSE_MODE_NORMAL)
		m_ctrlComboDataFormat.SetCurSel(1);
	else
		m_ctrlComboDataFormat.SetCurSel(2);

	/////////////////////////////////////////////////////////////////////////////
	// Operation Mode 
	/////////////////////////////////////////////////////////////////////////////
	RFID_RADIO_OPERATION_MODE operationMode;
	pFrame->GetRFIDRadioManager()->GetRadioOperationMode(0, &operationMode);

	if(operationMode == RFID_RADIO_OPERATION_MODE_NONCONTINUOUS)
		m_ctrlComboOperationMode.SetCurSel(0);
	else if( operationMode == RFID_RADIO_OPERATION_MODE_CONTINUOUS)
		m_ctrlComboOperationMode.SetCurSel(1);
	else
		m_ctrlComboOperationMode.SetCurSel(2);

	/////////////////////////////////////////////////////////////////////////////
	// Inventory Algorithm
	/////////////////////////////////////////////////////////////////////////////
	RFID_18K6C_SINGULATION_ALGORITHM singulationAlgorithm;
	pFrame->GetRFIDRadioManager()->GetRadio18K6CCurrentSingulationAlgorithm(0, &singulationAlgorithm);

	if(singulationAlgorithm == RFID_18K6C_SINGULATION_ALGORITHM_FIXEDQ)
		m_ctrlComboInventoryAlgorithm.SetCurSel(0);
	else if( singulationAlgorithm == RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ)
		m_ctrlComboInventoryAlgorithm.SetCurSel(1);
	else if( singulationAlgorithm == RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ_ADJUST)
		m_ctrlComboInventoryAlgorithm.SetCurSel(2);
	else if( singulationAlgorithm == RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ_THRESH)
		m_ctrlComboInventoryAlgorithm.SetCurSel(3);
	else
		m_ctrlComboInventoryAlgorithm.SetCurSel(4);


	/////////////////////////////////////////////////////////////////////////////
	// Operation Mode 
	/////////////////////////////////////////////////////////////////////////////
	RFID_RADIO_BEEP_MODE beepMode;
	pFrame->GetRFIDRadioManager()->GetRadioBeepMode(0, &beepMode);

	if(beepMode == RFID_RADIO_BEEP_MODE_DISABLE)
		m_ctrlComboBeepMode.SetCurSel(0);
	else if( beepMode == RFID_RADIO_BEEP_MODE_ENABLE)
		m_ctrlComboBeepMode.SetCurSel(1);
	else
		m_ctrlComboBeepMode.SetCurSel(2);

	theApp.DoWaitCursor(-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CGeneralSetPage::OnCbnSelchangeComboOperationMode()
{
	int flag = m_ctrlComboOperationMode.GetCurSel();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	switch(flag)
	{
	case 0:
		pFrame->GetRFIDRadioManager()->SetRadioOperationMode(0, 
			RFID_RADIO_OPERATION_MODE_NONCONTINUOUS);
		break;
	case 1:
		pFrame->GetRFIDRadioManager()->SetRadioOperationMode(0, 
			RFID_RADIO_OPERATION_MODE_CONTINUOUS);
		break;
	default:
		pFrame->GetRFIDRadioManager()->SetRadioOperationMode(0, 
			RFID_RADIO_OPERATION_MODE_CONTINUOUS - 1);
		break;
	}

}

void CGeneralSetPage::OnCbnSelchangeComboDataFormat()
{
	int flag = m_ctrlComboDataFormat.GetCurSel();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	switch(flag)
	{
	case 0:
		pFrame->GetRFIDRadioManager()->SetRadioResponseDataMode(0, 
			RFID_RESPONSE_MODE_COMPACT);
		break;
	case 1:
		pFrame->GetRFIDRadioManager()->SetRadioResponseDataMode(0, 
			RFID_RESPONSE_MODE_NORMAL);
		break;
	case 2:
		pFrame->GetRFIDRadioManager()->SetRadioResponseDataMode(0, 
			RFID_RESPONSE_MODE_EXTENDED);
		break;
	default:
		pFrame->GetRFIDRadioManager()->SetRadioResponseDataMode(0, 
			RFID_RESPONSE_MODE_NORMAL);
		break;
	}
	
}

void CGeneralSetPage::OnCbnSelchangeComboRegion()
{
	int flag = m_ctrlComboRegion.GetCurSel();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	switch(flag)
	{
	case 0:
		pFrame->GetRFIDRadioManager()->SetRadioMacRegion(0, 
			RFID_MAC_REGION_FCC_GENERIC);
		break;
	case 1:
		pFrame->GetRFIDRadioManager()->SetRadioMacRegion(0, 
			RFID_MAC_REGION_ETSI_GENERIC);
		break;
	case 2:
		pFrame->GetRFIDRadioManager()->SetRadioMacRegion(0, 
			RFID_MAC_REGION_NEWETSI_GENERIC);
		break;
	case 3:
		pFrame->GetRFIDRadioManager()->SetRadioMacRegion(0, 
			RFID_MAC_REGION_JAPAN_GENERIC);
		break;
	case 4:
		pFrame->GetRFIDRadioManager()->SetRadioMacRegion(0, 
			RFID_MAC_REGION_KOREA_LBT);
		break;
	case 5:
		pFrame->GetRFIDRadioManager()->SetRadioMacRegion(0, 
			RFID_MAC_REGION_KOREA_FHSS);
		break;
	}
}

void CGeneralSetPage::OnCbnSelchangeComboInventoryAlgorithm()
{
	int flag = m_ctrlComboInventoryAlgorithm.GetCurSel();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	switch(flag)
	{
	case 0:
		pFrame->GetRFIDRadioManager()->SetRadio18K6CCurrentSingulationAlgorithm(0,
			RFID_18K6C_SINGULATION_ALGORITHM_FIXEDQ);
		break;
	case 1:
		pFrame->GetRFIDRadioManager()->SetRadio18K6CCurrentSingulationAlgorithm(0,
			RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ);
		break;
	case 2:
		pFrame->GetRFIDRadioManager()->SetRadio18K6CCurrentSingulationAlgorithm(0,
			RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ_ADJUST);
		break;
	case 3:
		pFrame->GetRFIDRadioManager()->SetRadio18K6CCurrentSingulationAlgorithm(0,
			RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ_THRESH);
		break;
	default:
		break;
	}
}


void CGeneralSetPage::OnCbnSelchangeComboBeepMode()
{
	int flag = m_ctrlComboBeepMode.GetCurSel();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	switch(flag)
	{
	case 0:
		pFrame->GetRFIDRadioManager()->SetRadioBeepMode(0,
			RFID_RADIO_BEEP_MODE_DISABLE);
		break;
	case 1:
		pFrame->GetRFIDRadioManager()->SetRadioBeepMode(0,
			RFID_RADIO_BEEP_MODE_ENABLE);
		break;
	default:
		break;
	}

}
