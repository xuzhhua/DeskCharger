// DeskCharger.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DeskCharger.h"
#include "DeskChargerDlg.h"
#include "TRACEWIN.H"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeskChargerApp

BEGIN_MESSAGE_MAP(CDeskChargerApp, CWinApp)
	//{{AFX_MSG_MAP(CDeskChargerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeskChargerApp construction

CDeskChargerApp::CDeskChargerApp()
{
	HadSavedHandle = 0;     //初始化设置为已经保存
	IsEnable       = TRUE;  //初始化设置为不禁止
	m_IsWinXP      = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDeskChargerApp object

CDeskChargerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDeskChargerApp initialization

BOOL CDeskChargerApp::InitInstance()
{
	AfxEnableControlContainer();
	MfxTraceInit();  //使得TraceWin生效，仅在Debug模式下有效
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	
	//初始化操作
	//检查是否内存中已经有一个程序实例在运行
	HANDLE m_hMutex = CreateMutex(NULL,TRUE, m_pszAppName); 
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;

	//取得Windows的版本
	m_WinVerCd = GetWindowsVersion(m_IsWinXP);
	if (m_WinVerCd == 0)
	{
		CString MsgStr;
		MsgStr.LoadString(IDS_UNABLEGETVER);
		MessageBox(NULL, MsgStr, NULL, MB_ICONERROR | MB_OK);
		return FALSE;
	}

	//取得Windows的路径
	if (!GetWindowsPath())
	{
		CString MsgStr;
		MsgStr.LoadString(IDS_UNABLEGETPATH);
		MessageBox(NULL, MsgStr, NULL, MB_ICONERROR | MB_OK);
		return FALSE;
	}

	//取得程序是否禁用的标志
	if (!GetEnableStatus())
		return FALSE;

	CDeskChargerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CDeskChargerApp::GetWindowsVersion(BOOL &IsXP)
{
	OSVERSIONINFO CurWinVer;

	CurWinVer.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (!GetVersionEx(&CurWinVer))
		return 0;
	else
	{
		if (CurWinVer.dwMajorVersion >= 5 && CurWinVer.dwMinorVersion >= 1)
		{
			IsXP = TRUE;
		}
		return CurWinVer.dwMajorVersion;
	}
}

BOOL CDeskChargerApp::GetWindowsPath()
{
	if (GetWindowsDirectory(WinPath.GetBuffer(256), 256) == 0)
	{
		WinPath.ReleaseBuffer();
		return FALSE;
	}
	else
	{
		WinPath.ReleaseBuffer();
		return TRUE;
	}
}

BOOL CDeskChargerApp::GetEnableStatus()
{
	//取得程序是否禁用的标志
	CRegExec creEnableApp;
	CRegExec::RegKeyInfo rkiRegInfo;
	CString RegData;
	CString RegValueName;
	unsigned long datalen;
	unsigned char querydata[20];
	unsigned long datatype = REG_SZ;

	//取得CD-ROM的注册表设置信息
	rkiRegInfo.hKey = HKEY_CURRENT_USER;
	rkiRegInfo.lpSubKey = "Software\\DeskChargerMFC";
	rkiRegInfo.lpType = &datatype;
	RegValueName = "IsEnable";
	datalen = 20;
	
	rkiRegInfo.lpQueryValueName = RegValueName.GetBuffer(8);
	RegValueName.ReleaseBuffer(); 
	rkiRegInfo.lpcbData = &datalen;
	rkiRegInfo.lpQueryData = querydata;

	//如果为取得注册表信息的一般错误时，忽略，否则关闭程序 
	if (creEnableApp.GetHotReg(rkiRegInfo) == false && creEnableApp.m_Ret != ERROR_INVALID_FUNCTION)
	{
		AfxMessageBox(creEnableApp.m_ErrInfo);
		CString MsgStr;
		MsgStr.LoadString(IDS_REGERROR);
		MessageBox(NULL, MsgStr, NULL, MB_ICONERROR | MB_OK);
		return FALSE;
	}

	if (creEnableApp.m_Ret == ERROR_INVALID_FUNCTION)
	{
		rkiRegInfo.lpSetValueName = RegValueName;
		rkiRegInfo.dwType = REG_SZ;
		RegData = "1";//初始状态设置为启用
		rkiRegInfo.cbData = 15;
		rkiRegInfo.lpSetData = (CONST BYTE *)RegData.GetBuffer(1);
		RegData.ReleaseBuffer();
		
		if (creEnableApp.SetHotReg(rkiRegInfo) == false)
		{
			//取得注册表信息错误时提示用户并关闭程序
			AfxMessageBox(creEnableApp.m_ErrInfo);
			CString MsgStr;
			MsgStr.LoadString(IDS_REGERROR);
			MessageBox(NULL, MsgStr, NULL, MB_ICONERROR | MB_OK);
			return FALSE;
		}
	}
	else
	{
		RegData = querydata;
		if (RegData.Left(1) == "1")
			IsEnable = TRUE;
		else
			IsEnable = FALSE;
	}

	return TRUE;
}