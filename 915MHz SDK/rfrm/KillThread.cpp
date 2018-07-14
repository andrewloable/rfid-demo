// ../KillThread.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "KillThread.h"


// CKillThread

IMPLEMENT_DYNCREATE(CKillThread, CWinThread)

CKillThread::CKillThread()
{
}

CKillThread::~CKillThread()
{
}

BOOL CKillThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CKillThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CKillThread, CWinThread)
END_MESSAGE_MAP()


// CKillThread message handlers
