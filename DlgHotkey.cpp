// DlgHotkey.cpp : implementation file
//

#include "stdafx.h"
#include "DeskCharger.h"
#include "DlgHotkey.h"
#include "HKAddEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHotkey dialog


CDlgHotkey::CDlgHotkey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHotkey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHotkey)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_IsSetting = false;
}

CDlgHotkey::~CDlgHotkey()
{
	//注销所有内置热键
	for (int i = 0; i < 12; i++)
	{
		if (m_HotkeyExec.m_IHI[i].m_IsEnable == TRUE)
		{
			if (!m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_IHI[i].m_HotID))
				AfxMessageBox(m_HotkeyExec.m_ErrInfo);
		}
	}
	//注销所有用户定义热键
	for (i = 0; i < m_HotkeyExec.m_HotKeyInfo.GetSize(); i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_IsEnable == TRUE)
		{
			if (!m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID))
				AfxMessageBox(m_HotkeyExec.m_ErrInfo);
		}
	}
	//销毁弹出式菜单
	m_LstPopMenu.DestroyMenu(); 
}

void CDlgHotkey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHotkey)
	DDX_Control(pDX, IDC_HOTKEYLIST, m_HotkeyLst);
	DDX_Control(pDX, IDC_COMBOKEYSELECT, m_ComKeySel);
	DDX_Control(pDX, IDC_SAVEHOTKEYINFO, m_SaveHotkey);
	DDX_Control(pDX, IDC_READHOTKEYINFO, m_ReadHotkey);
	DDX_Control(pDX, IDC_EDITHOTKEYINFO, m_EditHotkey);
	DDX_Control(pDX, IDC_DELHOTKEYINFO, m_DelHotkey);
	DDX_Control(pDX, IDC_ADDHOTKEYNEW, m_AddHotkey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHotkey, CDialog)
	//{{AFX_MSG_MAP(CDlgHotkey)
	ON_COMMAND(IDM_LSTABLECUR, OnLstEnable)
	ON_BN_CLICKED(IDC_SAVEHOTKEYINFO, OnSavehotkeyinfo)
	ON_CBN_SELCHANGE(IDC_COMBOKEYSELECT, OnSelchangeCombokeyselect)
	ON_NOTIFY(NM_RCLICK, IDC_HOTKEYLIST, OnRclickHotkeylist)
	ON_COMMAND(IDM_LSTADDNEW, OnLstaddnew)
	ON_COMMAND(IDM_LSTEDIT, OnLstedit)
	ON_BN_CLICKED(IDC_ADDHOTKEYNEW, OnAddhotkeynew)
	ON_BN_CLICKED(IDC_EDITHOTKEYINFO, OnEdithotkeyinfo)
	ON_BN_CLICKED(IDC_READHOTKEYINFO, OnReadhotkeyinfo)
	ON_COMMAND(IDM_LSTDELCUR, OnLstdelcur)
	ON_BN_CLICKED(IDC_DELHOTKEYINFO, OnDelhotkeyinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHotkey message handlers

void CDlgHotkey::OnOK()
{
	//
}

void CDlgHotkey::OnCancel()
{
	//
}

BOOL CDlgHotkey::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CreatePopMenu();

	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();
	m_CilIcon.Create(16,16,TRUE,2,2);
	m_CilIcon.Add(app->LoadIcon(IDI_ENABLE));
	m_CilIcon.Add(app->LoadIcon(IDI_DISABLE));
	m_HotkeyLst.SetImageList(&m_CilIcon, LVSIL_SMALL);

	InitLstBox();  //初始化列表框
	InitDlgBtn();  //初始化对话框的按钮
	InitHotkeys(); //注册所有处于允许状态的内置热键

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgHotkey::InitDlgBtn()
{
	COLORREF	m_shBtnColor = RGB(255,255,210)/*30*/;

	m_AddHotkey.SetIcon(IDI_NEWINFO);
	m_AddHotkey.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_AddHotkey.SetTooltipText(IDS_ADDINFO);
	m_AddHotkey.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);

	m_DelHotkey.SetIcon(IDI_DELINFO);
	m_DelHotkey.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_DelHotkey.SetTooltipText(IDS_DELINFO);
	m_DelHotkey.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);

	m_EditHotkey.SetIcon(IDI_EDITINFO);
	m_EditHotkey.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_EditHotkey.SetTooltipText(IDS_EDITINFO);
	m_EditHotkey.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);

	m_ReadHotkey.SetIcon(IDI_READINFO);
	m_ReadHotkey.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_ReadHotkey.SetTooltipText(IDS_READINFO);
	m_ReadHotkey.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);

	m_SaveHotkey.SetIcon(IDI_SETTING);
	m_SaveHotkey.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_SaveHotkey.SetTooltipText(IDS_SETINFO);
	m_SaveHotkey.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);

	m_AddHotkey.ShowWindow(SW_HIDE); 
	m_DelHotkey.ShowWindow(SW_HIDE); 
	m_EditHotkey.ShowWindow(SW_HIDE); 
	m_ReadHotkey.ShowWindow(SW_HIDE); 
	m_ComKeySel.SetCurSel(0);
}

