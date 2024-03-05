/*
********************************************************************
类功能：建立与热键相关的信息，使之拥有热键启动功能

作者：徐仲华

修改纪录：
    2003.04.27  建立
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
	struct HotKeyInfo                               //热键信息结构
	{
		CString     m_StrCmd;					    //功能显示
		CString     m_Command;                      //命令
		CString     m_Parm;                         //参数
		long        m_HotKeyCode;                   //热键代码
		long        m_fsModifiers;                  //控制组合键的代号
		long        m_HotID;                        //热键的代号
		CString     m_CombineKey;                   //组合键字符(C、A、S)
		BOOL        m_IsDelete;                     //删除标志
		BOOL        m_IsModify;                     //编辑标志
		BOOL        m_IsEnable;                     //禁止标志
		long        m_ListIdx;                      //列表索引(总是从1开始)
	};

	struct InHotKeyInfo                             //内置热键信息结构
	{
		CString     m_StrCmd;					    //功能显示
		CString     m_Command;                      //命令
		CString     m_Parm;                         //参数
		long        m_HotKeyCode;                   //热键代码
		BOOL        m_IsEnable;                     //禁止标志
		long        m_HotID;                        //热键的代号
	};

	struct AddNumInfo                               //添加时的数字信息
	{
		int  m_A;
		int  m_C;
		int  m_S;
		int  m_AS;
		int  m_CS;
		int  m_CAS;
	};
	
	InHotKeyInfo m_IHI[12];                         //内置热键信息的存储数组
	CArray<HotKeyInfo, HotKeyInfo> m_HotKeyInfo;    //热键信息的存储数组

	long SetInHotkeyInfo();                         //设置内置热键的允许信息
	long GetInHotkeyInfo();                         //取得内置热键的允许信息

	long DelHotkeyInfo(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo);    //删除信息
	long SetHotkeyInfo(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo, HotKeyInfo &NewHotKeyInfo, BOOL IsAdd = FALSE);    //添加/编辑信息

	long GetRegHotKeyInfo(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo); //取得注册表信息
	long SetRegHotKeyInfo(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo); //设置注册表信息

	void SortArrayKey(CArray<HotKeyInfo, HotKeyInfo> &m_HotKeyInfo, BOOL IsAsc = FALSE); //按照组合键排序，缺省是降序
	CString ConvertCombinKey(long fsModifiers);  //转换组合键的字符组合
	void UserInit();                                //用户热键初始化
	void ChangeToAppDir(CString m_StrAppCmd);  //转换并且切换到应用程序的工作目录
		
protected:
	void InInit();                                  //内置热键初始化
};