#pragma once

#define RFID_POWER		1
#define RFID_RESET		2
#define RFID_GREEN_LED	3
#define RFID_RED_LED	4

#ifdef WINCE 

#include <pkfuncs.h>

// BEEP Message
#define SOUND_COMPLETE		200
#define SOUND_BEEP			201
#define SOUND_BATTERY		202

#define IOCTL_HAL_SSTW_RFID_CONTROL    CTL_CODE(FILE_DEVICE_HAL, 2121 , METHOD_BUFFERED, FILE_ANY_ACCESS)

// Modified by Youngho Kim
// Date : 2007/08/22
// Description : Mobilecompia 전원 인가 방식 수정

/* Original
typedef struct  
{
unsigned char u8SelectPin;	// [OUT] select pin : 1:power, 2:reset, 3:GreenLED, 4:RedLED, 5:Control1, 6:Control2, 7:Receive Status
unsigned char u8PinOut;		// [OUT] Out Pin : 0:Low, 1:High
} SSTWRFIDCTL, *PSSTWRFIDCTL;
*/

// Modified version
typedef struct  {
	unsigned char u8SelectPin; // [OUT] select pin : 1:power, 2:reset, 3:GreenLED, 4:RedLED, 5:Control1, 6:Control2, 7:Receive Status
	unsigned char u8PinOut;   // [OUT] Out Pin : 0:Low, 1:High
	unsigned char bReadStatus;  // [OUT] Read Pin state : 0:not Read, 1:Read Pin Status
} SSTWRFIDCTL, *PSSTWRFIDCTL;

#endif

BOOL SetControlState(int nSelectPin, BOOL bState);
BOOL GetControlState(int nSelectPin);

enum
{
	RFID_RADIO_FILTER_GABAGE,
	RFID_RADIO_FILTER_TIMMER
};
typedef INT32U  RFID_RADIO_FILTER_MODE;

class CWaveBox;
class CFrequencyBandList;
class CRFIDRadioManager
{
public:
	CRFIDRadioManager(CWnd* pWnd = NULL);
	~CRFIDRadioManager(void);

// Attribute
protected:
	RFID_VERSION					m_libraryVersion;
	RFID_RADIO_ENUM*				m_pRadioEnum;
	CPtrList						m_listRadio;
	
	CWnd*							m_pParent;
	
	//CPtrList						m_listPacketQueue;	
//	HANDLE							m_hThread;
//	DWORD							m_hThreadID;

	UINT32							m_nAntenna;
	UINT16							m_nChannel;
	RFID_RADIO_BEEP_MODE			m_radioBeepMode;
	RFID_RADIO_FILTER_MODE			m_radioFilterMode;

	DWORD							m_nPacketCount;
	CString							m_strBeepSound;
	CWaveBox*						m_waveBox;
	
	INT32U							m_nCmdCount;

	COleDateTime					m_oleStartDateTime;
public:
//	HANDLE							m_hEvent;

// Operations
public:
	void SetWaveBox(LPCTSTR strPath);
//#ifdef WINCE
	static BOOL SetControlState(int nSelectPin, BOOL bState);
	static BOOL GetControlState(int nSelectPin);
//#endif
	RFID_STATUS Connect();
	RFID_STATUS Disconnect(void);
	int GetRadioCount(void);
	RFID_STATUS RunInventory(int nModule = 0, INT32 nCount = -1);
	RFID_STATUS TagRead(int nModule, INT32U* epc, RFID_18K6C_MEMORY_BANK bank, INT16U offset, INT16U count);
	RFID_STATUS TagWrite(int nModule, INT32U* epc, RFID_18K6C_MEMORY_BANK bank, INT16U offset, INT16U count, INT16U* pData);
	RFID_STATUS TagLock(int nModule, INT32U* epc, RFID_18K6C_TAG_PERM permission, INT32U accessPassword);
	RFID_STATUS TagKill(int nModule, INT32U* epc, INT32U accessPassword, INT32U killPassword);
	RFID_STATUS StopInventory(int nModule = 0);
	BOOL m_bConnect;
	BOOL IsConnect(void);
	void SetParent(CWnd* pParent);
//	BOOL m_bStart;
	BOOL IsInventory(int nModule = 0);
//	virtual INT Run();
	void AddRadioPacket(RFID_PACKET_COMMON* packet, void* context);
//	static DWORD WINAPI ThreadAddTagProc(LPVOID lpParam);
	RFID_STATUS GetRadioOperationMode(int nModule, RFID_RADIO_OPERATION_MODE* mode);
	RFID_STATUS SetRadioOperationMode(int nModule, RFID_RADIO_OPERATION_MODE mode);
	RFID_STATUS GetRadioResponseDataMode(int nModule, RFID_RESPONSE_MODE* mode);
	RFID_STATUS SetRadioResponseDataMode(int nModule, RFID_RESPONSE_MODE mode);
	RFID_STATUS GetRadioMacRegion(int nModule, RFID_MAC_REGION* region);
	RFID_STATUS SetRadioMacRegion(int nModule, RFID_MAC_REGION region);

