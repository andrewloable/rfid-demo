#include "StdAfx.h"
#include "MainFrm.h"

#include "RFRMDoc.h"
#include "RFRMView.h"

#include "RFIDRadio.h"
#include "RFIDRadioManager.h"

//static CWnd* pWnd;
static CRFIDRadioManager* parent;

CRFIDRadio::CRFIDRadio(RFID_RADIO_INFO* pRadioInfo, void* pParent)
: AThread()
, m_bEmulated(FALSE)
, m_pRadioInfo(pRadioInfo)
, m_rfidIndentlevel(0)
, m_runStatus(RFID_INVENTORY)
, m_nStopCountDown(-1)
, m_bPerformSelectOpsFlag(FALSE)
, m_bPerformPostMatchFlag(FALSE)
, m_epc(NULL)
{
//	if(pParent->GetSafeHwnd() != NULL)
//		pWnd = pParent;
	
	parent = static_cast<CRFIDRadioManager*>(pParent);
}

CRFIDRadio::~CRFIDRadio(void)
{
}

RFID_STATUS CRFIDRadio::OpenRadio()
{
	RFID_STATUS result;

	/* Open the radio */
	if (RFID_STATUS_OK !=
		(result =
		RFID_RadioOpen(m_pRadioInfo->cookie, &m_rfidHandle, 
		m_bEmulated ? RFID_FLAG_MAC_EMULATION : 0)))
	{
		TRACE1("RFID_RadioOpen failed:  RC = %d\n", result);
		return result;
	}

	// Load Operation Mode data
	if(RFID_STATUS_OK !=
		( result = m_objectOperationMode.Load(this)))
	{
		TRACE1("Load Operation Mode failed:  RC = %d\n", result);
		return result;
	}

//	SetRadioOperationMode(RFID_RADIO_OPERATION_MODE_NONCONTINUOUS);
	SetRadioTransferTime(0);
//	SetRadioResponseDataMode(RFID_RESPONSE_MODE_COMPACT);
/*
	switch (GetSystemDefaultUILanguage()) 
	{ 
	case 0x0412: 
		{
			SetMacRegion(RFID_MAC_REGION_KOREA_FHSS);
			break; 
		}
	case 0x0409: 
		{
			SetMacRegion(RFID_MAC_REGION_FCC_GENERIC);
			break; 
		}
	case 0x0411: 
		{
			SetMacRegion(RFID_MAC_REGION_JAPAN_GENERIC);
			break; 
		}
	default:
		break;
	}
*/
	return result;
}

RFID_STATUS CRFIDRadio::CloseRadio()
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle)
	{
		if( RFID_STATUS_OK != 
			(status = RFID_MacClearError(m_rfidHandle)))
		{
			TRACE1("RFID_MacClearError failed: RC = %d\n",status);
			return status;
		}

		if( RFID_STATUS_OK != 
			(status = RFID_RadioClose(m_rfidHandle)))
		{
			TRACE1("RFID_RadioClose failed: RC = %d\n",status);
			return status;
		}
	}

	return status;
}

CString ByteArrayToCString(
	const INT8U *bytes,
	int length
	)
{
	int index;
	CString stemp, str; 
	str = "";

	for (index = 0; index < length; ++index)
	{
		stemp.Format(_T("%s%.2x"), (index && !(index % 4)) ? _T(" ") : _T(""), bytes[index]);
		//        sprintf((LPSTR)(LPCTSTR)temp, "%s%.2x", (index && !(index % 4)) ? _T(" ") : _T(""), bytes[index]);

		str += stemp;
	}

	return str;
}

