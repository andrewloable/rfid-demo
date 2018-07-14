#include "StdAfx.h"
#include "RFRM.h"
#include "RFIDRadioManager.h"
#include "RFIDRadio.h"

#include "mapfile.h"
#include "FirmwareUpdate.h"
#include "WaveBox.h"
#include "FrequencyBandList.h"

#include "Util.h"

static CFile file;

CRFIDRadioManager::CRFIDRadioManager(CWnd* pWnd)
: m_pRadioEnum(NULL)
, m_pParent(pWnd)
, m_bConnect(FALSE)
//, m_bStart(FALSE)
, m_nAntenna(0)
, m_nChannel(0)
, m_nPacketCount(0)
, m_radioFilterMode(RFID_RADIO_FILTER_GABAGE)
, m_nCmdCount(0)
{
	m_strBeepSound = AfxGetApp()->GetProfileString(TEXT("WaveBox"), TEXT("Path"));
	m_radioBeepMode = (RFID_RADIO_BEEP_MODE)AfxGetApp()->GetProfileInt(TEXT("WaveBox"), TEXT("Mode"), 0);

	if(!m_strBeepSound.IsEmpty())
	{
		m_waveBox = new CWaveBox();
		m_waveBox->Load((LPTSTR)(LPCTSTR)m_strBeepSound);
	}
}

CRFIDRadioManager::~CRFIDRadioManager(void)
{
	if(IsConnect())
		Disconnect();
	// free a buffer for radio enumeration
//	delete m_pRadioEnum;
	free(m_pRadioEnum);
}

RFID_STATUS CRFIDRadioManager::Connect()
{
	RFID_STATUS status;

	// First open the library
	if (RFID_STATUS_OK != 
		(status = RFID_Startup(&m_libraryVersion, 0x00000000)))
	{
		TRACE(L"RFID_Startup() failed.  RC = %d\n", status);

		return status;
	}

	// Allocate a buffer for radio enumeration
	m_pRadioEnum = (RFID_RADIO_ENUM *) malloc(sizeof(RFID_RADIO_ENUM));
	if (m_pRadioEnum == NULL)
	{
		TRACE(L"Failed to allocate memory\n");

		// Shut down the library
		RFID_Shutdown();

		status = RFID_ERROR_FAILURE;

		return status;
	}

	// Initialize the enumeration buffer
	m_pRadioEnum->length      = sizeof(RFID_RADIO_ENUM);
	m_pRadioEnum->totalLength = sizeof(RFID_RADIO_ENUM);

	// Keep attempting to enumerate while the library says that the buffer is
	// too small.  This accounts for a situation where a radio may be plugged
	// in between the call to enumerate and the return with the previously   
	// needed buffer size.                                                   
	while (RFID_ERROR_BUFFER_TOO_SMALL ==
		(status = RFID_RetrieveAttachedRadiosList(m_pRadioEnum, 0)))
	{
		/* Allocate a new, larger buffer */
		RFID_RADIO_ENUM* pNewEnum = 
			(RFID_RADIO_ENUM *) realloc(m_pRadioEnum, m_pRadioEnum->totalLength);

		if (NULL == pNewEnum)
		{
			TRACE(L"Failed to reallocate memory\n");

			/* Shut down the library */
			RFID_Shutdown();

			return FALSE;
		}

		m_pRadioEnum = pNewEnum;
	}

	// Verify that the enumeration was successful */
	if (RFID_STATUS_OK != status)
	{
		TRACE1("RFID_RetrieveAttachedRadiosList failed:  RC = %d\n", status);

		// Shut down the library
		RFID_Shutdown();

		return FALSE;
	}

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		for(unsigned int i = 0 ; i < m_pRadioEnum->countRadios; i++)
		{
			CRFIDRadio* pRadio = new CRFIDRadio(m_pRadioEnum->ppRadioInfo[i], this);

			if(RFID_STATUS_OK != 
				( status = pRadio->OpenRadio()))
			{
				TRACE(_T("%d's OpenRadio failed:  RC = %d\n"), i, status);
				return status;
			}

			m_listRadio.AddTail(pRadio);
		}

		m_bConnect = !m_bConnect;
	}

	file.Open(TEXT("Temperature.csv"), CFile::modeWrite | CFile::modeCreate);

	return status;
}

RFID_STATUS CRFIDRadioManager::Disconnect(void)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if(m_bConnect)
	{
		if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
		{
			for(unsigned int i = 0; i< m_pRadioEnum->countRadios; i++)
			{
				POSITION pos = m_listRadio.FindIndex(i);
				CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

				if(pRadio->IsActive())
				{
					if(RFID_STATUS_OK != 
						(status = pRadio->RadioAbortOperation()))
					{
						TRACE1("RadioAbortOperation failed:  RC = %d\n", status);
						//				return status;
					}
				}

				if(RFID_STATUS_OK != 
					(status = pRadio->CloseRadio()))
				{
					TRACE1("CloseRadio failed:  RC = %d\n", status);
					//				return status;
				}

				delete pRadio;
				pRadio = NULL;

				m_listRadio.RemoveAll();
			}
		}

		delete m_pRadioEnum;
		m_pRadioEnum = NULL;

		// Shut down the library
		if(RFID_STATUS_OK != 
			(status = RFID_Shutdown()))
		{
			TRACE1("RFID_Shutdown failed:  RC = %d\n", status);
			return status;
		}

		m_bConnect = !m_bConnect;
	}

	file.Close();

	return status;
}