	int			GetRadioAntennaCount(int nModule);
	RFID_STATUS GetRadioAntennaPortStatus(int nModule, int antennaNumber, RFID_ANTENNA_PORT_STATUS* antennaStatus);
	RFID_STATUS SetRadioAntennaPortState(int nModule, int antennaNumber, RFID_ANTENNA_PORT_STATE antennaStatus);
	RFID_STATUS GetRadioAntennaPortConfiguration(int nModule, int antennaNumber, RFID_ANTENNA_PORT_CONFIG* antennaConf);
	RFID_STATUS SetRadioAntennaPortConfiguration(int nModule, int antennaNumber, RFID_ANTENNA_PORT_CONFIG antennaConf);
	RFID_STATUS	GetRadioTransferTime(int nModule, INT32U* transferTime);
	RFID_STATUS SetRadioTransferTime(int nModule, INT32U transferTime);
	// Beep Mode function
	RFID_STATUS	GetRadioBeepMode(int nModule, RFID_RADIO_BEEP_MODE* mode);
	RFID_STATUS	SetRadioBeepMode(int nModule, RFID_RADIO_BEEP_MODE mode);

	RFID_STATUS GetRadioTrialCount(int nModule, INT32U* trial);
	RFID_STATUS SetRadioTrialCount(int nModule, INT32U trial);


	// get currently-active singulation algorithm
	RFID_STATUS GetRadio18K6CCurrentSingulationAlgorithm(int nModule, RFID_18K6C_SINGULATION_ALGORITHM* algorithm);
	RFID_STATUS SetRadio18K6CCurrentSingulationAlgorithm(int nModule, RFID_18K6C_SINGULATION_ALGORITHM algorithm);

	RFID_STATUS SetRadio18K6CQueryTagGroup(int nModule, RFID_18K6C_TAG_GROUP* tagGroup);
	RFID_STATUS GetRadio18K6CQueryTagGroup(int nModule, RFID_18K6C_TAG_GROUP* tagGroup);

	RFID_STATUS SetRadio18K6CQueryParameters(int nModule, RFID_18K6C_QUERY_PARMS* pParms);
	RFID_STATUS GetRadio18K6CQueryParameters(int nModule, RFID_18K6C_QUERY_PARMS* pParms);

	RFID_STATUS SetRadioConfigurationParameter(int nModule, INT16U parameter, INT32U val);
	RFID_STATUS GetRadioConfigurationParameter(int nModule, INT16U parameter, INT32U* val);

	RFID_STATUS RadioCarrierWaveOn(int nModule = 0);
	RFID_STATUS RadioCarrierWaveOff(int nModule = 0);

	RFID_STATUS Reset(int nModule = 0);

	RFID_STATUS GetRadioFirmwareVersion(int nModule, RFID_VERSION* version);
	RFID_STATUS GetRadioMacVersion(int nModule, RFID_VERSION* version);
	RFID_STATUS RadioFirmwareUpdate(int nModule, LPCTSTR filename, BOOL skipTestMode = FALSE, BOOL testModeOnly = FALSE, CWnd* pParent = NULL);
	RFID_STATUS RadioFirmwareUpdate(int nModule, LPCTSTR filename, 	RFID_RADIO_FIRMWARE_MODE mode, CWnd* pParent = NULL);

	RFID_STATUS GetFrequencyBand(int nModule, CFrequencyBandList* band);
	void		PrintPacket(const RFID_PACKET_COMMON *packet, int indent);
#ifdef WINCE
	BOOL		Sound(DWORD fre, DWORD due);
#endif
};
