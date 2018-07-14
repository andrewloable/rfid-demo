// ../InventoryThread.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "InventoryThread.h"


// CInventoryThread

IMPLEMENT_DYNCREATE(CInventoryThread, CRunThread)

CInventoryThread::CInventoryThread()
: m_rfidIndentlevel(0)
{
}

CInventoryThread::~CInventoryThread()
{
}

BOOL CInventoryThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CInventoryThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CRunThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CInventoryThread, CRunThread)
END_MESSAGE_MAP()
// CInventoryThread message handlers

int CInventoryThread::Run()
{
/*	UINT32 flags = 0;
	RFID_STATUS   status = RFID_ERROR_FAILURE;

	if(m_bPerformSelectOpsFlag)
		flags = RFID_FLAG_PERFORM_SELECT;

	if(m_bPerformPostMatchFlag)
		flags |= RFID_FLAG_PERFORM_POST_MATCH;

//	CALLBACK
	do
	{
		// Set up the inventory parameters
		m_rfid18K6CInventoryParms.length                = sizeof(RFID_18K6C_INVENTORY_PARMS);
		m_rfid18K6CInventoryParms.common.tagStopCount   = 0;
		m_rfid18K6CInventoryParms.common.pCallback      = PacketCallbackFunction;
		m_rfid18K6CInventoryParms.common.pCallbackCode  = 0;
		m_rfid18K6CInventoryParms.common.context        = &m_rfidIndentlevel;
		m_rfid18K6CInventoryParms.common.tagStopCount	= 0;
		m_rfid18K6CInventoryParms.common.epc			= NULL;
		m_rfid18K6CInventoryParms.common.sel_flag		= 0;

		// Attempt to perform an inventory on the radio 
		if(RFID_STATUS_OK != 
			(status = RFID_18K6CTagInventory(m_rfidHandle, &m_rfid18K6CInventoryParms, flags)))
		{
			TRACE(_T("RFID_18K6CTagInventory failed: RC = %d\n"),status);
			return -1;
		}


		// 				if(m_bStopRequest)
		// 				{
		// 					break;
		// 				}
	}while (m_nStopCountDown == -1 || // Run forever
		m_nStopCountDown-- > 0);
*/

	return CRunThread::Run();
}
