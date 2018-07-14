// ..\AlgorithmSetPage.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "AlgorithmSetPage.h"
#include "RFIDRadioManager.h"

#include "MainFrm.h"

#include <math.h>

// CAlgorithmSetPage dialog

IMPLEMENT_DYNAMIC(CAlgorithmSetPage, CPropertyPage)

CAlgorithmSetPage::CAlgorithmSetPage(const wchar_t* lpszTitle, HICON hIcon)
	: CPropertyPage(CAlgorithmSetPage::IDD)
{
	// Set the title and icon.
	if( NULL != hIcon )
	{
		m_psp.dwFlags |= PSP_USEHICON;
		//			HICON hIconTab = AfxGetApp()->LoadIcon( m_nIconID );
		m_psp.hIcon = hIcon;
	}
}

CAlgorithmSetPage::~CAlgorithmSetPage()
{
}

void CAlgorithmSetPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ALGORITHM, m_ctrlComboAlgorithm);
	DDX_Control(pDX, IDC_COMBO_SELECT_STATE, m_ctrlComboSelectState);
	DDX_Control(pDX, IDC_COMBO_SESSION, m_ctrlComboSelectSession);
	DDX_Control(pDX, IDC_COMBO_SESSION_TARGET, m_ctrlComboSelectSessionTarget);
	DDX_Control(pDX, IDC_COMBO_REPETE_UNTILE_NO_TAGS, m_ctrlComboRepeatUntilNoTags);
	DDX_Control(pDX, IDC_COMBO_TOGGLE_TARGET, m_ctrlComboToggleTarget);

	DDX_Control(pDX, IDC_SPIN_START_Q, m_ctrlSpinButtonCtrlStartQ);
	DDX_Control(pDX, IDC_SPIN_MIN_Q, m_ctrlSpinButtonCtrlMinQ);
	DDX_Control(pDX, IDC_SPIN_MAX_Q, m_ctrlSpinButtonCtrlMaxQ);
	DDX_Control(pDX, IDC_SPIN_RETRY_COUNT, m_ctrlSpinButtonCtrlRetryCount);
	DDX_Control(pDX, IDC_SPIN_QVALUE, m_ctrlSpinButtonCtrlQValue);
	DDX_Control(pDX, IDC_SPIN_MAX_QUERY_REPS, m_ctrlSpinButtonCtrlMaxQueryReps);
	DDX_Control(pDX, IDC_SPIN_THRESHOLD_MULTIPLIER, m_ctrlSpinButtonCtrlThresholdMultiplier);
	DDX_Control(pDX, IDC_SCROLLBAR_ALGORITHM, m_ctrlScrollAlgorithm);
}


BEGIN_MESSAGE_MAP(CAlgorithmSetPage, CPropertyPage)
	ON_CBN_SELCHANGE(IDC_COMBO_ALGORITHM, &CAlgorithmSetPage::OnCbnSelchangeComboAlgorithm)
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_COMBO_SELECT_STATE, &CAlgorithmSetPage::OnCbnSelchangeComboSelectState)
	ON_CBN_SELCHANGE(IDC_COMBO_SESSION, &CAlgorithmSetPage::OnCbnSelchangeComboSession)
	ON_CBN_SELCHANGE(IDC_COMBO_SESSION_TARGET, &CAlgorithmSetPage::OnCbnSelchangeComboSessionTarget)
	ON_EN_CHANGE(IDC_EDIT_START_Q, &CAlgorithmSetPage::OnEnChangeEditStartQ)
	ON_EN_CHANGE(IDC_EDIT_MIN_Q, &CAlgorithmSetPage::OnEnChangeEditMinQ)
	ON_EN_CHANGE(IDC_EDIT_MAX_Q, &CAlgorithmSetPage::OnEnChangeEditMaxQ)
	ON_EN_CHANGE(IDC_EDIT_RETRY_COUNT, &CAlgorithmSetPage::OnEnChangeEditRetryCount)
	ON_CBN_SELCHANGE(IDC_COMBO_TOGGLE_TARGET, &CAlgorithmSetPage::OnCbnSelchangeComboToggleTarget)
	ON_EN_CHANGE(IDC_EDIT_Q_VALUE, &CAlgorithmSetPage::OnEnChangeEditQValue)
	ON_EN_CHANGE(IDC_EDIT_MAX_QUERY_REPS, &CAlgorithmSetPage::OnEnChangeEditMaxQueryReps)
	ON_EN_CHANGE(IDC_EDIT_THRESHOLD_MULTIPLIER, &CAlgorithmSetPage::OnEnChangeEditThresholdMultiplier)
	ON_CBN_SELCHANGE(IDC_COMBO_REPETE_UNTILE_NO_TAGS, &CAlgorithmSetPage::OnCbnSelchangeComboRepeteUntileNoTags)
END_MESSAGE_MAP()

// CAlgorithmSetPage message handlers

BOOL CAlgorithmSetPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	theApp.DoWaitCursor(1);

	// TODO: Add extra initialization here
	CScrollBar *SB = (CScrollBar *) GetDlgItem(IDC_SCROLLBAR_ALGORITHM);

#ifdef WINCE
	SB->SetScrollRange(0, 50);
#else
	SB->ShowWindow(SW_HIDE);
