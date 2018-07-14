#pragma once

#include "RunThread.h"

// CWriteThread

class CWriteThread : public CRunThread
{
	DECLARE_DYNCREATE(CWriteThread)

protected:
	CWriteThread();           // protected constructor used by dynamic creation
	virtual ~CWriteThread();

protected:
	RFID_18K6C_WRITE_PARMS			m_rfid18K6CWriteParms;

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