int CRFIDRadioManager::GetRadioCount(void)
{
	if(m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
		return m_pRadioEnum->countRadios;

	return 0;
}

RFID_STATUS CRFIDRadioManager::RunInventory(int nModule, INT32 nCount)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if(m_listRadio.GetCount() > 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);	// find the radio oject
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		pRadio->m_nStopCountDown = nCount;	// set the inventory stop cound
		pRadio->m_runStatus = RFID_INVENTORY;	// set the inventory mode

		m_oleStartDateTime = COleDateTime::GetCurrentTime();	// set the current time

		pRadio->Create();		// create inventory thread
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::TagRead(int nModule, INT32U* epc, RFID_18K6C_MEMORY_BANK bank, INT16U offset, INT16U count)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if(m_listRadio.GetCount() > 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		pRadio->m_runStatus = RFID_READ;

		if(epc != NULL)
		{
			pRadio->m_epc = epc;
		}
		else
		{
			pRadio->m_epc = NULL;
		}

		pRadio->m_MBank = bank;
		pRadio->m_nOffset = offset;
		pRadio->m_nCount = count;

		pRadio->Create();

//		m_bStart = TRUE;
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::TagWrite(int nModule, INT32U* epc, RFID_18K6C_MEMORY_BANK bank, INT16U offset, INT16U count, INT16U* pData)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if(m_listRadio.GetCount() > 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		pRadio->m_runStatus = RFID_WRITE;

		if(epc != NULL)
		{
			pRadio->m_epc = epc;
		}
		else
		{
			pRadio->m_epc = NULL;
		}

		pRadio->m_MBank = bank;
		pRadio->m_nOffset = offset;
		pRadio->m_nCount = count;
		pRadio->m_nWriteData = pData;

		pRadio->Create();

		//m_bStart = TRUE;
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::TagLock(int nModule, INT32U* epc, RFID_18K6C_TAG_PERM permission, INT32U accessPassword)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if(m_listRadio.GetCount() > 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		pRadio->m_runStatus = RFID_LOCK;

		if(epc != NULL)
		{
			pRadio->m_epc = epc;
		}
		else
		{
			pRadio->m_epc = NULL;
		}

		pRadio->m_lockPermission = permission;
		pRadio->m_AccessPassword = accessPassword;

		pRadio->Create();

		//m_bStart = TRUE;
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::TagKill(int nModule, INT32U* epc, INT32U accessPassword, INT32U killPassword)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if(m_listRadio.GetCount() > 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		pRadio->m_runStatus = RFID_KILL;

		if(epc != NULL)
		{
			pRadio->m_epc = epc;
		}
		else
		{
			pRadio->m_epc = NULL;
		}

		pRadio->m_AccessPassword = accessPassword;
		pRadio->m_KillPassword = killPassword;

		pRadio->Create();

		//m_bStart = TRUE;
	}

	return status;
}


RFID_STATUS CRFIDRadioManager::StopInventory(int nModule)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		pRadio->NotifyStop();
#ifdef _WIN32_WCE
		if(RFID_STATUS_OK != 
			(status = pRadio->RadioAbortOperation()))
		{
			TRACE1("RadioAbortOperation failed:  RC = %d\n", status);
			return status;
		}
#else
		if(RFID_STATUS_OK != 
			(status = pRadio->RadioCancelOperation()))
		{
			TRACE1("RadioCancelOperation failed:  RC = %d\n", status);
			return status;
		}
#endif

//		m_bStart = FALSE;
	}

	return status;
}

BOOL CRFIDRadioManager::IsConnect(void)
{
	return m_bConnect;
}

void CRFIDRadioManager::SetParent(CWnd* pParent)
{
	m_pParent = pParent;
}

BOOL CRFIDRadioManager::IsInventory(int nModule)
{
	BOOL active = FALSE;

	if(m_listRadio.GetCount() > 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		active = pRadio->IsActive();

#ifdef _DEBUG
		CString str;

//		str.Format(TEXT("\n\nThread Activation State : %b\n\n"), active);
#endif
	}

	return active;
}

#ifdef WINCE
BOOL CRFIDRadioManager::Sound(DWORD fre, DWORD due)
{
	BOOL bRtn;
	LPCWSTR lpRes;
	_TCHAR	lpName[10];
	HANDLE hRes;
	HRSRC hResInfo;
	HINSTANCE Nl=AfxGetInstanceHandle();

	/* Find the WAVE resource. */
	switch(fre)
	{
	case SOUND_COMPLETE:
		wcscpy(lpName,_T("IDR_WAVE_COMPLETE"));
		break;
	case SOUND_BEEP:
		wcscpy(lpName,_T("IDR_WAVE_BEEP"));
		break;
	case SOUND_BATTERY:
		wcscpy(lpName,_T("IDR_WAVE_SOUND"));
		break;
	}

	hResInfo= FindResource(Nl,lpName,_T("WAVE"));

	if(hResInfo == NULL)
		return FALSE;
	/* Load the WAVE resource. */

	hRes = LoadResource(Nl,hResInfo);
	if (hRes == NULL)
		return FALSE;

	/* Lock the WAVE resource and play it. */
	lpRes=(LPWSTR)LockResource(hRes);
	if(lpRes==NULL)
		return FALSE;

	bRtn = sndPlaySound(lpRes, SND_MEMORY | SND_SYNC);
	if(bRtn == NULL)
		return FALSE;

	/* Free the WAVE resource and return success or failure. */
	FreeResource(hRes);
	return TRUE;
}
#endif

void CRFIDRadioManager::AddRadioPacket(RFID_PACKET_COMMON* packet, void* context)
{
	RFID_PACKET_COMMON *common = (RFID_PACKET_COMMON *)packet;
	INT16U packetType = MacToHost16(common->pkt_type);

	m_nPacketCount++;

	CString str;
	str.Format(L"========================= Packet Count : %u\n", m_nPacketCount);
	TRACE(str);

	switch (packetType)
	{
	case RFID_PACKET_TYPE_COMMAND_BEGIN:
		{
			RFID_PACKET_COMMAND_BEGIN *cmdbegin =
				(RFID_PACKET_COMMAND_BEGIN *)packet;
			INT32U command = MacToHost32(cmdbegin->command);

			TRACE(_T("Packet type: RFID_PACKET_COMMAND_BEGIN\n"));
			CString strTemp, temp;
			
			if(common->flags & 1)
				temp.Format(_T(""));
			else
				temp.Format(_T("%s"), _T("not"));

			TRACE(_T("\tOperation was %s executed in continuous mode\n"), temp);
			TRACE(_T("\tOperation started at millisecond %u\n"), MacToHost32(cmdbegin->ms_ctr));
			TRACE(_T("\tOperation that is beginning: "));
			switch (command)
			{
			case RFID_COMMAND_TYPE_18K6C_INVENTORY:
				temp.Format(TEXT("Inventory"));
				TRACE(_T("Inventory\n"));
				break;
			case RFID_COMMAND_TYPE_18K6C_READ:
				temp.Format(TEXT("Read"));
				TRACE(_T("Read\n"));
				break;
			case RFID_COMMAND_TYPE_18K6C_WRITE:
				temp.Format(TEXT("Write"));
				TRACE(_T("Write\n"));
				break;
			case RFID_COMMAND_TYPE_18K6C_LOCK:
				temp.Format(TEXT("Lock"));
				TRACE(_T("Lock\n"));
				break;
			case RFID_COMMAND_TYPE_18K6C_KILL:
				temp.Format(TEXT("Kill"));
				TRACE(_T("Kill\n"));
				break;
			default:
				temp.Format(TEXT("Unknown"));
				TRACE(_T("Unknown (%u)\n"), command);
				break;
			}

			strTemp.Format(_T(" #%u Command Beginning"), m_nCmdCount);

			temp += strTemp;

			TRACE(_T("Operation status: (%s)\n"), temp);

			m_pParent->SendMessage(WM_STATUS_MSG,(WPARAM)(LPCTSTR)temp);

			break;
		}
	case RFID_PACKET_TYPE_18K6C_TAG_ACCESS:
		{
			const RFID_PACKET_18K6C_TAG_ACCESS* pTagAccess = (const RFID_PACKET_18K6C_TAG_ACCESS*)packet;
			CONTEXT_PARMS*  pParms = (CONTEXT_PARMS *) context;
			CString			strTemp = TEXT("");

			/* Check to see if the tag access failed                                  */
			if (RFID_18K6C_TAG_ACCESS_ERROR(pTagAccess->cmn.flags))
			{
				if (RFID_18K6C_TAG_BACKSCATTER_ERROR(pTagAccess->cmn.flags))
				{
#ifdef _DEBUG
					TRACE(_T("ERROR: Tag backscattered error 0x%.8x on access\n"), pTagAccess->error_code);
#endif
					switch(pTagAccess->error_code)
					{
					case 0x00:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_BACKSCATTER_00);
							m_pParent->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);
						}
						break;
					case 0x03:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_BACKSCATTER_03);
							m_pParent->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);
						}
						break;
					case 0x04:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_BACKSCATTER_04);
							m_pParent->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);
						}
						break;
					case 0x0B:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_BACKSCATTER_0B);
							m_pParent->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);
						}
						break;
					case 0x0F:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_BACKSCATTER_0F);
							m_pParent->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);
						}
						break;
					}
				}
				else if (RFID_18K6C_TAG_ACCESS_TIMEOUT(pTagAccess->cmn.flags))
				{
#ifdef _DEBUG
					TRACE(_T("ERROR: Timeout waiting for tag to ACK\n"));
#endif
					strTemp.Format(_T("Timeout waiting for tag to ACK"));
					theApp.m_pMainWnd->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);
				}
				else if (RFID_18K6C_TAG_ACCESS_CRC_INVALID(pTagAccess->cmn.flags))
				{
#ifdef _DEBUG
					TRACE(_T("ERROR: Tag response failed CRC check\n"));
#endif
					strTemp.Format(_T("Tag response failed CRC check"));
					theApp.m_pMainWnd->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);
				}
				else
				{
#ifdef _DEBUG
					TRACE(_T("ERROR: MAC responded with error 0x%.8x\n"), MacToHost32(pTagAccess->data[0]));
#endif
					switch(pTagAccess->data[0])
					{
					case 0x01:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_ERROR_01);
						}
						break;
					case 0x02:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_ERROR_02);
						}
						break;
					case 0x03:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_ERROR_03);
						}
						break;
					case 0x04:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_ERROR_04);
						}
						break;
					case 0x05:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_ERROR_05);
						}
						break;
					case 0x06:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_ERROR_06);
						}
						break;
					case 0x07:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_ERROR_07);
						}
						break;
					case 0x0A:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_ERROR_0A);
						}
						break;

					case 0x0B:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_ERROR_0B);
						}
						break;

					case 0x0C:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_ERROR_0C);
						}
						break;

					case 0x0D:
						{
							strTemp.LoadString(IDS_STRING_TAGACCESS_ERROR_0D);
						}
						break;
					default:
						{
							strTemp.Format(TEXT("Undefined Error"));
						}
						break;
					}
					theApp.m_pMainWnd->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);
				}
			}
			else
			{
				/* If it is a read, then extract the data from the packet             */
				switch(pTagAccess->command)
				{
				case RFID_18K6C_TAG_ACCESS_READ:
					{
						/* Calculate the length of the data portion of the packet         */
						INT32U dataLength = 
							/* The length of the packet beyond the common header          */
							MacToHost16(pTagAccess->cmn.pkt_len) * BYTES_PER_LEN_UNIT   + 
							/* Add back in the size of the common header                  */
							sizeof(RFID_PACKET_COMMON)                                  -
							/* Minus the fixed part of the access packet                  */
							sizeof(RFID_PACKET_18K6C_TAG_ACCESS)                        + 
							/* Add back data field in the packet                          */
							sizeof(pTagAccess->data)                                    -
							/* Subtract out the padding bytes                             */
							RFID_18K6C_TAG_ACCESS_PADDING_BYTES(pTagAccess->cmn.flags);
#ifdef _DEBUG
						TRACE(_T("Tag Access : Read %s\n"), CUtil::Hex2Str((INT8U*)pTagAccess->data, dataLength));
#endif

							strTemp.Format(_T("Read Command Success"), CUtil::Hex2Str((INT8U*)pTagAccess->data, dataLength));
							theApp.m_pMainWnd->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);
							
							strTemp.Format(_T("Read Data : %s"), CUtil::Hex2Str((INT8U*)pTagAccess->data, dataLength));
							theApp.m_pMainWnd->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);
//							AfxMessageBox(strTemp);
						break;
					}
				case RFID_18K6C_TAG_ACCESS_WRITE:
					{
						strTemp.Format(TEXT("Write Command Success"));
						theApp.m_pMainWnd->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);

