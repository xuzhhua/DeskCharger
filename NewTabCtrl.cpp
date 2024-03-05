// NewTabCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "DeskCharger.h"
#include "NewTabCtrl.h"

#include "DlgCDROM.h"
#include "DlgHotkey.h"
#include "DlgTimer.h"
#include "DlgAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewTabCtrl

CNewTabCtrl::CNewTabCtrl()
{
	::ZeroMemory(&m_tabPages, sizeof(m_tabPages));

	m_tabPages[0]=new CDlgCDROM;
	m_tabPages[1]=new CDlgHotkey;
	//m_tabPages[2]=new CDlgTimer;
	m_tabPages[2]=new CDlgAbout;

	m_nNumberOfPages=3/*4*/;
}

CNewTabCtrl::~CNewTabCtrl()
{
	for(int nCount=0; nCount < m_nNumberOfPages; nCount++){
		delete m_tabPages[nCount];
	}
}

void CNewTabCtrl::Init()
{
	m_tabCurrent=0;

	m_tabPages[0]->Create(IDD_CDROM, this);
	m_tabPages[1]->Create(IDD_HOTKEY, this);
	//m_tabPages[2]->Create(IDD_TIMER, this);
	m_tabPages[2]->Create(IDD_ABOUT, this);

	m_tabPages[0]->ShowWindow(SW_SHOW);
	m_tabPages[1]->ShowWindow(SW_HIDE);
	m_tabPages[2]->ShowWindow(SW_HIDE);
	//m_tabPages[3]->ShowWindow(SW_HIDE);

	SetRectangle();
}

void CNewTabCtrl::SetRectangle()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX=itemRect.left;
	nY=itemRect.bottom+1;
	nXc=tabRect.right-itemRect.left-1;
	nYc=tabRect.bottom-nY-1;

	m_tabPages[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	for(int nCount=1; nCount < m_nNumberOfPages; nCount++){
		m_tabPages[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
	}
}

BEGIN_MESSAGE_MAP(CNewTabCtrl, CTabCtrl)
	//{{AFX_MSG_MAP(CNewTabCtrl)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewTabCtrl message handlers

void CNewTabCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CTabCtrl::OnLButtonDown(nFlags, point);

	if(m_tabCurrent != GetCurFocus()){
		m_tabPages[m_tabCurrent]->ShowWindow(SW_HIDE);
		m_tabCurrent=GetCurFocus();
		m_tabPages[m_tabCurrent]->ShowWindow(SW_SHOW);
		m_tabPages[m_tabCurrent]->SetFocus();
	}	
	//CTabCtrl::OnLButtonDown(nFlags, point);
}
