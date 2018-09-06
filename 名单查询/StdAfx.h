// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__2D262945_D0C5_4FD0_88BF_75701D3040E2__INCLUDED_)
#define AFX_STDAFX_H__2D262945_D0C5_4FD0_88BF_75701D3040E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxdb.h"
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include "afxdb.h"
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace \
rename("EOF","adoEOF") rename("BOF","adoBOF")
#define Provider\
	"Provider=SQLOLEDB.1;Integrated Security=SSPI;Persist Security Info=False;\
		Initial Catalog=MD;Data Source=ZGC-01601101722\\SQLEXPRESS"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__2D262945_D0C5_4FD0_88BF_75701D3040E2__INCLUDED_)
