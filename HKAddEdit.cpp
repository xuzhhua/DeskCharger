// HKAddEdit.cpp : implementation file
//

#include "stdafx.h"
#include "DeskCharger.h"
#include "HKAddEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHKAddEdit dialog


CHKAddEdit::CHKAddEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CHKAddEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHKAddEdit)
	//}}AFX_DATA_INIT
}

CHKAddEdit::CHKAddEdit(CArray<CHotKeyExec::HotKeyInfo, CHotKeyExec::HotKeyInfo> &NewHotKeyInfo, CHotKeyExec::AddNumInfo m_NewNumInfo, CWnd* pParent)
	: CDialog(CHKAddEdit::IDD, pParent)
{
	m_pHKIAddNew = &NewHotKeyInfo;
	m_NumInfo = m_NewNumInfo;
	m_IsAdd = TRUE;
}

CHKAddEdit::CHKAddEdit(CHotKeyExec::HotKeyInfo &EditHotKeyInfo, CWnd* pParent)
	: CDialog(CHKAddEdit::IDD, pParent)
{
	m_pHKIEdit = &EditHotKeyInfo;
	m_IsAdd = FALSE;
}

void CHKAddEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHKAddEdit)
	DDX_Control(pDX, IDC_KEYSHIFT, m_KeyShift);
	DDX_Control(pDX, IDC_KEYALT, m_KeyAlt);
	DDX_Control(pDX, IDC_HTIINFO, m_HTIInfo);
	DDX_Control(pDX, IDC_ADDEDIT, m_AddEdit);
	DDX_Control(pDX, IDC_CLOSE, m_Close);
	DDX_Control(pDX, IDC_LISTFILES, m_ListFiles);
	DDX_Control(pDX, IDC_KEYCTRL, m_KeyCtrl);
	DDX_Control(pDX, IDC_HTIPARM, m_HTIParm);
	DDX_Control(pDX, IDC_HTICMD, m_HTICmd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHKAddEdit, CDialog)
	//{{AFX_MSG_MAP(CHKAddEdit)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_LISTFILES, OnListfiles)
	ON_BN_CLICKED(IDC_ADDEDIT, OnAddedit)
	ON_EN_SETFOCUS(IDC_HTICMD, OnSetfocusHticmd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHKAddEdit message handlers

void CHKAddEdit::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CHKAddEdit::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

void CHKAddEdit::OnClose() 
{
	CDialog::OnOK();	
}

void CHKAddEdit::OnListfiles() 
{
	OPENFILENAME m_CurFileName;
	char FileName[260];
	CString StrTmp;

    //初始化结构
	ZeroMemory(&m_CurFileName, sizeof(m_CurFileName));
	m_CurFileName.lStructSize = sizeof(m_CurFileName);
	m_CurFileName.hwndOwner = this->m_hWnd;
	m_CurFileName.lpstrFile = FileName;
	m_CurFileName.lpstrFile[0] = '\0';
	m_CurFileName.nMaxFile = sizeof(FileName);
	m_CurFileName.nFilterIndex = 1;
	m_CurFileName.lpstrFileTitle = NULL;
	m_CurFileName.nMaxFileTitle = 0;
	m_CurFileName.lpstrInitialDir = NULL;
	m_CurFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	StrTmp.LoadString(IDS_GETFILENAME);
	StrTmp = StrTmp + '\0' + "*.exe;*.com;*.bat" + '\0' + "*.*" + '\0' + "*.*" + '\0';
	m_CurFileName.lpstrFilter =  StrTmp;
	//*****************************

	if (GetOpenFileName(&m_CurFileName))
		m_HTICmd.SetWindowText(FileName);
}

void CHKAddEdit::OnAddedit() 
{
	CHotKeyExec::HotKeyInfo m_AddEditHotKeyInfo;
	CString m_StrTmp;
	int m_iKeyCombin = 0;

	//取得命令
	m_HTICmd.GetWindowText(m_StrTmp);
	if (!m_StrTmp.IsEmpty())
		m_AddEditHotKeyInfo.m_Command = m_StrTmp;
	else
	{
		m_StrTmp.LoadString(IDS_CMDMUSTINPUT);
		MessageBox(m_StrTmp, NULL, MB_OK | MB_ICONINFORMATION);
		m_HTICmd.SetFocus(); 
		return;
	}

	//取得命令参数
	m_HTIParm.GetWindowText(m_StrTmp);
	if (!m_StrTmp.IsEmpty())
		m_AddEditHotKeyInfo.m_Parm = m_StrTmp;

	//取得功能显示
	m_HTIInfo.GetWindowText(m_StrTmp);
	if (!m_StrTmp.IsEmpty())
		m_AddEditHotKeyInfo.m_StrCmd = m_StrTmp;
	else
		m_AddEditHotKeyInfo.m_StrCmd = m_AddEditHotKeyInfo.m_Command;

	//取得组合键代号及设置组合键字符
	if (m_KeyCtrl.GetCheck())
		m_iKeyCombin += 2;
	if (m_KeyAlt.GetCheck())
		m_iKeyCombin += 4;
	if (m_KeyShift.GetCheck())
		m_iKeyCombin += 1;

	if (m_iKeyCombin == 0 || m_iKeyCombin == 6)
	{
		m_StrTmp.LoadString(IDS_KEYCOMBINMUST);
		MessageBox(m_StrTmp, NULL, MB_OK | MB_ICONINFORMATION);
		m_KeyCtrl.SetFocus(); 
		return;
	}
	m_AddEditHotKeyInfo.m_fsModifiers = m_iKeyCombin;
	m_AddEditHotKeyInfo.m_IsEnable = TRUE;
	switch (m_iKeyCombin)
	{
	case 1:
		m_AddEditHotKeyInfo.m_CombineKey = "S";
		if (m_NumInfo.m_S + 1 > 10 && m_IsAdd == TRUE)
		{
			m_StrTmp.LoadString(IDS_TOOMANYHKI);
			MessageBox(m_StrTmp, NULL, MB_OK | MB_ICONINFORMATION);
			return;
		}
		break;
	case 2:
		m_AddEditHotKeyInfo.m_CombineKey = "C";
		if (m_NumInfo.m_C + 1 > 10 && m_IsAdd == TRUE)
		{
			m_StrTmp.LoadString(IDS_TOOMANYHKI);
			MessageBox(m_StrTmp, NULL, MB_OK | MB_ICONINFORMATION);
			return;
		}
		break;
	case 3:
		m_AddEditHotKeyInfo.m_CombineKey = "C+S";
		if (m_NumInfo.m_CS + 1 > 10 && m_IsAdd == TRUE)
		{
			m_StrTmp.LoadString(IDS_TOOMANYHKI);
			MessageBox(m_StrTmp, NULL, MB_OK | MB_ICONINFORMATION);
			return;
		}
		break;
	case 4:
		m_AddEditHotKeyInfo.m_CombineKey = "A";
		if (m_NumInfo.m_A + 1 > 10 && m_IsAdd == TRUE)
		{
			m_StrTmp.LoadString(IDS_TOOMANYHKI);
			MessageBox(m_StrTmp, NULL, MB_OK | MB_ICONINFORMATION);
			return;
		}
		break;
	case 5:
		m_AddEditHotKeyInfo.m_CombineKey = "A+S";
		if (m_NumInfo.m_AS + 1 > 10 && m_IsAdd == TRUE)
		{
			m_StrTmp.LoadString(IDS_TOOMANYHKI);
			MessageBox(m_StrTmp, NULL, MB_OK | MB_ICONINFORMATION);
			return;
		}
		break;
	case 7:
		m_AddEditHotKeyInfo.m_CombineKey = "C+A+S";
		if (m_NumInfo.m_CAS + 1 > 10 && m_IsAdd == TRUE)
		{
			m_StrTmp.LoadString(IDS_TOOMANYHKI);
			MessageBox(m_StrTmp, NULL, MB_OK | MB_ICONINFORMATION);
			return;
		}
		break;
	}
	if (m_IsAdd)
	{
		m_pHKIAddNew->Add(m_AddEditHotKeyInfo);
		switch (m_iKeyCombin)
		{
		case 1:
			m_NumInfo.m_S++;
			break;
		case 2:
			m_NumInfo.m_C++;
			break;
		case 3:
			m_NumInfo.m_CS++;
			break;
		case 4:
			m_NumInfo.m_A++;
			break;
		case 5:
			m_NumInfo.m_AS++;
			break;
		case 7:
			m_NumInfo.m_CAS++;
			break;
		}
		m_HTICmd.SetWindowText(_T(""));
		m_HTIParm.SetWindowText(_T(""));
		m_HTIInfo.SetWindowText(_T(""));
		m_KeyCtrl.SetCheck(0);
		m_KeyAlt.SetCheck(0);
		m_KeyShift.SetCheck(0);
		m_HTICmd.SetFocus();
	}
	else
	{
		m_AddEditHotKeyInfo.m_IsModify = TRUE;
		*m_pHKIEdit = m_AddEditHotKeyInfo;
	}
}

BOOL CHKAddEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString StrTmp;
	COLORREF	m_shBtnColor = RGB(255,255,210)/*30*/;

	if (m_IsAdd)
	{
		StrTmp.LoadString(IDS_ADDNEW);
		m_AddEdit.SetWindowText(StrTmp);
		m_AddEdit.SetIcon(IDI_NEWINFO);
		m_AddEdit.SetTooltipText(IDS_ADDINFO);
		m_AddEdit.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);
	}
	else
	{
		StrTmp.LoadString(IDS_EDIT);
		m_AddEdit.SetWindowText(StrTmp);
		m_AddEdit.SetIcon(IDI_EDITINFO);
		m_AddEdit.SetTooltipText(IDS_EDITINFO);
		m_AddEdit.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);
	}
	
	m_AddEdit.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);

	m_Close.SetIcon(IDI_CLOSEDLG);
	m_Close.SetTooltipText(IDS_CLOSEDLG);
    m_Close.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);
	m_Close.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	
	m_ListFiles.SetIcon(IDI_OPENFILE);
    m_ListFiles.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);
	m_ListFiles.SetTooltipText(IDS_OPENFILE);

	if (!m_IsAdd)
	{
		m_HTICmd.SetWindowText(m_pHKIEdit->m_Command);
		m_HTIParm.SetWindowText(m_pHKIEdit->m_Parm);
		m_HTIInfo.SetWindowText(m_pHKIEdit->m_StrCmd);
		if (m_pHKIEdit->m_CombineKey.Find("C") != -1)
			m_KeyCtrl.SetCheck(1);
		if (m_pHKIEdit->m_CombineKey.Find("A") != -1)
			m_KeyAlt.SetCheck(1);
		if (m_pHKIEdit->m_CombineKey.Find("S") != -1)
			m_KeyShift.SetCheck(1);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CHKAddEdit::OnSetfocusHticmd() 
{
	//获得焦点时模拟按下Home键
	::SendMessage(m_HTICmd.m_hWnd, WM_KEYDOWN, 36, 0);
}