void CDlgHotkey::OnSavehotkeyinfo() 
{
	CString strTmp;
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();

	if (m_IsSetting == false)
	{
		//处于设置状态时
		m_AddHotkey.ShowWindow(SW_SHOW); 
		m_DelHotkey.ShowWindow(SW_SHOW); 
		m_EditHotkey.ShowWindow(SW_SHOW); 
		m_ReadHotkey.ShowWindow(SW_SHOW);
		m_ComKeySel.EnableWindow(FALSE); 

		strTmp.LoadString(IDS_SAVE);
		m_SaveHotkey.SetWindowText(strTmp);
		m_IsSetting = true;
		m_SaveHotkey.SetIcon(IDI_SAVE);
		m_SaveHotkey.SetTooltipText(IDS_SAVEINFO);
		app->HadSavedHandle += 2;
	}
	else
	{
		//处于设置完毕时
		m_AddHotkey.ShowWindow(SW_HIDE); 
		m_DelHotkey.ShowWindow(SW_HIDE); 
		m_EditHotkey.ShowWindow(SW_HIDE); 
		m_ReadHotkey.ShowWindow(SW_HIDE); 
		m_ComKeySel.EnableWindow(TRUE); 

		strTmp.LoadString(IDS_SET);
		m_SaveHotkey.SetWindowText(strTmp);
		m_IsSetting = false;
		m_SaveHotkey.SetIcon(IDI_SETTING);
		m_SaveHotkey.SetTooltipText(IDS_SETINFO);
		SaveInHotSettings();
		SaveHotSetting();
		app->HadSavedHandle -= 2;
	}	
}

void CDlgHotkey::InitLstBox()
{
	//初始化列表框
	LV_COLUMN lvcol;
	
	lvcol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcol.fmt = LVCFMT_LEFT;//靠左对齐
	int i = 0;
	int iCnt = m_HotkeyExec.m_HotKeyInfo.GetSize();
	CString strCol;

	//添加列名**************************
	strCol.LoadString(IDS_LSTHOTKEYFUNC);
	LPTSTR p = strCol.GetBuffer(5);
	strCol.ReleaseBuffer(); 
	lvcol.pszText = p;
	lvcol.iSubItem = i;
	lvcol.cx = 194;
	
	m_HotkeyLst.InsertColumn(i++, &lvcol);

	strCol.LoadString(IDS_LSTHOTKEYDEFINE);
	p = strCol.GetBuffer(3);
	strCol.ReleaseBuffer(); 
	lvcol.pszText = p;
	lvcol.iSubItem = i;
	lvcol.cx = 52;

	m_HotkeyLst.InsertColumn(i++, &lvcol);

	//**********************************
	//取得LISTCONTROL，设置风格为整行选择
	/*设置扁平滚动条(LVS_EX_FLATSB)*/
	//设置信息提示
	ListView_SetExtendedListViewStyle(m_HotkeyLst.m_hWnd, LVS_EX_LABELTIP | LVS_EX_FULLROWSELECT);
	SetLstData(0, TRUE, FALSE);
	for (i = 0; i < iCnt; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112)
			SetLstData(i, FALSE, FALSE);
	}
}

