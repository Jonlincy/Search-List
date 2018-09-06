// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "������ѯ.h"
#include "SearchDlg.h"
#include "ADOOperation.h"
#include "ModifyDlg.h"
#include "SearchSet.h"
#include "FunDlg.h"
#include <afxadv.h>
#include "afxole.h"
#include "AddNewRecordDlg.h"
#ifdef _DEBUG
#include <locale.h>
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "SkinH.h"//����Ƥ����
#pragma comment(lib,"SkinH.lib")
/////////////////////////////////////////////////////////////////////////////
// CSearchDlg dialog

CSearchSet testSet;
CSearchDlg::CSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchDlg)
	m_ShowPage = _T("");
	//}}AFX_DATA_INIT
	 pageSize = 20;
	pageNo = 0;

}


void CSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchDlg)
	DDX_Control(pDX, IDC_COMBO2, m_chose);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_info);
	DDX_Text(pDX, IDC_STATIC_SHOWPAGE, m_ShowPage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSearchDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_COMMAND(ID_COPY, OnCopy)
	ON_BN_CLICKED(IDC_BTN_FIRST, OnBtnFirst)
	ON_BN_CLICKED(IDC_BTN_PAGEUP, OnBtnPageup)
	ON_BN_CLICKED(IDC_BTN_PAGEDOWN, OnBtnPagedown)
	ON_BN_CLICKED(IDC_BTN_LAST, OnBtnLast)
	ON_BN_CLICKED(IDC_ADDRECORD, OnAddrecord)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, OnJump)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_COMMAND(ID_Reflesh, OnReflesh)
	ON_BN_CLICKED(IDC_NewPage, OnNewPage)
	ON_COMMAND(ID_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_COMMAND(ID_Open, OnOpen)
	ON_COMMAND(ID_TXT, OnTxt)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchDlg message handlers

BOOL CSearchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SkinH_Attach();
	// TODO: Add extra initialization here
	CADOOperation dbo;
	CString sql;
	pageNo = 1;
	ListStyle();
	ListShow();
	m_info.AddString("����/����");
	m_info.AddString("���(Ԫ)");
	m_info.AddString("�տ�����");
	m_info.AddString("��ע");
	m_info.SetCurSel(0);
	m_chose.AddString(">");
	m_chose.AddString("<");
	m_chose.AddString("=");
	m_chose.SetCurSel(0);
	m_Mytip.Create(this); 
    m_Mytip.AddTool( GetDlgItem(IDC_EDIT1), "������ѯ�������ݽ��Զ���ʾ���б���" );
	m_Mytip.AddTool( GetDlgItem(IDC_BUTTON1), "���ս����ڡ�С�ڻ����ĳһ����ѯ" );
	m_Mytip.AddTool( GetDlgItem(IDC_BUTTON2), "���ս��ķ�Χ��ѯ" );
	m_Mytip.AddTool( GetDlgItem(IDC_BUTTON3), "�������ݱ��浽EXCEL����" );
	m_Mytip.AddTool( GetDlgItem(IDCANCEL), "�˳���ѯ����" );
	m_Mytip.SetDelayTime(100); //�����ӳ�
	m_Mytip.SetTipTextColor( RGB(100,150,200) ); //������ʾ�ı�����ɫ
	m_Mytip.SetTipBkColor( RGB(255,255,255)); //������ʾ��ı�����ɫ
	m_Mytip.Activate(TRUE);
	SetDlgItemText(IDC_EDIT5, "0");
	CString strTime;
       CTime tm;
        tm=CTime::GetCurrentTime();         //��ȡ��ǰϵͳʱ��
       strTime=tm.Format("%y��%m��%d�� %X");   //��ʽ��ϵͳʱ�䡣��ʹϵͳʱ �䰴��Format�����õĸ�ʽ��ʾ
       SetDlgItemText(IDC_Curtime,strTime);        //��ʼ���༭����ʾ
       SetTimer(1,1000,NULL);         //������ʱ��
CString str;
int al=0;
	  // AfxMessageBox(str);

	
   /*
	int nColumnCount =m_ListCtrl.GetColumn();
		
	str.Format(TEXT("%d"),nColumnCount);
	SetDlgItemText(IDC_EDIT8, str);*/
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	
}
void CSearchDlg::ShowAllRecords(CString sql)
{ 
	
	m_ListCtrl.DeleteAllItems();
	CADOOperation list;
	CString str[] = {"xm", "mimi", "sj","bz"};
	list.OpenRecordset(sql);
	int i=0,j=0;
	CString *str1=new CString[4];
	list.MoveFirst();
	while(!list.IsLastRow())
	{list.GetItemContent("xm",CADOOperation::ADO_TYPE_STRING,&str1[0]);
	m_ListCtrl.InsertItem(j,str1[0]);
    for(i=1;i<4;i++)
	{
		list.GetItemContent(str[i],CADOOperation::ADO_TYPE_STRING,&str1[i]);
		m_ListCtrl.SetItemText(j,i,str1[i]);
	}
	j++;
	list.MoveNext();
	}
	list.CloseRecorset();
	int nColumnCount =m_ListCtrl.GetItemCount();
	CString al;	
	al.Format(TEXT("%d"),nColumnCount);
	SetDlgItemText(IDC_EDIT6, al);
}
void CSearchDlg::ListShow() // ��������ʾ��List Control���ʾҳ������ʾ��Ϣ��ʾ
{
	m_ListCtrl.DeleteAllItems();
	int i_num  = 0;
	char chrTemp='%';
	intStart = pageSize * (pageNo-1);
	intEnd = pageSize * pageNo;
	try
	{
		if(testSet.IsOpen())
		{
			testSet.Close();
		}

		testSet.m_strFilter.Format("name like '%c%s%c' ", chrTemp , "", chrTemp);
		testSet.Open(CRecordset::snapshot,NULL,CRecordset::none);
		
		while(!testSet.IsEOF()) // ���ƥ���ϲ�ѯ�����û���¼,ֱ����¼Ϊ��
		{			
			if (i_num >= intStart && i_num < intEnd) // ����ҳ����ʾ��Ӧ����
			{
				i_num = i_num % pageSize;
				CString strTemp;
				strTemp.Format("%s",testSet.m_name);
				m_ListCtrl.InsertItem(i_num,strTemp);
				strTemp.Format("%.2f",testSet.m_qian);
				m_ListCtrl.SetItemText(i_num, 1,strTemp);				
				strTemp.Format("%s",testSet.m_skrq);
				m_ListCtrl.SetItemText(i_num, 2, strTemp);
				strTemp.Format("%s",testSet.m_beizhu);
				m_ListCtrl.SetItemText(i_num, 3, strTemp);
				if (pageNo >= 2) // ��ҳ��Ϊ1ʱ��i��ֵ�����䱾�����ҳ������1ʱ��i��ֵ�ָ���ȡ����ǰ
				{
					i_num += (pageNo -1) * pageSize;	
				}
				
			}

			i_num++;	
			testSet.MoveNext(); // ��¼�α��Ƶ���һ����¼
		}
		
		if (i_num % pageSize == 0)
		{
			max_page = i_num / pageSize;
		}
		else
		{
			max_page = i_num / pageSize + 1;
		}		
		
		if(testSet.IsOpen()) // �رռ�¼��
		{
			testSet.Close();
		}
	}
	
	catch(CDBException*e)
	{
		e->ReportError ();
		return;
	}

	CString strShowPage, strpageNo, strMaxPage;
	strpageNo.Format("�� %d ҳ  ", pageNo);
	strMaxPage.Format("�� %d ҳ", max_page);
	strShowPage.Format(strpageNo + strMaxPage);
	GetDlgItem(IDC_STATIC_SHOWPAGE)->SetWindowText(strShowPage);
    int nColumnCount =m_ListCtrl.GetItemCount();
	CString str;	
	str.Format(TEXT("%d"),nColumnCount);
	SetDlgItemText(IDC_EDIT6, str);
}

