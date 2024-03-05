// DlgCDROM.cpp : implementation file
//

#include "stdafx.h"
#include "DeskCharger.h"
#include "DlgCDROM.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCDROM dialog


CDlgCDROM::CDlgCDROM(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCDROM::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCDROM)
	//}}AFX_DATA_INIT
	m_IsSetting = false;
}

CDlgCDROM::~CDlgCDROM()
{
	//注销打开指定CD-ROM的热键
	for (int i = 0; i < m_HotCDROM.m_CDROMInfo.GetSize(); i++)
	{
		if (!m_HotCDROM.SetHotKey(this->m_hWnd, m_HotCDROM.m_CDROMInfo[i].m_HotID))
			AfxMessageBox(m_HotCDROM.m_ErrInfo);
	}
	//注销打开所有的CD-ROM的固定热键
	if (!m_HotCDROM.SetHotKey(this->m_hWnd, 0xB000))
		AfxMessageBox(m_HotCDROM.m_ErrInfo);
	if (!m_HotCDROM.SetHotKey(this->m_hWnd, 0xB001))
		AfxMessageBox(m_HotCDROM.m_ErrInfo);
}

void CDlgCDROM::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCDROM)
	DDX_Control(pDX, IDC_SETDEFAULTCDROM, m_SetDefaultCDROM);
	DDX_Control(pDX, IDC_SETCDROMHOTKEY, m_SetCDROMHotkey);
	DDX_Control(pDX, IDC_SETCDROMDEFAULT, m_SetCDROMDefault);
	DDX_Control(pDX, IDC_CDROMSETHOTKEY, m_CDROMHotKey);
	DDX_Control(pDX, IDC_AUTOCLOSE, m_AutoClose);
	DDX_Control(pDX, IDC_AUTOEJECT, m_AutoEject);
	DDX_Control(pDX, IDC_CDROMLAB, m_CDROMLab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCDROM, CDialog)
	//{{AFX_MSG_MAP(CDlgCDROM)
	ON_CBN_SELCHANGE(IDC_CDROMLAB, OnSelchangeCdromlab)
	ON_BN_CLICKED(IDC_SETDEFAULTCDROM, OnSetdefaultcdrom)
	ON_BN_CLICKED(IDC_SETCDROMDEFAULT, OnSetcdromdefault)
	ON_BN_CLICKED(IDC_SETCDROMHOTKEY, OnSetcdromhotkey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCDROM message handlers

BOOL CDlgCDROM::OnInitDialog() 
{
	COLORREF	m_shBtnColor = RGB(255,255,210)/*30*/;

	CDialog::OnInitDialog();
	
	//光驱对话框的初始化操作
	m_CDROMHotKey.EnableWindow(FALSE);
	m_AutoEject.EnableWindow(FALSE);
	m_AutoClose.EnableWindow(FALSE);
	(CStatic *)GetDlgItem(IDC_LAB)->EnableWindow(FALSE);

	if (m_HotCDROM.m_CDROMInfo.GetSize() <= 0)
	{
		//计算机上没有光驱设备
		//m_SetDefaultCDROM.EnableWindow(FALSE);
		//m_SetCDROMDefault.EnableWindow(FALSE);
		//m_SetCDROMHotkey.EnableWindow(FALSE);
		m_SetCDROMDefault.DisableButton(IDI_DEFAULT);
		m_SetDefaultCDROM.DisableButton(IDI_CDROMDEFAULT);
		m_SetCDROMHotkey.DisableButton(IDI_SETTING);

		m_CDROMLab.EnableWindow(FALSE);
		
		CString MsgStr;
		MsgStr.LoadString(IDS_NOCDROM);
		SetDlgItemText(IDC_MAINCDROM, MsgStr);
		EnableWindow(FALSE);
	}
	else
	{
		//计算机上有光驱设备
		SetCDROMItemValue(TRUE);

		m_AutoClose.SetLimitText(2); 
		m_SetDefaultCDROM.SetIcon(IDI_CDROMDEFAULT);
		m_SetDefaultCDROM.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
		m_SetDefaultCDROM.SetTooltipText(IDS_CDROMDEFAULT);
		m_SetDefaultCDROM.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);

		m_SetCDROMDefault.SetIcon(IDI_DEFAULT);
		m_SetCDROMDefault.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
		m_SetCDROMDefault.SetTooltipText(IDS_DEFAULT);
		m_SetCDROMDefault.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);
	
		m_SetCDROMHotkey.SetIcon(IDI_SETTING);
		m_SetCDROMHotkey.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
		m_SetCDROMHotkey.SetTooltipText(IDS_SETINFO);
		m_SetCDROMHotkey.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCDROM::SetCDROMItemValue(BOOL IsInit)
{
	char InfoData[20];
	CString strMain;

	// 设置CD-ROM的盘符
	for (int i = 0; i < m_HotCDROM.m_CDROMInfo.GetSize(); i++)
	{
		if (m_CDROMLab.GetCount() < m_HotCDROM.m_CDROMInfo.GetSize())
		{
			m_CDROMLab.AddString(m_HotCDROM.m_CDROMInfo[i].m_CDROMName.Left(2));
		}
		if (m_HotCDROM.m_CDROMInfo[i].m_IsMainCDROM == true)
		{
			strMain.LoadString(IDS_MAINCDROM);
			strMain += m_HotCDROM.m_CDROMInfo[i].m_CDROMName.Left(2);
			SetDlgItemText(IDC_MAINCDROM, strMain);
		}
	}
	
	int idx = 0;

	if (IsInit)  //初始化时选择第一个光驱
	{
		m_CDROMLab.SetCurSel(0);
	}
	else
	{
		idx = m_CDROMLab.GetCurSel();
		m_CDROMLab.SetCurSel(idx);
	}

	//初始化设置自动弹出的值
	if (m_HotCDROM.m_CDROMInfo[idx].m_IsAutoEjectbeforeShutdown == true )
		m_AutoEject.SetCheck(1);
	else
		m_AutoEject.SetCheck(0);

	//自动关闭时间设置
	_itoa(m_HotCDROM.m_CDROMInfo[idx].m_AutoCloseTime, InfoData, 10);
	SetDlgItemText(IDC_AUTOCLOSE, InfoData);

	//适应扩展按键的热键设置
	//111为Num /;33为Page Up;34为Page Down;35为End;36为Home;45为Insert
	WORD VKeyAsc = (WORD)m_HotCDROM.m_CDROMInfo[idx].m_VKeyAsc;
	WORD fsModifiers = (WORD)m_HotCDROM.m_CDROMInfo[idx].m_fsModifiers;
	if (VKeyAsc == 111 || VKeyAsc == 33 ||
		VKeyAsc == 34  || VKeyAsc == 35 ||
		VKeyAsc == 36  || VKeyAsc == 45)
		fsModifiers += 8;
	m_CDROMHotKey.SetHotKey(VKeyAsc, fsModifiers);

	//注册CD-ROM的系统热键
	for (i = 0; i < m_HotCDROM.m_CDROMInfo.GetSize(); i++)
	{
		if (!IsInit)
		{
			if (!m_HotCDROM.SetHotKey(this->m_hWnd, m_HotCDROM.m_CDROMInfo[i].m_HotID))
				AfxMessageBox(m_HotCDROM.m_ErrInfo);
		}
		if (m_HotCDROM.m_CDROMInfo[i].m_IsEnable == true)
		{
			if (!m_HotCDROM.SetHotKey(this->m_hWnd, 
								 m_HotCDROM.m_CDROMInfo[i].m_HotID,
								 m_HotCDROM.m_CDROMInfo[i].m_fsModifiers,
								 m_HotCDROM.m_CDROMInfo[i].m_VKeyAsc))
				AfxMessageBox(m_HotCDROM.m_ErrInfo);
		}
	}
	
	//注销打开所有的CD-ROM的固定热键
	if (!IsInit)
	{
		if (!m_HotCDROM.SetHotKey(this->m_hWnd, 0xB000))
			AfxMessageBox(m_HotCDROM.m_ErrInfo);
		if (!m_HotCDROM.SetHotKey(this->m_hWnd, 0xB001))
			AfxMessageBox(m_HotCDROM.m_ErrInfo);
	}
	//注册打开所有的CD-ROM的固定热键
	//6为组合键：Ctrl + Alt
	//111为Num /;191为`
	if (!m_HotCDROM.SetHotKey(this->m_hWnd, 0xB000, 6, 192))
		AfxMessageBox(m_HotCDROM.m_ErrInfo);
	if (!m_HotCDROM.SetHotKey(this->m_hWnd, 0xB001, 6, 111))
		AfxMessageBox(m_HotCDROM.m_ErrInfo);
}

void CDlgCDROM::OnSelchangeCdromlab() 
{
	char InfoData[20];
	CString strMain;
	int idx = m_CDROMLab.GetCurSel();

	if (m_HotCDROM.m_CDROMInfo[idx].m_IsAutoEjectbeforeShutdown == true )
		m_AutoEject.SetCheck(1);
	else
		m_AutoEject.SetCheck(0);

	_itoa(m_HotCDROM.m_CDROMInfo[idx].m_AutoCloseTime, InfoData, 10);
	SetDlgItemText(IDC_AUTOCLOSE, InfoData);

	if (m_HotCDROM.m_CDROMInfo[idx].m_IsMainCDROM == true)
	{
		strMain.LoadString(IDS_MAINCDROM);
		strMain += m_HotCDROM.m_CDROMInfo[idx].m_CDROMName.Left(2);
		SetDlgItemText(IDC_MAINCDROM, strMain);
	}

	m_CDROMHotKey.SetHotKey((WORD)m_HotCDROM.m_CDROMInfo[idx].m_VKeyAsc, (WORD)m_HotCDROM.m_CDROMInfo[idx].m_fsModifiers);  
}

void CDlgCDROM::OnSetdefaultcdrom() 
{
	//设置当前CD-ROM为主CD-ROM

	int idx = m_CDROMLab.GetCurSel();
	for (int i = 0; i < m_HotCDROM.m_CDROMInfo.GetSize(); i++)
	{
		m_HotCDROM.m_CDROMInfo[i].m_IsMainCDROM = false;
	}
	m_HotCDROM.m_CDROMInfo[idx].m_IsMainCDROM = true;
	m_HotCDROM.SetCDROMRegInfo(m_HotCDROM.m_CDROMInfo);
	SetCDROMItemValue();
}

void CDlgCDROM::OnSetcdromdefault() 
{
	//设置当前CD-ROM的缺省信息
	int idx = m_CDROMLab.GetCurSel();
	m_HotCDROM.m_CDROMInfo[idx].m_IsDefault = true;
	m_HotCDROM.m_CDROMInfo[idx].m_IsEnable = true;
	m_HotCDROM.SetCDROMRegInfo(m_HotCDROM.m_CDROMInfo);
	SetCDROMItemValue();
}

void CDlgCDROM::OnOK()
{
	//
}

void CDlgCDROM::OnCancel()
{
	//
}

void CDlgCDROM::OnSetcdromhotkey() 
{
	//设置当前CD-ROM的信息
	CString strTmp;
	int idx = m_CDROMLab.GetCurSel();
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();

	if (m_IsSetting == false)
	{
		m_CDROMHotKey.EnableWindow(TRUE);
		m_AutoEject.EnableWindow(TRUE);
		m_AutoClose.EnableWindow(TRUE);

		m_CDROMLab.EnableWindow(FALSE);
		//m_SetDefaultCDROM.EnableWindow(FALSE);
		//m_SetCDROMDefault.EnableWindow(FALSE);
		m_SetCDROMDefault.DisableButton(IDI_DEFAULT);
		m_SetDefaultCDROM.DisableButton(IDI_CDROMDEFAULT);
		strTmp.LoadString(IDS_SAVE);
		m_SetCDROMHotkey.SetWindowText(strTmp);
		m_CDROMHotKey.SetFocus(); 
		(CStatic *)GetDlgItem(IDC_LAB)->EnableWindow(TRUE);
		m_IsSetting = true;
		m_SetCDROMHotkey.SetIcon(IDI_SAVE);
		m_SetCDROMHotkey.SetTooltipText(IDS_SAVEINFO);
		app->HadSavedHandle += 1;
	}
	else
	{
		WORD VKeyAsc, fsModifiers;
		m_AutoClose.GetWindowText(strTmp);
		int iCloseTime = atoi(strTmp);

		if (iCloseTime > 60)
		{
			strTmp.LoadString(IDS_TOOLARGERVALUE);
			AfxMessageBox(strTmp);
			m_AutoClose.SetFocus();
			m_AutoClose.SetSel(0, 2); 
			return;
		}

		m_CDROMHotKey.GetHotKey(VKeyAsc, fsModifiers); 

		if (VKeyAsc >= 112 && VKeyAsc <= 123)
		{
			strTmp.LoadString(IDS_HOTKEYUSEF);
			AfxMessageBox(strTmp);
			m_CDROMHotKey.SetFocus();
			return;
		}			

		if (fsModifiers == 0)
		{
			if (VKeyAsc != 0)
			{
				strTmp.LoadString(IDS_HOTKEYWARM);
				AfxMessageBox(strTmp);
				m_CDROMHotKey.SetFocus();
				return;
			}
			else
			{
				m_HotCDROM.m_CDROMInfo[idx].m_IsEnable = false;
				if (!m_HotCDROM.SetHotKey(this->m_hWnd, m_HotCDROM.m_CDROMInfo[idx].m_HotID))
					AfxMessageBox(m_HotCDROM.m_ErrInfo);
			}
		}
		else
			m_HotCDROM.m_CDROMInfo[idx].m_IsEnable = true;

		//适应扩展按键的热键设置
		//111为Num /;33为Page Up;34为Page Down;35为End;36为Home;45为Insert
		if (VKeyAsc == 111 || VKeyAsc == 33 ||
			VKeyAsc == 34  || VKeyAsc == 35 ||
			VKeyAsc == 36  || VKeyAsc == 45)
			fsModifiers -= 8;

		m_HotCDROM.m_CDROMInfo[idx].m_fsModifiers = fsModifiers;
		m_HotCDROM.m_CDROMInfo[idx].m_VKeyAsc = VKeyAsc;

		m_AutoClose.GetWindowText(strTmp);
		m_HotCDROM.m_CDROMInfo[idx].m_AutoCloseTime = atoi(strTmp);
		if (m_HotCDROM.m_CDROMInfo[idx].m_AutoCloseTime == 0)
			m_HotCDROM.m_CDROMInfo[idx].m_IsAutoClose = false;
		else
			m_HotCDROM.m_CDROMInfo[idx].m_IsAutoClose = true;

		if (m_AutoEject.GetCheck() == 1) 
			m_HotCDROM.m_CDROMInfo[idx].m_IsAutoEjectbeforeShutdown = true;
		else
			m_HotCDROM.m_CDROMInfo[idx].m_IsAutoEjectbeforeShutdown = false;

		TRACE1("idx %d\n", idx);
		TRACE1("fsModifiers %d\n", fsModifiers);
		TRACE1("VKeyAsc %d\n", VKeyAsc);
		TRACE1("IsAutoEject %d\n", m_HotCDROM.m_CDROMInfo[idx].m_IsAutoEjectbeforeShutdown);

		m_HotCDROM.SetCDROMRegInfo(m_HotCDROM.m_CDROMInfo);
		SetCDROMItemValue();

		m_CDROMHotKey.EnableWindow(FALSE);
		m_AutoEject.EnableWindow(FALSE);
		m_AutoClose.EnableWindow(FALSE);

		m_CDROMLab.EnableWindow(TRUE);
		//m_SetDefaultCDROM.EnableWindow(TRUE);
		//m_SetCDROMDefault.EnableWindow(TRUE);
		m_SetCDROMDefault.DisableButton(IDI_DEFAULT, FALSE, 0);
		m_SetDefaultCDROM.DisableButton(IDI_CDROMDEFAULT, FALSE, 0);

		strTmp.LoadString(IDS_SET);
		m_SetCDROMHotkey.SetWindowText(strTmp);
		m_IsSetting = false;
		(CStatic *)GetDlgItem(IDC_LAB)->EnableWindow(FALSE);
		m_SetCDROMHotkey.SetIcon(IDI_SETTING);
		m_SetCDROMHotkey.SetTooltipText(IDS_SETINFO);
		app->HadSavedHandle -= 1;
	}
}

LRESULT CDlgCDROM::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	int i, RetCDROM;
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();

	switch (message)
	{
	case WM_HOTKEY:
		if (app->IsEnable == TRUE)
		{
			//打开指定的CD-ROM
			for (i = 0; i < m_HotCDROM.m_CDROMInfo.GetSize(); i++)
			{
				if (wParam == (unsigned int)m_HotCDROM.m_CDROMInfo[i].m_HotID)
				{
					RetCDROM = m_HotCDROM.SetCDROMDoor(m_HotCDROM.m_CDROMInfo[i].m_CDROMName);
					if (m_HotCDROM.m_CDROMInfo[i].m_IsAutoClose == true && RetCDROM == 0)
					{
						//取得指定CD-ROM的自动关闭时间
						long TimeInterval = m_HotCDROM.m_CDROMInfo[i].m_AutoCloseTime * 1000; 
						::SetTimer(this->m_hWnd, (IDT_CDROM + i), TimeInterval, NULL);
					}
					break;
				}
			}

			//打开所有的CD-ROM
			if (wParam == 0xB000 || wParam == 0xB001)
			{
				for (i = 0; i < m_HotCDROM.m_CDROMInfo.GetSize(); i++)
				{
					RetCDROM = m_HotCDROM.SetCDROMDoor(m_HotCDROM.m_CDROMInfo[i].m_CDROMName);
					if (m_HotCDROM.m_CDROMInfo[i].m_IsAutoClose == true && RetCDROM == 0)
					{
						//取得指定CD-ROM的自动关闭时间
						long TimeInterval = m_HotCDROM.m_CDROMInfo[i].m_AutoCloseTime * 1000; 
						::SetTimer(this->m_hWnd, (IDT_ALLCDROM + i), TimeInterval, NULL);
					}
				}
			}
		}
		break;

	//定时器返回
	case WM_TIMER:
		if (wParam >= IDT_CDROM && wParam < IDT_ALLCDROM)
		{
			m_HotCDROM.SetCDROMDoor(m_HotCDROM.m_CDROMInfo[wParam - IDT_CDROM].m_CDROMName, true);
			::KillTimer(this->m_hWnd, wParam);
			break;
		}

		if (wParam >= IDT_ALLCDROM)
		{
			m_HotCDROM.SetCDROMDoor(m_HotCDROM.m_CDROMInfo[wParam - IDT_ALLCDROM].m_CDROMName, true);
			::KillTimer(this->m_hWnd, wParam);
			break;
		}
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}
