#pragma once

#include "IconPropertySheet.h"

// CReaderSetSheet

class CReaderSetSheet : public CIconPropertySheet
{
	DECLARE_DYNAMIC(CReaderSetSheet)

public:
	CReaderSetSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CReaderSetSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CReaderSetSheet();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};