#endif

	// save the original size
	GetWindowRect(m_rcOriginalRect);

	// initial scroll position
	m_nScrollPos = 0; 

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	// save the original size
	GetWindowRect(m_rcOriginalRect);

	// Algorithm
	m_ctrlComboAlgorithm.AddString(_T("FIXEDQ"));
	m_ctrlComboAlgorithm.AddString(_T("DYNAMICQ"));
	m_ctrlComboAlgorithm.AddString(_T("DYNAMICQ_ADJUST"));
	m_ctrlComboAlgorithm.AddString(_T("DYNAMICQ_THRESH"));
	m_ctrlComboAlgorithm.AddString(_T("UNKNOWN"));

	// Select State
	m_ctrlComboSelectState.AddString(_T("ALL"));
	m_ctrlComboSelectState.AddString(_T("OFF"));
	m_ctrlComboSelectState.AddString(_T("ON"));
	m_ctrlComboSelectState.AddString(_T("UNKNOWN"));

	// Inventory Session
	m_ctrlComboSelectSession.AddString(_T("S0"));
	m_ctrlComboSelectSession.AddString(_T("S1"));
	m_ctrlComboSelectSession.AddString(_T("S2"));
	m_ctrlComboSelectSession.AddString(_T("S3"));
	m_ctrlComboSelectSession.AddString(_T("UNKNOWN"));

	// Inventory Session Target
	m_ctrlComboSelectSessionTarget.AddString(_T("A"));
	m_ctrlComboSelectSessionTarget.AddString(_T("B"));
	m_ctrlComboSelectSessionTarget.AddString(_T("UNKNOWN"));

	m_ctrlComboRepeatUntilNoTags.AddString(_T("Disable"));
	m_ctrlComboRepeatUntilNoTags.AddString(_T("Enable"));

	m_ctrlComboToggleTarget.AddString(_T("Disable"));
	m_ctrlComboToggleTarget.AddString(_T("Enable"));

	m_ctrlSpinButtonCtrlStartQ.SetRange32(0,15);
	m_ctrlSpinButtonCtrlStartQ.SetBuddy(GetDlgItem(IDC_EDIT_START_Q));

	m_ctrlSpinButtonCtrlMinQ.SetRange32(0,15);
	m_ctrlSpinButtonCtrlMinQ.SetBuddy(GetDlgItem(IDC_EDIT_MIN_Q));

	m_ctrlSpinButtonCtrlMaxQ.SetRange32(0,15);
	m_ctrlSpinButtonCtrlMaxQ.SetBuddy(GetDlgItem(IDC_EDIT_MAX_Q));

	m_ctrlSpinButtonCtrlRetryCount.SetRange32(0,255);
	m_ctrlSpinButtonCtrlRetryCount.SetBuddy(GetDlgItem(IDC_EDIT_RETRY_COUNT));

	m_ctrlSpinButtonCtrlMaxQueryReps.SetRange32(0,255);
	m_ctrlSpinButtonCtrlMaxQueryReps.SetBuddy(GetDlgItem(IDC_EDIT_MAX_QUERY_REPS));

	m_ctrlSpinButtonCtrlQValue.SetRange32(0,15);
	m_ctrlSpinButtonCtrlQValue.SetBuddy(GetDlgItem(IDC_EDIT_Q_VALUE));

	m_ctrlSpinButtonCtrlThresholdMultiplier.SetRange32(0,255);
	m_ctrlSpinButtonCtrlThresholdMultiplier.SetBuddy(GetDlgItem(IDC_EDIT_THRESHOLD_MULTIPLIER));

	//	m_ctrlSpinButtonCtrlStartQ.ModifyStyle(0,UDS_SETBUDDYINT,0);

	// Default Cursor Select
	RFID_18K6C_QUERY_PARMS	parms;
	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryParameters(0, &parms);
	
	switch(parms.singulationParms.singulationAlgorithm)
	{
	case RFID_18K6C_SINGULATION_ALGORITHM_FIXEDQ:
		{
			RFID_18K6C_SINGULATION_FIXEDQ_PARMS fixedq_parms = parms.singulationParms.parameters.fixedQ;
			CString	temp;

			CEdit* pStartQEdit = (CEdit*)GetDlgItem(IDC_EDIT_START_Q);			pStartQEdit->SetWindowText(_T(""));
			CEdit* pMinQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MIN_Q);				pMinQEdit->SetWindowText(_T(""));
			CEdit* pMaxQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_Q);				pMaxQEdit->SetWindowText(_T(""));
			CEdit* pRetryEdit = (CEdit*)GetDlgItem(IDC_EDIT_RETRY_COUNT);		pRetryEdit->SetWindowText(_T(""));
			CEdit* pQValueEdit = (CEdit*)GetDlgItem(IDC_EDIT_Q_VALUE);			pQValueEdit->SetWindowText(_T(""));
			CEdit* pMaxQueryCntEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_QUERY_REPS);					pMaxQueryCntEdit->SetWindowText(_T(""));
			CEdit* pThresholdMultiplierEdit = (CEdit*)GetDlgItem(IDC_EDIT_THRESHOLD_MULTIPLIER);	pThresholdMultiplierEdit->SetWindowText(_T(""));

			pStartQEdit->EnableWindow(FALSE);
			pMinQEdit->EnableWindow(FALSE);
			pMaxQEdit->EnableWindow(FALSE);
			pRetryEdit->EnableWindow(TRUE);
			pQValueEdit->EnableWindow(TRUE);
			pMaxQueryCntEdit->EnableWindow(FALSE);
			pThresholdMultiplierEdit->EnableWindow(FALSE);

			m_ctrlSpinButtonCtrlStartQ.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlMinQ.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlMaxQ.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlRetryCount.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlQValue.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMaxQueryReps.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlThresholdMultiplier.EnableWindow(FALSE);

			m_ctrlComboToggleTarget.EnableWindow(TRUE);
			m_ctrlComboRepeatUntilNoTags.EnableWindow(TRUE);


			temp.Format(_T("%u"),fixedq_parms.qValue);
			pQValueEdit->SetWindowText(temp);

			temp.Format(_T("%u"),fixedq_parms.retryCount);
			pRetryEdit->SetWindowText(temp);

			if(fixedq_parms.toggleTarget == 0)
				m_ctrlComboToggleTarget.SetCurSel(0);
			else
				m_ctrlComboToggleTarget.SetCurSel(1);

			if(fixedq_parms.repeatUntilNoTags == 0)
				m_ctrlComboRepeatUntilNoTags.SetCurSel(0);
			else
				m_ctrlComboRepeatUntilNoTags.SetCurSel(1);

			break;
		}
	case RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ:
		{
			RFID_18K6C_SINGULATION_DYNAMICQ_PARMS dynamicq_parms = parms.singulationParms.parameters.dynamicQ;
			CString	temp;	

			CEdit* pStartQEdit = (CEdit*)GetDlgItem(IDC_EDIT_START_Q);			pStartQEdit->SetWindowText(_T(""));
			CEdit* pMinQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MIN_Q);				pMinQEdit->SetWindowText(_T(""));
			CEdit* pMaxQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_Q);				pMaxQEdit->SetWindowText(_T(""));
			CEdit* pRetryEdit = (CEdit*)GetDlgItem(IDC_EDIT_RETRY_COUNT);		pRetryEdit->SetWindowText(_T(""));
			CEdit* pQValueEdit = (CEdit*)GetDlgItem(IDC_EDIT_Q_VALUE);			pQValueEdit->SetWindowText(_T(""));
			CEdit* pMaxQueryCntEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_QUERY_REPS);					pMaxQueryCntEdit->SetWindowText(_T(""));
			CEdit* pThresholdMultiplierEdit = (CEdit*)GetDlgItem(IDC_EDIT_THRESHOLD_MULTIPLIER);	pThresholdMultiplierEdit->SetWindowText(_T(""));

			pStartQEdit->EnableWindow(TRUE);
			pMinQEdit->EnableWindow(TRUE);
			pMaxQEdit->EnableWindow(TRUE);
			pRetryEdit->EnableWindow(TRUE);
			pQValueEdit->EnableWindow(FALSE);
			pMaxQueryCntEdit->EnableWindow(FALSE);
			pThresholdMultiplierEdit->EnableWindow(FALSE);

			m_ctrlSpinButtonCtrlStartQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMinQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMaxQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlRetryCount.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlQValue.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlMaxQueryReps.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlThresholdMultiplier.EnableWindow(FALSE);

			m_ctrlComboToggleTarget.EnableWindow(TRUE);
			m_ctrlComboRepeatUntilNoTags.EnableWindow(FALSE);

			temp.Format(_T("%u"), dynamicq_parms.startQValue);
			pStartQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_parms.maxQValue);
			pMaxQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_parms.minQValue);
			pMinQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_parms.retryCount);
			pRetryEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_parms.maxQueryRepCount);
			pMaxQueryCntEdit->SetWindowText(temp);

			if(dynamicq_parms.toggleTarget == 0)
				m_ctrlComboToggleTarget.SetCurSel(0);
			else
				m_ctrlComboToggleTarget.SetCurSel(1);

			break;
		}
	case RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ_ADJUST:
		{
			RFID_18K6C_SINGULATION_DYNAMICQ_ADJUST_PARMS dynamicq_adjust_parms = parms.singulationParms.parameters.dynamicQAdjust;
			CString	temp;	

			CEdit* pStartQEdit = (CEdit*)GetDlgItem(IDC_EDIT_START_Q);			pStartQEdit->SetWindowText(_T(""));
			CEdit* pMinQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MIN_Q);				pMinQEdit->SetWindowText(_T(""));
			CEdit* pMaxQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_Q);				pMaxQEdit->SetWindowText(_T(""));
			CEdit* pRetryEdit = (CEdit*)GetDlgItem(IDC_EDIT_RETRY_COUNT);		pRetryEdit->SetWindowText(_T(""));
			CEdit* pQValueEdit = (CEdit*)GetDlgItem(IDC_EDIT_Q_VALUE);			pQValueEdit->SetWindowText(_T(""));
			CEdit* pMaxQueryCntEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_QUERY_REPS);					pMaxQueryCntEdit->SetWindowText(_T(""));
			CEdit* pThresholdMultiplierEdit = (CEdit*)GetDlgItem(IDC_EDIT_THRESHOLD_MULTIPLIER);	pThresholdMultiplierEdit->SetWindowText(_T(""));

			pStartQEdit->EnableWindow(TRUE);
			pMinQEdit->EnableWindow(TRUE);
			pMaxQEdit->EnableWindow(TRUE);
			pRetryEdit->EnableWindow(TRUE);
			pQValueEdit->EnableWindow(FALSE);
			pMaxQueryCntEdit->EnableWindow(TRUE);
			pThresholdMultiplierEdit->EnableWindow(FALSE);

			m_ctrlSpinButtonCtrlStartQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMinQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMaxQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlRetryCount.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlQValue.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlMaxQueryReps.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlThresholdMultiplier.EnableWindow(FALSE);

			m_ctrlComboToggleTarget.EnableWindow(TRUE);
			m_ctrlComboRepeatUntilNoTags.EnableWindow(FALSE);

			temp.Format(_T("%u"), dynamicq_adjust_parms.startQValue);
			pStartQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_adjust_parms.maxQValue);
			pMaxQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_adjust_parms.minQValue);
			pMinQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_adjust_parms.retryCount);
			pRetryEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_adjust_parms.maxQueryRepCount);
			pMaxQueryCntEdit->SetWindowText(temp);

			if(dynamicq_adjust_parms.toggleTarget)
				m_ctrlComboToggleTarget.SetCurSel(0);
			else
				m_ctrlComboToggleTarget.SetCurSel(1);

			break;	
		}
	case RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ_THRESH:
		{
			RFID_18K6C_SINGULATION_DYNAMICQ_THRESH_PARMS dynamicq_thresh_parms = parms.singulationParms.parameters.dynamicQThresh;
			CString	temp;	

			CEdit* pStartQEdit = (CEdit*)GetDlgItem(IDC_EDIT_START_Q);			pStartQEdit->SetWindowText(_T(""));
			CEdit* pMinQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MIN_Q);				pMinQEdit->SetWindowText(_T(""));
			CEdit* pMaxQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_Q);				pMaxQEdit->SetWindowText(_T(""));
			CEdit* pRetryEdit = (CEdit*)GetDlgItem(IDC_EDIT_RETRY_COUNT);		pRetryEdit->SetWindowText(_T(""));
			CEdit* pQValueEdit = (CEdit*)GetDlgItem(IDC_EDIT_Q_VALUE);			pQValueEdit->SetWindowText(_T(""));
			CEdit* pMaxQueryCntEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_QUERY_REPS);					pMaxQueryCntEdit->SetWindowText(_T(""));
			CEdit* pThresholdMultiplierEdit = (CEdit*)GetDlgItem(IDC_EDIT_THRESHOLD_MULTIPLIER);	pThresholdMultiplierEdit->SetWindowText(_T(""));


			pStartQEdit->EnableWindow(TRUE);
			pMinQEdit->EnableWindow(TRUE);
			pMaxQEdit->EnableWindow(TRUE);
			pRetryEdit->EnableWindow(TRUE);
			pQValueEdit->EnableWindow(FALSE);
			pMaxQueryCntEdit->EnableWindow(FALSE);
			pThresholdMultiplierEdit->EnableWindow(TRUE);

			m_ctrlSpinButtonCtrlStartQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMinQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMaxQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlRetryCount.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlQValue.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlMaxQueryReps.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlThresholdMultiplier.EnableWindow(TRUE);

			m_ctrlComboToggleTarget.EnableWindow(TRUE);
			m_ctrlComboRepeatUntilNoTags.EnableWindow(FALSE);


			temp.Format(_T("%u"), dynamicq_thresh_parms.startQValue);
			pStartQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_thresh_parms.maxQValue);
			pMaxQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_thresh_parms.minQValue);
			pMinQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_thresh_parms.retryCount);
			pRetryEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_thresh_parms.thresholdMultiplier);
			pThresholdMultiplierEdit->SetWindowText(temp);

			if(dynamicq_thresh_parms.toggleTarget == 0)
				m_ctrlComboToggleTarget.SetCurSel(0);
			else
				m_ctrlComboToggleTarget.SetCurSel(1);

			break;
		}
	default:
		break;
	}


	/////////////////////////////////////////////////////////////////////////////
	// Region
	/////////////////////////////////////////////////////////////////////////////
	RFID_18K6C_SINGULATION_ALGORITHM	algorithm;
	pFrame->GetRFIDRadioManager()->GetRadio18K6CCurrentSingulationAlgorithm(0, &algorithm);

	switch(algorithm)
	{
	case RFID_18K6C_SINGULATION_ALGORITHM_FIXEDQ:
		m_ctrlComboAlgorithm.SetCurSel(0);
		break;
	case RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ:
		m_ctrlComboAlgorithm.SetCurSel(1);
		break;
	case RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ_ADJUST:
		m_ctrlComboAlgorithm.SetCurSel(2);
		break;
	case RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ_THRESH:
		m_ctrlComboAlgorithm.SetCurSel(3);
		break;
	default:
		m_ctrlComboAlgorithm.SetCurSel(4);
		break;
	}

	RFID_18K6C_TAG_GROUP	tagGroup;
	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryTagGroup(0, &tagGroup);

	switch(tagGroup.selected)
	{
	case RFID_18K6C_SELECTED_ALL:
		m_ctrlComboSelectState.SetCurSel(0);
		break;
	case RFID_18K6C_SELECTED_OFF:
		m_ctrlComboSelectState.SetCurSel(1);
		break;
	case RFID_18K6C_SELECTED_ON:
		m_ctrlComboSelectState.SetCurSel(2);
		break;
	default:
		m_ctrlComboSelectState.SetCurSel(3);
		break;
	}

	switch(tagGroup.session)
	{
	case RFID_18K6C_INVENTORY_SESSION_S0:
		m_ctrlComboSelectSession.SetCurSel(0);
		break;
	case RFID_18K6C_INVENTORY_SESSION_S1:
		m_ctrlComboSelectSession.SetCurSel(1);
		break;
	case RFID_18K6C_INVENTORY_SESSION_S2:
		m_ctrlComboSelectSession.SetCurSel(2);
		break;
	case RFID_18K6C_INVENTORY_SESSION_S3:
		m_ctrlComboSelectSession.SetCurSel(3);
		break;
	default:
		m_ctrlComboSelectSession.SetCurSel(4);
		break;
	}

	switch(tagGroup.target)
	{
	case RFID_18K6C_INVENTORY_SESSION_TARGET_A:
		m_ctrlComboSelectSessionTarget.SetCurSel(0);
		break;
	case RFID_18K6C_INVENTORY_SESSION_TARGET_B:
		m_ctrlComboSelectSessionTarget.SetCurSel(1);
		break;
	default:
		m_ctrlComboSelectSessionTarget.SetCurSel(2);
		break;
	}

	theApp.DoWaitCursor(-1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAlgorithmSetPage::OnCbnSelchangeComboAlgorithm()
{
	int flag = m_ctrlComboAlgorithm.GetCurSel();
	RFID_18K6C_QUERY_PARMS	parms;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryParameters(0, &parms);

	switch(flag)
	{
	case 0:
		{
			pFrame->GetRFIDRadioManager()->SetRadio18K6CCurrentSingulationAlgorithm(0, 
				RFID_18K6C_SINGULATION_ALGORITHM_FIXEDQ);

			RFID_18K6C_SINGULATION_FIXEDQ_PARMS fixedq_parms = parms.singulationParms.parameters.fixedQ;
			CString	temp;

			CEdit* pStartQEdit = (CEdit*)GetDlgItem(IDC_EDIT_START_Q);			pStartQEdit->SetWindowText(_T(""));
			CEdit* pMinQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MIN_Q);				pMinQEdit->SetWindowText(_T(""));
			CEdit* pMaxQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_Q);				pMaxQEdit->SetWindowText(_T(""));
			CEdit* pRetryEdit = (CEdit*)GetDlgItem(IDC_EDIT_RETRY_COUNT);		pRetryEdit->SetWindowText(_T(""));
			CEdit* pQValueEdit = (CEdit*)GetDlgItem(IDC_EDIT_Q_VALUE);			pQValueEdit->SetWindowText(_T(""));
			CEdit* pMaxQueryCntEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_QUERY_REPS);					pMaxQueryCntEdit->SetWindowText(_T(""));
			CEdit* pThresholdMultiplierEdit = (CEdit*)GetDlgItem(IDC_EDIT_THRESHOLD_MULTIPLIER);	pThresholdMultiplierEdit->SetWindowText(_T(""));

			pStartQEdit->EnableWindow(FALSE);
			pMinQEdit->EnableWindow(FALSE);
			pMaxQEdit->EnableWindow(FALSE);
			pRetryEdit->EnableWindow(TRUE);
			pQValueEdit->EnableWindow(TRUE);
			pMaxQueryCntEdit->EnableWindow(FALSE);
			pThresholdMultiplierEdit->EnableWindow(FALSE);

			m_ctrlSpinButtonCtrlStartQ.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlMinQ.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlMaxQ.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlRetryCount.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlQValue.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMaxQueryReps.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlThresholdMultiplier.EnableWindow(FALSE);

			m_ctrlComboToggleTarget.EnableWindow(TRUE);
			m_ctrlComboRepeatUntilNoTags.EnableWindow(TRUE);

			temp.Format(_T("%u"),fixedq_parms.qValue);
			pQValueEdit->SetWindowText(temp);

			temp.Format(_T("%u"),fixedq_parms.retryCount);
			pRetryEdit->SetWindowText(temp);

			if(fixedq_parms.toggleTarget == 0)
				m_ctrlComboToggleTarget.SetCurSel(0);
			else
				m_ctrlComboToggleTarget.SetCurSel(1);

			if(fixedq_parms.repeatUntilNoTags == 0)
				m_ctrlComboRepeatUntilNoTags.SetCurSel(0);
			else
				m_ctrlComboRepeatUntilNoTags.SetCurSel(1);


			break;
		}
	case 1:
		{
			pFrame->GetRFIDRadioManager()->SetRadio18K6CCurrentSingulationAlgorithm(0, 
				RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ);

			RFID_18K6C_SINGULATION_DYNAMICQ_PARMS dynamicq_parms = parms.singulationParms.parameters.dynamicQ;
			CString	temp;	

			CEdit* pStartQEdit = (CEdit*)GetDlgItem(IDC_EDIT_START_Q);			pStartQEdit->SetWindowText(_T(""));
			CEdit* pMinQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MIN_Q);				pMinQEdit->SetWindowText(_T(""));
			CEdit* pMaxQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_Q);				pMaxQEdit->SetWindowText(_T(""));
			CEdit* pRetryEdit = (CEdit*)GetDlgItem(IDC_EDIT_RETRY_COUNT);		pRetryEdit->SetWindowText(_T(""));
			CEdit* pQValueEdit = (CEdit*)GetDlgItem(IDC_EDIT_Q_VALUE);			pQValueEdit->SetWindowText(_T(""));
			CEdit* pMaxQueryCntEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_QUERY_REPS);					pMaxQueryCntEdit->SetWindowText(_T(""));
			CEdit* pThresholdMultiplierEdit = (CEdit*)GetDlgItem(IDC_EDIT_THRESHOLD_MULTIPLIER);	pThresholdMultiplierEdit->SetWindowText(_T(""));

			pStartQEdit->EnableWindow(TRUE);
			pMinQEdit->EnableWindow(TRUE);
			pMaxQEdit->EnableWindow(TRUE);
			pRetryEdit->EnableWindow(TRUE);
			pQValueEdit->EnableWindow(FALSE);
			pMaxQueryCntEdit->EnableWindow(TRUE);
			pThresholdMultiplierEdit->EnableWindow(FALSE);

			m_ctrlSpinButtonCtrlStartQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMinQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMaxQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlRetryCount.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlQValue.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlMaxQueryReps.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlThresholdMultiplier.EnableWindow(FALSE);

			m_ctrlComboToggleTarget.EnableWindow(TRUE);
			m_ctrlComboRepeatUntilNoTags.EnableWindow(FALSE);


			temp.Format(_T("%u"), dynamicq_parms.startQValue);
			pStartQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_parms.maxQValue);
			pMaxQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_parms.minQValue);
			pMinQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_parms.retryCount);
			pRetryEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_parms.maxQueryRepCount);
			pMaxQueryCntEdit->SetWindowText(temp);

			if(dynamicq_parms.toggleTarget == 0)
				m_ctrlComboToggleTarget.SetCurSel(0);
			else
				m_ctrlComboToggleTarget.SetCurSel(1);

			break;	
		}
	case 2:
		{
			pFrame->GetRFIDRadioManager()->SetRadio18K6CCurrentSingulationAlgorithm(0, 
				RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ_ADJUST);

			RFID_18K6C_SINGULATION_DYNAMICQ_ADJUST_PARMS dynamicq_adjust_parms = parms.singulationParms.parameters.dynamicQAdjust;
			CString	temp;	

			CEdit* pStartQEdit = (CEdit*)GetDlgItem(IDC_EDIT_START_Q);			pStartQEdit->SetWindowText(_T(""));
			CEdit* pMinQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MIN_Q);				pMinQEdit->SetWindowText(_T(""));
			CEdit* pMaxQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_Q);				pMaxQEdit->SetWindowText(_T(""));
			CEdit* pRetryEdit = (CEdit*)GetDlgItem(IDC_EDIT_RETRY_COUNT);		pRetryEdit->SetWindowText(_T(""));
			CEdit* pQValueEdit = (CEdit*)GetDlgItem(IDC_EDIT_Q_VALUE);			pQValueEdit->SetWindowText(_T(""));
			CEdit* pMaxQueryCntEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_QUERY_REPS);					pMaxQueryCntEdit->SetWindowText(_T(""));
			CEdit* pThresholdMultiplierEdit = (CEdit*)GetDlgItem(IDC_EDIT_THRESHOLD_MULTIPLIER);	pThresholdMultiplierEdit->SetWindowText(_T(""));

			pStartQEdit->EnableWindow(TRUE);
			pMinQEdit->EnableWindow(TRUE);
			pMaxQEdit->EnableWindow(TRUE);
			pRetryEdit->EnableWindow(TRUE);
			pQValueEdit->EnableWindow(FALSE);
			pMaxQueryCntEdit->EnableWindow(TRUE);
			pThresholdMultiplierEdit->EnableWindow(FALSE);

			m_ctrlSpinButtonCtrlStartQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMinQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMaxQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlRetryCount.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlQValue.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlMaxQueryReps.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlThresholdMultiplier.EnableWindow(FALSE);

			m_ctrlComboToggleTarget.EnableWindow(TRUE);
			m_ctrlComboRepeatUntilNoTags.EnableWindow(FALSE);

			temp.Format(_T("%u"), dynamicq_adjust_parms.startQValue);
			pStartQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_adjust_parms.maxQValue);
			pMaxQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_adjust_parms.minQValue);
			pMinQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_adjust_parms.retryCount);
			pRetryEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_adjust_parms.maxQueryRepCount);
			pMaxQueryCntEdit->SetWindowText(temp);

			if(dynamicq_adjust_parms.toggleTarget == 0)
				m_ctrlComboToggleTarget.SetCurSel(0);
			else
				m_ctrlComboToggleTarget.SetCurSel(1);

			break;	
		}
	case 3:
		{
			pFrame->GetRFIDRadioManager()->SetRadio18K6CCurrentSingulationAlgorithm(0, 
				RFID_18K6C_SINGULATION_ALGORITHM_DYNAMICQ_THRESH);

			RFID_18K6C_SINGULATION_DYNAMICQ_THRESH_PARMS dynamicq_thresh_parms = parms.singulationParms.parameters.dynamicQThresh;
			CString	temp;	

			CEdit* pStartQEdit = (CEdit*)GetDlgItem(IDC_EDIT_START_Q);			pStartQEdit->SetWindowText(_T(""));
			CEdit* pMinQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MIN_Q);				pMinQEdit->SetWindowText(_T(""));
			CEdit* pMaxQEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_Q);				pMaxQEdit->SetWindowText(_T(""));
			CEdit* pRetryEdit = (CEdit*)GetDlgItem(IDC_EDIT_RETRY_COUNT);		pRetryEdit->SetWindowText(_T(""));
			CEdit* pQValueEdit = (CEdit*)GetDlgItem(IDC_EDIT_Q_VALUE);			pQValueEdit->SetWindowText(_T(""));
			CEdit* pMaxQueryCntEdit = (CEdit*)GetDlgItem(IDC_EDIT_MAX_QUERY_REPS);					pMaxQueryCntEdit->SetWindowText(_T(""));
			CEdit* pThresholdMultiplierEdit = (CEdit*)GetDlgItem(IDC_EDIT_THRESHOLD_MULTIPLIER);	pThresholdMultiplierEdit->SetWindowText(_T(""));

			pStartQEdit->EnableWindow(TRUE);
			pMinQEdit->EnableWindow(TRUE);
			pMaxQEdit->EnableWindow(TRUE);
			pRetryEdit->EnableWindow(TRUE);
			pQValueEdit->EnableWindow(FALSE);
			pMaxQueryCntEdit->EnableWindow(FALSE);
			pThresholdMultiplierEdit->EnableWindow(TRUE);

			m_ctrlSpinButtonCtrlStartQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMinQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlMaxQ.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlRetryCount.EnableWindow(TRUE);
			m_ctrlSpinButtonCtrlQValue.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlMaxQueryReps.EnableWindow(FALSE);
			m_ctrlSpinButtonCtrlThresholdMultiplier.EnableWindow(TRUE);

			m_ctrlComboToggleTarget.EnableWindow(TRUE);
			m_ctrlComboRepeatUntilNoTags.EnableWindow(FALSE);

			temp.Format(_T("%u"), dynamicq_thresh_parms.startQValue);
			pStartQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_thresh_parms.maxQValue);
			pMaxQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_thresh_parms.minQValue);
			pMinQEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_thresh_parms.retryCount);
			pRetryEdit->SetWindowText(temp);

			temp.Format(_T("%u"), dynamicq_thresh_parms.thresholdMultiplier);
			pThresholdMultiplierEdit->SetWindowText(temp);

			if(dynamicq_thresh_parms.toggleTarget == 0)
				m_ctrlComboToggleTarget.SetCurSel(0);
			else
				m_ctrlComboToggleTarget.SetCurSel(1);

			break;
		}
	default:
		pFrame->GetRFIDRadioManager()->SetRadio18K6CCurrentSingulationAlgorithm(0, 
			RFID_18K6C_SINGULATION_ALGORITHM_FIXEDQ - 1);
		break;
	}
}

