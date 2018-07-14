// ../LockThread.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "LockThread.h"


// CLockThread

IMPLEMENT_DYNCREATE(CLockThread, CRunThread)

CLockThread::CLockThread()
{
}

CLockThread::~CLockThread()
{
}

BOOL CLockThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CLockThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CRunThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CLockThread, CRunThread)
END_MESSAGE_MAP()


// CLockThread message handlers