void PrintPacket(const INT8U *packet, int indent)
{
	RFID_PACKET_COMMON *common = (RFID_PACKET_COMMON *)packet;
	INT16U packetType = MacToHost16(common->pkt_type);

	switch (packetType)
	{
	case RFID_PACKET_TYPE_COMMAND_BEGIN:
		{
			RFID_PACKET_COMMAND_BEGIN *cmdbegin =
				(RFID_PACKET_COMMAND_BEGIN *)packet;
			INT32U command = MacToHost32(cmdbegin->command);

			TRACE(_T("Packet type: RFID_PACKET_COMMAND_BEGIN\n"));
			CString temp;
			if(common->flags & 1)
				temp.Format(_T(""));
			else
				temp.Format(_T("%s"), "not");
			TRACE(_T("  Operation was %s executed in continuous mode\n"), temp);
			TRACE(_T("  Operation started at millisecond %u\n"), MacToHost32(cmdbegin->ms_ctr));
			TRACE(_T("  Operation that is beginning: "));
			switch (command)
			{
			case RFID_COMMAND_TYPE_18K6C_INVENTORY:
				TRACE(_T("Inventory\n"));
				break;
			case RFID_COMMAND_TYPE_18K6C_READ:
				TRACE(_T("Read\n"));
				break;
			case RFID_COMMAND_TYPE_18K6C_WRITE:
				TRACE(_T("Write\n"));
				break;
			case RFID_COMMAND_TYPE_18K6C_LOCK:
				TRACE(_T("Lock\n"));
				break;
			case RFID_COMMAND_TYPE_18K6C_KILL:
				TRACE(_T("Kill\n"));
				break;
			default:
				TRACE(_T("Unknown (%u)\n"), command);
				break;
			}
			break;
		}
	case RFID_PACKET_TYPE_COMMAND_END:
		{
			CString temp;
			RFID_PACKET_COMMAND_END *cmdend = (RFID_PACKET_COMMAND_END *)packet;
			
			TRACE(_T("Packet type: RFID_PACKET_COMMAND_END\n"));
			TRACE(_T("Operation ended at millisecond %u\n"), MacToHost32(cmdend->ms_ctr));

			if(cmdend->status)
				temp.Format(_T("Failed %s"), MacToHost32(cmdend->status));
			else
				temp.Format(_T("Succeeded"));

			TRACE(_T("Operation status: %u (%s)\n"), MacToHost32(cmdend->status), temp);

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

			break;
		}
	case RFID_PACKET_TYPE_ANTENNA_END:
		TRACE(_T("Packet type: RFID_PACKET_ANTENNA_END\n"));
		break;
	case RFID_PACKET_TYPE_INVENTORY_CYCLE_BEGIN:
		TRACE(_T("Packet type: RFID_PACKET_INVENTORY_CYCLE_BEGIN\n"));
		break;
	case RFID_PACKET_TYPE_INVENTORY_CYCLE_END:
		TRACE(_T("Packet type: RFID_PACKET_INVENTORY_CYCLE_END\n"));
		break;
	case RFID_PACKET_TYPE_18K6C_INVENTORY_ROUND_BEGIN:
		TRACE(_T("Packet type: RFID_PACKET_18K6C_INVENTORY_ROUND_BEGIN\n"));
		break;
	case RFID_PACKET_TYPE_18K6C_INVENTORY_ROUND_END:
		TRACE(_T("Packet type: RFID_PACKET_18K6C_INVENTORY_ROUND_END\n"));
		break;
	case RFID_PACKET_TYPE_18K6C_INVENTORY:
		{
			RFID_PACKET_18K6C_INVENTORY *inv = (RFID_PACKET_18K6C_INVENTORY *)packet;
			int length = (MacToHost16(common->pkt_len)-1)*4 - (common->flags >> 6);

			if(common->flags)
			{
				TRACE(_T("CRC Check Error\n"));
				break;
			}

//			parent->AddRadioPacket(common, packetType);

			break;
		}
	default:
		TRACE(_T("Packet type %u not handled yet\n"), packetType);
		break;
	}
}

INT32S PacketCallbackFunction(RFID_RADIO_HANDLE   handle,
							  INT32U              bufferLength,
							  const INT8U*        pBuffer,
							  void *              context)
{
	INT32S	status = 0;
	int *indent = (int *)context;

	/* Process the packets in the buffer until either the entire buffer is    */
	/* processed.                   
	*/
	while (!status && bufferLength)
	{
		/* Get the packet pointer and determine the length in bytes           */
		RFID_PACKET_COMMON*   pPacket = 
			(RFID_PACKET_COMMON *) pBuffer;
		INT32U packetLength    = 
			(MacToHost16(pPacket->pkt_len) * BYTES_PER_LEN_UNIT) + sizeof(RFID_PACKET_COMMON);

		/* Verify that the buffer is large enough for the packet              */
		if (bufferLength < packetLength )
		{
			TRACE(_T("ERROR: Remaining buffer = %d bytes, need %d bytes\n"),
				bufferLength,
				packetLength);
			status = -1;
		}
		else
		{
			INT16U packetType = 
				MacToHost16(pPacket->pkt_type);

			parent->AddRadioPacket(pPacket, context);

#ifdef _DEBUG_PACKET
			PrintPacket(pBuffer, *context);
#endif	// _DEBUG_PACKET
		}

		/* pkt_len is measured in 4-byte words, and
		doesn't include the 8-byte common preamble */
//		packetLength = MacToHost16(pPacket->pkt_len) * BYTES_PER_LEN_UNIT + 8;

		pBuffer += packetLength;
		bufferLength -= packetLength;
	}

	return status;
}

