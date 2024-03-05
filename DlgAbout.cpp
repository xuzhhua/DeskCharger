// DlgAbout.cpp : implementation file
//

#include "stdafx.h"
#include "DeskCharger.h"
#include "DlgAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAbout dialog


CDlgAbout::CDlgAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAbout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAbout)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAbout)
	DDX_Control(pDX, IDC_DECLARE, m_Declare);
	DDX_Control(pDX, IDC_VERSION, m_Version);
	DDX_Control(pDX, IDC_TITLE, m_Title);
	DDX_Control(pDX, IDC_MAIL, m_Mailme);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAbout, CDialog)
	//{{AFX_MSG_MAP(CDlgAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAbout message handlers
void CDlgAbout::OnOK()
{
	//
}

void CDlgAbout::OnCancel()
{
	//
}

BOOL CDlgAbout::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString strTmp;

	strTmp.LoadString(IDS_MAILTOME);

	HCURSOR hHandCursor = AfxGetApp()->LoadCursor(IDC_HANDURL);
	m_Mailme.SetCursor(hHandCursor);
	m_Mailme.SetURL("mailto:silerspray@ynmail.com", strTmp);
	
	m_Title.SetFTCTLColor(RGB(71, 114, 234));
	m_Version.SetFTCTLColor(RGB(71, 114, 234));
	m_Declare.SetFTCTLColor(RGB(119, 11, 11));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}