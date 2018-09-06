#if !defined(AFX_MODIFYDLG_H__B5BD8830_E3D4_41B3_9066_A8142FD5B19C__INCLUDED_)
#define AFX_MODIFYDLG_H__B5BD8830_E3D4_41B3_9066_A8142FD5B19C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModifyDlg dialog

class CModifyDlg : public CDialog
{
// Construction
public:
	CModifyDlg(CWnd* pParent = NULL);   // standard constructor
    CString id;
// Dialog Data
	//{{AFX_DATA(CModifyDlg)
	enum { IDD = IDD_Modify };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYDLG_H__B5BD8830_E3D4_41B3_9066_A8142FD5B19C__INCLUDED_)
