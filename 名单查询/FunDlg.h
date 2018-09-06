//{{AFX_INCLUDES()
#include "webbrowser2.h"
//}}AFX_INCLUDES
#if !defined(AFX_FUNDLG_H__D906B6E0_FB26_4AF7_888F_06A0D7D20969__INCLUDED_)
#define AFX_FUNDLG_H__D906B6E0_FB26_4AF7_888F_06A0D7D20969__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FunDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFunDlg dialog

class CFunDlg : public CDialog
{
// Construction
public:
	CFunDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFunDlg)
	enum { IDD = IDD_FUN };
	CWebBrowser2	m_web;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFunDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFunDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FUNDLG_H__D906B6E0_FB26_4AF7_888F_06A0D7D20969__INCLUDED_)
