// ADOOperation.cpp: implementation of the CADOOperation class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADOOperation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction             
//////////////////////////////////////////////////////////////////////
const DWORD CADOOperation::ADO_TYPE_STRING			= 100;
const DWORD CADOOperation::ADO_TYPE_BITMAP_FIEL		= 101;
const DWORD CADOOperation::ADO_TYPE_INT				= 102;
const DWORD CADOOperation::ADO_TYPE_FLOAT			= 103;
const DWORD CADOOperation::ADO_TYPE_DATE			= 104;
const DWORD CADOOperation::ADO_TYPE_BITMAP_HANDLE	= 105;
const DWORD CADOOperation::ADO_TYPE_TEXT			= 106;

CADOOperation::CADOOperation()//ADO连接数据库
{
	try{
		//第一种是通过名字创建对象,可能会出现冲突.
        //第二是通过uuid创建对象,这个uuid是唯一的.
		//m_pConnection.CreateInstance("ADODB.Connection");//创建Connection对象
		m_pConnection.CreateInstance(_uuidof(Connection));//创建Connection实例
	//	_bstr_t strConnect="Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;Initial Catalog=HRMS;Data Source=WIN-20140909GPP\\SQLEXPRESS";
		m_pConnection->Open(Provider, "", "", adModeUnknown);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description(), MB_OK);
		exit(0);
	}
	m_pRecordset.CreateInstance(_uuidof(Recordset));//创建Recordset实例
	m_CurrentRecord = -1;
}

CADOOperation::~CADOOperation()
{
	m_pConnection->Close();//销毁Connection实例
}

