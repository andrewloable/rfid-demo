// RFRMView.h : interface of the CRFRMView class
//

#pragma once

#include "ListViewEx.h"
#include "SocketClass.h"

// ListView Column Number
#define TAGINFO_EPC				0		
#define TAGINFO_PC				1
#define TAGINFO_TOTAL_COUNT		2
#define	TAGINFO_READ_COUNT		3
#define TAGINFO_TRIAL_COUNT		4
#define TAGINFO_ANTENNA_NUMBER	5
#define TAGINFO_CHANNEL_NUMBER	6
#define TAGINFO_RSSI			7
#define	TAGINFO_LNA				8
#define TAGINFO_RECEIVE_TIME	9

class CRFRMView : public CListViewEx
{
protected: // create from serialization only
	CRFRMView();
	DECLARE_DYNCREATE(CRFRMView)

// Attributes
public:
	CRFRMDoc*			GetDocument() const;
	CPtrList			m_listTempQ;

protected:
	CImageList			m_smallImageList;
	CImageList			m_largeImageList;
	CSocketClass		m_pSocket;

	BOOL				m_bItemClick;
	int					m_nItemClick;

// Operations
public:
	BOOL InsertTagItem(int nItem, int nSubItem, LPCWSTR strItem, int mask =LVIF_TEXT | LVIF_STATE, int iImage = 0);

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CRFRMView();
	DWORD GetViewType();
	BOOL SetViewType(DWORD dwViewType);
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnListIcon();
	afx_msg void OnListList();
	afx_msg void OnListReport();
	afx_msg void OnUpdateListIcon(CCmdUI *pCmdUI);
	afx_msg void OnUpdateListList(CCmdUI *pCmdUI);
	afx_msg void OnUpdateListReport(CCmdUI *pCmdUI);
	afx_msg void OnListSmallIcon();
	afx_msg void OnUpdateListSmallIcon(CCmdUI *pCmdUI);
	LRESULT OnProcessTag(WPARAM wParam = 0, LPARAM lParam = 0);
	LRESULT OnStatusMSg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnClearButton();
//	afx_msg	void OnListContextMenu(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRfidServerconnect();

protected:
	virtual void PostNcDestroy();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual	bool					SortList(int nColumn, bool bAscending);

public:
	void InitListCtrl(void);
	void InsertTagData(CTagInfo* pTagInfo);
	void UpdateTagData(CTagInfo* pTagInfo);
};

#ifndef _DEBUG  // debug version in RFRMView.cpp
inline CRFRMDoc* CRFRMView::GetDocument() const
   { return reinterpret_cast<CRFRMDoc*>(m_pDocument); }
#endif

