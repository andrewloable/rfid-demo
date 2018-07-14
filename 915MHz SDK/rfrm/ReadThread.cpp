// ../ReadThread.cpp : implementation file
//

#include "stdafx.h"
#include "RFRM.h"
#include "ReadThread.h"

#include "RFIDRadio.h"

// CReadThread

IMPLEMENT_DYNCREATE(CReadThread, CWinThread)

CReadThread::CReadThread()
{

}

CReadThread::~CReadThread()
{
}


BOOL CReadThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CReadThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}


BEGIN_MESSAGE_MAP(CReadThread, CWinThread)
END_MESSAGE_MAP()



// CReadThread message handlers



int CReadThread::Run()
{
	// TODO: Add your specialized code here and/or call the base class

	return CRunThread::Run();
}
