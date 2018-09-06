// FunDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Ãûµ¥²éÑ¯.h"
#include "FunDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFunDlg dialog


CFunDlg::CFunDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFunDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFunDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFunDlg)
	DDX_Control(pDX, IDC_EXPLORER1, m_web);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFunDlg, CDialog)
	//{{AFX_MSG_MAP(CFunDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFunDlg message handlers

BOOL CFunDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_web.Navigate("http://map.baidu.com",NULL,NULL,NULL,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


