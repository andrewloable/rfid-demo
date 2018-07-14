#pragma once


#define BYTES_PER_LEN_UNIT	4

// CRunThread
class CRFIDRadio;
class CRFIDRadioManager;
class CRunThread : public CWinThread
{
	DECLARE_DYNCREATE(CRunThread)

public:
	CRFIDRadio*						m_pRadio;

protected:
	CRunThread();           // protected constructor used by dynamic creation
	virtual ~CRunThread();

//	RFID_RADIO_HANDLE				m_rfidHandle;


	INT32U*							m_epc;
	RFID_18K6C_MEMORY_BANK			m_MBank;
	INT16U							m_nOffset;
	INT16U							m_nCount;
	INT16U*							m_nWriteData;
	INT32							m_nStopCountDown;

	BOOL							m_bPerformSelectOpsFlag;
	BOOL							m_bPerformPostMatchFlag;

public:
	static CRFIDRadioManager*		m_pParent;
//    RFID_18K6C_COMMON_PARMS common;
	static INT32S RFID_CALLBACK PacketCallbackFunction(RFID_RADIO_HANDLE   handle,
		INT32U              bufferLength,
		const INT8U*        pBuffer,
		void *              context);

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


