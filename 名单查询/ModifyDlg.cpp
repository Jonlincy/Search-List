// ModifyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "������ѯ.h"
#include "ModifyDlg.h"
#include "ADOOperation.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyDlg dialog


CModifyDlg::CModifyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModifyDlg, CDialog)
	//{{AFX_MSG_MAP(CModifyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyDlg message handlers

void CModifyDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(MessageBox("ȷ��Ҫ�޸Ĵ���Ϣ��","ϵͳ��ʾ",MB_OKCANCEL|MB_ICONQUESTION)!=IDOK)
		return;
	CADOOperation sushe;
	CString str,sql;
	sql.Format("select * from test where name='%s'",id);
	sushe.OpenRecordset(sql);
	//����ѧ������
	GetDlgItemText(IDC_EDIT4, str);				
	sushe.SetItemContent("beizhu",CADOOperation::ADO_TYPE_STRING, &str);
	sushe.UpdateData();
	sushe.CloseRecorset();
	if(MessageBox("��Ϣ�޸ĳɹ���","ϵͳ��ʾ",MB_OK|MB_ICONINFORMATION)!=IDOK)
		return;
		CDialog::OnOK();
}

BOOL CModifyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CADOOperation xiugai; CString str;
	xiugai.OpenTable("test");
	if(xiugai.IsLastRow())
		return TRUE;
	xiugai.MoveFirst();
	do
	{xiugai.GetItemContent("name",
		CADOOperation::ADO_TYPE_STRING, &str);
	xiugai.MoveNext();
	}while(!xiugai.IsLastRow());
	xiugai.CloseTable();
	CADOOperation dbo;
	CString sql;
	sql.Format("select * from test where name='%s'",id);
	dbo.OpenRecordset(sql);
	//��ȡ����
	dbo.GetItemContent("name",CADOOperation::ADO_TYPE_STRING, &str);
	SetDlgItemText(IDC_EDIT1, str);
	//��ȡ���
	dbo.GetItemContent("qian",CADOOperation::ADO_TYPE_STRING, &str);
	SetDlgItemText(IDC_EDIT2, str);
	//��ȡ����
	dbo.GetItemContent("skrq",CADOOperation::ADO_TYPE_STRING, &str);
	SetDlgItemText(IDC_EDIT3, str);
	//��ȡ��ע
	dbo.GetItemContent("beizhu",CADOOperation::ADO_TYPE_STRING, &str);
	SetDlgItemText(IDC_EDIT4, str);
	dbo.CloseRecorset();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
