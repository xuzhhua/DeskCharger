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
	BOOL GetEnableStatus();  //ȡ��Ӧ�ó�������״̬
	//}}AFX_VIRTUAL

//����(ȫ�ֱ���)
	int HadSavedHandle;  //�û������Ƿ��Ѿ�����
						 //CD-ROM����δ����Ϊ1
						 //�ȼ�����δ����Ϊ2
						 //��ʱ����δ����Ϊ4
	BOOL IsEnable;       //��ֹ����
	int  m_WinVerCd;     //���浱ǰWindows�İ汾
						 //9X/MEΪ4
						 //2000/XPΪ5
	BOOL  m_IsWinXP;     //�Ƿ�ΪXP�Ժ�汾��Windows
	CString WinPath;     //Windows��ϵͳ·��
	int  GetWindowsVersion(BOOL &IsXP);  //��ȡ��ǰWindows�İ汾
	BOOL GetWindowsPath();     //��ȡ��ǰWindowsϵͳ·��
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
