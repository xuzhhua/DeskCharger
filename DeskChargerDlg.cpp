// DeskChargerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DeskCharger.h"
#include "DeskChargerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT WM_TASKBARCREATED = ::RegisterWindowMessage(_T("TaskbarCreated"));
/////////////////////////////////////////////////////////////////////////////
// CDeskChargerDlg dialog

CDeskChargerDlg::CDeskChargerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeskChargerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeskChargerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_AlreadyEjected = FALSE;
}

void CDeskChargerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeskChargerDlg)
	DDX_Control(pDX, IDC_AUTORUN, m_AutoRun);
	DDX_Control(pDX, IDC_CLOSE, m_CloseDlg);
	DDX_Control(pDX, IDC_MAINTAB, m_MainTabCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDeskChargerDlg, CDialog)
	//{{AFX_MSG_MAP(CDeskChargerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_COMMAND(IDM_HELP, OnHelp)
	ON_COMMAND(IDM_OPTION, OnOption)
	ON_COMMAND(IDM_UNINST, OnUninst)
	ON_COMMAND(IDM_ENABLE, OnEnable)
	ON_MESSAGE(WM_QUERYENDSESSION, OnQueryEndSession)
	ON_BN_CLICKED(IDC_AUTORUN, OnAutorun)
    ON_REGISTERED_MESSAGE(WM_TASKBARCREATED, OnTaskBarCreated)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeskChargerDlg message handlers

BOOL CDeskChargerDlg::OnInitDialog()
{
	COLORREF	m_shBtnColor = RGB(255,255,210)/*30*/;

	CDialog::OnInitDialog();
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		//��ֹʹ�ùرհ�ť�Ͳ˵�
		pSysMenu->EnableMenuItem(IDM_CLOSE, MF_BYPOSITION || MF_DISABLED);
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	//��ʼ����ҳ�ؼ�
	CString StrTmp;
	StrTmp.LoadString(IDS_TABCDROMSET);
	m_MainTabCtrl.InsertItem(0, StrTmp);
	StrTmp.LoadString(IDS_TABHOTKEYSET);
	m_MainTabCtrl.InsertItem(1, StrTmp);
	/*StrTmp.LoadString(IDS_TABTIMINGSET);
	m_MainTabCtrl.InsertItem(2, StrTmp);*/
	StrTmp.LoadString(IDS_TABABOUT);
	m_MainTabCtrl.InsertItem(2, StrTmp);
	m_MainTabCtrl.Init();

	//��������ʽ�˵�
	CreateMyPopMenu();
	//��ʼ��ϵͳ������Ϣ
	CreateTrayIcon();
    //ȡ���Զ�ִ����Ϣ
	GetAutoRunInfo();
	
	//��ʼ���رհ�ť
	m_CloseDlg.SetIcon(IDI_CLOSEDLG);
	m_CloseDlg.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_CloseDlg.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);
	m_CloseDlg.SetTooltipText(IDS_CLOSEDLG);

	CenterWindow();
	ShowWindow(SW_MINIMIZE);
	
	::SetTimer(this->m_hWnd, IDT_HIDEWINDOW, 50, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDeskChargerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDeskChargerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDeskChargerDlg::OnOK() 
{
	// TODO: Add extra validation here
	//CDialog::OnOK();
}

void CDeskChargerDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	//CDialog::OnCancel();
}

