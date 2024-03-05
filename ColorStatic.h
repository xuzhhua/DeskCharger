#if !defined(AFX_COLORSTATIC_H__081576B8_D1A0_4F48_A8A5_7DAE058A3C3D__INCLUDED_)
#define AFX_COLORSTATIC_H__081576B8_D1A0_4F48_A8A5_7DAE058A3C3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorStatic window

class CColorStatic : public CStatic
{
// Construction
public:
	CColorStatic();
	
// Attributes
public:
	
private:
	COLORREF m_ftclr;
	CBrush   m_brush; //background brush

// Operations
public:
    virtual void SetFTCTLColor(COLORREF m_FONTclr = 0x00000000);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorStatic)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSTATIC_H__081576B8_D1A0_4F48_A8A5_7DAE058A3C3D__INCLUDED_)
