/*
********************************************************************
类功能：建立与热键相关的信息，使之拥有热键启动功能

作者：徐仲华

修改纪录：
    2003.04.27  建立
********************************************************************
*/

#include "stdafx.h"
#include "DeskCharger.h"
#include "resource.h"
#include "HotKeyExec.h"

CHotKeyExec::CHotKeyExec()
{
	InInit();   //初始化内置信息
	UserInit(); //初始化用户信息
}

CHotKeyExec::~CHotKeyExec()
{
	m_HotKeyInfo.RemoveAll();
}

long CHotKeyExec::DelHotkeyInfo(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo)
{
	CArray<HotKeyInfo, HotKeyInfo> m_TmpHKI;
	int i = 0;

	for (i = 0; i < m_HotKeyInfo.GetSize(); i++)
	{
		if (m_HotKeyInfo[i].m_IsDelete != TRUE)
		{
			m_TmpHKI.Add(m_HotKeyInfo[i]);
		}
	}

	m_HotKeyInfo.RemoveAll();

	for (i = 0; i < m_TmpHKI.GetSize(); i++)
	{
		m_HotKeyInfo.Add(m_TmpHKI[i]);
	}
	
	return 0;
}

long CHotKeyExec::SetHotkeyInfo(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo, CHotKeyExec::HotKeyInfo &NewHotKeyInfo, BOOL IsAdd)
{
	if (IsAdd == TRUE)
	{
		//添加
		m_HotKeyInfo.Add(NewHotKeyInfo);
		return 0;
	}
	else
	{
		//编辑
		for (int i = 0; i < m_HotKeyInfo.GetSize(); i++)
		{
			if (m_HotKeyInfo[i].m_IsModify == TRUE)
			{
				m_HotKeyInfo.SetAt(i, NewHotKeyInfo);
				m_HotKeyInfo[i].m_IsModify = FALSE;
				break;
			}
		}
	}

	return 0;
}

void CHotKeyExec::InInit()
{
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();

	for (int i = 0; i < 12; i++)
	{
		m_IHI[i].m_HotID = 0xB010 + i;
		m_IHI[i].m_HotKeyCode = 112 + i;
		m_IHI[i].m_IsEnable = TRUE;
		m_IHI[i].m_Command.Empty();
		m_IHI[i].m_Parm.Empty();
		m_IHI[i].m_StrCmd.Empty();
	}

	//控制面板F1
	m_IHI[0].m_StrCmd.LoadString(IDS_CONTROLPAD); 
	m_IHI[0].m_Command = "rundll32.exe";
	m_IHI[0].m_Parm = "shell32.dll,Control_RunDLL";
	//添加/删除程序F2
	m_IHI[1].m_StrCmd.LoadString(IDS_ADDREMOVEAPP);
	m_IHI[1].m_Command = "rundll32.exe";
	m_IHI[1].m_Parm = "shell32.dll,Control_RunDLL Appwiz.cpl";

	//记事本F3
	m_IHI[2].m_StrCmd.LoadString(IDS_NOTEPAD);
	if (app->m_WinVerCd == 4)
		m_IHI[2].m_Command = app->WinPath + "\\notepad.exe";
	else
		m_IHI[2].m_Command = app->WinPath + "\\System32\\notepad.exe";
	//MS-DOS方式F4
	m_IHI[3].m_StrCmd.LoadString(IDS_MSDOSMODE);
	if (app->m_WinVerCd == 4)
		m_IHI[3].m_Command = app->WinPath + "\\Command.com";
	else
		m_IHI[3].m_Command = app->WinPath + "\\System32\\cmd.exe";
	//计算器F5
	m_IHI[4].m_StrCmd.LoadString(IDS_CALCPAD);
	if (app->m_WinVerCd == 4)
		m_IHI[4].m_Command = app->WinPath + "\\CALC.EXE";
	else
		m_IHI[4].m_Command = app->WinPath + "\\System32\\calc.exe";
	//IEF6
	m_IHI[5].m_StrCmd.LoadString(IDS_IEEXPLORER);
	m_IHI[5].m_Command = app->WinPath.Left(3) + "Progra~1\\Intern~1\\IEXPLORE.EXE";
	//关机F7
	m_IHI[6].m_StrCmd.LoadString(IDS_SHUTDOWN);
	//重启F8
	m_IHI[7].m_StrCmd.LoadString(IDS_RESTART);
	//注销F9
	m_IHI[8].m_StrCmd.LoadString(IDS_LOGOFF);
	//屏保F10
	m_IHI[9].m_StrCmd.LoadString(IDS_SCREENSAVER);
	//等待F11
	m_IHI[10].m_StrCmd.LoadString(IDS_WAITMODE);
	//休眠F12
	m_IHI[11].m_StrCmd.LoadString(IDS_SLEEPMODE);

	if (GetInHotkeyInfo())
		AfxMessageBox(m_ErrInfo);
	if (SetInHotkeyInfo())
		AfxMessageBox(m_ErrInfo);
}

