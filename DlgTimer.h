#if !defined(AFX_DLGTIMER_H__3A6223A7_0405_44BE_BDE9_8518EA797EDD__INCLUDED_)
#define AFX_DLGTIMER_H__3A6223A7_0405_44BE_BDE9_8518EA797EDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTimer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTimer dialog
#include "HETime.h"
#include "BtnST.h"
#include "BCMenu.h"
#include "WinXPButtonST.h"

class CDlgTimer : public CDialog
{
// Construction
public:
	CDlgTimer(CWnd* pParent = NULL);   // standard constructor
	void InitDlgBtn();
	void InitLstBox();
	void CreatePopMenu();              //建立弹出式菜单
	
// Dialog Data
	//{{AFX_DATA(CDlgTimer)
	enum { IDD = IDD_TIMER };
	CListCtrl	m_TimeLst;
	CWinXPButtonST	m_StartTime;
	CWinXPButtonST	m_SaveTime;
	CWinXPButtonST	m_ReadTime;
	CWinXPButtonST	m_EditTime;
	CWinXPButtonST	m_DelTime;
	CWinXPButtonST	m_AddTimeNew;
	//}}AFX_DATA

	bool        m_IsSetting;
	CTimeExec   m_TimeExec;
	CImageList  m_CilIcon;
	BCMenu      m_LstPopMenu;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTimer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTimer)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnReadtimeinfo();
	virtual BOOL OnInitDialog();
	afx_msg void OnSavetimeinfo();
	afx_msg void OnRclickTimelist(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTIMER_H__3A6223A7_0405_44BE_BDE9_8518EA797EDD__INCLUDED_)

