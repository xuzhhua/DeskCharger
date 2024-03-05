/*
********************************************************************
类功能：建立与CD-ROM相关的信息，使之拥有热键开关、自动关闭等功能

作者：徐仲华

修改纪录：
    2002.12.19  建立
	2003.03.09  更改取得信息的方法，做出CD-ROM信息结构
********************************************************************
*/

#include "stdafx.h"
#include "HECDROM.H"
#include "resource.h"

CHotCDROMExec::CHotCDROMExec()
{
	//取得CD-ROM的个数
	m_CDROMNumber = GetCDROMBaseInfo(m_CDROMInfo);
	//TRACE1("CD-ROM数量：%d\n", m_CDROMNumber);
	if (m_CDROMNumber > 0)
	{
		//初始化CD-ROM信息
		for (int i = 0; i < m_CDROMNumber; i++)
		{
			m_CDROMInfo[i].m_IsMainCDROM = false;
			m_CDROMInfo[i].m_IsDefault = true;
			m_CDROMInfo[i].m_IsEnable = true;
			m_CDROMInfo[i].m_IsOpened = false;
		}

		if (GetCDROMRegInfo(m_CDROMInfo))
			AfxMessageBox(m_ErrInfo);
		if (SetCDROMRegInfo(m_CDROMInfo))
			AfxMessageBox(m_ErrInfo);
	}
}

CHotCDROMExec::~CHotCDROMExec()
{
	m_CDROMInfo.RemoveAll();
}

bool CHotCDROMExec::UpDate_Cds(CString CurrentCD) //更新当前CD-ROM
{
	mciSendString("stop cdaudio", NULL, 0, NULL);
    mciSendString("close cdaudio", NULL, 0, NULL);
    
    mciSendString("open  " + CurrentCD + " type cdaudio alias cdaudio wait shareable", NULL, 0, NULL);
    mciSendString("set cdaudio time format tmsf", NULL, 0, NULL);

	return true;
}

long CHotCDROMExec::GetCDROMBaseInfo(CArray<CDROMInfo, CDROMInfo> &m_CDROMInfos)
{
	CDROMInfo tmpCDROM;
	CString strDriver;
	CString strNameList;
	char cdNameList[256];
	int iPos = 0;
	int NumOfCDROM = 0;

	//取得当前计算机上所有的驱动器
	long ret = GetLogicalDriveStrings(256, cdNameList);
	for (int i = 0;i < ret;i++)
	{
		if (cdNameList[i] != NULL)
		{
			//取得驱动器盘符列表
			strNameList += cdNameList[i];
		}
	}
	
	do
	{
		iPos = strNameList.Find("\\");
		//取得单个驱动器盘符
		strDriver = strNameList.Left(iPos + 1);
		strDriver.MakeUpper();

		if (strDriver.IsEmpty() != 0)
			return NumOfCDROM;

        strNameList = strNameList.Mid(iPos + 1);
		if (GetDriveType(strDriver) == DRIVE_CDROM)
		{
			tmpCDROM.m_CDROMName = strDriver;
			m_CDROMInfos.Add(tmpCDROM);
			NumOfCDROM++;
		}
	} while (iPos > 0 && NumOfCDROM < 10);

	return NumOfCDROM;
}

