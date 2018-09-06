// AddNewRecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "名单查询.h"
#include "AddNewRecordDlg.h"
#include "ADOOperation.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddNewRecordDlg dialog


CAddNewRecordDlg::CAddNewRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddNewRecordDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddNewRecordDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAddNewRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddNewRecordDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddNewRecordDlg, CDialog)
	//{{AFX_MSG_MAP(CAddNewRecordDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddNewRecordDlg message handlers

void CAddNewRecordDlg::OnOK() 
{
	// TODO: Add extra validation here
	CADOOperation add;
	DWORD count=0;
	BOOL save;
	CString mz,moneya,sktime,str,sql;
	GetDlgItemText(IDC_EDIT1, mz);
	GetDlgItemText(IDC_EDIT2, moneya);
	GetDlgItemText(IDC_EDIT3, sktime);
	//GetDlgItemText(IDC_EDIT4, ssh);
	
	if(mz.IsEmpty())
	{
      AfxMessageBox("姓名/网名不能为空（若符号怪异可用*号代替，一个*代表一个字符）");
	  CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT1);
	  edit->SetFocus();
	  return;
	}
	if(moneya.IsEmpty())
	{
      AfxMessageBox("金额不能为空，若数额不详可用0代替");
	  CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT2);
	  edit->SetFocus();
	  return;
	}
	if(sktime.IsEmpty())
	{
      AfxMessageBox("日期不能为空，格式为2016.XX.XX（若日期不详用X表示）");
	  CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT3);
	  edit->SetFocus();
	  return;
	}

	if(MessageBox("此操作不可逆，确定要添加此记录吗？","系统提示",MB_OKCANCEL|MB_ICONWARNING)!=IDOK)
		return;
	
		add.OpenTable("test");
		add.AddNew();
		//保存宿舍号
		GetDlgItemText(IDC_EDIT1, str);
		save = add.SetItemContent("name",CADOOperation::ADO_TYPE_STRING, &str);	
		//保存宿舍名
		GetDlgItemText(IDC_EDIT2, str);
		save = add.SetItemContent("qian",CADOOperation::ADO_TYPE_STRING, &str);	
		//保存床位个数
		GetDlgItemText(IDC_EDIT3, str);
		save = add.SetItemContent("skrq",CADOOperation::ADO_TYPE_STRING, &str);	
		GetDlgItemText(IDC_EDIT4, str);
		save = add.SetItemContent("beizhu",CADOOperation::ADO_TYPE_STRING, &str);	
		add.UpdateData();
		add.CloseTable();
		if(MessageBox("收款记录添加成功,是否继续添加？","添加记录",MB_OKCANCEL|MB_ICONQUESTION)!=IDCANCEL)
		{		
			SetDlgItemText(IDC_EDIT1, "");
			SetDlgItemText(IDC_EDIT2, "");
			SetDlgItemText(IDC_EDIT3, "");
			SetDlgItemText(IDC_EDIT4, "");
			UpdateData();
			Invalidate();
		}
		
		else{ 
			CDialog::OnOK();  
		} 
	}


