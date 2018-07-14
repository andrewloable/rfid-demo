// ReadTagAccessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "ReadTagAccessDlg.h"


// CReadTagAccessDlg dialog

IMPLEMENT_DYNAMIC(CReadTagAccessDlg, CDialog)

CReadTagAccessDlg::CReadTagAccessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadTagAccessDlg::IDD, pParent)
	, m_tagInfo(NULL)
	, m_strEPC(TEXT(""))
	, m_nComboCount(0)
	, m_nComboOffset(0)
{

}

CReadTagAccessDlg::~CReadTagAccessDlg()
{
}

void CReadTagAccessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_EPC, m_editEPC);   
	DDX_Control(pDX, IDC_COMBO_MBANK, m_comboMBank);
	DDX_Control(pDX, IDC_COMBO_OFFSET, m_comboOffset);
	DDX_Control(pDX, IDC_COMBO_COUNT, m_comboCount);
}


BEGIN_MESSAGE_MAP(CReadTagAccessDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_OFFSET, &CReadTagAccessDlg::OnCbnSelchangeComboOffset)
	ON_BN_CLICKED(IDOK, &CReadTagAccessDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CReadTagAccessDlg message handlers
void CReadTagAccessDlg::SetSelectedTag(CTagInfo* pTag)
{
	m_tagInfo = pTag;
}

BOOL CReadTagAccessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_tagInfo != NULL)
		m_editEPC.SetWindowText(m_tagInfo->GetTagString());
/*
	else if(!theApp.GetProfileString(TEXT("TagAccess"), TEXT("EPC")).IsEmpty())
		m_editEPC.SetWindowText(theApp.GetProfileString(TEXT("TagAccess"), TEXT("EPC")));
*/	

	m_comboMBank.SetCurSel(theApp.GetProfileInt(TEXT("TagAccess"), TEXT("Bank"), 0));
	m_comboOffset.SetCurSel(theApp.GetProfileInt(TEXT("TagAccess"), TEXT("Offset"), 0));
	m_comboCount.SetCurSel(theApp.GetProfileInt(TEXT("TagAccess"), TEXT("Count"), 0) - 1);

	this->SetFocus();

//	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CReadTagAccessDlg::OnCbnSelchangeComboOffset()
{
	CString strOffset;
	m_comboOffset.GetWindowText(strOffset);

	int nOffset = _ttoi(strOffset);

	m_comboCount.ResetContent();

	for(int i = 0; i < (18 - nOffset) ; i++)
	{
		CString temp;
		temp.Format(_T("%d"), i + 1);

		m_comboCount.AddString(temp);
	}

	m_comboCount.SetCurSel(0);
}

void CReadTagAccessDlg::OnBnClickedOk()
{
	CString strOffset, strCount;

	m_comboOffset.GetWindowText(strOffset);
	m_comboCount.GetWindowText(strCount);

	// Get Dat from Control
	m_editEPC.GetWindowText(m_strEPC);
	m_nComboMBank = m_comboMBank.GetCurSel();
	m_nComboOffset = _ttoi(strOffset);
	m_nComboCount = _ttoi(strCount);

	// Write Registry
	theApp.WriteProfileString(TEXT("TagAccess"), TEXT("EPC"), m_strEPC);
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("Bank"), m_nComboMBank);
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("Offset"), m_nComboOffset);
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("Count"), m_nComboCount);

	OnOK();
}