long CHotKeyExec::GetInHotkeyInfo()
{
	RegKeyInfo CurRegInfo;
	CString RegData;
	CString RegValueName;
	char idx[20];
	unsigned long datalen;
	unsigned char querydata[256];
	unsigned long datatype = REG_SZ;

	CurRegInfo.hKey = HKEY_CURRENT_USER;
	CurRegInfo.lpSubKey = "Software\\DeskChargerMFC\\HotkeyInfo";
	CurRegInfo.lpType = &datatype;
	for (int i = 0; i < 12; i++)
	{
		RegValueName = "Hotkey";
		datalen = 256;
		_itoa(i, idx, 10);
		RegValueName += idx;
		
		CurRegInfo.lpQueryValueName = RegValueName.GetBuffer(8);
		RegValueName.ReleaseBuffer(); 
		CurRegInfo.lpcbData = &datalen;
		CurRegInfo.lpQueryData = querydata;

		//如果为取得注册表信息的一般错误时，忽略
		if (GetHotReg(CurRegInfo) == false && ((m_ErrPos != 1 && m_ErrPos != 2) || m_Ret != ERROR_INVALID_FUNCTION))
		{
			TRACE1("%s\n", m_ErrInfo);
			return 1;
		}

		if (m_ErrPos == 0)
		{
			RegData = querydata;
			if (RegData.Left(1) == '0')
				m_IHI[i].m_IsEnable = FALSE;
			else
				m_IHI[i].m_IsEnable = TRUE;
		}
	}
	return 0;
}

long CHotKeyExec::SetInHotkeyInfo()
{
	char idx[20];
	CString RegValueName;
	CString RegData;
	RegKeyInfo CurRegInfo;
	int i = 0;

	CurRegInfo.hKey = HKEY_CURRENT_USER;
	CurRegInfo.lpSubKey = "Software\\DeskChargerMFC\\HotkeyInfo";
	CurRegInfo.dwType = REG_SZ;

	for (i = 0; i < 12; i++)
	{
		//设置数值名称和数据
		RegValueName = "Hotkey";
		_itoa(i, idx, 10);
		RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		
		CurRegInfo.cbData = 200;

		/*数据格式为：
			禁止标志
		*/
		RegData.Empty(); 
		if (m_IHI[i].m_IsEnable == FALSE)
			RegData += "0";
		else
			RegData += "1";

		CurRegInfo.lpSetData = (CONST BYTE *)RegData.GetBuffer(200);
		RegData.ReleaseBuffer(); 
		if (SetHotReg(CurRegInfo) == false)
		{
			TRACE1("%s\n", m_ErrInfo);
			return 1;
		}
	}
	return 0;
}

