/*
********************************************************************
�๦�ܣ��������ȼ���ص���Ϣ��ʹ֮ӵ���ȼ���������

���ߣ����ٻ�

�޸ļ�¼��
    2003.04.27  ����
********************************************************************
*/

#include "HEHotExec.h"
#include <Afxtempl.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CHotKeyExec : public CHotRegExec
{
public:
	CHotKeyExec();
	~CHotKeyExec();
	struct HotKeyInfo                               //�ȼ���Ϣ�ṹ
	{
		CString     m_StrCmd;					    //������ʾ
		CString     m_Command;                      //����
		CString     m_Parm;                         //����
		long        m_HotKeyCode;                   //�ȼ�����
		long        m_fsModifiers;                  //������ϼ��Ĵ���
		long        m_HotID;                        //�ȼ��Ĵ���
		CString     m_CombineKey;                   //��ϼ��ַ�(C��A��S)
		BOOL        m_IsDelete;                     //ɾ����־
		BOOL        m_IsModify;                     //�༭��־
		BOOL        m_IsEnable;                     //��ֹ��־
		long        m_ListIdx;                      //�б�����(���Ǵ�1��ʼ)
	};

	struct InHotKeyInfo                             //�����ȼ���Ϣ�ṹ
	{
		CString     m_StrCmd;					    //������ʾ
		CString     m_Command;                      //����
		CString     m_Parm;                         //����
		long        m_HotKeyCode;                   //�ȼ�����
		BOOL        m_IsEnable;                     //��ֹ��־
		long        m_HotID;                        //�ȼ��Ĵ���
	};

	struct AddNumInfo                               //���ʱ��������Ϣ
	{
		int  m_A;
		int  m_C;
		int  m_S;
		int  m_AS;
		int  m_CS;
		int  m_CAS;
	};
	
	InHotKeyInfo m_IHI[12];                         //�����ȼ���Ϣ�Ĵ洢����
	CArray<HotKeyInfo, HotKeyInfo> m_HotKeyInfo;    //�ȼ���Ϣ�Ĵ洢����

	long SetInHotkeyInfo();                         //���������ȼ���������Ϣ
	long GetInHotkeyInfo();                         //ȡ�������ȼ���������Ϣ

	long DelHotkeyInfo(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo);    //ɾ����Ϣ
	long SetHotkeyInfo(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo, HotKeyInfo &NewHotKeyInfo, BOOL IsAdd = FALSE);    //���/�༭��Ϣ

	long GetRegHotKeyInfo(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo); //ȡ��ע�����Ϣ
	long SetRegHotKeyInfo(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo); //����ע�����Ϣ

	void SortArrayKey(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo, BOOL IsAsc = FALSE); //������ϼ�����ȱʡ�ǽ���
	CString ConvertCombinKey(long fsModifiers);  //ת����ϼ����ַ����
	void UserInit();                                //�û��ȼ���ʼ��
	void ChangeToAppDir(CString m_StrAppCmd);  //ת�������л���Ӧ�ó���Ĺ���Ŀ¼
		
protected:
	void InInit();                                  //�����ȼ���ʼ��
};