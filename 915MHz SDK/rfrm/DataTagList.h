/*
############################################################################
# Samsung Techwin 					Confidential       #
############################################################################
*/

// DataTagList.h: interface for the CDataTagList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATATAGLIST_H__FA86FE8E_0494_48F5_B1FF_BCE26AEED299__INCLUDED_)
#define AFX_DATATAGLIST_H__FA86FE8E_0494_48F5_B1FF_BCE26AEED299__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataTagList : public CPtrList  
{
public:
	CDataTagList();
	virtual ~CDataTagList();

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

	void				Clear();
	void				SetAt(POSITION pos, void* pObject);
	void*				GetAt(POSITION pos);

	POSITION			FindIndex(int nIndex);

	DWORD				GetCount();

public:
	ULONG				m_ReadTotalCnt;	// ReadCount 합산
	ULONG				m_UpReadTotalCnt;
//	float				m_TotalRate;	// 모든 Tag의 Rate 평균값
};

#endif // !defined(AFX_DATATAGLIST_H__FA86FE8E_0494_48F5_B1FF_BCE26AEED299__INCLUDED_)
