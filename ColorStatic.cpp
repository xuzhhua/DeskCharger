// ColorStatic.cpp : implementation file
//

#include "stdafx.h"
#include "DeskCharger.h"
#include "ColorStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorStatic

CColorStatic::CColorStatic()
{
	m_brush.CreateSysColorBrush(HS_CROSS);
	m_ftclr = RGB(0, 0, 0);
}

CColorStatic::~CColorStatic()
{
	m_brush.DeleteObject();
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorStatic message handlers

HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetTextColor(m_ftclr);
	pDC->SetBkMode(TRANSPARENT);

	return (HBRUSH)GetStockObject(NULL_BRUSH);
}

void CColorStatic::PreSubclassWindow() 
{
    DWORD dwStyle = GetStyle();
    ::SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);
	
	CStatic::PreSubclassWindow();
}

void CColorStatic::SetFTCTLColor(COLORREF m_FONTclr /* = 0x00000000 */)
{
	m_ftclr = m_FONTclr;
}

BOOL CColorStatic::OnEraseBkgnd(CDC* pDC) 
{
    CRect rect;
    GetClientRect(rect);
    pDC->FillSolidRect(rect, ::GetSysColor(COLOR_3DFACE));
	
    //return TRUE;
	
	return CStatic::OnEraseBkgnd(pDC);
}