// Override Virtual Function for Thread
INT CRFIDRadio::Run(void)
{
	if(m_rfidHandle)
	{
		RFID_STATUS   status;
		UINT32 flags = 0;

		if ( m_bPerformSelectOpsFlag )
		{
			flags = 1;  //RFID_FLAG_PERFORM_SELECT
		}

		if ( m_bPerformPostMatchFlag )
		{
			flags |= 2; // RFID_FLAG_PERFORM_POST_MATCH
		}

		switch(m_runStatus)
		{
		case RFID_INVENTORY:
			{
				// Set up the inventory parameters
				m_rfid18K6CInventoryParms.length                = sizeof(RFID_18K6C_INVENTORY_PARMS);
				m_rfid18K6CInventoryParms.common.tagStopCount   = 0;
				m_rfid18K6CInventoryParms.common.pCallback      = PacketCallbackFunction;
				m_rfid18K6CInventoryParms.common.pCallbackCode  = 0;
				m_rfid18K6CInventoryParms.common.context        = &m_rfidIndentlevel;
				m_rfid18K6CInventoryParms.common.epc			= NULL;
				m_rfid18K6CInventoryParms.common.sel_flag		= 0;

				do
				{
					// Attempt to perform an inventory on the radio 
					if(RFID_STATUS_OK != 
						(status = RFID_18K6CTagInventory(m_rfidHandle, &m_rfid18K6CInventoryParms, flags)))
					{
						TRACE(_T("RFID_18K6CTagInventory failed: RC = %d\n"),status);
						break;
					}

					if(!IsActive())
					{
						break;
					}
				}while (m_nStopCountDown == -1 || // Run forever
					m_nStopCountDown-- > 0);
			}
			break;
		case RFID_READ:
			{
				INT8U			readData[EPC_WORD_LENGTH * 2];		// read data buffer : default 128 bit size
				CONTEXT_PARMS	context;							// read context parameter

				// initialize read parameter using input value
				context.operationSucceeded					= 0;
				context.pReadData							= readData;
				m_rfid18K6CReadParms.length					= sizeof(RFID_18K6C_READ_PARMS);
				m_rfid18K6CReadParms.bank					= m_MBank;
				m_rfid18K6CReadParms.count					= m_nCount;
				m_rfid18K6CReadParms.offset					= m_nOffset;
				m_rfid18K6CReadParms.accessPassword			= 0;
				m_rfid18K6CReadParms.common.pCallback		= PacketCallbackFunction;	// read callback function
				m_rfid18K6CReadParms.common.pCallbackCode	= NULL;
				m_rfid18K6CReadParms.common.tagStopCount	= 0;
				m_rfid18K6CReadParms.common.context			= &context;					// read context paramter

				if(m_epc != NULL)
				{
					m_rfid18K6CReadParms.common.epc				= m_epc;
					m_rfid18K6CReadParms.common.sel_flag		= true;
				}

				do
				{
					// Start tag read access process
					if(RFID_STATUS_OK !=
						(status =  RFID_18K6CTagRead(m_rfidHandle, &m_rfid18K6CReadParms, flags)))
					{
						TRACE(_T("RFID_18K6CTagRead failed: RC = %d\n"),status);
						break;
					}

					// Check tag read access success
					if( !IsActive() /*|| context.operationSucceeded ||*/)
					{
						NotifyStop();
// 
// 						if(RFID_STATUS_OK != 
// 							(status = RadioCancelOperation()))
// 						{
// 							TRACE1("RadioAbortOperation failed:  RC = %d\n", status);
// 						}

						break;
					}

				} while ( m_nStopCountDown == -1 || // Run forever
					m_nStopCountDown-- > 0);
			}
			break;
		case RFID_WRITE:
			{
				INT16U			writeData[8];						// write data buffer : default 128 bit size
				CONTEXT_PARMS	context;							// read context parameter

				context.operationSucceeded								= 0;
				context.pWriteData										= writeData;
				m_rfid18K6CWriteParms.length							= sizeof(RFID_18K6C_WRITE_PARMS);
				m_rfid18K6CWriteParms.writeType							= RFID_18K6C_WRITE_TYPE_SEQUENTIAL;
				m_rfid18K6CWriteParms.parameters.sequential.length		= sizeof(RFID_18K6C_WRITE_SEQUENTIAL_PARMS);
				m_rfid18K6CWriteParms.parameters.sequential.bank		= m_MBank;
				m_rfid18K6CWriteParms.parameters.sequential.count		= m_nCount;
				m_rfid18K6CWriteParms.parameters.sequential.offset		= m_nOffset;
				m_rfid18K6CWriteParms.parameters.sequential.pData		= m_nWriteData;
				m_rfid18K6CWriteParms.verify							= 1;
				m_rfid18K6CWriteParms.verifyRetryCount					= 7;
				m_rfid18K6CWriteParms.accessPassword					= 0;
				m_rfid18K6CWriteParms.common.pCallback					= PacketCallbackFunction;
				m_rfid18K6CWriteParms.common.pCallbackCode				= NULL;
				m_rfid18K6CWriteParms.common.tagStopCount				= 0;
				m_rfid18K6CWriteParms.common.context					= &context;

				if(m_epc != NULL)
				{
					m_rfid18K6CWriteParms.common.epc			= m_epc;
					m_rfid18K6CWriteParms.common.sel_flag		= true;
				}

				do
				{
					if(RFID_STATUS_OK !=
						(status =  RFID_18K6CTagWrite(m_rfidHandle, &m_rfid18K6CWriteParms, flags)))
					{
						TRACE(_T("RFID_18K6CTagWrite failed: RC = %d\n"),status);
						break;
					}

					// Check tag read access success
					if( !IsActive() /*|| context.operationSucceeded ||*/)
					{
						NotifyStop();
						break;
					}
				} while ( m_nStopCountDown == -1 || // Run forever
					m_nStopCountDown-- > 0);
			}
			break;
		case RFID_LOCK:
			{
				RFID_18K6C_LOCK_PARMS m_rfid18K6CLockParms;
				CONTEXT_PARMS	context;							// read context parameter

				context.operationSucceeded									= 0;
				m_rfid18K6CLockParms.length									= sizeof(RFID_18K6C_LOCK_PARMS);
				m_rfid18K6CLockParms.common.tagStopCount					= 0;
				m_rfid18K6CLockParms.common.pCallback						= PacketCallbackFunction;
				m_rfid18K6CLockParms.common.pCallbackCode					= NULL;
				m_rfid18K6CLockParms.common.context							= &context;
				m_rfid18K6CLockParms.common.epc								= m_epc;
				m_rfid18K6CLockParms.common.sel_flag						= true;

				m_rfid18K6CLockParms.permissions							= m_lockPermission;
				m_rfid18K6CLockParms.accessPassword							= m_AccessPassword;


				if(m_epc != NULL)
				{
					m_rfid18K6CLockParms.common.epc				= m_epc;
					m_rfid18K6CLockParms.common.sel_flag		= true;
				}

				// 			m_rfid18K6CLockParms.permissions.accessPasswordPermissions = accessPasswordPermissions;
				// 			m_rfid18K6CLockParms.permissions.epcMemoryBankPermissions  = epcMemoryBankPermissions;
				// 			m_rfid18K6CLockParms.permissions.tidMemoryBankPermissions  = tidMemoryBankPermissions;
				// 			m_rfid18K6CLockParms.permissions.userMemoryBankPermissions = userMemoryBankPermissions;

				do
				{
					if(RFID_STATUS_OK !=
						(status =  RFID_18K6CTagLock(m_rfidHandle, &m_rfid18K6CLockParms, flags)))
					{
						TRACE(_T("RFID_18K6CTagLock failed: RC = %d\n"),status);
						break;
					}

					// Check tag read access success
					if( !IsActive() /*|| context.operationSucceeded ||*/)
					{
						NotifyStop();
						break;
					}
				} while ( m_nStopCountDown == -1 || // Run forever
					m_nStopCountDown-- > 0);
			}
			break;
		case RFID_KILL:
			{
				RFID_18K6C_KILL_PARMS m_rfid18K6CKillParms;
				CONTEXT_PARMS	context;							// read context parameter

				context.operationSucceeded								= 0;
				m_rfid18K6CKillParms.common.tagStopCount					= 0;
				m_rfid18K6CKillParms.common.pCallback						= PacketCallbackFunction;
				m_rfid18K6CKillParms.common.pCallbackCode					= NULL;
				m_rfid18K6CKillParms.common.context							= &context;
				m_rfid18K6CKillParms.killPassword							= m_KillPassword;
				m_rfid18K6CKillParms.accessPassword							= m_AccessPassword;

				if(m_epc != NULL)
				{
					m_rfid18K6CKillParms.common.epc				= m_epc;
					m_rfid18K6CKillParms.common.sel_flag		= true;
				}

				do
				{
					if(RFID_STATUS_OK !=
						(status =  RFID_18K6CTagKill(m_rfidHandle, &m_rfid18K6CKillParms, flags)))
					{
						TRACE(_T("RFID_18K6CTagKill failed: RC = %d\n"),status);
						break;
					}

					// Check tag read access success
					if( !IsActive() /*|| context.operationSucceeded ||*/)
					{
						NotifyStop();
						break;
					}
				} while ( m_nStopCountDown == -1 || // Run forever
					m_nStopCountDown-- > 0);
			}
			break;
		}

	}

	m_epc = NULL;

	return 0L;
}

