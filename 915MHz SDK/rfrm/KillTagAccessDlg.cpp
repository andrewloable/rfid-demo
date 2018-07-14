// ../KillTagAccessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "KillTagAccessDlg.h"
#include "Util.h"


// CKillTagAccessDlg dialog

IMPLEMENT_DYNAMIC(CKillTagAccessDlg, CDialog)

CKillTagAccessDlg::CKillTagAccessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKillTagAccessDlg::IDD, pParent)
{

}

CKillTagAccessDlg::~CKillTagAccessDlg()
{
}

void CKillTagAccessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_EPC, m_editEPC);   
	DDX_Control(pDX, IDC_EDIT_ACCESS_PASSWORD, m_editAccessPassword);
	DDX_Control(pDX, IDC_EDIT_KILL_PASSWORD, m_editKillPassword);
}


BEGIN_MESSAGE_MAP(CKillTagAccessDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CKillTagAccessDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CKillTagAccessDlg message handlers

// CKillTagAccessDlg message handlers
void CKillTagAccessDlg::SetSelectedTag(CTagInfo* pTag)
{
	ASSERT(pTag);
	m_tagInfo = pTag;
}

BOOL CKillTagAccessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	CString strAccessPassword, strKillPassword;

	if(m_tagInfo != NULL)
		m_editEPC.SetWindowText(m_tagInfo->GetTagString());

	strAccessPassword.Format(TEXT("%.8x"), theApp.GetProfileInt(TEXT("TagAccess"), TEXT("AccessPassword"), 0));
	m_editAccessPassword.SetWindowText(strAccessPassword);

	strKillPassword.Format(TEXT("%.8x"), theApp.GetProfileInt(TEXT("TagAccess"), TEXT("KillPassword"), 0));
	m_editKillPassword.SetWindowText(strKillPassword);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CKillTagAccessDlg::OnBnClickedOk()
{
	CUtil util;
	CString strTemp1, strTemp2;

	UpdateData(TRUE);

	// EPC Data
	m_editEPC.GetWindowText(m_strEPC);

	theApp.WriteProfileString(TEXT("TagAccess"), TEXT("EPC"), m_strEPC);

	m_editAccessPassword.GetWindowText(strTemp1);
	m_editKillPassword.GetWindowText(strTemp2);

	//	DWORD address = (DWORD) strTemp.GetBuffer(strTemp.GetLength());
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("AccessPassword"), util.StrToWord(strTemp1));
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("KillPassword"), util.StrToWord(strTemp2));

	UpdateData(FALSE);

	OnOK();
}