#ifdef _DEBUG
						TRACE(_T("Tag Access : Write\n"));
#endif

						break;
					}
				case RFID_18K6C_TAG_ACCESS_LOCK:
					{
						strTemp.Format(TEXT("Lock Command Success"));
						theApp.m_pMainWnd->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);						
#ifdef _DEBUG
						TRACE(_T("Tag Access : Lock\n"));
#endif
						break;
					}
				case RFID_18K6C_TAG_ACCESS_KILL:
					{
						strTemp.Format(TEXT("Kill Command Success"));
						theApp.m_pMainWnd->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);
#ifdef _DEBUG
						TRACE(_T("Tag Access : Kill\n"));
#endif
						break;
					}
				default:
					{
#ifdef _DEBUG
						TRACE(_T("Tag Access Success\n"));
#endif
						break;
					}
				}

				pParms->operationSucceeded = 1;
			}
//			pParms->operationSucceeded = 1;
			break;
		}
	case RFID_PACKET_TYPE_COMMAND_END:
		{
			RFID_PACKET_COMMAND_END *cmdend = (RFID_PACKET_COMMAND_END *)packet;
			TRACE(_T("Packet type: RFID_PACKET_COMMAND_END\n"));
			TRACE(_T("Operation ended at millisecond %u\n"), MacToHost32(cmdend->ms_ctr));


			CString temp;
			if(cmdend->status)
			{
				temp.Format(_T("Fail to Command End %u / %u sec"), MacToHost32(cmdend->status), MacToHost32(cmdend->ms_ctr));
			}
			else
			{
				temp.Format(_T("#%u Command End"), m_nCmdCount);
			}

			TRACE(_T("Operation status: (%s)\n"), temp);

			// increase inventory count
			m_nCmdCount++;

			break;
		}
	case RFID_PACKET_TYPE_ANTENNA_CYCLE_BEGIN:
		TRACE(_T("Packet type: RFID_PACKET_ANTENNA_CYCLE_BEGIN\n"));
		break;
	case RFID_PACKET_TYPE_ANTENNA_CYCLE_END:
		TRACE(_T("Packet type: RFID_PACKET_ANTENNA_CYCLE_END\n"));
		break;
	case RFID_PACKET_TYPE_ANTENNA_BEGIN:
		{
			RFID_PACKET_ANTENNA_BEGIN *antennabegin = (RFID_PACKET_ANTENNA_BEGIN *)packet;
			TRACE(_T("Packet type: RFID_PACKET_ANTENNA_BEGIN\n"));
			TRACE(_T("Antenna ID: %u\n"), MacToHost32(antennabegin->antenna));

			m_nAntenna = MacToHost32(antennabegin->antenna) + 1;

			break;
		}
	case RFID_PACKET_TYPE_ANTENNA_END:
		{
			TRACE(_T("Packet type: RFID_PACKET_ANTENNA_END\n"));
			break;
		}
	case RFID_PACKET_TYPE_CARRIER_INFO:
		{
			RFID_PACKET_CARRIER_INFO* carrier_info = 
				(RFID_PACKET_CARRIER_INFO *)packet;
			TRACE(_T("Packet type: RFID_PACKET_TYPE_CARRIER_INFO\n"));
			TRACE(_T("Channel ID: %u\n"), MacToHost16(carrier_info->chan));

			m_nChannel = MacToHost16(carrier_info->chan);

			break;
		}
	case RFID_PACKET_TYPE_INVENTORY_CYCLE_BEGIN:
		{
			TRACE(_T("Packet type: RFID_PACKET_INVENTORY_CYCLE_BEGIN\n"));
			break;
		}
	case RFID_PACKET_TYPE_INVENTORY_CYCLE_END:
		{
			TRACE(_T("Packet type: RFID_PACKET_INVENTORY_CYCLE_END\n"));
			break;
		}
	case RFID_PACKET_TYPE_18K6C_INVENTORY_ROUND_BEGIN:
		TRACE(_T("Packet type: RFID_PACKET_18K6C_INVENTORY_ROUND_BEGIN\n"));
		break;
	case RFID_PACKET_TYPE_18K6C_INVENTORY_ROUND_END:
		TRACE(_T("Packet type: RFID_PACKET_18K6C_INVENTORY_ROUND_END\n"));
		break;
	case RFID_PACKET_TYPE_18K6C_INVENTORY:
		{
			RFID_PACKET_18K6C_INVENTORY *inv = 
				(RFID_PACKET_18K6C_INVENTORY *)packet;
			/* Calculate the length of the data portion of the packet         */
			int length =
				/* The length of the packet beyond the common header          */
				(MacToHost16(common->pkt_len)-1) * BYTES_PER_LEN_UNIT -
				/* Add back in the size of the common header                  */
				(common->flags >> 6);

			if(common->flags & 0x01)
				break;

			int padding_byte = (int)(common->flags & 0xC0);

#ifdef _DEBUG
			TRACE(_T("Packet type: RFID_PACKET_18K6C_INVENTORY\n"));
			TRACE(_T("Packet CRC was %s\n"), common->flags & 0x01 ? _T("invalid") : _T("valid"));
			TRACE(_T("Tag was inventoried at millisecond %u\n"), MacToHost32(inv->ms_ctr));
			TRACE(_T("Inventory data length: %u"), length);
			TRACE(_T("Inventory data is: "));
			CUtil::Hex2Str((INT8U *)inv->inv_data, length);
			TRACE(_T("\n"));
			TRACE(_T("read count: %u\n"), inv->count);
			TRACE(_T("trial count: %u\n"), inv->trial_count);
#endif
// 			if(m_radioFilterMode == RFID_RADIO_FILTER_GABAGE)
// 			{
// 
//  				if((length != 28) && (length != 32) && (length != 48))
// 				{
// 					break;
// 				}
// 			}

			POSITION pos = m_listRadio.FindIndex(0);
			CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

			if(pRadio->m_runStatus != RFID_INVENTORY)
			{
				CString strTemp = TEXT("Tag ID : ");
				CTagInfo lpTagInfo;// = new CTagInfo();

				lpTagInfo.SetTagMemory(inv->inv_data);

				strTemp += lpTagInfo.GetTagString();

				theApp.m_pMainWnd->SendMessage(WM_TAG_ACCESS, (WPARAM)(LPCTSTR)strTemp, 0);

#ifdef _WIN32_WCE
				if(m_radioBeepMode == RFID_RADIO_BEEP_MODE_ENABLE)
					m_waveBox->Play(0);
#endif
				break;
			}

			// Tag Data Process
			CTagInfo* lpTagInfo = new CTagInfo();

			lpTagInfo->SetTagMemory(inv->inv_data);
			lpTagInfo->SetTagReadCount(inv->count);
			lpTagInfo->SetTagTrialCount(inv->trial_count);
			lpTagInfo->SetTagAntenna(m_nAntenna);
			lpTagInfo->SetTagChannel(m_nChannel);
			lpTagInfo->SetTagRSSI(MacToHost16(inv->rssi));
			lpTagInfo->SetTagLNAGain(MacToHost16(inv->ana_ctrl1));
			lpTagInfo->SetTagReveiveTime(COleDateTime::GetCurrentTime());

#ifdef _WIN32_WCE
			if(m_radioBeepMode == RFID_RADIO_BEEP_MODE_ENABLE)
				m_waveBox->Play(0);
#endif

			m_pParent->SendMessage(WM_PROCESS_TAG, (WPARAM)lpTagInfo);

			break;

		}

	case RFID_PACKET_TYPE_TEMPERATURE_INFO:
		{
#ifdef _DEBUG
			TRACE(_T("Packet type: RFID_PACKET_TYPE_TEMPERATURE\n"));
#endif
			RFID_PACKET_TEMPERATURE_INFO* temp = (RFID_PACKET_TEMPERATURE_INFO*)packet;
			CString temperature, strDate;
			COleDateTime currentTime = COleDateTime::GetCurrentTime();

#ifdef _DEBUG
			TRACE(_T("Temperature status: (%u)\n"), temp->temperature);
#endif


			// calculate time stamp
			COleDateTimeSpan span = currentTime- m_oleStartDateTime;//COleDateTimeSpan(newTime.wDay, newTime.wHour, newTime.wMinute, newTime.wSecond);

#ifdef _WIN32_WCE
			temperature.Format(_T("(%u) "), temp->temperature);

			strDate.Format(TEXT("%s (%d)"),
				(LPCTSTR)span.Format(TEXT("%H:%M:%S")), span.GetDays());

			temperature += strDate;
#else
			temperature.Format(_T("Temperature status: (%u)\t"), temp->temperature);

			strDate.Format(TEXT("%s and %d days"),
				(LPCTSTR)span.Format(TEXT("%H:%M:%S")), span.GetDays());

			temperature += strDate;
#endif
			file.Write(temperature.GetBuffer(1024), temperature.GetLength() * sizeof(WCHAR));  // Excel 파일 쓰기 
			file.Flush();

			m_pParent->SendMessage(WM_STATUS_MSG,(WPARAM)(LPCTSTR)temperature);

			break;
		}

	default:
		TRACE(_T("Packet type %u not handled yet\n"), packetType);
		break;
	}
}

