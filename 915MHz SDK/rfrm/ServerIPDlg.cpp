// ../ServerIPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "ServerIPDlg.h"


// CServerIPDlg dialog

IMPLEMENT_DYNAMIC(CServerIPDlg, CDialog)

CServerIPDlg::CServerIPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerIPDlg::IDD, pParent)
	, m_strIPAddress(_T("192.168.1.1"))
{

}

CServerIPDlg::~CServerIPDlg()
{
}

void CServerIPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_IPADDRESS, m_strIPAddress);

}


BEGIN_MESSAGE_MAP(CServerIPDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CServerIPDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CServerIPDlg message handlers

void CServerIPDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
	OnOK();
}
