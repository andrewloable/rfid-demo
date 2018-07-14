// ../WriteThread.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "WriteThread.h"


// CWriteThread

IMPLEMENT_DYNCREATE(CWriteThread, CWinThread)

CWriteThread::CWriteThread()
{
}

CWriteThread::~CWriteThread()
{
}

BOOL CWriteThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CWriteThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CWriteThread, CWinThread)
END_MESSAGE_MAP()


// CWriteThread message handlers
