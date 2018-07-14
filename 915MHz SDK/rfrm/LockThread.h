#pragma once

#include "RunThread.h"

// CLockThread

class CLockThread : public CRunThread
{
	DECLARE_DYNCREATE(CLockThread)

protected:
	CLockThread();           // protected constructor used by dynamic creation
	virtual ~CLockThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


