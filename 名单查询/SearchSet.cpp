// SearchSet.cpp : implementation file
//

#include "stdafx.h"
#include "Ãûµ¥²éÑ¯.h"
#include "SearchSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchSet

IMPLEMENT_DYNAMIC(CSearchSet, CRecordset)

CSearchSet::CSearchSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSearchSet)
	m_name = _T("");
	m_qian = 0.0;
	m_skrq = _T("");
	m_beizhu = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSearchSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=pageChange");
}

CString CSearchSet::GetDefaultSQL()
{
	return _T("[dbo].[test]");
}

void CSearchSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSearchSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[name]"), m_name);
	RFX_Double(pFX, _T("[qian]"), m_qian);
	RFX_Text(pFX, _T("[skrq]"), m_skrq);
	RFX_Text(pFX, _T("[beizhu]"), m_beizhu);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSearchSet diagnostics

#ifdef _DEBUG
void CSearchSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSearchSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
