/*
############################################################################
# Samsung Techwin 					Confidential       #
############################################################################
*/

// TagPtrList.h: interface for the CCommPtrList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PTR_LIST_EX_)
#define _PTR_LIST_EX_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace techwin
{

class CPtrListEx  : public CPtrList
{
public:
	CPtrListEx();
	virtual ~CPtrListEx();

private:
	CRITICAL_SECTION	m_cs;

public:
	BOOL				IsEmpty();
	void				RemovePtr(void* pObject);
	void				RemoveAt( POSITION pos);
	POSITION			Find(void* pObject);
	void				RemoveAll();
	void				AddTail(void* pObject);
	void*				RemoveHead();

	POSITION			FindIndex(int nIndex);

	DWORD				GetCount();
};
};

#endif // !defined(_PTR_LIST_EX_)
