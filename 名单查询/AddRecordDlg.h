#if !defined(AFX_ADDRECORDDLG_H__55A43078_7452_424F_98D1_80E7379E9A71__INCLUDED_)
#define AFX_ADDRECORDDLG_H__55A43078_7452_424F_98D1_80E7379E9A71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddRecordDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddRecordDlg dialog

class CAddRecordDlg : public CDialog
{
// Construction
public:
	CAddRecordDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddRecordDlg)
	enum { IDD = IDD_AddRec };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddRecordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddRecordDlg)
	afx_msg void OnAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDRECORDDLG_H__55A43078_7452_424F_98D1_80E7379E9A71__INCLUDED_)
