#if !defined(AFX_DLGCDROM_H__42995FA1_8912_4C16_928F_73DEB5166BB3__INCLUDED_)
#define AFX_DLGCDROM_H__42995FA1_8912_4C16_928F_73DEB5166BB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCDROM.h : header file
//
#include "HECDROM.H"

#include "BtnST.h"
#include "WinXPButtonST.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgCDROM dialog

class CDlgCDROM : public CDialog
{
// Construction
public:
	CDlgCDROM(CWnd* pParent = NULL);   // standard constructor
	~CDlgCDROM();

// Dialog Data
	//{{AFX_DATA(CDlgCDROM)
	enum { IDD = IDD_CDROM };
	CWinXPButtonST	m_SetDefaultCDROM;
	CWinXPButtonST	m_SetCDROMHotkey;
	CWinXPButtonST	m_SetCDROMDefault;
	CHotKeyCtrl	m_CDROMHotKey;
	CEdit	    m_AutoClose;
	CButton     m_AutoEject;
	CComboBox	m_CDROMLab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCDROM)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	CHotCDROMExec m_HotCDROM;
	bool m_IsSetting;

	void SetCDROMItemValue(BOOL IsInit = FALSE);  //设置对话框控件的值

	// Generated message map functions
	//{{AFX_MSG(CDlgCDROM)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCdromlab();
	afx_msg void OnSetdefaultcdrom();
	afx_msg void OnSetcdromdefault();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSetcdromhotkey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCDROM_H__42995FA1_8912_4C16_928F_73DEB5166BB3__INCLUDED_)
