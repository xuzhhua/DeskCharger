/*
********************************************************************
�๦�ܣ������붨ʱ��ص���Ϣ��ʹ֮ӵ�ж�ʱ��������

���ߣ����ٻ�

�޸ļ�¼��
    2003.07.12  ����
********************************************************************
*/

#include "HEHotExec.h"
#include <Afxtempl.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//ExecFlag����
#define CTE_MSG        0x00000000
#define CTE_EXEC       0x00000001
#define CTE_SYS        0x00000002

//SysCode����
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

	void GetTimeInfo(CTime CurTime, CString ExecMessage, long ExecTimes = 0, long TimeInterval = 0, long SysCode = 0, bool IsExec = true, long ExecFlag = 0);  //ȡ�ö�ʱ����Ϣ

	struct TimeInfo              //��ʱִ�е���Ϣ�洢�ṹ
	{
		long    m_Ymd;           //��ʱ��������(�����ÿ�죬������Ϊ99999999)
		long    m_Time;          //��ʱ��ʱ��
		CString m_ExecMessage;   //��ʱ���ѵ���Ϣ(���m_ExecFlag!=0�������)
		long    m_ExecTimes;     //���ִ�еĴ���
		long    m_TimeInterval;  //������ѵļ��ʱ��(��λ���룬���ExecTimes=0�������)
		long    m_SysCode;       //��ʱִ��ϵͳ���ܵĹ�������(���m_ExecFlag=0�������)
		BOOL    m_IsExec;        //�Ƿ�ִ�еı�־
		BOOL    m_IsDelete;      //ɾ����־
		BOOL    m_IsModify;      //�༭��־
		long    m_ExecFlag;      //��ʱִ�еĹ�������
		long    m_ListIdx;       //�б�����
	};
	CArray<TimeInfo, TimeInfo> m_TimeInfo;

	long DelHotkeyInfo(CArray<TimeInfo, TimeInfo> &m_TimeInfo);    //ɾ����Ϣ
	long SetHotkeyInfo(CArray<TimeInfo, TimeInfo> &m_TimeInfo, TimeInfo &NewTimeInfo);    //�༭��Ϣ
	
	long GetRegHotKeyInfo(CArray<TimeInfo, TimeInfo> &m_TimeInfo); //ȡ��ע�����Ϣ
	long SetRegHotKeyInfo(CArray<TimeInfo, TimeInfo> &m_TimeInfo); //����ע�����Ϣ

	void SortArrayKey(CArray<TimeInfo, TimeInfo> &m_TimeInfo, BOOL IsAsc = FALSE); //������ϼ�����ȱʡ�ǽ���
	
};