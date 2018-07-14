#pragma once


// CMessageView view

class CMessageView : public CView
{
	DECLARE_DYNCREATE(CMessageView)

protected:
	CMessageView();           // protected constructor used by dynamic creation
	virtual ~CMessageView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

// Attributes
public:
	CEdit m_wndEdit;
// Operations
public:
	CEdit* GetEditCtrl();
	void TextOut(LPCTSTR lpszText);
};


