/*
############################################################################
# Samsung Techwin 					Confidential       #
############################################################################
*/

// DataTagList.cpp: implementation of the CDataTagList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CE_RFRM.h"
#include "DataTagList.h"
#include "DataTag.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataTagList::CDataTagList()
{
	m_ReadTotalCnt	= 0;
	m_UpReadTotalCnt = 0;
//	m_TotalRate		= 0;
	::InitializeCriticalSection(&m_cs);
}

CDataTagList::~CDataTagList()
{
	Clear();
//	RemoveAll();
	::DeleteCriticalSection(&m_cs);
}

void CDataTagList::AddTail(void* pObject)
{
	EnterCriticalSection(&m_cs);

	CPtrList::AddTail(pObject);

	LeaveCriticalSection(&m_cs);
}

void* CDataTagList::RemoveHead()
{
	void* pObject = NULL;

	EnterCriticalSection(&m_cs);

	pObject = CPtrList::RemoveHead();

	LeaveCriticalSection(&m_cs);

	return pObject;
}

void CDataTagList::RemoveAll()
{
	EnterCriticalSection(&m_cs);

	CPtrList::RemoveAll();

	LeaveCriticalSection(&m_cs);
}

POSITION CDataTagList::Find(void *pObject)
{
	POSITION pos = NULL;

	EnterCriticalSection(&m_cs);

	pos = CPtrList::Find(pObject);

	LeaveCriticalSection(&m_cs);

	return pos;
}

void CDataTagList::RemoveAt(POSITION pos)
{
	EnterCriticalSection(&m_cs);

	CPtrList::RemoveAt(pos);

	LeaveCriticalSection(&m_cs);
}

POSITION CDataTagList::FindIndex( int nIndex )
{
	POSITION pos = NULL;

	EnterCriticalSection(&m_cs);

	pos = CPtrList::FindIndex( nIndex );

	LeaveCriticalSection(&m_cs);

	return pos;
}

DWORD CDataTagList::GetCount()
{
	DWORD dwCount = 0;

	EnterCriticalSection(&m_cs);

	dwCount = CPtrList::GetCount();

	LeaveCriticalSection(&m_cs);

	return dwCount;
}

void CDataTagList::RemovePtr(void* pObject)
{
	POSITION pos = NULL;

	EnterCriticalSection(&m_cs);

	pos = CPtrList::Find( pObject );
	if ( pos )
		CPtrList::RemoveAt( pos );

	LeaveCriticalSection(&m_cs);
}

BOOL CDataTagList::IsEmpty()
{
	BOOL b = 0;
	EnterCriticalSection(&m_cs);

	b = CPtrList::IsEmpty();

	LeaveCriticalSection(&m_cs);
	return b;
}

void CDataTagList::Clear()
{
	EnterCriticalSection(&m_cs);

	CDataTag* pTagInfo;
	while(!IsEmpty())
	{
		pTagInfo = (CDataTag*)RemoveHead();
		delete pTagInfo;
	}

	RemoveAll();

	LeaveCriticalSection(&m_cs);
}

void CDataTagList::SetAt(POSITION pos, void* pObject)
{
	EnterCriticalSection(&m_cs);

	CPtrList::SetAt(pos, pObject);

	LeaveCriticalSection(&m_cs);
}

void* CDataTagList::GetAt(POSITION pos)
{
	void* pObject = NULL;

	EnterCriticalSection(&m_cs);

	pObject = CPtrList::GetAt(pos);

	LeaveCriticalSection(&m_cs);

	return pObject;
}