void CDeskChargerDlg::OnClose() 
{
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();
	CString MsgStr, tmpStr, EndStr, StartStr;
	EndStr.LoadString(IDS_PLEASESAVE);
	StartStr.LoadString(IDS_NOTSAVED); 

	switch (app->HadSavedHandle) 
	{
	case 0:
		//���ضԻ���
		ShowWindow(SW_MINIMIZE);
		ShowWindow(SW_HIDE);
		break;
	case 1:
		MsgStr.LoadString(IDS_CDROMNOTSAVED);
		MsgStr += EndStr;
		MsgStr = StartStr + MsgStr;
		MessageBox(MsgStr, NULL, MB_ICONINFORMATION | MB_OK);
		break;
	case 2:
		MsgStr.LoadString(IDS_HOTCMDNOTSAVED);
		MsgStr += EndStr;
		MsgStr = StartStr + MsgStr;
		MessageBox(MsgStr, NULL, MB_ICONINFORMATION | MB_OK);
		break;
	case 3:
		MsgStr.LoadString(IDS_CDROMNOTSAVED);
		tmpStr.LoadString(IDS_HOTCMDNOTSAVED);
		MsgStr += tmpStr + EndStr;
		MsgStr = StartStr + MsgStr;
		MessageBox(MsgStr, NULL, MB_ICONINFORMATION | MB_OK);
		break;
	case 4:
		MsgStr.LoadString(IDS_TIMINGNOTSAVED);
		MsgStr += EndStr;
		MsgStr = StartStr + MsgStr;
		MessageBox(MsgStr, NULL, MB_ICONINFORMATION | MB_OK);
		break;
	case 5:
		MsgStr.LoadString(IDS_CDROMNOTSAVED);
		tmpStr.LoadString(IDS_TIMINGNOTSAVED);
		MsgStr += tmpStr + EndStr;
		MsgStr = StartStr + MsgStr;
		MessageBox(MsgStr, NULL, MB_ICONINFORMATION | MB_OK);
		break;
	case 6:
		MsgStr.LoadString(IDS_HOTCMDNOTSAVED);
		tmpStr.LoadString(IDS_TIMINGNOTSAVED);
		MsgStr += tmpStr + EndStr;
		MsgStr = StartStr + MsgStr;
		MessageBox(MsgStr, NULL, MB_ICONINFORMATION | MB_OK);
		break;
	case 7:
		MsgStr.LoadString(IDS_CDROMNOTSAVED);
		tmpStr.LoadString(IDS_HOTCMDNOTSAVED);
		MsgStr += tmpStr;
		tmpStr.LoadString(IDS_TIMINGNOTSAVED);
		MsgStr += tmpStr + EndStr;
		MsgStr = StartStr + MsgStr;
		MessageBox(MsgStr, NULL, MB_ICONINFORMATION | MB_OK);
		break;
	}
}

void CDeskChargerDlg::OnExit() 
{
	//�˳�����
	Shell_NotifyIcon(NIM_DELETE, &m_TrayIcon);
	TrayPop.DestroyMenu();
	CDialog::OnCancel();
	//SendMessage(WM_CANCEL);
}

void CDeskChargerDlg::OnHelp() 
{
	//��ʾ�����ļ�
	CString strFileInfo;
	CString strShortFilePath;
	
	if (GetModuleFileName(NULL, strFileInfo.GetBuffer(255), 255) == 0)
	{
		CString StrTmp;
		StrTmp.LoadString(IDS_GETAPPNAMEERR);
		AfxMessageBox(StrTmp);
		return;
	}
	strFileInfo.ReleaseBuffer();
	
	//��ó���·���Ķ���
	GetShortPathName(strFileInfo.GetBuffer(255), strShortFilePath.GetBuffer(255), 255);
	strFileInfo.ReleaseBuffer();
	strShortFilePath.ReleaseBuffer();
	
	//ȡ���ļ�����·��
	int iPos;
	iPos = strShortFilePath.ReverseFind('\\');
	iPos = strShortFilePath.GetLength() - iPos;
	strShortFilePath = strShortFilePath.Left(strShortFilePath.GetLength() - iPos + 1);

	HINSTANCE hiRet = ShellExecute(NULL, "open", strShortFilePath + "ReadMe.pdf", NULL, NULL, SW_SHOW);

	if ((int)hiRet == ERROR_FILE_NOT_FOUND || (int)hiRet == ERROR_PATH_NOT_FOUND)
	{
		CString StrTmp;
		StrTmp.LoadString(IDS_NOFILEDIRERR);
		AfxMessageBox(StrTmp);
		return;
	}

	if ((int)hiRet <= 32)
	{
		CString StrTmp;
		StrTmp.LoadString(IDS_EXECERR);
		AfxMessageBox(StrTmp);
		return;
	}
}

