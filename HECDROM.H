/*
********************************************************************
�๦�ܣ�������CD-ROM��ص���Ϣ��ʹ֮ӵ���ȼ����ء��Զ��رյȹ���

���ߣ����ٻ�

�޸ļ�¼��
    2002.12.19  ����
	2003.03.09  ����ȡ����Ϣ�ķ���������CD-ROM��Ϣ�ṹ
	2003.03.30  ����m_IsOpened�����ڱ���CD-ROM�Ƿ��Ѿ��򿪵���Ϣ
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
	struct CDROMInfo  //CD-ROM��Ϣ�ṹ
	{
		CString     m_CDROMName;                 //Ҫ��ѯ��CD-ROM�̷�
		bool        m_IsMainCDROM;               //�Ƿ�����CD-ROM
		bool        m_IsAutoClose;               //�Ƿ��Զ��ر�
		long        m_AutoCloseTime;             //�Զ��ر�ʱ��(��)
		bool        m_IsAutoEjectbeforeShutdown; //�Ƿ��ڹرռ����ǰ�Զ���������
		long        m_fsModifiers;               //������ϼ��Ĵ���
		long        m_VKeyAsc;                   //�ȼ���ASCII��
		long        m_HotID;                     //�ȼ��Ĵ���
		bool        m_IsDefault;                 //�Ƿ�Ҫȱʡ������Ϣ
		bool        m_IsEnable;                  //CD-ROM�Ƿ񱻽�ֹ
		bool        m_IsOpened;                  //CD-ROM�Ƿ��Ѿ���
	};

	CArray<CDROMInfo, CDROMInfo> m_CDROMInfo;    //CD-ROM��Ϣ�Ĵ洢����

	bool UpDate_Cds(CString CurrentCD);          //���µ�ǰCD-ROM
	long GetCDROMBaseInfo(CArray<CDROMInfo, CDROMInfo> &m_CDROMInfos);  //ȡ��CD-ROM������Ϣ�������̷�����Ŀ
	long GetCDROMRegInfo(CArray<CDROMInfo, CDROMInfo> &m_CDROMInfos);   //ȡ��CD-ROM����Ϣ�������ȼ����Զ��ر���Ϣ����CD-ROM��Ϣ���Զ�������Ϣ
	long SetCDROMRegInfo(CArray<CDROMInfo, CDROMInfo> &m_CDROMInfos);   //����CD-ROM����Ϣ�������ȼ����Զ��ر���Ϣ����CD-ROM��Ϣ���Զ�������Ϣ]
	long IsDriverReady(CString DriverName);                             //����������Ƿ��Ѿ�׼����
	long SetCDROMDoor(CString DriverName, bool IsOnlyClose = false);    //����CD-ROM�����̿���״̬

protected:
	long m_CDROMNumber;                          //�������CD-ROM�ĸ���
};