void CAlgorithmSetPage::OnSize(UINT nType, int cx, int cy)
{
	CPropertyPage::OnSize(nType, cx, cy);

	//	m_nCurHeight = cy;

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
//	si.fMask = SIF_ALL; 
	si.nMin = 0;
	si.nMax = m_rcOriginalRect.Height();
	si.nPage = cy;
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si, TRUE); 	

}

void CAlgorithmSetPage::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nDelta;
	int nMaxPos = m_rcOriginalRect.Height();// - m_nCurHeight;

	UINT id = pScrollBar->GetDlgCtrlID();

	if(id != IDC_SCROLLBAR_ALGORITHM)
	{
		switch (nSBCode)
		{
		case SB_LINEDOWN:
			if (m_nScrollPos >= nMaxPos)
				return;

			nDelta = min(max(nMaxPos/20,5),nMaxPos-m_nScrollPos);
			break;

		case SB_LINEUP:
			if (m_nScrollPos <= 0)
				return;
			nDelta = -min(max(nMaxPos/20,5),m_nScrollPos);
			break;
		case SB_PAGEDOWN:
			if (m_nScrollPos >= nMaxPos)
				return;
			nDelta = min(max(nMaxPos/10,5),nMaxPos-m_nScrollPos);
			break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			nDelta = (int)nPos - m_nScrollPos;
			break;

		case SB_PAGEUP:
			if (m_nScrollPos <= 0)
				return;
			nDelta = -min(max(nMaxPos/10,5),m_nScrollPos);
			break;

		default:
			return;
		}
		m_nScrollPos += nDelta;

		Control_VScroll(-nDelta);
		pScrollBar->SetScrollPos(m_nScrollPos, TRUE);
	}

	CPropertyPage::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CAlgorithmSetPage::Control_VScroll(int interval) 
{
	CWnd * p_Child;
	CRect	rt;
	HDWP h_Dwp;
	UINT id, cnt =0;
	int imsi;

	if(interval)
	{
		h_Dwp = BeginDeferWindowPos(56);
		p_Child = this->GetWindow(GW_CHILD);
		while(p_Child)
		{
			cnt++;
			p_Child->GetWindowRect(&rt);
			ScreenToClient(rt);

			id = p_Child->GetDlgCtrlID();

			if(id != IDC_SCROLLBAR_ALGORITHM)
			{
				imsi = rt.top + interval;
				DeferWindowPos(h_Dwp,p_Child->GetSafeHwnd(),HWND_TOP,rt.left,imsi,0,0,SWP_NOZORDER | SWP_NOSIZE);
			}

			p_Child = p_Child->GetNextWindow(GW_HWNDNEXT);
		}
		EndDeferWindowPos(h_Dwp);
	}
}
void CAlgorithmSetPage::OnCbnSelchangeComboSelectState()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	RFID_18K6C_TAG_GROUP	tagGroup;

	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryTagGroup(0, &tagGroup);

	switch(m_ctrlComboAlgorithm.GetCurSel())
	{
	case 0:
		tagGroup.selected = RFID_18K6C_SELECTED_ALL;
		pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryTagGroup(0, &tagGroup);
		break;
	case 1:
		tagGroup.selected = RFID_18K6C_SELECTED_OFF;
		pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryTagGroup(0, &tagGroup);
		break;
	case 2:
		tagGroup.selected = RFID_18K6C_SELECTED_ON;
		pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryTagGroup(0, &tagGroup);
		break;
	default:
		tagGroup.selected = -1;
		pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryTagGroup(0, &tagGroup);
		break;
	}
}

