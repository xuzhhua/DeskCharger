/*
********************************************************************
类功能：建立与定时相关的信息，使之拥有定时启动功能

作者：徐仲华

修改纪录：
    2003.07.26  建立
********************************************************************
*/
#include "stdafx.h"
#include "DeskCharger.h"
#include "resource.h"
#include "HETime.h"

CTimeExec::CTimeExec()
{
	if (GetRegHotKeyInfo(m_TimeInfo))
		AfxMessageBox(m_ErrInfo);
	
	SortArrayKey(m_TimeInfo, TRUE);
}

CTimeExec::~CTimeExec()
{
	m_TimeInfo.RemoveAll(); 
}

long CTimeExec::DelHotkeyInfo(CArray<TimeInfo, TimeInfo> &m_TimeInfo)
{
	CArray<TimeInfo, TimeInfo> m_TmpTI;
	int i = 0;
	
	for (i = 0; i < m_TimeInfo.GetSize(); i++)
	{
		if (!m_TimeInfo[i].m_IsDelete)
		{
			m_TmpTI.Add(m_TimeInfo[i]);
		}
	}
	
	m_TimeInfo.RemoveAll();
	
	for (i = 0; i < m_TmpTI.GetSize(); i++)
	{
		m_TimeInfo.Add(m_TmpTI[i]);
	}
	
	return 0;
}

long CTimeExec::SetHotkeyInfo(CArray<TimeInfo, TimeInfo> &m_TimeInfo, CTimeExec::TimeInfo &NewTimeInfo)
{
	//编辑
	int i = 0;

	for (i = 0; i < m_TimeInfo.GetSize(); i++)
	{
		if (m_TimeInfo[i].m_IsModify)
		{
			m_TimeInfo.SetAt(i, NewTimeInfo);
			m_TimeInfo[i].m_IsModify = FALSE;
			break;
		}
	}
	return 0;
}

long CTimeExec::GetRegHotKeyInfo(CArray<TimeInfo, TimeInfo> &m_TimeInfo)
{
	RegKeyInfo CurRegInfo;
	CTimeExec::TimeInfo m_CurTI;

	CString RegData;
	CString RegValueName;
	char idx[20];
	unsigned long datalen;
	unsigned char querydata[256];
	unsigned long datatype = REG_SZ;
	WORD ymd = 0;
	WORD time = 0;
	
	CurRegInfo.hKey = HKEY_CURRENT_USER;
	CurRegInfo.lpSubKey = "Software\\DeskChargerMFC\\TimeInfo";
	CurRegInfo.lpType = &datatype;
	for (int i = 0; i < 20; i++)
	{
		//取得主要设置信息
		RegValueName = "TimeMain";
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
			
			m_CurTI.m_Ymd = atoi(RegData.Left(8));
			m_CurTI.m_Time = atoi(RegData.Mid(8, 6));
			m_CurTI.m_SysCode = atoi(RegData.Mid(14, 1));
			m_CurTI.m_ExecFlag = atoi(RegData.Mid(16, 1));

			if (RegData.Mid(15, 1) == '0')
				m_CurTI.m_IsExec = FALSE;
			else
				m_CurTI.m_IsExec = TRUE;
			TRACE1("m_Ymd=%d\n", m_CurTI.m_Ymd);
			TRACE1("m_Time=%d\n", m_CurTI.m_Time);
			TRACE1("m_SysCode=%d\n", m_CurTI.m_SysCode);
			TRACE1("m_IsExec=%d\n", m_CurTI.m_IsExec);
			TRACE1("m_ExecFlag=%d\n", m_CurTI.m_ExecFlag);
		}

		//取得多次执行的次数
		RegValueName = "TimeTimes";
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
			m_CurTI.m_ExecTimes = atoi(RegData);
			TRACE1("m_ExecTimes=%d\n", m_CurTI.m_ExecTimes);
		}
		
		//取得执行时的提示信息
		RegValueName = "TimeMsg";
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
			m_CurTI.m_ExecMessage = RegData;
			TRACE1("m_ExecMessage=%s\n", m_CurTI.m_ExecMessage);
		}

		//取得执行的间隔时间
		RegValueName = "TimeInterval";
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
			m_CurTI.m_TimeInterval = atoi(RegData);
			TRACE1("m_TimeInterval=%d\n", m_CurTI.m_TimeInterval);
		}

		m_CurTI.m_IsModify = FALSE;
		m_CurTI.m_IsDelete = FALSE;

		m_TimeInfo.Add(m_CurTI);
	}
	return 0;
}