void CHotKeyExec::SortArrayKey(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo, BOOL IsAsc)
{
	CHotKeyExec::HotKeyInfo m_CurHKI;

	for (int i = 0; i < m_HotKeyInfo.GetSize(); i++)
	{
		for (int j = i + 1; j < m_HotKeyInfo.GetSize(); j++)
		{
			if (IsAsc)
			{
				if (m_HotKeyInfo[i].m_CombineKey > m_HotKeyInfo[j].m_CombineKey)
				{
					m_CurHKI = m_HotKeyInfo[j];
					m_HotKeyInfo[j] = m_HotKeyInfo[i];
					m_HotKeyInfo[i] = m_CurHKI;
				}
			}
			else
			{
				if (m_HotKeyInfo[i].m_CombineKey < m_HotKeyInfo[j].m_CombineKey)
				{
					m_CurHKI = m_HotKeyInfo[j];
					m_HotKeyInfo[j] = m_HotKeyInfo[i];
					m_HotKeyInfo[i] = m_CurHKI;
				}
			}
		}
	}
}

long CHotKeyExec::SetRegHotKeyInfo(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo)
{
	char idx[20];
	char KeyData[20];
	CString RegValueName;
	CString RegData;
	RegKeyInfo CurRegInfo;
	int i = 0;
	int nCnt = 0;

	nCnt = m_HotKeyInfo.GetSize(); 
	CurRegInfo.hKey = HKEY_CURRENT_USER;
	CurRegInfo.lpSubKey = "Software\\DeskChargerMFC\\HotkeyInfo";
	CurRegInfo.dwType = REG_SZ;

	//清空原有数据
	for (i = 0; i < 720; i++)
	{
		RegValueName = "HotkeyMain";
		_itoa(i, idx, 10);
		RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		if (SetHotReg(CurRegInfo, true) == false)
		{
			if (m_Ret == ERROR_INVALID_FUNCTION)
				break;
			else
			{
				TRACE1("%s\n", m_ErrInfo);
				return 1;
			}
		}

		RegValueName.Empty();
		RegValueName = "HotkeyDisp";
		RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		if (SetHotReg(CurRegInfo, true) == false)
		{
			if (m_Ret == ERROR_INVALID_FUNCTION)
				break;
			else
			{
				TRACE1("%s\n", m_ErrInfo);
				return 1;
			}
		}

		RegValueName.Empty();
		RegValueName = "HotkeyParm";
		RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		if (SetHotReg(CurRegInfo, true) == false)
		{
			if (m_Ret == ERROR_INVALID_FUNCTION)
				break;
			else
			{
				TRACE1("%s\n", m_ErrInfo);
				return 1;
			}
		}
			
		RegValueName.Empty();
		RegValueName = "HotkeyCmd";
		RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		if (SetHotReg(CurRegInfo, true) == false)
		{
			if (m_Ret == ERROR_INVALID_FUNCTION)
				break;
			else
			{
				TRACE1("%s\n", m_ErrInfo);
				return 1;
			}
		}		
	}

	for (i = 0; i < nCnt; i++)
	{
		//设置数值主要数据
		RegValueName = "HotkeyMain";
		_itoa(i, idx, 10);
		RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		
		CurRegInfo.cbData = 50;

		/*数据格式为：
			3位按键代码
			1位组合键代码
			5位热键ID号
			1位禁止标志
		*/
		RegData.Empty();
		
		_itoa(m_HotKeyInfo[i].m_HotKeyCode, KeyData, 10);
		RegData += KeyData;
		
		_itoa(m_HotKeyInfo[i].m_fsModifiers, KeyData, 10);
		RegData += KeyData;

		_itoa(m_HotKeyInfo[i].m_HotID, KeyData, 10);
		RegData += KeyData;
		
		if (m_HotKeyInfo[i].m_IsEnable == FALSE)
			RegData += "0";
		else
			RegData += "1";

		CurRegInfo.lpSetData = (CONST BYTE *)RegData.GetBuffer(50);
		RegData.ReleaseBuffer(); 
		if (SetHotReg(CurRegInfo) == false)
		{
			TRACE1("%s\n", m_ErrInfo);
			return 1;
		}

		//设置数值显示信息
		RegValueName.Empty();
		RegValueName = "HotkeyDisp";
		RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		
		CurRegInfo.cbData = 255;

		RegData.Empty();
		RegData = m_HotKeyInfo[i].m_StrCmd; 

		CurRegInfo.lpSetData = (CONST BYTE *)RegData.GetBuffer(255);
		RegData.ReleaseBuffer(); 
		if (SetHotReg(CurRegInfo) == false)
		{
			TRACE1("%s\n", m_ErrInfo);
			return 1;
		}

		//设置数值参数信息
		RegValueName.Empty();
		RegValueName = "HotkeyParm";
			RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		
		CurRegInfo.cbData = 255;
		
		RegData.Empty();
		RegData = m_HotKeyInfo[i].m_Parm; 
		
		CurRegInfo.lpSetData = (CONST BYTE *)RegData.GetBuffer(255);
		RegData.ReleaseBuffer(); 
		if (SetHotReg(CurRegInfo) == false)
		{
			TRACE1("%s\n", m_ErrInfo);
			return 1;
		}

		//设置数值命令信息
		RegValueName.Empty();
		RegValueName = "HotkeyCmd";
		RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		
		CurRegInfo.cbData = 255;
		
		RegData.Empty();
		RegData = m_HotKeyInfo[i].m_Command;
		
		CurRegInfo.lpSetData = (CONST BYTE *)RegData.GetBuffer(255);
		RegData.ReleaseBuffer(); 
		if (SetHotReg(CurRegInfo) == false)
		{
			TRACE1("%s\n", m_ErrInfo);
			return 1;
		}
	}
	return 0;
}