RFID_STATUS CRFIDRadio::RadioCancelOperation(void)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle)
	{
		if( RFID_STATUS_OK != 
			(status = RFID_RadioCancelOperation(m_rfidHandle, 0)))
		{
			TRACE1("RFID_RadioCancelOperation failed: RC = %d\n",status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::RadioAbortOperation(void)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle)
	{
		if( RFID_STATUS_OK != 
			(status = RFID_RadioAbortOperation(m_rfidHandle, 0)))
		{
			TRACE1("RFID_RadioAbortOperation failed: RC = %d\n",status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::SetRadioOperationMode(RFID_RADIO_OPERATION_MODE mode)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(RFID_STATUS_OK !=
		(status = 
		RFID_RadioSetOperationMode(m_rfidHandle, 
		mode)))
	{
		TRACE1("RFID_RadioSetOperationMode failed:  RC = %d\n", status);
		return status;
	}

	return status;
}

RFID_STATUS CRFIDRadio::GetRadioOperationMode(RFID_RADIO_OPERATION_MODE* mode)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
		if(RFID_STATUS_OK !=
			(status = 
			RFID_RadioGetOperationMode(m_rfidHandle, 
			mode)))
		{
			TRACE1("RFID_RadioGetOperationMode failed:  RC = %d\n", status);
			return status;
		}

	return status;
}

RFID_STATUS CRFIDRadio::SetRadioTransferTime(UINT32 time)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(RFID_STATUS_OK !=
		(status = 
		RFID_RadioSetTransferTime(m_rfidHandle, 
		time)))
	{
		TRACE1("RFID_RadioSetTransferTime failed:  RC = %d\n", status);
		return status;
	}

	return status;
}

RFID_STATUS CRFIDRadio::GetRadioTransferTime(UINT32* time)
{
	RFID_STATUS   status = RFID_STATUS_OK;


	if(m_rfidHandle != NULL)
		if(RFID_STATUS_OK !=
			(status = 
			RFID_RadioGetTransferTime(m_rfidHandle, 
			time)))
		{
			TRACE1("RFID_RadioGetTransferTime failed:  RC = %d\n", status);
			return status;
		}

		return status;
}


RFID_STATUS CRFIDRadio::SetRadioResponseDataMode(RFID_RESPONSE_MODE mode)
{
	RFID_STATUS   status = RFID_STATUS_OK;
	RFID_RESPONSE_TYPE	responseType = RFID_RESPONSE_TYPE_DATA;

	if(m_rfidHandle != NULL)
		if(RFID_STATUS_OK !=
			(status = 
			RFID_RadioSetResponseDataMode(m_rfidHandle, responseType,
			mode)))
		{
			TRACE1("RFID_RadioGetResponseDataMode failed:  RC = %d\n", status);
			return status;
		}

		return status;
}

RFID_STATUS CRFIDRadio::GetRadioResponseDataMode(RFID_RESPONSE_MODE* mode)
{
	RFID_STATUS   status = RFID_STATUS_OK;
	RFID_RESPONSE_TYPE	responseType = RFID_RESPONSE_TYPE_DATA;

	if(m_rfidHandle != NULL)
		if(RFID_STATUS_OK !=
			(status = 
			RFID_RadioGetResponseDataMode(m_rfidHandle, responseType,
			mode)))
		{
			TRACE1("RFID_RadioGetResponseDataMode failed:  RC = %d\n", status);
			return status;
		}

	return status;
}

RFID_STATUS CRFIDRadio::SetMacRegion(RFID_MAC_REGION region)
{
	RFID_STATUS   status = RFID_STATUS_OK;

// 	if(m_rfidHandle != NULL)
// 		if(RFID_STATUS_OK !=
// 			(status = 
// 			RFID_MacGetRegion(m_rfidHandle, &region, NULL)))
// 		{
// 			TRACE1("RFID_MacGetRegion failed:  RC = %d\n", status);
// 			return status;
// 		}

	if(m_rfidHandle != NULL)
		if(RFID_STATUS_OK !=
			(status = 
			RFID_MacSetRegion(m_rfidHandle, region,	NULL)))
		{
			TRACE1("RFID_MacSetRegion failed:  RC = %d\n", status);
			return status;
		}

	return status;
}

RFID_STATUS CRFIDRadio::GetMacRegion(RFID_MAC_REGION* region)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
		if(RFID_STATUS_OK !=
			(status = 
			RFID_MacGetRegion(m_rfidHandle, region, NULL)))
		{
			TRACE1("RFID_MacGetRegion failed:  RC = %d\n", status);
			return status;
		}

		return status;
}

int	CRFIDRadio::GetAntennaCount()
{
	RFID_STATUS   status = RFID_STATUS_OK;
	int antenna_count;

	for (antenna_count = 0; RFID_STATUS_OK == status; antenna_count++)
	{
		RFID_ANTENNA_PORT_STATUS antennaPortStatus;

		// Initialize Antenn Information
		int antennaPort = antenna_count;
		antennaPortStatus.length = sizeof(RFID_ANTENNA_PORT_STATUS);

		// Get Antenna Port Status
		status = RFID_AntennaPortGetStatus(m_rfidHandle, antennaPort, &antennaPortStatus);
		if (RFID_STATUS_OK != status)
		{
			TRACE(_T("Antenna #%d: disable\n"), antennaPort);
			break;
		}

		if (RFID_ANTENNA_PORT_STATE_DISABLED == antennaPortStatus.state)
		{
			continue;
		}
	}

	return antenna_count;
}

RFID_STATUS CRFIDRadio::GetAntennaPortStatus(int antennaNumber, RFID_ANTENNA_PORT_STATUS* antennaStatus)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	/* Get the state of each antenna.  For enabled antennas, get the          */
	/* configuration for that antenna.                                        */
//	for (unsigned int antenna_count = 0; RFID_STATUS_OK == status; antenna_count++)
	{
		// Initialize Antenna Information
		antennaStatus->length = sizeof(RFID_ANTENNA_PORT_STATUS);

		// Get Antenna Port Status
		status = RFID_AntennaPortGetStatus(m_rfidHandle, antennaNumber, antennaStatus);
//		if (RFID_STATUS_OK != status)
//		{
//			break;
//		}
#ifdef _DEBUG
		TRACE(_T("Antenna #%d:\n"), antennaNumber);
		TRACE(_T("State: %s\n"), (antennaStatus->state == RFID_ANTENNA_PORT_STATE_DISABLED ? 
			_T("disabled") : _T("enabled")));

		TRACE(_T("Last Antenna Sense Value: %u ohms\n"),
			antennaStatus->antennaSenseValue);

#endif
//		if (RFID_ANTENNA_PORT_STATE_DISABLED == antennaStatus.state)
//		{
//			continue;
//		}
/*
		// Get Antenna Port Configuration
		status = RFID_AntennaPortGetConfiguration(m_rfidHandle, antenna->antennaPort, &(antenna->antennaPortConfig));
		if (RFID_STATUS_OK != status)
		{
			TRACE(_T("ERROR: RFID_AntennaPortGetConfiguration returned 0x%.8x\n"), status);
			return status;
		}

#ifdef _DEBUG
		TRACE(_T("Power Level: %.1f dBm\n"), (double) antenna->antennaPortConfig.powerLevel / 10);
		TRACE(_T("Dwell Time: %u ms\n"), antenna->antennaPortConfig.dwellTime);
		TRACE(_T("Number Inventory Cycles: %u\n"), antenna->antennaPortConfig.numberInventoryCycles);
		TRACE(_T("Physical RX: %u\n"), antenna->antennaPortConfig.physicalRxPort);
		TRACE(_T("\tPhysical TX: %u\n"), antenna->antennaPortConfig.physicalTxPort);
		TRACE(_T("Antenna Sense Threshold (global): %u ohms\n"), antenna->antennaPortConfig.antennaSenseThreshold);
#endif
*/
	}
	
	return status;
}