RFID_STATUS CRFIDRadioManager::GetRadioOperationMode(int nModule, RFID_RADIO_OPERATION_MODE* mode)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetRadioOperationMode(mode)))
			{
				TRACE1("RadioCancelOperation failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;	
}

RFID_STATUS CRFIDRadioManager::SetRadioOperationMode(int nModule, RFID_RADIO_OPERATION_MODE mode)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->SetRadioOperationMode(mode)))
			{
				TRACE1("RadioCancelOperation failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;	
}

RFID_STATUS CRFIDRadioManager::GetRadioResponseDataMode(int nModule, RFID_RESPONSE_MODE* mode)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetRadioResponseDataMode(mode)))
			{
				TRACE1("GetRadioResponseDataMode failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;	
}

RFID_STATUS CRFIDRadioManager::SetRadioResponseDataMode(int nModule, RFID_RESPONSE_MODE mode)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->SetRadioResponseDataMode(mode)))
			{
				TRACE1("SetRadioResponseDataMode failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;	
}


RFID_STATUS CRFIDRadioManager::GetRadioMacRegion(int nModule, RFID_MAC_REGION* region)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetMacRegion(region)))
			{
				TRACE1("GetMacRegion failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;	
}

RFID_STATUS CRFIDRadioManager::SetRadioMacRegion(int nModule, RFID_MAC_REGION region)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->SetMacRegion(region)))
			{
				TRACE1("SetMacRegion failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;	
}

int	CRFIDRadioManager::GetRadioAntennaCount(int nModule)
{
//	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			return pRadio->GetAntennaCount();
	}

	return 0;	
}

