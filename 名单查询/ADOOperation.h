// ADOOperation.h: interface for the CADOOperation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOOPERATION_H__25CF0522_2F36_474F_AE67_BB68713F34EE__INCLUDED_)
#define AFX_ADOOPERATION_H__25CF0522_2F36_474F_AE67_BB68713F34EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CADOOperation  
{
public:
	static const DWORD ADO_TYPE_BITMAP_HANDLE;
	static const DWORD ADO_TYPE_INT;
	static const DWORD ADO_TYPE_FLOAT;
	static const DWORD ADO_TYPE_DATE;
	static const DWORD ADO_TYPE_BITMAP_FIEL;
	static const DWORD ADO_TYPE_STRING;
	static const DWORD ADO_TYPE_TEXT;
public:
	void SetClientDC(HDC hDC);
	void ShowError(_bstr_t error);
	HRESULT MoveNext();
	HRESULT MoveFirst();
	BOOL DeleteItem(DWORD index);
	void CloseRecorset();
	BOOL ChangeTypeTo(_variant_t from, DWORD type, void *pTo, long add);
	_variant_t GetSubItem(CString field);
	_variant_t GetSubItem(DWORD index);
	BOOL GetItemContent(DWORD field, DWORD type, void *variable);
	BOOL GetItemContent(CString field, DWORD type, void* variable);
	BOOL SetItemContent(CString field, DWORD type, const void* variable);
	BOOL OpenRecordset(CString sql);
	DWORD GetRecordCount();
	BOOL MoveTo(DWORD index);
	BOOL IsLastRow();
	BOOL UpdateData();
	HRESULT AddNew();
	BOOL CloseTable();
	BOOL OpenTable(CString name);
	CADOOperation();
	virtual ~CADOOperation();
private:
	HDC m_hDC;
	DWORD m_CurrentRecord;
	_RecordsetPtr m_pRecordset;
	_ConnectionPtr m_pConnection;
};

#endif // !defined(AFX_ADOOPERATION_H__25CF0522_2F36_474F_AE67_BB68713F34EE__INCLUDED_)