RFID_STATUS CRFIDRadio::SetAntennaPortState(int antennaNumber, RFID_ANTENNA_PORT_STATE antennaState)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_AntennaPortSetState(m_rfidHandle, antennaNumber, antennaState)))
		{
			TRACE1("RFID_AntennaPortSetState failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::GetAntennaPortConfiguration(int antennaNumber, RFID_ANTENNA_PORT_CONFIG* antennaConf)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		antennaConf->length = sizeof(RFID_ANTENNA_PORT_CONFIG);

		if(RFID_STATUS_OK !=
			(status = 
			RFID_AntennaPortGetConfiguration(m_rfidHandle, antennaNumber, antennaConf)))
		{
			TRACE1("RFID_AntennaPortGetConfiguration failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::SetAntennaPortConfiguration(int antennaNumber, RFID_ANTENNA_PORT_CONFIG antennaConf)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_AntennaPortSetConfiguration(m_rfidHandle, antennaNumber, &antennaConf)))
		{
			TRACE1("RFID_AntennaPortSetConfiguration failed:  RC = %d\n", status);
			return status;
		}
	}
	return status;
}

// Transfer time configuration
RFID_STATUS	CRFIDRadio::GetTransferTime(INT32U* transferTime)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_RadioGetTransferTime(m_rfidHandle, transferTime)))
		{
			TRACE1("RFID_RadioGetTransferTime failed:  RC = %d\n", status);
			return status;
		}
	}
	return status;
}