void CAlgorithmSetPage::OnCbnSelchangeComboSession()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	RFID_18K6C_TAG_GROUP	tagGroup;

	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryTagGroup(0, &tagGroup);

	switch(m_ctrlComboSelectSession.GetCurSel())
	{
	case 0:
		tagGroup.session = RFID_18K6C_INVENTORY_SESSION_S0;
		pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryTagGroup(0, &tagGroup);
		break;
	case 1:
		tagGroup.session = RFID_18K6C_INVENTORY_SESSION_S1;
		pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryTagGroup(0, &tagGroup);
		break;
	case 2:
		tagGroup.session = RFID_18K6C_INVENTORY_SESSION_S2;
		pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryTagGroup(0, &tagGroup);
		break;
	case 3:
		tagGroup.session = RFID_18K6C_INVENTORY_SESSION_S3;
		pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryTagGroup(0, &tagGroup);
		break;
	default:
		tagGroup.session = -1;
		pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryTagGroup(0, &tagGroup);
		break;
	}
}

void CAlgorithmSetPage::OnCbnSelchangeComboSessionTarget()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	RFID_18K6C_TAG_GROUP	tagGroup;

	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryTagGroup(0, &tagGroup);

	switch(m_ctrlComboSelectSessionTarget.GetCurSel())
	{
	case 0:
		tagGroup.target = RFID_18K6C_INVENTORY_SESSION_TARGET_A;
		pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryTagGroup(0, &tagGroup);
		break;
	case 1:
		tagGroup.target = RFID_18K6C_INVENTORY_SESSION_TARGET_B;
		pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryTagGroup(0, &tagGroup);
		break;
	default:
		tagGroup.target = -1;
		pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryTagGroup(0, &tagGroup);
		break;
	}
}