void CDlgHotkey::SetLstData(long idxKey, BOOL IsInFunc, BOOL IsRefresh)
{
	LV_ITEM lvitem;
	
	if (IsInFunc == TRUE)
	{
		//插入内置热键的信息
		lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
		lvitem.iItem = 0;
		lvitem.iSubItem = 0;
		if (m_HotkeyExec.m_IHI[idxKey].m_IsEnable == TRUE)
			lvitem.iImage = 0;
		else
			lvitem.iImage = 1;

		lvitem.pszText = m_HotkeyExec.m_IHI[idxKey].m_StrCmd.GetBuffer(255);
		m_HotkeyExec.m_IHI[idxKey].m_StrCmd.ReleaseBuffer();

		//如果不是新插入项目则忽略
		if (IsRefresh == FALSE)
		{
			int iPos = m_HotkeyLst.InsertItem(&lvitem);//返回表项插入后的索引号

			lvitem.mask = LVIF_TEXT;
			lvitem.iItem = iPos;
			lvitem.iSubItem = 1;
			lvitem.pszText = "C+A";
			m_HotkeyLst.SetItem(&lvitem);
		}
		else
			m_HotkeyLst.SetItem(&lvitem);
		
	}
	else
	{
		lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
		if (IsRefresh == TRUE)
			lvitem.iItem = m_HotkeyExec.m_HotKeyInfo[idxKey].m_ListIdx;
		else
			lvitem.iItem = idxKey + 1;

		lvitem.iSubItem = 0;
		if (m_HotkeyExec.m_HotKeyInfo[idxKey].m_IsEnable == TRUE)
			lvitem.iImage = 0;
		else
			lvitem.iImage = 1;

		lvitem.pszText = m_HotkeyExec.m_HotKeyInfo[idxKey].m_StrCmd.GetBuffer(255);
		m_HotkeyExec.m_HotKeyInfo[idxKey].m_StrCmd.ReleaseBuffer();
		
		//如果不是新插入项目则忽略
		if (IsRefresh == FALSE)
		{
			lvitem.iItem = m_HotkeyLst.GetItemCount();
			
			int iPos = m_HotkeyLst.InsertItem(&lvitem);//返回表项插入后的索引号
			m_HotkeyExec.m_HotKeyInfo[idxKey].m_ListIdx = iPos;
			
			lvitem.mask = LVIF_TEXT;
			lvitem.iItem = iPos;
			lvitem.iSubItem = 1;
			lvitem.pszText = m_HotkeyExec.m_HotKeyInfo[idxKey].m_CombineKey.GetBuffer(255);
			m_HotkeyExec.m_HotKeyInfo[idxKey].m_CombineKey.ReleaseBuffer();
			m_HotkeyLst.SetItem(&lvitem);
		}
		else
			m_HotkeyLst.SetItem(&lvitem);
	}
}

void CDlgHotkey::OnSelchangeCombokeyselect() 
{
	long Lstidx = (long)m_ComKeySel.GetCurSel();

	m_HotkeyLst.DeleteAllItems();
	SetLstData(Lstidx, TRUE, FALSE);

	int nCount = m_HotkeyExec.m_HotKeyInfo.GetSize();
	for (int i = 0; i < nCount; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112 + m_ComKeySel.GetCurSel())
		{
			SetLstData(i, FALSE, FALSE);
		}
	}
}

void CDlgHotkey::InitHotkeys()
{ 
	//注册所有处于允许状态的内置热键
	int i = 0;
	int iCnt = m_HotkeyExec.m_HotKeyInfo.GetSize();

	for (i = 0; i < 12; i++)
	{
		if (m_HotkeyExec.m_IHI[i].m_IsEnable == TRUE)
		{
			if (!m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_IHI[i].m_HotID, 6, m_HotkeyExec.m_IHI[i].m_HotKeyCode))
				AfxMessageBox(m_HotkeyExec.m_ErrInfo);
		}
	}
	for (i = 0; i < iCnt; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_IsEnable == TRUE)
		{
			if (!m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID, m_HotkeyExec.m_HotKeyInfo[i].m_fsModifiers, m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode))
				AfxMessageBox(m_HotkeyExec.m_ErrInfo);
		}
	}
}

