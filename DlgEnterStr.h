#pragma once


// CDlgEnterStr dialog

class CDlgEnterStr : public CDialog
{
	DECLARE_DYNAMIC(CDlgEnterStr)

public:
	CDlgEnterStr(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgEnterStr();
	void Initialize( CString * win_str, CString * ini_str );

// Dialog Data
	enum { IDD = IDD_STR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_win_str;
	CString m_str; //
	CEdit m_edit;
};