long CTimeExec::SetRegHotKeyInfo(CArray<TimeInfo, TimeInfo> &m_TimeInfo)
{
	char idx[20];
	char KeyData[20];
	CString RegValueName;
	CString RegData;
	RegKeyInfo CurRegInfo;
	int i = 0;
	int nCnt = 0;

	nCnt = m_TimeInfo.GetSize(); 
	CurRegInfo.hKey = HKEY_CURRENT_USER;
	CurRegInfo.lpSubKey = "Software\\DeskChargerMFC\\TimeInfo";
	CurRegInfo.dwType = REG_SZ;

	//清空原有数据
	for (i = 0; i < 20; i++)
	{
		RegValueName = "TimeMain";
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
		RegValueName = "TimeTimes";
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
		RegValueName = "TimeMsg";
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
		RegValueName = "TimeInterval";
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
		RegValueName = "TimeMain";
		_itoa(i, idx, 10);
		RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		
		CurRegInfo.cbData = 50;

		/*数据格式为：
			8位年月日
			6位时间
			1位系统功能区分
			1位执行标志
			1位定时功能区分
		*/
		RegData.Empty();
		
		_itoa(m_TimeInfo[i].m_Ymd, KeyData, 10);
		RegData += KeyData;
		
		_itoa(m_TimeInfo[i].m_Time, KeyData, 10);
		RegData += KeyData;

		_itoa(m_TimeInfo[i].m_SysCode, KeyData, 10);
		RegData += KeyData;
		
		if (m_TimeInfo[i].m_IsExec == FALSE)
			RegData += "0";
		else
			RegData += "1";

		_itoa(m_TimeInfo[i].m_ExecFlag, KeyData, 10);
		RegData += KeyData;

		CurRegInfo.lpSetData = (CONST BYTE *)RegData.GetBuffer(50);
		RegData.ReleaseBuffer(); 
		if (SetHotReg(CurRegInfo) == false)
		{
			TRACE1("%s\n", m_ErrInfo);
			return 1;
		}

		//设置多次执行的次数信息
		RegValueName.Empty();
		RegValueName = "TimeTimes";
		RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		
		CurRegInfo.cbData = 255;

		RegData.Empty();
		_itoa(m_TimeInfo[i].m_ExecTimes, KeyData, 10);
		RegData += KeyData;
		
		CurRegInfo.lpSetData = (CONST BYTE *)RegData.GetBuffer(255);
		RegData.ReleaseBuffer(); 
		if (SetHotReg(CurRegInfo) == false)
		{
			TRACE1("%s\n", m_ErrInfo);
			return 1;
		}

		//设置执行的提示消息信息
		RegValueName.Empty();
		RegValueName = "TimeMsg";
			RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		
		CurRegInfo.cbData = 255;
		
		RegData.Empty();
		RegData = m_TimeInfo[i].m_ExecMessage; 
		
		CurRegInfo.lpSetData = (CONST BYTE *)RegData.GetBuffer(255);
		RegData.ReleaseBuffer(); 
		if (SetHotReg(CurRegInfo) == false)
		{
			TRACE1("%s\n", m_ErrInfo);
			return 1;
		}

		//设置数值命令信息
		RegValueName.Empty();
		RegValueName = "TimeInterval";
		RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		
		CurRegInfo.cbData = 255;
		
		RegData.Empty();
		_itoa(m_TimeInfo[i].m_TimeInterval, KeyData, 10);
		RegData += KeyData;
		
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

void CTimeExec::SortArrayKey(CArray<TimeInfo, TimeInfo> &m_TimeInfo, BOOL IsAsc)
{
	CTimeExec::TimeInfo m_CurTI;
	
	for (int i = 0; i < m_TimeInfo.GetSize(); i++)
	{
		for (int j = i + 1; j < m_TimeInfo.GetSize(); j++)
		{
			if (IsAsc)
			{
				if (m_TimeInfo[i].m_Ymd > m_TimeInfo[j].m_Ymd)
				{
					m_CurTI = m_TimeInfo[j];
					m_TimeInfo[j] = m_TimeInfo[i];
					m_TimeInfo[i] = m_CurTI;
				}
			}
			else
			{
				if (m_TimeInfo[i].m_Ymd < m_TimeInfo[j].m_Ymd)
				{
					m_CurTI = m_TimeInfo[j];
					m_TimeInfo[j] = m_TimeInfo[i];
					m_TimeInfo[i] = m_CurTI;
				}
			}
		}
	}
}