LRESULT CDlgHotkey::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();
	int i = 0;
	int nCount = m_HotkeyExec.m_HotKeyInfo.GetSize();

	switch (message)
	{
	case WM_HOTKEY:
		if (app->IsEnable == TRUE)
		{
			//内置热键
			//关闭计算机
			if (wParam == (unsigned)m_HotkeyExec.m_IHI[6].m_HotID &&
				m_HotkeyExec.m_IHI[6].m_IsEnable == TRUE)
			{
				if (app->m_WinVerCd == 4)
					ExitWindowsEx(EWX_SHUTDOWN, 0); //Win9X中关闭计算机
				else
				{
					AdjustTokenPrivilegesForNT();
					ExitWindowsEx(EWX_POWEROFF, 0); //Win2000/XP中关闭计算机
				}
				
				break;
			}
			//重新启动计算机
			if (wParam == (unsigned)m_HotkeyExec.m_IHI[7].m_HotID &&
				m_HotkeyExec.m_IHI[7].m_IsEnable == TRUE)
			{
				AdjustTokenPrivilegesForNT();
				ExitWindowsEx(EWX_REBOOT, 0);
				break;
			}
			//注销当前用户
			if (wParam == (unsigned)m_HotkeyExec.m_IHI[8].m_HotID &&
				m_HotkeyExec.m_IHI[8].m_IsEnable == TRUE)
			{
				ExitWindowsEx(EWX_LOGOFF, 0);
				break;
			}
			//屏幕保护程序
			if (wParam == (unsigned)m_HotkeyExec.m_IHI[9].m_HotID &&
				m_HotkeyExec.m_IHI[9].m_IsEnable == TRUE)
			{
				if (app->m_WinVerCd == 4)
					LoadScreenSaverFor9X();
				else
					SendMessage(WM_SYSCOMMAND, SC_SCREENSAVE);

				break;
			}
			//计算机进入等待
			if (wParam == (unsigned)m_HotkeyExec.m_IHI[10].m_HotID &&
				m_HotkeyExec.m_IHI[10].m_IsEnable == TRUE)
			{
				AdjustTokenPrivilegesForNT();
				SetSystemPowerState(1, TRUE);
				break;
			}
			//计算机休眠
			if (wParam == (unsigned)m_HotkeyExec.m_IHI[11].m_HotID &&
				m_HotkeyExec.m_IHI[11].m_IsEnable == TRUE)
			{
				AdjustTokenPrivilegesForNT();
				SetSystemPowerState(0, TRUE);
				break;
			}
			//其他内置热键
			for (i = 0; i <= 5; i++)
			{
				if (wParam == (unsigned)m_HotkeyExec.m_IHI[i].m_HotID &&
					m_HotkeyExec.m_IHI[i].m_IsEnable == TRUE)
				{
					m_HotkeyExec.ChangeToAppDir(m_HotkeyExec.m_IHI[i].m_Command);
					HINSTANCE hiRet = ShellExecute(NULL, "Open", m_HotkeyExec.m_IHI[i].m_Command, m_HotkeyExec.m_IHI[i].m_Parm, NULL, SW_SHOW);
					if ((int)hiRet == ERROR_FILE_NOT_FOUND || (int)hiRet == ERROR_PATH_NOT_FOUND)
					{
						CString StrTmp;
						StrTmp.LoadString(IDS_NOFILEDIRERR);
						AfxMessageBox(StrTmp);
						break;
					}
					
					if ((int)hiRet <= 32)
					{
						CString StrTmp;
						StrTmp.LoadString(IDS_EXECERR);
						AfxMessageBox(StrTmp);
						break;
					}
					break;
				}
			}
			//用户热键
			for (i = 0; i < nCount; i++)
			{
				if (wParam == (unsigned)m_HotkeyExec.m_HotKeyInfo[i].m_HotID &&
					m_HotkeyExec.m_HotKeyInfo[i].m_IsEnable == TRUE)
				{
					m_HotkeyExec.ChangeToAppDir(m_HotkeyExec.m_HotKeyInfo[i].m_Command);
					//执行命令为网络地址时，特别处理
					if (m_HotkeyExec.m_HotKeyInfo[i].m_Command.Find("://") != -1)
						ShellExecute(NULL, "Open", "explorer.exe", m_HotkeyExec.m_HotKeyInfo[i].m_Command, NULL, SW_SHOW);
					else
						ShellExecute(NULL, "Open", m_HotkeyExec.m_HotKeyInfo[i].m_Command, m_HotkeyExec.m_HotKeyInfo[i].m_Parm, NULL, SW_SHOW);
					Sleep(100);
				}
			}
		}
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CDlgHotkey::AdjustTokenPrivilegesForNT()
{
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
 
	// Get a token for this process. 
 
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
 
	// Get the LUID for the shutdown privilege. 
 
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 
 
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 
	// Get the shutdown privilege for this process. 
 
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); 
}

void CDlgHotkey::LoadScreenSaverFor9X()
{
	//在Windows9X下执行屏幕保护程序
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();
	CString StrTmp;

	GetPrivateProfileString("boot", "SCRNSAVE.EXE", "", StrTmp.GetBuffer(256), 256, app->WinPath + "\\system.ini");
	StrTmp.ReleaseBuffer();
	HINSTANCE hiRet = ShellExecute(NULL, "Open", StrTmp, "/s", NULL, SW_SHOW);
	if ((int)hiRet == ERROR_FILE_NOT_FOUND || (int)hiRet == ERROR_PATH_NOT_FOUND)
	{
		StrTmp.LoadString(IDS_NOFILEDIRERR);
		AfxMessageBox(StrTmp);
		return;
	}
	
	if ((int)hiRet <= 32)
	{
		StrTmp.LoadString(IDS_EXECERR);
		AfxMessageBox(StrTmp);
		return;
	}
}

