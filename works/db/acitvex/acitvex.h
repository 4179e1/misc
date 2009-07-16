// acitvex.h : main header file for the ACITVEX application
//

#if !defined(AFX_ACITVEX_H__BA3D01F5_548B_4B19_9CCA_44C55871CB0D__INCLUDED_)
#define AFX_ACITVEX_H__BA3D01F5_548B_4B19_9CCA_44C55871CB0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAcitvexApp:
// See acitvex.cpp for the implementation of this class
//

class CAcitvexApp : public CWinApp
{
public:
	CAcitvexApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAcitvexApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAcitvexApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACITVEX_H__BA3D01F5_548B_4B19_9CCA_44C55871CB0D__INCLUDED_)
