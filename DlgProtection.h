#pragma once


// CDlgProtection dialog

class CDlgProtection : public CDialog
{
	DECLARE_DYNAMIC(CDlgProtection)

public:
	CDlgProtection(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgProtection();

// Dialog Data
	enum { IDD = IDD_PROTECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void Ini( CFreePcbDoc * doc );
	void ExtProtection( int protect );
	BOOL Protect( int protect );
	BOOL FindArchive();	
	BOOL CheckTxtMsg();
	CFreePcbDoc * m_doc;
	CButton m_en;
	CButton m_dis;
	CButton m_en_NL;
	CButton m_dis_NL;
	CButton m_gerber_gen_protect;
	CButton m_arch_pres_protect;
	CButton m_import_protect;
	afx_msg void OnBnClickedCancel();
};