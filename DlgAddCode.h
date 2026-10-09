#pragma once
#include "afxwin.h"

 

class CDlgAddCode : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddCode)

public:
	CDlgAddCode(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAddCode();
	void Initialize( CShape* fp, CArray <CString> * iniCode = NULL);

// Dialog Data
	enum { IDD = IDD_ADD_CODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_code;
	CFont m_font;
	CShape* m_fp;
	CArray<CString> * m_code_text;
	void Outgoing();
	void CodeTextIni();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnSetfocusCode();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeCode();
	afx_msg void OnBnClickedScadTranslate();
	afx_msg void OnBnClickedScadRotate();
	afx_msg void OnBnClickedScadCube();
	afx_msg void OnBnClickedScadCylinder();
	afx_msg void OnBnClickedScadYellow();
	afx_msg void OnBnClickedScadCrimson();
	afx_msg void OnBnClickedScadAqua();
	afx_msg void OnBnClickedScadRosy();
};
