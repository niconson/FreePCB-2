// DlgImportOptions.cpp : implementation file
//

#include "stdafx.h"
#include "FreePcb.h"
#include "DlgImportOptions.h"
#include ".\dlgimportoptions.h"


// CDlgImportOptions dialog

IMPLEMENT_DYNAMIC(CDlgImportOptions, CDialog)
CDlgImportOptions::CDlgImportOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImportOptions::IDD, pParent)
{
}

CDlgImportOptions::~CDlgImportOptions()
{
}

void CDlgImportOptions::DoDataExchange(CDataExchange* pDX)
{
	int m_reload = 0;
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_REMOVE_PARTS, m_radio_remove_parts);
	DDX_Control(pDX, IDC_RADIO_KEEP_PARTS_NO_CONNECTIONS, m_radio_keep_parts_no_connections);
	DDX_Control(pDX, IDC_RADIO_KEEP_PARTS_AND_CONNECTIONS, m_radio_keep_parts_and_connections);
	DDX_Control(pDX, IDC_RADIO4, m_radio_change_fp);
	DDX_Control(pDX, IDC_RADIO3, m_radio_keep_fp);
	DDX_Control(pDX, IDC_RADIO5, m_radio_keep_fp_package_m);
	DDX_Control(pDX, IDC_REMOVE_NOT_NL, m_radio_remove_not_nl_nets);
	DDX_Control(pDX, IDC_REMOVE_OLD_NET, m_radio_remove_part_nets);
	DDX_Control(pDX, IDC_RENAME_SAME, m_radio_rename_netxxxxx_nets);
	DDX_Control(pDX, IDC_CHECK_KEEP_TRACES, m_check_keep_traces);
	DDX_Control(pDX, IDC_CHECK_KEEP_STUBS, m_check_keep_stubs);
	DDX_Control(pDX, IDC_CHECK_KEEP_AREAS, m_check_keep_areas);
	DDX_Control(pDX, ID_SAVE_AND_IMPORT, m_button_save_and_import);
	DDX_Check(pDX, IDC_RELOAD_LIB, m_reload);
	if( !pDX->m_bSaveAndValidate )
	{
		// incoming
		if( m_flags & IMPORT_PARTS )
		{
			m_radio_remove_parts.EnableWindow( 1 );
			m_radio_keep_parts_no_connections.EnableWindow( 1 );
			m_radio_keep_parts_and_connections.EnableWindow( 1 );
			m_radio_keep_fp.EnableWindow( 1 );
			m_radio_keep_fp_package_m.EnableWindow( 1 );
			m_radio_change_fp.EnableWindow( 1 );
			if( m_flags & KEEP_PARTS_AND_CON )
				m_radio_keep_parts_and_connections.SetCheck( TRUE );
			else if( m_flags & KEEP_PARTS_NO_CON )
				m_radio_keep_parts_no_connections.SetCheck( TRUE );
			else
				m_radio_remove_parts.SetCheck( TRUE );
			if( m_flags & KEEP_FP )
				m_radio_keep_fp.SetCheck( TRUE );
			else if( m_flags & KEEP_FP_PACKAGE_MATCH )
				m_radio_keep_fp_package_m.SetCheck( TRUE );
			else
				m_radio_change_fp.SetCheck( TRUE );
		}
		else
		{
			m_radio_remove_parts.EnableWindow( 0 );
			m_radio_keep_parts_no_connections.EnableWindow( 0 );
			m_radio_keep_parts_and_connections.EnableWindow( 0 );
			m_radio_keep_fp.EnableWindow( 0 );
			m_radio_keep_fp_package_m.EnableWindow( 0 );
			m_radio_change_fp.EnableWindow( 0 );
		}
		if( m_flags & IMPORT_NETS )
		{
			m_radio_remove_not_nl_nets.EnableWindow( 1 );
			m_radio_remove_part_nets.EnableWindow( 1 );
			m_radio_rename_netxxxxx_nets.EnableWindow( 1 );
			m_check_keep_traces.EnableWindow( 1 );
			m_check_keep_stubs.EnableWindow( 1 );
			m_check_keep_areas.EnableWindow( 1 );
			//
			m_radio_remove_not_nl_nets.SetCheck( 0 );
			m_radio_remove_part_nets.SetCheck( 0 );
			m_radio_rename_netxxxxx_nets.SetCheck( 0 );
			//
			if( m_flags & REM_NOT_NL_NETS )
				m_radio_remove_not_nl_nets.SetCheck( TRUE );
			if( m_flags & REM_PRES_PART_NETS )
				m_radio_remove_part_nets.SetCheck( TRUE );
			if( m_flags & RENAME_NETXXXXX_NETS )
				m_radio_rename_netxxxxx_nets.SetCheck( TRUE );
			m_check_keep_traces.SetCheck( m_flags & KEEP_TRACES );
			m_check_keep_stubs.SetCheck( m_flags & KEEP_STUBS );
			m_check_keep_areas.SetCheck( m_flags & KEEP_AREAS );
			//
			OnBnClickedRemoveNotNl();
		}
		else
		{
			m_radio_remove_not_nl_nets.EnableWindow( 0 );
			m_radio_remove_not_nl_nets.EnableWindow( 0 );
			m_radio_rename_netxxxxx_nets.EnableWindow( 0 );
			m_check_keep_traces.EnableWindow( 0 );
			m_check_keep_stubs.EnableWindow( 0 );
			m_check_keep_areas.EnableWindow( 0 );
		}
	}
	else
	{
		// outgoing
		if( m_flags & IMPORT_PARTS )
		{
			m_flags &= ~(KEEP_PARTS_NO_CON | KEEP_PARTS_AND_CON | KEEP_FP | KEEP_FP_PACKAGE_MATCH);
			if( m_radio_keep_parts_no_connections.GetCheck() )
				m_flags |= KEEP_PARTS_NO_CON;
			else if( m_radio_keep_parts_and_connections.GetCheck() )
				m_flags |= KEEP_PARTS_AND_CON;
			//
			if( m_radio_keep_fp.GetCheck() )
				m_flags |= KEEP_FP;
			else if( m_radio_keep_fp_package_m.GetCheck() )
				m_flags |= KEEP_FP_PACKAGE_MATCH;
		}
		if( m_flags & IMPORT_NETS )
		{
			m_flags &= ~(REM_NOT_NL_NETS | REM_PRES_PART_NETS | RENAME_NETXXXXX_NETS | KEEP_TRACES | KEEP_STUBS | KEEP_AREAS);
			if( m_radio_remove_not_nl_nets.GetCheck() )
				m_flags |= REM_NOT_NL_NETS;
			if( m_radio_remove_part_nets.GetCheck() )
				m_flags |= REM_PRES_PART_NETS;
			if( m_radio_rename_netxxxxx_nets.GetCheck() )
				m_flags |= RENAME_NETXXXXX_NETS;
			if( m_check_keep_traces.GetCheck() )
				m_flags |= KEEP_TRACES;
			if( m_check_keep_stubs.GetCheck() )
				m_flags |= KEEP_STUBS;
			if( m_check_keep_areas.GetCheck() )
				m_flags |= KEEP_AREAS;
		}
		if( m_reload )
			m_flags |= UPDATE_LIB_INDEX;
		else
			m_flags &= ~UPDATE_LIB_INDEX;
	}
}


BEGIN_MESSAGE_MAP(CDlgImportOptions, CDialog)
	ON_BN_CLICKED(ID_SAVE_AND_IMPORT, OnBnClickedSaveAndImport)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_REMOVE_NOT_NL, &CDlgImportOptions::OnBnClickedRemoveNotNl)
END_MESSAGE_MAP()

void CDlgImportOptions::Initialize( int flags )
{
	m_flags = flags;
}

// CDlgImportOptions message handlers

void CDlgImportOptions::OnBnClickedSaveAndImport()
{
	m_flags |= SAVE_BEFORE_IMPORT;
	OnOK();
}

void CDlgImportOptions::OnBnClickedOk()
{
	m_flags &= ~SAVE_BEFORE_IMPORT;
	OnOK();
}

void CDlgImportOptions::OnBnClickedRemoveNotNl()
{
	// TODO: добавьте свой код обработчика уведомлений
	if( m_radio_remove_not_nl_nets.GetCheck() )
	{
		m_radio_rename_netxxxxx_nets.SetCheck( 0 );
		m_radio_rename_netxxxxx_nets.EnableWindow( 0 );
	}
	else
		m_radio_rename_netxxxxx_nets.EnableWindow( 1 );
}