BOOL CSearchDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
		if(pMsg->message==WM_MOUSEMOVE)
		m_Mytip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}



void CSearchDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	int index = ((CComboBox*)GetDlgItem(IDC_COMBO2))->GetCurSel();	
	int test=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();	
	int nColumnCount =m_ListCtrl.GetItemCount();
	CString buf,xl;	
	GetDlgItemText(IDC_EDIT2, buf);
	GetDlgItemText(IDC_EDIT1, xl);
    CADOOperation dbo;	
	switch(index)
	{ 
	case 0://����ע��ѯ�տ���Ϣ
        if(xl=="")
		{sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian<'%s'",buf);
		}
		else if(test==0) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian<'%s' and beizhu like '%s%%'",buf,xl);}
		else if(test==1) {
             SetDlgItemText(IDC_EDIT1, "");
			sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian<'%s'",buf);}
		else if(test==2){sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian<'%s' and skrq like '%s%%'",buf,xl);}
		else if(test==3) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian<'%s' and name like '%s%%'",buf,xl);}
		else{AfxMessageBox("û�в鵽���������ļ�¼!");}
	    dbo.OpenRecordset(sql);
	if(buf.IsEmpty())
	{
		AfxMessageBox("���ݲ���Ϊ�գ�");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT2);
		edit->SetFocus();
		return;		
	}
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("�鲻���ü�¼,��˶Ժ�������!");
		SetDlgItemText(IDC_EDIT2, "");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT2);
	    edit->SetFocus();
	    dbo.CloseRecorset();
	    return;
	}
    dbo.CloseRecorset(); 	
    ShowAllRecords(sql);			
	break;
	case 1://������ѯ�տ���Ϣ
		  if(xl=="")
		{sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian='%s'",buf);
		}
		else if(test==0) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian='%s' and beizhu like '%s%%'",buf,xl);}
		else if(test==2){sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian='%s' and skrq like '%s%%'",buf,xl);}
		else if(test==3) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian='%s' and name like '%s%%'",buf,xl);}
		else{AfxMessageBox("û�в鵽���������ļ�¼!");}
	dbo.OpenRecordset(sql);
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("�鲻���ü�¼,��˶Ժ�������!");
		SetDlgItemText(IDC_EDIT2, "");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT2);
	    edit->SetFocus();
	    dbo.CloseRecorset();
	    return;
	}
    dbo.CloseRecorset(); 
    ShowAllRecords(sql);		
	break;
	case 2://���տ����ڲ�ѯ�տ���Ϣ
       if(xl=="")
		{sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian>'%s'",buf);
		}
		else if(test==0) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian>'%s' and beizhu like '%s%%'",buf,xl);}
		else if(test==2){sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian>'%s' and skrq like '%s%%'",buf,xl);}
		else if(test==3) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian>'%s' and name like '%s%%'",buf,xl);}
		else{AfxMessageBox("û�в鵽���������ļ�¼!");}
	dbo.OpenRecordset(sql);
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("�鲻���ü�¼,��˶Ժ�������!");
		SetDlgItemText(IDC_EDIT1, "");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT1);
	    edit->SetFocus();
	    dbo.CloseRecorset();
	    return;
	}
    dbo.CloseRecorset();
    ShowAllRecords(sql);
	break;
	default:return ;
	}	
}

void CSearchDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	CString buf,sj,xl;
	int tes=((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	GetDlgItemText(IDC_EDIT1, xl);
	GetDlgItemText(IDC_EDIT3, buf);
	GetDlgItemText(IDC_EDIT4, sj);
	CADOOperation dbo,list;	
	if(xl=="")
		{sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test  where qian between '%s' and '%s' ",buf,sj);
		}
		else if(tes==0) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test  where qian between '%s' and '%s' and beizhu like '%s%%'",buf,sj,xl);}
		else if(tes==2){sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test  where qian between '%s' and '%s' and skrq like '%s%%'",buf,sj,xl);}
		else if(tes==3){sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test  where qian between '%s' and '%s' and name like '%s%%'",buf,sj,xl);}
		else{AfxMessageBox("û�в鵽���������ļ�¼!");}
	dbo.OpenRecordset(sql);
	if(buf.IsEmpty())
	{
		AfxMessageBox("���ݲ���Ϊ�գ�");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT3);
		edit->SetFocus();
		return;		
	}
	if(sj.IsEmpty())
	{
		AfxMessageBox("���ݲ���Ϊ�գ�");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT4);
		edit->SetFocus();
		return;		
	}
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("�鲻���ü�¼,��˶Ժ�������!");
		MessageBox("�����������ݣ����Ժ�....","ϵͳ��ʾ",MB_OKCANCEL|MB_ICONQUESTION);
		SetDlgItemText(IDC_EDIT3, "");
		SetDlgItemText(IDC_EDIT4, "");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT3);
	    edit->SetFocus();
	    dbo.CloseRecorset();
	    return;
	}
    dbo.CloseRecorset(); 
	ShowAllRecords(sql);
}

void CSearchDlg::OnOK() 
{
	// TODO: Add extra validation here

}