RFID_STATUS CRFIDRadioManager::GetRadioAntennaPortStatus(int nModule, int antennaNumber, RFID_ANTENNA_PORT_STATUS* antennaStatus)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetAntennaPortStatus(antennaNumber, antennaStatus)))
			{
				TRACE1("GetAntennaPortStatus failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;	
}

RFID_STATUS CRFIDRadioManager::SetRadioAntennaPortState(int nModule, int antennaNumber, RFID_ANTENNA_PORT_STATE antennaState)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->SetAntennaPortState(antennaNumber, antennaState)))
			{
				TRACE1("SetAntennaPortState failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;	
}

RFID_STATUS CRFIDRadioManager::GetRadioAntennaPortConfiguration(int nModule, int antennaNumber, RFID_ANTENNA_PORT_CONFIG* antennaConf)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetAntennaPortConfiguration(antennaNumber, antennaConf)))
			{
				TRACE1("GetAntennaPortConfiguration failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;	
}

RFID_STATUS CRFIDRadioManager::SetRadioAntennaPortConfiguration(int nModule, int antennaNumber, RFID_ANTENNA_PORT_CONFIG antennaConf)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->SetAntennaPortConfiguration(antennaNumber, antennaConf)))
			{
				TRACE1("SetAntennaPortConfiguration failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;	
}

RFID_STATUS	CRFIDRadioManager::GetRadioTransferTime(int nModule, INT32U* transferTime)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetRadioTransferTime(transferTime)))
			{
				TRACE1("GetRadioTransferTime failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;	
}

RFID_STATUS CRFIDRadioManager::SetRadioTransferTime(int nModule, INT32U transferTime)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->SetRadioTransferTime(transferTime)))
			{
				TRACE1("SetRadioTransferTime failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;	
}

RFID_STATUS	CRFIDRadioManager::GetRadioBeepMode(int nModule, RFID_RADIO_BEEP_MODE* mode)
{
	RFID_STATUS status = RFID_STATUS_OK;

#ifndef _WIN32_WCE
	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetBeepMode(mode)))
			{
				TRACE1("GetBeepMode failed:  RC = %d\n", status);
				return status;
			}

			return status;
	}