long CHotKeyExec::GetRegHotKeyInfo(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo)
{
	RegKeyInfo CurRegInfo;
	CHotKeyExec::HotKeyInfo m_CurHKI;

	CString RegData;
	CString RegValueName;
	char idx[20];
	unsigned long datalen;
	unsigned char querydata[256];
	unsigned long datatype = REG_SZ;
	
	CurRegInfo.hKey = HKEY_CURRENT_USER;
	CurRegInfo.lpSubKey = "Software\\DeskChargerMFC\\HotkeyInfo";
	CurRegInfo.lpType = &datatype;
	for (int i = 0; i < 720; i++)
	{
		//取得主要设置信息
		RegValueName = "HotkeyMain";
		datalen = 256;
		_itoa(i, idx, 10);
		RegValueName += idx;

		CurRegInfo.lpQueryValueName = RegValueName.GetBuffer(15);
		RegValueName.ReleaseBuffer(); 
		CurRegInfo.lpcbData = &datalen;
		CurRegInfo.lpQueryData = querydata;
		
		//如果为取得注册表信息的一般错误时，忽略
		if ((GetHotReg(CurRegInfo) == false))
		{
			if (m_Ret != ERROR_INVALID_FUNCTION)
			{
				TRACE1("%s\n", m_ErrInfo);
				return 1;
			}
			else
				break;
		}
		
		if (m_ErrPos == 0)
		{
			RegData = querydata;
			
			m_CurHKI.m_HotKeyCode = atoi(RegData.Left(3));
			m_CurHKI.m_fsModifiers = atoi(RegData.Mid(3,1));
			m_CurHKI.m_CombineKey = ConvertCombinKey(m_CurHKI.m_fsModifiers);
			TRACE1("m_fsModifiers=%d\n", m_CurHKI.m_fsModifiers);
			if (m_CurHKI.m_CombineKey == "")
		    	break;
			m_CurHKI.m_HotID = atoi(RegData.Mid(4,5));

			if (RegData.Right(1) == '0')
				m_CurHKI.m_IsEnable = FALSE;
			else
				m_CurHKI.m_IsEnable = TRUE;
		}

		//取得显示信息
		RegValueName = "HotkeyDisp";
		datalen = 256;
		RegValueName += idx;

		CurRegInfo.lpQueryValueName = RegValueName.GetBuffer(15);
		RegValueName.ReleaseBuffer(); 
		CurRegInfo.lpcbData = &datalen;
		CurRegInfo.lpQueryData = querydata;
		
		//如果为取得注册表信息的一般错误时，忽略
		if ((GetHotReg(CurRegInfo) == false))
		{
			if (m_Ret != ERROR_INVALID_FUNCTION)
			{
				TRACE1("%s\n", m_ErrInfo);
				return 1;
			}
			else
				break;
		}
		
		if (m_ErrPos == 0)
		{
			RegData = querydata;
			m_CurHKI.m_StrCmd = RegData;
			TRACE1("m_StrCmd=%s\n", m_CurHKI.m_StrCmd);
		}
		
		//取得参数信息
		RegValueName = "HotkeyParm";
		datalen = 256;
		RegValueName += idx;
		
		CurRegInfo.lpQueryValueName = RegValueName.GetBuffer(15);
		RegValueName.ReleaseBuffer(); 
		CurRegInfo.lpcbData = &datalen;
		CurRegInfo.lpQueryData = querydata;

		//如果为取得注册表信息的一般错误时，忽略
		if ((GetHotReg(CurRegInfo) == false))
		{
			if (m_Ret != ERROR_INVALID_FUNCTION)
			{
				TRACE1("%s\n", m_ErrInfo);
				return 1;
			}
			else
				break;
		}
		
		if (m_ErrPos == 0)
		{
			RegData = querydata;
			m_CurHKI.m_Parm = RegData;
			TRACE1("m_Parm=%s\n", m_CurHKI.m_Parm);
		}

		//取得命令信息
		RegValueName = "HotkeyCmd";
		datalen = 256;
		RegValueName += idx;
		
		CurRegInfo.lpQueryValueName = RegValueName.GetBuffer(15);
		RegValueName.ReleaseBuffer(); 
		CurRegInfo.lpcbData = &datalen;
		CurRegInfo.lpQueryData = querydata;

		//如果为取得注册表信息的一般错误时，忽略
		if ((GetHotReg(CurRegInfo) == false))
		{
			if (m_Ret != ERROR_INVALID_FUNCTION)
			{
				TRACE1("%s\n", m_ErrInfo);
				return 1;
			}
			else
				break;
		}
		
		if (m_ErrPos == 0)
		{
			RegData = querydata;
			m_CurHKI.m_Command = RegData;
			TRACE1("m_Command=%s\n", m_CurHKI.m_Command);
		}

		m_CurHKI.m_IsModify = FALSE;
		m_CurHKI.m_IsDelete = FALSE;

		m_HotKeyInfo.Add(m_CurHKI);
	}
	return 0;
}

void CHotKeyExec::UserInit()
{
	if (GetRegHotKeyInfo(m_HotKeyInfo))
		AfxMessageBox(m_ErrInfo);

	SortArrayKey(m_HotKeyInfo, TRUE);
}

CString CHotKeyExec::ConvertCombinKey(long fsModifiers)
{
	switch (fsModifiers)
	{
	case 1:
		return "S";
		break;
	case 2:
		return "C";
		break;
	case 3:
		return "C+S";
		break;
	case 4:
		return "A";
		break;
	case 5:
		return "A+S";
		break;
	case 7:
		return "C+A+S";
		break;
	}
	return "";
}

void CHotKeyExec::ChangeToAppDir(CString m_StrAppCmd)
{
	CString StrTmp;
	int iPos = m_StrAppCmd.ReverseFind('\\');

	if (iPos == -1)
		return;

	StrTmp = m_StrAppCmd.Left(iPos + 1);

	SetCurrentDirectory(StrTmp);
}