void CSearchDlg::OnButton3() 
{
	if ( m_ListCtrl.GetItemCount()<= 0 )
 {
  AfxMessageBox("�б���û�м�¼��Ҫ���棡");
  return;
 }
 //�����Ϊ�Ի��� ����Ҫ���� #include <Afxdlgs.h>
 CFileDialog dlg( FALSE, 
      "xls", 
      "�տ�����", 
      OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
      "Excel �ļ�(*.xls)|*.xls||");
 dlg.m_ofn.lpstrTitle = "���ļ����Ϊ...";
 
 if (dlg.DoModal() != IDOK)
  return;
 CString strFilePath;
 //����ļ�·����
 strFilePath = dlg.GetPathName();
 //�ж��ļ��Ƿ��Ѿ����ڣ�������ɾ���ؽ�
 DWORD dwRe = GetFileAttributes(strFilePath);
 if ( dwRe != (DWORD)-1 )
 {
  DeleteFile(strFilePath);
 }
 CDatabase database;//���ݿ����Ҫ����ͷ�ļ� #include <afxdb.h>
 CString sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)"; // Excel����
 CString sSql,strInsert;
 TRY
 {
  // �������д�ȡ���ַ���
  sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, strFilePath, strFilePath);
  
  // �������ݿ� (��Excel����ļ�)
  if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
  {
   //����б��������
   int iColumnNum,iRowCount;
   LVCOLUMN lvCol;
   CString strColName; //���ڱ����б�������
   int i,j; //�С���ѭ������
  
   iColumnNum = m_ListCtrl.GetHeaderCtrl()->GetItemCount();
   iRowCount = m_ListCtrl.GetItemCount();
   sSql = " CREATE TABLE DSO_DX ( ";
   strInsert = " INSERT INTO DSO_DX ( " ;
   //����б�������
   lvCol.mask = LVCF_TEXT; //�������ã�˵��LVCOLUMN������pszText������Ч
   lvCol.cchTextMax = 32; //���裬pszText������ָ����ַ����Ĵ�С
   lvCol.pszText = strColName.GetBuffer(32); //���裬pszText ��ָ����ַ�����ʵ�ʴ洢λ�á�
   //���������������ú����ͨ�� GetColumn()��������б��������
   for( i=0 ; i< iColumnNum ; i++ )
   {
    if ( !(m_ListCtrl.GetColumn(i,&lvCol)) )
     return;
    if ( i<iColumnNum-1 )
    {
     sSql = sSql + lvCol.pszText + " TEXT , ";
     strInsert = strInsert + lvCol.pszText + " , ";
    }
    else
    {
     sSql = sSql + lvCol.pszText + " TEXT ) ";
     strInsert = strInsert + lvCol.pszText + " )  VALUES ( ";
    }
   }
   //����Excel����ļ�
   database.ExecuteSQL(sSql);
   //ѭ����ȡ��¼�����뵽EXCEL��
   sSql = strInsert;
   char chTemp[33];
   for ( j=0 ; j<iRowCount ; j++ )
   {
    memset(chTemp,0,33);
    for ( i=0 ; i<iColumnNum ; i++ )
    {
     m_ListCtrl.GetItemText(j,i,chTemp,33);
     if ( i < (iColumnNum-1) )
     {
      sSql = sSql + "'" + chTemp + "' , ";
     }
     else
     {
      sSql = sSql + "'" + chTemp + "' ) ";
     }
    }
    //����¼���뵽�����
    database.ExecuteSQL(sSql);
    sSql = strInsert; 
   }
  }     
  // �ر�Excel����ļ�
  database.Close();
  AfxMessageBox("�����տ���Ϣ��ɹ���");
 }
 CATCH_ALL(e)
 {
  //�������ͺܶ࣬������Ҫ���б���
  AfxMessageBox("Excel��񱣴�ʧ�ܡ�");
 }
 END_CATCH_ALL;
	
}

void CSearchDlg::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
    int ls=pNMListView->iSubItem;
	CString sql;
	if(ls==0)
	sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test order by name");	
	else if(ls==1)
	sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test order by qian");	
    else if(ls==2)
	sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test order by skrq");	
	else if(ls==3)
	sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test order by beizhu");	
    ShowAllRecords(sql);
	*pResult = 0;
}

void CSearchDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	m_CurSel = ((LPNMLISTVIEW)pNMHDR)->iItem;
	int i=m_CurSel;
	if(i==-1)
	{	AfxMessageBox("��ѡ��һ����¼���в���!");
	return;
	}
	else
	{
    CModifyDlg dlg;
	dlg.id=m_ListCtrl.GetItemText(m_CurSel,0);	
    dlg.DoModal();
	//ShowAllRecords(sql);
ListShow();
	}
	*pResult = 0;
}

