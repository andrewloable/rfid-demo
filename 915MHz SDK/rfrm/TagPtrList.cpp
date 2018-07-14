/*
############################################################################
# Samsung Techwin 					Confidential       #
############################################################################
*/

// TagPtrList.cpp: implementation of the CTagPtrList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "TagPtrList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTagPtrList::CTagPtrList()
{
	::InitializeCriticalSection(&m_cs);
}

CTagPtrList::~CTagPtrList()
{
	RemoveAll();
	::DeleteCriticalSection(&m_cs);
}

void CTagPtrList::AddTail(void* pObject)
{
	EnterCriticalSection(&m_cs);

	CPtrList::AddTail(pObject);

	LeaveCriticalSection(&m_cs);
}

void* CTagPtrList::RemoveHead()
{
	void* pObject = NULL;

	EnterCriticalSection(&m_cs);

	pObject = CPtrList::RemoveHead();

	LeaveCriticalSection(&m_cs);

	return pObject;
}

void CTagPtrList::RemoveAll()
{
	EnterCriticalSection(&m_cs);

	CPtrList::RemoveAll();

	LeaveCriticalSection(&m_cs);
}

POSITION CTagPtrList::Find(void *pObject)
{
	POSITION pos = NULL;

	EnterCriticalSection(&m_cs);

	pos = CPtrList::Find(pObject);

	LeaveCriticalSection(&m_cs);

	return pos;
}

void CTagPtrList::RemoveAt(POSITION pos)
{
	EnterCriticalSection(&m_cs);

	CPtrList::RemoveAt(pos);

	LeaveCriticalSection(&m_cs);
}

POSITION CTagPtrList::FindIndex( int nIndex )
{
	POSITION pos = NULL;

	EnterCriticalSection(&m_cs);

	pos = CPtrList::FindIndex( nIndex );

	LeaveCriticalSection(&m_cs);

	return pos;
}

DWORD CTagPtrList::GetCount()
{
	DWORD dwCount = 0;

	EnterCriticalSection(&m_cs);

	dwCount = CPtrList::GetCount();

	LeaveCriticalSection(&m_cs);

	return dwCount;
}

void CTagPtrList::RemovePtr(void* pObject)
{
	POSITION pos = NULL;

	EnterCriticalSection(&m_cs);

	pos = CPtrList::Find( pObject );
	if ( pos )
		CPtrList::RemoveAt( pos );

	LeaveCriticalSection(&m_cs);
}

BOOL CTagPtrList::IsEmpty()
{
	BOOL b = 0;
	EnterCriticalSection(&m_cs);

	b = CPtrList::IsEmpty();

	LeaveCriticalSection(&m_cs);
	return b;
}
