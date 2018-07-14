// ../FirmwareUpdateOptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "FirmwareUpdateOptionDlg.h"

#include "MainFrm.h"
#include "RFRMDoc.h"


// CFirmwareUpdateOptionDlg dialog

IMPLEMENT_DYNAMIC(CFirmwareUpdateOptionDlg, CDialog)

CFirmwareUpdateOptionDlg::CFirmwareUpdateOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFirmwareUpdateOptionDlg::IDD, pParent)
{

}

CFirmwareUpdateOptionDlg::~CFirmwareUpdateOptionDlg()
{
}

void CFirmwareUpdateOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO_UPDATE_ALL, mode);
}

BEGIN_MESSAGE_MAP(CFirmwareUpdateOptionDlg, CDialog)
	ON_BN_CLICKED(IDC_RADIO_UPDATE_ALL, &CFirmwareUpdateOptionDlg::OnBnClickedRadioUpdateAll)
	ON_BN_CLICKED(IDC_RADIO_TEST_MODE_ONLY, &CFirmwareUpdateOptionDlg::OnBnClickedRadioTestModeOnly)
	ON_BN_CLICKED(IDC_RADIO_SKIP_TEST_MODE, &CFirmwareUpdateOptionDlg::OnBnClickedRadioSkipTestMode)
END_MESSAGE_MAP()


// CFirmwareUpdateOptionDlg message handlers

BOOL CFirmwareUpdateOptionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadState();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CFirmwareUpdateOptionDlg::LoadState()
{
	mode = AfxGetApp()->GetProfileInt(_T("Update"),_T("Option"), 0);
}

void CFirmwareUpdateOptionDlg::SaveState(int mode)
{
	AfxGetApp()->WriteProfileInt(_T("Update"),_T("Option"), mode);
}

void CFirmwareUpdateOptionDlg::OnOK()
{
//	UpdateData(TRUE);

	SaveState(mode);

	CDialog::OnOK();
}

void CFirmwareUpdateOptionDlg::OnBnClickedRadioUpdateAll()
{
	mode = 0;

//	UpdateData(FALSE);
}

void CFirmwareUpdateOptionDlg::OnBnClickedRadioTestModeOnly()
{
	mode = 1;

//	UpdateData(FALSE);
}

void CFirmwareUpdateOptionDlg::OnBnClickedRadioSkipTestMode()
{
	mode = 2;

//	UpdateData(FALSE);
}