long CHotCDROMExec::GetCDROMRegInfo(CArray<CDROMInfo, CDROMInfo> &m_CDROMInfos)
{
	RegKeyInfo CurRegInfo;
	CString RegData;
	CString RegValueName;
	char idx[20];
	unsigned long datalen;
	unsigned char querydata[256];
	unsigned long datatype = REG_SZ;
	long Pos = 0;

	//取得CD-ROM的注册表设置信息
	CurRegInfo.hKey = HKEY_CURRENT_USER;
	CurRegInfo.lpSubKey = "Software\\DeskChargerMFC\\CDROMInfo";
	CurRegInfo.lpType = &datatype;
	for (int i = 0; i < m_CDROMInfos.GetSize(); i++)
	{
		RegValueName = "CDROM";
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
			if (RegData.Mid(0, 1) == '1')
				m_CDROMInfos[i].m_IsAutoClose = true;
			else
				m_CDROMInfos[i].m_IsAutoClose = false;

			if (RegData.Mid(1, 1) == '1')
				m_CDROMInfos[i].m_IsAutoEjectbeforeShutdown = true;
			else
				m_CDROMInfos[i].m_IsAutoEjectbeforeShutdown = false;

			if (RegData.Mid(2, 1) == '1')
				m_CDROMInfos[i].m_IsMainCDROM = true;
			else
				m_CDROMInfos[i].m_IsMainCDROM = false;

			Pos = RegData.Find(_T("450"));

			m_CDROMInfos[i].m_AutoCloseTime = atoi(RegData.Mid(3, Pos - 3));
			m_CDROMInfos[i].m_HotID = atoi(RegData.Mid(Pos, 5));
			m_CDROMInfos[i].m_fsModifiers = atoi(RegData.Mid(Pos + 5, 1));
			m_CDROMInfos[i].m_VKeyAsc = atoi(RegData.Mid(Pos + 6, RegData.GetLength() - (Pos + 5)));
			m_CDROMInfos[i].m_IsDefault = false;
			m_CDROMInfos[i].m_IsEnable = true;

			if (m_CDROMInfos[i].m_fsModifiers == 0 || m_CDROMInfos[i].m_VKeyAsc == 0)
			{
				m_CDROMInfos[i].m_fsModifiers = 0;
				m_CDROMInfos[i].m_VKeyAsc = 0;
				m_CDROMInfos[i].m_IsEnable = false;
			}
			
			/*TRACE1("m_IsAutoClose %d\n", m_CDROMInfos[i].m_IsAutoClose);
			TRACE1("m_IsAutoEjectbeforeShutdown %d\n", m_CDROMInfos[i].m_IsAutoEjectbeforeShutdown);
			TRACE1("m_IsMainCDROM %d\n", m_CDROMInfos[i].m_IsMainCDROM);
			TRACE1("m_AutoCloseTime %d\n", m_CDROMInfos[i].m_AutoCloseTime);
			TRACE1("m_HotID %0x\n", m_CDROMInfos[i].m_HotID);
			TRACE1("m_fsModifiers %d\n", m_CDROMInfos[i].m_fsModifiers);
			TRACE1("m_VKeyAsc %d\n", m_CDROMInfos[i].m_VKeyAsc);
			TRACE1("m_IsEnable %d\n", m_CDROMInfos[i].m_IsEnable);*/
		}
		//TRACE1("m_IsDefault %d\n", m_CDROMInfos[i].m_IsDefault);
	}
	return 0;
}

