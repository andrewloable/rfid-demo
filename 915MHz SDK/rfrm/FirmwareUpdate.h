#pragma once

#include "mapfile.h"

typedef struct xmlNode
{
	char*           pName;          /* The name of this node                  */
	struct xmlNode* pNextSibling;   /* The next sibling (if any) of this node */
	struct xmlNode* pFirstChild;    /* The first child (if any) of this node  */
	struct xmlNode* pLastChild;     /* The first child (if any) of this node  */
	char*           pValue;         /* The value (if any) of this node        */
} XML_NODE;

class CFirmwareUpdate : public CObject
{
public:
	CFirmwareUpdate(RFID_RADIO_HANDLE handle);
	CFirmwareUpdate(RFID_RADIO_HANDLE handle, BOOL skipTestMode = FALSE, BOOL testModeOnly = TRUE);
	CFirmwareUpdate(RFID_RADIO_HANDLE handle, LPCTSTR filename, BOOL skipTestMode = FALSE, BOOL testModeOnly = TRUE);
	CFirmwareUpdate(RFID_RADIO_HANDLE handle, LPCTSTR filename, BOOL skipTestMode = FALSE, BOOL testModeOnly = TRUE, CWnd* pParent = NULL);
	CFirmwareUpdate(RFID_RADIO_HANDLE handle, LPCTSTR filename, RFID_RADIO_FIRMWARE_MODE mode, CWnd* pParent = NULL);
	virtual ~CFirmwareUpdate();

// operation
protected:
	XML_NODE* CreateXmlTree(    
		const char* pFileStream,
		INT32U      length);

	void DestroyXmlTree(
		XML_NODE*   pRoot
		);
	INT32S ProcessXmlTree(
		const XML_NODE*                 pRoot,
		RFID_NONVOLATILE_MEMORY_BLOCK** ppBlocks,
		MEMMAP_HANDLE**                 ppHandles,
		INT32U*                         pNumberBlocks
		);
public:
	BOOL FirmwareUpate();
	inline RFID_RADIO_HANDLE GetHandle();
	inline BOOL GetSkipTestMode() { return m_bSkipTestMode; }
	inline BOOL GetTestOnlyMode() { return m_bTestModeOnly; }
	inline INT32U GetNumberofBlocks() { return m_numberBlocks; }
	inline RFID_NONVOLATILE_MEMORY_BLOCK* GetBlocks() { return m_pBlocks; }
	inline CWnd* GetParent();
		
protected:
	static DWORD WINAPI FirmwareUpdateThreadProc(LPVOID pParam);

protected:
	CWnd*							m_pParent;
	CWinThread*						m_pThread;						
	BOOL							m_bStopRequest;
	XML_NODE*                       m_pRoot;

	MEMMAP_HANDLE                   memmap;
	RFID_RADIO_HANDLE				m_rfidHandle;

	INT32U							m_numberBlocks;
	RFID_NONVOLATILE_MEMORY_BLOCK*  m_pBlocks;

	BOOL							m_bSkipTestMode;
	BOOL							m_bTestModeOnly;
	CString							m_strFileName;
};

inline RFID_RADIO_HANDLE CFirmwareUpdate::GetHandle()
{
	return m_rfidHandle;
}

inline CWnd* CFirmwareUpdate::GetParent()
{
	return m_pParent;
}