void CDlgHotkey::CreatePopMenu()
{
	//建立并且初始化弹出菜单
	CString StrMenu;

	m_LstPopMenu.CreatePopupMenu();
	//禁止/允许当前项目
	StrMenu.LoadString(IDS_LSTDISABLECUROPTION);
	m_LstPopMenu.AppendMenu(MF_STRING, IDM_LSTABLECUR, StrMenu);
	m_LstPopMenu.AppendMenu(MF_SEPARATOR);

	//新建项目
	StrMenu.LoadString(IDS_LSTADDNEW); 
	m_LstPopMenu.AppendMenu(MF_STRING, IDM_LSTADDNEW, StrMenu);

	//编辑项目
	StrMenu.LoadString(IDS_LSTEDITCUR); 
	m_LstPopMenu.AppendMenu(MF_STRING, IDM_LSTEDIT, StrMenu);

	//删除当前项目
	StrMenu.LoadString(IDS_LSTDELETECUROPTION);
	m_LstPopMenu.AppendMenu(MF_STRING, IDM_LSTDELCUR, StrMenu);

	m_LstPopMenu.SetDefaultItem(0, TRUE);
	m_LstPopMenu.SetMenuDrawMode(TRUE);
	m_LstPopMenu.SetBitmapBackground(RGB(0, 128, 128));
	m_LstPopMenu.SetIconSize(16, 15);
	m_LstPopMenu.LoadToolbar(IDR_LSTTOOLBAR);
}

void CDlgHotkey::OnRclickHotkeylist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if (m_ComKeySel.IsWindowEnabled() == TRUE)
	{
		*pResult = 0;
		return;
	}

	POSITION pos = m_HotkeyLst.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		*pResult = 0;
		return;
	}
	else
	{
		while (pos)
		{
			int idx = m_HotkeyLst.GetNextSelectedItem(pos);
			if (idx == 0)
			{
				//用户选择内置热键时禁止编辑/删除菜单
				//m_LstPopMenu.EnableMenuItem(2, MF_GRAYED | MF_BYPOSITION);
				m_LstPopMenu.EnableMenuItem(3, MF_GRAYED | MF_BYPOSITION);
				m_LstPopMenu.EnableMenuItem(4, MF_GRAYED | MF_BYPOSITION);
			}
			else
			{
				m_LstPopMenu.EnableMenuItem(3, MF_ENABLED | MF_BYPOSITION);
				m_LstPopMenu.EnableMenuItem(4, MF_ENABLED | MF_BYPOSITION);
			}

			POINT p;
			GetCursorPos(&p);
			SetForegroundWindow();
			m_LstPopMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);
		}
	}

	*pResult = 0;
}

void CDlgHotkey::OnLstEnable()
{
	POSITION pos = m_HotkeyLst.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}
	else
	{
		while (pos)
		{
			int idx = m_HotkeyLst.GetNextSelectedItem(pos);
			if (idx == 0)
			{
				//更新内置热键的禁止状态
				if (m_HotkeyExec.m_IHI[m_ComKeySel.GetCurSel()].m_IsEnable == TRUE)
				{
					m_HotkeyExec.m_IHI[m_ComKeySel.GetCurSel()].m_IsEnable = FALSE;
				}
				else
				{
					m_HotkeyExec.m_IHI[m_ComKeySel.GetCurSel()].m_IsEnable = TRUE;
				}
				SetLstData(m_ComKeySel.GetCurSel(), TRUE);
			}
			else
			{
				//更新用户定义热键的禁止状态
				int i = 0;
				int iCnt = m_HotkeyExec.m_HotKeyInfo.GetSize();
				for (i = 0; i < iCnt; i++)
				{
					if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112 + m_ComKeySel.GetCurSel()
						&& m_HotkeyExec.m_HotKeyInfo[i].m_ListIdx == idx)
					{
						if (m_HotkeyExec.m_HotKeyInfo[i].m_IsEnable == TRUE)
							m_HotkeyExec.m_HotKeyInfo[i].m_IsEnable = FALSE;
						else
							m_HotkeyExec.m_HotKeyInfo[i].m_IsEnable = TRUE;

						break;
					}
						
				}
				SetLstData(i, FALSE);
			}
		}
	}
}

