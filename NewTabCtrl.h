#if !defined(AFX_NEWTABCTRL_H__1C3F3D68_D9CF_4D10_B6CA_989FFD80AEC0__INCLUDED_)
#define AFX_NEWTABCTRL_H__1C3F3D68_D9CF_4D10_B6CA_989FFD80AEC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewTabCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewTabCtrl window

class CNewTabCtrl : public CTabCtrl
{
// Construction
public:
	CNewTabCtrl();
	CDialog *m_tabPages[3/*4*/];
	int m_tabCurrent;
	int m_nNumberOfPages;
// Attributes
public:

// Operations
public:
	void Init();
	void SetRectangle();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewTabCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNewTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNewTabCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWTABCTRL_H__1C3F3D68_D9CF_4D10_B6CA_989FFD80AEC0__INCLUDED_)