#else
	m_radioBeepMode = AfxGetApp()->GetProfileInt(TEXT("WaveBox"), TEXT("Mode"), 0);

	switch(m_radioBeepMode)
	{
	case RFID_RADIO_BEEP_MODE_ENABLE:
		*mode = RFID_RADIO_BEEP_MODE_ENABLE;
		break;
	case RFID_RADIO_BEEP_MODE_DISABLE:
		*mode = RFID_RADIO_BEEP_MODE_DISABLE;
		break;
	}
#endif

	return status;	
}

RFID_STATUS CRFIDRadioManager::SetRadioBeepMode(int nModule, RFID_RADIO_BEEP_MODE mode)
{
	RFID_STATUS status = RFID_STATUS_OK;

#ifndef _WIN32_WCE
	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->SetBeepMode(mode)))
			{
				TRACE1("SetBeepMode failed:  RC = %d\n", status);
				return status;
			}

		return status;
	}
#else
	AfxGetApp()->WriteProfileInt(TEXT("WaveBox"), TEXT("Mode"), mode);
	m_radioBeepMode = mode;
#endif

	return status;	
}

RFID_STATUS CRFIDRadioManager::GetRadioTrialCount(int nModule, INT32U* trial)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetTrialCount(trial)))
			{
				TRACE1("GetTrialCount failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::SetRadioTrialCount(int nModule, INT32U trial)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->SetTrialCount(trial)))
			{
				TRACE1("SetTrialCount failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::GetRadio18K6CCurrentSingulationAlgorithm(int nModule, RFID_18K6C_SINGULATION_ALGORITHM* algorithm)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetCurrentSingulationAlgorithm(algorithm)))
			{
				TRACE1("GetCurrentSingulationAlgorithm failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::SetRadio18K6CCurrentSingulationAlgorithm(int nModule, RFID_18K6C_SINGULATION_ALGORITHM algorithm)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->SetCurrentSingulationAlgorithm(algorithm)))
			{
				TRACE1("SetGetCurrentSingulationAlgorithm failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::SetRadio18K6CQueryTagGroup(int nModule, RFID_18K6C_TAG_GROUP* tagGroup)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->SetQueryTagGroup(tagGroup)))
			{
				TRACE1("SetQueryTagGroup failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::GetRadio18K6CQueryTagGroup(int nModule, RFID_18K6C_TAG_GROUP* tagGroup)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetQueryTagGroup(tagGroup)))
			{
				TRACE1("SetQueryTagGroup failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::SetRadio18K6CQueryParameters(int nModule, RFID_18K6C_QUERY_PARMS* pParms)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->SetQueryParameters(pParms)))
			{
				TRACE1("SetQueryParameters failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::GetRadio18K6CQueryParameters(int nModule, RFID_18K6C_QUERY_PARMS* pParms)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetQueryParameters(pParms)))
			{
				TRACE1("GetQueryParameters failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::SetRadioConfigurationParameter(int nModule, INT16U param, INT32U val)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->SetConfigurationParameter(param, val)))
			{
				TRACE1("SetConfigurationParameter failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;

}

RFID_STATUS CRFIDRadioManager::GetRadioConfigurationParameter(int nModule, INT16U param, INT32U* val)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetConfigurationParameter(param, val)))
			{
				TRACE1("GetConfigurationParameter failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;

}

RFID_STATUS CRFIDRadioManager::GetRadioFirmwareVersion(int nModule, RFID_VERSION* version)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetFirmwareVersion(version)))
			{
				TRACE1("GetFirmwareVersion failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::GetRadioMacVersion(int nModule, RFID_VERSION* version)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetMacVersion(version)))
			{
				TRACE1("GetFirmwareVersion failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}


RFID_STATUS CRFIDRadioManager::RadioCarrierWaveOn(int nModule)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->CarrierWaveOn()))
			{
				TRACE1("CarrierWaveOn failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::RadioCarrierWaveOff(int nModule )
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->CarrierWaveOff()))
			{
				TRACE1("CarrierWaveOff failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}


RFID_STATUS CRFIDRadioManager::Reset(int nModule)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
		{
			if(RFID_STATUS_OK != 
				(status = pRadio->MacReset()))
			{
				TRACE1("MacReset failed:  RC = %d\n", status);
				return status;
			}
		}
	}

	return status;
}


BOOL SetControlState(int nSelectPin, BOOL bState)
{
#ifdef _WIN32_WCE
	try
	{
		SSTWRFIDCTL sstwRfidCtl;

		memset(&sstwRfidCtl, NULL, sizeof(SSTWRFIDCTL));

		// Modified by Youngho Kim
		// Date : 2007/08/22
		// Description : Mobilecompia 전원 인가 방식 수정

		// Pin 제어

		// Original Version
		//sstwRfidCtl.u8SelectPin = (unsigned char)nSelectPin;
		//sstwRfidCtl.u8PinOut = (unsigned char)fState;

		// Modified Version
		sstwRfidCtl.u8SelectPin = nSelectPin; // x = 1~6
		sstwRfidCtl.u8PinOut = bState;    // 0:low, 1:high
		sstwRfidCtl.bReadStatus = 0; // not Read Pin State   

		return KernelIoControl(IOCTL_HAL_SSTW_RFID_CONTROL, &sstwRfidCtl, sizeof(SSTWRFIDCTL), NULL, NULL, NULL);
	}
	catch(CException* e)
	{
		e->ReportError();
		TRACE(_T("Set Control State Error\n"));	
		return FALSE;
	}
#endif // _WIN32_WCE
	return TRUE;
}

BOOL GetControlState(int nSelectPin)
{
#ifdef _WIN32_WCE
	try
	{
		SSTWRFIDCTL		sstwRfidCtl;
		unsigned char	pinIn;
		unsigned long   outSize;

		memset(&sstwRfidCtl, NULL, sizeof(SSTWRFIDCTL));

		// Modified by Youngho Kim
		// Date : 2007/08/22
		// Description : Mobilecompia 전원 인가 방식 수정

		// Pin Read시

		// Original Version
		//sstwRfidCtl.u8SelectPin = (unsigned char)nSelectPin;

		// Modified Version
		sstwRfidCtl.u8SelectPin = nSelectPin;  // x=1~7
		sstwRfidCtl.bReadStatus = 1;  // Read Pin State

		if(!KernelIoControl(IOCTL_HAL_SSTW_RFID_CONTROL, &sstwRfidCtl, sizeof(SSTWRFIDCTL), &pinIn, sizeof(unsigned char), &outSize))
		{
			return FALSE;
		}

		return (BOOL)pinIn;
	}
	catch (CException* e)
	{
		e->ReportError();
		TRACE(_T("Set Control State Error\n"));	
		return FALSE;
	}
#endif // _WIN32_WCE

	return TRUE;
}

BOOL CRFIDRadioManager::SetControlState(int nSelectPin, BOOL bState)
{
	return ::SetControlState(nSelectPin, bState);
}

BOOL CRFIDRadioManager::GetControlState(int nSelectPin)
{
	return ::GetControlState(nSelectPin);
}

RFID_STATUS CRFIDRadioManager::RadioFirmwareUpdate(int nModule, LPCTSTR filename, BOOL skipTestMode, BOOL testModeOnly, CWnd* pParent)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
		{
			CFirmwareUpdate *pUpdate = new CFirmwareUpdate( pRadio->GetRadioHandle(), filename, skipTestMode, testModeOnly, pParent);

			pUpdate->FirmwareUpate();
		}
	}

	return status;
}

RFID_STATUS CRFIDRadioManager::RadioFirmwareUpdate(int nModule, LPCTSTR filename, RFID_RADIO_FIRMWARE_MODE mode, CWnd* pParent)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
		{
			CFirmwareUpdate* pUpdate = new CFirmwareUpdate(pRadio->GetRadioHandle(), filename, mode, pParent);
			pUpdate->FirmwareUpate();
		}
	}

	return status;
}


void CRFIDRadioManager::SetWaveBox(LPCTSTR strPath)
{
	AfxGetApp()->WriteProfileString(TEXT("WaveBox"), TEXT("Path"), strPath);

	if(m_waveBox)
	{
		delete m_waveBox;

		m_waveBox = new CWaveBox();
		m_waveBox->Load((LPTSTR)strPath);
	}
}

RFID_STATUS CRFIDRadioManager::GetFrequencyBand(int nModule, CFrequencyBandList* band)
{
	RFID_STATUS status = RFID_STATUS_OK;

	if( m_pRadioEnum != NULL && m_pRadioEnum->countRadios != 0)
	{
		POSITION pos = m_listRadio.FindIndex(nModule);
		CRFIDRadio* pRadio = (CRFIDRadio*)m_listRadio.GetAt(pos);

		if( pRadio != NULL )
			if(RFID_STATUS_OK != 
				(status = pRadio->GetFrequencyBandList(band)))
			{
				TRACE1("GetFrequencyBandList failed:  RC = %d\n", status);
				return status;
			}
	}

	return status;
}