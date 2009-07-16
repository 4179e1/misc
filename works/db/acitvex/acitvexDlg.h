// acitvexDlg.h : header file
//

#if !defined(AFX_ACITVEXDLG_H__45005162_C299_4496_A591_9466C6418FDC__INCLUDED_)
#define AFX_ACITVEXDLG_H__45005162_C299_4496_A591_9466C6418FDC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAcitvexDlg dialog

class CAcitvexDlg : public CDialog
{
// Construction
public:
	CAcitvexDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAcitvexDlg)
	enum { IDD = IDD_ACITVEX_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAcitvexDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAcitvexDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACITVEXDLG_H__45005162_C299_4496_A591_9466C6418FDC__INCLUDED_)