void CDlgHotkey::SaveInHotSettings()
{
	//保存并更新内置热键的设置信息
	if (m_HotkeyExec.SetInHotkeyInfo())
		AfxMessageBox(m_HotkeyExec.m_ErrInfo);

	for (int i = 0; i < 12; i++)
	{
		if (!m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_IHI[i].m_HotID))
			AfxMessageBox(m_HotkeyExec.m_ErrInfo);

		if (m_HotkeyExec.m_IHI[i].m_IsEnable == TRUE)
		{
			if (!m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_IHI[i].m_HotID, 6, m_HotkeyExec.m_IHI[i].m_HotKeyCode))
				AfxMessageBox(m_HotkeyExec.m_ErrInfo);
		}
	}
}

void CDlgHotkey::OnLstaddnew() 
{
	CArray<CHotKeyExec::HotKeyInfo, CHotKeyExec::HotKeyInfo> m_HKIAddNew;
	CHotKeyExec::AddNumInfo m_NumInfo;
	int i = 0;
	int nCount = m_HotkeyExec.m_HotKeyInfo.GetSize();

	//初始化信息数量纪录
	m_NumInfo.m_A   = 0;
	m_NumInfo.m_AS  = 0;
	m_NumInfo.m_C   = 0;
	m_NumInfo.m_CAS = 0;
	m_NumInfo.m_CS  = 0;
	m_NumInfo.m_S   = 0;
	for (i = 0; i < nCount; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112 + m_ComKeySel.GetCurSel())
		{
			switch(m_HotkeyExec.m_HotKeyInfo[i].m_fsModifiers)
			{
			case 2:
				m_NumInfo.m_C++;
				break;
			case 1:
				m_NumInfo.m_S++;
				break;
			case 4:
				m_NumInfo.m_A++;
				break;
			case 3:
				m_NumInfo.m_CS++;
				break;
			case 5:
				m_NumInfo.m_AS++;
				break;
			case 7:
				m_NumInfo.m_CAS++;
				break;
			}
		}
	}
	
	CHKAddEdit DlgAddNewHTI(m_HKIAddNew, m_NumInfo);
	DlgAddNewHTI.DoModal();
	
	if (!m_HKIAddNew.GetSize())
		return;

	nCount = m_HotkeyLst.GetItemCount();
	for (i = 1; i <= nCount; i++)
	{
		m_HotkeyLst.DeleteItem(1);
	}
	
	nCount = m_HKIAddNew.GetSize();
	for (i = 0; i < nCount; i++)
	{
		m_HKIAddNew[i].m_IsEnable = TRUE;
		m_HKIAddNew[i].m_HotKeyCode = 112 + m_ComKeySel.GetCurSel();
		m_HKIAddNew[i].m_HotID = GetHotKeyID(m_HKIAddNew[i].m_fsModifiers, m_ComKeySel.GetCurSel());
		m_HotkeyExec.SetHotkeyInfo(m_HotkeyExec.m_HotKeyInfo, m_HKIAddNew[i], TRUE);
	}

	//排序
	m_HotkeyExec.SortArrayKey(m_HotkeyExec.m_HotKeyInfo, TRUE);

	nCount = m_HotkeyExec.m_HotKeyInfo.GetSize();
	for (i = 0; i < nCount; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112 + m_ComKeySel.GetCurSel())
		{
			SetLstData(i, FALSE, FALSE);
			m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID);
			if (m_HotkeyExec.m_HotKeyInfo[i].m_IsEnable == TRUE)
				m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID, m_HotkeyExec.m_HotKeyInfo[i].m_fsModifiers, m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode);
		}
	}
}

