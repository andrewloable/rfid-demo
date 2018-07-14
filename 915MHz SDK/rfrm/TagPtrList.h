/*
############################################################################
# Samsung Techwin 					Confidential       #
############################################################################
*/

// TagPtrList.h: interface for the CCommPtrList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TAGTRLIST_H__9AAB01C9_046D_4B74_AB69_4F6619C4CDD0__INCLUDED_)
#define AFX_TAGPTRLIST_H__9AAB01C9_046D_4B74_AB69_4F6619C4CDD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTagPtrList  : public CPtrList
{
public:
	CTagPtrList();
	virtual ~CTagPtrList();

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
public:
	ULONG				m_ReadTotalCnt;	// Count гу╩Й
	ULONG				m_UpReadTotalCnt;
};

#endif // !defined(AFX_TAGPTRLIST_H__9AAB01C9_046D_4B74_AB69_4F6619C4CDD0__INCLUDED_)
