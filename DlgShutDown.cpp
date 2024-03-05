// DlgShutDown.cpp : implementation file
//

#include "stdafx.h"
#include "DeskCharger.h"
#include "DlgShutDown.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgShutDown dialog


CDlgShutDown::CDlgShutDown(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShutDown::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShutDown)
	//}}AFX_DATA_INIT
}


void CDlgShutDown::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShutDown)
	DDX_Control(pDX, IDC_RESTART, m_Restart);
	DDX_Control(pDX, IDC_CLOSE, m_ShutDown);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgShutDown, CDialog)
	//{{AFX_MSG_MAP(CDlgShutDown)
	ON_BN_CLICKED(IDC_RESTART, OnRestart)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgShutDown message handlers

void CDlgShutDown::OnCancel() 
{
	//CDialog::OnCancel();
}

void CDlgShutDown::OnOK() 
{
	//CDialog::OnOK();
}

void CDlgShutDown::OnRestart() 
{
	//重新启动计算机
	AdjustTokenPrivilegesForNT();
	ExitWindowsEx(EWX_REBOOT, 0);
}

void CDlgShutDown::OnClose() 
{
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();
	
	//关闭计算机
	if (app->m_WinVerCd == 4)
		ExitWindowsEx(EWX_SHUTDOWN, 0); //Win9X中关闭计算机
	else
	{
		AdjustTokenPrivilegesForNT();
		ExitWindowsEx(EWX_POWEROFF, 0); //Win2000/XP中关闭计算机
	}
}

BOOL CDlgShutDown::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	COLORREF	m_shBtnColor = RGB(255,255,210)/*30*/;

	m_Restart.SetIcon(IDI_RESTART);
	m_Restart.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_Restart.SetTooltipText(IDS_RESTART);
	m_Restart.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);
	m_Restart.SetRounded(TRUE);

	m_ShutDown.SetIcon(IDI_SHUTDOWN);
	m_ShutDown.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_ShutDown.SetTooltipText(IDS_SHUTDOWN);
	m_ShutDown.SetColor(CButtonST::BTNST_COLOR_BK_IN, m_shBtnColor);
	m_ShutDown.SetRounded(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgShutDown::AdjustTokenPrivilegesForNT()
{
	HANDLE hToken; 
	TOKEN_PRIVILEGES tkp; 
	
	// Get a token for this process. 
	
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	
	// Get the LUID for the shutdown privilege. 
	
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid); 
	
	tkp.PrivilegeCount = 1;  // one privilege to set    
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	
	// Get the shutdown privilege for this process. 
	
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0); 
}