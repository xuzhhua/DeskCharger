/*
*****************************************************
�๦�ܣ���ϵͳ��ע���ע�ᡢ�޸ġ�ɾ����ȡ���ȼ���Ϣ
���ߣ����ٻ�

�޸ļ�¼��
    2002.12.17  ����
	2003.03.09  ���ڶ�ʱ���ܲ���Ҫע���ȼ������Խ�ע
	            ����������Ϊ����

*****************************************************
*/
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CRegExec  //��ע������/ȡ����Ϣ����
{
public:
	CRegExec();
	~CRegExec();
	struct RegKeyInfo //�ȼ���Ϣ�Ľṹ������ȡ��ע����������õ���Ϣ
	{
		//RegOpenKey/RegCreateKey/RegDeleteKey/RegCloseKeyʹ��
		HKEY    hKey;             // Ҫ�򿪵ĸ�Key���
		LPCTSTR lpSubKey;         // Ҫ�򿪵�SubKey���ַ���
		PHKEY   phkResult;        // �򿪼��ľ��ָ��(��Ҫ��ֵ)
		HKEY    hKeyResult;       // �򿪼��ľ��(��Ҫ��ֵ)
		//RegQueryValueExʹ��
		LPTSTR  lpQueryValueName; // ���������ַ���(RegQueryValueEx��)
		LPDWORD lpType;           // ��ȡֵ����(RegQueryValueEx��)
		LPBYTE  lpQueryData;      // ���ݻ�����(RegQueryValueEx��)
		LPDWORD lpcbData;         // ���ݻ�������С(RegQueryValueEx��)
		//RegSetValueExʹ��
		LPCTSTR lpSetValueName;   // ���������ַ���(RegSetValueEx��)
		DWORD   dwType;           // ���õ���������(RegSetValueExʹ��)
		CONST   BYTE *lpSetData;  // ���ݵ�ַ(RegSetValueEx��)
		DWORD   cbData;           // ���ݴ�С(RegSetValueEx��)
	};
	//ȫ��ʹ��
	CString m_ErrInfo;            // ������ִ��ʧ�ܣ����ش�����Ϣ
	long m_Ret;                   // ������ִ��ʧ�ܣ����ش���
	long m_ErrPos;                // ������ִ��ʧ�ܣ����ش���λ��
	bool GetHotReg(RegKeyInfo &GetRegKeyInfo); //ȡ��ע�����Ϣ
	bool SetHotReg(RegKeyInfo &SetRegKeyInfo, bool IsDelete = false); //����ע�����Ϣ
	void ErrMsgGet(CString &ErrMsg, long ErrCD, long ErrPos);  //ȡ�ò���ʾ������Ϣ
};

class CHotRegExec :  public CRegExec//ִ���ȼ���Ϣ��
{
public:
	//�����ȼ�
	bool SetHotKey(HWND hWnd, int id, UINT fsModifiers, UINT vk); //�޸ġ��½��ȼ�
	bool SetHotKey(HWND hWnd, int id); //ɾ���ȼ�
};