long CHotCDROMExec::SetCDROMRegInfo(CArray<CDROMInfo, CDROMInfo> &m_CDROMInfos)
{
	char idx[20];
	char KeyData[20];
	CString RegValueName;
	CString RegData;
	RegKeyInfo CurRegInfo;
	bool IsMainSeted;
	int i = 0;

	CurRegInfo.hKey = HKEY_CURRENT_USER;
	CurRegInfo.lpSubKey = "Software\\DeskChargerMFC\\CDROMInfo";
	CurRegInfo.dwType = REG_SZ;

	//检查主CD-ROM的设置状态
	for (i = 0; i < m_CDROMInfos.GetSize(); i++)
	{
		if (m_CDROMInfos[i].m_IsMainCDROM == true)
		{
			IsMainSeted = true;
			break;
		}
		else
		{
			IsMainSeted = false;
		}
	}

	//设置第一个CD-ROM为主CD-ROM
	if (IsMainSeted == false)
		m_CDROMInfo[0].m_IsMainCDROM = true;
	
	for (i = 0; i < m_CDROMInfos.GetSize(); i++)
	{
		//监测是否为缺省设置
		if (m_CDROMInfos[i].m_IsDefault == true)
		{
			m_CDROMInfos[i].m_IsAutoClose = true;
			m_CDROMInfos[i].m_AutoCloseTime = 10;
			m_CDROMInfos[i].m_IsAutoEjectbeforeShutdown = true;
			m_CDROMInfos[i].m_VKeyAsc = 48 + i;
			m_CDROMInfos[i].m_fsModifiers = 6;
			m_CDROMInfos[i].m_HotID = 0xB002 + i;
			m_CDROMInfos[i].m_IsEnable = true;
			m_CDROMInfos[i].m_IsDefault = false;
		}
		//设置数值名称和数据
		RegValueName = "CDROM";
		_itoa(i, idx, 10);
		RegValueName += idx;
		CurRegInfo.lpSetValueName = RegValueName;
		
		CurRegInfo.cbData = 200;

		/*数据格式为：
			是否自动关闭，是否在关闭计算机前自动弹出光盘，是否是主CD-ROM，
			自动关闭时间(秒)，热键的代号，控制组合键的代号，热键的ASCII码
		*/
		RegData.Empty(); 
		if (m_CDROMInfos[i].m_IsAutoClose == true)
			RegData += "1";
		else
			RegData += "0";

		if (m_CDROMInfos[i].m_IsAutoEjectbeforeShutdown == true)
			RegData += "1";
		else
			RegData += "0";

		if (m_CDROMInfos[i].m_IsMainCDROM == true)
			RegData += "1";
		else
			RegData += "0";

		_itoa(m_CDROMInfos[i].m_AutoCloseTime, KeyData, 10);
		RegData += KeyData;

		_itoa(m_CDROMInfos[i].m_HotID, KeyData, 10);
		RegData += KeyData;

		_itoa(m_CDROMInfos[i].m_fsModifiers, KeyData, 10);
		RegData += KeyData;

		_itoa(m_CDROMInfos[i].m_VKeyAsc, KeyData, 10);
		RegData += KeyData;

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

long CHotCDROMExec::IsDriverReady(CString DriverName)
{
	char FilePath[256];
	CFileFind CurFindFile;

	sprintf(FilePath, "%s*.*", DriverName);
	
	if (!CurFindFile.FindFile(FilePath))
	{
		/*long ret = GetLastError();
		//如果出现的错误不是设备没有准备好，则返回错误
		if (ret != ERROR_NOT_READY)
		{
			m_ErrPos = 11;
			ErrMsgGet(m_ErrInfo, ret, m_ErrPos);
			TRACE1("%s\n", m_ErrInfo);
			return CHCE_DRIVER_ERR;   //2
		}*/

		return CHCE_DRIVER_NOT_READY; //1
	}

	return CHCE_DRIVER_READY;         //0
}

long CHotCDROMExec::SetCDROMDoor(CString DriverName, bool IsOnlyClose)
{
	long TimeInterval;
	SYSTEMTIME StartTime, EndTime;

	//只是单纯关闭指定的CD-ROM
	if (IsOnlyClose == true)
	{
		UpDate_Cds(DriverName);
		mciSendString("set cdaudio door closed", NULL, 0, NULL);
		mciSendString("stop cdaudio", NULL, 0, NULL);
		mciSendString("close cdaudio", NULL, 0, NULL);
		return 1;
	}

	//if (IsDriverReady(DriverName) == CHCE_DRIVER_ERR)
	//	return 1;

	//如果驱动器已经准备好，则直接弹出托盘
	if (IsDriverReady(DriverName) == CHCE_DRIVER_READY)
	{
		UpDate_Cds(DriverName);
		mciSendString("set cdaudio door open", NULL, 0, NULL);
		return 0;
	}

	UpDate_Cds(DriverName);

	GetSystemTime(&StartTime);  //取得操作前的时间
	mciSendString("set cdaudio door open", NULL, 0, NULL);
	GetSystemTime(&EndTime);    //取得操作后的时间

	//取得操作时间差
	TimeInterval = abs(EndTime.wSecond - StartTime.wSecond);
	/*TRACE0("******************\n");
	TRACE1("StartTime.wSecond: %d\n", StartTime.wSecond);
	TRACE1("EndTime.wSecond: %d\n", EndTime.wSecond);
	TRACE1("StartTime.wMilliseconds: %d\n", StartTime.wMilliseconds);
	TRACE1("EndTime.wMilliseconds: %d\n", EndTime.wMilliseconds);
	TRACE1("TimeInterval: %d\n", abs(EndTime.wMilliseconds - StartTime.wMilliseconds));
	TRACE0("******************\n");*/
	switch (TimeInterval)
	{
	case 0:
		if (abs(EndTime.wMilliseconds - StartTime.wMilliseconds) <= 100)
		{
			mciSendString("set cdaudio door closed", NULL, 0, NULL);
			mciSendString("stop cdaudio", NULL, 0, NULL);
			mciSendString("close cdaudio", NULL, 0, NULL);
			return 1;
		}
	case 1:
		if (abs(EndTime.wMilliseconds - StartTime.wMilliseconds) > 900)
		{
			mciSendString("set cdaudio door closed", NULL, 0, NULL);
			mciSendString("stop cdaudio", NULL, 0, NULL);
			mciSendString("close cdaudio", NULL, 0, NULL);
			return 1;
		}
	}

	return 0;
}