void CSearchDlg::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POINT pt;
	m_CurSel = ((LPNMLISTVIEW)pNMHDR)->iItem;
	if(m_CurSel < 0)
		return;
	::GetCursorPos(&pt);
    CMenu menu;
	CMenu *subMenu;
	menu.LoadMenu(IDR_MENU1);
	subMenu = menu.GetSubMenu(0);
	subMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x,  pt.y, this);
	*pResult = 0;
}

void CSearchDlg::OnCopy() 
{
	// TODO: Add your command handler code here
	/*COleDataSource* pSource=new COleDataSource();
CSharedFile sf(GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);
char* strText;
strText=new char[40];//�洢���ļ���ȡ������
for(int i=0;i<m_ListCtrl.GetItemCount();i++)
{
m_ListCtrl.GetItemText(i,(int)strText);
sf.Seek(40*i,CFile::begin);//��λ�ļ�ָ��
sf.Write(strText,40);//д�ļ�����
}
HGLOBAL hMem=sf.Detach();
if(!hMem)
return;
CoInitialize(NULL);
pSource->CacheGlobalData(CF_TEXT,hMem);
pSource->SetClipboard();//��ӵ����а���
*/
/*	CString str;  
HGLOBAL hClip;  
//����һ��HGLOBAL�����������ָ�������ڴ��
if (OpenClipboard())
{
EmptyClipboard(); //���������������
hClip=GlobalAlloc(GMEM_MOVEABLE,str.GetLength()+1);  
//�ڶ��Ϸ�����ƶ����ڴ�飬���򷵻�һ���ڴ���
char * buff; //����ָ���ַ��͵�ָ�����
buff=(char*)GlobalLock(hClip);
//�Է�����ڴ����м��������ڴ����ת����һ��ָ��,������Ӧ�����ü�������1
strcpy(buff,str);
//���û���������ݸ��Ƶ�ָ������У�ʵ���Ͼ��Ǹ��Ƶ�������ڴ����
GlobalUnlock(hClip);
//����д����ϣ����н����������������ü��������ּ�1
SetClipboardData(CF_TEXT,hClip);
//����������ݵ��ڴ�������������Դ������
CloseClipboard();
//�رռ����壬�ͷż�������Դ��ռ��Ȩ
MessageBox("�ѽ����ݴ��������");
}  

//�Ӽ�������ȡ���ı���  

//CString str;
//�ַ��ͱ��������ɼ����帴������������
//HANDLE hClip;
//����HANDLE����ͱ�������ָ��GetClipboardData�������صľ��
if (OpenClipboard())
{
hClip=GetClipboardData(CF_TEXT);
//�Ӽ�������ȡ��һ���ڴ�ľ��
char* buff;
//�����ַ���ָ��������������ڴ���е�����
buff=(char*)GlobalLock(hClip);
//���ڴ����м��������ڴ���ֵת��Ϊһ��ָ��,�����ڴ������ü�������һ���ڴ��е�����Ҳ���ص�ָ���ͱ�����
str=buff;
//�����ݱ��浽�ַ��ͱ�����
GlobalUnlock(hClip);
//���ڴ������ü�������һ
CloseClipboard();
//�رռ����壬�ͷż�������Դ��ռ��Ȩ

}
  */
}

void CSearchDlg::OnBtnFirst() 
{
	// TODO: Add your control notification handler code here
		if (pageNo == 1)
	{
		AfxMessageBox(_T("���ǵ�һҳ"));
	}
	else
	{
		pageNo = 1;
		m_ListCtrl.DeleteAllItems();
		ListShow();
		int nColumnCount =m_ListCtrl.GetItemCount();
		CString str;	
		str.Format(TEXT("%d"),nColumnCount);
		SetDlgItemText(IDC_EDIT6, str);
	}
}

void CSearchDlg::OnBtnPageup() 
{
	// TODO: Add your control notification handler code here
	if(pageNo==1)
    {
        AfxMessageBox(_T("���ǵ�һҳ"));
    }
    if(pageNo>1)
    {
        pageNo--;
        m_ListCtrl.DeleteAllItems();
		ListShow();
		int nColumnCount =m_ListCtrl.GetItemCount();
		CString str;	
		str.Format(TEXT("%d"),nColumnCount);
		SetDlgItemText(IDC_EDIT6, str);
    }
}

