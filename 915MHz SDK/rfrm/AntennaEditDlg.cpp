// AntennaEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "AntennaEditDlg.h"

#include "MainFrm.h"
#include "RFIDRadioManager.h"
// CAntennaEditDlg dialog

IMPLEMENT_DYNAMIC(CAntennaEditDlg, CDialog)
/*
CAntennaEditDlg::CAntennaEditDlg(CWnd* pParent)
	: CDialog(CAntennaEditDlg::IDD, pParent)
	, m_iAntennaNumber(0)
	, m_nEditPowerLevel(0)
	, m_nEditPhyTxPort(0)
	, m_nEditDWellTime(0)
	, m_nEditNumberInventoryCycles(0)
{

}
*/
CAntennaEditDlg::CAntennaEditDlg(CWnd* pParent /*=NULL*/, int antennaNumber)
: CDialog(CAntennaEditDlg::IDD, pParent)
, m_iAntennaNumber(antennaNumber)
, m_nEditPowerLevel(0)
, m_nEditPhyTxPort(0)
, m_nEditDWellTime(0)
, m_nEditNumberInventoryCycles(0)
{

}

CAntennaEditDlg::~CAntennaEditDlg()
{
}

void CAntennaEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STATE, m_ctrlComboAntennaState);

	DDX_Text(pDX, IDC_EDIT_POWER, m_nEditPowerLevel);
	DDX_Control(pDX, IDC_SPIN_POWER, m_ctrlSpinPowerLevel);

	DDX_Text(pDX, IDC_EDIT_PHY_TX, m_nEditPhyTxPort);
	DDX_Control(pDX, IDC_SPIN_PHY_TX, m_ctrlSpinPhyTxPort);

	DDX_Text(pDX, IDC_EDIT_DWELL, m_nEditDWellTime);
	DDX_Control(pDX, IDC_SPIN_DWELL, m_ctrlSpinDWellTime);

	DDX_Text(pDX, IDC_EDIT_INV_CYCLE, m_nEditNumberInventoryCycles);
	DDX_Control(pDX, IDC_SPIN_INV_CYCLE, m_ctrlSpinNumberInventoryCycles);
}


BEGIN_MESSAGE_MAP(CAntennaEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAntennaEditDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CAntennaEditDlg message handlers

BOOL CAntennaEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	RFID_ANTENNA_PORT_STATUS antennaStatus;
	RFID_ANTENNA_PORT_CONFIG antennaConf;
	RFID_STATUS status;

	if(RFID_STATUS_OK !=
		(status = 
		pFrame->GetRFIDRadioManager()->GetRadioAntennaPortStatus(0, m_iAntennaNumber, &antennaStatus)))
	{
		TRACE1("Get Antenna Port Status failed:  RC = %d\n", status);
		return FALSE;
	}

	if(RFID_STATUS_OK !=
		(status = 
		pFrame->GetRFIDRadioManager()->GetRadioAntennaPortConfiguration(0, m_iAntennaNumber, &antennaConf)))
	{
		TRACE1("Get Antenna Port Status failed:  RC = %d\n", status);
		return FALSE;
	}

// 	GetWindowRect(&rect);
// 
// 	MoveWindow(0, 0, rect.Width(), rect.Height());
// 	SetWindowPos(&wndTopMost, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE | SWP_NOSIZE);

	m_ctrlComboAntennaState.AddString(_T("Enable"));
	m_ctrlComboAntennaState.AddString(_T("Disable"));
	m_ctrlComboAntennaState.AddString(_T("Unknown"));

	if(MacToHost32(antennaStatus.state) == RFID_ANTENNA_PORT_STATE_ENABLED)
		m_ctrlComboAntennaState.SetCurSel(0);
	else if(MacToHost32(antennaStatus.state) == RFID_ANTENNA_PORT_STATE_DISABLED)
		m_ctrlComboAntennaState.SetCurSel(1);
	else
		m_ctrlComboAntennaState.SetCurSel(2);

	m_ctrlSpinPowerLevel.SetRange32(0, 30);
	m_ctrlSpinPhyTxPort.SetRange32(0, 10);
	m_ctrlSpinDWellTime.SetRange32(0, 5000);
	m_ctrlSpinNumberInventoryCycles.SetRange32(0, 10000);

	m_ctrlSpinPowerLevel.SetPos(antennaConf.powerLevel / 10);
	m_ctrlSpinPowerLevel.SetBuddy(GetDlgItem(IDC_EDIT_POWER));

	m_ctrlSpinPhyTxPort.SetPos(antennaConf.physicalTxPort);
	m_ctrlSpinPhyTxPort.SetBuddy(GetDlgItem(IDC_EDIT_PHY_TX));

	m_ctrlSpinDWellTime.SetPos(antennaConf.dwellTime);
	m_ctrlSpinDWellTime.SetBuddy(GetDlgItem(IDC_EDIT_DWELL));

	m_ctrlSpinNumberInventoryCycles.SetPos(antennaConf.numberInventoryCycles);
	m_ctrlSpinNumberInventoryCycles.SetBuddy(GetDlgItem(IDC_EDIT_INV_CYCLE));;

	SetDlgItemInt(IDC_EDIT_POWER, antennaConf.powerLevel / 10);
	SetDlgItemInt(IDC_EDIT_PHY_TX, antennaConf.physicalTxPort);
	SetDlgItemInt(IDC_EDIT_DWELL, antennaConf.dwellTime);
	SetDlgItemInt(IDC_EDIT_INV_CYCLE, antennaConf.numberInventoryCycles);
//	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAntennaEditDlg::OnBnClickedOk()
{
	UpdateData();

	RFID_STATUS status;

	int flag = m_ctrlComboAntennaState.GetCurSel();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	RFID_ANTENNA_PORT_CONFIG config;
	memset(&config,0,sizeof(RFID_ANTENNA_PORT_CONFIG));

	switch(flag)
	{
	case 0:
		pFrame->GetRFIDRadioManager()->SetRadioAntennaPortState(0, m_iAntennaNumber,
			RFID_ANTENNA_PORT_STATE_ENABLED);
		break;
	case 1:
		pFrame->GetRFIDRadioManager()->SetRadioAntennaPortState(0, m_iAntennaNumber,
			RFID_ANTENNA_PORT_STATE_DISABLED);
		break;
	case 2:
		pFrame->GetRFIDRadioManager()->SetRadioAntennaPortState(0, m_iAntennaNumber,
			RFID_ANTENNA_PORT_STATE_DISABLED - 1);
		break;
	default:
		break;
	}

	config.length                   = sizeof( RFID_ANTENNA_PORT_CONFIG );
	config.powerLevel				= m_ctrlSpinPowerLevel.GetPos() * 10;
	config.dwellTime                = m_ctrlSpinDWellTime.GetPos();
	config.numberInventoryCycles    = m_ctrlSpinNumberInventoryCycles.GetPos();
	config.physicalRxPort           = m_ctrlSpinPhyTxPort.GetPos();
	config.physicalTxPort           = m_ctrlSpinPhyTxPort.GetPos();
	config.antennaSenseThreshold    = 1048575; //12974;

	if(RFID_STATUS_OK !=
		(status = 
		pFrame->GetRFIDRadioManager()->SetRadioAntennaPortConfiguration(0, m_iAntennaNumber, config)))
	{
		TRACE1("Get Antenna Port Status failed:  RC = %d\n", status);
		return;
	}

//	UpdateData(TRUE);

	OnOK();
}
