// ../RunThread.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "RunThread.h"

#include "RFIDRadioManager.h"

//static CRFIDRadioManager* CRunThread::m_pParent;

// CRunThread

IMPLEMENT_DYNCREATE(CRunThread, CWinThread)

CRunThread::CRunThread()
: m_bPerformSelectOpsFlag(FALSE)
, m_bPerformPostMatchFlag(FALSE)
{
//	parent = static_cast<CRFIDRadioManager*>(m_pParent);
}

CRunThread::~CRunThread()
{
}

BOOL CRunThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CRunThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CRunThread, CWinThread)
END_MESSAGE_MAP()


// CRunThread message handlers
INT32S RFID_CALLBACK CRunThread::PacketCallbackFunction(RFID_RADIO_HANDLE   handle,
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

			m_pParent->AddRadioPacket(pPacket, context);

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