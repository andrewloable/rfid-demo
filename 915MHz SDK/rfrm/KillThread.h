#pragma once

#include "RunThread.h"
// CKillThread

class CKillThread : public CRunThread
{
	DECLARE_DYNCREATE(CKillThread)

protected:
	CKillThread();           // protected constructor used by dynamic creation
	virtual ~CKillThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