void CDlgHotkey::OnLstedit()
{
	CHotKeyExec::HotKeyInfo CurHKI;
	int i = 0;
	int idx = 0;
	int iCnt = m_HotkeyExec.m_HotKeyInfo.GetSize();

	POSITION pos = m_HotkeyLst.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}
	else
	{
		while (pos)
		{
			idx = m_HotkeyLst.GetNextSelectedItem(pos);
			if (idx == 0)
				return;
		}
	}

	for (i = 0; i < iCnt; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112 + m_ComKeySel.GetCurSel() &&
			idx == m_HotkeyExec.m_HotKeyInfo[i].m_ListIdx)
		{
			CurHKI = m_HotkeyExec.m_HotKeyInfo[i];
			break;
		}
	}
	CHKAddEdit DlgEditHTI(CurHKI);
	DlgEditHTI.DoModal();

	if (CurHKI.m_IsModify == TRUE)
	{
		m_HotkeyExec.m_HotKeyInfo[i].m_CombineKey = CurHKI.m_CombineKey;
		m_HotkeyExec.m_HotKeyInfo[i].m_Command = CurHKI.m_Command;
		m_HotkeyExec.m_HotKeyInfo[i].m_fsModifiers = CurHKI.m_fsModifiers;
		m_HotkeyExec.m_HotKeyInfo[i].m_Parm = CurHKI.m_Parm;
		m_HotkeyExec.m_HotKeyInfo[i].m_StrCmd = CurHKI.m_StrCmd;
		m_HotkeyExec.m_HotKeyInfo[i].m_IsModify = TRUE;
		m_HotkeyExec.m_HotKeyInfo[i].m_HotID = GetHotKeyID(CurHKI.m_fsModifiers, m_ComKeySel.GetCurSel());
	}
	else
		return;

	//提交修改
	m_HotkeyExec.SetHotkeyInfo(m_HotkeyExec.m_HotKeyInfo, m_HotkeyExec.m_HotKeyInfo[i], FALSE);
	//重新排序
	m_HotkeyExec.SortArrayKey(m_HotkeyExec.m_HotKeyInfo, TRUE);

	for (i = 1; i <= iCnt; i++)
	{
		m_HotkeyLst.DeleteItem(1);
	}
	
	for (i = 0; i < iCnt; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112 + m_ComKeySel.GetCurSel())
		{
			SetLstData(i, FALSE, FALSE);
			m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID);
			if (m_HotkeyExec.m_HotKeyInfo[i].m_IsEnable == TRUE)
				m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID, m_HotkeyExec.m_HotKeyInfo[i].m_fsModifiers, m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode);
		}
	}
}

int CDlgHotkey::GetHotKeyID(int iCombinKey, int ivKeyIdx)
{
	switch (ivKeyIdx)
	{
	case 0:
		return  0xB020 + iCombinKey;
		break;
	case 1:
		return  0xB030 + iCombinKey;
		break;
	case 2:
		return  0xB040 + iCombinKey;
		break;
	case 3:
		return  0xB050 + iCombinKey;
		break;
	case 4:
		return  0xB060 + iCombinKey;
		break;
	case 5:
		return  0xB070 + iCombinKey;
		break;
	case 6:
		return  0xB080 + iCombinKey;
		break;
	case 7:
		return  0xB090 + iCombinKey;
		break;
	case 8:
		return  0xB0A0 + iCombinKey;
		break;
	case 9:
		return  0xB0B0 + iCombinKey;
		break;
	case 10:
		return  0xB0C0 + iCombinKey;
		break;
	case 11:
		return  0xB0D0 + iCombinKey;
		break;
	}

	return 0;
}

void CDlgHotkey::SaveHotSetting()
{
	//保存并更新用户设置热键的设置信息
	int i = 0;
	int iCnt = m_HotkeyExec.m_HotKeyInfo.GetSize();

	if (m_HotkeyExec.SetRegHotKeyInfo(m_HotkeyExec.m_HotKeyInfo))
		AfxMessageBox(m_HotkeyExec.m_ErrInfo);
	
	for (i = 0; i < iCnt; i++)
	{
		if (!m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID))
			AfxMessageBox(m_HotkeyExec.m_ErrInfo);
		
		if (m_HotkeyExec.m_HotKeyInfo[i].m_IsEnable == TRUE)
		{
			if (!m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID, m_HotkeyExec.m_HotKeyInfo[i].m_fsModifiers, m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode))
				AfxMessageBox(m_HotkeyExec.m_ErrInfo);
		}
	}
}

void CDlgHotkey::OnAddhotkeynew()
{
	OnLstaddnew();
}

void CDlgHotkey::OnEdithotkeyinfo() 
{
	OnLstedit();
}

void CDlgHotkey::OnReadhotkeyinfo() 
{
	m_HotkeyExec.m_HotKeyInfo.RemoveAll();
	m_HotkeyExec.UserInit();
	int nCount = 0;
	int i = 0;

	nCount = m_HotkeyLst.GetItemCount();
	for (i = 1; i <= nCount; i++)
	{
		m_HotkeyLst.DeleteItem(1);
	}
	
	nCount = m_HotkeyExec.m_HotKeyInfo.GetSize();
	for (i = 0; i < nCount; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112 + m_ComKeySel.GetCurSel())
		{
			SetLstData(i, FALSE, FALSE);
			if (m_HotkeyExec.m_HotKeyInfo[i].m_IsEnable == TRUE)
			{
				if (!m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID, m_HotkeyExec.m_HotKeyInfo[i].m_fsModifiers, m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode))
					AfxMessageBox(m_HotkeyExec.m_ErrInfo);
			}
		}
	}
}