void CAlgorithmSetPage::OnEnChangeEditStartQ()
{
	int flag = m_ctrlComboAlgorithm.GetCurSel();
	RFID_18K6C_QUERY_PARMS	parms;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryParameters(0, &parms);

	switch(flag)
	{
	case 0:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));
			break;
		}
	case 1:
		{

			parms.singulationParms.parameters.dynamicQ.startQValue = GetDlgItemInt(IDC_EDIT_START_Q);

			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;	
		}
	case 2:
		{

			parms.singulationParms.parameters.dynamicQAdjust.startQValue = GetDlgItemInt(IDC_EDIT_START_Q);

			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;	
		}
	case 3:
		{
			parms.singulationParms.parameters.dynamicQThresh.startQValue = GetDlgItemInt(IDC_EDIT_START_Q);

			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;
		}
	default:
		break;
	}
}

void CAlgorithmSetPage::OnEnChangeEditMinQ()
{
	int flag = m_ctrlComboAlgorithm.GetCurSel();
	RFID_18K6C_QUERY_PARMS	parms;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryParameters(0, &parms);

	switch(flag)
	{
	case 0:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));
			break;
		}
	case 1:
		{

			parms.singulationParms.parameters.dynamicQ.minQValue = GetDlgItemInt(IDC_EDIT_MIN_Q);

			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;	
		}
	case 2:
		{

			parms.singulationParms.parameters.dynamicQAdjust.minQValue = GetDlgItemInt(IDC_EDIT_MIN_Q);

			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;	
		}
	case 3:
		{
			parms.singulationParms.parameters.dynamicQThresh.minQValue = GetDlgItemInt(IDC_EDIT_MIN_Q);

			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;
		}
	default:
		break;
	}
}

