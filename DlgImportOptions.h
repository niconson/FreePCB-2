#pragma once
#include "afxwin.h"


// CDlgImportOptions dialog

class CDlgImportOptions : public CDialog
{
	DECLARE_DYNAMIC(CDlgImportOptions)

public:
	CDlgImportOptions(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgImportOptions();
	void Initialize( int flags );

// Dialog Data
	enum { IDD = IDD_IMPORT_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_flags;
	CButton m_radio_remove_parts;
	CButton m_radio_keep_parts_no_connections;
	CButton m_radio_keep_parts_and_connections;
	CButton m_radio_change_fp;
	CButton m_radio_keep_fp;
	CButton m_radio_keep_fp_package_m;
	CButton m_radio_remove_not_nl_nets;
	CButton m_radio_remove_part_nets;
	CButton m_radio_rename_netxxxxx_nets;
	CButton m_check_keep_traces;
	CButton m_check_keep_stubs;
	CButton m_check_keep_areas;
	CButton m_button_save_and_import;
	afx_msg void OnBnClickedSaveAndImport();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedRemoveNotNl();
};
