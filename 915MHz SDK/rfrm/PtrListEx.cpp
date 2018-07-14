/*
############################################################################
# Samsung Techwin 					Confidential       #
############################################################################
*/

// TagPtrList.cpp: implementation of the CPtrListEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "PtrListEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

namespace techwin
{
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPtrListEx::CPtrListEx()
{
	::InitializeCriticalSection(&m_cs);
}

CPtrListEx::~CPtrListEx()
{
//	RemoveAll();
	::DeleteCriticalSection(&m_cs);
}

void CPtrListEx::AddTail(void* pObject)
{
	EnterCriticalSection(&m_cs);

	CPtrList::AddTail(pObject);

	LeaveCriticalSection(&m_cs);
}

void* CPtrListEx::RemoveHead()
{
	void* pObject = NULL;

	EnterCriticalSection(&m_cs);

	pObject = CPtrList::RemoveHead();

	LeaveCriticalSection(&m_cs);

	return pObject;
}

void CPtrListEx::RemoveAll()
{
	EnterCriticalSection(&m_cs);

	CPtrList::RemoveAll();

	LeaveCriticalSection(&m_cs);
}

POSITION CPtrListEx::Find(void *pObject)
{
	POSITION pos = NULL;

	EnterCriticalSection(&m_cs);

	pos = CPtrList::Find(pObject);

	LeaveCriticalSection(&m_cs);

	return pos;
}

void CPtrListEx::RemoveAt(POSITION pos)
{
	EnterCriticalSection(&m_cs);

	CPtrList::RemoveAt(pos);

	LeaveCriticalSection(&m_cs);
}

POSITION CPtrListEx::FindIndex( int nIndex )
{
	POSITION pos = NULL;

	EnterCriticalSection(&m_cs);

	pos = CPtrList::FindIndex( nIndex );

	LeaveCriticalSection(&m_cs);

	return pos;
}

DWORD CPtrListEx::GetCount()
{
	DWORD dwCount = 0;

	EnterCriticalSection(&m_cs);

	dwCount = CPtrList::GetCount();

	LeaveCriticalSection(&m_cs);

	return dwCount;
}

void CPtrListEx::RemovePtr(void* pObject)
{
	POSITION pos = NULL;

	EnterCriticalSection(&m_cs);

	pos = CPtrList::Find( pObject );
	if ( pos )
		CPtrList::RemoveAt( pos );

	LeaveCriticalSection(&m_cs);
}

BOOL CPtrListEx::IsEmpty()
{
	BOOL b = 0;
	EnterCriticalSection(&m_cs);

	b = CPtrList::IsEmpty();

	LeaveCriticalSection(&m_cs);
	return b;
}
};