void CDeskChargerDlg::OnOption()
{
	//��ԭ�Ի���
	ShowWindow(SW_SHOW);
	Sleep(1);
	ShowWindow(SW_RESTORE);
	CenterWindow();
}

void CDeskChargerDlg::OnUninst() 
{
	//�ṩɾ����������������Ϣ�Ĺ���
	CString strInfo;
	CString strFileInfo;
	CString strShortFilePath;
	CString strShortFileName;
	CString strUnistName;
	CString strUnistRegName;
	CString strReadMeName;
    char buffer[20];

	strInfo.LoadString(IDS_UNISTINFO);
	if (MessageBox(strInfo, NULL, MB_ICONQUESTION | MB_YESNO) == IDNO)
	{
		//�û�ѡ�񡰷�ʱֱ�ӷ���
		return;
	}
	
	//ɾ��ע����Զ�ִ����Ϣ
	CRegExec creAutoRun;
	CRegExec::RegKeyInfo rkiRegInfo;
	CString RegData;
	CString RegValueName;
	
	RegValueName = "DeskChargerMFC";
	rkiRegInfo.dwType = REG_SZ;
	rkiRegInfo.cbData = 255;
	rkiRegInfo.lpSetValueName = RegValueName;
	rkiRegInfo.hKey = HKEY_CURRENT_USER;
	rkiRegInfo.lpSubKey = "software\\microsoft\\windows\\currentversion\\run";

	if (creAutoRun.SetHotReg(rkiRegInfo, true) == false)
	{
		if (creAutoRun.m_Ret != 1)
		{
			AfxMessageBox(creAutoRun.m_ErrInfo);
			return;
		}
	}
	
	//����ɾ��������������ļ�
	//ȡ�ñ������·��
	if (GetModuleFileName(NULL, strFileInfo.GetBuffer(255), 255) == 0)
	{
		CString StrTmp;
		StrTmp.LoadString(IDS_GETAPPNAMEERR);
		AfxMessageBox(StrTmp);
		return;
	}
	strFileInfo.ReleaseBuffer();
	
	//��ó���·���Ķ���
	GetShortPathName(strFileInfo.GetBuffer(255), strShortFilePath.GetBuffer(255), 255);
	strFileInfo.ReleaseBuffer();
	strShortFilePath.ReleaseBuffer();
	
	//ȡ���ļ�����·��
	int iPos;
	iPos = strShortFilePath.ReverseFind('\\');
	iPos = strShortFilePath.GetLength() - iPos;
	strShortFileName = strShortFilePath;
	strShortFilePath = strShortFilePath.Left(strShortFilePath.GetLength() - iPos + 1);

	//ȡ��ϵͳʱ��
	SYSTEMTIME stCurTime;
	GetLocalTime(&stCurTime);

	//ȡ��˵���ļ�����
	strReadMeName = strShortFilePath + "ReadMe.pdf";
	//ȡ�÷���װ�ļ���
	strUnistName = strShortFilePath + "Unist";
	_itoa(stCurTime.wYear, buffer, 10);
	strUnistName = strUnistName + buffer;
	_itoa(stCurTime.wMonth, buffer, 10);
	strUnistName = strUnistName + buffer;
	_itoa(stCurTime.wDay, buffer, 10);
	strUnistName = strUnistName + buffer;
	_itoa(stCurTime.wHour, buffer, 10);
	strUnistName = strUnistName + buffer;
	_itoa(stCurTime.wMinute, buffer, 10);
	strUnistName = strUnistName + buffer;
	_itoa(stCurTime.wSecond, buffer, 10);
	strUnistName = strUnistName + buffer;
	_itoa(stCurTime.wMilliseconds, buffer, 10);
	strUnistName = strUnistName + buffer;
	
	strUnistRegName = strUnistName + ".reg";
    strUnistName = strUnistName + ".bat";
	//TRACE1("filename=%s\n", strShortFileName);
	
	//��������װע�����Ϣ�ļ�
	strInfo.LoadString(IDS_UNISTREGECHO);
	
	CFile UnistRegFile;
	CFileException exReg;
	if (!UnistRegFile.Open(strUnistRegName, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive, &exReg))
	{
		TCHAR szErrorReg[1024];
		exReg.GetErrorMessage(szErrorReg, 1024);
		AfxMessageBox(szErrorReg, NULL, MB_OK | MB_ICONWARNING);
		return;
	}
	UnistRegFile.Write(strInfo, strInfo.GetLength());
	
	UnistRegFile.Close();
	
	//��������װ�ļ�
	strInfo.LoadString(IDS_UNISTECHO);

	CFile UnistFile;
	CFileException exUnist;
	if (!UnistFile.Open(strUnistName, CFile::modeCreate | CFile::modeWrite | CFile::shareExclusive, &exUnist))
	{
		TCHAR szErrorUnist[1024];
		exUnist.GetErrorMessage(szErrorUnist, 1024);
		AfxMessageBox(szErrorUnist, NULL, MB_OK | MB_ICONWARNING);
		return;
	}

	//��ʾͷ����Ϣ
	UnistFile.Write(strInfo, strInfo.GetLength());
	//����ע�������ļ�
	UnistFile.Write("regedit /s ", 11);
    UnistFile.Write(strUnistRegName, strUnistRegName.GetLength());
	UnistFile.Write("\r\n", 2);
	//����������ļ���˵���ļ�����
	UnistFile.Write("attrib -a -r -s -h ", 19);
	UnistFile.Write(strShortFileName, strShortFileName.GetLength());
	UnistFile.Write("\r\n", 2);
	UnistFile.Write("attrib -a -r -s -h ", 19);
	UnistFile.Write(strReadMeName, strReadMeName.GetLength());
	UnistFile.Write("\r\n", 2);
	//ɾ���������ļ�
	UnistFile.Write("del ", 4);
	UnistFile.Write(strShortFileName, strShortFileName.GetLength());
	UnistFile.Write("\r\n", 2);
	//ɾ��ע�������ļ�
    UnistFile.Write("del ", 4);
	UnistFile.Write(strUnistRegName, strUnistRegName.GetLength());
    UnistFile.Write("\r\n", 2);
	//ɾ��˵���ļ�
    UnistFile.Write("del ", 4);
	UnistFile.Write(strReadMeName, strReadMeName.GetLength());
    UnistFile.Write("\r\n", 2);
	//ɾ�����ļ�
	UnistFile.Write("del ", 4);
	UnistFile.Write(strUnistName, strUnistName.GetLength());
	UnistFile.Write("\r\n", 2);
	
	UnistFile.Close();
	
	HINSTANCE hiRet = ShellExecute(NULL, "open", strUnistName, NULL, NULL, SW_SHOW);
	if ((int)hiRet == ERROR_FILE_NOT_FOUND || (int)hiRet == ERROR_PATH_NOT_FOUND)
	{
		CString StrTmp;
		StrTmp.LoadString(IDS_NOFILEDIRERR);
		AfxMessageBox(StrTmp);
		return;
	}
	
	if ((int)hiRet <= 32)
	{
		CString StrTmp;
		StrTmp.LoadString(IDS_EXECERR);
		AfxMessageBox(StrTmp);
		return;
	}
	OnExit();
}

