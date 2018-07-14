#ifndef __TOOLBAREX_H__
#define __TOOLBAREX_H__

namespace techwin
{


class CSTWToolBar : public CToolBar
{
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarWithCombo)
	//}}AFX_VIRTUAL

	BOOL			CreateComboBox(class CComboBox& comboBox, UINT nIndex, UINT nID, int nWidth, int nDropHeight);
	BOOL			CreateEdit(CEdit& edit, UINT nIndex, UINT nID, int nWidth);
	BOOL			CreateCheckButton(CButton& button, UINT nIndex, UINT nID, int nWidth);

// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarWithCombo)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

}
#endif // __TOOLBAREX_H__
