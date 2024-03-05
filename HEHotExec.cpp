//*****************************************************
//类功能：向系统及注册表注册、修改、删除、取得热键信息
//
//建立时间：2002.12.17
//
//作者：徐仲华
//*****************************************************

#include "stdafx.h"
#include "HEHotExec.h"
#include "resource.h"

bool CHotRegExec::SetHotKey(HWND hWnd, int id) //注销热键
{
	m_ErrPos = 0;
	m_Ret = 0;

	if (!UnregisterHotKey(hWnd, id))
	{
		m_ErrPos = 9;
		m_Ret = GetLastError();

		if (m_Ret == ERROR_HOTKEY_NOT_REGISTERED)
			return true;
		
		ErrMsgGet(m_ErrInfo, m_Ret, m_ErrPos);
		TRACE("注销热键失败\n");
		return false;
	}

	return true;
}

bool CHotRegExec::SetHotKey(HWND hWnd, int id, UINT fsModifiers, UINT vk) //注册/修改热键
{
	m_ErrPos = 0;
	m_Ret = 0;

	//由于系统的原因Shift与Alt相互转换
	switch (fsModifiers)
	{
	case 4:
		fsModifiers = 1;
		break;
	case 1:
		fsModifiers = 4;
		break;
	case 3:
		fsModifiers = 6;
		break;
	case 6:
		fsModifiers = 3;
		break;
	}

	if (!RegisterHotKey(hWnd, id, fsModifiers, vk))
	{
		m_ErrPos = 10;
		m_Ret = GetLastError();

		if (m_Ret == ERROR_HOTKEY_ALREADY_REGISTERED)
			return true;

		ErrMsgGet(m_ErrInfo, m_Ret, m_ErrPos);
		TRACE1("hWnd: %d\n", hWnd);
		TRACE1("id: %d\n", id);
		TRACE1("fsModifiers: %d\n", fsModifiers);
		TRACE1("vk: %d\n", vk);
		TRACE("注册/修改热键失败\n");
		return false;
	}

	return true;
}

CRegExec::CRegExec()
{
	m_ErrInfo.Empty();
	m_ErrPos = 0;
	m_Ret = 0;
}

CRegExec::~CRegExec()
{
	m_ErrInfo.Empty();
}

bool CRegExec::GetHotReg(CRegExec::RegKeyInfo &GetRegKeyInfo) //取得注册表信息
{
	m_ErrPos = 0;
	m_Ret = 0;

	GetRegKeyInfo.phkResult = &GetRegKeyInfo.hKeyResult; //句柄间建立对应关系
	if (m_Ret = RegOpenKey(GetRegKeyInfo.hKey, GetRegKeyInfo.lpSubKey, GetRegKeyInfo.phkResult) != ERROR_SUCCESS)
	{
		m_ErrPos = 1;
		ErrMsgGet(m_ErrInfo, m_Ret, m_ErrPos);
		return false;
	}
	else
	{
		if (m_Ret = RegQueryValueEx(GetRegKeyInfo.hKeyResult, GetRegKeyInfo.lpQueryValueName, NULL, GetRegKeyInfo.lpType, GetRegKeyInfo.lpQueryData, GetRegKeyInfo.lpcbData) != ERROR_SUCCESS)
		{
			m_ErrPos = 2;
			ErrMsgGet(m_ErrInfo, m_Ret, m_ErrPos);
			return false;
		}
		else if (m_Ret = RegCloseKey(GetRegKeyInfo.hKeyResult) != ERROR_SUCCESS)
		{
			m_ErrPos = 3;
			ErrMsgGet(m_ErrInfo, m_Ret, m_ErrPos);
			return false;
		}
	}
	
	return true;
}

bool CRegExec::SetHotReg(CRegExec::RegKeyInfo &SetRegKeyInfo, bool IsDelete) //设置注册表信息
{
	m_ErrPos = 0;
	m_Ret = 0;

	SetRegKeyInfo.phkResult = &SetRegKeyInfo.hKeyResult; //句柄间建立对应关系
	if (RegOpenKey(SetRegKeyInfo.hKey, SetRegKeyInfo.lpSubKey, SetRegKeyInfo.phkResult) != ERROR_SUCCESS) //打开注册表键值
	{
		if (IsDelete == true)
			return true;

		if (m_Ret = RegCreateKey(SetRegKeyInfo.hKey, SetRegKeyInfo.lpSubKey, SetRegKeyInfo.phkResult) != ERROR_SUCCESS) //新建注册表键值
		{
			m_ErrPos = 4;
			ErrMsgGet(m_ErrInfo, m_Ret, m_ErrPos);
			return false;
		}
		else if (m_Ret = RegOpenKey(SetRegKeyInfo.hKey, SetRegKeyInfo.lpSubKey, SetRegKeyInfo.phkResult) != ERROR_SUCCESS) //打开注册表键值
		{
			m_ErrPos = 5;
			ErrMsgGet(m_ErrInfo, m_Ret, m_ErrPos);
			return false;
		}
	}

	if (IsDelete == false)
	{
		if (m_Ret = RegSetValueEx(SetRegKeyInfo.hKeyResult, SetRegKeyInfo.lpSetValueName, 0, SetRegKeyInfo.dwType, SetRegKeyInfo.lpSetData, SetRegKeyInfo.cbData) != ERROR_SUCCESS) //设置注册表键值的数据
		{
			m_ErrPos = 6;
			ErrMsgGet(m_ErrInfo, m_Ret, m_ErrPos);
			return false;
		}
	}
	else
	{
		if (m_Ret = RegDeleteValue(SetRegKeyInfo.hKeyResult, SetRegKeyInfo.lpSetValueName) != ERROR_SUCCESS) //删除键值数据
		{
			m_ErrPos = 7;
			ErrMsgGet(m_ErrInfo, m_Ret, m_ErrPos);
			return false;
		}
	}
	
	if (m_Ret = RegCloseKey(SetRegKeyInfo.hKeyResult) != ERROR_SUCCESS) //关闭注册表键值
	{
		m_ErrPos = 8;
		ErrMsgGet(m_ErrInfo, m_Ret, m_ErrPos);
		return false;
	}
	return true;
}

void CRegExec::ErrMsgGet(CString &ErrMsg, long ErrCD, long ErrPos)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		ErrCD,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
	);
	char chErrCD[20];
	CString resErrPos;
	resErrPos.LoadString(IDS_ERRMSGPOS);

	ErrMsg.LoadString(IDS_ERRMSGCODE); 
	ErrMsg += _itoa(ErrCD, chErrCD, 10);
	ErrMsg += "\n";
	ErrMsg += (LPCTSTR)lpMsgBuf;
	ErrMsg += resErrPos;
	ErrMsg += _itoa(ErrPos, chErrCD, 10);
	// Free the buffer.
	//MessageBox(NULL, ErrMsg, "发生错误", MB_OK | MB_ICONINFORMATION);
	LocalFree(lpMsgBuf);
}
