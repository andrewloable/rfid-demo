// ../CountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "CountDlg.h"

#ifdef LARGE_COUNT
// CCountDlg dialog

IMPLEMENT_DYNAMIC(CCountDlg, CDialog)

CCountDlg::CCountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCountDlg::IDD, pParent)
{

}

CCountDlg::~CCountDlg()
{
}

void CCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCountDlg, CDialog)
END_MESSAGE_MAP()


// CCountDlg message handlers

BOOL CCountDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	CClientDC dc(this);
	CEdit* pCtlEdit = (CEdit*) GetDlgItem(IDC_EDIT_COUNT_LARGE); // edit control의 

	pCtlEdit->GetWindowRect(&rect);

	int height = dc.GetDeviceCaps(LOGPIXELSY) * 300 / 72; // 9포인트

	_traceLogfont.CreateFont(height, 0, 0, 0, FW_BOLD, 0, 0, 0, 
		DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, 
		CLIP_CHARACTER_PRECIS, 
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial Black"));

	dc.SelectObject(&_traceLogfont);//<==================요게 더들어가욤 
	pCtlEdit->SetFont(&_traceLogfont, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCountDlg::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}

void CCountDlg::SetCount(LPCTSTR count)
{
	CEdit* pCtlEdit = (CEdit*) GetDlgItem(IDC_EDIT_COUNT_LARGE); // edit control의 
	pCtlEdit->SetWindowText(count);
}

#endif