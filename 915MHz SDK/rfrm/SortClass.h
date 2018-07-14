// Copyright (c) Iuri Apollonio 1998
// Use & modify as you want & need, and leave those 3 lines.
// http://www.codeguru.com
// class extended by Max Poliashenko.

// CJSortClass.h: interface for the CSortClass class.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef __CJSORTCLASS_H__
#define __CJSORTCLASS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// enumeration data type for sorting
typedef enum DATA_TYPE
{
	DT_INT = 1,		// sort type int
	DT_STRING,		// sort type string
	DT_DATETIME,	// sort type date / time
	DT_DEC			// sort type decimal
};


namespace techwin
{
// This class will sort a List control by a column of text, integer, float or
// date/time type. It could be easily extended for other data types.
class CSortClass  
{

public:

	// Default constructor
	//
	CSortClass(CListCtrl* pWnd, const int nCol);

	// Virtual destructor
	//
	virtual ~CSortClass();

public:

	// this member function is call to peform the actual sort
	// proceedure.
	//
	virtual void Sort(bool bAsc, DATA_TYPE eType);

protected:

	CListCtrl* m_pWnd;	// pointer to the CListCtrl object to peform sort on
	
	// this callback member function is called to compare to data items
	// during sorting operations
	//
	static int CALLBACK Compare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	
	// helper struct used during sorting operations
	//
	struct CSortItem
	{
		CSortItem(const DWORD dwData, const CString &strItemText);
		DWORD	m_dwData;
		CString m_strItemText;
	};
};

/////////////////////////////////////////////////////////////////////////////
//	Inline Functions
/////////////////////////////////////////////////////////////////////////////

inline CSortClass::CSortItem::CSortItem(const DWORD dwData, const CString & strItemText)
	{ m_dwData  = dwData; m_strItemText = strItemText; }
};
#endif // __CJSORTCLASS_H__
