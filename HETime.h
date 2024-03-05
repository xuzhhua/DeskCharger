/*
********************************************************************
类功能：建立与定时相关的信息，使之拥有定时启动功能

作者：徐仲华

修改纪录：
    2003.07.12  建立
********************************************************************
*/

#include "HEHotExec.h"
#include <Afxtempl.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//ExecFlag分类
#define CTE_MSG        0x00000000
#define CTE_EXEC       0x00000001
#define CTE_SYS        0x00000002

//SysCode分类
#define CTE_SHUTDOWN   0x00000000
#define CTE_RESTART    0x00000001
#define CTE_LOGOFF     0x00000002
#define CTE_WAIT       0x00000003
#define CTE_SLEEP      0x00000004
#define CTE_SCREENSAV  0x00000005

class CTimeExec : public CRegExec
{
public:
	CTimeExec();
	~CTimeExec();

	void GetTimeInfo(CTime CurTime, CString ExecMessage, long ExecTimes = 0, long TimeInterval = 0, long SysCode = 0, bool IsExec = true, long ExecFlag = 0);  //取得定时的信息

	struct TimeInfo              //定时执行的信息存储结构
	{
		long    m_Ymd;           //定时的年月日(如果是每天，则设置为99999999)
		long    m_Time;          //定时的时间
		CString m_ExecMessage;   //定时提醒的消息(如果m_ExecFlag!=0，则忽略)
		long    m_ExecTimes;     //多次执行的次数
		long    m_TimeInterval;  //多次提醒的间隔时间(单位是秒，如果ExecTimes=0，则忽略)
		long    m_SysCode;       //定时执行系统功能的功能区分(如果m_ExecFlag=0，则忽略)
		BOOL    m_IsExec;        //是否执行的标志
		BOOL    m_IsDelete;      //删除标志
		BOOL    m_IsModify;      //编辑标志
		long    m_ExecFlag;      //定时执行的功能区分
		long    m_ListIdx;       //列表索引
	};
	CArray<TimeInfo, TimeInfo> m_TimeInfo;

	long DelHotkeyInfo(CArray<TimeInfo, TimeInfo> &m_TimeInfo);    //删除信息
	long SetHotkeyInfo(CArray<TimeInfo, TimeInfo> &m_TimeInfo, TimeInfo &NewTimeInfo);    //编辑信息
	
	long GetRegHotKeyInfo(CArray<TimeInfo, TimeInfo> &m_TimeInfo); //取得注册表信息
	long SetRegHotKeyInfo(CArray<TimeInfo, TimeInfo> &m_TimeInfo); //设置注册表信息

	void SortArrayKey(CArray<TimeInfo, TimeInfo> &m_TimeInfo, BOOL IsAsc = FALSE); //按照组合键排序，缺省是降序
	
};