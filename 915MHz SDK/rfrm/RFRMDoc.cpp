// RFRMDoc.cpp : implementation of the CRFRMDoc class
//

#include "stdafx.h"
#include "RFRM.h"

#include "RFRMDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRFRMDoc

IMPLEMENT_DYNCREATE(CRFRMDoc, CDocument)

BEGIN_MESSAGE_MAP(CRFRMDoc, CDocument)
	ON_COMMAND(ID_FILE_EXPORT, &CRFRMDoc::OnFileExport)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORT, &CRFRMDoc::OnUpdateFileExport)
END_MESSAGE_MAP()

// CRFRMDoc construction/destruction

CRFRMDoc::CRFRMDoc()
: m_bLeakEnable(FALSE)
, m_nLeakTime(1)
, m_bLeakMode(TRUE)
, m_selectedTagInfo(NULL)
, m_radioFirmwareMode(0)
{
	// TODO: add one-time construction code here
}

CRFRMDoc::~CRFRMDoc()
{
}

BOOL CRFRMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CRFRMDoc serialization

#ifndef _WIN32_WCE_NO_ARCHIVE_SUPPORT
void CRFRMDoc::Serialize(CArchive& ar)
{
	(ar);
}
#endif // !_WIN32_WCE_NO_ARCHIVE_SUPPORT


// CRFRMDoc diagnostics

#ifdef _DEBUG
void CRFRMDoc::AssertValid() const
{
	CDocument::AssertValid();
}
#endif //_DEBUG


// CRFRMDoc commands
CPtrList* CRFRMDoc::GetTagList()
{
	return &m_listTag;
}

BOOL CRFRMDoc::GetLeakEnable()
{
	return m_bLeakEnable;
}

void CRFRMDoc::SetLeakEnable(BOOL leak)
{
	m_bLeakEnable = leak;
}


void CRFRMDoc::OnFileExport()
{
	CFileDialog l_ExportDlg( FALSE, TEXT("Export"), TEXT(""),
		OFN_HIDEREADONLY|OFN_LONGNAMES,
		TEXT("Coma Separated Values (*.csv) | *.csv |Text File (*.txt)| *.txt |All Files (*.*) | *.* ||"));

	int iRet = l_ExportDlg.DoModal();
	CString l_strFileName;
	l_strFileName = l_ExportDlg.GetPathName();

	if(iRet == IDOK && l_strFileName.GetLength() > 0)
	{
		CFile file;
		CString strData = TEXT("");

		if(file.Open(l_strFileName, CFile::modeWrite | CFile::modeCreate))
		{
			POSITION pos = m_listTag.GetHeadPosition();

			strData = TEXT("Tag ID,");
			strData += TEXT("Total Read Count,");
			strData += TEXT("Read Count,");
			strData += TEXT("Trial Count,");
			strData += TEXT("Antenna,");
			strData += TEXT("Channel,");
			strData += TEXT("Date/Time,\n");

			file.Write(strData.GetBuffer(1024), strData.GetLength() * sizeof(WCHAR));  // Excel 파일 쓰기 
			file.Flush();

			while(pos != NULL)
			{
				CTagInfo* lpTagInfo = (CTagInfo*)m_listTag.GetNext(pos);
				RFID_TAG_DISPLAY_MODE mode = AfxGetApp()->GetProfileInt(_T("Engineering"),_T("Display"), 0);


				CString temp = TEXT("");

				switch(mode)
				{
				case RFID_TAG_DISPLAY_MODE_EPC:
					strData =  lpTagInfo->GetTagString();
					break;
				case RFID_TAG_DISPLAY_MODE_ASCII:
					strData =  lpTagInfo->GetTagAsciiString();
					break;
				}
				strData += _T(",");

				temp.Format(_T("%u"), lpTagInfo->GetTagTotalReadCount());		// Total Read count
				strData += temp;
				strData += _T(",");

				temp.Format(_T("%u"), lpTagInfo->GetTagReadCount());		// Tag Read count
				strData += temp;
				strData += _T(",");

				temp.Format(_T("%u"), lpTagInfo->GetTagTrialCount());		// Trial count
				strData += temp;
				strData += _T(",");

				temp.Format(_T("%u"), lpTagInfo->GetTagAntenna());		//Total Read
				strData += temp;
				strData += _T(",");

				temp.Format(_T("%u"), lpTagInfo->GetTagChannel());		//Total Read
				strData += temp;
				strData += _T(",");

				temp.Format(_T("%s"), lpTagInfo->GetTagReceiveTime().Format(_T("%H:%M:%S")));		//Total Read
				strData += temp;
				strData += _T(",\n");
			
				file.Write(strData.GetBuffer(1024), strData.GetLength()*sizeof(WCHAR));  // Excel 파일 쓰기 
				file.Flush();
			}

			file.Close();
		}
	}
}

void CRFRMDoc::OnUpdateFileExport(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_listTag.IsEmpty());
}
