#if !defined(AFX_DLGABOUT_H__B6C96C9E_B04C_4C17_BFA1_5F7CCFF497DD__INCLUDED_)
#define AFX_DLGABOUT_H__B6C96C9E_B04C_4C17_BFA1_5F7CCFF497DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAbout.h : header file
//
#include "HyperLink.h"
#include "ColorStatic.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgAbout dialog

class CDlgAbout : public CDialog
{
// Construction
public:
	CDlgAbout(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CDlgAbout)
	enum { IDD = IDD_ABOUT };
	CColorStatic	m_Declare;
	CColorStatic	m_Version;
	CColorStatic	m_Title;
	CHyperLink	    m_Mailme;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAbout)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAbout)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGABOUT_H__B6C96C9E_B04C_4C17_BFA1_5F7CCFF497DD__INCLUDED_)