BOOL CADOOperation::OpenTable(CString name)//打开数据表
{

	ASSERT(!name.IsEmpty());//表名不能为空
	CString sql;
	sql.Format("select * from %s" , name);//构造所要打开表的SQL语句
	try
	{
		//打开记录集
		m_pRecordset->Open(_bstr_t(sql), m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch(_com_error e)//捕获可能的异常
	{
#ifdef _DEBUG
		ShowError(e.Description());//显示异常信息
#endif
		return FALSE;
	}

	return TRUE;
}

BOOL CADOOperation::CloseTable()//关闭打开的数据表
{

	try
	{//判断当前的记录集状态
		if(adStateOpen == m_pRecordset->GetState())
			m_pRecordset->Close();//如果没有关闭则将其关闭
	}
	catch(_com_error e)//捕获可能的异常
	{
		return FALSE;
	}

	return TRUE;
}

HRESULT CADOOperation::AddNew()//添加新记录
{
	return m_pRecordset->AddNew();
}

BOOL CADOOperation::UpdateData()//更新记录
{
	try
	{
		  m_pRecordset->Update();
	}
	catch(_com_error e)
	{
#ifdef _DEBUG
		ShowError(e.Description());
#endif
		return FALSE;
	}

	return  TRUE;
}



BOOL CADOOperation::IsLastRow()//是否到最后一行
{

	if(m_pRecordset->adoEOF)
		return TRUE;

	return FALSE;
}

BOOL CADOOperation::MoveTo(DWORD index)//移动到下一条记录
{
	try
	{
		m_pRecordset->Move(index);
		m_CurrentRecord = index;
	}
	catch(_com_error e)
	{
#ifdef _DEBUG
		ShowError(e.Description());
#endif
		return FALSE;
	}
	return TRUE;
}

DWORD CADOOperation::GetRecordCount()//获取记录集中记录数
{
	DWORD count = 1;
	if(m_pRecordset->adoEOF)
		return 0;

	m_pRecordset->MoveFirst();
	do
	{
		count++;
		m_pRecordset->MoveNext();
	}while(!m_pRecordset->adoEOF);

	return count;
}



BOOL CADOOperation::OpenRecordset(CString sql)//打开记录集
{
	ASSERT(!sql.IsEmpty());//SQL语句不能为空
	try
	{
		//执行SQL得到记录集
		m_pRecordset->Open(_bstr_t(sql), m_pConnection.GetInterfacePtr(), 
			adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch(_com_error e)//捕获可能的异常
	{
#ifdef _DEBUG
		ShowError(e.Description());//显示异常信息
#endif
		return FALSE;
	}

	return TRUE;
}
////读取当前记录指定域的值
BOOL CADOOperation::GetItemContent(DWORD field, DWORD type, void *variable)
{
	ASSERT(type != ADO_TYPE_BITMAP_HANDLE);
	_variant_t variant;
	BOOL ret = TRUE;

	try{
		variant = m_pRecordset->GetCollect(_variant_t((long)field));
		ret = ChangeTypeTo(variant, type, variable, 0);
	}
	catch(_com_error e)
	{
#ifdef _DEBUG
		ShowError(e.Description());
#endif
		return FALSE;
	}
	
	return ret;
}
//得到当前记录指定域的值
BOOL CADOOperation::GetItemContent(CString field,
								   DWORD type, 
								   void *variable)
{
	ASSERT(!field.IsEmpty());
	_variant_t variant;
	try
	{
		if(type != ADO_TYPE_BITMAP_HANDLE && type != ADO_TYPE_TEXT)
		{
			variant = GetSubItem(field);
			ChangeTypeTo(variant, type, variable, 0);
			return TRUE;
		}
		if(type == ADO_TYPE_BITMAP_HANDLE || ADO_TYPE_TEXT == type)
		{
			long bits;

			bits = m_pRecordset->GetFields()->GetItem(_bstr_t(field))->ActualSize;
			if(bits <= 0)
				return TRUE;
			variant = m_pRecordset->GetFields()->GetItem(_bstr_t(field))->GetChunk(bits);
			ChangeTypeTo(variant, type, variable, bits);
		}
	}
	catch(_com_error e)
	{
#ifdef _DEBUG
		ShowError(e.Description());
#endif
		return FALSE;
	}
	return TRUE;
}
//得到记录的序号为index的域的值
_variant_t CADOOperation::GetSubItem(DWORD index)
{
	_variant_t var;
	try{

			var = m_pRecordset->GetCollect(_variant_t((long)index));
	}
	catch(_com_error e)
	{
#ifdef _DEBUG
		ShowError(e.Description());
#endif
		return var;
	}

	return var;
}
//读取当前记录的field域的数据
_variant_t CADOOperation::GetSubItem(CString field)
{
	_variant_t var;
	try{

			var = m_pRecordset->GetCollect(_bstr_t(field));
	}
	catch(_com_error e)
	{
#ifdef _DEBUG
		ShowError(e.Description());
#endif
		return var;
	}

	return var;
}
//设定指定字段的值
BOOL CADOOperation::SetItemContent(CString field, 
								   DWORD type, 
								   const void *variable)
{
	ASSERT(!field.IsEmpty());
	ASSERT(variable != NULL);

	try
	{
		switch(type)
		{
		case ADO_TYPE_STRING:
			m_pRecordset->PutCollect(_bstr_t(field), _bstr_t(*(CString*)(variable)));
			break;
		case ADO_TYPE_BITMAP_FIEL:
			{
				CString* lpStr = (CString*)variable;
				VARIANT bitData = {0};
				CFile file(*lpStr, CFile::modeRead);
				DWORD fileSize = file.GetLength() + 1;
				char* bitBuffer = new char[fileSize];

				file.ReadHuge(bitBuffer, fileSize);
				file.Close();
				
				bitData.vt = VT_ARRAY | VT_UI1;
				SAFEARRAY* pSafeArray;
				SAFEARRAYBOUND arrayBound[1];
				arrayBound[0].cElements = fileSize - 1;
				arrayBound[0].lLbound = 0;
				
				pSafeArray = ::SafeArrayCreate(VT_UI1, 1, arrayBound);
				for(long i = 0; i < fileSize-1; i++)
					::SafeArrayPutElement(pSafeArray, &i, bitBuffer++);
				bitData.parray = pSafeArray;

				m_pRecordset->GetFields()->GetItem(_bstr_t(field))->AppendChunk(bitData);
			}
			break;
		case ADO_TYPE_TEXT:
			{
				CString* lpStr = (CString*)variable;
				VARIANT data;
				SAFEARRAY* pSafeArray;
				SAFEARRAYBOUND arrayBound;
				char *buf;

				data.vt = VT_ARRAY | VT_UI1;
				arrayBound.cElements = lpStr->GetLength();
				arrayBound.lLbound = 0;
				pSafeArray = ::SafeArrayCreate(VT_UI1, 1, &arrayBound);
				buf = lpStr->GetBuffer(0);
				for(unsigned long i = 0; i < arrayBound.cElements; i++)
					::SafeArrayPutElement(pSafeArray, (long*)&i, buf++);
				data.parray = pSafeArray;

				m_pRecordset->GetFields()->GetItem(_bstr_t(field))->AppendChunk(data);
			}
			break;
		case ADO_TYPE_DATE:
			{
				CString str;
				LPSYSTEMTIME lpSystemTime = (LPSYSTEMTIME)variable;

				str.Format("%d-%d-%d", 
					lpSystemTime->wYear, lpSystemTime->wMonth, lpSystemTime->wDay);
				m_pRecordset->PutCollect(_bstr_t(field), 
					_bstr_t(str));
			}
			break;
		case ADO_TYPE_INT:
			{
				CString str;
				str.Format("%d", *(int*)variable);
				m_pRecordset->PutCollect(_bstr_t(field), _bstr_t(str));
			}
			break;
		case ADO_TYPE_FLOAT:
			{
				CString str;
				str.Format("%.2f", *(float*)variable);
				m_pRecordset->PutCollect(_bstr_t(field), _bstr_t(str));
			}
			break;
		default:
			return FALSE;
		}
	}
	catch(_com_error e)
	{
#ifdef _DEBUG
		ShowError(e.Description());
#endif
		return FALSE;
	}

	return TRUE;
}
//把_variant_t转换为指定的类型
BOOL CADOOperation::ChangeTypeTo(_variant_t from, DWORD type, void *pTo, long add)
{
	ASSERT(NULL != pTo);
	switch(type)
	{
	case ADO_TYPE_DATE:
		{
			if(from.vt == VT_NULL)
				return FALSE;

			LPSYSTEMTIME sysTime = (LPSYSTEMTIME)pTo;
			int n, l;
			CString str	= (char*)_bstr_t(from);
			CString d ,m,y;
			
			n = str.Find("-", 0);
			y = str.Left(n);
			l = str.Find("-", n + 1);
			d = str.Right(str.GetLength() - l - 1);
			m = str.Mid(n + 1, l-n-1);
			sysTime->wDay	= atoi(d.GetBuffer(0));
			sysTime->wMonth	= atoi(m.GetBuffer(0));
			sysTime->wYear	= atoi(y.GetBuffer(0));
		}
		break;
	case ADO_TYPE_FLOAT:
		if(from.vt == VT_NULL)
		{
			(*(double*)pTo) = 0;
			break;
		}
		(*(double*)pTo) = (double)from;
		break;
	case ADO_TYPE_BITMAP_HANDLE:
		{
			if(from.vt == VT_NULL)
				return FALSE;
			if(add > 0)
			{
				char *pBuffer;
				if((pBuffer = new char[add]) != NULL)
				{
					if(from.vt == (VT_ARRAY | VT_UI1))
					{
						char *pBuf;
						::SafeArrayAccessData(from.parray, (void**)&pBuf);
						::memcpy(pBuffer, pBuf, add);
						::SafeArrayUnaccessData(from.parray);
						
						char *pDib;
						LPVOID lpDibBits;
						BITMAPFILEHEADER &bmfHeader = *(BITMAPFILEHEADER*)pBuffer;
						DWORD bmfHeaderLen = sizeof(bmfHeader);
						if(bmfHeader.bfType != (*(DWORD*)"BM"))
							return TRUE;
						pDib = pBuffer + bmfHeaderLen;
						BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)pDib;
						BITMAPINFO &bmInfo = *(LPBITMAPINFO)pDib;
						lpDibBits = pBuffer + ((BITMAPFILEHEADER*)pBuffer)->bfOffBits;
						
						*(HBITMAP*)pTo = ::CreateDIBitmap(m_hDC, 
							&bmiHeader, CBM_INIT, lpDibBits, &bmInfo, DIB_RGB_COLORS);
					}
				}
			}
		}
		break;
	case ADO_TYPE_TEXT:
		{
			CString *pStr = (CString* )pTo;
			*pStr = (char*)_bstr_t(from);
		}
		break;
	case ADO_TYPE_INT:
		if(from.vt == VT_NULL)
		{
			(*(long*)pTo) = 0;
			break;
		}
		(*(long*)pTo) = (long)from;
		break ;
	case ADO_TYPE_STRING:
		*(CString* )pTo = 
			(char*)_bstr_t(from);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

void CADOOperation::CloseRecorset()//关闭记录集
{
	try
	{
		if(adStateOpen == m_pRecordset->GetState())
			m_pRecordset->Close();
	}
	catch(_com_error e)
	{
		return ;
	}
}
//删除序号为index的记录
BOOL CADOOperation::DeleteItem(DWORD index)
{
	ASSERT(index >= 0);
	try
	{
		m_pRecordset->Move(index);
		m_pRecordset->Delete(adAffectCurrent);
	}catch(_com_error e)
	{
#ifdef _DEBUG
		ShowError(e.Description());
#endif
		return FALSE;
	}

	return TRUE;
}

HRESULT CADOOperation::MoveFirst()//移动到第一条记录
{
	return m_pRecordset->MoveFirst();
}

HRESULT CADOOperation::MoveNext()//移动到下一条记录
{
	return m_pRecordset->MoveNext();
}


void CADOOperation::ShowError(_bstr_t error)//为了显示出错信息而定义的函数
{
	::MessageBox(NULL, error, "ADO错误", MB_OK | MB_ICONWARNING);
}


void CADOOperation::SetClientDC(HDC hDC)//设置客户端HDC
{
	m_hDC = hDC;
}