void CDlgHotkey::OnLstdelcur() 
{
	int iCnt = m_HotkeyExec.m_HotKeyInfo.GetSize();
	int idx  = 0;
	int i    = 0;
	
	POSITION pos = m_HotkeyLst.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return;
	}
	else
	{
		while (pos)
		{
			idx = m_HotkeyLst.GetNextSelectedItem(pos);
			if (idx == 0)
				return;
		}
	}

	CString strTmp((LPCTSTR)IDS_ISDELCURINFO);
	int iret = MessageBox(strTmp, NULL, MB_ICONWARNING | MB_YESNO);
	if (iret == IDNO)
		return;

	//设置删除标志
	for (i = 0; i < iCnt; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112 + m_ComKeySel.GetCurSel() &&
			idx == m_HotkeyExec.m_HotKeyInfo[i].m_ListIdx)
		{
			m_HotkeyExec.m_HotKeyInfo[i].m_IsDelete = TRUE;
			break;
		}
	}
	
	//重新整理信息结构
	iCnt = m_HotkeyExec.m_HotKeyInfo.GetSize();
	for (i = 0; i < iCnt; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112 + m_ComKeySel.GetCurSel())
		{
			m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID);
			if (m_HotkeyExec.m_HotKeyInfo[i].m_IsEnable == TRUE && m_HotkeyExec.m_HotKeyInfo[i].m_IsDelete == FALSE)
				m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID, m_HotkeyExec.m_HotKeyInfo[i].m_fsModifiers, m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode);
		}
	}
	
	m_HotkeyExec.DelHotkeyInfo(m_HotkeyExec.m_HotKeyInfo);

	m_HotkeyExec.SortArrayKey(m_HotkeyExec.m_HotKeyInfo, TRUE);

	iCnt = m_HotkeyLst.GetItemCount();
	for (i = 1; i <= iCnt; i++)
	{
		m_HotkeyLst.DeleteItem(1);
	}
	
	iCnt = m_HotkeyExec.m_HotKeyInfo.GetSize();
	for (i = 0; i < iCnt; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112 + m_ComKeySel.GetCurSel())
		{
			SetLstData(i, FALSE, FALSE);
		}
	}
}

void CDlgHotkey::OnDelhotkeyinfo() 
{
	int iCnt = m_HotkeyExec.m_HotKeyInfo.GetSize();
	int i    = 0;
	
	CString strTmp((LPCTSTR)IDS_ISDELALLINFO);
	int iret = MessageBox(strTmp, NULL, MB_ICONWARNING | MB_YESNO);
	if (iret == IDNO)
		return;
	
	//设置删除标志
	for (i = 0; i < iCnt; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112 + m_ComKeySel.GetCurSel())
		{
			m_HotkeyExec.m_HotKeyInfo[i].m_IsDelete = TRUE;
		}
	}
	
	//重新整理信息结构
	iCnt = m_HotkeyExec.m_HotKeyInfo.GetSize();
	for (i = 0; i < iCnt; i++)
	{
		if (m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode == 112 + m_ComKeySel.GetCurSel())
		{
			m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID);
			if (m_HotkeyExec.m_HotKeyInfo[i].m_IsEnable == TRUE && m_HotkeyExec.m_HotKeyInfo[i].m_IsDelete == FALSE)
				m_HotkeyExec.SetHotKey(this->m_hWnd, m_HotkeyExec.m_HotKeyInfo[i].m_HotID, m_HotkeyExec.m_HotKeyInfo[i].m_fsModifiers, m_HotkeyExec.m_HotKeyInfo[i].m_HotKeyCode);
		}
	}
	
	m_HotkeyExec.DelHotkeyInfo(m_HotkeyExec.m_HotKeyInfo);
	
	m_HotkeyExec.SortArrayKey(m_HotkeyExec.m_HotKeyInfo, TRUE);
	
	iCnt = m_HotkeyLst.GetItemCount();
	for (i = 1; i <= iCnt; i++)
	{
		m_HotkeyLst.DeleteItem(1);
	}
}
