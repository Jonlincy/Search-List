#if !defined(AFX_ADDNEWRECORDDLG_H__4F5569EC_F43B_4051_9460_6DDA87CE6AC1__INCLUDED_)
#define AFX_ADDNEWRECORDDLG_H__4F5569EC_F43B_4051_9460_6DDA87CE6AC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddNewRecordDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddNewRecordDlg dialog

class CAddNewRecordDlg : public CDialog
{
// Construction
public:
	CAddNewRecordDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddNewRecordDlg)
	enum { IDD = IDD_ADDRECDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddNewRecordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddNewRecordDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDNEWRECORDDLG_H__4F5569EC_F43B_4051_9460_6DDA87CE6AC1__INCLUDED_)
