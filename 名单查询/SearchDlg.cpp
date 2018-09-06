// SearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "名单查询.h"
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
#include "SkinH.h"//调用皮肤库
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
	m_info.AddString("姓名/网名");
	m_info.AddString("金额(元)");
	m_info.AddString("收款日期");
	m_info.AddString("备注");
	m_info.SetCurSel(0);
	m_chose.AddString(">");
	m_chose.AddString("<");
	m_chose.AddString("=");
	m_chose.SetCurSel(0);
	m_Mytip.Create(this); 
    m_Mytip.AddTool( GetDlgItem(IDC_EDIT1), "输入后查询到的数据将自动显示在列表中" );
	m_Mytip.AddTool( GetDlgItem(IDC_BUTTON1), "按照金额大于、小于或等于某一金额查询" );
	m_Mytip.AddTool( GetDlgItem(IDC_BUTTON2), "按照金额的范围查询" );
	m_Mytip.AddTool( GetDlgItem(IDC_BUTTON3), "将表数据保存到EXCEL表中" );
	m_Mytip.AddTool( GetDlgItem(IDCANCEL), "退出查询界面" );
	m_Mytip.SetDelayTime(100); //设置延迟
	m_Mytip.SetTipTextColor( RGB(100,150,200) ); //设置提示文本的颜色
	m_Mytip.SetTipBkColor( RGB(255,255,255)); //设置提示框的背景颜色
	m_Mytip.Activate(TRUE);
	SetDlgItemText(IDC_EDIT5, "0");
	CString strTime;
       CTime tm;
        tm=CTime::GetCurrentTime();         //获取当前系统时间
       strTime=tm.Format("%y年%m月%d日 %X");   //格式化系统时间。即使系统时 间按照Format中设置的格式显示
       SetDlgItemText(IDC_Curtime,strTime);        //初始化编辑框显示
       SetTimer(1,1000,NULL);         //启动定时器
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
void CSearchDlg::ListShow() // 将数据显示在List Control里，显示页数，显示消息提示
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
		
		while(!testSet.IsEOF()) // 输出匹配上查询条件用户记录,直到记录为空
		{			
			if (i_num >= intStart && i_num < intEnd) // 根据页数显示相应数据
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
				if (pageNo >= 2) // 当页数为1时，i的值就是其本身，如果页数大于1时，i的值恢复到取余以前
				{
					i_num += (pageNo -1) * pageSize;	
				}
				
			}

			i_num++;	
			testSet.MoveNext(); // 记录游标移到下一条记录
		}
		
		if (i_num % pageSize == 0)
		{
			max_page = i_num / pageSize;
		}
		else
		{
			max_page = i_num / pageSize + 1;
		}		
		
		if(testSet.IsOpen()) // 关闭记录集
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
	strpageNo.Format("第 %d 页  ", pageNo);
	strMaxPage.Format("共 %d 页", max_page);
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
	case 0://按备注查询收款信息
        if(xl=="")
		{sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian<'%s'",buf);
		}
		else if(test==0) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian<'%s' and beizhu like '%s%%'",buf,xl);}
		else if(test==1) {
             SetDlgItemText(IDC_EDIT1, "");
			sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian<'%s'",buf);}
		else if(test==2){sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian<'%s' and skrq like '%s%%'",buf,xl);}
		else if(test==3) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian<'%s' and name like '%s%%'",buf,xl);}
		else{AfxMessageBox("没有查到符合条件的记录!");}
	    dbo.OpenRecordset(sql);
	if(buf.IsEmpty())
	{
		AfxMessageBox("数据不能为空！");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT2);
		edit->SetFocus();
		return;		
	}
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("查不到该记录,请核对后再输入!");
		SetDlgItemText(IDC_EDIT2, "");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT2);
	    edit->SetFocus();
	    dbo.CloseRecorset();
	    return;
	}
    dbo.CloseRecorset(); 	
    ShowAllRecords(sql);			
	break;
	case 1://按金额查询收款信息
		  if(xl=="")
		{sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian='%s'",buf);
		}
		else if(test==0) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian='%s' and beizhu like '%s%%'",buf,xl);}
		else if(test==2){sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian='%s' and skrq like '%s%%'",buf,xl);}
		else if(test==3) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian='%s' and name like '%s%%'",buf,xl);}
		else{AfxMessageBox("没有查到符合条件的记录!");}
	dbo.OpenRecordset(sql);
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("查不到该记录,请核对后再输入!");
		SetDlgItemText(IDC_EDIT2, "");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT2);
	    edit->SetFocus();
	    dbo.CloseRecorset();
	    return;
	}
    dbo.CloseRecorset(); 
    ShowAllRecords(sql);		
	break;
	case 2://按收款日期查询收款信息
       if(xl=="")
		{sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian>'%s'",buf);
		}
		else if(test==0) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian>'%s' and beizhu like '%s%%'",buf,xl);}
		else if(test==2){sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian>'%s' and skrq like '%s%%'",buf,xl);}
		else if(test==3) {sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test where qian>'%s' and name like '%s%%'",buf,xl);}
		else{AfxMessageBox("没有查到符合条件的记录!");}
	dbo.OpenRecordset(sql);
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("查不到该记录,请核对后再输入!");
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
		else{AfxMessageBox("没有查到符合条件的记录!");}
	dbo.OpenRecordset(sql);
	if(buf.IsEmpty())
	{
		AfxMessageBox("数据不能为空！");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT3);
		edit->SetFocus();
		return;		
	}
	if(sj.IsEmpty())
	{
		AfxMessageBox("数据不能为空！");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT4);
		edit->SetFocus();
		return;		
	}
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("查不到该记录,请核对后再输入!");
		MessageBox("正在重载数据，请稍后....","系统提示",MB_OKCANCEL|MB_ICONQUESTION);
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
  AfxMessageBox("列表中没有记录需要保存！");
  return;
 }
 //打开另存为对话框 ，需要包含 #include <Afxdlgs.h>
 CFileDialog dlg( FALSE, 
      "xls", 
      "收款名单", 
      OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
      "Excel 文件(*.xls)|*.xls||");
 dlg.m_ofn.lpstrTitle = "将文件另存为...";
 
 if (dlg.DoModal() != IDOK)
  return;
 CString strFilePath;
 //获得文件路径名
 strFilePath = dlg.GetPathName();
 //判断文件是否已经存在，存在则删除重建
 DWORD dwRe = GetFileAttributes(strFilePath);
 if ( dwRe != (DWORD)-1 )
 {
  DeleteFile(strFilePath);
 }
 CDatabase database;//数据库库需要包含头文件 #include <afxdb.h>
 CString sDriver = "MICROSOFT EXCEL DRIVER (*.XLS)"; // Excel驱动
 CString sSql,strInsert;
 TRY
 {
  // 创建进行存取的字符串
  sSql.Format("DRIVER={%s};DSN='';FIRSTROWHASNAMES=1;READONLY=FALSE;CREATE_DB=\"%s\";DBQ=%s",sDriver, strFilePath, strFilePath);
  
  // 创建数据库 (既Excel表格文件)
  if( database.OpenEx(sSql,CDatabase::noOdbcDialog) )
  {
   //获得列别框总列数
   int iColumnNum,iRowCount;
   LVCOLUMN lvCol;
   CString strColName; //用于保存列标题名称
   int i,j; //列、行循环参数
  
   iColumnNum = m_ListCtrl.GetHeaderCtrl()->GetItemCount();
   iRowCount = m_ListCtrl.GetItemCount();
   sSql = " CREATE TABLE DSO_DX ( ";
   strInsert = " INSERT INTO DSO_DX ( " ;
   //获得列标题名称
   lvCol.mask = LVCF_TEXT; //必需设置，说明LVCOLUMN变量中pszText参数有效
   lvCol.cchTextMax = 32; //必设，pszText参数所指向的字符串的大小
   lvCol.pszText = strColName.GetBuffer(32); //必设，pszText 所指向的字符串的实际存储位置。
   //以上三个参数设置后才能通过 GetColumn()函数获得列标题的名称
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
   //创建Excel表格文件
   database.ExecuteSQL(sSql);
   //循环提取记录并插入到EXCEL中
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
    //将记录插入到表格中
    database.ExecuteSQL(sSql);
    sSql = strInsert; 
   }
  }     
  // 关闭Excel表格文件
  database.Close();
  AfxMessageBox("保存收款信息表成功！");
 }
 CATCH_ALL(e)
 {
  //错误类型很多，根据需要进行报错。
  AfxMessageBox("Excel表格保存失败。");
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
	{	AfxMessageBox("请选择一条记录进行操作!");
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
strText=new char[40];//存储从文件读取的数据
for(int i=0;i<m_ListCtrl.GetItemCount();i++)
{
m_ListCtrl.GetItemText(i,(int)strText);
sf.Seek(40*i,CFile::begin);//定位文件指针
sf.Write(strText,40);//写文件数据
}
HGLOBAL hMem=sf.Detach();
if(!hMem)
return;
CoInitialize(NULL);
pSource->CacheGlobalData(CF_TEXT,hMem);
pSource->SetClipboard();//添加到剪切板中
*/
/*	CString str;  
HGLOBAL hClip;  
//定义一个HGLOBAL句柄变量用来指向分配的内存块
if (OpenClipboard())
{
EmptyClipboard(); //将剪贴板内容清空
hClip=GlobalAlloc(GMEM_MOVEABLE,str.GetLength()+1);  
//在堆上分配可移动的内存块，程序返回一个内存句柄
char * buff; //定义指向字符型的指针变量
buff=(char*)GlobalLock(hClip);
//对分配的内存块进行加锁，将内存块句柄转化成一个指针,并将相应的引用计数器加1
strcpy(buff,str);
//将用户输入的数据复制到指针变量中，实际上就是复制到分配的内存块中
GlobalUnlock(hClip);
//数据写入完毕，进行解锁操作，并将引用计数器数字减1
SetClipboardData(CF_TEXT,hClip);
//将存放有数据的内存块放入剪贴板的资源管理中
CloseClipboard();
//关闭剪贴板，释放剪贴板资源的占用权
MessageBox("已将数据存入剪贴板");
}  

//从剪贴板中取出文本：  

//CString str;
//字符型变量保存由剪贴板复制下来的数据
//HANDLE hClip;
//定义HANDLE句柄型变量用来指向GetClipboardData函数返回的句柄
if (OpenClipboard())
{
hClip=GetClipboardData(CF_TEXT);
//从剪贴板中取出一个内存的句柄
char* buff;
//定义字符型指针变量用来保存内存块中的数据
buff=(char*)GlobalLock(hClip);
//对内存块进行加锁，将内存句柄值转化为一个指针,并将内存块的引用计数器加一，内存中的数据也返回到指针型变量中
str=buff;
//将数据保存到字符型变量中
GlobalUnlock(hClip);
//将内存块的引用计数器减一
CloseClipboard();
//关闭剪贴板，释放剪贴板资源的占用权

}
  */
}

void CSearchDlg::OnBtnFirst() 
{
	// TODO: Add your control notification handler code here
		if (pageNo == 1)
	{
		AfxMessageBox(_T("已是第一页"));
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
        AfxMessageBox(_T("已是第一页"));
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
		AfxMessageBox("已是最后一页");
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
		AfxMessageBox("已是最后一页");
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
void CSearchDlg::ListStyle() // 设置List Control风格
{
    m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_ONECLICKACTIVATE| LVS_EX_GRIDLINES );
	m_ListCtrl.InsertColumn(0, "姓名或网名", LVCFMT_LEFT, 200);
	m_ListCtrl.InsertColumn(1, "收款金额", LVCFMT_LEFT,100);
	m_ListCtrl.InsertColumn(2, "收款日期", LVCFMT_LEFT, 150);
	m_ListCtrl.InsertColumn(3, "备注", LVCFMT_LEFT, 230);
}



void CSearchDlg::OnAddrecord() 
{
	// TODO: Add your control notification handler code here
if(MessageBox("1、姓名/网名如果不知道可用*号代替;\
			               2、收款金额如果不清楚可用0代替;\
			               3、收款日期不清楚的可以用X代替;\
				  （注：以上说明每个字符代表一个字）\
				  确定进入吗？","系统提示",\
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
	   strTime=tm.Format("%Y年%m月%d日 %X");
       SetDlgItemText(IDC_Curtime,strTime);        //显示系统时间
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
		AfxMessageBox("数据不能为空！");
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT7);
		edit->SetFocus();
		return;		
	}
	if(n>max_page||n<0)
	{	
		AfxMessageBox("超出已有的范围,请重新输入!");
	    pageNo=1;
		m_ListCtrl.DeleteAllItems();
		ListShow();
     	((CEdit*)GetDlgItem(IDC_EDIT7))->SetFocus();//设置焦点
	    ((CEdit*)GetDlgItem(IDC_EDIT7))->SetSel(0, -1);//选中其中内容
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
	{AfxMessageBox("数据不能为空!");
	 CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT1);
	    edit->SetFocus();
		return;}
    switch(index)
	{ 
	case 0://按备注查询收款信息
	sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test  where beizhu like '%s%%'",buf);	
	dbo.OpenRecordset(sql);
	if(dbo.GetRecordCount()==0)
	{    
	    AfxMessageBox("查不到该记录,请核对后再输入!");
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetFocus();//设置焦点
	    ((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(0, -1);//选中其中内容
		CEdit* edit=(CEdit*)GetDlgItem(IDC_EDIT1);
	    edit->SetFocus();
		m_ListCtrl.DeleteAllItems();
	    dbo.CloseRecorset();
	    return;
	}
    dbo.CloseRecorset(); 
    ShowAllRecords(sql);		
	break;
	case 1://按金额查询收款信息
	 sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test  where qian like'%s%%'",buf);	
	dbo.OpenRecordset(sql);
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("查不到该记录,请核对后再输入!");
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetFocus();//设置焦点
	    ((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(0, -1);//选中其中内容
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
	case 2://按收款日期查询收款信息

	  sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test  where skrq like '%s%%'",buf);	
	dbo.OpenRecordset(sql);
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("查不到该记录,请核对后再输入!");
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetFocus();//设置焦点
	    ((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(0, -1);//选中其中内容
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
	case 3://按姓名查询收款信息

	  sql.Format("select name as xm, qian as mimi, skrq as sj,beizhu as bz from test  where name like '%s%%'",buf);	
	dbo.OpenRecordset(sql);
	if(dbo.GetRecordCount()==0)
	{    
		AfxMessageBox("查不到该记录,请核对后再输入!");
		((CEdit*)GetDlgItem(IDC_EDIT1))->SetFocus();//设置焦点
	    ((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(0, -1);//选中其中内容
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
	//if(MessageBox("请谨慎考虑，删除后就找不到了!想好了吗？","系统提示",MB_OKCANCEL|MB_ICONWARNING)!=IDOK)
	//	return;
	/*CString cs;
	CADOOperation ado;
	ado.OpenTable("test");
	cs=m_ListCtrl.GetItemText(m_CurSel,0);
	AfxMessageBox(cs);
	sql.Format("delete from test where name='%s'",cs);
	//ado.DeleteItem(m_CurSel);
	ado.CloseTable();
	AfxMessageBox("记录删除成功！");
	//ListShow();
	m_CurSel = -1;*/
	
}

void CSearchDlg::OnButton6() 

{
BOOL m=CopyFile("E:\\sy3\\Debug\\sy3.exe","f:\\x.exe",TRUE);   
if(!m)   
AfxMessageBox("文件已经存在，复制失败!");//这里是添加消息提示 
else MessageBox("复制文件成功!");
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
  MessageBox(_T("列表中没有数据可以复制!"),_T("警告"),MB_OK|MB_ICONEXCLAMATION);
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
 ofn->lpstrFilter = _T("文本文件\0*.txt\0");
 ofn->nFilterIndex = 1;  
 ofn->lpstrFileTitle = NULL;  
 ofn->nMaxFileTitle = 0;  
 ofn->lpstrInitialDir = _T("Record//");  
 ofn->Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;  
 CString strFile;
 // 显示打开选择文件对话框。  
 if ( GetSaveFileName(ofn))  
 {  
  //显示选择的文件。  
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
   lastdir=i;//反射查找
   break;
  }
 }
 tmp=strFile.Right(4);
 int pos=tmp.Find(_T(".txt"));//找后缀名
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
  setlocale( LC_CTYPE, "chs" );//设定中文
  RecFile.WriteString(_T("姓名或网名\t\t\t 收款金额\t收款日期\t\t备注\t\t\r\n"));
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
  free( old_locale );//还原区域设定
  RecFile.Close();
  MessageBox("文件已保存成功!");
  // RecFile.Open(strFile,CFile::typeText|CFile::modeCreate|CFile::modeWrite|CFile::shareExclusive),&fileException;
  /*CFileDialog dlg( TRUE, ".txt", NULL, OFN_HIDEREADONLY, ".txt");
CString csFileName;
if( dlg.DoModal() == IDOK )
{
    csFileName = dlg.GetPathName();    //选择的文件路径   
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
 TCHAR servPath[MAX_PATH];//用来存放文件夹路径  
 BROWSEINFO bi;  
 LPITEMIDLIST pidl;  
 bi.hwndOwner = this->m_hWnd;  
 bi.pidlRoot = NULL;  
 bi.pszDisplayName = servPath;  
 bi.lpszTitle = _T("选择输出文件路径");  
 bi.ulFlags = BIF_RETURNONLYFSDIRS;  
 bi.lpfn = NULL;  
 bi.lParam = NULL;  
 bi.iImage = NULL;  
 if((pidl = SHBrowseForFolder(&bi)) != NULL)  
 {  
  if(SUCCEEDED(SHGetPathFromIDList(pidl, servPath))) //得到文件夹的全路径，不要的话，只得本文件夹名  
  {  
      AfxMessageBox(servPath);  
  }  
 }  
}
