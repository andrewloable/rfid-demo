// ../LockTagAccessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "LockTagAccessDlg.h"

#include "Util.h"


// CLockTagAccessDlg dialog

IMPLEMENT_DYNAMIC(CLockTagAccessDlg, CDialog)

CLockTagAccessDlg::CLockTagAccessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLockTagAccessDlg::IDD, pParent)
	, m_tagInfo(NULL)
{

}

CLockTagAccessDlg::~CLockTagAccessDlg()
{
}

void CLockTagAccessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_EPC, m_editEPC);   
	DDX_Control(pDX, IDC_COMBO_KILL_PASSWORD_PERMISSION, m_comboKillPasswordPermission);
	DDX_Control(pDX, IDC_COMBO_ACCESS_PASSWORD_PERMISSION, m_comboAccessPasswordPermission);
	DDX_Control(pDX, IDC_COMBO_EPC_BANK_PERMISSION, m_comboEPCBankPermission);
	DDX_Control(pDX, IDC_COMBO_TID_BANK_PERMISSION, m_comboTIDBankPermission);
	DDX_Control(pDX, IDC_COMBO_USER_BANK_PERMISSION, m_comboUserBankPermission);
	DDX_Control(pDX, IDC_EDIT_ACCESS_PASSWORD, m_editAccessPassword);

}


BEGIN_MESSAGE_MAP(CLockTagAccessDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CLockTagAccessDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLockTagAccessDlg message handlers

void CLockTagAccessDlg::SetSelectedTag(CTagInfo* pTag)
{
	ASSERT(pTag);
	m_tagInfo = pTag;
}

BOOL CLockTagAccessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strAccessPassword;

	if(m_tagInfo != NULL)
		m_editEPC.SetWindowText(m_tagInfo->GetTagString());

	m_comboKillPasswordPermission.SetCurSel(theApp.GetProfileInt(TEXT("TagAccess"), TEXT("KillPasswordPermission"), 0));
	m_comboAccessPasswordPermission.SetCurSel(theApp.GetProfileInt(TEXT("TagAccess"), TEXT("AccessPasswordPermission"), 0));
	m_comboEPCBankPermission.SetCurSel(theApp.GetProfileInt(TEXT("TagAccess"), TEXT("EPCMemoryBankPermission"), 0));
	m_comboTIDBankPermission.SetCurSel(theApp.GetProfileInt(TEXT("TagAccess"), TEXT("TIDMemoryBankPermission"), 0));
	m_comboUserBankPermission.SetCurSel(theApp.GetProfileInt(TEXT("TagAccess"), TEXT("UserMemoryBankPermission"), 0));

	strAccessPassword.Format(TEXT("%.8x"), theApp.GetProfileInt(TEXT("TagAccess"), TEXT("AccessPassword"), 0));
	m_editAccessPassword.SetWindowText(strAccessPassword);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CLockTagAccessDlg::OnBnClickedOk()
{
	CUtil util;
	CString strTemp;

	UpdateData(TRUE);

	// EPC Data
	m_editEPC.GetWindowText(m_strEPC);

	theApp.WriteProfileString(TEXT("TagAccess"), TEXT("EPC"), m_strEPC);
	
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("KillPasswordPermission"), m_comboKillPasswordPermission.GetCurSel());
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("AccessPasswordPermission"), m_comboAccessPasswordPermission.GetCurSel());
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("EPCMemoryBankPermission"), m_comboEPCBankPermission.GetCurSel());
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("TIDMemoryBankPermission"), m_comboTIDBankPermission.GetCurSel());
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("UserMemoryBankPermission"), m_comboUserBankPermission.GetCurSel());

	m_editAccessPassword.GetWindowText(strTemp);

//	DWORD address = (DWORD) strTemp.GetBuffer(strTemp.GetLength());
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("AccessPassword"), util.StrToWord(strTemp));

	UpdateData(FALSE);

	OnOK();
}
