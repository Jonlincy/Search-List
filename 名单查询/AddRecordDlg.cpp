// AddRecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ãûµ¥²éÑ¯.h"
#include "AddRecordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddRecordDlg dialog


CAddRecordDlg::CAddRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddRecordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddRecordDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAddRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddRecordDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddRecordDlg, CDialog)
	//{{AFX_MSG_MAP(CAddRecordDlg)
	ON_BN_CLICKED(IDOK, OnAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddRecordDlg message handlers

void CAddRecordDlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	
}
