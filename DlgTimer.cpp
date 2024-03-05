// DlgTimer.cpp : implementation file
//

#include "stdafx.h"
#include "DeskCharger.h"
#include "DlgTimer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTimer dialog


CDlgTimer::CDlgTimer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTimer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTimer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_IsSetting = false;
}


void CDlgTimer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTimer)
	DDX_Control(pDX, IDC_TIMELIST, m_TimeLst);
	DDX_Control(pDX, IDC_STARTTIME, m_StartTime);
	DDX_Control(pDX, IDC_SAVETIMEINFO, m_SaveTime);
	DDX_Control(pDX, IDC_READTIMEINFO, m_ReadTime);
	DDX_Control(pDX, IDC_EDITTIMEINFO, m_EditTime);
	DDX_Control(pDX, IDC_DELTIMEINFO, m_DelTime);
	DDX_Control(pDX, IDC_ADDTIMENEW, m_AddTimeNew);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTimer, CDialog)
	//{{AFX_MSG_MAP(CDlgTimer)
	ON_BN_CLICKED(IDC_READTIMEINFO, OnReadtimeinfo)
	ON_BN_CLICKED(IDC_SAVETIMEINFO, OnSavetimeinfo)
	ON_NOTIFY(NM_RCLICK, IDC_TIMELIST, OnRclickTimelist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTimer message handlers

void CDlgTimer::OnOK()
{
	//
}

void CDlgTimer::OnCancel()
{
	//
}
void CDlgTimer::OnReadtimeinfo() 
{
	// TODO: Add your control notification handler code here
	
}

BOOL CDlgTimer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CreatePopMenu();
	
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();
	m_CilIcon.Create(16,16,TRUE,2,2);
	m_CilIcon.Add(app->LoadIcon(IDI_ENABLE));
	m_CilIcon.Add(app->LoadIcon(IDI_DISABLE));
	m_TimeLst.SetImageList(&m_CilIcon, LVSIL_SMALL);
	
	//��ʼ���Ի����ϵİ�ť
	InitDlgBtn();
	InitLstBox();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTimer::InitDlgBtn()
{
	m_StartTime.SetIcon(IDI_TIMING);
	m_StartTime.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_StartTime.SetTooltipText(IDS_TIMING);
	
	m_AddTimeNew.SetIcon(IDI_NEWINFO);
	m_AddTimeNew.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_AddTimeNew.SetTooltipText(IDS_ADDINFO);

	m_DelTime.SetIcon(IDI_DELINFO);
	m_DelTime.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_DelTime.SetTooltipText(IDS_DELINFO);

	m_EditTime.SetIcon(IDI_EDITINFO);
	m_EditTime.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_EditTime.SetTooltipText(IDS_EDITINFO);

	m_ReadTime.SetIcon(IDI_READINFO);
	m_ReadTime.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_ReadTime.SetTooltipText(IDS_READINFO);

	m_SaveTime.SetIcon(IDI_SETTING);
	m_SaveTime.SetColor(CButtonST::BTNST_COLOR_FG_IN, 0x00000080);
	m_SaveTime.SetTooltipText(IDS_SETINFO);

	m_AddTimeNew.ShowWindow(SW_HIDE); 
	m_DelTime.ShowWindow(SW_HIDE); 
	m_EditTime.ShowWindow(SW_HIDE); 
	m_ReadTime.ShowWindow(SW_HIDE); 
}

void CDlgTimer::OnSavetimeinfo() 
{
	CString strTmp;
	CDeskChargerApp * app = (CDeskChargerApp *)AfxGetApp();

	if (m_IsSetting == false)
	{
		m_AddTimeNew.ShowWindow(SW_SHOW); 
		m_DelTime.ShowWindow(SW_SHOW); 
		m_EditTime.ShowWindow(SW_SHOW); 
		m_ReadTime.ShowWindow(SW_SHOW); 

		strTmp.LoadString(IDS_SAVE);
		m_SaveTime.SetWindowText(strTmp);
		m_IsSetting = true;
		m_SaveTime.SetIcon(IDI_SAVE);
		m_SaveTime.SetTooltipText(IDS_SAVEINFO);
		app->HadSavedHandle += 4;
	}
	else
	{
		m_AddTimeNew.ShowWindow(SW_HIDE); 
		m_DelTime.ShowWindow(SW_HIDE); 
		m_EditTime.ShowWindow(SW_HIDE); 
		m_ReadTime.ShowWindow(SW_HIDE); 

		strTmp.LoadString(IDS_SET);
		m_SaveTime.SetWindowText(strTmp);
		m_IsSetting = false;
		m_SaveTime.SetIcon(IDI_SETTING);
		m_SaveTime.SetTooltipText(IDS_SETINFO);
		app->HadSavedHandle -= 4;
	}
}

void CDlgTimer::CreatePopMenu()
{
	//�������ҳ�ʼ�������˵�
	CString StrMenu;
	
	m_LstPopMenu.CreatePopupMenu();
	//��ֹ/����ǰ��Ŀ
	StrMenu.LoadString(IDS_LSTDISABLECUROPTION);
	m_LstPopMenu.AppendMenu(MF_STRING, IDM_LSTABLECUR, StrMenu);
	m_LstPopMenu.AppendMenu(MF_SEPARATOR);
	
	//�½���Ŀ
	StrMenu.LoadString(IDS_LSTADDNEW); 
	m_LstPopMenu.AppendMenu(MF_STRING, IDM_LSTADDNEW, StrMenu);
	
	//�༭��Ŀ
	StrMenu.LoadString(IDS_LSTEDITCUR); 
	m_LstPopMenu.AppendMenu(MF_STRING, IDM_LSTEDIT, StrMenu);
	
	//ɾ����ǰ��Ŀ
	StrMenu.LoadString(IDS_LSTDELETECUROPTION);
	m_LstPopMenu.AppendMenu(MF_STRING, IDM_LSTDELCUR, StrMenu);
	
	m_LstPopMenu.SetDefaultItem(0, TRUE);
	m_LstPopMenu.SetMenuDrawMode(TRUE);
	m_LstPopMenu.SetBitmapBackground(RGB(0, 128, 128));
	m_LstPopMenu.SetIconSize(16, 15);
	m_LstPopMenu.LoadToolbar(IDR_LSTTOOLBAR);
}

void CDlgTimer::InitLstBox()
{
	//��ʼ���б��
	LV_COLUMN lvcol;
	
	lvcol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcol.fmt = LVCFMT_LEFT;//�������
	int i = 0;
	CString strCol;

	//�������**************************
	strCol.LoadString(IDS_LSTHOTKEYFUNC);
	LPTSTR p = strCol.GetBuffer(5);
	strCol.ReleaseBuffer(); 
	lvcol.pszText = p;
	lvcol.iSubItem = i;
	lvcol.cx = 150;
	
	m_TimeLst.InsertColumn(i++, &lvcol);
	
	strCol.LoadString(IDS_LSTTIME);
    p = strCol.GetBuffer(2);
	strCol.ReleaseBuffer(); 
	lvcol.pszText = p;
	lvcol.iSubItem = i;
	lvcol.cx = 60;
	
	m_TimeLst.InsertColumn(i++, &lvcol);
	
	strCol.LoadString(IDS_LSTDATE);
	p = strCol.GetBuffer(2);
	strCol.ReleaseBuffer(); 
	lvcol.pszText = p;
	lvcol.iSubItem = i;
	lvcol.cx = 75;
	
	m_TimeLst.InsertColumn(i++, &lvcol);
	
	strCol.LoadString(IDS_LSTOTHERTIMEINFO);
	p = strCol.GetBuffer(6);
	strCol.ReleaseBuffer(); 
	lvcol.pszText = p;
	lvcol.iSubItem = i;
	lvcol.cx = 170;

	m_TimeLst.InsertColumn(i++, &lvcol);

	//**********************************
	//ȡ��LISTCONTROL�����÷��Ϊ����ѡ��
	/*���ñ�ƽ������(LVS_EX_FLATSB)*/
	//������Ϣ��ʾ
	ListView_SetExtendedListViewStyle(m_TimeLst.m_hWnd, LVS_EX_LABELTIP | LVS_EX_FULLROWSELECT);
	
	LV_ITEM lvitem;
	//���������ȼ�����Ϣ
	lvitem.mask = LVIF_IMAGE | LVIF_TEXT;
	lvitem.iItem = 0;
	lvitem.iSubItem = 0;
	lvitem.iImage = 1;
	
	lvitem.pszText = "Ӧ���°�ؼ�����";
	
	//��������²�����Ŀ�����
	int iPos = m_TimeLst.InsertItem(&lvitem);//���ر��������������
		
	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = iPos;
	lvitem.iSubItem = 1;
	lvitem.pszText = "23:30:00";
	m_TimeLst.SetItem(&lvitem);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = iPos;
	lvitem.iSubItem = 2;
	lvitem.pszText = "2003/08/02";
	m_TimeLst.SetItem(&lvitem);
	
	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = iPos;
	lvitem.iSubItem = 3;
	lvitem.pszText = "�ظ�3��/���180��/��������";
	m_TimeLst.SetItem(&lvitem);
}

void CDlgTimer::OnRclickTimelist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = m_TimeLst.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		*pResult = 0;
		return;
	}
	else
	{
		while (pos)
		{
			int idx = m_TimeLst.GetNextSelectedItem(pos);
			
			POINT p;
			GetCursorPos(&p);
			SetForegroundWindow();
			m_LstPopMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p.x, p.y, this);
		}
	}
	
	*pResult = 0;
}