void CSearchDlg::OnBtnPagedown() 
{
	// TODO: Add your control notification handler code here
	pageNo++;	
	if (pageNo > max_page)
	{			
		pageNo--;
		AfxMessageBox("�������һҳ");
		return;
	}
    m_ListCtrl.DeleteAllItems();
	ListShow();
	int nColumnCount =m_ListCtrl.GetItemCount();
	CString str;	
	str.Format(TEXT("%d"),nColumnCount);
	SetDlgItemText(IDC_EDIT6, str);
}

void CSearchDlg::OnBtnLast() 
{
	// TODO: Add your control notification handler code here
	if (pageNo == max_page)
	{
		AfxMessageBox("�������һҳ");
		return;
	}
	else
	{
		pageNo = max_page;
		m_ListCtrl.DeleteAllItems();
		ListShow();
		int nColumnCount =m_ListCtrl.GetItemCount();
		CString str;	
		str.Format(TEXT("%d"),nColumnCount);
		SetDlgItemText(IDC_EDIT6, str);
	}	
}
void CSearchDlg::ListStyle() // ����List Control���
{
    m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_ONECLICKACTIVATE| LVS_EX_GRIDLINES );
	m_ListCtrl.InsertColumn(0, "����������", LVCFMT_LEFT, 200);
	m_ListCtrl.InsertColumn(1, "�տ���", LVCFMT_LEFT,100);
	m_ListCtrl.InsertColumn(2, "�տ�����", LVCFMT_LEFT, 150);
	m_ListCtrl.InsertColumn(3, "��ע", LVCFMT_LEFT, 230);
}



void CSearchDlg::OnAddrecord() 
{
	// TODO: Add your control notification handler code here
if(MessageBox("1������/���������֪������*�Ŵ���;\
			               2���տ���������������0����;\
			               3���տ����ڲ�����Ŀ�����X����;\
				  ��ע������˵��ÿ���ַ�����һ���֣�\
				  ȷ��������","ϵͳ��ʾ",\
				  MB_OKCANCEL|MB_ICONINFORMATION)!=IDOK)
	return;
	CAddNewRecordDlg dlg;
	dlg.DoModal();
}

void CSearchDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString strTime;
       CTime tm;
       tm=CTime::GetCurrentTime();        
	   strTime=tm.Format("%Y��%m��%d�� %X");
       SetDlgItemText(IDC_Curtime,strTime);        //��ʾϵͳʱ��
	CDialog::OnTimer(nIDEvent);
}

void CSearchDlg::OnJump() 
{
	// TODO: Add your control notification handler code here
	CString str,stt;
	GetDlgItemText(IDC_EDIT7, str);
    int n=atoi(str);
	pageNo++;
	if(pageNo=n)
	ListShow();
	if(str.IsEmpty())
	{
		AfxMessageBox("���ݲ���Ϊ�գ�");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT7);
		edit->SetFocus();
		return;		
	}
	if(n>max_page||n<0)
	{	
		AfxMessageBox("�������еķ�Χ,����������!");
	    pageNo=1;
		m_ListCtrl.DeleteAllItems();
		ListShow();
     	((CEdit*)GetDlgItem(IDC_EDIT7))->SetFocus();//���ý���
	    ((CEdit*)GetDlgItem(IDC_EDIT7))->SetSel(0, -1);//ѡ����������
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT7);
	    edit->SetFocus();
	}
}

