// ..\InterfaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "InterfaceDlg.h"


// CInterfaceDlg dialog

IMPLEMENT_DYNAMIC(CInterfaceDlg, CDialog)

CInterfaceDlg::CInterfaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInterfaceDlg::IDD, pParent)
{

}

CInterfaceDlg::~CInterfaceDlg()
{
}

void CInterfaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_INTERFACE, m_ctrlComboInterface);
	DDX_Control(pDX, IDC_EDIT_ADDRESS,	m_ctrlEditAddress);
	DDX_Control(pDX, IDC_EDIT_PORT,	m_ctrlEditPort);
}


BEGIN_MESSAGE_MAP(CInterfaceDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_INTERFACE, &CInterfaceDlg::OnCbnSelchangeComboInterface)
	ON_BN_CLICKED(IDOK, &CInterfaceDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInterfaceDlg message handlers

BOOL CInterfaceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
#ifndef _WIN32_WCE
	TCHAR szAddress[ 50 ] = TEXT("");
	TCHAR szPort[ 50 ] = TEXT("");
	TCHAR szInterface[ 50 ] = TEXT("");

	// Region
	m_ctrlComboInterface.AddString(_T("0 : USB"));
	m_ctrlComboInterface.AddString(_T("1 : SERIAL"));
	m_ctrlComboInterface.AddString(_T("2 : TCP/IP"));
	m_ctrlComboInterface.AddString(_T("2 : UNKNOWN"));

	m_ctrlEditAddress.SetWindowText(TEXT("127.0.0.1"));
	
	m_ctrlEditPort.SetWindowText(TEXT("1470"));

	if( GetPrivateProfileString(TEXT("APP CONFIG"), TEXT("ADDRESS"), TEXT("0.0.0.0"), szAddress, 50, TEXT("appconfig.ini")) &&
		GetPrivateProfileString(TEXT("APP CONFIG"), TEXT("PORT"), TEXT("1470"), szPort, 50, TEXT("appconfig.ini")) &&
		GetPrivateProfileString(TEXT("APP CONFIG"), TEXT("IF"), TEXT("USB"), szInterface, 50, TEXT("appconfig.ini")))
	{
		if(_tcscmp(szInterface, TEXT("USB")) == 0)
		{
			m_ctrlEditAddress.EnableWindow(FALSE);
			m_ctrlEditPort.EnableWindow(FALSE);

			m_ctrlComboInterface.SetCurSel(0);
		}
		else if(_tcscmp(szInterface, TEXT("SERIAL")) == 0)
		{
			m_ctrlEditAddress.EnableWindow(FALSE);
			m_ctrlEditPort.EnableWindow(TRUE);

			CString port;

			port.Format(TEXT("%s"), szPort);
			m_ctrlEditPort.SetWindowText(port);

			m_ctrlComboInterface.SetCurSel(1);
		}
		else if(_tcscmp(szInterface, TEXT("TCP")) == 0)
		{
			m_ctrlEditAddress.EnableWindow(TRUE);
			m_ctrlEditPort.EnableWindow(TRUE);

			m_ctrlEditAddress.SetWindowText(szAddress);

			CString port;

			port.Format(TEXT("%s"), szPort);
			m_ctrlEditPort.SetWindowText(port);

			m_ctrlComboInterface.SetCurSel(2);
		}
		else
		{
			m_ctrlEditAddress.EnableWindow(FALSE);
			m_ctrlEditPort.EnableWindow(FALSE);

			m_ctrlComboInterface.SetCurSel(3);
		}
	}
#endif

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CInterfaceDlg::OnCbnSelchangeComboInterface()
{
	int curSel = m_ctrlComboInterface.GetCurSel();
#ifndef _WIN32_WCE
	switch(curSel)
	{
	case 0:
		m_ctrlEditAddress.EnableWindow(FALSE);
		m_ctrlEditPort.EnableWindow(FALSE);

		break;
	case 1:
		m_ctrlEditAddress.EnableWindow(FALSE);
		m_ctrlEditPort.EnableWindow(TRUE);

		break;
	case 2:
		m_ctrlEditAddress.EnableWindow(TRUE);
		m_ctrlEditPort.EnableWindow(TRUE);

		break;
	default:
		m_ctrlEditAddress.EnableWindow(FALSE);
		m_ctrlEditPort.EnableWindow(FALSE);

		break;
	}
#endif
}

void CInterfaceDlg::OnBnClickedOk()
{
	CString szInterface;
	CString szAddress;
	CString szPort;
#ifndef _WIN32_WCE
	int curSel = m_ctrlComboInterface.GetCurSel();

	switch(curSel)
	{
	case 0:
		m_ctrlEditAddress.GetWindowText(szAddress);
		m_ctrlEditPort.GetWindowText(szPort);

		WritePrivateProfileString(TEXT("APP CONFIG"), TEXT("ADDRESS"), szAddress, TEXT("appconfig.ini"));
		WritePrivateProfileString(TEXT("APP CONFIG"), TEXT("PORT"), szPort, TEXT("appconfig.ini"));
		WritePrivateProfileString(TEXT("APP CONFIG"), TEXT("IF"), TEXT("USB"), TEXT("appconfig.ini"));

//		AfxMessageBox(_T("USB"));
		break;
	case 1:
		m_ctrlEditAddress.GetWindowText(szAddress);
		m_ctrlEditPort.GetWindowText(szPort);

		WritePrivateProfileString(TEXT("APP CONFIG"), TEXT("ADDRESS"), szAddress, TEXT("appconfig.ini"));
		WritePrivateProfileString(TEXT("APP CONFIG"), TEXT("PORT"), szPort, TEXT("appconfig.ini"));
		WritePrivateProfileString(TEXT("APP CONFIG"), TEXT("IF"), TEXT("SERIAL"), TEXT("appconfig.ini"));

//		AfxMessageBox(_T("SERIAL"));
		break;
	case 2:
		m_ctrlEditAddress.GetWindowText(szAddress);
		m_ctrlEditPort.GetWindowText(szPort);

		WritePrivateProfileString(TEXT("APP CONFIG"), TEXT("ADDRESS"), szAddress, TEXT("appconfig.ini"));
		WritePrivateProfileString(TEXT("APP CONFIG"), TEXT("PORT"), szPort, TEXT("appconfig.ini"));
		WritePrivateProfileString(TEXT("APP CONFIG"), TEXT("IF"), TEXT("TCP"), TEXT("appconfig.ini"));

//		AfxMessageBox(_T("TCP"));
		break;
	default:
		m_ctrlEditAddress.GetWindowText(szAddress);
		m_ctrlEditPort.GetWindowText(szPort);

		WritePrivateProfileString(TEXT("APP CONFIG"), TEXT("ADDRESS"), szAddress, TEXT("appconfig.ini"));
		WritePrivateProfileString(TEXT("APP CONFIG"), TEXT("PORT"), szPort, TEXT("appconfig.ini"));
		WritePrivateProfileString(TEXT("APP CONFIG"), TEXT("IF"), TEXT("UNKNOWN"), TEXT("appconfig.ini"));

//		AfxMessageBox(_T("UNKNOWN"));
		break;
	}
#endif
	// TODO: Add your control notification handler code here
	OnOK();
}
