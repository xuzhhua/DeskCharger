// DeskChargerDlg.h : header file
//

#if !defined(AFX_DESKCHARGERDLG_H__9392BD73_6E0C_4011_A24D_EAC1F6FD4F84__INCLUDED_)
#define AFX_DESKCHARGERDLG_H__9392BD73_6E0C_4011_A24D_EAC1F6FD4F84__INCLUDED_

#include "NewTabCtrl.h"
#include "HECDROM.H"
#include "DlgShutDown.h"

#include "BtnST.h"
#include "BCMenu.h"
#include "WinXPButtonST.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_TRAYMOUSE_MSG     WM_USER + 101
#define ID_DESKCHARGER_TRAY  255
#define IDT_HIDEWINDOW       275
/////////////////////////////////////////////////////////////////////////////
// CDeskChargerDlg dialog

class CDeskChargerDlg : public CDialog
{
// Construction
public:
	CDeskChargerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDeskChargerDlg)
	enum { IDD = IDD_DESKCHARGER_DIALOG };
	CButton		m_AutoRun;
	CWinXPButtonST	m_CloseDlg;
	CNewTabCtrl	m_MainTabCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeskChargerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void CreateMyPopMenu();   //建立弹出式菜单
	virtual void CreateTrayIcon();    //建立系统托盘图标信息
	virtual void GetAutoRunInfo();    //取得自动执行信息
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	NOTIFYICONDATA m_TrayIcon;
	BCMenu TrayPop;
	BOOL m_AlreadyEjected;
	CHotCDROMExec m_TrayCDROM;

	struct stAutoEject
	{
		CHotCDROMExec * pTrayCDROM;
		HWND          * pHwnd;
	};

	stAutoEject stAE;

	static UINT AutoEjectThread(LPVOID);
	// Generated message map functions
	//{{AFX_MSG(CDeskChargerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnExit();
	afx_msg void OnHelp();
	afx_msg void OnOption();
	afx_msg void OnUninst();
	afx_msg void OnEnable();
	afx_msg BOOL OnQueryEndSession(WPARAM wReserved, LPARAM lEndReason);
	afx_msg void OnAutorun();
	afx_msg void OnTaskBarCreated(WPARAM wp, LPARAM lp);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESKCHARGERDLG_H__9392BD73_6E0C_4011_A24D_EAC1F6FD4F84__INCLUDED_)
