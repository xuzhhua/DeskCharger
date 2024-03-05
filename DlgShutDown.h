#if !defined(AFX_DLGSHUTDOWN_H__F881BEDB_BB39_425D_936A_EB3B3EDF3E2A__INCLUDED_)
#define AFX_DLGSHUTDOWN_H__F881BEDB_BB39_425D_936A_EB3B3EDF3E2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgShutDown.h : header file
//

#include "BtnST.h"
#include "WinXPButtonST.h"
#include "DlgShutDown.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgShutDown dialog

class CDlgShutDown : public CDialog
{
// Construction
public:
	CDlgShutDown(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgShutDown)
	enum { IDD = IDD_SHUTDOWN };
	CWinXPButtonST	m_Restart;
	CWinXPButtonST	m_ShutDown;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgShutDown)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void AdjustTokenPrivilegesForNT();  //2000/XP系统取得关机权限
	
	// Generated message map functions
	//{{AFX_MSG(CDlgShutDown)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnRestart();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSHUTDOWN_H__F881BEDB_BB39_425D_936A_EB3B3EDF3E2A__INCLUDED_)
