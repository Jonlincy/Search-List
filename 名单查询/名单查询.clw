; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSearchDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "名单查询.h"

ClassCount=9
Class1=CMyApp
Class2=CMyDlg
Class3=CAboutDlg

ResourceCount=9
Resource1=IDD_AddRec
Resource2=IDR_MAINFRAME
Resource3=IDD_FUN
Class4=CSearchDlg
Resource4=IDD_MY_DIALOG
Class5=CModifyDlg
Resource5=IDD_ADDRECDLG
Class6=CSearchSet
Resource6=IDD_Sousuo
Class7=CAddRecordDlg
Resource7=IDD_Modify
Class8=CAddNewRecordDlg
Resource8=IDD_ABOUTBOX
Class9=CFunDlg
Resource9=IDR_MENU1

[CLS:CMyApp]
Type=0
HeaderFile=名单查询.h
ImplementationFile=名单查询.cpp
Filter=N

[CLS:CMyDlg]
Type=0
HeaderFile=名单查询Dlg.h
ImplementationFile=名单查询Dlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CMyDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=名单查询Dlg.h
ImplementationFile=名单查询Dlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MY_DIALOG]
Type=1
Class=CMyDlg
ControlCount=3
Control1=IDC_BUTTON1,button,1342242816
Control2=IDC_BUTTON2,button,1342242816
Control3=IDC_STATIC,static,1342177294

[DLG:IDD_Sousuo]
Type=1
Class=CSearchDlg
ControlCount=49
Control1=IDCANCEL,button,1342242816
Control2=IDC_LIST1,SysListView32,1350631425
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO1,combobox,1344340226
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT1,edit,1350631552
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT2,edit,1350631552
Control10=IDC_BUTTON1,button,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT3,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT4,edit,1350631552
Control15=IDC_BUTTON2,button,1342242816
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_COMBO2,combobox,1344340226
Control19=IDC_STATIC,button,1342177287
Control20=IDC_STATIC,button,1342177287
Control21=IDC_STATIC,button,1342177287
Control22=IDC_STATIC,static,1342308352
Control23=IDC_EDIT5,edit,1484849280
Control24=IDC_STATIC,static,1342308352
Control25=IDC_EDIT6,edit,1484849280
Control26=IDC_STATIC,button,1342177287
Control27=IDC_BUTTON3,button,1342242816
Control28=IDC_BTN_FIRST,button,1342242816
Control29=IDC_BTN_PAGEUP,button,1342242816
Control30=IDC_BTN_PAGEDOWN,button,1342242816
Control31=IDC_BTN_LAST,button,1342242816
Control32=IDC_STATIC_SHOWPAGE,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_ADDRECORD,button,1342242816
Control35=IDC_STATIC,static,1342308352
Control36=IDC_EDIT7,edit,1350631552
Control37=IDC_STATIC,static,1342308352
Control38=IDC_BUTTON5,button,1342242816
Control39=IDC_STATIC,static,1342308352
Control40=IDC_Curtime,edit,1350631552
Control41=IDC_STATIC,static,1342308352
Control42=IDC_BUTTON4,button,1342242816
Control43=IDC_NewPage,button,1342242816
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,static,1342308352
Control46=IDC_EDIT8,edit,1350631552
Control47=IDC_STATIC,static,1342308352
Control48=IDC_BUTTON6,button,1342242816
Control49=IDC_BUTTON7,button,1342242816

[CLS:CSearchDlg]
Type=0
HeaderFile=SearchDlg.h
ImplementationFile=SearchDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_TXT

[DLG:IDD_Modify]
Type=1
Class=CModifyDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1484849280
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1484849280
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT3,edit,1484849280
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT4,edit,1350631552

[CLS:CModifyDlg]
Type=0
HeaderFile=ModifyDlg.h
ImplementationFile=ModifyDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[MNU:IDR_MENU1]
Type=1
Class=?
Command1=ID_Reflesh
Command2=ID_COPY
Command3=ID_DELETE
Command4=ID_Open
Command5=ID_TXT
CommandCount=5

[CLS:CSearchSet]
Type=0
HeaderFile=SearchSet.h
ImplementationFile=SearchSet.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=CSearchSet

[DB:CSearchSet]
DB=1
DBType=ODBC
ColumnCount=4
Column1=[name], -9, 510
Column2=[qian], 6, 8
Column3=[skrq], -9, 510
Column4=[beizhu], -9, 510

[DLG:IDD_AddRec]
Type=1
Class=CAddRecordDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT3,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT4,edit,1350631552

[CLS:CAddRecordDlg]
Type=0
HeaderFile=AddRecordDlg.h
ImplementationFile=AddRecordDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAddRecordDlg
VirtualFilter=dWC

[DLG:IDD_ADDRECDLG]
Type=1
Class=CAddNewRecordDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT2,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT3,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT4,edit,1350631552

[CLS:CAddNewRecordDlg]
Type=0
HeaderFile=AddNewRecordDlg.h
ImplementationFile=AddNewRecordDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CAddNewRecordDlg
VirtualFilter=dWC

[DLG:IDD_FUN]
Type=1
Class=CFunDlg
ControlCount=1
Control1=IDC_EXPLORER1,{8856F961-340A-11D0-A96B-00C04FD705A2},1342242816

[CLS:CFunDlg]
Type=0
HeaderFile=FunDlg.h
ImplementationFile=FunDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_Open
VirtualFilter=dWC