RFID_STATUS CRFIDRadio::SetTransferTime(INT32U transferTime)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_RadioSetTransferTime(m_rfidHandle, transferTime)))
		{
			TRACE1("RFID_RadioSetTransferTime failed:  RC = %d\n", status);
			return status;
		}
	}
	return status;
}

// Transfer time configuration
RFID_STATUS	CRFIDRadio::GetBeepMode(RFID_RADIO_BEEP_MODE* mode)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_RadioGetBeepMode(m_rfidHandle, mode)))
		{
			TRACE1("RFID_RadioGetBeepMode failed:  RC = %d\n", status);
			return status;
		}
	}
	return status;
}

RFID_STATUS CRFIDRadio::SetBeepMode(RFID_RADIO_BEEP_MODE mode)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_RadioSetBeepMode(m_rfidHandle, mode)))
		{
			TRACE1("RFID_RadioSetTransferTime failed:  RC = %d\n", status);
			return status;
		}
	}
	return status;
}

// trail count configuration
RFID_STATUS CRFIDRadio::GetTrialCount(INT32U* trial)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_MacGetTrialMaxCount(m_rfidHandle, trial)))
		{
			TRACE1("RFID_MacGetTrialMaxCount failed:  RC = %d\n", status);
			return status;
		}
	}
	return status;

}

