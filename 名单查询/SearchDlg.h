#if !defined(AFX_SEARCHDLG_H__CF717B84_31EA_4E43_AFB8_874A26654815__INCLUDED_)
#define AFX_SEARCHDLG_H__CF717B84_31EA_4E43_AFB8_874A26654815__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SearchDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog

class CSearchDlg : public CDialog
{
// Construction
public:
	CSearchDlg(CWnd* pParent = NULL);   // standard constructor
    void ShowAllRecords(CString sql);
	void ListExport();
	void ListShow();
	void ListStyle();
    CString sql;
	CToolTipCtrl m_Mytip;
	int m_CurSel;
	int pageNo; //页数编号
	int pageSize; // 每页显示条数
	int intStart; // 开始记录
	int intEnd; // 结束记录
	int max_page; // 记录最大页数
// Dialog Data
	//{{AFX_DATA(CSearchDlg)
	enum { IDD = IDD_Sousuo };
	CComboBox	m_chose;
	CListCtrl	m_ListCtrl;
	CComboBox	m_info;
	CString	m_ShowPage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSearchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	virtual void OnOK();
	afx_msg void OnButton3();
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCopy();
	afx_msg void OnBtnFirst();
	afx_msg void OnBtnPageup();
	afx_msg void OnBtnPagedown();
	afx_msg void OnBtnLast();
	afx_msg void OnAddrecord();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnJump();
	afx_msg void OnButton4();
	afx_msg void OnReflesh();
	afx_msg void OnNewPage();
	afx_msg void OnDelete();
	afx_msg void OnButton6();
	afx_msg void OnOpen();
	afx_msg void OnTxt();
	afx_msg void OnButton7();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHDLG_H__CF717B84_31EA_4E43_AFB8_874A26654815__INCLUDED_)
