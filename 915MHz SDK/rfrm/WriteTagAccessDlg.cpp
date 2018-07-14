// ..\WriteTagAccessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "WriteTagAccessDlg.h"


// CWriteTagAccessDlg dialog

IMPLEMENT_DYNAMIC(CWriteTagAccessDlg, CDialog)

CWriteTagAccessDlg::CWriteTagAccessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWriteTagAccessDlg::IDD, pParent)
	, m_tagInfo(NULL)
{

}

CWriteTagAccessDlg::~CWriteTagAccessDlg()
{
}

void CWriteTagAccessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_EPC, m_editEPC);   
	DDX_Control(pDX, IDC_COMBO_MBANK, m_comboMBank);
	DDX_Control(pDX, IDC_COMBO_OFFSET, m_comboOffset);
	DDX_Control(pDX, IDC_COMBO_COUNT, m_comboCount);
	DDX_Control(pDX, IDC_EDIT_WRITE_DATA, m_editWriteData);
}


BEGIN_MESSAGE_MAP(CWriteTagAccessDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_OFFSET, &CWriteTagAccessDlg::OnCbnSelchangeComboOffset)
	ON_BN_CLICKED(IDOK, &CWriteTagAccessDlg::OnBnClickedOk)
/*	ON_CBN_SELCHANGE(IDC_COMBO_COUNT, &CWriteTagAccessDlg::OnCbnSelchangeComboCount)*/
END_MESSAGE_MAP()


// CWriteTagAccessDlg message handlers
void CWriteTagAccessDlg::SetSelectedTag(CTagInfo* pTag)
{
	m_tagInfo = pTag;
}

BOOL CWriteTagAccessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString str;

	if(m_tagInfo != NULL)
		m_editEPC.SetWindowText(m_tagInfo->GetTagString());
/*
	else if(!theApp.GetProfileString(TEXT("TagAccess"), TEXT("EPC")).IsEmpty())
		m_editEPC.SetWindowText(theApp.GetProfileString(TEXT("TagAccess"), TEXT("EPC")));
*/
	m_comboMBank.SetCurSel(theApp.GetProfileInt(TEXT("TagAccess"), TEXT("Bank"), 0));
	m_comboOffset.SetCurSel(theApp.GetProfileInt(TEXT("TagAccess"), TEXT("Offset"), 0));
	m_comboCount.SetCurSel(theApp.GetProfileInt(TEXT("TagAccess"), TEXT("Count"), 0) - 1);
	m_editWriteData.SetWindowText(theApp.GetProfileString(TEXT("TagAccess"), TEXT("Data")));

//	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CWriteTagAccessDlg::OnCbnSelchangeComboOffset()
{
	CString strOffset, strCount;
	m_comboOffset.GetWindowText(strOffset);
	m_comboCount.GetWindowText(strCount);

	int nOffset = _ttoi(strOffset);
	int nCount = _ttoi(strCount);

	m_comboCount.ResetContent();

	for(int i = 0; i < (18 - nOffset) ; i++)
	{
		CString temp;
		temp.Format(_T("%d"), i + 1);

		m_comboCount.AddString(temp);
	}

	m_comboCount.SetCurSel(0);
}

void CWriteTagAccessDlg::OnBnClickedOk()
{
	CString strOffset, strCount;

	m_comboOffset.GetWindowText(strOffset);
	m_comboCount.GetWindowText(strCount);

	m_editEPC.GetWindowText(m_strEPC);
	m_nComboMBank = m_comboMBank.GetCurSel();
	m_nComboOffset = _ttoi(strOffset);
	m_nComboCount = _ttoi(strCount);
	m_editWriteData.GetWindowText(m_strData);

	theApp.WriteProfileString(TEXT("TagAccess"), TEXT("EPC"), m_strEPC);
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("Bank"), m_nComboMBank);
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("Offset"), m_nComboOffset);
	theApp.WriteProfileInt(TEXT("TagAccess"), TEXT("Count"), m_nComboCount);
	theApp.WriteProfileString(TEXT("TagAccess"), TEXT("Data"), m_strData);

	int iLength = m_strData.GetLength();
	if(iLength == 0 || iLength % 4)
	{
		AfxMessageBox(_T("Check Data, Please"));
		return;
	}

	int iDataCount = iLength / 4;

	if((__int64)iDataCount != m_nComboCount)
	{
		AfxMessageBox(_T("Check Compare to WordCount And DataLength, Please"));
		return;
	}

	OnOK();
}