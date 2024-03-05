/*
********************************************************************
类功能：建立与CD-ROM相关的信息，使之拥有热键开关、自动关闭等功能

作者：徐仲华

修改纪录：
    2002.12.19  建立
	2003.03.09  更改取得信息的方法，做出CD-ROM信息结构
	2003.03.30  添加m_IsOpened，用于保存CD-ROM是否已经打开的信息
********************************************************************
*/

//#include "stdafx.h"
#include "HEHotExec.h"
#include <Afxtempl.h>

#define CHCE_DRIVER_READY      0L
#define CHCE_DRIVER_NOT_READY  1L
#define CHCE_DRIVER_ERR        2L

class CHotCDROMExec : public CHotRegExec
{
public:
	CHotCDROMExec();
	~CHotCDROMExec();
	struct CDROMInfo  //CD-ROM信息结构
	{
		CString     m_CDROMName;                 //要查询的CD-ROM盘符
		bool        m_IsMainCDROM;               //是否是主CD-ROM
		bool        m_IsAutoClose;               //是否自动关闭
		long        m_AutoCloseTime;             //自动关闭时间(秒)
		bool        m_IsAutoEjectbeforeShutdown; //是否在关闭计算机前自动弹出光盘
		long        m_fsModifiers;               //控制组合键的代号
		long        m_VKeyAsc;                   //热键的ASCII码
		long        m_HotID;                     //热键的代号
		bool        m_IsDefault;                 //是否要缺省设置信息
		bool        m_IsEnable;                  //CD-ROM是否被禁止
		bool        m_IsOpened;                  //CD-ROM是否已经打开
	};

	CArray<CDROMInfo, CDROMInfo> m_CDROMInfo;    //CD-ROM信息的存储数组

	bool UpDate_Cds(CString CurrentCD);          //更新当前CD-ROM
	long GetCDROMBaseInfo(CArray<CDROMInfo, CDROMInfo> &m_CDROMInfos);  //取得CD-ROM基本信息，包括盘符、数目
	long GetCDROMRegInfo(CArray<CDROMInfo, CDROMInfo> &m_CDROMInfos);   //取得CD-ROM的信息，包括热键、自动关闭信息、主CD-ROM信息和自动弹出信息
	long SetCDROMRegInfo(CArray<CDROMInfo, CDROMInfo> &m_CDROMInfos);   //设置CD-ROM的信息，包括热键、自动关闭信息、主CD-ROM信息和自动弹出信息]
	long IsDriverReady(CString DriverName);                             //检查驱动器是否已经准备好
	long SetCDROMDoor(CString DriverName, bool IsOnlyClose = false);    //设置CD-ROM的托盘开关状态

protected:
	long m_CDROMNumber;                          //计算机上CD-ROM的个数
};