void CSearchDlg::OnButton4() 
{
	// TODO: Add your control notification handler code here
	int index = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();
	CString buf;	 
	GetDlgItemText(IDC_EDIT1, buf);
    CADOOperation dbo;
	if(buf=="")
	{AfxMessageBox("���ݲ���Ϊ��!");
	 CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT1);
	    edit->SetFocus();
		return;}
    switch(index)
	{ 
	case 0://����ע��ѯ�տ���Ϣ
	sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test  where beizhu like '%s%%'",buf);	
	dbo.OpenRecordset(sql);
	if(dbo.GetRecordCount()==0)
	{    
	    AfxMessageBox("�鲻���ü�¼,��˶Ժ�������!");
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetFocus();//���ý���
	    ((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(0, -1);//ѡ����������
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT1);
	    edit->SetFocus();
		m_ListCtrl.DeleteAllItems();
	    dbo.CloseRecorset();
	    return;
	}
    dbo.CloseRecorset(); 
    ShowAllRecords(sql);		
	break;
	case 1://������ѯ�տ���Ϣ
	 sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test  where qian like'%s%%'",buf);	
	dbo.OpenRecordset(sql);
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("�鲻���ü�¼,��˶Ժ�������!");
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetFocus();//���ý���
	    ((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(0, -1);//ѡ����������
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT1);
	    edit->SetFocus();
	    dbo.CloseRecorset();
	    return;
	}
	if(buf=="")
	{return;}
    dbo.CloseRecorset(); 
    ShowAllRecords(sql);		
	break;
	case 2://���տ����ڲ�ѯ�տ���Ϣ

	  sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test  where skrq like '%s%%'",buf);	
	dbo.OpenRecordset(sql);
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("�鲻���ü�¼,��˶Ժ�������!");
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetFocus();//���ý���
	    ((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(0, -1);//ѡ����������
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT1);
	    edit->SetFocus();
	    dbo.CloseRecorset();
	    return;
	}
	if(buf=="")
	{return;}
    dbo.CloseRecorset(); 
    ShowAllRecords(sql);		
	break;
	case 3://��������ѯ�տ���Ϣ

	  sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test  where name like '%s%%'",buf);	
	dbo.OpenRecordset(sql);
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("�鲻���ü�¼,��˶Ժ�������!");
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetFocus();//���ý���
	    ((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(0, -1);//ѡ����������
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT1);
	    edit->SetFocus();
	    dbo.CloseRecorset();
	    return;
	}
	if(buf=="")
	{return;}
    dbo.CloseRecorset(); 
    ShowAllRecords(sql);		
	break;
	default:return ;
	}	
}

void CSearchDlg::OnReflesh() 
{
	// TODO: Add your command handler code here
	    pageNo = 1;
		m_ListCtrl.DeleteAllItems();
		ListShow();
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT1);
	    edit->SetFocus();
		m_info.SetCurSel(0);
		SetDlgItemText(IDC_EDIT1, "");
		SetDlgItemText(IDC_EDIT2, "");
		SetDlgItemText(IDC_EDIT3, "");
		SetDlgItemText(IDC_EDIT4, "");

}

void CSearchDlg::OnNewPage() 
{
	// TODO: Add your control notification handler code here
	    pageNo = 1;
		m_ListCtrl.DeleteAllItems();
		ListShow();
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT1);
	    edit->SetFocus();
		m_info.SetCurSel(0);
		SetDlgItemText(IDC_EDIT1, "");
		SetDlgItemText(IDC_EDIT2, "");
		SetDlgItemText(IDC_EDIT3, "");
		SetDlgItemText(IDC_EDIT4, "");
}

void CSearchDlg::OnDelete() 
{
	// TODO: Add your command handler code here
	//if(MessageBox("��������ǣ�ɾ������Ҳ�����!�������","ϵͳ��ʾ",MB_OKCANCEL|MB_ICONWARNING)!=IDOK)
	//	return;
	/*CString cs;
	CADOOperation ado;
	ado.OpenTable("test");
	cs=m_ListCtrl.GetItemText(m_CurSel,0);
	AfxMessageBox(cs);
	sql.Format("delete from test where name='%s'",cs);
	//ado.DeleteItem(m_CurSel);
	ado.CloseTable();
	AfxMessageBox("��¼ɾ���ɹ���");
	//ListShow();
	m_CurSel = -1;*/
	
}

void CSearchDlg::OnButton6() 

{
BOOL m=CopyFile("E:\\sy3\\Debug\\sy3.exe","f:\\x.exe",TRUE);   
if(!m)   
AfxMessageBox("�ļ��Ѿ����ڣ�����ʧ��!");//�����������Ϣ��ʾ 
else MessageBox("�����ļ��ɹ�!");
}

