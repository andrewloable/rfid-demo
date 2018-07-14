#include "stdafx.h"
#include "ListCtrlCommon.h"

CListCtrlCommon::CListCtrlCommon()
{
}

CListCtrlCommon::~CListCtrlCommon()
{
}

BOOL CListCtrlCommon::AddItem(int nItem, int nSubItem, LPCWSTR strItem, int mask)
{
	LV_ITEM         lvitem;
	CString			szText;

	memset(&lvitem,0,sizeof(LV_ITEM));
	lvitem.mask = mask;
	lvitem.iItem = nItem;
	lvitem.iSubItem = nSubItem;
	lvitem.pszText = szText.GetBuffer(_tcslen(strItem));
	_tcscpy(lvitem.pszText,(LPCTSTR)strItem);

	if (nSubItem == 0)
	{
		if(InsertItem(&lvitem) == -1) // insert new item
			return false; 
	}
//	else
		return(SetItem(&lvitem)); // modify existing item (the sub-item text)}
}

BOOL CListCtrlCommon::AddColumn(int nItem, LPCWSTR strItem, int width, int nFmt, int nSubItem, int nMask)
{
	return(InsertColumn(nItem, (LPCTSTR)strItem, nFmt, width, nSubItem)!=-1?true:false);
}