RFID_STATUS CRFIDRadio::SetTrialCount(INT32U trial)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_MacSetTrialMaxCount(m_rfidHandle, trial)))
		{
			TRACE1("RFID_MacSetTrialMaxCount failed:  RC = %d\n", status);
			return status;
		}
	}
	return status;
}

RFID_STATUS CRFIDRadio::SetCurrentSingulationAlgorithm(RFID_18K6C_SINGULATION_ALGORITHM algorithm)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_18K6CSetCurrentSingulationAlgorithm(m_rfidHandle, algorithm)))
		{
			TRACE1("RFID_18K6CSetCurrentSingulationAlgorithm failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::GetCurrentSingulationAlgorithm(RFID_18K6C_SINGULATION_ALGORITHM* algorithm)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_18K6CGetCurrentSingulationAlgorithm(m_rfidHandle, algorithm)))
		{
			TRACE1("RFID_18K6CGetCurrentSingulationAlgorithm failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

// Query Tag Group
RFID_STATUS CRFIDRadio::SetQueryTagGroup(RFID_18K6C_TAG_GROUP* tagGroup)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_18K6CSetQueryTagGroup(m_rfidHandle, tagGroup)))
		{
			TRACE1("RFID_18K6CSetQueryTagGroup failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::GetQueryTagGroup(RFID_18K6C_TAG_GROUP* tagGroup)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_18K6CGetQueryTagGroup(m_rfidHandle, tagGroup)))
		{
			TRACE1("RFID_18K6CGetQueryTagGroup failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::SetQueryParameters(RFID_18K6C_QUERY_PARMS* pParms)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_18K6CSetQueryParameters(m_rfidHandle, pParms, 0)))
		{
			TRACE1("RFID_18K6CSetQueryParameters failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::GetQueryParameters(RFID_18K6C_QUERY_PARMS* pParms)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_18K6CGetQueryParameters(m_rfidHandle, pParms)))
		{
			TRACE1("RFID_18K6CGetQueryParameters failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::SetConfigurationParameter(INT16U parameter, INT32U value)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_RadioSetConfigurationParameter(m_rfidHandle, parameter, value)))
		{
			TRACE1("RFID_RadioSetConfigurationParameter failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::GetConfigurationParameter(INT16U parameter, INT32U* value)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_RadioGetConfigurationParameter(m_rfidHandle, parameter, value)))
		{
			TRACE1("RFID_RadioGetConfigurationParameter failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::GetFirmwareVersion(RFID_VERSION* version)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_MacGetFirmwareVersion(m_rfidHandle, version)))
		{
			TRACE1("RFID_MacGetFirmwareVersion failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::GetMacVersion(RFID_VERSION* version)
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_MacGetVersion(m_rfidHandle, version)))
		{
			TRACE1("RFID_MacGetVersion failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}



RFID_STATUS	CRFIDRadio::MacReset()
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_MacReset(m_rfidHandle, RFID_MAC_RESET_TYPE_SOFT)))
		{
			TRACE1("RFID_MacReset failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS	CRFIDRadio::CarrierWaveOn()
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_RadioTurnCarrierWaveOn(m_rfidHandle)))
		{
			TRACE1("RFID_RadioTurnCarrierWaveOn failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS	CRFIDRadio::CarrierWaveOff()
{
	RFID_STATUS   status = RFID_STATUS_OK;

	if(m_rfidHandle != NULL)
	{
		if(RFID_STATUS_OK !=
			(status = 
			RFID_RadioTurnCarrierWaveOff(m_rfidHandle)))
		{
			TRACE1("RFID_RadioTurnCarrierWaveOff failed:  RC = %d\n", status);
			return status;
		}
	}

	return status;
}

RFID_STATUS CRFIDRadio::GetFrequencyBandList(CFrequencyBandList* band)
{
	RFID_STATUS status  = RFID_STATUS_OK;
	// Load Frequency Bands
	if(RFID_STATUS_OK !=
		(status = band->Load(this)))
	{
		TRACE1("Load Radio Frequency failed:  RC = %d\n", status);
		return status;
	}

	return status;
}

RFID_STATUS CRFIDRadio::SetFrequencyBandList(CFrequencyBandList band)
{
	RFID_STATUS status  = RFID_STATUS_OK;
	// Load Frequency Bands
	if(RFID_STATUS_OK !=
		(status = band.Store(this)))
	{
		TRACE1("Store Radio Frequency failed:  RC = %d\n", status);
		return status;
	}

	return status;
}