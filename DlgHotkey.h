#if !defined(AFX_DLGHOTKEY_H__4F6A2D82_4B67_467F_A849_529ECD0F5B52__INCLUDED_)
#define AFX_DLGHOTKEY_H__4F6A2D82_4B67_467F_A849_529ECD0F5B52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHotkey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHotkey dialog
#include "HotKeyExec.h"
#include "BtnST.h"
#include "BCMenu.h"
#include "WinXPButtonST.h"

class CDlgHotkey : public CDialog
{
// Construction
public:
	CDlgHotkey(CWnd* pParent = NULL);   // standard constructor
	~CDlgHotkey();
	void InitDlgBtn();
	void InitLstBox();
	void SetLstData(long idxKey, BOOL IsInFunc = FALSE, BOOL IsRefresh = TRUE);
	void InitHotkeys();
	void AdjustTokenPrivilegesForNT();  //2000/XP系统取得关机权限
	void LoadScreenSaverFor9X();        //9X中启动屏幕保护程序
	void CreatePopMenu();               //建立弹出式菜单
	void SaveInHotSettings();           //保存并更新内置热键设置信息
	int  GetHotKeyID(int iCombinKey, int ivKeyIdx);  //取得热键的ID号
	void SaveHotSetting();              //保存并更新用户热键设置信息

// Dialog Data
	//{{AFX_DATA(CDlgHotkey)
	enum { IDD = IDD_HOTKEY };
	CListCtrl	m_HotkeyLst;
	CComboBox	m_ComKeySel;
	CWinXPButtonST	m_SaveHotkey;
	CWinXPButtonST	m_ReadHotkey;
	CWinXPButtonST	m_EditHotkey;
	CWinXPButtonST	m_DelHotkey;
	CWinXPButtonST	m_AddHotkey;
	//}}AFX_DATA

	bool        m_IsSetting;
	CHotKeyExec m_HotkeyExec;
	CImageList  m_CilIcon;
	BCMenu      m_LstPopMenu;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHotkey)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual void OnCancel();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHotkey)
	virtual BOOL OnInitDialog();
	afx_msg void OnLstEnable();
	afx_msg void OnSavehotkeyinfo();
	afx_msg void OnSelchangeCombokeyselect();
	afx_msg void OnRclickHotkeylist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLstaddnew();
	afx_msg void OnLstedit();
	afx_msg void OnAddhotkeynew();
	afx_msg void OnEdithotkeyinfo();
	afx_msg void OnReadhotkeyinfo();
	afx_msg void OnLstdelcur();
	afx_msg void OnDelhotkeyinfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHOTKEY_H__4F6A2D82_4B67_467F_A849_529ECD0F5B52__INCLUDED_)
