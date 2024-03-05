// DeskCharger.h : main header file for the DESKCHARGER application
//

#if !defined(AFX_DESKCHARGER_H__5C4505EC_3893_46F0_B552_3BFAEEA494F1__INCLUDED_)
#define AFX_DESKCHARGER_H__5C4505EC_3893_46F0_B552_3BFAEEA494F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
/////////////////////////////////////////////////////////////////////////////
// CDeskChargerApp:
// See DeskCharger.cpp for the implementation of this class
//

class CDeskChargerApp : public CWinApp
{
public:
	CDeskChargerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeskChargerApp)
	public:
	virtual BOOL InitInstance();
	BOOL GetEnableStatus();  //取得应用程序允许状态
	//}}AFX_VIRTUAL

//属性(全局变量)
	int HadSavedHandle;  //用户设置是否已经保存
						 //CD-ROM设置未保存为1
						 //热键设置未保存为2
						 //定时设置未保存为4
	BOOL IsEnable;       //禁止功能
	int  m_WinVerCd;     //保存当前Windows的版本
						 //9X/ME为4
						 //2000/XP为5
	BOOL  m_IsWinXP;     //是否为XP以后版本的Windows
	CString WinPath;     //Windows的系统路径
	int  GetWindowsVersion(BOOL &IsXP);  //获取当前Windows的版本
	BOOL GetWindowsPath();     //获取当前Windows系统路径
// Implementation

	//{{AFX_MSG(CDeskChargerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESKCHARGER_H__5C4505EC_3893_46F0_B552_3BFAEEA494F1__INCLUDED_)