void CAlgorithmSetPage::OnEnChangeEditMaxQ()
{
	int flag = m_ctrlComboAlgorithm.GetCurSel();
	RFID_18K6C_QUERY_PARMS	parms;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryParameters(0, &parms);

	switch(flag)
	{
	case 0:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));
			break;
		}
	case 1:
		{

			parms.singulationParms.parameters.dynamicQ.maxQValue = GetDlgItemInt(IDC_EDIT_MAX_Q);

			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;	
		}
	case 2:
		{
			parms.singulationParms.parameters.dynamicQAdjust.maxQValue = GetDlgItemInt(IDC_EDIT_MAX_Q);

			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;	
		}
	case 3:
		{

			parms.singulationParms.parameters.dynamicQThresh.maxQValue = GetDlgItemInt(IDC_EDIT_MAX_Q);

			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;
		}
	default:
		break;
	}
}

void CAlgorithmSetPage::OnEnChangeEditRetryCount()
{
	int flag = m_ctrlComboAlgorithm.GetCurSel();
	RFID_18K6C_QUERY_PARMS	parms;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryParameters(0, &parms);

	switch(flag)
	{
	case 0:
		{
			parms.singulationParms.parameters.fixedQ.retryCount = GetDlgItemInt(IDC_EDIT_RETRY_COUNT);
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;
		}
	case 1:
		{
			parms.singulationParms.parameters.dynamicQ.retryCount = GetDlgItemInt(IDC_EDIT_RETRY_COUNT);
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;	
		}
	case 2:
		{
			parms.singulationParms.parameters.dynamicQAdjust.retryCount = GetDlgItemInt(IDC_EDIT_RETRY_COUNT);
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;	
		}
	case 3:
		{
			parms.singulationParms.parameters.dynamicQThresh.retryCount = GetDlgItemInt(IDC_EDIT_RETRY_COUNT);
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;
		}
	default:
		break;
	}
}

