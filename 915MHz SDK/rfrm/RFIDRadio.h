#pragma once
//#include "afxcoll.h"

#include "FrequencyBandList.h"
#include "OperationMode.h"

#define MAX_HANDLE_CNT		10
#define BYTES_PER_LEN_UNIT	4
#define EPC_WORD_LENGTH		8

enum 
{
	RFID_INVENTORY,
	RFID_READ,
	RFID_WRITE,
	RFID_LOCK,
	RFID_KILL,
};
typedef INT32U  RFID_RUN_STATUS;

typedef struct
{
	BOOL32  operationSucceeded;
	INT8U*  pReadData;
	INT16U*	pWriteData;
} CONTEXT_PARMS;


//class CRFIDRadioManager;
class CRFIDRadio : public AThread
{
public:
	CRFIDRadio(RFID_RADIO_INFO* pRadioInfo = NULL, void* pParent = NULL);
	~CRFIDRadio(void);
	// Radio Number

// Attributes
public:
	RFID_RUN_STATUS					m_runStatus;

	INT32U*							m_epc;
	RFID_18K6C_MEMORY_BANK			m_MBank;
	INT16U							m_nOffset;
	INT16U							m_nCount;
	INT16U*							m_nWriteData;
	INT32							m_nStopCountDown;

	RFID_18K6C_TAG_PERM				m_lockPermission;

	INT32U							m_AccessPassword;
	INT32U							m_KillPassword;

protected:
	RFID_18K6C_INVENTORY_PARMS		m_rfid18K6CInventoryParms;
	RFID_18K6C_READ_PARMS			m_rfid18K6CReadParms;
	RFID_18K6C_WRITE_PARMS			m_rfid18K6CWriteParms;
	RFID_RADIO_HANDLE				m_rfidHandle;

	BOOL							m_bEmulated;
	int								m_rfidIndentlevel;
	RFID_RADIO_INFO*				m_pRadioInfo;

	BOOL							m_bPerformSelectOpsFlag;
	BOOL							m_bPerformPostMatchFlag;

//	CFrequencyBandList				m_listFrequencyBand;
	COperationMode					m_objectOperationMode;			

// Operations
public:
	virtual INT Run();
	inline RFID_RADIO_HANDLE GetRadioHandle();
	inline void	SetRunStatus(RFID_RUN_STATUS status);
	RFID_STATUS OpenRadio();
	RFID_STATUS CloseRadio();
	RFID_STATUS RadioCancelOperation(void);
	RFID_STATUS RadioAbortOperation(void);

	// Transfer Time
	RFID_STATUS SetRadioTransferTime(UINT32 time);
	RFID_STATUS GetRadioTransferTime(UINT32* time);

	// Operation Mode
	RFID_STATUS SetRadioOperationMode(RFID_RADIO_OPERATION_MODE mode = RFID_RADIO_OPERATION_MODE_NONCONTINUOUS);
	RFID_STATUS GetRadioOperationMode(RFID_RADIO_OPERATION_MODE* mode);
	// Response Data mode
	RFID_STATUS SetRadioResponseDataMode(RFID_RESPONSE_MODE mode = RFID_RESPONSE_MODE_NORMAL);
	RFID_STATUS GetRadioResponseDataMode(RFID_RESPONSE_MODE* mode);
	// Mac Region
	RFID_STATUS SetMacRegion(RFID_MAC_REGION region);
	RFID_STATUS GetMacRegion(RFID_MAC_REGION* region);
	// Antenna Port Status
	int			GetAntennaCount();
	RFID_STATUS GetAntennaPortStatus(int antennaNumber, RFID_ANTENNA_PORT_STATUS* antenna);
	RFID_STATUS SetAntennaPortState(int antennaNumber, RFID_ANTENNA_PORT_STATE antennaState);
	// Antenna Port Configuration
	RFID_STATUS GetAntennaPortConfiguration(int antennaNumber, RFID_ANTENNA_PORT_CONFIG* antennaConf);
	RFID_STATUS SetAntennaPortConfiguration(int antennaNumber, RFID_ANTENNA_PORT_CONFIG antennaConf);
	// Transfer time configuration
	RFID_STATUS	GetTransferTime(INT32U* transferTime);
	RFID_STATUS SetTransferTime(INT32U transferTime);

	RFID_STATUS GetBeepMode(RFID_RADIO_BEEP_MODE* mode);
	RFID_STATUS SetBeepMode(RFID_RADIO_BEEP_MODE mode);

	// trail count configuration
	RFID_STATUS GetTrialCount(INT32U* trial);
	RFID_STATUS SetTrialCount(INT32U trial);


	// Singulation Algorithm
	RFID_STATUS SetCurrentSingulationAlgorithm(RFID_18K6C_SINGULATION_ALGORITHM algorithm);
	RFID_STATUS GetCurrentSingulationAlgorithm(RFID_18K6C_SINGULATION_ALGORITHM* algorithm);

	// Query Tag Group
	RFID_STATUS SetQueryTagGroup(RFID_18K6C_TAG_GROUP* tagGroup);
	RFID_STATUS GetQueryTagGroup(RFID_18K6C_TAG_GROUP* tagGroup);

	// Query Param
	RFID_STATUS SetQueryParameters(RFID_18K6C_QUERY_PARMS* pParms);
	RFID_STATUS GetQueryParameters(RFID_18K6C_QUERY_PARMS* pParms);

	// Configuration Param
	RFID_STATUS SetConfigurationParameter(INT16U parameter, INT32U value);
	RFID_STATUS GetConfigurationParameter(INT16U parameter, INT32U* value);

	// Get Version
	RFID_STATUS GetFirmwareVersion(RFID_VERSION* version);
	RFID_STATUS GetMacVersion(RFID_VERSION* version);

	RFID_STATUS CarrierWaveOn();
	RFID_STATUS CarrierWaveOff();

	// Frequency Band
	RFID_STATUS GetFrequencyBandList(CFrequencyBandList* band);
	RFID_STATUS SetFrequencyBandList(CFrequencyBandList band);

	RFID_STATUS	MacReset();
};

inline void	CRFIDRadio::SetRunStatus(RFID_RUN_STATUS status)
{
	m_runStatus = status;
}

inline RFID_RADIO_HANDLE CRFIDRadio::GetRadioHandle()
{
	return m_rfidHandle;
}