void CDeskChargerDlg::OnEnable() 
{
	//��ֹ����
	CRegExec creEnableApp;
	CRegExec::RegKeyInfo rkiRegInfo;
	CString RegData;
	CString RegValueName;

	//ȡ��CD-ROM��ע���������Ϣ
	rkiRegInfo.hKey = HKEY_CURRENT_USER;
	rkiRegInfo.lpSubKey = "Software\\DeskChargerMFC";
	RegValueName = "IsEnable";
	rkiRegInfo.lpSetValueName = RegValueName;
	rkiRegInfo.dwType = REG_SZ;
	rkiRegInfo.cbData = 15;

	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();
	if (app->IsEnable)
	{
		//����ϵͳ����ͼ��
		m_TrayIcon.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
		if (app->m_IsWinXP)
			m_TrayIcon.hIcon = AfxGetApp()->LoadIcon(IDI_TRAYABNORMALXP);
		else
			m_TrayIcon.hIcon = AfxGetApp()->LoadIcon(IDI_TRAYABNORMAL);
		Shell_NotifyIcon(NIM_MODIFY, &m_TrayIcon);
		//�޸Ĳ˵�״̬
		TrayPop.CheckMenuItem(IDM_ENABLE, MF_BYCOMMAND | MF_CHECKED);
		app->IsEnable = FALSE;

		RegData = "0";//״̬����Ϊ����
		rkiRegInfo.lpSetData = (CONST BYTE *)RegData.GetBuffer(1);
		RegData.ReleaseBuffer();
		
		if (creEnableApp.SetHotReg(rkiRegInfo) == false)
			AfxMessageBox(creEnableApp.m_ErrInfo);
	}
	else
	{
		//����ϵͳ����ͼ��
		m_TrayIcon.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
		if (app->m_IsWinXP)
			m_TrayIcon.hIcon = AfxGetApp()->LoadIcon(IDI_TRAYNORMALXP);
		else
			m_TrayIcon.hIcon = AfxGetApp()->LoadIcon(IDI_TRAYNORMAL);
		Shell_NotifyIcon(NIM_MODIFY, &m_TrayIcon);
		//�޸Ĳ˵�״̬
		TrayPop.CheckMenuItem(IDM_ENABLE, MF_BYCOMMAND | MF_UNCHECKED);
		app->IsEnable = TRUE;

		RegData = "1";//״̬����Ϊ����
		rkiRegInfo.lpSetData = (CONST BYTE *)RegData.GetBuffer(1);
		RegData.ReleaseBuffer();
		
		if (creEnableApp.SetHotReg(rkiRegInfo) == false)
			AfxMessageBox(creEnableApp.m_ErrInfo);
	}
}