void CAlgorithmSetPage::OnCbnSelchangeComboToggleTarget()
{
	int flag = m_ctrlComboAlgorithm.GetCurSel();
	RFID_18K6C_QUERY_PARMS	parms;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryParameters(0, &parms);

	switch(flag)
	{
	case 0:
		{
			parms.singulationParms.parameters.fixedQ.toggleTarget = m_ctrlComboToggleTarget.GetCurSel();
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;
		}
	case 1:
		{
			parms.singulationParms.parameters.dynamicQ.toggleTarget = m_ctrlComboToggleTarget.GetCurSel();
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;	
		}
	case 2:
		{
			parms.singulationParms.parameters.dynamicQAdjust.toggleTarget = m_ctrlComboToggleTarget.GetCurSel();
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;	
		}
	case 3:
		{
			parms.singulationParms.parameters.dynamicQThresh.toggleTarget = m_ctrlComboToggleTarget.GetCurSel();
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;
		}
	default:
		break;
	}
}

void CAlgorithmSetPage::OnEnChangeEditQValue()
{
	int flag = m_ctrlComboAlgorithm.GetCurSel();
	RFID_18K6C_QUERY_PARMS	parms;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryParameters(0, &parms);

	switch(flag)
	{
	case 0:
		{
			parms.singulationParms.parameters.fixedQ.qValue = GetDlgItemInt(IDC_EDIT_Q_VALUE);
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;
		}
	case 1:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));
			break;	
		}
	case 2:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));

			break;	
		}
	case 3:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));

			break;
		}
	default:
		break;
	}
}

