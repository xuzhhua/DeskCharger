#if !defined(AFX_HKADDEDIT_H__AE80CC62_37D7_4A8F_8AD0_C52C50A76701__INCLUDED_)
#define AFX_HKADDEDIT_H__AE80CC62_37D7_4A8F_8AD0_C52C50A76701__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HKAddEdit.h : header file
//
#include "HotKeyExec.h"
#include "BtnST.h"
#include "BCMenu.h"
#include "WinXPButtonST.h"
/////////////////////////////////////////////////////////////////////////////
// CHKAddEdit dialog

class CHKAddEdit : public CDialog
{
// Construction
public:

	CHKAddEdit(CWnd* pParent = NULL);   // standard constructor
	CHKAddEdit(CArray<CHotKeyExec::HotKeyInfo, CHotKeyExec::HotKeyInfo> &NewHotKeyInfo, CHotKeyExec::AddNumInfo m_NewNumInfo, CWnd* pParent = NULL);  //新建热键时的建构函数
	CHKAddEdit(CHotKeyExec::HotKeyInfo &EditHotKeyInfo, CWnd* pParent = NULL);  //编辑的热键时的建构函数
// Dialog Data
	//{{AFX_DATA(CHKAddEdit)
	enum { IDD = IDD_HOTKEYADDEDIT };
	CButton		m_KeyShift;
	CButton		m_KeyAlt;
	CEdit		m_HTIInfo;
	CWinXPButtonST	m_AddEdit;
	CWinXPButtonST	m_Close;
	CWinXPButtonST	m_ListFiles;
	CButton		m_KeyCtrl;
	CEdit		m_HTIParm;
	CEdit		m_HTICmd;
	BOOL		m_IsAdd;
	CHotKeyExec::AddNumInfo	m_NumInfo;
	//}}AFX_DATA
	CArray<CHotKeyExec::HotKeyInfo, CHotKeyExec::HotKeyInfo> *m_pHKIAddNew;  //新建热键的信息存储数组指针
	CHotKeyExec::HotKeyInfo *m_pHKIEdit;  //编辑热键的信息存储变量指针

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHKAddEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHKAddEdit)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnListfiles();
	afx_msg void OnAddedit();
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocusHticmd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HKADDEDIT_H__AE80CC62_37D7_4A8F_8AD0_C52C50A76701__INCLUDED_)