LRESULT CDeskChargerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();
	int i, RetCDROM;
	//����ϵͳ���̵��Ҽ��˵�
	if (app->HadSavedHandle == 0 && message == WM_TRAYMOUSE_MSG && lParam == WM_RBUTTONDOWN && wParam == ID_DESKCHARGER_TRAY)
	{
		POINT p;
		GetCursorPos(&p);
		SetForegroundWindow();
		TrayPop.TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this );
	}

	//���������/�ر���CD-ROM
	if (message == WM_TRAYMOUSE_MSG && lParam == WM_LBUTTONDOWN && wParam == ID_DESKCHARGER_TRAY && app->IsEnable == TRUE)
	{
		m_TrayCDROM.GetCDROMRegInfo(m_TrayCDROM.m_CDROMInfo);

		for (i = 0; i < m_TrayCDROM.m_CDROMInfo.GetSize(); i++)
		{
			if (m_TrayCDROM.m_CDROMInfo[i].m_IsMainCDROM == true)
			{
				RetCDROM = m_TrayCDROM.SetCDROMDoor(m_TrayCDROM.m_CDROMInfo[i].m_CDROMName);
				if (m_TrayCDROM.m_CDROMInfo[i].m_IsAutoClose == true && RetCDROM == 0)
				{
					//ȡ��ָ��CD-ROM���Զ��ر�ʱ��
					long TimeInterval = m_TrayCDROM.m_CDROMInfo[i].m_AutoCloseTime * 1000; 
					::SetTimer(this->m_hWnd, (IDT_CDROM + i), TimeInterval, NULL);
					break;
				}
			}
		}
	}

	//��ʱ������
	if (message == WM_TIMER && wParam >= IDT_CDROM && wParam < IDT_ALLCDROM)
	{
		m_TrayCDROM.GetCDROMRegInfo(m_TrayCDROM.m_CDROMInfo);
		m_TrayCDROM.SetCDROMDoor(m_TrayCDROM.m_CDROMInfo[wParam - IDT_CDROM].m_CDROMName, true);
		::KillTimer(this->m_hWnd, wParam);
	}

	if (message == WM_TIMER && wParam == IDT_HIDEWINDOW)
	{
		ShowWindow(SW_HIDE);
		::KillTimer(this->m_hWnd, IDT_HIDEWINDOW);
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CDeskChargerDlg::OnQueryEndSession(WPARAM wReserved, LPARAM lEndReason)
{
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();
	
    if (lEndReason == ENDSESSION_LOGOFF || app->IsEnable == FALSE)
	{
        // user is logging off
		return TRUE;
	}
    else
	{
        // Windows is going down

		if (m_AlreadyEjected == TRUE)
		{
			return TRUE;
		}

		BOOL isAnyCDIn = FALSE;
		m_TrayCDROM.GetCDROMRegInfo(m_TrayCDROM.m_CDROMInfo);
		//������������й���δȡ������ִ����ʾ�߳�
		for (int i = 0; i < m_TrayCDROM.m_CDROMInfo.GetSize(); i++)
		{
			if (m_TrayCDROM.m_CDROMInfo[i].m_IsAutoEjectbeforeShutdown == true)
			{
				if (m_TrayCDROM.IsDriverReady(m_TrayCDROM.m_CDROMInfo[i].m_CDROMName) == CHCE_DRIVER_READY)
				{
					isAnyCDIn = TRUE;
				}
			}
		}

		if (isAnyCDIn == FALSE)
		{
			return TRUE;
		}

		m_AlreadyEjected = TRUE;
		//Shell_NotifyIcon(NIM_DELETE, &m_TrayIcon);
		//TrayPop.DestroyMenu();
		app->HadSavedHandle = 255;
		
		CWinThread * pThread;
		stAE.pTrayCDROM = &m_TrayCDROM;
		stAE.pHwnd = &(this->m_hWnd);
		pThread = AfxBeginThread(CDeskChargerDlg::AutoEjectThread, &stAE);
		
		return FALSE;
	}

}

void CDeskChargerDlg::CreateMyPopMenu()
{
	CString StrTmp;

	//��������ʽ�˵�
	TrayPop.CreatePopupMenu();
	StrTmp.LoadString(IDS_MENUENABLE); 
	TrayPop.AppendMenu(MF_STRING, IDM_ENABLE, StrTmp);
	StrTmp.LoadString(IDS_MENUOPTION); 
	TrayPop.AppendMenu(MF_STRING, IDM_OPTION, StrTmp);
	TrayPop.AppendMenu(MF_SEPARATOR);
	StrTmp.LoadString(IDS_MENUHELP); 
	TrayPop.AppendMenu(MF_STRING, IDM_HELP, StrTmp);
	StrTmp.LoadString(IDS_MENUUNINST); 
	TrayPop.AppendMenu(MF_STRING, IDM_UNINST, StrTmp);
	TrayPop.AppendMenu(MF_SEPARATOR);
	StrTmp.LoadString(IDS_MENUEXIT); 
	TrayPop.AppendMenu(MF_STRING, IDM_EXIT, StrTmp);

	TrayPop.SetMenuDrawMode(TRUE);
	TrayPop.SetBitmapBackground(RGB(0, 128, 128));
	TrayPop.SetIconSize(16, 15);
	TrayPop.LoadToolbar(IDR_TOOLBAR);
}

void CDeskChargerDlg::CreateTrayIcon()
{
	CString StrTmp;
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();

	//��ʼ������ͼ����Ϣ
	StrTmp.LoadString(IDS_TRAYINFOTITLE); 
	m_TrayIcon.cbSize = sizeof(NOTIFYICONDATA);
	if (app->m_IsWinXP)
		m_TrayIcon.hIcon = AfxGetApp()->LoadIcon(IDI_TRAYNORMALXP);
	else
		m_TrayIcon.hIcon = AfxGetApp()->LoadIcon(IDI_TRAYNORMAL);

	m_TrayIcon.hWnd = this->m_hWnd;
	strcpy(m_TrayIcon.szTip, StrTmp);
	strcpy(m_TrayIcon.szInfoTitle, StrTmp);
	m_TrayIcon.uID = ID_DESKCHARGER_TRAY;
	m_TrayIcon.uCallbackMessage = WM_TRAYMOUSE_MSG;
	m_TrayIcon.uFlags = NIF_INFO | NIF_ICON | NIF_TIP | NIF_MESSAGE;
	m_TrayIcon.uTimeout = 1000;
	m_TrayIcon.dwInfoFlags = NIIF_INFO;
	StrTmp.LoadString(IDS_TRAYINFO); 
	strcpy(m_TrayIcon.szInfo, StrTmp);

	//���ͼ�굽ϵͳ����
	Shell_NotifyIcon(NIM_ADD, &m_TrayIcon);

	//�������Ϊ��ֹ״̬
	if (!app->IsEnable)
	{
		//����ϵͳ����ͼ��
		if (app->m_IsWinXP)
			m_TrayIcon.hIcon = AfxGetApp()->LoadIcon(IDI_TRAYABNORMALXP);
		else
			m_TrayIcon.hIcon = AfxGetApp()->LoadIcon(IDI_TRAYABNORMAL);
		
		m_TrayIcon.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
		Shell_NotifyIcon(NIM_MODIFY, &m_TrayIcon);
		//�޸Ĳ˵�״̬
		TrayPop.CheckMenuItem(IDM_ENABLE, MF_BYCOMMAND | MF_CHECKED);
	}
}

void CDeskChargerDlg::OnAutorun() 
{
	CRegExec creAutoRun;
	CRegExec::RegKeyInfo rkiRegInfo;
	CString RegData;
	CString RegValueName;
	
	RegValueName = "DeskChargerMFC";
	rkiRegInfo.dwType = REG_SZ;
	rkiRegInfo.cbData = 255;
	rkiRegInfo.lpSetValueName = RegValueName;
	rkiRegInfo.hKey = HKEY_CURRENT_USER;
	rkiRegInfo.lpSubKey = "software\\microsoft\\windows\\currentversion\\run";

	//�������Ƿ��Զ����б�����
	if (m_AutoRun.GetCheck() == 1)
	{
		//ȡ�ó���ȫ��
		if (GetModuleFileName(NULL, RegData.GetBuffer(255), 255) == 0)
		{
			CString StrTmp;
			StrTmp.LoadString(IDS_GETAPPNAMEERR);
			AfxMessageBox(StrTmp);
			return;
		}
		RegData.ReleaseBuffer();
		rkiRegInfo.lpSetData = (CONST BYTE *)RegData.GetBuffer(255);
		RegData.ReleaseBuffer();

		if (creAutoRun.SetHotReg(rkiRegInfo) == false)
		{
			AfxMessageBox(creAutoRun.m_ErrInfo);
		}		
	}
	else
	{
		//ɾ���Զ�ִ����Ϣ
		if (creAutoRun.SetHotReg(rkiRegInfo, true) == false)
		{
			AfxMessageBox(creAutoRun.m_ErrInfo);
		}		
	}
}

void CDeskChargerDlg::GetAutoRunInfo()
{
	CRegExec creAutoRun;
	CRegExec::RegKeyInfo rkiRegInfo;
	CString RegData;
	CString RegValueName;
	unsigned long datalen;
	unsigned char querydata[255];
	unsigned long datatype = REG_SZ;

	//ȡ��CD-ROM��ע���������Ϣ
	rkiRegInfo.hKey = HKEY_CURRENT_USER;
	rkiRegInfo.lpSubKey = "software\\microsoft\\windows\\currentversion\\run";
	rkiRegInfo.lpType = &datatype;
	RegValueName = "DeskChargerMFC";
	datalen = 255;
	
	rkiRegInfo.lpQueryValueName = RegValueName.GetBuffer(14);
	RegValueName.ReleaseBuffer(); 
	rkiRegInfo.lpcbData = &datalen;
	rkiRegInfo.lpQueryData = querydata;

	//���Ϊȡ��ע�����Ϣ��һ�����ʱ������
	if (creAutoRun.GetHotReg(rkiRegInfo) == false && creAutoRun.m_Ret != ERROR_INVALID_FUNCTION)
	{
		AfxMessageBox(creAutoRun.m_ErrInfo);
	}
	else
	{
		//ȡ�ó���ȫ��
		if (GetModuleFileName(NULL, RegData.GetBuffer(255), 255) == 0)
		{
			CString StrTmp;
			StrTmp.LoadString(IDS_GETAPPNAMEERR);
			AfxMessageBox(StrTmp);
			return;
		}
		RegData.ReleaseBuffer();
		if (rkiRegInfo.lpQueryData == RegData)
			m_AutoRun.SetCheck(1);
	}
}

void CDeskChargerDlg::OnTaskBarCreated(WPARAM wp, LPARAM lp)
{
	//ϵͳ����ָ�ʱ�Զ������̼���ͼ��
	m_TrayIcon.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	Shell_NotifyIcon(NIM_ADD, &m_TrayIcon);
}

UINT CDeskChargerDlg::AutoEjectThread(LPVOID pParam)
{
	stAutoEject m_stAE = *(stAutoEject *)pParam;
	HWND * dwHwnd = m_stAE.pHwnd;
	CHotCDROMExec * dwCHCRE = m_stAE.pTrayCDROM;

	dwCHCRE->GetCDROMRegInfo(dwCHCRE->m_CDROMInfo);
	bool IsAnyEjected = false;
	
	//������������й���δȡ�����򵯳�
	for (int i = 0; i < dwCHCRE->m_CDROMInfo.GetSize(); i++)
	{
		if (dwCHCRE->m_CDROMInfo[i].m_IsAutoEjectbeforeShutdown == true)
		{
			if (dwCHCRE->IsDriverReady(dwCHCRE->m_CDROMInfo[i].m_CDROMName) == CHCE_DRIVER_READY)
			{
				dwCHCRE->SetCDROMDoor(dwCHCRE->m_CDROMInfo[i].m_CDROMName);
				IsAnyEjected = true;
				dwCHCRE->m_CDROMInfo[i].m_IsOpened = true;
			}
		}
	}
	
	if (IsAnyEjected == true)
	{
		//��Ϣ��ʾ�û������ҹرչ���
		CString MsgStr;
		MsgStr.LoadString(IDS_AUTOEJECT); 
		AfxMessageBox(MsgStr, MB_ICONINFORMATION | MB_OK | MB_SYSTEMMODAL);
		for (int i = 0; i < dwCHCRE->m_CDROMInfo.GetSize(); i++)
		{
			if (dwCHCRE->m_CDROMInfo[i].m_IsAutoEjectbeforeShutdown == true && dwCHCRE->m_CDROMInfo[i].m_IsOpened == true)
			{
				dwCHCRE->SetCDROMDoor(dwCHCRE->m_CDROMInfo[i].m_CDROMName);
			}
		}
	}

	
	CDlgShutDown dlgDown;
	dlgDown.DoModal();

	AfxEndThread(0);
	return 0;
}
