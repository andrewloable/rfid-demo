#pragma once

#include "RunThread.h"

// CInventoryThread

class CInventoryThread : public CRunThread
{
	DECLARE_DYNCREATE(CInventoryThread)

protected:
	CInventoryThread();           // protected constructor used by dynamic creation
	virtual ~CInventoryThread();

	RFID_18K6C_INVENTORY_PARMS		m_rfid18K6CInventoryParms;
	int								m_rfidIndentlevel;
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();


protected:
	DECLARE_MESSAGE_MAP()
};


