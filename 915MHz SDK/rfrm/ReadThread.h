#pragma once

#include "RunThread.h"
// CReadThread

class CReadThread : public CRunThread
{
	DECLARE_DYNCREATE(CReadThread)

public:
	CReadThread();
	virtual ~CReadThread();

protected:
	RFID_18K6C_READ_PARMS			m_rfid18K6CReadParms;

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual int Run();
};