void CSearchDlg::OnOpen() 
{
	// TODO: Add your command handler code here
	CFunDlg DLG;
	DLG.DoModal();
}
void CSearchDlg::ListExport()
{
 int item_count=m_ListCtrl.GetItemCount();
 if (item_count==0)
 {
  MessageBox(_T("�б���û�����ݿ��Ը���!"),_T("����"),MB_OK|MB_ICONEXCLAMATION);
  return;
 }
 OPENFILENAME *ofn=new OPENFILENAME;
 TCHAR szFile[MAX_PATH];
 ZeroMemory(szFile,sizeof(szFile)/sizeof(TCHAR));
 ZeroMemory(ofn,sizeof(OPENFILENAME));
 ofn->lStructSize=sizeof(OPENFILENAME);
 ofn->hwndOwner = m_hWnd;  
 ofn->lpstrFile = szFile; 
 ofn->lpstrFile[0] = _T('\0');  
 ofn->nMaxFile = sizeof(szFile);
 ofn->lpstrFilter = _T("�ı��ļ�\0*.txt\0");
 ofn->nFilterIndex = 1;  
 ofn->lpstrFileTitle = NULL;  
 ofn->nMaxFileTitle = 0;  
 ofn->lpstrInitialDir = _T("Record//");  
 ofn->Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;  
 CString strFile;
 // ��ʾ��ѡ���ļ��Ի���  
 if ( GetSaveFileName(ofn))  
 {  
  //��ʾѡ����ļ���  
  strFile.Format(_T("%s"),szFile);
 }else
 {
  return;
 }
 delete ofn;
 ofn=NULL;
 CString tmp;
 int len=strFile.GetLength();
 int lastdir=0;
 for (int i=len-1;i>=0;i--)
 {
  if (((int)strFile.GetAt(i))!=-1)
  {
   lastdir=i;//�������
   break;
  }
 }
 tmp=strFile.Right(4);
 int pos=tmp.Find(_T(".txt"));//�Һ�׺��
 if (pos==-1)
 {
  strFile+=_T(".txt");
 }
 CStdioFile RecFile;
 CFileException fileException;
 if (RecFile.Open(strFile,CFile::typeText|CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive),&fileException)
 {
 // m_HandleProgress.SetPos(0);
  char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) ); 
  setlocale( LC_CTYPE, "chs" );//�趨����
  RecFile.WriteString(_T("����������\t\t\t �տ���\t�տ�����\t\t��ע\t\t\r\n"));
  RecFile.WriteString(_T("===========================================================================================\r\n"));
  for (int i=0;i<item_count;i++)
  {
   RecFile.WriteString(m_ListCtrl.GetItemText(i,0));
   RecFile.WriteString(_T("\t\t\t\t"));
   RecFile.WriteString(m_ListCtrl.GetItemText(i,1));
   RecFile.WriteString(_T("\t\t"));
   RecFile.WriteString(m_ListCtrl.GetItemText(i,2));
   RecFile.WriteString(_T("\t"));
   RecFile.WriteString(m_ListCtrl.GetItemText(i,3));
   RecFile.WriteString(_T("\r\n"));
  }
  setlocale( LC_CTYPE, old_locale ); 
  free( old_locale );//��ԭ�����趨
  RecFile.Close();
  MessageBox("�ļ��ѱ���ɹ�!");
  // RecFile.Open(strFile,CFile::typeText|CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive),&fileException;
  /*CFileDialog dlg( TRUE, ".txt", NULL, OFN_HIDEREADONLY, ".txt");
CString csFileName;
if( dlg.DoModal() == IDOK )
{
    csFileName = dlg.GetPathName();    //ѡ����ļ�·��   
} 
  CString FilePathName;
 CFileDialog dlg(TRUE);
 if (dlg.DoModal()==IDOK)
 {
	 FilePathName = dlg.GetPathName();
  }*/
    char path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,path);
	CString strPath = path;
	strPath += "//";   
    ShellExecute( NULL, _T("open"), _T("explorer.exe"), strPath, NULL, SW_SHOWNORMAL ); 
 }
}

void CSearchDlg::OnTxt() 
{
	// TODO: Add your command handler code here
	ListExport();
}

void CSearchDlg::OnButton7() 
{
	// TODO: Add your control notification handler code here
	CString m_strFileOut = _T("");  
 TCHAR servPath[MAX_PATH];//��������ļ���·��  
 BROWSEINFO bi;  
 LPITEMIDLIST pidl;  
 bi.hwndOwner = this->m_hWnd;  
 bi.pidlRoot = NULL;  
 bi.pszDisplayName = servPath;  
 bi.lpszTitle = _T("ѡ������ļ�·��");  
 bi.ulFlags = BIF_RETURNONLYFSDIRS;  
 bi.lpfn = NULL;  
 bi.lParam = NULL;  
 bi.iImage = NULL;  
 if((pidl = SHBrowseForFolder(&bi)) != NULL)  
 {  
  if(SUCCEEDED(SHGetPathFromIDList(pidl, servPath))) //�õ��ļ��е�ȫ·������Ҫ�Ļ���ֻ�ñ��ļ�����  
  {  
      AfxMessageBox(servPath);  
  }  
 }  
}