void CAlgorithmSetPage::OnEnChangeEditMaxQueryReps()
{
	int flag = m_ctrlComboAlgorithm.GetCurSel();
	RFID_18K6C_QUERY_PARMS	parms;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryParameters(0, &parms);

	switch(flag)
	{
	case 0:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));

			break;
		}
	case 1:
		{
			parms.singulationParms.parameters.dynamicQ.maxQueryRepCount = GetDlgItemInt(IDC_EDIT_MAX_QUERY_REPS);
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;	
		}
	case 2:
		{
			parms.singulationParms.parameters.dynamicQAdjust.maxQueryRepCount = GetDlgItemInt(IDC_EDIT_MAX_QUERY_REPS);
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;	
		}
	case 3:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));
			
			break;
		}
	default:
		break;
	}
}

void CAlgorithmSetPage::OnEnChangeEditThresholdMultiplier()
{
	int flag = m_ctrlComboAlgorithm.GetCurSel();
	RFID_18K6C_QUERY_PARMS	parms;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryParameters(0, &parms);

	switch(flag)
	{
	case 0:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));

			break;
		}
	case 1:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));

			break;	
		}
	case 2:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));

			break;	
		}
	case 3:
		{
			parms.singulationParms.parameters.dynamicQThresh.thresholdMultiplier = GetDlgItemInt(IDC_EDIT_THRESHOLD_MULTIPLIER);
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;
		}
	default:
		break;
	}
}

void CAlgorithmSetPage::OnCbnSelchangeComboRepeteUntileNoTags()
{
	int flag = m_ctrlComboAlgorithm.GetCurSel();
	RFID_18K6C_QUERY_PARMS	parms;

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	pFrame->GetRFIDRadioManager()->GetRadio18K6CQueryParameters(0, &parms);

	switch(flag)
	{
	case 0:
		{
			parms.singulationParms.parameters.fixedQ.repeatUntilNoTags = m_ctrlComboRepeatUntilNoTags.GetCurSel();
			pFrame->GetRFIDRadioManager()->SetRadio18K6CQueryParameters(0, &parms);

			break;
		}
	case 1:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));
			break;	
		}
	case 2:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));
			break;	
		}
	case 3:
		{
//			AfxMessageBox(_T("This Option does change on this Algorithm"));
			break;
		}
	default:
		break;
	}
}
