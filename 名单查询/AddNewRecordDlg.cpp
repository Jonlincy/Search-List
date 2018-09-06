// AddNewRecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "������ѯ.h"
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
      AfxMessageBox("����/��������Ϊ�գ������Ź������*�Ŵ��棬һ��*����һ���ַ���");
	  CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT1);
	  edit->SetFocus();
	  return;
	}
	if(moneya.IsEmpty())
	{
      AfxMessageBox("����Ϊ�գ�����������0����");
	  CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT2);
	  edit->SetFocus();
	  return;
	}
	if(sktime.IsEmpty())
	{
      AfxMessageBox("���ڲ���Ϊ�գ���ʽΪ2016.XX.XX�������ڲ�����X��ʾ��");
	  CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT3);
	  edit->SetFocus();
	  return;
	}

	if(MessageBox("�˲��������棬ȷ��Ҫ��Ӵ˼�¼��","ϵͳ��ʾ",MB_OKCANCEL|MB_ICONWARNING)!=IDOK)
		return;
	
		add.OpenTable("test");
		add.AddNew();
		//���������
		GetDlgItemText(IDC_EDIT1, str);
		save = add.SetItemContent("name",CADOOperation::ADO_TYPE_STRING, &str);	
		//����������
		GetDlgItemText(IDC_EDIT2, str);
		save = add.SetItemContent("qian",CADOOperation::ADO_TYPE_STRING, &str);	
		//���洲λ����
		GetDlgItemText(IDC_EDIT3, str);
		save = add.SetItemContent("skrq",CADOOperation::ADO_TYPE_STRING, &str);	
		GetDlgItemText(IDC_EDIT4, str);
		save = add.SetItemContent("beizhu",CADOOperation::ADO_TYPE_STRING, &str);	
		add.UpdateData();
		add.CloseTable();
		if(MessageBox("�տ��¼��ӳɹ�,�Ƿ������ӣ�","��Ӽ�¼",MB_OKCANCEL|MB_ICONQUESTION)!=IDCANCEL)
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


