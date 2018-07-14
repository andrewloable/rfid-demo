// RFRMDoc.h : interface of the CRFRMDoc class
//

#pragma once

//class CTagInfo;
class CRFRMDoc : public CDocument
{
protected: // create from serialization only
	CRFRMDoc();
	DECLARE_DYNCREATE(CRFRMDoc)

// Attributes
public:
	BOOL				m_bLeakEnable;
	UINT				m_nLeakTime;
	bool				m_bLeakMode;
protected:
	CPtrList			m_listTag;
	CTagInfo*			m_selectedTagInfo;
	
	RFID_RADIO_FIRMWARE_MODE	m_radioFirmwareMode;
// Operations
public:
	CPtrList* GetTagList();

	inline RFID_RADIO_FIRMWARE_MODE GetFirmwareUpdateMode();
	inline void GetFirmwareUpdateMode(RFID_RADIO_FIRMWARE_MODE* mode);
	inline void SetFirmwareUpdateMode(RFID_RADIO_FIRMWARE_MODE mode);
// Overrides
public:
	virtual BOOL OnNewDocument();
#ifndef _WIN32_WCE_NO_ARCHIVE_SUPPORT
	virtual void Serialize(CArchive& ar);
#endif // !_WIN32_WCE_NO_ARCHIVE_SUPPORT

// Implementation
public:
	virtual ~CRFRMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	inline void SetSelectedTag(CTagInfo* tag);
	inline CTagInfo* GetSelectedTag();
	BOOL	GetLeakEnable();
	void	SetLeakEnable(BOOL leak);
	inline void	SetLeakMode(bool mode);
	inline bool	GetLeakMode();
	afx_msg void OnFileExport();
	afx_msg void OnUpdateFileExport(CCmdUI *pCmdUI);
};

inline CTagInfo* CRFRMDoc::GetSelectedTag()
{
	return m_selectedTagInfo;	
}

inline  void CRFRMDoc::SetSelectedTag(CTagInfo* tag)
{
//	AfxMessageBox(tag->GetTagString());

	m_selectedTagInfo = tag;
}

inline void CRFRMDoc::SetLeakMode(bool mode)
{
	m_bLeakMode = mode;
}

inline bool CRFRMDoc::GetLeakMode()
{
	return m_bLeakMode;
}

inline void CRFRMDoc::GetFirmwareUpdateMode(RFID_RADIO_FIRMWARE_MODE* mode)
{
	mode = &m_radioFirmwareMode;
}

inline void CRFRMDoc::SetFirmwareUpdateMode(RFID_RADIO_FIRMWARE_MODE mode)
{
	m_radioFirmwareMode = mode;
}

inline RFID_RADIO_FIRMWARE_MODE CRFRMDoc::GetFirmwareUpdateMode()
{
	return m_radioFirmwareMode;
}
