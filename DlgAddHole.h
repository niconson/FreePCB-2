
#pragma once
#include "afxwin.h"



class CDlgAddHole : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddHole)

public:
	CDlgAddHole(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAddHole();
	void Initialize(CShape* fp);

	// Dialog Data
	enum { IDD = IDD_ADD_CODE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_code;
	CFont m_font;
	CShape* m_fp;
	CArray<CString>* m_code_text;
	void Outgoing();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnSetfocusCode();
	afx_msg void OnBnClickedOk();
};
