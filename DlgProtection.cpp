// DlgAddMerge.cpp : implementation file
//

#include "stdafx.h"
#include "FreePcb.h"
#include "DlgProtection.h"


// CDlgAddMergeName dialog

IMPLEMENT_DYNAMIC(CDlgProtection, CDialog)
CDlgProtection::CDlgProtection(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProtection::IDD, pParent)
{
	m_doc = NULL;
}  

CDlgProtection::~CDlgProtection()
{
}

void CDlgProtection::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_EE, m_en);
	DDX_Control(pDX, IDC_RADIO_DE, m_dis);
	DDX_Control(pDX, IDC_RADIO_EE2, m_en_NL);
	DDX_Control(pDX, IDC_RADIO_DE2, m_dis_NL);
	DDX_Control(pDX, IDC_PROTECT_AFTER_GERBER, m_gerber_gen_protect);
	DDX_Control(pDX, IDC_PROTECT_ARCH_PRESENT, m_arch_pres_protect);
	DDX_Control(pDX, IDC_PROTECT_AFTER_IMPORT, m_import_protect);
	if( pDX->m_bSaveAndValidate )
	{
		if( m_dis.GetCheck() )
			setbit( m_doc->m_view->m_protected, CFreePcbDoc::PROTECT );
		else
			clrbit( m_doc->m_view->m_protected, CFreePcbDoc::PROTECT );
		//
		if( m_dis_NL.GetCheck() )
			m_doc->m_netlist_completed = 1;
		else
			m_doc->m_netlist_completed = 0;
		//
		if( m_gerber_gen_protect.GetCheck() )
			setbit( m_doc->m_view->m_protected, CFreePcbDoc::PROTECT_ON_GERBER );
		else
			clrbit( m_doc->m_view->m_protected, CFreePcbDoc::PROTECT_ON_GERBER );
		//
		if( m_arch_pres_protect.GetCheck() )
			setbit( m_doc->m_view->m_protected, CFreePcbDoc::PROTECT_ARCHIVED );
		else
			clrbit( m_doc->m_view->m_protected, CFreePcbDoc::PROTECT_ARCHIVED );
		//
		if( m_import_protect.GetCheck() )
			setbit( m_doc->m_view->m_protected, CFreePcbDoc::AUTOPROTECT_NETLIST );
		else
			clrbit( m_doc->m_view->m_protected, CFreePcbDoc::AUTOPROTECT_NETLIST );
		//
		if( m_en.GetCheck() && CheckTxtMsg() == CFreePcbDoc::PROTECT )
			Protect(0);
		else if( m_dis.GetCheck() && CheckTxtMsg() == CFreePcbDoc::NO_PROTECT )
			Protect(1);
		m_doc->SaveOptions();
		m_doc->m_view->SetFKText( m_doc->m_view->m_cursor_mode );
		m_doc->ProjectModified( FALSE );
	}
	else
	{
		m_en.SetCheck(0);
		m_dis.SetCheck(0);
		m_en_NL.SetCheck(0);
		m_dis_NL.SetCheck(0);
		int ch = CheckTxtMsg();
		if( ch == 0 )
		{
			CString new_folder = m_doc->m_path_to_folder + freeasy_netlist;
			new_folder.Truncate( new_folder.GetLength()-1 );
			_mkdir( new_folder );
			new_folder += "\\" + m_doc->m_name + ".fpc.txt";
			CStdioFile f;
			if( f.Open( new_folder, CFile::modeCreate | CFile::modeWrite ) )
				f.Close();
			ch = CheckTxtMsg();
		}
		if( ch == 0 )
		{
			AfxMessageBox("There is no synchronization with the netlist of the compatible editor \"Schematic Constructor\"", MB_ICONWARNING );
			pDX->Fail();
		}
		else if( ch == CFreePcbDoc::PROTECT )
			m_dis.SetCheck(1);
		else if( ch == CFreePcbDoc::NO_PROTECT )
			m_en.SetCheck(1);
		m_gerber_gen_protect.SetCheck(0);
		m_arch_pres_protect.SetCheck(0);
		m_import_protect.SetCheck(0);
		if( getbit( m_doc->m_view->m_protected, CFreePcbDoc::PROTECT_ON_GERBER ) )
			m_gerber_gen_protect.SetCheck(1);
		if( getbit( m_doc->m_view->m_protected, CFreePcbDoc::PROTECT_ARCHIVED ) )
			m_arch_pres_protect.SetCheck(1);
		if( getbit( m_doc->m_view->m_protected, CFreePcbDoc::AUTOPROTECT_NETLIST ) )
			m_import_protect.SetCheck(1);
		//
		if( m_doc->m_netlist_completed )
			m_dis_NL.SetCheck(1);
		else
			m_en_NL.SetCheck(1);
	}
}

void CDlgProtection::Ini( CFreePcbDoc * doc )
{
	m_doc = doc;
}

BEGIN_MESSAGE_MAP(CDlgProtection, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDlgProtection::OnBnClickedCancel)
END_MESSAGE_MAP()


void CDlgProtection::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnOK();
}

int CDlgProtection::CheckTxtMsg()
{
	CString s = m_doc->m_path_to_folder + freeasy_netlist + m_doc->m_name + ".fpc.txt";
	CStdioFile F;
	int ok = F.Open( s, CFile::modeRead, NULL );
	if( ok )
	{
		F.ReadString( s );
		if( s.GetLength() == 0 )
			return CFreePcbDoc::NO_PROTECT;
		else if( s.Compare( FILE_PROTECTED ) == 0 )
			return CFreePcbDoc::PROTECT;
		F.Close();
	}
	else
		return 0;
	AfxMessageBox( s, MB_ICONERROR );
	return 0;
}

BOOL CDlgProtection::Protect( int protect )
{
	CString s = m_doc->m_path_to_folder + freeasy_netlist + m_doc->m_name + ".fpc.txt";
	CStdioFile F;
	int ok = F.Open( s, CFile::modeCreate | CFile::modeWrite );
	if( ok )
	{
		if( protect )
			F.WriteString( FILE_PROTECTED );
		else
			F.WriteString( "" );
		F.Close();
		return 1;
	}
	return 0;
}

void CDlgProtection::ExtProtection( int protect )
{
	if( protect == 0 && CheckTxtMsg() == CFreePcbDoc::PROTECT )
	{
		if( Protect( protect ) )
			clrbit( m_doc->m_view->m_protected, CFreePcbDoc::PROTECT );
	}
	else if( protect && CheckTxtMsg() == CFreePcbDoc::NO_PROTECT )
	{
		if( Protect( protect ) )
			setbit( m_doc->m_view->m_protected, CFreePcbDoc::PROTECT );
	}
	m_doc->m_view->SetFKText( m_doc->m_view->m_cursor_mode );
	m_doc->ProjectModified( FALSE );
}

BOOL CDlgProtection::FindArchive()
{
	CFileFind finder;
	if( _chdir( m_doc->m_path_to_folder ) == 0 )
	{
		CString EXT[10] = { "*.zip","*.7z","*.rar","*.tar","*.gz","*.nop","*.nop","*.nop","*.nop","*.nop" };
		BOOL bWorking = 0;
		for ( int i=0; (bWorking==0&&i<10); i++ )
		{
			bWorking = finder.FindFile( EXT[i] );
			while( bWorking )
			{
				bWorking = finder.FindNextFile();
				if( !finder.IsDirectory() && !finder.IsDots() )
				{
					CString fn = finder.GetFileName();
					//if( fn.Find( "(" + m_doc->m_name + ")" ) > 0 )
						return 1; // ok
				}
			}
		}
	}
	return 0;
}