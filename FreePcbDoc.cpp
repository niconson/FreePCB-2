// FreePcbDoc.cpp : implementation of the CFreePcbDoc class
//
#pragma once
#include "stdafx.h"
#include "PcbFont.h"
#include "DlgAddPart.h"
#include "DlgEditNet.h"
#include "DlgAssignNet.h"
#include "DlgNetlist.h"
#include "DlgProjectOptions.h"
#include "DlgImportOptions.h" 
#include "freepcbdoc.h"
#include "DlgLayers.h"
#include "DlgPartlist.h"
#include "DlgIvex.h"
#include "DlgViaGrig.h"
#include "DlgIndexing.h"
#include "DlgEnterStr.h"
#include "UndoBuffer.h"
#include "UndoList.h"
#include "DlgCAD.h"
#include "DlgWizQuad.h"
#include "utility.h"
#include "gerber.h"
#include "dlgdrc.h"
#include "DlgGroupPaste.h"
#include "DlgReassignLayers.h"
#include "DlgExportDsn.h"
#include "DlgImportSes.h"
#include "RTcall.h"
#include "DlgReport.h"
#include "DlgNetCombine.h"
#include "DlgMyMessageBox.h"
#include "DlgSaveLib.h"
#include "DlgPDFColors.h"
#include "DlgProtection.h"
#include "RectArray.h"
#include "SpeedFiles.h"
#include "AddSymmetricalBlank.h"
#include "Additional.h"

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CFreePcbApp theApp;

CFreePcbDoc * this_Doc;		// global for callback

BOOL m_bShowMessageForClearance = TRUE;

/////////////////////////////////////////////////////////////////////////////
// CFreePcbDoc

IMPLEMENT_DYNCREATE(CFreePcbDoc, CDocument)

BEGIN_MESSAGE_MAP(CFreePcbDoc, CDocument)
	//{{AFX_MSG_MAP(CFreePcbDoc)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_VERSION, OnFileSaveVersion)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_ADD_PART, OnAddPart)
	ON_COMMAND(ID_NONE_ADDPART, OnAddPart)
	ON_COMMAND(ID_VIEW_NETLIST, OnProjectNetlist)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_VIEW_LAYERS, OnViewLayers)
	ON_COMMAND(ID_VIEW_PARTLIST, OnProjectPartlist)
	ON_COMMAND(ID_PART_PROPERTIES, OnPartProperties)
	ON_COMMAND(ID_FILE_IMPORTNETLIST, OnFileImportNetlist)
	ON_COMMAND(ID_FILE_RELOADNETLIST, OnFileReloadNetlist)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_FILE_CONVERT, OnFileConvert)
	ON_COMMAND(ID_FILE_GENERATECADFILES, OnFileGenerateCadFiles)
	ON_COMMAND(ID_TOOLS_FOOTPRINTWIZARD, OnToolsFootprintwizard)
	ON_COMMAND(ID_PROJECT_OPTIONS, OnProjectOptions)
	ON_COMMAND(ID_FILE_EXPORTNETLIST, OnFileExport)
	ON_COMMAND(ID_TOOLS_CHECK_PARTS_NETS, OnToolsCheckPartsAndNets)
	ON_COMMAND(ID_TOOLS_DRC, OnToolsDrc)
	ON_COMMAND(ID_TOOLS_CLEAR_DRC, OnToolsClearDrc)
	ON_COMMAND(ID_TOOLS_SHOWDRCERRORLIST, OnToolsShowDRCErrorlist)
	ON_COMMAND(ID_TOOLS_CHECK_CONNECTIVITY, OnToolsCheckConnectivity)
	ON_COMMAND(ID_VIEW_LOG, OnViewLog)
	ON_COMMAND(ID_TOOLS_CHECKCOPPERAREAS, OnToolsCheckCopperAreas)
	ON_COMMAND(ID_TOOLS_CHECKTRACES, OnToolsCheckTraces)
	ON_COMMAND(ID_EDIT_PASTEFROMFILE, OnEditPasteFromFile)
	ON_COMMAND(ID_SELECTALL, OnEditSelectAll)
	ON_COMMAND(ID_FILE_PRINT, OnFilePrint)
	ON_COMMAND(ID_FILE_CAM1, OnFileCam1)
	ON_COMMAND(ID_FILE_CAM2, OnFileCam2)
	ON_COMMAND(ID_FILE_CAM3, OnFileCam3)
	ON_COMMAND(ID_FILE_CAM4, OnFileCam4)
	ON_COMMAND(ID_FILE_CAM5, OnFileCam5)
	ON_COMMAND(ID_FILE_CAM6, OnFileCam6)
	ON_COMMAND(ID_FILE_CAM7, OnFileCam7)
	ON_COMMAND(ID_FILE_CAM8, OnFileCam8)
	ON_COMMAND(ID_FILE_CAM9, OnFileCam9)
	ON_COMMAND(ID_FILE_CAM10, OnFileCam10)
	ON_COMMAND(ID_FILE_CAM11, OnFileCam11)
	ON_COMMAND(ID_FILE_CAM12, OnFileCam12)
	ON_COMMAND(ID_FILE_CAM13, OnFileCam13)
	ON_COMMAND(ID_FILE_CAM14, OnFileCam14)
	ON_COMMAND(ID_FILE_CAM15, OnFileCam15)
	ON_COMMAND(ID_FILE_CAM16, OnFileCam16)
	ON_COMMAND(ID_FILE_CAM17, OnFileCam17)
	ON_COMMAND(ID_FILE_CAM18, OnFileCam18)
	ON_COMMAND(ID_FILE_CAM19, OnFileCam19)
	ON_COMMAND(ID_FILE_CAM20, OnFileCam20)
	ON_COMMAND(ID_FILE_CAM21, OnFileCam21)
	ON_COMMAND(ID_DSN_FILE_EXPORT, OnFileExportDsn)
	ON_COMMAND(ID_SES_FILE_IMPORT, OnFileImportSes)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_COMMAND(ID_NONE_REPEATDRC, OnRepeatDrc)
	ON_COMMAND(ID_TOOLS_REPEATDRC, OnRepeatDrc)
	ON_COMMAND(ID_FILE_GENERATEREPORTFILE, OnFileGenerateReportFile)
	ON_COMMAND(ID_FILE_GENERATE_3D, OnFileGenerate3DFile)
	ON_COMMAND(ID_PROJECT_COMBINENETS, OnProjectCombineNets)
	ON_COMMAND(ID_PROJECT_COMBINEBOARD, OnProjectCombineBoard)
	ON_COMMAND(ID_FILE_LOADLIBRARYASPROJECT, OnFileLoadLibrary)
	ON_COMMAND(ID_FILE_SAVEPROJECTASLIBRARY, OnFileSaveLibrary)
	ON_COMMAND(ID_SWITCH_TO_ECDS, SwitchTo__ECDS)
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_ADD_VIAS_GRID, AddViaGrid)
	ON_COMMAND(ID_ADD_SYMMETRICAL_BLANK, AddSymmetricalBlank)
	ON_COMMAND(ID_CHANNEL_DUPLICATION, ChannelDuplication)
	ON_COMMAND(ID_PROTECTION, OnProtection)
	ON_COMMAND(ID_IMAGE1, OnAddTopImage)
	ON_COMMAND(ID_IMAGE2, OnAddBottomImage)
	ON_COMMAND(ID_IMAGE1DEL, OnDeleteTopImage)
	ON_COMMAND(ID_IMAGE2DEL, OnDeleteBottomImage)
	ON_COMMAND(ID_INVERTCOLORS, OnInvertColors)
	ON_COMMAND(ID_SWAPIMAGES, OnSwapImages)
	ON_COMMAND(ID_FILE_SEL_FOLDER, OnSelectProjectFolder)
	ON_COMMAND(ID_FILE_RELOAD_MENU, OnReloadMenu)
	ON_COMMAND_EX_RANGE(ID_FILE_OPEN_FROM_START,ID_FILE_OPEN_FROM_END, OnSpeedFile)
	ON_COMMAND_EX_RANGE(ID_FILE_GENERATEDXFFILE1, ID_FILE_GENERATEDXFFILE8, OnFileGenerateDXFFile)
	ON_COMMAND_EX_RANGE(ID_FILE_GENERATEGRBLFILE1, ID_FILE_GENERATEGRBLFILE6, OnFileGenerateGRBLFile)
	ON_COMMAND_EX_RANGE(ID_FILE_GENERATEHPGLFILE1, ID_FILE_GENERATEHPGLFILE16, OnFileGenerateHPGLFile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFreePcbDoc construction/destruction

CFreePcbDoc::CFreePcbDoc()
{
	// get application directory
	// (there must be a better way to do this!!!)
	int token_start = 0;
	CString delim = " ";
	CString cmdline = GetCommandLine();
	if( cmdline[0] == '\"' )
	{
		delim = "\"";
		token_start = 1;
	}
	CString app_dir = cmdline.Tokenize( delim, token_start );
	int pos = app_dir.ReverseFind( '\\' );
	if( pos == -1 )
		pos = app_dir.ReverseFind( ':' ); 
	if( pos == -1 )
		ASSERT(0);	// failed to find application folder
	app_dir = app_dir.Left( pos );
	m_app_dir = app_dir;
	m_app_dir.Trim();
	int err = _chdir( m_app_dir );	// change to application folder
	if( err )
		ASSERT(0);	// failed to switch to application folder

	m_smfontutil = new SMFontUtil( &m_app_dir );// CFreePcbDoc()
	/*m_pcbu_per_wu = 25400;	// default nm per world unit
	DWORD dwVersion = ::GetVersion();
	DWORD dwWindowsMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
	if( dwWindowsMajorVersion > 4 )
		m_pcbu_per_wu = _2540;		// if Win2000 or XP or vista*/
	m_dlist = new CDisplayList();// CFreePcbDoc()
	m_dlist_fp = new CDisplayList();// CFreePcbDoc()
	m_plist = new CPartList( m_dlist, m_smfontutil );// CFreePcbDoc()
	m_nlist = new CNetList( m_dlist, m_plist );// CFreePcbDoc()
	m_mlist = new Merge();// CFreePcbDoc()
	m_plist->UseNetList( m_nlist );
	m_plist->SetShapeCacheMap( &m_footprint_cache_map );
	m_tlist = new CTextList( m_dlist, m_smfontutil );// CFreePcbDoc()
	m_drelist = new DRErrorList;// CFreePcbDoc()
	m_drelist->SetLists( m_plist, m_nlist, m_dlist, m_tlist, &m_outline_poly );
	for(int i=0; i<NUM_CAM_FOLDERS; i++)
		CAM[i] = "";
	m_pcb_filename = "";
	m_pcb_full_path = "";
	m_cds_filename = "";
	m_png_settings = "800 0.05";
	for( int ii=0; ii<NUM_SHORTCUTS; ii++ )
		m_cam_shortcut[ii] = "";
	m_full_lib_dir = "";
	m_outline_poly.RemoveAll();
	m_project_open = FALSE;
	m_project_modified = FALSE;
	m_project_modified_since_autosave = FALSE;
	m_footprint_modified = FALSE;
	m_footprint_name_changed = FALSE;
	theApp.m_Doc = this;
	m_undo_list = new CUndoList( 9999, 35 );// CFreePcbDoc()
	m_redo_list = new CUndoList( 9999, 35 );// CFreePcbDoc()
	this_Doc = this;
	m_auto_interval = 0;
	m_auto_elapsed = 0;
	m_dlg_log = NULL;
	bNoFilesOpened = TRUE;
	// VERSION (key)
	m_version = 2.427;
	m_file_version = m_version;
	m_dlg_log = new CDlgLog;// CFreePcbDoc()
	m_dlg_log->Create( IDD_LOG );
	m_import_flags = IMPORT_PARTS | IMPORT_NETS | KEEP_FP_PACKAGE_MATCH | REM_NOT_NL_NETS | REM_PRES_PART_NETS | KEEP_TRACES | KEEP_STUBS | KEEP_AREAS;

	// initialize pseudo-clipboard
	clip_plist = new CPartList( NULL, m_smfontutil );// CFreePcbDoc()
	clip_nlist = new CNetList( NULL, clip_plist );// CFreePcbDoc()
	clip_plist->UseNetList( clip_nlist );// 
	clip_plist->SetShapeCacheMap( &m_footprint_cache_map );// 
	clip_tlist = new CTextList( NULL, m_smfontutil );// CFreePcbDoc()
	clip_mlist = new Merge();// CFreePcbDoc()
	//
	m_i_b = 0;
	m_system_colors = TRUE;
	m_pdf_pin1 = 0.8;
	m_pdf_use_font1 = 500000; // default
	m_pdf_use_font2 = 500000; // default
	m_pdf_use_font3 = 500000;
	m_netlist_completed = 0;
	//
	// is protected?
	DWORD attr = GetFileAttributesA((LPCSTR) m_app_dir);
	if (attr != FILE_ATTRIBUTE_DIRECTORY )
    {
		//AfxMessageBox( "You installed FreePcb-2 in a protected folder, so the application will not work correctly. Remove the read-only attribute to continue." );
		//SetFileAttributesW((LPCWSTR)(&m_app_dir), FILE_ATTRIBUTE_DIRECTORY);
	}
	// m_crop_data, data for trim polygons
	m_crop_data.RemoveAll();
}

CFreePcbDoc::~CFreePcbDoc()
{
	ClearSpeedFiles( this );
	// delete group clipboard
	delete clip_nlist;
	delete clip_plist;
	delete clip_tlist;
	delete clip_mlist;
	m_outline_poly.RemoveAll();
	clip_outline_poly.RemoveAll();
	// delete partlist, netlist, displaylist, etc.
	delete m_drelist;
	delete m_undo_list;
	delete m_redo_list;
	delete m_nlist;
	delete m_plist;
	delete m_tlist;
	delete m_dlist;
	delete m_mlist;
	delete m_dlist_fp;
	delete m_smfontutil;
	// delete all footprints from local cache
	POSITION pos = m_footprint_cache_map.GetStartPosition();
	while( pos != NULL )
	{
		void * ptr;
		CShape * shape;
		CString string;
		m_footprint_cache_map.GetNextAssoc( pos, string, ptr );
		shape = (CShape*)ptr;
		delete shape;
	}
	m_footprint_cache_map.RemoveAll();
	// delete log window
	if( m_dlg_log )
	{
		m_dlg_log->DestroyWindow();
		delete m_dlg_log;
	}
}

void CFreePcbDoc::SendInitialUpdate()
{
	CDocument::SendInitialUpdate();
}

// this is only executed once, at beginning of app
//
BOOL CFreePcbDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_window_title = (G_LANGUAGE==0?"no project open":"редактор печатных плат");
	m_parent_folder = "..\\projects\\";
	m_lib_dir = "..\\lib\\" ;
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFreePcbDoc serialization

void CFreePcbDoc::Serialize(CArchive& ar)
{
}

/////////////////////////////////////////////////////////////////////////////
// CFreePcbDoc diagnostics

#ifdef _DEBUG
void CFreePcbDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFreePcbDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFreePcbDoc commands


BOOL CFreePcbDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	return CDocument::OnSaveDocument(lpszPathName);
}

void CFreePcbDoc::OnFileNew()
{
	if( theApp.m_view_mode == CFreePcbApp::FOOTPRINT )
	{
		theApp.m_View_fp->OnFootprintFileNew();
		return;
	}

	if( FileClose() == IDCANCEL )
		return;

	m_view->CancelSelection();

	// now set default project options
	InitializeNewProject();
	CDlgProjectOptions dlg;
	dlg.Init( TRUE, &m_name, &m_parent_folder, &m_full_lib_dir, &m_app_dir,
		m_num_copper_layers, m_bSMT_copper_connect, m_view->m_merge_show, m_default_glue_w,
		m_trace_w, m_via_w, m_via_hole_w,
		60, m_auto_ratline_disable, m_auto_ratline_min_pins,
		&m_w, &m_v_w, &m_v_h_w );
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		// set up project file name and path
		m_get_app_folder = m_app_dir;
		m_name = dlg.GetName();
		m_pcb_filename = m_name + ".fpc";
		CString fullpath;
		char full[_MAX_PATH];
		fullpath = _fullpath( full, (LPCSTR)dlg.GetPathToFolder(), MAX_PATH );
		m_path_to_folder = (CString)fullpath;

		// Check if project folder exists and create it if necessary
		struct _stat buf;
		int err = _stat( m_path_to_folder, &buf );
		if( err )
		{
			CString str;
			str.Format(G_LANGUAGE == 0 ? 
				"Folder \"%s\" doesn't exist, create it?":
				"Папка \"%s\" не существует, создать ее?", m_path_to_folder);
			int ret = AfxMessageBox( str, MB_YESNO );
			if( ret == IDYES )
			{
				err = _mkdir( m_path_to_folder );
				if( err )
				{
					str.Format(G_LANGUAGE == 0 ? "Unable to create folder \"%s\"":"Невозможно создать папку \"%s\"", m_path_to_folder);
					AfxMessageBox( str, MB_OK );
				}
			}
		}
		if( err )
			return;
		m_netlist_completed = 0;
		CString str;
		m_pcb_full_path = (CString)fullpath	+ "\\" + m_pcb_filename;
		m_window_title = PROGRAM_CAP + m_pcb_filename;
		CWnd* pMain = AfxGetMainWnd();
		if (pMain != NULL)
		{
			pMain->SetWindowText( m_window_title );
			CMenu* pMenu = pMain->GetMenu();
			CMainFrame * pMainWnd = (CMainFrame*)pMain;
			pMainWnd->EnableMenuItems(pMenu);
			pMain->DrawMenuBar();
		}

		// make path to library folder and index libraries
		m_lib_dir = dlg.GetLibFolder();
		fullpath = _fullpath( full, (LPCSTR)m_lib_dir, MAX_PATH );
		if( fullpath[fullpath.GetLength()-1] == '\\' )	
			fullpath = fullpath.Left(fullpath.GetLength()-1);
		m_full_lib_dir = fullpath;
		MakeLibraryMaps( &m_full_lib_dir );

		// set options from dialog
		m_auto_ratline_disable = dlg.GetAutoRatlineDisable();
		m_auto_ratline_min_pins = dlg.GetAutoRatlineMinPins();
		m_num_copper_layers = dlg.GetNumCopperLayers();
		m_plist->SetNumCopperLayers( m_num_copper_layers );
		m_nlist->SetNumCopperLayers( m_num_copper_layers );
		//
		m_view->m_merge_show = dlg.m_bShow_merges;
		m_bSMT_copper_connect = dlg.m_bSMT_connect_copper;		
		m_nlist->SetSMTconnect( m_bSMT_copper_connect );
		//
		m_num_layers = m_num_copper_layers + LAY_TOP_COPPER;
		m_trace_w = dlg.GetTraceWidth();
		m_via_w = dlg.GetViaWidth();
		m_via_hole_w = dlg.GetViaHoleWidth();
		m_nlist->SetWidths( abs(m_trace_w), abs(m_via_w), abs(m_via_hole_w) );
		for( int i=0; i<m_num_layers; i++ )
		{
			m_vis[i] = 1;
			m_dlist->SetLayerRGB( i, m_rgb[i][0], m_rgb[i][1], m_rgb[i][2] );
		}

		CRect screen_r;
		m_view->GetWindowRect( &screen_r );
		m_view->GetClientRect( &m_view->m_client_r );
		m_dlist->SetMapping( &m_view->m_client_r, 
							 &screen_r, 
							 m_view->m_left_pane_w, 
							 m_view->m_bottom_pane_h, 
							 m_view->m_pcbu_per_pixel, 
							 m_view->m_org_x, 
						     m_view->m_org_y );

		// force redraw of left pane
		m_view->InvalidateLeftPane();
		m_view->Invalidate( FALSE );
		m_project_open = TRUE;

		// force redraw of function key text
		m_view->m_cursor_mode = 999;
		m_view->SetCursorMode( CUR_NONE_SELECTED );

		// force redraw of window title
		ProjectModified(FALSE);
		m_project_modified_since_autosave = FALSE;
		m_auto_elapsed = 0;
		m_view->m_sel_mask = ~0;
		// save project
		OnFileSave();
		SaveOptions();
	}
}

CString CFreePcbDoc::RunFileDialog( BOOL bMODE, CString format )
{
#define BUFSIZE	_2540/10
	format = format.MakeLower();
	const int size = 32;
	const int MAX_ITERATORS = 200;
	HANDLE cmd = GlobalAlloc(GMEM_FIXED,size);
	if( bMODE )
	{	// reading
		if( format.Find("fp") >= 0 )
			memcpy( cmd, "fpc_imp", size );
		else if( format.Find("pas") >= 0 )
			memcpy( cmd, "grp_imp", size );
		else if( format.Find("ses") >= 0 )
			memcpy( cmd, "ses_imp", size );
		else if( format.Find("net") >= 0 )
			memcpy( cmd, "net_imp", size );
		else if( format.Find("mod") >= 0 || format.Find("txt") >= 0 )
			memcpy( cmd, "mod_imp", size );
		else if( format.Find("img") >= 0 )
			memcpy( cmd, "pic_imp", size );
		else return "";
	}
	else
	{	// saving
		if( format.Find("fpc") >= 0 )
			memcpy( cmd, "fpc_exp", size );
		else if( format.Find("sav") >= 0 )
			memcpy( cmd, "grp_exp", size );
		else if( format.Find("dsn") >= 0 )
			memcpy( cmd, "dsn_exp", size );
		else if( format.Find("net") >= 0 )
			memcpy( cmd, "net_exp", size );
		else if( format.Find("fpl") >= 0 )
			memcpy( cmd, "fpl_exp", size );
		else return "";
	}
	HWND WND = theApp.GetMainWnd()->GetSafeHwnd();
	do Sleep(100);  
		while(!OpenClipboard(WND));
	EmptyClipboard();
	SetClipboardData(CF_TEXT,cmd);
	CloseClipboard();
	CString command_str = m_app_dir + "\\VCL_Dialog\\VCL_Dialogs.exe";
	CString Path = "";// empty (default)
	char buffer[(int)BUFSIZE];
	int ret = GetFullPathName( command_str, BUFSIZE, buffer, NULL );
	if (ret)
	{
		HWND dlg = FindWindow(NULL,"File dialog");
		if( dlg )
		{
			AfxMessageBox(G_LANGUAGE == 0 ? "File dialog already running!":"Диалоговое окно «Файл» уже запущено!");
			return Path;
		}
		if ( (UINT)ShellExecute(	NULL,"open",command_str, NULL,buffer,SW_SHOWNORMAL) > 32 )
		{
			for( int i=0; FindWindow(NULL,"File dialog") == NULL && i<MAX_ITERATORS; i++ ){Sleep(100);}
			dlg = FindWindow(NULL,"File dialog");
			if(dlg)
			{
				//ShowWindow(WND,SW_HIDE);
				for( int st=0; dlg; st++ )
				{
					ret=0;
					Sleep(200);
					dlg = FindWindow(NULL,"Infobox");
					if( dlg )
					{
						COPYDATASTRUCT cd;
						cd.cbData = 1;
						cd.lpData = '\0';
						SendMessage( dlg, WM_COPYDATA,0, (LPARAM)&cd );
					}
					dlg = FindWindow(NULL,"File dialog");	
					if( dlg )
					{
						COPYDATASTRUCT cd;
						cd.cbData = 1;
						cd.lpData = '\0';
						SendMessage( dlg, WM_COPYDATA,0, (LPARAM)&cd );
						BringWindowToTop( dlg );
						UpdateWindow(WND);
						{
							MSG msg;
							PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
							if (msg.message)
							{
								TranslateMessage(&msg);
								DispatchMessage(&msg);
							}
						}
					}
				}
				//ShowWindow(WND,SW_SHOW);
			}
			Sleep(200);
			SetForegroundWindow(WND);
			UpdateWindow(WND);
			if( m_view )
				m_view->Invalidate(false);
			if( !ret )
			{		
				CStdioFile pth;
				for( int ITERATOR=0; pth.Open( m_app_dir+"\\VCL_Dialog\\file_dialog.pth", CFile::modeReadWrite, NULL ) == 0; ITERATOR++ )
				{
					Sleep(50);
					if( ITERATOR > 50 )
					{
						AfxMessageBox(G_LANGUAGE == 0 ? 
							"Unable to open global configuration file \"file_dialog.pth\"\nYou installed this program in a protected folder, so the application will not work correctly. Remove the read-only attribute to continue.":
							"Невозможно открыть глобальный файл конфигурации «file_dialog.pth». Вы, вероятно, установили эту программу в защищенную папку, поэтому приложение не будет работать правильно. Снимите атрибут «только для чтения», чтобы продолжить.");
						return Path;
					}
				}
				pth.ReadString( Path );
				pth.Close();
			}
			else
				AfxMessageBox(G_LANGUAGE == 0 ? "File dialog is not connected!":"Диалоговое окно выбора файлов не подключено!");
		}
	}
#undef BUFSIZE


	//CFileDialog dlg( bMODE );
	//dlg.UpdateOFNFromShellDialog();
	//dlg.m_ofn.lpstrTitle = "New Dialog Title";
	//dlg.m_ofn.
	//dlg.ApplyOFNToShellDialog();
	//dlg.DoModal();
	//Path = dlg.GetFileName();



	return Path;
}

void CFreePcbDoc::OnFileOpen()
{
	if( theApp.m_view_mode == CFreePcbApp::FOOTPRINT )
	{
		theApp.m_View_fp->OnFootprintFileImport();
		return;
	}

	if( FileClose() == IDCANCEL )
		return;

	m_view->CancelSelection();
	InitializeNewProject();		// set defaults
	//
	CString filename = RunFileDialog( 1, "fpc" ); 
	if ( filename.GetLength() )
	{
		CString pathname = filename.Left( filename.ReverseFind('\\') );
		BOOL bLIB = 1;
		if( filename.GetLength() < 4 )
			bLIB = 0;
		else if( filename.Right(4) != ".fpl" )
			bLIB = 0;
		//
		if( bLIB )
		{
			CString mess = "You are opening a file with extension \".fpl\"\n";
			mess += "which is usually a FreePCB footprint library.\n\n";
			mess += "Would you like to load this library as a project?";
			if (G_LANGUAGE)
			{
				mess = "Вы открываете файл с расширением \".fpl\"\n";
				mess += "который хранит библиотеку футпринтов.\n\n";
				mess += "Хотите его открыть как проект ПлатФорм?";
			}
			int ret = AfxMessageBox( mess, MB_YESNOCANCEL );
			if( ret == IDCANCEL )
				return;
			else if( ret == IDYES )
				FileLoadLibrary( filename );
		}
		else
		{
			// read project file
			FileOpen( filename );
		}
	}
}

void CFreePcbDoc::OnFileAutoOpen( LPCTSTR fn )
{
	CString pathname = fn;
	if( pathname.GetLength() < 4 )
		FileOpen( fn );
	else if( pathname.Right(4).MakeLower() != ".fpl" )
		FileOpen( fn );
	else 
	{
		CString mess = "You are opening a file with extension \".fpl\"\n";
		mess += "which is usually a FreePCB footprint library.\n\n";
		mess += "Would you like to load this library as a project?";
		if (G_LANGUAGE)
		{
			mess = "Вы открываете файл с расширением \".fpl\"\n";
			mess += "который хранит библиотеку футпринтов.\n\n";
			mess += "Хотите его открыть как проект ПлатФорм?";
		}
		int ret = AfxMessageBox( mess, MB_YESNOCANCEL );
		if( ret == IDCANCEL )
			return;
		else if( ret == IDYES )
		{
			FileLoadLibrary( fn );
			return;
		}
		else
			FileOpen( fn );
			return;
	}	
}

// open project file, fn = full path to file
// if bLibrary = true, open library file and read footprints
// return TRUE if success
//
BOOL CFreePcbDoc::FileOpen( LPCTSTR fn, BOOL bLibrary )
{
	// if another file open, offer to save before closing
	if( FileClose() == IDCANCEL )
		return FALSE;		// file close cancelled
	
	// reset before opening new project
	m_view->CancelSelection();
	InitializeNewProject();		// set defaults


	// now open it
	CStdioFile pcb_file;
	int err = pcb_file.Open( fn, CFile::modeRead, NULL );
	if( !err )
	{
		// error opening project file
		CString mess;
		mess.Format(G_LANGUAGE == 0 ? "Unable to open file %s":"Невозможно открыть файл %s", fn);
		AfxMessageBox( mess );
		return FALSE;
	}
	try
	{
		int m_org_changed = 0;
		if( !bLibrary )
		{
			//
			// read project from file
			CString key_str;
			CString in_str;
			CArray<CString> p;
			int u = m_units;
			CMainFrame * pMain = (CMainFrame*) AfxGetApp()->m_pMainWnd;
			if( !pMain ) 
			{
				pcb_file.Close();
				return FALSE;
			}
			CString str;

			// read footprints

			str.Format( "Reading footprints");
			pMain->DrawStatus( 3, &str );
			m_org_changed = ReadOptions( &pcb_file, !m_system_colors );
			m_plist->SetPinAnnularRing( m_annular_ring_pins );
			m_nlist->SetViaAnnularRing( m_annular_ring_vias );
			ReadFootprints( &pcb_file );
			UpdateWindow((HWND)m_view->GetActiveWindow());
			// check file version
			if( m_file_version < 1.3 )
			{
				pcb_file.Close();
				if(G_LANGUAGE==0)
					AfxMessageBox("File version too old. Try to save your file to FreePcb-1.3xx and then try again");
				else
					AfxMessageBox("Версия файла очень старая. Не поддерживается");
				return FALSE;
			}
			if( m_file_version > m_version )
			{
				CString mess;
				mess.Format( "Warning: the file version is %5.3f\n\nYou are running an earlier program version %5.3f", 
					m_file_version, m_version );
				mess += "\n\nErrors may occur\n\nClick on OK to continue reading or CANCEL to cancel";
				if (G_LANGUAGE)
				{
					mess.Format("Внимание: версия файла %5.3f\nВы используете более раннюю версию программы %5.3f. ",
						m_file_version, m_version);
					mess += "Могут возникнуть ошибки. Нажмите «ОК», чтобы продолжить чтение, или «ОТМЕНА», чтобы отменить.";
				}
				int ret = AfxMessageBox( mess, MB_OKCANCEL );
				if( ret == IDCANCEL )
				{
					pcb_file.Close();
					CString * err_str = new CString( "Reading project file failed: Cancelled by user" );//throw
					throw err_str;
				}
			}
			m_nlist->m_dis_hatch = ((m_vis[LAY_BOTTOM_COPPER] && m_view->m_active_layer==LAY_SM_TOP) ||
									(m_vis[LAY_TOP_COPPER] && m_view->m_active_layer==LAY_SM_BOTTOM));
			m_mlist->max_number = -1;
			// read BoardOutline
			str.Format( "Reading board outline");
			pMain->DrawStatus( 3, &str );
			ReadBoardOutline( &pcb_file );
			UpdateWindow((HWND)m_view->GetActiveWindow());
			// read solder mask cutouts
			str.Format( "Reading solder mask cutouts");
			pMain->DrawStatus( 3, &str );
			ReadSolderMaskCutouts( &pcb_file );
			UpdateWindow((HWND)m_view->GetActiveWindow());
			// read graphics
			str.Format( "Reading graphics");
			pMain->DrawStatus( 3, &str );
			ReadGraphics( &pcb_file );
			UpdateWindow((HWND)m_view->GetActiveWindow());
			// read Parts
			str.Format( "Reading parts");
			pMain->DrawStatus( 3, &str );
			int num_m = m_plist->ReadParts( &pcb_file );
			m_mlist->max_number = max( m_mlist->max_number, num_m );
			UpdateWindow((HWND)m_view->GetActiveWindow());
			// read Nets
			str.Format( "Reading nets");
			pMain->DrawStatus( 3, &str );
			num_m = m_nlist->ReadNets( &pcb_file, m_file_version );
			///m_mlist->max_number = max( m_mlist->max_number, num_m );
			UpdateWindow((HWND)m_view->GetActiveWindow());
			// read Texts
			str.Format( "Reading texts");
			pMain->DrawStatus( 3, &str );
			m_tlist->ReadTexts( &pcb_file, m_file_version );

			// read Merges
			str.Format( "Reading merges");
			pMain->DrawStatus( 3, &str );
			m_mlist->Clear();
			ReadMerges( &pcb_file, m_mlist );

			str.Format( "Complete");
			pMain->DrawStatus( 3, &str );

			// make path to library folder and index libraries
			struct _stat buf;
			int err = _stat(m_full_lib_dir, &buf);
			if (err)
			{
				int isep = m_app_dir.ReverseFind('\\');
				if (isep == -1)
					isep = m_app_dir.ReverseFind(':');
				if (isep == -1)
					ASSERT(0);		// unable to parse filename
				CString app = m_app_dir.Left(isep + 1);
				m_full_lib_dir = app + "fp_lib\\lib";
			}
			MakeLibraryMaps( &m_full_lib_dir );
		}
		else
		{
			// read library as project
			ReadFootprints( &pcb_file, NULL, FALSE );
		}
		pcb_file.Close();
		//
		m_pcb_full_path = fn;
		int fpl = m_pcb_full_path.GetLength();
		int isep = m_pcb_full_path.ReverseFind( '\\' );
		if( isep == -1 )
			isep = m_pcb_full_path.ReverseFind( ':' );
		if( isep == -1 )
			ASSERT(0);		// unable to parse filename
		m_pcb_filename = m_pcb_full_path.Right( fpl - isep - 1);
		int fnl = m_pcb_filename.GetLength();
		m_path_to_folder = m_pcb_full_path.Left( m_pcb_full_path.GetLength() - fnl - 1 );
		m_window_title = PROGRAM_CAP + m_pcb_filename;
		CWnd* pMain = AfxGetMainWnd();
		//

		// check backgnd image
		CString img = m_path_to_folder + "\\related_files\\pictures\\" + m_pcb_filename + "1";
		struct _stat buf;
		int pic1 = _stat( img, &buf );//ok
		if( pic1 == 0 )	
			m_dlist->Images.Load( &img, 0 );
		img = m_path_to_folder + "\\related_files\\pictures\\" + m_pcb_filename + "2";
		int pic2 = _stat( img, &buf );//ok
		if( pic2 == 0 )	
			m_dlist->Images.Load( &img,	1 );
		if( pic1==0 || pic2==0 )
			m_dlist->Images.UpdateBoardOutline();
		//
		//
		m_name = m_pcb_filename;
		if( m_name.Right(4).MakeLower() == ".fpc" )
			m_name = m_name.Left( m_name.GetLength() - 4 );
		//
		if( m_get_app_folder.Compare( m_app_dir ) )
		{
			CString path = m_app_dir + "\\Backups";
			struct _stat buf;
			int err = _stat( path+"\\"+m_pcb_filename, &buf );
			if( err == 0 )
			{
				int ret = AfxMessageBox(G_LANGUAGE == 0 ? 
					"This project has been changed in another version of the program. To restore a project that was edited in the current version of the program, open the BackUps folder. This folder contains the most recent versions of files. Open this folder?":
					"Этот проект был изменен с помощью другого исполняемого файла программы (другой exe-файл, запущенный из другого места). Чтобы восстановить проект, отредактированный именно в текущей версии программы, откройте папку BackUps. Эта папка содержит самые последние версии файлов. Открыть эту папку?", MB_OKCANCEL);
				if( ret == IDOK )
				{
					ShellExecute(	NULL,"open",path,NULL,path,SW_SHOWNORMAL);
				}
			}
		}
		//
		int bRELOAD = ReadMessageFromSchematic( &m_pcb_full_path );
		//
		m_project_open = TRUE;
		theApp.AddMRUFile( &m_pcb_full_path );
		// now set layer visibility
		for( int i=0; i<m_num_layers; i++ )
		{
			m_dlist->SetLayerRGB( i, m_rgb[i][0], m_rgb[i][1], m_rgb[i][2] );
			m_dlist->SetLayerVisible( i, m_vis[i] );
		}
		//
		if (pMain != NULL)
		{
			CMenu* pMenu = pMain->GetMenu();
			CMainFrame * pMainWnd = (CMainFrame*)pMain;
			pMainWnd->EnableMenuItems(pMenu);
			pMain->DrawMenuBar();
		}
		// force redraw of function key text
		m_view->m_cursor_mode = 999;
		m_view->SetCursorMode( CUR_NONE_SELECTED );
		m_view->ShowActiveLayer(m_num_copper_layers);
		if( m_view->m_merge_show )
			m_view->ShowMerges();
		m_view->InvalidateLeftPane();
		ProjectModified( FALSE );

		// set mapping
		if( m_org_changed )
		{
			CRect screen_r;
			m_view->GetWindowRect( &screen_r );
			m_view->GetClientRect( &m_view->m_client_r );
			//
			//m_view->m_client_r.right = screen_r.right-screen_r.left;
			//m_view->m_client_r.bottom = screen_r.bottom-screen_r.top;
			m_dlist->SetMapping( &m_view->m_client_r, 
								 &screen_r, 
								 m_view->m_left_pane_w, 
								 m_view->m_bottom_pane_h, 
								 m_view->m_pcbu_per_pixel, 
								 m_view->m_org_x, 
							     m_view->m_org_y );
		}
		else
		{
			m_view->OnViewAllElements();
		}
		m_auto_elapsed = 0;
		CDC * pDC = m_view->GetDC();
		m_view->OnDraw( pDC );
		m_view->ReleaseDC( pDC );
		m_view->Invalidate( FALSE );
		//m_plist->CheckForProblemFootprints();
		GetGerberPathes(fn);
		bNoFilesOpened = FALSE;
		if (pMain != NULL)
			pMain->SetWindowText( m_window_title );
		if( bRELOAD == 2 )
			OnFileReloadNetlist();
		return TRUE;
	}
	catch( CString * err_str )
	{
		// parsing error
		AfxMessageBox( *err_str );
		delete err_str;
		CDC * pDC = m_view->GetDC();
		m_view->OnDraw( pDC );
		m_view->ReleaseDC( pDC );
	}
	return FALSE;
}

void CFreePcbDoc::OnFileClose()
{
	FileClose();
}

// return IDCANCEL if closing cancelled by user
//
int CFreePcbDoc::FileClose()
{
	if( m_project_open )
	{
		if( m_get_app_folder.Compare( m_app_dir ) == 0 )
		{
			CString BackUps = m_app_dir + "\\Backups";
			FileSave( &BackUps, &m_pcb_filename, NULL, NULL, FALSE );
		}
		int ret = 0;
		if( m_project_modified )
		{
			ret = AfxMessageBox(G_LANGUAGE == 0 ? 
				"Project modified, save it ?":
				"Проект изменен, сохранить его?", MB_YESNOCANCEL);
			if( ret == IDCANCEL )
				return IDCANCEL;
			else if( ret == IDYES )
				OnFileSave();
		}
		///if( ret != IDYES )
		{
			CStdioFile fmess;
			CString file_p = m_pcb_full_path;
			int ifo = m_pcb_full_path.ReverseFind('\\');
			CString name = file_p.Right( file_p.GetLength() - ifo - 1 );
			file_p = file_p.Left(ifo) + freeasy_netlist + name + ".txt";
			int ok = fmess.Open( file_p, CFile::modeRead, NULL );
			if( ok )
			{
				CString in_str;
				fmess.ReadString( in_str );
				fmess.Close();
				if( in_str.GetLength() )
				{
					if( in_str.Left(in_str.GetLength()) == NETLIST_WARNING )
					{
						// Here it is necessary 
						// to change the text of 
						// the message in order to 
						// save this warning when 
						// saving the file
						ok = fmess.Open( LPCSTR(file_p), CFile::modeCreate | CFile::modeWrite, NULL );
						if( ok )
						{
							fmess.WriteString(NETLIST_UPDATED);// only NETLIST_UPDATED text !!!
							fmess.Close();
						}
					}
				}
				else if( getbit( m_view->m_protected, PROTECT_ARCHIVED ) )
				{
					CDlgProtection dlg;
					dlg.Ini( this );
					if( dlg.FindArchive() )
						dlg.ExtProtection( TRUE );
				}
			}
		}
		m_dlist->Images.Clear();
	}
	m_view->CancelSelection();

	// destroy existing project
	// delete undo list, partlist, netlist, displaylist, etc.
	m_outline_poly.RemoveAll();
	m_drelist->Clear();
	ResetUndoState();
	m_nlist->RemoveAllNets();
	m_plist->RemoveAllParts();
	m_tlist->RemoveAllTexts();
	m_dlist->RemoveAll();
	m_mlist->Clear();

	// clear clipboard
	ClipClear();

	// delete all shapes from local cache
	POSITION pos = m_footprint_cache_map.GetStartPosition();
	while( pos != NULL )
	{
		void * ptr;
		CShape * shape;
		CString string;
		m_footprint_cache_map.GetNextAssoc( pos, string, ptr );
		shape = (CShape*)ptr;
		delete shape;
	}
	m_footprint_cache_map.RemoveAll();
	CWnd* pMain = AfxGetMainWnd();
	if (pMain != NULL)
	{
		GetGerberPathes("");
		CMenu* pMenu = pMain->GetMenu();
		CMainFrame * pMainWnd = (CMainFrame*)pMain;
		pMainWnd->DisableMenuItems(pMenu);
		pMain->DrawMenuBar();
	}
	m_view->Invalidate( FALSE );
	m_project_open = FALSE;
	ProjectModified( FALSE );
	m_auto_elapsed = 0;
	// force redraw
	m_view->m_cursor_mode = 999;
	m_view->SetCursorMode( CUR_NONE_SELECTED );
	m_window_title = (CString)PROGRAM_CAP + (G_LANGUAGE == 0 ? "no project open" : "редактор печатных плат");
	pMain->SetWindowText( m_window_title );
	CDC * pDC = m_view->GetDC();
	m_view->OnDraw( pDC );
	m_view->ReleaseDC( pDC );
	bNoFilesOpened = TRUE;
	return IDOK;
}

void CFreePcbDoc::OnFileSaveBeforeImport()
{
	if( !FileSave( &m_path_to_folder, &m_pcb_filename, &m_path_to_folder, &m_pcb_filename, FALSE ) )
	{
		AfxMessageBox(G_LANGUAGE == 0 ? "Unable to save file. Remove write protection":"Невозможно сохранить файл. Снимите защиту от записи");
	}
	else
		m_import_flags &= ~SAVE_BEFORE_IMPORT;
}

void CFreePcbDoc::OnFileSave() 
{
	if( theApp.m_view_mode == CFreePcbApp::FOOTPRINT )
	{
		theApp.m_View_fp->OnFootprintFileSaveAs();
		return;
	}
	if( m_file_version < 2.0 )
	{
		if(G_LANGUAGE==0)
			AfxMessageBox("This project file was created in the previous version of FREEPCB. Use the SAVE AS menu item to avoid overwriting the file and to be able to open it with the old version of the program in the future.");
		else 
			AfxMessageBox("Этот проект был создан в предыдущей версии ПлатФорм. Используйте меню СОХРАНИТЬ_КАК чтобы создать копию данного файла и сохранить его в текущей версии программы.");
		return;
	}
	// clear clipboard
	ClipClear();

	PurgeFootprintCache();
	m_view->m_seg_clearance = m_dr.trace_trace + _2540*2;
	if( !FileSave( &m_path_to_folder, &m_pcb_filename, &m_path_to_folder, &m_pcb_filename ) )
	{
		AfxMessageBox(G_LANGUAGE == 0 ? "Unable to save file. Remove write protection." : "Невозможно сохранить файл. Снимите защиту от записи");
	}
	ProjectModified( FALSE );
	ResetUndoState();
	bNoFilesOpened = FALSE;
}

// Autosave
//
BOOL CFreePcbDoc::AutoSave()
{
	CString str;
	CString auto_folder = m_app_dir + "\\Autosave";
	struct _stat s;
	int err = _stat( auto_folder, &s );
	if( err )
	{
		if( err )
		{
			err = _mkdir( auto_folder );
			if( err )
			{
				m_project_modified_since_autosave = 0;
				str.Format(G_LANGUAGE == 0 ? "Unable to create autosave folder \"%s\"":"Не удалось создать папку автосохранения \"%s\"", auto_folder);
				AfxMessageBox( str, MB_OK );
				return FALSE;
			}
		}
	}
	CFileFind finder;
	CString list_str = "";
	CTime time;
	time_t bin_time;
	time_t max_time = 0;
	int max_suffix = 0;
	if( _chdir( auto_folder ) != 0 )
	{
		m_project_modified_since_autosave = 0;
		CString mess;
		mess.Format(G_LANGUAGE == 0 ? "Unable to open autosave folder \"%s\"":"Невозможно открыть папку автосохранения \"%s\"", auto_folder);
		AfxMessageBox( mess );
	}
	else
	{
		CString first_f = "\\??.fpc";
		CString search_str = auto_folder + first_f;
		BOOL bWorking = finder.FindFile( search_str );
		if( !bWorking )
		{
			first_f = "01.fpc";
			FileSave( &auto_folder, &first_f, NULL, NULL, FALSE );
		}
		else while (bWorking)
		{
			bWorking = finder.FindNextFile();
			CString fn = finder.GetFileName();
			if( !finder.IsDirectory() )
			{
				// found a file
				int suffix = atoi( fn.Left(2) );
				finder.GetLastWriteTime( time );
				bin_time = time.GetTime();
				if( bin_time > max_time )
				{
					max_time = bin_time;
					max_suffix = suffix;
				}
			}
		}
	}
	if( max_suffix )
	{
		CString new_file_name;
		int new_suffix = max_suffix%25 + 1;
		if( new_suffix < 10 )
			new_file_name.Format( "0%d.fpc", new_suffix );
		else
			new_file_name.Format( "%d.fpc", new_suffix );
		FileSave( &auto_folder, &new_file_name, NULL, NULL, FALSE );
		m_project_modified_since_autosave = FALSE;		
	}
	finder.Close();
	return TRUE;
}

// save project file
// make backup if the new file has the same path and filename as the old file
// returns TRUE if successful, FALSE if fails
//
BOOL CFreePcbDoc::FileSave( CString * folder, CString * filename, 
						   CString * old_folder, CString * old_filename,
						   BOOL bBackup ) 
{
	if( !m_project_open )
		return FALSE;

	// write project file
	CString full_path = *folder;
	CString full_path_b = *folder + "\\related_files";
	struct _stat buf;
	int err = _stat( full_path_b, &buf );
	if( bBackup )
	{
		if( err )
		{
			CString str;
			err = _mkdir( full_path_b );
			if( err )
			{
				str.Format(G_LANGUAGE == 0 ? "Unable to create folder \"%s\"" : "Невозможно создать папку \"%s\"", full_path_b );
				AfxMessageBox( str, MB_OK );
				old_folder = NULL;
			}
		}

		// check for imported netlist
		CStdioFile m_file;
		CString messg = *folder + freeasy_netlist + *filename + ".txt";
		err = m_file.Open( LPCSTR(messg), CFile::modeRead );
		if( err )
		{
			CString instr;
			m_file.ReadString(instr);
			m_file.Close();
			if( instr.Left(instr.GetLength()) == NETLIST_WARNING )
			{
				err = m_file.Open( LPCSTR(messg), CFile::modeCreate | CFile::modeWrite, NULL );
				if( err )
				{
					m_file.Close();
					CString rnmb = messg.Left(messg.GetLength()-3) + "rnmb";
					DeleteFile(rnmb);
				}
			}
		}

		// create IB folder
		CString path_infobox = full_path_b + "\\infobox";
		err = _stat( path_infobox, &buf );
		if( err )
		{
			CString str;
			err = _mkdir( path_infobox );
			if( err )
			{
				str.Format(G_LANGUAGE == 0 ? "Unable to create folder \"%s\"":"Невозможно создать папку \"%s\"", path_infobox );
				AfxMessageBox( str, MB_OK );
			}
		}
		//
		CString full_path_n = full_path_b + "\\PCB_netlist";
		full_path_b += "\\backup";
		err = _stat( full_path_b, &buf );
		if( err )
		{
			CString str;
			err = _mkdir( full_path_b );
			if( err )
			{
				str.Format(G_LANGUAGE == 0 ? "Unable to create folder \"%s\"":"Невозможно создать папку \"%s\"", full_path_b );
				AfxMessageBox( str, MB_OK );
				old_folder = NULL;
			}
		}
		// netlist
		err = _stat( full_path_n, &buf );
		if( err )
		{
			CString str;
			err = _mkdir( full_path_n );
			if( err )
			{
				str.Format(G_LANGUAGE == 0 ? "Unable to create folder \"%s\"":"Невозможно создать папку \"%s\"", full_path_n );
				AfxMessageBox( str, MB_OK );
				old_folder = NULL;
			}
		}
		CString backup = full_path_b + "\\" + *filename + ".b";
		// see if we need to make a backup file
		if( old_folder != NULL && old_filename != NULL )
		{
			if( bBackup && *folder == *old_folder && *filename == *old_filename )
			{
				// rename file
				remove( backup );
				CopyFile( full_path + "\\" + *filename, backup, 1 );
			}
		}
		FileExport( full_path_n + "\\" + *filename + ".net" );
		theApp.AddMRUFile( &m_pcb_full_path );
	}
	full_path = full_path + "\\" + *filename;
	CStdioFile pcb_file;
	err = pcb_file.Open( LPCSTR(full_path), CFile::modeCreate | CFile::modeWrite, NULL );
	if( !err )
	{
		// error opening file
		return FALSE;
	}
	else
	{
		// write project to file
		try
		{
			WriteOptions( &pcb_file, 0 );
			WriteFootprints( &pcb_file );
			WriteOutlinesPoly( &pcb_file );
			m_plist->WriteParts( &pcb_file );
			m_nlist->WriteNets( &pcb_file );
			m_tlist->WriteTexts( &pcb_file );
			WriteMerges( &pcb_file, m_mlist );
			pcb_file.WriteString( "[end]\n" );
			pcb_file.Close();
			bNoFilesOpened = FALSE;
			m_auto_elapsed = 0;

			// Save Pcb View for Schemator
			if (bBackup)
			{
				AddBoardHoles(); // valid
				MarkLegalElementsForExport(this);
				SavePcbView(this);
				CancelBoardHoles();
				ProjectModified(FALSE);
			}
		}
		catch( CString * err_str )
		{
			// error
			AfxMessageBox( *err_str );
			delete err_str;
			CDC * pDC = m_view->GetDC();
			m_view->OnDraw( pDC ) ;
			m_view->ReleaseDC( pDC );
			return FALSE;
		}
	}
	return TRUE;
}


void CFreePcbDoc::ReadMerges( CStdioFile * pcb_file, Merge * merge_list )
{
	int  err;
	CString in_str, key_str;
	CArray<CString> p;
	// find beginning of [parts] section
	do
	{
		err = pcb_file->ReadString( in_str );
		if( !err )
		{
			// error reading pcb file
			if (G_LANGUAGE == 0)
				AfxMessageBox("This project file was created in the previous version of FREEPCB.");
			else 
				AfxMessageBox("Этот проект был создан в предыдущей версии ПлатФорм.");
			break;
		}
		in_str.Trim();
	}
	while( in_str != "[merges]" );
	if(err)
	{
		merge_list->Clear();
		do
		{
			err = pcb_file->ReadString( in_str );
			if( !err )
			{
				// error reading pcb file
				CString mess;
				mess.Format(G_LANGUAGE == 0 ? "Unable to find [end] section in file":"Не удалось найти [end] раздел в файле");
				AfxMessageBox( mess );
				return;
			}
			in_str.Trim();
			int np = ParseKeyString( &in_str, &key_str, &p );
			if( np >= 2 )
			{
				if( key_str.Left(5) == "merge" )
				{
					int clrn = 0;
					if( np >= 3 )
						clrn = atoi(p[1]);
					if( merge_list->GetSize() <= merge_list->max_number )
						merge_list->AddNew(p[0],clrn);
				}
			}			
		}
		while( in_str != "[end]" );
	}
}

void CFreePcbDoc::WriteMerges( CStdioFile * pcb_file, Merge * merge_list )
{
	CMapStringToPtr shape_map;
	CString line;
	CString key;
	try
	{  
		// now write all parts
		line.Format( "[merges]\n\n" );
		pcb_file->WriteString( line );
		for( int ml=0; ml<merge_list->GetSize(); ml++ )
		{
			// test
			CString str;
			CString test = merge_list->GetMerge(ml);
			str.Format( "  merge: \"%s\" %d\n", test, merge_list->GetClearance(ml) );
			pcb_file->WriteString( str );
		}
		pcb_file->WriteString( "\n" );
	}
	catch( CFileException * e )
	{
		CString str;
		if( e->m_lOsError == -1 )
			str.Format( "File error: %d\n", e->m_cause );
		else
			str.Format( "File error: %d %ld (%s)\n", e->m_cause, e->m_lOsError,
			_sys_errlist[e->m_lOsError] );
	}
}

void CFreePcbDoc::OnFileSaveVersion()
{
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	CString s;
	s.Format( "%s(%d-%02d-%02d-%02d-%02d-%02d).fpc", m_name, timeinfo->tm_year+1900, timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec );
	if( FileSave( &m_path_to_folder, &s, NULL, NULL, FALSE ) )
	{
		AfxMessageBox(G_LANGUAGE == 0 ? "File saved successfully":"Файл успешно сохранен");
		ShellExecute(	NULL, "open", m_path_to_folder, NULL, NULL, SW_SHOWNORMAL);
	}
}

void CFreePcbDoc::OnFileSaveAs() 
{
	// force old-style file dialog by setting size of OPENFILENAME struct
	CWnd * WND = theApp.GetMainWnd();
	CString filename = RunFileDialog( 0, "fpc" ); 
	if ( filename.GetLength() )
	{
		if( filename.Right(3).MakeLower() != "fpc" )
		{
			CString S = filename;
			filename.Format( "%s.fpc", S );
		}
		// get new filename and folder
		CString new_pathname = filename;
		CString new_folder = filename.Left( filename.ReverseFind('\\') );
		int nfl = new_folder.GetLength();
		CString new_filename = filename.Right( filename.GetLength()-nfl-1 );
		// write project file
		BOOL ok = FileSave( &new_folder, &new_filename, &m_path_to_folder, &m_pcb_filename );
		if( ok )
		{
			// update member variables, MRU files and window title
			m_pcb_filename = new_filename;
			m_pcb_full_path = new_pathname;
			m_path_to_folder = new_folder;
			theApp.AddMRUFile( &m_pcb_full_path );
			m_window_title = PROGRAM_CAP + m_pcb_filename;
			CWnd* pMain = AfxGetMainWnd();
			pMain->SetWindowText( m_window_title );
			ProjectModified( FALSE );
		}
		else
		{
			AfxMessageBox(G_LANGUAGE == 0 ? "File save failed":"Сохранение файла не удалось");
		}
	}
}

void CFreePcbDoc::OnAddPart()
{
	enum{
		UTILITY = 2
	};
	// invoke dialog
	CDlgAddPart dlg;
	partlist_info pl;
	m_plist->ExportPartListInfo( &pl, NULL );
	dlg.Initialize( &pl, -1, TRUE, TRUE, FALSE, 0, m_netlist_completed, &m_footprint_cache_map, 
		&m_footlibfoldermap, m_units, m_dlg_log, &m_part_search );
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		// select new part, and start dragging it if requested
		m_full_lib_dir = *m_footlibfoldermap.GetDefaultFolder();
		cpart * find = NULL;
		CString nRef;
		m_view->m_Doc->m_plist->MarkAllParts(0);
		BOOL bNEW_EVENT = TRUE;
		do
		{
			find = NULL;
			for( int ipl=pl.GetSize()-1; ipl>=0; ipl-- )
			{	
				if( pl[ipl].part == NULL )
					continue;
				if( pl[ipl].part->utility == UTILITY )
					continue;
				if( pl[ipl].ref_des.Compare( pl[ipl].part->ref_des ) )
				{
					find = pl[ipl].part;
					nRef = pl[ipl].ref_des;
					// test on ref match 
					CString find_str = pl[ipl].ref_des;
					cpart * gP;
					BOOL REP;
					do{
						gP = m_view->m_Doc->m_plist->GetPart( find_str );

						//break if null
						if( !gP )
							break;

						//break if repeat
						if( gP->utility == UTILITY )
							break;
						
						REP = 0;
						for( int f=pl.GetSize()-1; f>=0; f-- )
						{
							if( pl[f].part == NULL )
								continue;
							if( pl[f].part->utility == UTILITY )
								continue;
							if( gP->ref_des.Compare( pl[f].part->ref_des ) == 0 )
							{
								find_str = pl[f].ref_des;
								find = gP;
								nRef = find_str;
								REP = TRUE;
								break;
							}
						}
					}while( REP );
					// end test
					break;
				}	
			}
			if( find )
			{
				if( m_netlist_completed )
				{
					CString str = " Warning, netlist is protected. Procedure aborted...";
					CDlgMyMessageBox dlg;
					dlg.Initialize( str );
					dlg.DoModal();
					m_view->g_bShow_nl_lock_Warning = !dlg.bDontShowBoxState;
					return;
				}
				id pid( ID_PART, ID_SEL_RECT, 0, 0, 0 );
				m_view->NewSelect( find, &pid,0,0 );
				m_view->SaveUndoInfoForPart( find, CPartList::UNDO_PART_MODIFY, &nRef, bNEW_EVENT, m_undo_list );
				find->utility = UTILITY;
			}
		}while( find ); 
		//test
		int n_parts = pl.GetSize();
		CString S1 = pl[n_parts-1].ref_des;
		S1 = S1.MakeLower();
		CString S2 = pl[n_parts-1].ref_des;
		S2 = S2.MakeUpper();
		if( m_plist->GetPart( S1 ) || m_plist->GetPart( S2 ) )
		{
			AfxMessageBox(G_LANGUAGE == 0 ? 
				"A bad tone in the design of printed circuit boards, when the designations of parts differ only in the case of letters (Uppercase/Lowercase). It is recommended to rename, otherwise there will be problems with external applications.":
				"Дурной тон в дизайне печатных плат, когда обозначения деталей отличаются только регистром букв (Заглавные/Строчные). Рекомендуется переименовать, иначе будут проблемы с внешними приложениями.");
		}
		m_plist->ImportPartListInfo( &pl, 0 );
		cpart * part = m_plist->GetPart( pl[n_parts-1].ref_des );
		ProjectModified( TRUE );
		m_view->SaveUndoInfoForPart( part, CPartList::UNDO_PART_ADD, &part->ref_des, TRUE, m_undo_list );
		if( pl[n_parts-1].part )
			if( pl[n_parts-1].ref_des.Compare( pl[n_parts-1].part->ref_des ) )
				m_view->SaveUndoInfoForPart( part, CPartList::UNDO_PART_MODIFY, &nRef, 1, m_undo_list );
		m_view->SelectPart( part );
		id ID(ID_PART,ID_SEL_RECT,0,0,0);
		m_view->NewSelect( part, &ID, 1, 0 );
		if( m_view->m_sel_part->shape )
			m_view->m_sel_part->shape->m_package = dlg.m_package;
		//
		if( dlg.GetDragFlag() )
		{
			m_view->m_dragging_new_item = TRUE;
			m_view->OnPartMove();
		}
	}
}

void CFreePcbDoc::OnProjectNetlist()
{
	CFreePcbView * view = (CFreePcbView*)m_view;
	CDlgNetlist dlg;
	dlg.Initialize( m_nlist, m_plist, &m_w, &m_v_w, &m_v_h_w, m_units, (m_netlist_completed+(2*getbit(m_view->m_protected,PROTECT))) );
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		ResetUndoState();
		view->CancelSelection();
		ProjectModified( TRUE );
		if( getbit(m_view->m_protected,PROTECT) == 0 )
			m_netlist_completed = dlg.m_nl_comp;
		m_nlist->ImportNetListInfo( dlg.m_nl, 0, NULL, m_trace_w, m_via_w, m_via_hole_w );
		//
		//
		if( m_vis[LAY_RAT_LINE] && !m_auto_ratline_disable )
			m_nlist->OptimizeConnections();
		view->SetMainMenu( TRUE );
		for( int h=0; h<dlg.m_selected.GetSize(); h++ )
		{
			cnet * hnet = m_nlist->GetNetPtrByName( &dlg.m_selected.GetAt(h) );
			if( hnet )
			{
				m_nlist->HighlightNet( hnet );
				m_nlist->HighlightNetConnections( hnet );
				m_plist->HighlightAllPadsOnNet( hnet, 0, 0 );
				if( m_view )
				{
					m_view->m_sel_net = hnet;
					m_view->m_sel_id = hnet->id;
					m_view->m_sel_id.type = ID_NET;
					m_view->m_sel_id.st = ID_ENTIRE_NET;
					m_view->SetCursorMode( CUR_NET_SELECTED );
					m_view->HighlightGroup();
				}
			}
		}
		view->SetDrawLayer( ENABLE_CHANGE_DRAW_LAYER );
		view->Invalidate( FALSE );
	}
}

// write footprint info from local cache to file
//
int CFreePcbDoc::WriteFootprints( CStdioFile * file, CMapStringToPtr * cache_map, BOOL wFOOTPRINTS )
{
	CMapStringToPtr * use_map = cache_map;
	if( use_map == NULL )
		use_map = &m_footprint_cache_map;

	void * ptr;
	CShape * s;
	POSITION pos;
	CString key;
	if( wFOOTPRINTS )
		file->WriteString( "[footprints]\n\n" );
	for( pos = use_map->GetStartPosition(); pos != NULL; )
	{
		use_map->GetNextAssoc( pos, key, ptr );
		s = (CShape*)ptr;
		s->WriteFootprint( file );
	}
	return 0;
}

// get shape from cache
// if necessary, make shape from library file and put into cache first
// returns NULL if shape not found
//
CShape * CFreePcbDoc::GetFootprintPtr( CString name )
{
	// lookup shape, first in cache
	void * ptr;
	CShape * sh = NULL;
	int err = m_footprint_cache_map.Lookup( name, ptr );
	if( err )
	{
		// found in cache
		sh = (CShape*)ptr;
		if( sh )
			if( sh->m_package.Compare("ERROR") )
				return sh; 
	}
	{
		// not in cache, lookup in library file
		int ilib;
		CString file_name;
		int offset;
		CString * project_lib_folder_str;
		project_lib_folder_str = m_footlibfoldermap.GetDefaultFolder();
		CFootLibFolder * project_footlibfolder = m_footlibfoldermap.GetFolder( project_lib_folder_str, m_dlg_log );
		BOOL ok = project_footlibfolder->GetFootprintInfo( &name, NULL, &ilib, NULL, &file_name, &offset );
		if( !ok )
		{
			// unable to find shape, return NULL
			return sh;
		}
		else
		{
			// make shape from library file and put into cache
			CShape * shape;
			if( sh == NULL )
				shape = new CShape;//ok
			else
				shape = sh;
			CString lib_name = *project_footlibfolder->GetFullPath();
			err = shape->MakeFromFile( NULL, name, file_name, offset ); 
			if( err )
			{
				// failed
				CString mess;
				mess.Format(G_LANGUAGE == 0 ? "Unable to make shape %s from file":"Невозможно создать форму %s из файла", name);
				AfxMessageBox( mess );
				delete shape;
				return NULL;
			}
			else
			{
				// success, put into cache and return pointer
				if( sh == NULL )
					m_footprint_cache_map.SetAt( name, shape );
				m_plist->FootprintChanged( shape );
				ProjectModified( TRUE );
				return shape;
			}
		}
	}
	return NULL;
}

// read shapes from file
//
void CFreePcbDoc::ReadFootprints( CStdioFile * pcb_file, 
								  CMapStringToPtr * cache_map,
								  BOOL bFindSection )
{
	// set up cache map to use
	CMapStringToPtr * use_map = cache_map;
	if( use_map == NULL )
		use_map = &m_footprint_cache_map;

	// find beginning of shapes section
	ULONGLONG pos;
	int err;
	CString key_str;
	CString in_str;
	CArray<CString> p;

	// delete all shapes from local cache
	POSITION mpos = use_map->GetStartPosition();
	while( mpos != NULL )
	{
		void * ptr;
		CShape * shape;
		CString string;
		use_map->GetNextAssoc( mpos, string, ptr );
		shape = (CShape*)ptr;
		delete shape;
	}
	use_map->RemoveAll();

	if( bFindSection )
	{
		// find beginning of shapes section
		do
		{
			err = pcb_file->ReadString( in_str );
			if( !err )
			{
				// error reading pcb file
				CString mess;
				mess.Format(G_LANGUAGE == 0 ? "Unable to find [footprints] section in file":"Не удалось найти раздел [footprints] в файле");
				AfxMessageBox( mess );
				return;
			}
			in_str.Trim();
		}
		while( in_str != "[shapes]" && in_str != "[footprints]" );
	}

	// get each shape and add it to the cache
	while( 1 )
	{
		pos = pcb_file->GetPosition();
		err = pcb_file->ReadString( in_str );
		if( !err )
		{
			if( bFindSection )
			{
				CString * err_str = new CString( "unexpected EOF in project file" );// throw
				throw err_str;
			}
			else
				break;
		}
		in_str.Trim();
		if( in_str.Left(1) == "[" )
		{
			pcb_file->Seek(pos,CFile::begin);
			break;		// next section, exit
		}
		else if( in_str.Left(5) == "name:" )
		{
			CString name = in_str.Right( in_str.GetLength()-5 );
			name = name.Trim();
			if( name.Right(1) == '\"' )
				name = name.Left( name.GetLength() - 1 );
			if( name.Left(1) == '\"' )
				name = name.Right( name.GetLength() - 1 );
			name = name.Left( CShape::MAX_NAME_SIZE );
			name = name.Trim();
			void * ptr;
			BOOL found = m_footprint_cache_map.Lookup( name, ptr );
			if( found == NULL )
			{
				CShape * s = new CShape;//ok
				pcb_file->Seek( pos, CFile::begin );	// back up
				err = s->MakeFromFile( pcb_file, "", "", 0 );
				if( !err )
					use_map->SetAt( name, s );
				else
					delete s;
			}
		}
	}
}

// write outline to file
//
// throws CString * exception on error
//

void CFreePcbDoc::WriteOutlinesPoly( CStdioFile * file, CArray<CPolyLine> * sm )
{
	CString line;
	CArray<CPolyLine> * smc = sm;
	if( sm == NULL )
		smc = &m_outline_poly;

	try
	{
		// board outlines
		line.Format( "[board]\n\n" );
		file->WriteString( line );
		for( int i=0; i<smc->GetSize(); i++ )
		{
			int l = (*smc)[i].GetLayer();
			if( l != LAY_BOARD_OUTLINE )
				continue;
			int ncr = (*smc)[i].GetNumCorners();
			if( ncr < 2 )
			{
				CPolyLine * pp = &smc->GetAt(i);
				pp->Undraw();
				smc->RemoveAt(i);
				OPRefreshID();
				i--;
				continue;
			}
			line.Format( "outline: %d %d %d %d %d %d\n", 
				ncr, i, (*smc)[i].GetW(), (*smc)[i].GetHatch(), (*smc)[i].GetMerge(), (*smc)[i].GetMerge(TRUE) );
			file->WriteString( line );
			for( int icor=0; icor<ncr; icor++ )
			{
				line.Format( "  corner: %d %d %d %d %d\n", icor+1,
					(*smc)[i].GetX( icor ),
					(*smc)[i].GetY( icor ),
					(*smc)[i].GetSideStyle( icor ),
					(*smc)[i].GetNumContour( icor )
					);
				file->WriteString( line );
			}
			file->WriteString( "\n" );
		}
		file->WriteString( "\n" );
		//
		// solder_mask_cutouts
		line.Format( "[solder_mask_cutouts]\n\n" );
		file->WriteString( line );
		for( int i=0; i<smc->GetSize(); i++ )
		{
			int l = (*smc)[i].GetLayer();
			if( l != LAY_SM_TOP && l != LAY_SM_BOTTOM )
				continue;
			int ncr = (*smc)[i].GetNumCorners();
			if( ncr < 2 )
			{
				CPolyLine * pp = &smc->GetAt(i);
				pp->Undraw();
				smc->RemoveAt(i);
				OPRefreshID();
				i--;
				continue;
			}
			line.Format( "sm_cutout: %d %d %d %d %d %d\n", 
				ncr, (*smc)[i].GetHatch(), (*smc)[i].GetLayer(), (*smc)[i].GetW(), (*smc)[i].GetMerge(), (*smc)[i].GetMerge(TRUE) );
			file->WriteString( line );
			for( int icor=0; icor<ncr; icor++ )
			{
				line.Format( "  corner: %d %d %d %d %d\n", icor+1,
					(*smc)[i].GetX( icor ),
					(*smc)[i].GetY( icor ),
					(*smc)[i].GetSideStyle( icor ),
					(*smc)[i].GetNumContour( icor )
					);
				file->WriteString( line );
			}
			file->WriteString( "\n" );
		}
		file->WriteString( "\n" );
		//
		// outlines
		line.Format( "[graphics]\n\n" );
		file->WriteString( line );
		for( int i=0; i<smc->GetSize(); i++ )
		{
			int l = (*smc)[i].GetLayer();
			int ncr = (*smc)[i].GetNumCorners();
			if( l <= LAY_BOARD_OUTLINE || l == LAY_SM_TOP || l == LAY_SM_BOTTOM )
				continue;
			if( ncr < 2 )
			{
				CPolyLine * pp = &smc->GetAt(i);
				pp->Undraw();
				smc->RemoveAt(i);
				OPRefreshID();
				i--;
				continue;
			}
			if( (*smc)[i].GetClosed() == 0 )
			{
				line.Format( "line: %d %d %d %d %d %d\n",  
					(*smc)[i].GetNumCorners(), (*smc)[i].GetHatch(), (*smc)[i].GetLayer(), (*smc)[i].GetW(), (*smc)[i].GetMerge(), (*smc)[i].GetMerge(TRUE) );
				file->WriteString( line );
				int end_cont = (*smc)[i].GetContourEnd(0);
				for( int icor=0; icor<=end_cont; icor++ )
				{
					line.Format( "  corner: %d %d %d %d\n", icor+1,
						(*smc)[i].GetX( icor ),
						(*smc)[i].GetY( icor ),
						(*smc)[i].GetSideStyle( min( icor,end_cont-1 ) )
						);
					file->WriteString( line );
				}
			}
			else
			{
				line.Format( "polyline: %d %d %d %d %d %d\n", 
					(*smc)[i].GetNumCorners(), (*smc)[i].GetHatch(), (*smc)[i].GetLayer(), (*smc)[i].GetW(), (*smc)[i].GetMerge(), (*smc)[i].GetMerge(TRUE) );
				file->WriteString( line );
				for( int icor=0; icor<ncr; icor++ )
				{
					line.Format( "  corner: %d %d %d %d %d\n", icor+1,
						(*smc)[i].GetX( icor ),
						(*smc)[i].GetY( icor ),
						(*smc)[i].GetSideStyle( icor ),
						(*smc)[i].GetNumContour( icor )
						);
					file->WriteString( line );
				}
			}
			file->WriteString( "\n" );
		}
		file->WriteString( "\n" );
	}
	catch( CFileException * e )
	{
		CString * err_str = new CString;//throw
		if( e->m_lOsError == -1 )
			err_str->Format( "File error: %d\n", e->m_cause );
		else
			err_str->Format( "File error: %d %ld (%s)\n", 
				e->m_cause, e->m_lOsError, _sys_errlist[e->m_lOsError] );
		*err_str = "CFreePcbDoc::WriteOutlinesPoly()\n" + *err_str;
		throw err_str;
	}
}

// read board outline from file
//
// throws CString * exception on error
//
void CFreePcbDoc::ReadBoardOutline( CStdioFile * pcb_file, CArray<CPolyLine> * bbd )
{
	int err, pos, np;
	CArray<CString> p;
	CString in_str, key_str;
	int last_side_style = CPolyLine::STRAIGHT;
	CArray<CPolyLine> * bd = bbd;
	if( bd == NULL )
		bd = &m_outline_poly;
	if( m_view )
		m_view->m_board_back = 0;
	try
	{
		// find beginning of [board] section
		do
		{
			err = pcb_file->ReadString( in_str );
			if( !err )
			{
				// error reading pcb file
				CString mess;
				mess.Format(G_LANGUAGE == 0 ? "Unable to find [board] section in file":"Не удалось найти раздел [board] в файле");
				AfxMessageBox( mess );
				return;
			}
			in_str.Trim();
		}
		while( in_str != "[board]" );

		// get data
		while( 1 )
		{
			pos = pcb_file->GetPosition();
			err = pcb_file->ReadString( in_str );
			if( !err )
			{
				CString * err_str = new CString( "unexpected EOF in project file" );//throw
				throw err_str;
			}
			in_str.Trim();
			if( in_str.Left(1) == "[" )
			{
				// normal return
				pcb_file->Seek(pos,CFile::begin);
				return;
			}
			np = ParseKeyString( &in_str, &key_str, &p );
			if( np && key_str == "outline" )
			{
				if( np < 2 )
				{
					CString * err_str = new CString( "error parsing [board] section of project file" );//throw
					throw err_str;
				}
				int ncorners = my_atoi( &p[0] );
				int ib = 0;
				if( np >= 3 )
					ib = my_atoi( &p[1] );
				int wid = 0;
				if ( np >= 4 )
					wid = my_atoi( &p[2] );
				if( wid <= 0 )
					wid = NM_PER_MIL*10;
				else
					wid = max( wid, NM_PER_MIL*2 );
				int hatch = CPolyLine::DIAGONAL_FULL;
				//if ( np >= 5 )
				//	hatch = my_atoi( &p[3] ); 
				if( m_view && hatch == CPolyLine::DIAGONAL_FULL )
					m_view->m_board_back = 1;
				int merge = -1;
				if ( np >= 6 )
					merge = my_atoi( &p[4] );
				int s_merge = -1;
				if ( np >= 7 )
					s_merge = my_atoi( &p[5] );
				///m_mlist->max_number = max( m_mlist->max_number, merge );
				///m_mlist->max_number = max( m_mlist->max_number, s_merge );
				int n_cont=0, last_n_cont=0, i_start=0;
				for( int icor=0; icor<ncorners; icor++ )
				{
					err = pcb_file->ReadString( in_str );
					if( !err )
					{
						CString * err_str = new CString( "unexpected EOF in project file" );//throw
						throw err_str;
					}
					np = ParseKeyString( &in_str, &key_str, &p );
					if( key_str != "corner" || np < 4 )
					{
						CString * err_str = new CString( "error parsing [board] section of project file" );//throw
						throw err_str;
					}

					// end contour
					if( np >= 6 )
						n_cont = my_atoi( &p[4] );
					else
						n_cont = 0;
					if( last_n_cont != n_cont && icor > i_start+2 )
					{
						(*bd)[ib].Close( last_side_style, 0 );
						i_start = icor;
					}
					int ncor = my_atoi( &p[0] );
					if( (ncor-1) != icor )
					{
						CString * err_str = new CString( "error parsing [board] section of project file" );//throw
						throw err_str;
					}
					int x = my_atoi( &p[1] );
					int y = my_atoi( &p[2] );
					if( icor == 0 )
					{
						// make new board outline
						bd->SetSize( ib + 1 );
						if( bbd )
							(*bd)[ib].SetDisplayList( NULL );
						else
							(*bd)[ib].SetDisplayList( m_dlist );
						id bid( ID_POLYLINE, ID_BOARD, ib );
						(*bd)[ib].Start( LAY_BOARD_OUTLINE, wid, 20*NM_PER_MIL, x, y, 
							hatch, &bid, NULL );
					}
					else
						(*bd)[ib].AppendCorner( x, y, last_side_style, FALSE );
					if( np >= 5 )
						last_side_style = my_atoi( &p[3] );
					else
						last_side_style = CPolyLine::STRAIGHT;
					last_n_cont = n_cont;
					if( icor == (ncorners-1) )
					{
						(*bd)[ib].Close( last_side_style );
						(*bd)[ib].SetMerge(merge);
						(*bd)[ib].SetMerge(s_merge,TRUE);
					}
				}
			}
		}
	}
	catch( CFileException * e )
	{
		CString * err_str = new CString;//throw
		if( e->m_lOsError == -1 )
			err_str->Format( "File error: %d\n", e->m_cause );
		else
			err_str->Format( "File error: %d %ld (%s)\n", 
				e->m_cause, e->m_lOsError, _sys_errlist[e->m_lOsError] );
		*err_str = "CFreePcbDoc::ReadBoardOutline()\n" + *err_str;
		throw err_str;
	}
}

// read solder mask cutouts from file
//
// throws CString * exception on error
//
void CFreePcbDoc::ReadSolderMaskCutouts( CStdioFile * pcb_file, CArray<CPolyLine> * ssm )
{
	int err, pos, np;
	CArray<CString> p;
	CString in_str, key_str;
	int last_side_style = CPolyLine::STRAIGHT;
	CArray<CPolyLine> * sm = ssm;
	if( sm == NULL )
		sm = &m_outline_poly;

	try
	{
		// find beginning of [solder_mask_cutouts] section
		int pos = pcb_file->GetPosition();
		do
		{
			err = pcb_file->ReadString( in_str );
			if( !err )
			{
				// error reading pcb file
				CString mess;
				mess.Format(G_LANGUAGE == 0 ? "Unable to find [solder_mask_cutouts] section in file":"Не удалось найти раздел [solder_mask_cutouts] в файле");
				AfxMessageBox( mess );
				return;
			}
			in_str.Trim();
		}
		while( in_str[0] != '[' );

		if( in_str != "[solder_mask_cutouts]" )
		{
			pcb_file->Seek(pos,CFile::begin);
			return;
		}

		// get data
		while( 1 )
		{
			pos = pcb_file->GetPosition();
			err = pcb_file->ReadString( in_str );
			if( !err )
			{
				CString * err_str = new CString( "unexpected EOF in project file" );//throw
				throw err_str;
			}
			in_str.Trim();
			if( in_str.Left(1) == "[" )
			{
				// normal return
				pcb_file->Seek( pos, CFile::begin );
				return;
			}
			np = ParseKeyString( &in_str, &key_str, &p );
			if( np && key_str == "sm_cutout" )
			{
				if( np < 4 ) 
				{
					CString * err_str = new CString( "error parsing [solder_mask_cutouts] section of project file" );//throw
					throw err_str;
				}
				int ncorners = my_atoi( &p[0] );
				int hatch = my_atoi( &p[1] );
				int lay = my_atoi( &p[2] );
				if( m_file_version < 2.0199 )
					lay += 3;
				int wid = 0;
				if ( np >= 5 )
					wid = my_atoi( &p[3] );
				int merge = -1;
				if ( np >= 6 )
					merge = my_atoi( &p[4] );
				int s_merge = -1;
				if ( np >= 7 )
					s_merge = my_atoi( &p[5] );
				///m_mlist->max_number = max( m_mlist->max_number, merge );
				///m_mlist->max_number = max( m_mlist->max_number, s_merge );
				int ic = sm->GetSize();
				sm->SetSize(ic+1);
				int n_cont=0, last_n_cont=0, i_start=0;
				for( int icor=0; icor<ncorners; icor++ )
				{
					err = pcb_file->ReadString( in_str );
					if( !err )
					{
						CString * err_str = new CString( "unexpected EOF in project file" );//throw
						throw err_str;
					}
					np = ParseKeyString( &in_str, &key_str, &p );
					if( key_str != "corner" || np < 4 )
					{
						CString * err_str = new CString( "error parsing [solder_mask_cutouts] section of project file" );//throw
						throw err_str;
					}
					// end contour
					if( np >= 6 )
						n_cont = my_atoi( &p[4] );
					else
						n_cont = 0;
					if( last_n_cont != n_cont && icor > i_start+2 )
					{
						(*sm)[ic].Close( last_side_style, 0 );
						i_start = icor;
					}
					//
					int ncor = my_atoi( &p[0] );
					if( (ncor-1) != icor )
					{
						CString * err_str = new CString( "error parsing [solder_mask_cutouts] section of project file" );//throw
						throw err_str;
					}

					int x = my_atoi( &p[1] );
					int y = my_atoi( &p[2] );
					id id_sm( ID_POLYLINE, ID_SM_CUTOUT, ic );
					if( icor == 0 )
					{
						// make new cutout 
						(*sm)[ic].Start( lay, wid, 20*NM_PER_MIL, x, y, hatch, &id_sm, NULL );
						if( ssm )
							(*sm)[ic].SetDisplayList( NULL );
						else
							(*sm)[ic].SetDisplayList( m_dlist );
					}
					else
						(*sm)[ic].AppendCorner( x, y, last_side_style, FALSE );
					if( np >= 5 )
						last_side_style = my_atoi( &p[3] );
					else
						last_side_style = CPolyLine::STRAIGHT;
					last_n_cont = n_cont;
					if( icor == (ncorners-1) )
					{
						(*sm)[ic].Close( last_side_style );
						(*sm)[ic].SetMerge(merge);
						(*sm)[ic].SetMerge(s_merge,TRUE);
					}
				}
			}
		}
	}
	catch( CFileException * e )
	{
		CString * err_str = new CString;//throw
		if( e->m_lOsError == -1 )
			err_str->Format( "File error: %d\n", e->m_cause );
		else
			err_str->Format( "File error: %d %ld (%s)\n", 
				e->m_cause, e->m_lOsError, _sys_errlist[e->m_lOsError] );
		*err_str = "CFreePcbDoc::ReadSolderMaskCutouts()\n" + *err_str;
		throw err_str;
	}
}

void CFreePcbDoc::ReadGraphics( CStdioFile * pcb_file, CArray<CPolyLine> * ssm )
{
	int err, pos, np;
	CArray<CString> p;
	CString in_str, key_str;
	int last_side_style = CPolyLine::STRAIGHT;
	CArray<CPolyLine> * op = ssm;
	if( op == NULL )
		op = &m_outline_poly;

	try
	{
		// find beginning of [outlines] section
		int pos = pcb_file->GetPosition();
		do
		{
			err = pcb_file->ReadString( in_str );
			if( !err )
			{
				// error reading pcb file
				CString mess;
				mess.Format(G_LANGUAGE == 0 ? "Unable to find [graphics] section in file":"Не удалось найти раздел [графика] в файле");
				AfxMessageBox( mess );
				return;
			}
			in_str.Trim();
		}
		while( in_str[0] != '[' );
		//
		if( in_str == "[parts]" )
		{
			pcb_file->Seek(pos,CFile::begin);
			return;
		}
		if( in_str != "[graphics]" )
		{
			pcb_file->Seek(pos,CFile::begin);
			return;
		}

		// get data
		while( 1 )
		{
			pos = pcb_file->GetPosition();
			err = pcb_file->ReadString( in_str );
			if( !err )
			{
				CString * err_str = new CString( "unexpected EOF in project file" );//throw
				throw err_str;
			}
			in_str.Trim();
			if( in_str.Left(1) == "[" )
			{
				// normal return
				pcb_file->Seek( pos, CFile::begin );
				return;
			}
			np = ParseKeyString( &in_str, &key_str, &p );
			if( np && (key_str == "line" || key_str == "polyline") )
			{
				if( np < 4 ) 
				{
					CString * err_str = new CString( "error parsing [graphics] section of project file" );//throw
					throw err_str;
				}
				int ncorners = my_atoi( &p[0] );
				int hatch = my_atoi( &p[1] );
				int lay = my_atoi( &p[2] );
				int clsd = 1;
				if( key_str == "line" )
					clsd = 0;
				if( m_file_version < 2.0199 )
					lay += 3;
				int wid = 0;
				if ( np >= 5 )
					wid = my_atoi( &p[3] );
				int merge = -1;
				if ( np >= 6 )
					merge = my_atoi( &p[4] );
				int s_merge = -1;
				if ( np >= 7 )
					s_merge = my_atoi( &p[5] );
				///m_mlist->max_number = max( m_mlist->max_number, merge );
				///m_mlist->max_number = max( m_mlist->max_number, s_merge );
				//
				int ic = op->GetSize();
				op->SetSize(ic+1);
				int n_cont=0, last_n_cont=0, i_start=0;
				for( int icor=0; icor<ncorners; icor++ )
				{
					err = pcb_file->ReadString( in_str );
					if( !err )
					{
						CString * err_str = new CString( "unexpected EOF in project file" );//throw
						throw err_str;
					}
					np = ParseKeyString( &in_str, &key_str, &p );
					if( key_str != "corner" || np < 4 )
					{
						CString * err_str = new CString( "error parsing [graphics] section of project file" );//throw
						throw err_str;
					}
					// end contour
					if( np >= 6 )
						n_cont = my_atoi( &p[4] );
					else
						n_cont = 0;
					if( last_n_cont != n_cont && icor > i_start+2 )
					{
						(*op)[ic].Close( last_side_style, 0 );
						i_start = icor;
					}
					//
					int ncor = my_atoi( &p[0] );
					if( (ncor-1) != icor )
					{
						CString * err_str = new CString( "error parsing [graphics] section of project file" );
						throw err_str;
					}
					int x = my_atoi( &p[1] );
					int y = my_atoi( &p[2] );
					id id_sm( ID_POLYLINE, ID_GRAPHIC, ic );
					if( icor == 0 )
					{
						// make new line
						(*op)[ic].Start( lay, wid, 20*NM_PER_MIL, x, y, hatch, &id_sm, NULL );
						if( ssm )
							(*op)[ic].SetDisplayList( NULL );
						else
							(*op)[ic].SetDisplayList( m_dlist );
					}
					else
						(*op)[ic].AppendCorner( x, y, last_side_style, FALSE );
					if( np >= 5 )
						last_side_style = my_atoi( &p[3] );
					else
						last_side_style = CPolyLine::STRAIGHT;
					last_n_cont = n_cont;
					if( icor == (ncorners-1) )
					{
						if( clsd )
							(*op)[ic].Close( last_side_style );
						else
							(*op)[ic].Draw( (*op)[ic].GetDisplayList() );
						(*op)[ic].SetMerge(merge);
						(*op)[ic].SetMerge(s_merge,TRUE);
					}
				}
			}
		}
	}
	catch( CFileException * e )
	{
		CString * err_str = new CString;//throw
		if( e->m_lOsError == -1 )
			err_str->Format( "File error: %d\n", e->m_cause );
		else
			err_str->Format( "File error: %d %ld (%s)\n", 
				e->m_cause, e->m_lOsError, _sys_errlist[e->m_lOsError] );
		*err_str = "CFreePcbDoc::ReadGraphics()\n" + *err_str;
		throw err_str;
	}
}
// read project options from file
//
// throws CString * exception on error
//
int CFreePcbDoc::ReadOptions( CStdioFile * pcb_file, BOOL rColors, BOOL rCropData )
{
	int err, pos, np;
	int layer_info_number = -1;
	CArray<CString> p;
	CString in_str, key_str;
	BOOL m_org_changed = FALSE;
	// initalize
	CFreePcbView * view = (CFreePcbView*)m_view;
	if( rColors )
	{
		m_visible_grid.SetSize( 0 );
		m_part_grid.SetSize( 0 );
		m_routing_grid.SetSize( 0 );
		m_fp_visible_grid.SetSize( 0 );
		m_fp_part_grid.SetSize( 0 );
	}
	if( rCropData )
		m_crop_data.RemoveAll();
	m_name = "";
	m_auto_interval = 0;
	m_dr.bCheckUnrouted = FALSE;
	m_bSMT_copper_connect = FALSE;
	m_default_glue_w = 25*NM_PER_MIL;
	m_report_flags = 0;
	m_view->m_active_layer = LAY_TOP_COPPER;
	m_view->m_sel_mask = INT_MAX;
	m_view->SetSelMaskArray( m_view->m_sel_mask );
	m_dlist->SetTopLayer(m_view->m_active_layer);
	m_file_version = 1.2;
	m_plist->m_part_line_visible = 1;
	m_snap_angle = 45;
	try
	{
		// find beginning of [options] section
		do
		{
			err = pcb_file->ReadString( in_str );
			if( !err )
			{
				// error reading pcb file
				CString mess;
				mess.Format(G_LANGUAGE == 0 ? "Unable to find [options] section in file":"Не удалось найти раздел [options] в файле");
				AfxMessageBox( mess );
				return 0;
			}
			in_str.Trim();
		}
		while( in_str != "[options]" );

		// get data
		while( 1 )
		{
			pos = pcb_file->GetPosition();
			err = pcb_file->ReadString( in_str );
			if( !err )
			{
				CString * err_str = new CString( "unexpected EOF in project file" );//throw
				throw err_str;
			}
			in_str.Trim();
			if( in_str.Left(1) == "[" && in_str != "[options]" )
			{
				// normal return
				pcb_file->Seek(pos,CFile::begin);
				break;
			}
			//
			np = ParseKeyString( &in_str, &key_str, &p );
			if( np == 2 && key_str == "project_name" )
			{
				m_name = p[0];
			}
			else if( np == 2 && key_str == "app_folder" )
			{
				m_get_app_folder = p[0];
			}
			else if( np == 2 && key_str == "version" )
			{
				m_read_version = my_atof( &p[0] );
			}
			else if( np == 2 && key_str == "file_version" )
			{
				m_file_version = my_atof( &p[0] );
			}
			else if( np == 2 && key_str == "protected" )
			{
				if( m_view )
					m_view->m_protected = my_atof( &p[0] );
			}
			else if( np && key_str == "parent_folder" && rColors )
			{
				m_parent_folder = p[0];
				if( m_parent_folder.Right(1) == "\\" )
					m_parent_folder = m_parent_folder.Left(m_parent_folder.GetLength() - 1);
				struct _stat buf;
				int err = _stat( m_parent_folder, &buf );//ok
				if( err && m_parent_folder.GetLength() > 3 )
				{
					int isep = m_app_dir.ReverseFind( '\\' );
					if( isep == -1 )
						isep = m_app_dir.ReverseFind( ':' );
					if( isep == -1 )
						ASSERT(0);		// unable to parse path
					CString app = m_app_dir.Left(isep+1);
					m_parent_folder = app + "Projects\\";
				}
			}
			else if( np && key_str == "library_folder" )
			{
				m_lib_dir = p[0];
			}
			else if( np && key_str == "full_library_folder" )
			{
				m_full_lib_dir = p[0];
				if( m_full_lib_dir.Left(1) == "?" )
					m_full_lib_dir.Replace( "?", m_parent_folder );
				struct _stat buf;
				int STAT = _stat( m_full_lib_dir, &buf );
				if( STAT )
				{
					int rf = m_parent_folder.ReverseFind('\\');
					if( rf > 0 )
					{
						CString keyword = m_parent_folder.Right( m_parent_folder.GetLength()-rf );
						int wordfind = m_full_lib_dir.Find( keyword );
						if( wordfind > 0 )
						{
							CString rightstr = m_full_lib_dir.Right( m_full_lib_dir.GetLength()-wordfind );
							rightstr.Replace( keyword, m_parent_folder );
							m_full_lib_dir = rightstr;
						}
					}
				}
			}
			else if( np && key_str == "CAM_folder" )
			{
				m_cam_full_path = p[0];
			}
			else if( np && key_str == "netlist_file_path" )
			{
				m_netlist_full_path = p[0];
				if( m_netlist_full_path.GetLength() > 4 )
				{
					int r = m_netlist_full_path.ReverseFind('\\');
					if( r > 0 )
					{
						CString command_str = m_app_dir + "\\VCL_Dialog\\net_imp";
						CStdioFile net_path;
						int ok = net_path.Open( command_str, CFile::modeCreate | CFile::modeWrite );
						if( ok )
						{
							net_path.WriteString( m_netlist_full_path.Left(r) );
							net_path.Close();
						}
					}
				}
			}
			else if( np>=3 && key_str == "font_options" )
			{
				if( m_smfontutil )
				{
					m_smfontutil->m_font_number = (FONT_TYPE)my_atoi( &p[0] );
					m_smfontutil->m_letter_spacing = my_atof( &p[1] );
					if( m_smfontutil->m_font_number > GOTHIC )
						m_smfontutil->m_font_number = GOTHIC;
					if( m_smfontutil->m_font_number < SMALL_SIMPLEX )
						m_smfontutil->m_font_number = SMALL_SIMPLEX;
				}
			}
			else if( np && key_str == "part_search" )
			{
				m_part_search = p[0];
			}
			else if( np && key_str == "png_settings" )
			{
				m_png_settings = p[0];
			}	
			else if( np && key_str == "ses_file_path" )
			{
				m_ses_full_path = p[0];
			}
			else if( np && key_str == "dsn_flags" )
			{
				m_dsn_flags = my_atoi( &p[0] );
			}
			else if( np && key_str == "dsn_bounds_poly" )
			{
				m_dsn_bounds_poly = my_atoi( &p[0] );
			}
			else if( np && key_str == "dsn_signals_poly" )
			{
				m_dsn_signals_poly = my_atoi( &p[0] );
			}
			else if( np && key_str == "SMT_connect_copper" )
			{
				m_bSMT_copper_connect = my_atoi( &p[0] );
				m_nlist->SetSMTconnect( m_bSMT_copper_connect );
			}
			else if( np && key_str == "default_glue_width" )
			{
				m_default_glue_w = my_atoi( &p[0] );
			}
			else if( np && key_str == "n_copper_layers" )
			{
				m_num_copper_layers = my_atoi( &p[0] );
				m_num_copper_layers = min(16, m_num_copper_layers);
				m_plist->SetNumCopperLayers( m_num_copper_layers );
				m_nlist->SetNumCopperLayers( m_num_copper_layers );
				m_num_layers = m_num_copper_layers + LAY_TOP_COPPER;
			}
			else if( np && key_str == "autosave_interval" )
			{
				m_auto_interval = my_atoi( &p[0] );
			}
			else if( np && key_str == "auto_ratline_disable" )
			{
				m_auto_ratline_disable = my_atoi( &p[0] );
			}
			else if( np && key_str == "auto_ratline_disable_min_pins" )
			{
				m_auto_ratline_min_pins = my_atoi( &p[0] );
			}
			else if( np && key_str == "netlist_import_flags" )
			{
				m_import_flags = my_atoi( &p[0] );
			}
			else if( np && key_str ==  "netlist_completed" )
			{
				m_netlist_completed = my_atoi( &p[0] );
			}
			else if( np && key_str == "m_client_rect_top" )
			{
				m_view->m_client_r.top = my_atoi( &p[0] );
			}
			else if( np && key_str == "m_client_rect_left" )
			{
				m_view->m_client_r.left = my_atoi( &p[0] );
			}
			else if( np && key_str == "m_client_rect_right" )
			{
				m_view->m_client_r.right = my_atoi( &p[0] );
			}
			else if( np && key_str == "m_client_rect_bottom" )
			{
				m_view->m_client_r.bottom = my_atoi( &p[0] );
			}
			else if( np && key_str == "m_org_x" )
			{
				m_org_changed = TRUE;
				m_view->m_org_x = my_atoi( &p[0] )*m_pcbu_per_wu;
			}
			else if( np && key_str == "m_org_y" )
			{
				m_org_changed = TRUE;
				m_view->m_org_y = my_atoi( &p[0] )*m_pcbu_per_wu;
			}
			else if( np && key_str == "m_scale_factor" )
			{
				int scale = my_atoi( &p[0] );
				m_view->m_pcbu_per_pixel = (double)scale;
			}
			else if( np && key_str == "m_system_colors" )
			{
				m_system_colors = my_atoi( &p[0] );
			}
			else if( np && key_str == "pdf_pin1" )
			{
				m_pdf_pin1 = my_atof( &p[0] );
			}
			else if( np && key_str == "pdf_use_font" )
			{
				m_pdf_use_font1 = my_atoi( &p[0] );
				if( np >= 3 )
					m_pdf_use_font2 = my_atoi( &p[1] );
				if( np >= 4 )
					m_pdf_use_font3 = my_atoi( &p[2] );
			}
			else if( np && key_str == "part_line_visible" && !rColors )
			{
				if( m_plist )
					m_plist->m_part_line_visible = my_atoi( &p[0] );
				if( m_plist->m_part_line_visible == 0 )
					if( AfxMessageBox(G_LANGUAGE == 0 ? 
						"The visibility of the silkscreen lines of the parts in this project is disabled. Make them visible?":
						"Видимость линий шелкографии у деталей в этом проекте отключена. Сделать их видимыми?", MB_YESNO | MB_ICONQUESTION) == IDYES)
						m_plist->m_part_line_visible = 1;
			}
			else if( np && key_str == "units" )
			{
				if( p[0] == "MM" )
					m_units = MM;
				else
					m_units = MIL;
			}
			else if( np && key_str == "m_grid_style" )
			{
				int gs = my_atoi( &p[0] );
				m_dlist->SetGridStyle(gs);
			}
			else if( np && key_str == "m_top_layer" )
			{
				int tl = my_atoi( &p[0] );
				m_view->m_active_layer = max(tl,LAY_SM_TOP);
				m_dlist->SetTopLayer(m_view->m_active_layer);

			}
			else if( np && key_str == "m_visible_layers" )
			{
				int vl = my_atoi( &p[0] );
				for( int ii=0; ii<MAX_LAYERS; ii++ )
					if( getbit( vl, ii ) )
						m_vis[ii] = 1;
					else
						m_vis[ii] = 0;
			}
			else if( np && key_str == "m_sel_mask" )
			{
				int msm = my_atoi( &p[0] );
				clrbit( msm, SEL_MASK_REF );
				m_view->m_sel_mask = msm;	
				m_view->SetSelMaskArray( msm );
			}
			else if( np && key_str == "visible_grid_spacing" )
			{
				m_visual_grid_spacing = my_atof( &p[0] );
			}
			else if( np && key_str == "visible_grid_item" && rColors )
			{
				CString str;
				double value;
				if( np == 3 )
					str = p[1];
				else
					str = p[0];
				value = my_atof( &str );
				if( str.Right(2) == "MM" || str.Right(2) == "mm" )
					m_visible_grid.Add( -value );
				else
					m_visible_grid.Add( value );
			}
			else if( np && key_str == "placement_grid_spacing" )
			{
				m_part_grid_spacing = my_atof( &p[0] );
			}
			else if( np && key_str == "placement_grid_item" && rColors )
			{
				CString str;
				double value;
				if( np == 3 )
					str = p[1];
				else
					str = p[0];
				value = my_atof( &str );
				if( str.Right(2) == "MM" || str.Right(2) == "mm" )
					m_part_grid.Add( -value );
				else
					m_part_grid.Add( value );
			}
			else if( np && key_str == "routing_grid_spacing" )
			{
				m_routing_grid_spacing = my_atof( &p[0] );
			}
			else if( np && key_str == "routing_grid_item" && rColors )
			{
				CString str;
				double value;
				if( np == 3 )
					str = p[1];
				else
					str = p[0];
				value = my_atof( &str );
				if( str.Right(2) == "MM" || str.Right(2) == "mm" )
					m_routing_grid.Add( -value );
				else
					m_routing_grid.Add( value );
			}
			else if( np && key_str == "snap_angle" )
			{
				m_snap_angle = my_atof( &p[0] );
			}
			else if( np && key_str == "fp_visible_grid_spacing" )
			{
				m_fp_visual_grid_spacing = my_atof( &p[0] );
			}
			else if( np && key_str == "fp_visible_grid_item" && rColors )
			{
				CString str;
				double value;
				if( np == 3 )
					str = p[1];
				else
					str = p[0];
				value = my_atof( &str );
				if( str.Right(2) == "MM" || str.Right(2) == "mm" )
					m_fp_visible_grid.Add( -value );
				else
					m_fp_visible_grid.Add( value );
			}
			else if( np && key_str == "fp_placement_grid_spacing" )
			{
				m_fp_part_grid_spacing = my_atof( &p[0] );
			}
			else if( np && key_str == "fp_placement_grid_item" && rColors )
			{
				CString str;
				double value;
				if( np == 3 )
					str = p[1];
				else
					str = p[0];
				value = my_atof( &str );
				if( str.Right(2) == "MM" || str.Right(2) == "mm" )
					m_fp_part_grid.Add( -value );
				else
					m_fp_part_grid.Add( value );
			}
			else if( np && key_str == "fp_snap_angle" )
			{
				m_fp_snap_angle = my_atof( &p[0] );
			}
			else if( np && key_str == "m_seg_clearance" )
			{
				////m_view->m_seg_clearance = my_atoi( &p[0] );
			}
			else if( np && key_str == "m_pin_state" )
			{
				m_view->m_pin_state = my_atoi( &p[0] );
			}
			// CAM stuff
			else if( np && key_str == "fill_clearance" )
			{
				m_fill_clearance = my_atoi( &p[0] );
			}
			else if (np >= 3 && key_str == "panel_fields")
			{
				m_panel_fields[0] = my_atoi(&p[0]);
				m_panel_fields[1] = my_atoi(&p[1]);
			}
			else if (np >= 3 && key_str == "panel_holes")
			{
				m_panel_holes[0] = my_atoi(&p[0]);
				m_panel_holes[1] = my_atoi(&p[1]);
			}
			else if (np && key_str == "panel_ref_count")
			{
				m_panel_ref_count = my_atoi(&p[0]);
			}
			else if (np && key_str == "panel_reference")
			{
				m_panel_reference = p[0];
			}
			else if (np && key_str == "panel_scribing")
			{
				m_panel_scribing = my_atoi(&p[0]);
			}
			else if (np >= 5 && key_str == "panel_text")
			{
				m_panel_text[0] = p[0];
				m_panel_text[1] = p[1];
				m_panel_text[2] = p[2];
				m_panel_text[3] = p[3];
			}
			else if (np >= 5 && key_str == "panel_frame_for_paste")
			{
				m_panel_frame_for_paste.left = my_atoi(&p[0]);
				m_panel_frame_for_paste.right = my_atoi(&p[1]);
				m_panel_frame_for_paste.top = my_atoi(&p[2]);
				m_panel_frame_for_paste.bottom = my_atoi(&p[3]);
			}
			else if( np && key_str == "mask_clearance" )
			{
				m_mask_clearance = my_atoi( &p[0] );
				m_plist->Set_default_mask_clearance( m_mask_clearance );
			}
			else if( np && key_str == "thermal_width" )
			{
				m_thermal_width = my_atoi( &p[0] );
			}
			else if( np && key_str == "thermal_clearance" )
			{
				m_thermal_clearance = my_atoi( &p[0] );
			}
			else if( np && key_str == "min_silkscreen_width" )
			{
				m_min_silkscreen_stroke_wid = my_atoi( &p[0] );
			}
			else if( np && key_str == "highlight_width" )
			{
				m_highlight_wid = my_atoi( &p[0] );
			}
			else if( np && key_str == "pilot_diameter" )
			{
				m_pilot_diameter = my_atoi( &p[0] );
			}
			else if( np && key_str == "hole_clearance" )
			{
				m_hole_clearance = my_atoi( &p[0] );
			}
			else if( np && key_str == "annular_ring_for_pins" )
			{
				m_annular_ring_pins = my_atoi( &p[0] );
			}
			else if( np && key_str == "annular_ring_for_vias" )
			{
				m_annular_ring_vias = my_atoi( &p[0] );
			}
			else if( np && key_str == "shrink_paste_mask" )
			{
				m_paste_shrink = my_atoi( &p[0] );
				m_plist->Set_default_paste_clearance( m_paste_shrink );
			}
			else if( np && key_str == "cam_flags" )
			{
				m_cam_flags = my_atoi( &p[0] );
			}
			else if( np && key_str == "crop_flags" )
			{
				m_crop_flags = my_atoi( &p[0] );
			}
			else if( np && key_str == "crop_data" )
			{
				if( rCropData )
					m_crop_data.Add( in_str );
			}
			else if( np && key_str == "cam_layers" )
			{
				m_cam_layers = my_atoi( &p[0] );
			}
			else if( np && key_str == "cam_drill_file" )
			{
				m_cam_drill_file = my_atoi( &p[0] );
			}
			else if( np && key_str == "cam_units" )
			{
				m_cam_units = my_atoi( &p[0] );
			}
			else if( np && key_str == "cam_n_x" )
			{
				m_n_x = my_atoi( &p[0] );
			}
			else if( np && key_str == "cam_n_y" )
			{
				m_n_y = my_atoi( &p[0] );
			}
			else if( np && key_str == "cam_space_x" )
			{
				m_space_x = my_atoi( &p[0] );
			}
			else if( np && key_str == "cam_space_y" )
			{
				m_space_y = my_atoi( &p[0] );
			}
			else if (np && key_str == "symmetrization_x")
			{
				m_symmetric_x = my_atoi(&p[0]);
			}
			else if (np && key_str == "symmetrization_y")
			{
				m_symmetric_y = my_atoi(&p[0]);
			}
			else if( np && key_str == "report_options" )
			{
				m_report_flags = my_atoi( &p[0] );
			}
			// DRC stuff
			else if( np && key_str == "drc_check_unrouted" )
			{
				m_dr.bCheckUnrouted = my_atoi( &p[0] );
			}
			else if( np && key_str == "drc_trace_width" )
			{
				m_dr.trace_width = my_atoi( &p[0] );
			}
			else if( np && key_str == "drc_pad_pad" )
			{
				m_dr.pad_pad = my_atoi( &p[0] );
			}
			else if( np && key_str == "drc_pad_trace" )
			{
				m_dr.pad_trace = my_atoi( &p[0] );
			}
			else if( np && key_str == "drc_trace_trace" )
			{
				m_dr.trace_trace = my_atoi( &p[0] );
				m_view->m_seg_clearance = m_dr.trace_trace + _2540*2;
			}
			else if( np && key_str == "drc_hole_copper" )
			{
				m_dr.hole_copper = my_atoi( &p[0] );
			}
			else if( np && key_str == "drc_annular_ring_pins" )
			{
				m_dr.annular_ring_pins = my_atoi( &p[0] );
			}
			else if( np && key_str == "drc_annular_ring_vias" )
			{
				m_dr.annular_ring_vias = my_atoi( &p[0] );
			}
			else if( np && key_str == "drc_board_edge_copper" )
			{
				m_dr.board_edge_copper = my_atoi( &p[0] );
			}
			else if( np && key_str == "drc_board_edge_hole" )
			{
				m_dr.board_edge_hole = my_atoi( &p[0] );
			}
			else if( np && key_str == "drc_hole_hole" )
			{
				m_dr.hole_hole = my_atoi( &p[0] );
			}
			else if( np && key_str == "drc_copper_copper" )
			{
				m_dr.copper_copper = my_atoi( &p[0] );
			}
			else if( np && key_str == "default_trace_width" )
			{
				if( p[0].Right(2) == "MM" || p[0].Right(2) == "mm" )
					m_trace_w = -my_atof( &p[0] );
				else
					m_trace_w = my_atof( &p[0] );
				m_nlist->SetWidths( abs(m_trace_w), abs(m_via_w), abs(m_via_hole_w) );
			}
			else if( np && key_str == "default_via_pad_width" )
			{
				if( p[0].Right(2) == "MM" || p[0].Right(2) == "mm" )
					m_via_w = -my_atof( &p[0] );
				else
					m_via_w = my_atof( &p[0] );
				m_nlist->SetWidths( abs(m_trace_w), abs(m_via_w), abs(m_via_hole_w) );
			}
			else if( np && key_str == "default_via_hole_width" )
			{
				if( p[0].Right(2) == "MM" || p[0].Right(2) == "mm" )
					m_via_hole_w = -my_atof( &p[0] );
				else
					m_via_hole_w = my_atof( &p[0] );
				m_nlist->SetWidths( abs(m_trace_w), abs(m_via_w), abs(m_via_hole_w) );
			}
			else if( np && key_str == "n_width_menu" )
			{
				int n = my_atoi( &p[0] );
				m_w.SetSize( n );
				m_v_w.SetSize( n );
				m_v_h_w.SetSize( n );
				for( int i=0; i<n; )
				{
					pos = pcb_file->GetPosition();
					err = pcb_file->ReadString( in_str );
					in_str.Trim();
					if( in_str.GetLength() == 0 )
						continue;
					//
					if( !err )
					{
						CString * err_str = new CString( "unexpected EOF in project file" );//throw
						throw err_str;
					}
					np = ParseKeyString( &in_str, &key_str, &p );
					if( np < 5 || key_str != "width_menu_item" )
					{
						CString * err_str = new CString( "error parsing [options] section of project file" );//throw
						throw err_str;
					}
					int ig = my_atoi( &p[0] ) - 1;
					if( ig != i )
					{
						CString * err_str = new CString( "error parsing [options] section of project file" );//throw
						throw err_str;
					}
					if( p[1].Right(2) == "MM" || p[1].Right(2) == "mm" )
						m_w[i] = -my_atof( &p[1] );
					else
						m_w[i] = my_atof( &p[1] );
					if( p[2].Right(2) == "MM" || p[2].Right(2) == "mm" )
						m_v_w[i] = -my_atof( &p[2] );
					else
						m_v_w[i] = my_atof( &p[2] );
					if( p[3].Right(2) == "MM" || p[3].Right(2) == "mm" )
						m_v_h_w[i] = -my_atof( &p[3] );
					else
						m_v_h_w[i] = my_atof( &p[3] );
					i++;
				}
			}
			else if( np && key_str == "layer_info" )
			{
				CString file_layer_name = p[0];
				int i = my_atoi( &p[1] );
				int layer = -1;
				if( rColors )
					for( int il=0; il<=LAY_BOTTOM_COPPER; il++ )
					{
						CString layer_string = &layer_str[il][0];
						if( file_layer_name == layer_string )
						{
							layer = il;
							layer_info_number = -1;
							break;
						}
					}
				if( rColors && layer == -1 )
					for( int il=LAY_BOTTOM_COPPER+1; il<MAX_LAYERS; il++ )
					{
						CString layer_string = &layer_str[il][0];
						if( file_layer_name == layer_string )
						{
							layer = il;
							layer_info_number = -1;
							break;
						}
					}
				if (layer < 0 && layer_info_number >= 0)
				{
					layer = layer_info_number;
					layer_info_number++;
				}
				if( layer < 0 || layer >= MAX_LAYERS )
				{
					//AfxMessageBox( "Warning: layer \"" + file_layer_name + "\" not supported" );
				}
				else if( np >= 7 )
				{
					m_rgb[layer][0] = my_atoi( &p[2] );
					m_rgb[layer][1] = my_atoi( &p[3] );
					m_rgb[layer][2] = my_atoi( &p[4] );
					m_vis[layer] = my_atoi( &p[5] );
					if( np >= 11 )
					{
						m_pdf_rgb[layer][0] = my_atoi( &p[6] );
						m_pdf_rgb[layer][1] = my_atoi( &p[7] );
						m_pdf_rgb[layer][2] = my_atoi( &p[8] );
						m_pdf_vis[layer] = my_atoi( &p[9] );
					}
				}
			}
			else if( np && key_str == "merge_shown" )
			{
				m_view->m_merge_show = my_atoi( &p[0] );
			}
		}
		if( m_fp_visible_grid.GetSize() == 0 )
		{
			m_fp_visual_grid_spacing = m_visual_grid_spacing;
			for( int i=0; i<m_visible_grid.GetSize(); i++ )
				m_fp_visible_grid.Add( m_visible_grid[i] );
		}
		if( m_fp_part_grid.GetSize() == 0 )
		{
			m_fp_part_grid_spacing = m_part_grid_spacing;
			for( int i=0; i<m_part_grid.GetSize(); i++ )
				m_fp_part_grid.Add( m_part_grid[i] );
		}
		if( m_fp_snap_angle != 0 && m_fp_snap_angle != 45 && m_fp_snap_angle != 90 )
			m_fp_snap_angle = m_snap_angle;
		m_vis[LAY_HILITE] = TRUE;
		m_dlist->m_vis[LAY_HILITE] = TRUE;
		CMainFrame * frm = (CMainFrame*)AfxGetMainWnd();
		frm->m_wndMyToolBar.SetLists( &m_visible_grid, &m_part_grid, &m_routing_grid,
			m_visual_grid_spacing, m_part_grid_spacing, m_routing_grid_spacing, m_snap_angle, m_units );
		m_dlist->SetVisibleGrid( TRUE, m_visual_grid_spacing );
		LoadSpeedFiles( this );
		return m_org_changed;
	}
	catch( CFileException * e )
	{
		CString * err_str = new CString;//throw
		if( e->m_lOsError == -1 )
			err_str->Format( "File error: %d\n", e->m_cause );
		else
			err_str->Format( "File error: %d %ld (%s)\n", 
				e->m_cause, e->m_lOsError, _sys_errlist[e->m_lOsError] );
		*err_str = "CFreePcbDoc::WriteOptions()\n" + *err_str;
		throw err_str;
	}
}

// write project options to file
//
// throws CString * exception on error
//
void CFreePcbDoc::WriteOptions( CStdioFile * file, BOOL bConfig )
{
	CString line;

	try
	{
		CString str;
		CFreePcbView * view = (CFreePcbView*)m_view;
		line.Format( "[options]\n\n" );
		file->WriteString( line );
		line.Format( "app_folder: \"%s\"\n", m_app_dir );
		file->WriteString( line );
		line.Format( "version: %5.3f\n", m_version );
		file->WriteString( line );
		m_file_version = m_version;
		line.Format( "file_version: %5.3f\n", m_file_version );
		file->WriteString( line );
		if( m_view && bConfig )
		{
			line.Format( "protected: %d\n", m_view->m_protected );
			file->WriteString( line );
		}
		line.Format( "project_name: \"%s\"\n", m_name );
		file->WriteString( line );
		CString lp = m_full_lib_dir.Left( m_full_lib_dir.ReverseFind( '\\' ) );
		line.Format( "library_folder: \"%s\"\n", lp );
		file->WriteString( line );

		if( bConfig )
		{
			line.Format( "parent_folder: \"%s\"\n", m_parent_folder );
			file->WriteString( line );
		}
		// lib folder
		{
			str = m_full_lib_dir;
			line.Format( "full_library_folder: \"%s\"\n", str );
			file->WriteString( line );
		}
		
		line.Format( "CAM_folder: \"%s\"\n", m_cam_full_path );
		file->WriteString( line );
		line.Format( "ses_file_path: \"%s\"\n", m_ses_full_path );
		file->WriteString( line );
		line.Format( "netlist_completed: \"%d\"\n", (bConfig?0:m_netlist_completed) );
		file->WriteString( line );
		if( bConfig && m_smfontutil )
		{
			line.Format( "font_options: %d %.2f\n", (int)m_smfontutil->m_font_number, m_smfontutil->m_letter_spacing );
			file->WriteString( line );
		}
		line.Format( "part_search: \"%s\"\n", (bConfig?"":m_part_search) );
		file->WriteString( line );
		line.Format( "png_settings: \"%s\"\n", m_png_settings );
		file->WriteString( line );
		line.Format( "netlist_file_path: \"%s\"\n", (bConfig?"":m_netlist_full_path) );
		file->WriteString( line );
		line.Format( "SMT_connect_copper: \"%d\"\n", m_bSMT_copper_connect );
		file->WriteString( line );
		line.Format( "default_glue_width: \"%d\"\n", m_default_glue_w );
		file->WriteString( line );
		line.Format( "dsn_flags: \"%d\"\n", m_dsn_flags );
		file->WriteString( line );
		line.Format( "dsn_bounds_poly: \"%d\"\n", m_dsn_bounds_poly );
		file->WriteString( line );
		line.Format( "dsn_signals_poly: \"%d\"\n", m_dsn_signals_poly );
		file->WriteString( line );
		line.Format( "autosave_interval: %d\n", m_auto_interval );
		file->WriteString( line );
		line.Format( "auto_ratline_disable: \"%d\"\n", m_auto_ratline_disable );
		file->WriteString( line );
		line.Format( "auto_ratline_disable_min_pins: \"%d\"\n", m_auto_ratline_min_pins );
		file->WriteString( line );
		line.Format( "netlist_import_flags: %d\n", m_import_flags );
		file->WriteString( line );
		line.Format( "m_client_rect_left: %d\n", m_view->m_client_r.left );
		file->WriteString( line );
		line.Format( "m_client_rect_right: %d\n", m_view->m_client_r.right );
		file->WriteString( line );
		line.Format( "m_client_rect_bottom: %d\n", m_view->m_client_r.bottom );
		file->WriteString( line );
		line.Format( "m_client_rect_top: %d\n", m_view->m_client_r.top );
		file->WriteString( line );
		line.Format( "m_org_x: %d\n", (int)((double)m_view->m_org_x/(double)m_pcbu_per_wu) );
		file->WriteString( line );
		line.Format( "m_org_y: %d\n", (int)((double)m_view->m_org_y/(double)m_pcbu_per_wu) );
		file->WriteString( line );
		line.Format( "m_scale_factor: %d\n", (int)m_view->m_pcbu_per_pixel );
		file->WriteString( line );
		if( m_plist )
		{
			line.Format( "part_line_visible: %d\n", (bConfig?1:m_plist->m_part_line_visible) );
			file->WriteString( line );
		}
		line.Format( "merge_shown: %d\n", m_view->m_merge_show );
		file->WriteString( line );
		//
		if( bConfig )
		{
			line.Format( "m_pin_state: %d\n", m_view->m_pin_state );
			file->WriteString( line );
			line.Format( "m_system_colors: %d\n", m_system_colors );
			file->WriteString( line );
		}
		// pdf options
		line.Format( "pdf_pin1: %f\n", m_pdf_pin1 );
		file->WriteString( line );
		line.Format( "pdf_use_font: %d %d %d\n", m_pdf_use_font1, m_pdf_use_font2, m_pdf_use_font3 );
		file->WriteString( line );
		//
		//
		if( m_units == MIL )
			file->WriteString( "units: MIL\n\n" );
		else
			file->WriteString( "units: MM\n\n" );
		line.Format( "m_sel_mask: %d\n", m_view->m_sel_mask );
		file->WriteString( line );
		int m_vis_lrs = 0;
		for ( int ii=0; ii< MAX_LAYERS; ii++ )
			if( m_dlist->m_vis[ii] )
				setbit( m_vis_lrs, ii );
		line.Format( "m_visible_layers: %d\n", m_vis_lrs );
		file->WriteString( line );
		line.Format( "m_top_layer: %d\n", m_dlist->GetTopLayer() );
		file->WriteString( line );
		line.Format( "m_grid_style: %d\n", m_dlist->GetGridStyle() );
		file->WriteString( line );
		//
		line.Format( "visible_grid_spacing: %f\n", m_visual_grid_spacing );
		file->WriteString( line );
		for( int i=0; i<m_visible_grid.GetSize(); i++ )
		{
			if( m_visible_grid[i] > 0 )
				::MakeCStringFromDimension( &str, m_visible_grid[i], MIL, TRUE, TRUE );
			else
				::MakeCStringFromDimension( &str, -m_visible_grid[i], MM, TRUE, TRUE );
			file->WriteString( "  visible_grid_item: " + str + "\n" );
		}
		file->WriteString( "\n" );

		//
		line.Format( "placement_grid_spacing: %f\n", m_part_grid_spacing );
		file->WriteString( line );
		for( int i=0; i<m_part_grid.GetSize(); i++ )
		{
			if( m_part_grid[i] > 0 )
				::MakeCStringFromDimension( &str, m_part_grid[i], MIL, TRUE, TRUE );
			else
				::MakeCStringFromDimension( &str, -m_part_grid[i], MM, TRUE, TRUE );
			file->WriteString( "  placement_grid_item: " + str + "\n" );
		}
		file->WriteString( "\n" );
		line.Format( "routing_grid_spacing: %f\n", m_routing_grid_spacing );
		file->WriteString( line );
		for( int i=0; i<m_routing_grid.GetSize(); i++ )
		{
			if( m_routing_grid[i] > 0 )
				::MakeCStringFromDimension( &str, m_routing_grid[i], MIL, TRUE, TRUE );
			else
				::MakeCStringFromDimension( &str, -m_routing_grid[i], MM, TRUE, TRUE );
			file->WriteString( "  routing_grid_item: " + str + "\n" );
		}
		file->WriteString( "\n" );
		line.Format( "snap_angle: %d\n", m_snap_angle );
		file->WriteString( line );
		file->WriteString( "\n" );
		line.Format( "fp_visible_grid_spacing: %f\n", m_fp_visual_grid_spacing );
		file->WriteString( line );
		for( int i=0; i<m_fp_visible_grid.GetSize(); i++ )
		{
			if( m_fp_visible_grid[i] > 0 )
				::MakeCStringFromDimension( &str, m_fp_visible_grid[i], MIL, TRUE, TRUE );
			else
				::MakeCStringFromDimension( &str, -m_fp_visible_grid[i], MM, TRUE, TRUE );
			file->WriteString( "  fp_visible_grid_item: " + str + "\n" );
		}
		file->WriteString( "\n" );
		line.Format( "fp_placement_grid_spacing: %f\n", m_fp_part_grid_spacing );
		file->WriteString( line );
		for( int i=0; i<m_fp_part_grid.GetSize(); i++ )
		{
			if( m_fp_part_grid[i] > 0 )
				::MakeCStringFromDimension( &str, m_fp_part_grid[i], MIL, TRUE, TRUE );
			else
				::MakeCStringFromDimension( &str, -m_fp_part_grid[i], MM, TRUE, TRUE );
			file->WriteString( "  fp_placement_grid_item: " + str + "\n" );
		}
		file->WriteString( "\n" );
		line.Format( "fp_snap_angle: %d\n", m_fp_snap_angle );
		file->WriteString( line );
		file->WriteString( "\n" );
		line.Format( "m_seg_clearance: %d\n", m_view->m_seg_clearance );
		file->WriteString( line );
		line.Format( "fill_clearance: %d\n", m_fill_clearance );
		file->WriteString( line );
		// for panelization
		line.Format("panel_fields: %d %d\n", m_panel_fields[0], m_panel_fields[1] );
		file->WriteString(line);
		line.Format("panel_holes: %d %d\n", m_panel_holes[0], m_panel_holes[1]);
		file->WriteString(line);
		line.Format("panel_ref_count: %d\n", m_panel_ref_count);
		file->WriteString(line);
		line.Format("panel_reference: \"%s\"\n", m_panel_reference);
		file->WriteString(line);
		line.Format("panel_scribing: %d\n", m_panel_scribing);
		file->WriteString(line);
		line.Format("panel_text: \"%s\" \"%s\" \"%s\" \"%s\"\n", m_panel_text[0], m_panel_text[1], m_panel_text[2], m_panel_text[3]);
		file->WriteString(line);
		line.Format("panel_frame_for_paste: %d %d %d %d\n", m_panel_frame_for_paste.left, m_panel_frame_for_paste.right, m_panel_frame_for_paste.top, m_panel_frame_for_paste.bottom);
		file->WriteString(line);
		//
		line.Format( "mask_clearance: %d\n", m_mask_clearance );
		file->WriteString( line );
		line.Format( "thermal_width: %d\n", m_thermal_width );
		file->WriteString( line );
		line.Format( "thermal_clearance: %d\n", m_thermal_clearance );
		file->WriteString( line );
		line.Format( "min_silkscreen_width: %d\n", m_min_silkscreen_stroke_wid );
		file->WriteString( line );
		line.Format( "highlight_width: %d\n", m_highlight_wid );
		file->WriteString( line );
		line.Format( "hole_clearance: %d\n", m_hole_clearance );
		file->WriteString( line );
		line.Format( "pilot_diameter: %d\n", m_pilot_diameter );
		file->WriteString( line );
		line.Format( "annular_ring_for_pins: %d\n", m_annular_ring_pins );
		file->WriteString( line );
		line.Format( "annular_ring_for_vias: %d\n", m_annular_ring_vias );
		file->WriteString( line );
		line.Format( "shrink_paste_mask: %d\n", m_paste_shrink );
		file->WriteString( line );
		line.Format( "cam_flags: %d\n", m_cam_flags );
		file->WriteString( line );
		line.Format( "crop_flags: %d\n", m_crop_flags );
		file->WriteString( line );
		if( bConfig )
			for( int idata=0; idata<m_crop_data.GetSize(); idata++ )
				file->WriteString( m_crop_data[idata]+"\n" );
		line.Format( "cam_layers: %d\n", m_cam_layers );
		file->WriteString( line );
		line.Format( "cam_drill_file: %d\n", m_cam_drill_file );
		file->WriteString( line );
		line.Format( "cam_units: %d\n", m_cam_units );
		file->WriteString( line );
		line.Format( "cam_n_x: %d\n", m_n_x );
		file->WriteString( line );
		line.Format( "cam_n_y: %d\n", m_n_y );
		file->WriteString( line );
		line.Format( "cam_space_x: %d\n", m_space_x );
		file->WriteString( line );
		line.Format( "cam_space_y: %d\n", m_space_y );
		file->WriteString( line );
		line.Format("symmetrization_x: %d\n", m_symmetric_x);
		file->WriteString(line);
		line.Format("symmetrization_y: %d\n", m_symmetric_y);
		file->WriteString(line);
		file->WriteString( "\n" );
		//
		line.Format( "report_options: %d\n", m_report_flags );
		file->WriteString( line );
		line.Format( "drc_check_unrouted: %d\n", m_dr.bCheckUnrouted );
		file->WriteString( line );
		line.Format( "drc_trace_width: %d\n", m_dr.trace_width );
		file->WriteString( line );
		line.Format( "drc_pad_pad: %d\n", m_dr.pad_pad );
		file->WriteString( line );
		line.Format( "drc_pad_trace: %d\n", m_dr.pad_trace );
		file->WriteString( line );
		line.Format( "drc_trace_trace: %d\n", m_dr.trace_trace );
		file->WriteString( line );
		line.Format( "drc_hole_copper: %d\n", m_dr.hole_copper );
		file->WriteString( line );
		line.Format( "drc_annular_ring_pins: %d\n", m_dr.annular_ring_pins );
		file->WriteString( line );
		line.Format( "drc_annular_ring_vias: %d\n", m_dr.annular_ring_vias );
		file->WriteString( line );
		line.Format( "drc_board_edge_copper: %d\n", m_dr.board_edge_copper );
		file->WriteString( line );
		line.Format( "drc_board_edge_hole: %d\n", m_dr.board_edge_hole );
		file->WriteString( line );
		line.Format( "drc_hole_hole: %d\n", m_dr.hole_hole );
		file->WriteString( line );
		line.Format( "drc_copper_copper: %d\n", m_dr.copper_copper );
		file->WriteString( line );
		file->WriteString( "\n" );
		//
		line = "default_trace_width:";
		file->WriteString( line );
		::MakeCStringFromDimension( &line, abs(m_trace_w), (m_trace_w>=0?MIL:MM), TRUE, TRUE, FALSE, (m_trace_w>=0?0:3) );
		file->WriteString( line );
		file->WriteString( "\n" );
		//
		line = "default_via_pad_width:";
		file->WriteString( line );
		::MakeCStringFromDimension( &line, abs(m_via_w), (m_via_w>=0?MIL:MM), TRUE, TRUE, FALSE, (m_via_w>=0?0:3) );
		file->WriteString( line );
		file->WriteString( "\n" );
		//
		line = "default_via_hole_width:";
		file->WriteString( line );
		::MakeCStringFromDimension( &line, abs(m_via_hole_w), (m_via_hole_w>=0?MIL:MM), TRUE, TRUE, FALSE, (m_via_hole_w>=0?0:3) );
		file->WriteString( line );
		file->WriteString( "\n" );
		//
		line.Format( "n_width_menu: %d\n", m_w.GetSize() );
		file->WriteString( line );
		for( int i=0; i<m_w.GetSize(); i++ )
		{
			line.Format( "  width_menu_item: %d ", i+1 );
			file->WriteString( line );
			::MakeCStringFromDimension( &line, abs(m_w[i]), (m_w[i]>=0?MIL:MM), TRUE, TRUE, FALSE, (m_w[i]>=0?0:3) );
			file->WriteString( line );
			file->WriteString( " " );
			::MakeCStringFromDimension( &line, abs(m_v_w[i]), (m_v_w[i]>=0?MIL:MM), TRUE, TRUE, FALSE, (m_v_w[i]>=0?0:3) );
			file->WriteString( line );
			file->WriteString( " " );
			::MakeCStringFromDimension( &line, abs(m_v_h_w[i]), (m_v_h_w[i]>=0?MIL:MM), TRUE, TRUE, FALSE, (m_v_h_w[i]>=0?0:3) );
			file->WriteString( line );
			file->WriteString( "\n" );
		}
		file->WriteString( "\n" );
		line.Format( "n_copper_layers: %d\n", m_num_copper_layers );
		file->WriteString( line );
		///if( wColors )  always write, read optional
			for( int i=0; i<=(m_num_copper_layers==1?LAY_TOP_COPPER:LAY_BOTTOM_COPPER); i++ )
			{
				line.Format( "  layer_info: \"%s\" %d %d %d %d %d %d %d %d %d\n",
					&layer_str[i][0], i,
					m_rgb[i][0], m_rgb[i][1], m_rgb[i][2], m_vis[i], m_pdf_rgb[i][0], m_pdf_rgb[i][1], m_pdf_rgb[i][2], m_pdf_vis[i] );
				file->WriteString( line );
			}
		for( int i=(m_num_copper_layers==1?LAY_BOTTOM_COPPER:LAY_BOTTOM_COPPER+1); i<(LAY_TOP_COPPER+m_num_copper_layers); i++ )
		{
			line.Format( "  layer_info: \"%s\" %d %d %d %d %d %d %d %d %d\n",
				&layer_str[i][0], i,
				m_rgb[i][0], m_rgb[i][1], m_rgb[i][2], m_vis[i], m_pdf_rgb[i][0], m_pdf_rgb[i][1], m_pdf_rgb[i][2], m_pdf_vis[i] );
			file->WriteString( line );
		}
		file->WriteString( "\n" );
		return;
	}
	catch( CFileException * e )
	{
		CString * err_str = new CString;//throw
		if( e->m_lOsError == -1 )
			err_str->Format( "File error: %d\n", e->m_cause );
		else
			err_str->Format( "File error: %d %ld (%s)\n", 
				e->m_cause, e->m_lOsError, _sys_errlist[e->m_lOsError] );
		*err_str = "CFreePcbDoc::WriteBoardOutline()\n" + *err_str;
		throw err_str;
	}
}

// set defaults for a new project
//
void CFreePcbDoc::InitializeNewProject()
{
	m_bShowMessageForClearance = TRUE;

	// these are the embedded defaults
	for(int i=0; i<NUM_CAM_FOLDERS; i++)
		CAM[i] = "";
	m_name = "";
	m_get_app_folder = "";
	m_path_to_folder = "..\\projects\\";
	m_lib_dir = "..\\lib\\" ;
	m_pcb_filename = "";
	m_pcb_full_path = "";
	m_cds_filename = "";
	m_outline_poly.RemoveAll();
	m_units = MIL;
	m_num_copper_layers = 4;
	m_plist->SetNumCopperLayers( m_num_copper_layers );
	m_nlist->SetNumCopperLayers( m_num_copper_layers );
	m_nlist->SetSMTconnect( m_bSMT_copper_connect );
	m_num_layers = m_num_copper_layers + LAY_TOP_COPPER;
	m_auto_ratline_disable = FALSE;
	m_auto_ratline_min_pins = 100;
	m_auto_interval = 0;

	// colors for layers
	for( int i=0; i<MAX_LAYERS; i++ )
	{
		m_vis[i] = 0;
		m_rgb[i][0] = 127; 
		m_rgb[i][1] = 127; 
		m_rgb[i][2] = 127;			// default grey
		m_pdf_vis[i] = 0;
		m_pdf_rgb[i][0] = 127; 
		m_pdf_rgb[i][1] = 127; 
		m_pdf_rgb[i][2] = 127;		// default grey
	}
	m_rgb[LAY_BACKGND][0] = 0; 
	m_rgb[LAY_BACKGND][1] = 0; 
	m_rgb[LAY_BACKGND][2] = 0;			// background BLACK
	m_rgb[LAY_VISIBLE_GRID][0] = 255; 
	m_rgb[LAY_VISIBLE_GRID][1] = 255; 
	m_rgb[LAY_VISIBLE_GRID][2] = 255;	// visible grid WHITE 
	m_rgb[LAY_HILITE][0] = 255; 
	m_rgb[LAY_HILITE][1] = 255; 
	m_rgb[LAY_HILITE][2] = 255;			//highlight WHITE
	m_rgb[LAY_DRC_ERROR][0] = 255; 
	m_rgb[LAY_DRC_ERROR][1] = 128; 
	m_rgb[LAY_DRC_ERROR][2] = 64;		// DRC error ORANGE
	m_rgb[LAY_BOARD_OUTLINE][0] = 0; 
	m_rgb[LAY_BOARD_OUTLINE][1] = 0; 
	m_rgb[LAY_BOARD_OUTLINE][2] = 255;	//board outline BLUE
	m_rgb[LAY_SELECTION][0] = 255; 
	m_rgb[LAY_SELECTION][1] = 255; 
	m_rgb[LAY_SELECTION][2] = 255;		//selection WHITE
	m_rgb[LAY_SILK_TOP][0] = 255; 
	m_rgb[LAY_SILK_TOP][1] = 255; 
	m_rgb[LAY_SILK_TOP][2] =   0;		//top silk YELLOW
	m_rgb[LAY_SILK_BOTTOM][0] = 255; 
	m_rgb[LAY_SILK_BOTTOM][1] = 192; 
	m_rgb[LAY_SILK_BOTTOM][2] = 192;	//bottom silk PINK
	m_rgb[LAY_SM_TOP][0] =   160; 
	m_rgb[LAY_SM_TOP][1] =   160; 
	m_rgb[LAY_SM_TOP][2] =   160;		//top solder mask cutouts LIGHT GREY
	m_rgb[LAY_SM_BOTTOM][0] = 95; 
	m_rgb[LAY_SM_BOTTOM][1] = 95; 
	m_rgb[LAY_SM_BOTTOM][2] = 95;	//bottom solder mask cutouts DARK GREY
	m_rgb[LAY_PAD_THRU][0] =   0; 
	m_rgb[LAY_PAD_THRU][1] =   0; 
	m_rgb[LAY_PAD_THRU][2] = 255;		//thru-hole pads BLUE
	m_rgb[LAY_RAT_LINE][0] = 255; 
	m_rgb[LAY_RAT_LINE][1] = 0; 
	m_rgb[LAY_RAT_LINE][2] = 255;		//ratlines VIOLET
	m_rgb[LAY_TOP_COPPER][0] =   0; 
	m_rgb[LAY_TOP_COPPER][1] = 255; 
	m_rgb[LAY_TOP_COPPER][2] =   0;		//top copper GREEN
	m_rgb[LAY_BOTTOM_COPPER][0] = 255; 
	m_rgb[LAY_BOTTOM_COPPER][1] =   0; 
	m_rgb[LAY_BOTTOM_COPPER][2] =   0;	//bottom copper RED
	m_rgb[LAY_BOTTOM_COPPER+1][0] = 64; 
	m_rgb[LAY_BOTTOM_COPPER+1][1] = 128; 
	m_rgb[LAY_BOTTOM_COPPER+1][2] = 64;	
	m_rgb[LAY_BOTTOM_COPPER+2][0] = 128; // inner 1 
	m_rgb[LAY_BOTTOM_COPPER+2][1] = 64; 
	m_rgb[LAY_BOTTOM_COPPER+2][2] = 64;	
	m_rgb[LAY_BOTTOM_COPPER+3][0] = 64; // inner 2
	m_rgb[LAY_BOTTOM_COPPER+3][1] = 64; 
	m_rgb[LAY_BOTTOM_COPPER+3][2] = 128;	
	m_rgb[LAY_BOTTOM_COPPER+4][0] = 64; // inner 3
	m_rgb[LAY_BOTTOM_COPPER+4][1] = 64; 
	m_rgb[LAY_BOTTOM_COPPER+4][2] = 64;	
	m_rgb[LAY_BOTTOM_COPPER+5][0] = 64; // inner 5
	m_rgb[LAY_BOTTOM_COPPER+5][1] = 64; 
	m_rgb[LAY_BOTTOM_COPPER+5][2] = 64;	
	m_rgb[LAY_BOTTOM_COPPER+6][0] = 64; // inner 6 
	m_rgb[LAY_BOTTOM_COPPER+6][1] = 64; 
	m_rgb[LAY_BOTTOM_COPPER+6][2] = 64;	

	// now set layer colors and visibility
	for( int i=0; i<m_num_layers; i++ )
	{
		m_vis[i] = 1;
		m_dlist->SetLayerRGB( i, m_rgb[i][0], m_rgb[i][1], m_rgb[i][2] );
		m_dlist->SetLayerVisible( i, m_vis[i] );
	}

	// colors for footprint editor layers
	m_fp_num_layers = NUM_FP_LAYERS;
	m_fp_rgb[LAY_FP_SELECTION][0] = 255; 
	m_fp_rgb[LAY_FP_SELECTION][1] = 255; 
	m_fp_rgb[LAY_FP_SELECTION][2] = 255;		//selection WHITE
	m_fp_rgb[LAY_FP_BACKGND][0] = 0; 
	m_fp_rgb[LAY_FP_BACKGND][1] = 0; 
	m_fp_rgb[LAY_FP_BACKGND][2] = 0;			// background BLACK
	m_fp_rgb[LAY_FP_VISIBLE_GRID][0] = 99; 
	m_fp_rgb[LAY_FP_VISIBLE_GRID][1] = 99; 
	m_fp_rgb[LAY_FP_VISIBLE_GRID][2] = 99;	// visible grid GRAY 
	m_fp_rgb[LAY_FP_HILITE][0] = 255; 
	m_fp_rgb[LAY_FP_HILITE][1] = 255; 
	m_fp_rgb[LAY_FP_HILITE][2] = 255;		//highlight WHITE
	m_fp_rgb[LAY_FP_SILK_TOP][0] = 255; 
	m_fp_rgb[LAY_FP_SILK_TOP][1] = 128; 
	m_fp_rgb[LAY_FP_SILK_TOP][2] = 255;		//top silk
	m_fp_rgb[LAY_FP_SILK_BOTTOM][0] = 128; 
	m_fp_rgb[LAY_FP_SILK_BOTTOM][1] = 255; 
	m_fp_rgb[LAY_FP_SILK_BOTTOM][2] = 128;		//bot silk
	m_fp_rgb[LAY_FP_NOTES_T][0] = 128;
	m_fp_rgb[LAY_FP_NOTES_T][1] = 0;
	m_fp_rgb[LAY_FP_NOTES_T][2] = 255;
	m_fp_rgb[LAY_FP_NOTES_B][0] = 0;
	m_fp_rgb[LAY_FP_NOTES_B][1] = 128;
	m_fp_rgb[LAY_FP_NOTES_B][2] = 255;
	m_fp_rgb[LAY_FP_CENTROID][0] = 255; 
	m_fp_rgb[LAY_FP_CENTROID][1] = 255; 
	m_fp_rgb[LAY_FP_CENTROID][2] = 255;		//centroid WHITE
	m_fp_rgb[LAY_FP_DOT][0] = 255; 
	m_fp_rgb[LAY_FP_DOT][1] = 128; 
	m_fp_rgb[LAY_FP_DOT][2] =  64;			//adhesive dot ORANGE
	m_fp_rgb[LAY_FP_PAD_THRU][0] =   0; 
	m_fp_rgb[LAY_FP_PAD_THRU][1] =   0; 
	m_fp_rgb[LAY_FP_PAD_THRU][2] = 255;		//thru-hole pads BLUE
	m_fp_rgb[LAY_FP_TOP_COPPER][0] =   0; 
	m_fp_rgb[LAY_FP_TOP_COPPER][1] = 255; 
	m_fp_rgb[LAY_FP_TOP_COPPER][2] =   0;		//top copper GREEN
	m_fp_rgb[LAY_FP_INNER_COPPER][0] =  128; 
	m_fp_rgb[LAY_FP_INNER_COPPER][1] = 128; 
	m_fp_rgb[LAY_FP_INNER_COPPER][2] =  128;		//inner copper GREY
	m_fp_rgb[LAY_FP_BOTTOM_COPPER][0] = 255; 
	m_fp_rgb[LAY_FP_BOTTOM_COPPER][1] = 0; 
	m_fp_rgb[LAY_FP_BOTTOM_COPPER][2] = 0;		//bottom copper RED
	m_fp_rgb[LAY_FP_TOP_MASK][0] = 0; 
	m_fp_rgb[LAY_FP_TOP_MASK][1] = 127; 
	m_fp_rgb[LAY_FP_TOP_MASK][2] = 0;		//top mask DARK GREEN
	m_fp_rgb[LAY_FP_TOP_PASTE][0] = 0; 
	m_fp_rgb[LAY_FP_TOP_PASTE][1] = 127; 
	m_fp_rgb[LAY_FP_TOP_PASTE][2] = 0;		//top paste DARK GREEN
	m_fp_rgb[LAY_FP_BOTTOM_MASK][0] = 127; 
	m_fp_rgb[LAY_FP_BOTTOM_MASK][1] = 0; 
	m_fp_rgb[LAY_FP_BOTTOM_MASK][2] = 0;		//bottom mask DARK RED
	m_fp_rgb[LAY_FP_BOTTOM_PASTE][0] = 127; 
	m_fp_rgb[LAY_FP_BOTTOM_PASTE][1] = 0; 
	m_fp_rgb[LAY_FP_BOTTOM_PASTE][2] = 0;		//bottom paste DARK RED

	// now set footprint editor layer colors and visibility
	for( int i=0; i<m_fp_num_layers; i++ )
	{
		m_fp_vis[i] = 1;
		m_dlist_fp->SetLayerRGB( i, m_fp_rgb[i][0], m_fp_rgb[i][1], m_fp_rgb[i][2] );
		m_dlist_fp->SetLayerVisible( i, 1 );
	}

	// default visible grid spacing menu values (in NM)
	m_visible_grid.RemoveAll();
	m_visible_grid.Add( 100*NM_PER_MIL );
	m_visible_grid.Add( 125*NM_PER_MIL );
	m_visible_grid.Add( 200*NM_PER_MIL );	// default index = 2
	m_visible_grid.Add( 250*NM_PER_MIL );
	m_visible_grid.Add( 400*NM_PER_MIL );
	m_visible_grid.Add( 500*NM_PER_MIL );
	m_visible_grid.Add( 1000*NM_PER_MIL );
	m_visual_grid_spacing = 200*NM_PER_MIL;
	m_dlist->SetVisibleGrid( TRUE, m_visual_grid_spacing );

	// default placement grid spacing menu values (in NM)
	m_part_grid.RemoveAll();
	m_part_grid.Add( 10*NM_PER_MIL );
	m_part_grid.Add( 20*NM_PER_MIL );
	m_part_grid.Add( 25*NM_PER_MIL );
	m_part_grid.Add( 40*NM_PER_MIL );
	m_part_grid.Add( 50*NM_PER_MIL );		// default
	m_part_grid.Add( 100*NM_PER_MIL );
	m_part_grid.Add( 200*NM_PER_MIL );
	m_part_grid.Add( 250*NM_PER_MIL );
	m_part_grid.Add( 400*NM_PER_MIL );
	m_part_grid.Add( 500*NM_PER_MIL );
	m_part_grid.Add( 1000*NM_PER_MIL );
	m_part_grid_spacing = 50*NM_PER_MIL;

	// default routing grid spacing menu values (in NM)
	m_routing_grid.RemoveAll();
	m_routing_grid.Add( 1*NM_PER_MIL );
	m_routing_grid.Add( 2*NM_PER_MIL );
	m_routing_grid.Add( 2.5*NM_PER_MIL );
	m_routing_grid.Add( 3.333333333333*NM_PER_MIL );
	m_routing_grid.Add( 4*NM_PER_MIL );
	m_routing_grid.Add( 5*NM_PER_MIL );
	m_routing_grid.Add( 8.333333333333*NM_PER_MIL );
	m_routing_grid.Add( 10*NM_PER_MIL );	// default
	m_routing_grid.Add( 16.66666666666*NM_PER_MIL );
	m_routing_grid.Add( 20*NM_PER_MIL );
	m_routing_grid.Add( 25*NM_PER_MIL );
	m_routing_grid.Add( 40*NM_PER_MIL );
	m_routing_grid.Add( 50*NM_PER_MIL );
	m_routing_grid.Add( 100*NM_PER_MIL );
	m_routing_grid_spacing = 10*NM_PER_MIL;

	// footprint editor parameters 
	m_fp_units = MIL;

	// default footprint editor visible grid spacing menu values (in NM)
	m_fp_visible_grid.RemoveAll();
	m_fp_visible_grid.Add( 100*NM_PER_MIL );
	m_fp_visible_grid.Add( 125*NM_PER_MIL );
	m_fp_visible_grid.Add( 200*NM_PER_MIL );	
	m_fp_visible_grid.Add( 250*NM_PER_MIL );
	m_fp_visible_grid.Add( 400*NM_PER_MIL );
	m_fp_visual_grid_spacing = 200*NM_PER_MIL;

	// default footprint editor placement grid spacing menu values (in NM)
	m_fp_part_grid.RemoveAll();
	m_fp_part_grid.Add( 10*NM_PER_MIL );
	m_fp_part_grid.Add( 20*NM_PER_MIL );
	m_fp_part_grid.Add( 25*NM_PER_MIL );
	m_fp_part_grid.Add( 40*NM_PER_MIL );
	m_fp_part_grid.Add( 50*NM_PER_MIL );
	m_fp_part_grid.Add( 100*NM_PER_MIL );
	m_fp_part_grid.Add( 200*NM_PER_MIL );
	m_fp_part_grid.Add( 250*NM_PER_MIL );
	m_fp_part_grid.Add( 400*NM_PER_MIL );
	m_fp_part_grid.Add( 500*NM_PER_MIL );
	m_fp_part_grid.Add( 1000*NM_PER_MIL );
	m_fp_part_grid_spacing = 50*NM_PER_MIL;

	CMainFrame * frm = (CMainFrame*)AfxGetMainWnd();
	frm->m_wndMyToolBar.SetLists( &m_visible_grid, &m_part_grid, &m_routing_grid,
		m_visual_grid_spacing, m_part_grid_spacing, m_routing_grid_spacing, m_snap_angle, MIL );

	// default PCB parameters
	m_project_validated = FALSE;
	m_bSMT_copper_connect = FALSE;
	m_default_glue_w = 25*NM_PER_MIL;
	m_trace_w = 10*NM_PER_MIL;
	m_via_w = 28*NM_PER_MIL;
	m_via_hole_w = 14*NM_PER_MIL;
	m_nlist->SetWidths( abs(m_trace_w), abs(m_via_w), abs(m_via_hole_w) );
	//
	//
	// default cam parameters
	m_dsn_flags = 0;
	m_dsn_bounds_poly = 0;
	m_dsn_signals_poly = 0;
	for( int ii=0; ii<NUM_SHORTCUTS; ii++ )
		m_cam_shortcut[ii] = "";
	m_cam_full_path = "";
	m_ses_full_path = "";
	m_panel_fields[0] = m_panel_fields[1] = 10 * NM_PER_MM;
	m_panel_holes[0] = 2 * NM_PER_MM;
	m_panel_holes[1] = 4;
	m_panel_ref_count = 2;
	m_panel_reference = "none";
	m_panel_scribing = 0;
	m_panel_text[0] = m_panel_text[2] = "OnTop";
	m_panel_text[1] = m_panel_text[3] = "OnBot";
	m_panel_frame_for_paste.left = m_panel_frame_for_paste.right = m_panel_frame_for_paste.top = m_panel_frame_for_paste.bottom = 0;
	m_fill_clearance = 10 * NM_PER_MIL;
	m_mask_clearance = 8 * NM_PER_MIL;
	m_thermal_clearance = 8 * NM_PER_MIL; 
	m_thermal_width = 10 * NM_PER_MIL;
	m_min_silkscreen_stroke_wid = 5 * NM_PER_MIL;
	m_highlight_wid = 5 * NM_PER_MIL;
	m_pilot_diameter = 10 * NM_PER_MIL;
	m_cam_flags = GERBER_BOARD_OUTLINE;
	m_crop_flags = 0;
	m_cam_layers = 0xf00fff;	// default layers
	m_cam_units = MIL;
	m_cam_drill_file = 1;
	m_hole_clearance = 15*NM_PER_MIL;
	m_annular_ring_pins = 7*NM_PER_MIL;
	m_annular_ring_vias = 5*NM_PER_MIL;
	m_paste_shrink = 0;
	m_n_x = 1;
	m_n_y = 1;
	m_space_x = 0;
	m_space_y = 0;
	m_symmetric_x = m_symmetric_y = 0;

	// default DRC limits
	m_dr.bCheckUnrouted = FALSE;
	m_dr.trace_width = 10*NM_PER_MIL; 
	m_dr.pad_pad = 10*NM_PER_MIL; 
	m_dr.pad_trace = 10*NM_PER_MIL;
	m_dr.trace_trace = 10*NM_PER_MIL; 
	m_dr.hole_copper = 15*NM_PER_MIL; 
	m_dr.annular_ring_pins = 7*NM_PER_MIL;
	m_dr.annular_ring_vias = 5*NM_PER_MIL;
	m_dr.board_edge_copper = 25*NM_PER_MIL;
	m_dr.board_edge_hole = 25*NM_PER_MIL;
	m_dr.hole_hole = 25*NM_PER_MIL;
	m_dr.copper_copper = 10*NM_PER_MIL;

	// default trace widths (must be in ascending order)
	m_w.SetAtGrow( 0, 6*NM_PER_MIL );
	m_w.SetAtGrow( 1, 8*NM_PER_MIL );
	m_w.SetAtGrow( 2, 10*NM_PER_MIL );
	m_w.SetAtGrow( 3, 12*NM_PER_MIL );
	m_w.SetAtGrow( 4, 15*NM_PER_MIL );
	m_w.SetAtGrow( 5, 20*NM_PER_MIL );
	m_w.SetAtGrow( 6, 25*NM_PER_MIL );

	// default via widths
	m_v_w.SetAtGrow( 0, 24*NM_PER_MIL );
	m_v_w.SetAtGrow( 1, 24*NM_PER_MIL );
	m_v_w.SetAtGrow( 2, 24*NM_PER_MIL );
	m_v_w.SetAtGrow( 3, 24*NM_PER_MIL );
	m_v_w.SetAtGrow( 4, 30*NM_PER_MIL );
	m_v_w.SetAtGrow( 5, 30*NM_PER_MIL );
	m_v_w.SetAtGrow( 6, 40*NM_PER_MIL );

	// default via hole widths
	m_v_h_w.SetAtGrow( 0, 15*NM_PER_MIL );
	m_v_h_w.SetAtGrow( 1, 15*NM_PER_MIL );
	m_v_h_w.SetAtGrow( 2, 15*NM_PER_MIL );
	m_v_h_w.SetAtGrow( 3, 15*NM_PER_MIL );
	m_v_h_w.SetAtGrow( 4, 18*NM_PER_MIL );
	m_v_h_w.SetAtGrow( 5, 18*NM_PER_MIL );
	m_v_h_w.SetAtGrow( 6, 20*NM_PER_MIL );

	// netlist import options
	m_netlist_full_path = "";
	m_import_flags = IMPORT_PARTS | IMPORT_NETS | KEEP_TRACES | KEEP_STUBS | KEEP_AREAS;

	CFreePcbView * view = (CFreePcbView*)m_view;
	view->InitializeView();

	// now try to find global options file
	CStdioFile file;
	CString fn = m_app_dir + "\\default.cfg";
	if( !file.Open( fn, CFile::modeRead | CFile::typeText ) )
	{
		AfxMessageBox(G_LANGUAGE == 0 ? 
			"Unable to open global configuration file \"default.cfg\"\nUsing application defaults":
			"Невозможно открыть глобальный файл конфигурации «default.cfg», поэтому будут использоваться настройки приложения по умолчанию");
	}
	else
	{
		try
		{
			// read global default file options
			ReadOptions( &file, 1, TRUE );
			// make path to library folder and index libraries
			if( m_full_lib_dir.GetLength() == 0 )
			{
				char full[_MAX_PATH];
				CString fullpath = _fullpath( full, (LPCSTR)m_lib_dir, MAX_PATH );
				if( fullpath[fullpath.GetLength()-1] == '\\' )	
					fullpath = fullpath.Left(fullpath.GetLength()-1);
				m_full_lib_dir = fullpath;
			}
		}
		catch( CString * err_str )
		{
			*err_str = "CFreePcbDoc::InitializeNewProject()\n" + *err_str;
			AfxMessageBox(*err_str);
			delete err_str;
		}
	}
	m_plist->SetPinAnnularRing( m_annular_ring_pins );
	m_nlist->SetViaAnnularRing( m_annular_ring_vias );
	m_window_title = (CString)PROGRAM_CAP + (G_LANGUAGE == 0 ? "no project open" : "редактор печатных плат");
	CWnd* pMain = AfxGetMainWnd(); 
	pMain->SetWindowText(m_window_title);
}

// Call this function when the project is modified,
// or to clear the modified flags
//
void CFreePcbDoc::ProjectModified( BOOL flag, BOOL b_clear_redo )
{
	CWnd* pMain = AfxGetMainWnd();
	if( flag )
	{
		// set modified flag
		if( b_clear_redo && m_redo_list->m_num_items > 0 )
		{
			// can't redo after a new operation
			m_redo_list->Clear();
		}
		if( m_project_modified )
		{
			// flag already set
			m_project_modified_since_autosave = TRUE;
		}
		else
		{
			// set flags
			m_project_modified = TRUE;
			m_project_modified_since_autosave = TRUE;
			m_window_title = m_window_title + "*";
			pMain->SetWindowText( m_window_title );
		}
		m_project_validated = FALSE;
	}
	else
	{
		// clear flags
		m_project_modified = FALSE;
		m_project_modified_since_autosave = FALSE;
		int len = m_window_title.GetLength();
		if( len > 1 && m_window_title[len-1] == '*' )
		{
			m_window_title = m_window_title.Left(len-1);
			pMain->SetWindowText( m_window_title );
		}
		m_undo_list->Clear();
		m_redo_list->Clear();
	}
	// enable/disable menu items
	pMain->SetWindowText( m_window_title );
	CMenu* pMenu = pMain->GetMenu();
	CMenu* submenu = pMenu->GetSubMenu(1);	// "Edit" submenu
	if( m_undo_list->m_num_items == 0 )
		submenu->EnableMenuItem( ID_EDIT_UNDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );	
	else
		submenu->EnableMenuItem( ID_EDIT_UNDO, MF_BYCOMMAND | MF_ENABLED );	
	if( m_redo_list->m_num_items == 0 )
		submenu->EnableMenuItem( ID_EDIT_REDO, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );	
	else
		submenu->EnableMenuItem( ID_EDIT_REDO, MF_BYCOMMAND | MF_ENABLED );
	submenu = pMenu->GetSubMenu(3);	// "Project" submenu
	if( getbit( m_view->m_protected, PROTECT ) )
	{
		pMenu->EnableMenuItem( 6, MF_BYPOSITION | MF_DISABLED | MF_GRAYED );
		pMenu->EnableMenuItem( 7, MF_BYPOSITION | MF_DISABLED | MF_GRAYED );
		submenu->EnableMenuItem( ID_PROJECT_COMBINENETS, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
		submenu->EnableMenuItem( ID_PROJECT_COMBINEBOARD, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
		submenu->EnableMenuItem( ID_CHANNEL_DUPLICATION, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
	}
	else
	{
		if( m_project_open )
		{
			pMenu->EnableMenuItem( 6, MF_BYPOSITION | MF_ENABLED );
			pMenu->EnableMenuItem( 7, MF_BYPOSITION | MF_ENABLED );
		}
		submenu->EnableMenuItem( ID_PROJECT_COMBINENETS, MF_BYCOMMAND | MF_ENABLED );
		submenu->EnableMenuItem( ID_PROJECT_COMBINEBOARD, MF_BYCOMMAND | MF_ENABLED );
		submenu->EnableMenuItem( ID_CHANNEL_DUPLICATION, MF_BYCOMMAND | MF_ENABLED );
	}
	if( m_project_modified )
		submenu->EnableMenuItem( ID_PROTECTION, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED );
	else
		submenu->EnableMenuItem( ID_PROTECTION, MF_BYCOMMAND | MF_ENABLED );
	pMain->DrawMenuBar();
}

void CFreePcbDoc::SaveOptions()
{
	// now try to save global options file
	CString fn = m_app_dir + "\\" + "default.cfg";
	CStdioFile file;
	int err = file.Open( LPCSTR(fn), CFile::modeCreate | CFile::modeWrite, NULL );
	if( !err )
	{
		// error opening file
		CString mess;
		mess.Format(G_LANGUAGE == 0 ? "Unable to open file \"%s\"":"Невозможно открыть файл \"%s\"", fn);
		AfxMessageBox( mess );
		return;
	}
	else
	{
		// write 
		try
		{
			WriteOptions( &file, 1 );
			file.WriteString("[end]");
			file.Close();
		}
		catch( CString * err_str )
		{
			*err_str = "CFreePcbDoc::SaveOptions()\n" + *err_str;
			AfxMessageBox(*err_str);
			delete err_str;
		}
	}
}

void CFreePcbDoc::OnViewLayers()
{
	CDlgLayers dlg;
	CFreePcbView * view = (CFreePcbView*)m_view;
	dlg.Initialize( m_num_layers, m_vis, m_rgb, m_system_colors );
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		for( int i=0; i<m_num_layers; i++ )
		{
			m_dlist->SetLayerRGB( i, m_rgb[i][0], m_rgb[i][1], m_rgb[i][2] );
			m_dlist->SetLayerVisible( i, m_vis[i] );
		}
		m_system_colors = dlg.m_sys_clrs;
		view->m_left_pane_invalid = TRUE;	// force erase of left pane
		view->CancelSelection();
		view->Invalidate( FALSE );
		SaveOptions();
	}
}

void CFreePcbDoc::OnProjectPartlist()
{
	CDlgPartlist dlg;
	dlg.Initialize( m_plist, &m_footprint_cache_map, &m_footlibfoldermap, 
		m_units, m_dlg_log, (m_netlist_completed+(2*getbit(m_view->m_protected,PROTECT))), &m_part_search );
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		ResetUndoState();
		CFreePcbView * view = (CFreePcbView*)m_view;
		for( cpart * p = m_plist->GetFirstPart(); p; p = m_plist->GetNextPart(p) )
			if( p->utility )
			{
				id Id( ID_PART_DEF );
				view->NewSelect( p, &Id, 0, 0 );
			}
		if( view->m_sel_count )
		{
			view->SetCursorMode( CUR_GROUP_SELECTED );
			view->HighlightGroup();
		}
		if( m_vis[LAY_RAT_LINE] && !m_auto_ratline_disable )
			m_nlist->OptimizeConnections();
		ProjectModified( TRUE );
		view->SetDrawLayer( ENABLE_CHANGE_DRAW_LAYER );
		view->Invalidate( FALSE );
	}
}

void CFreePcbDoc::OnPartProperties()
{
	PartProperties();
	m_view->Invalidate( FALSE );
}
void CFreePcbDoc::PartProperties()
{
	enum{
		UTILITY = 2
	};
	if( m_view->m_sel_part == NULL )
		return;
	int mem_px = m_view->m_sel_part->x;
	int mem_py = m_view->m_sel_part->y;
	cpart * mp = m_view->m_sel_part;
	CShape sh;
	CString msh = "";
	if( m_view->m_sel_part->shape )
	{
		msh = mp->shape->m_name;
		sh.Copy( mp->shape );
	}			
	partlist_info pl;
	int ip = m_plist->ExportPartListInfo( &pl, m_view->m_sel_part );
	CDlgAddPart dlg;
	dlg.Initialize( &pl, ip, TRUE, FALSE, FALSE, 0, (m_netlist_completed+(2*getbit(m_view->m_protected,PROTECT))), &m_footprint_cache_map, 
		&m_footlibfoldermap, m_units, m_dlg_log, &m_part_search );
	int ret = dlg.DoModal();
	if (ret == IDOK)
	{
		BOOL bNEW_EVENT = TRUE;
		m_view->SaveUndoInfoForGroup(CFreePcbView::UNDO_GROUP_MODIFY, m_undo_list);
		m_full_lib_dir = *m_footlibfoldermap.GetDefaultFolder();
		cpart* find = NULL;
		CString nRef;
		m_view->m_Doc->m_plist->MarkAllParts(0);
		do
		{
			find = NULL;
			for (int ipl = pl.GetSize() - 1; ipl >= 0; ipl--)
			{
				if (pl[ipl].part == NULL)
					continue;
				if (pl[ipl].part->utility == UTILITY)
					continue;
				if (pl[ipl].ref_des.Compare(pl[ipl].part->ref_des))
				{
					find = pl[ipl].part;
					nRef = pl[ipl].ref_des;
					// test on ref match 
					CString find_str = pl[ipl].ref_des;
					cpart* gP;
					BOOL REP;
					do {
						gP = m_view->m_Doc->m_plist->GetPart(find_str);

						//break if null
						if (!gP)
							break;

						//break if repeat
						if (gP->utility == UTILITY)
							break;

						REP = 0;
						for (int f = pl.GetSize() - 1; f >= 0; f--)
						{
							if (pl[f].part == NULL)
								continue;
							if (pl[f].part->utility == UTILITY)
								continue;
							if (gP->ref_des.Compare(pl[f].part->ref_des) == 0)
							{
								find_str = pl[f].ref_des;
								find = gP;
								nRef = find_str;
								REP = TRUE;
								break;
							}
						}
					} while (REP);
					// end test
					break;
				}
			}
			if (find)
			{
				if (m_netlist_completed)
				{
					if (m_nlist->PartCheckConnect(find))
						if (find->shape->GetNumPins() > 1)
						{
							CString str = " Warning, netlist is protected.\n It is impossible to change the part ref.";
							CDlgMyMessageBox dlg;
							dlg.Initialize(str);
							dlg.DoModal();
							m_view->g_bShow_nl_lock_Warning = !dlg.bDontShowBoxState;
							return;
						}
				}
				id pid(ID_PART_DEF);
				m_view->NewSelect(find, &pid, 0, 0);
				m_view->SaveUndoInfoForPart(find, CPartList::UNDO_PART_MODIFY, &nRef, bNEW_EVENT, m_undo_list);
				find->utility = UTILITY;
			}
		} while (find);
		//
		// see if ref_des has changed
		m_plist->ImportPartListInfo(&pl, 0);
		if (m_view->m_sel_part->shape)
		{
			if (m_view->m_sel_part->shape->m_name.Compare(msh) == 0)
				if (m_view->m_sel_part->shape->Compare(&sh) == 0)
					ResetUndoState(); // footprint was replaced
			m_view->m_sel_part->shape->m_package = dlg.m_package;
		}
		if (m_view->m_sel_part->ref_des.Left(3) == "VIA")
		{
			m_view->m_sel_part->m_ref_vis = 0;
			m_view->m_sel_part->m_ref_size = 0;
			m_view->m_sel_part->m_ref_w = 0;
			m_plist->DrawPart(m_view->m_sel_part);
		}
		m_dlist->CancelHighLight();
		m_view->HighlightGroup();
		if( dlg.GetDragFlag() )
			ASSERT(0);	// not allowed
		else
		{
			if( m_vis[LAY_RAT_LINE] && !m_auto_ratline_disable )
				m_nlist->OptimizeConnections();
			ProjectModified( TRUE );
		}
	}
	if( abs(mp->x-mem_px) > 10 ||
		abs(mp->y-mem_py) > 10 )
	{
		int iM = mp->m_merge;
		if( iM >= 0 && msh.Compare(mp->shape->m_name) == 0 )
		{
			CString ps;
			ps.Format(G_LANGUAGE == 0 ? 
				"This part is connected to other objects through the \"MERGE\" property. Move all objects of the group %s?":
				"Эта деталь связана с другими объектами через свойство \"СЛИЯНИЕ\". Переместить все объекты группы %s?", m_mlist->GetMerge(iM));
			if( AfxMessageBox( ps, MB_YESNO ) == IDYES )
			{
				int gx = mp->x;
				int gy = mp->y;
				m_view->CancelSelection();
				m_view->NewSelectM(NULL, iM);
				m_view->MoveGroup( gx-mem_px, gy-mem_py, 0 );
				m_plist->Move( mp, gx, gy, mp->angle, mp->side );
				m_nlist->PartMoved( mp, 0 );
				m_dlist->CancelHighLight();
				m_view->HighlightGroup();
			}
		}
	}
}

void CFreePcbDoc::FileExport( CString str )
{
	CStdioFile file;
	if( !file.Open( str, CFile::modeWrite | CFile::modeCreate ) )
	{
		str.Format(G_LANGUAGE == 0 ? "Unable to open file %s":"Невозможно открыть файл %s", str);
		AfxMessageBox( str );
	}
	else
	{
		partlist_info pl;
		netlist_info nl;
		m_plist->ExportPartListInfo( &pl, NULL );
		m_nlist->ExportNetListInfo( &nl );
		int flags = 0;
		/*setbit( flags, EXPORT_PARTS );
		setbit( flags, EXPORT_NETS );
		setbit( flags, EXPORT_VALUES );*/
		flags |= EXPORT_PARTS;
		flags |= EXPORT_NETS;
		flags |= EXPORT_VALUES;
		ExportPADSPCBNetlist( &file, flags, &pl, &nl );
		file.Close();
	}
}

void CFreePcbDoc::OnFileExport()
{
	// force old-style file dialog by setting size of OPENFILENAME struct
	//
	CString filename = RunFileDialog( 0, "net" ); 
	if ( filename.GetLength() )
	{
		FileExport( filename );
	}
}

void CFreePcbDoc::OnFileReloadNetlist()
{
	FileImportNetlist( &m_netlist_full_path );
	if( getbit( m_view->m_protected, CFreePcbDoc::AUTOPROTECT_NETLIST ) )
		m_netlist_completed = 1;
}
void CFreePcbDoc::OnFileImportNetlist()
{
	int save_check = m_netlist_completed;
	if( m_netlist_completed )
	{
		int ret1;
		if( getbit( m_view->m_protected, CFreePcbDoc::AUTOPROTECT_NETLIST ) )
			ret1 = IDYES;
		else
			ret1 = AfxMessageBox(G_LANGUAGE == 0 ? 
				"Netlist is locked! Do you want to continue despite this?":
				"Список эл.цепей заблокирован в настройках проекта! Хотите продолжить, несмотря на это?", MB_YESNO);
		if( ret1 != IDYES )
			return;
		m_netlist_completed = 0;
	}
	FileImportNetlist( NULL );
	if( getbit( m_view->m_protected, CFreePcbDoc::AUTOPROTECT_NETLIST ) )
		m_netlist_completed = 1;
	else 
		m_netlist_completed = save_check;
}
void CFreePcbDoc::FileImportNetlist( CString * filename )
{
	static BOOL bCompleted = TRUE;
	if( bCompleted == 0 )
		return;
	bCompleted = 0;
	enum { FREEPCB, PADSPCB }; 
	// force old-style file dialog by setting size of OPENFILENAME struct
	/*CMyFileDialog dlg( TRUE, NULL, (LPCTSTR)m_netlist_full_path, OFN_HIDEREADONLY | OFN_EXPLORER, 
		"All Files (*.*)|*.*||", NULL, 0 );
	dlg.SetTemplate(( IDD_IMPORT, IDD_IMPORT );*/							// err in windows10 
	CWnd * WND = theApp.GetMainWnd();
	CString file_str = "";
	if( filename == NULL )
	{
		CStdioFile dlg_path;
		int ok_path = dlg_path.Open( LPCSTR(m_app_dir+"\\VCL_Dialog\\net_imp"), CFile::modeCreate | CFile::modeWrite );
		if( ok_path )
		{
			CString szFavorite_path = m_pcb_full_path.Left(m_pcb_full_path.ReverseFind('\\'));
			dlg_path.WriteString( szFavorite_path + freeasy_netlist );
			dlg_path.Close();
		}
		file_str = RunFileDialog( 1, "net" ); 
		filename = &file_str;
	}
	else
	{
		CString temp = m_pcb_filename + ".net";
		int rf = m_pcb_full_path.ReverseFind('\\');
		if( rf > 0 )
			temp = m_pcb_full_path.Left(rf) + freeasy_netlist + m_pcb_filename + ".net";
		if( filename->GetLength() == 0 )
			*filename = temp;
		if( filename->Right( temp.GetLength() ) != temp )
		{
			int ret1 = AfxMessageBox(G_LANGUAGE == 0 ? 
				("Do you want to open the file " + (*filename) + "?"):
				("Вы хотите открыть файл " + (*filename) + "?"), MB_YESNO);
			if( ret1 == IDNO )
			{
				bCompleted = TRUE;
				return;
			}
		}
	}
	if ( filename->GetLength() )
	{ 
		CStdioFile m_file;
		CString messg = filename->Left(filename->GetLength()-3) + "txt";
		if( filename->Compare( messg ) )
		{
			int ne = m_file.Open( LPCSTR(messg), CFile::modeRead );
			if( ne )
			{
				CString in_str;
				m_file.ReadString( in_str );
				m_file.Close();
				if( in_str.GetLength() )
					if( in_str.Left(in_str.GetLength()) != NETLIST_WARNING &&
						in_str.Left(in_str.GetLength()) != NETLIST_UPDATED )
					{
						AfxMessageBox( in_str, MB_ICONERROR );
						bCompleted = TRUE;
						return;
					}
			}
		}
		CStdioFile file;
		if( !file.Open( *filename, CFile::modeRead ) )
		{
			AfxMessageBox(G_LANGUAGE == 0 ? ("Unable to open file * "+(*filename)):("Невозможно открыть файл * " + (*filename)) );
		}
		else
		{
			if( m_project_modified )
			{
				if( AfxMessageBox(G_LANGUAGE == 0 ? 
					"This option has no undo action. Want to save your project before importing?":
					"Эта опция не имеет отмены действия. Хотите сохранить проект перед импортом?", MB_ICONQUESTION | MB_YESNO) == IDYES)
					OnFileSave();
			}
			ResetUndoState();	
			m_view->CancelSelection();
			ProjectModified( TRUE ); // !!!
			// write info warning
			m_dlg_log->Clear();
			m_dlg_log->ShowWindow( SW_SHOW );
			m_dlg_log->UpdateWindow();
			m_dlg_log->BringWindowToTop();
			//
			partlist_info pl;
			netlist_info nl;
			m_netlist_full_path = *filename;	// save path for next time	
			m_import_flags |= IMPORT_FROM_NETLIST_FILE;
			m_import_flags |= IMPORT_PARTS;
			m_import_flags |= IMPORT_NETS;
			///if( m_plist->GetFirstPart() == NULL || file_str.GetLength() )
			{
				// there are parts and/or nets in project 
				CDlgImportOptions dlg_options;
				dlg_options.Initialize( m_import_flags );
				int ret = dlg_options.DoModal();
				if( ret == IDCANCEL )
				{
					file.Close();
					bCompleted = TRUE;
					return;	
				}
				m_import_flags = dlg_options.m_flags;

				// update library indexes
				if( m_import_flags & UPDATE_LIB_INDEX )
				{
					CString * last_folder_path = m_footlibfoldermap.GetLastFolder();
					CFootLibFolder * m_folder = m_footlibfoldermap.GetFolder( last_folder_path, m_dlg_log );
					if( m_folder )
						m_folder->IndexAllLibs( last_folder_path, m_dlg_log );
				}
			}
			m_renumbering.RemoveAll(); //remove renumber list if project is empty
			CString rnmb_name="";
			if( m_plist->GetFirstPart() != NULL || m_nlist->m_map.GetCount() != 0 )
			{		
				// reading rnmb file
				CStdioFile rnmb;
				int ifo = filename->ReverseFind('.');
				rnmb_name = filename->Left(ifo) + ".rnmb";
				// loading renumbering file
				int ok = rnmb.Open( rnmb_name, CFile::modeRead, NULL );
				if( ok )
				{
					CString in_str;
					while( rnmb.ReadString( in_str ) )
						if( in_str.GetLength() > 5 )
							m_renumbering.Add(in_str);
					rnmb.Close();
				}
			}	
			// SAVE_BEFORE_IMPORT
			if( m_import_flags & SAVE_BEFORE_IMPORT )
			{
				// save project
				OnFileSaveBeforeImport();
			}
			// write info warning
			m_dlg_log->UpdateWindow();
			m_dlg_log->BringWindowToTop();

			CString instr = ""; // empty ! 
			int err = m_file.Open( LPCSTR(messg), CFile::modeRead );
			{
				if( err )
					m_file.ReadString( instr );
				if( instr.Left(instr.GetLength()) == NETLIST_WARNING )
				{
					if( m_renumbering.GetSize() )
						AfxMessageBox(G_LANGUAGE == 0 ? 
							"File of renumbering is now ignored because repeated renaming is invalid":
							"Файл перенумерации теперь проигнорируется, так как повторное переименование заведомо ошибочно", MB_ICONINFORMATION);
					m_renumbering.RemoveAll();
				}
				else if( instr.Left(instr.GetLength()) == NETLIST_UPDATED || err == 0 )
				{
					if( m_renumbering.GetSize() && m_plist->GetFirstPart() != NULL )
					{
						// open txt
						CopyFile( rnmb_name, rnmb_name+".txt", 0 );
						ShellExecute( NULL, "open", (rnmb_name+".txt"), NULL, (rnmb_name+".txt"), SW_SHOWNORMAL);
						int rnmb_ok = AfxMessageBox(G_LANGUAGE == 0 ? 
							"The parts renumbering file found. Want to rename project part numbers?":
							"Найден файл перенумерации деталей. Хотите переименовать номера деталей проекта?", MB_YESNO | MB_ICONQUESTION);
						CopyFile( rnmb_name+".txt", rnmb_name, 0 );
						DeleteFile( rnmb_name+".txt" );
						if( rnmb_ok == IDYES )
						{
							// reading rnmb file
							m_renumbering.RemoveAll(); //reload renumber list because it my have been modified by users
							{		
								// reading rnmb file
								CStdioFile rnmb;

								// loading renumbering file
								int ok = rnmb.Open( rnmb_name, CFile::modeRead, NULL );
								if( ok )
								{
									CString in_str;
									while( rnmb.ReadString( in_str ) )
										if( in_str.GetLength() > 5 )
											m_renumbering.Add(in_str);
									rnmb.Close();
								}
							}
							CString key;
							CArray<CString> arr;
							int MAX_ITERs = 20;
							for( int ir=0; ir<m_renumbering.GetSize(); ir++ )
							{
								ParseKeyString(&m_renumbering.GetAt(ir),&key,&arr);	

								// for multi-graphic parts
								int dot = key.Find(".");
								if( dot == -1 )
									dot = key.Find("-");
								if( dot > 0 )
									key = key.Left(dot);
								//
								CString newref = arr.GetAt(1);

								// for multi-graphic parts
								dot = newref.Find(".");
								if( dot == -1 )
									dot = newref.Find("-");
								if( dot > 0 )
									newref = newref.Left(dot);
								//
								CString sERROR = G_LANGUAGE == 0 ? ("Unable to rename part "+key+" to "+newref):("Невозможно переименовать деталь " + key + " в " + newref);
								int iter = 0;
								for( cpart * p=m_plist->GetPart(key); iter<MAX_ITERs;  )
								{
									iter++;
									if(p)
									{
										for( int iadd=0; iadd<iter; iadd++ )
											newref += "#";// special character to avoid duplication when renaming
										cpart * p2 = m_plist->GetPart(newref);
										if( p2 == NULL )
										{
											CString addl;
											addl.Format( "  Rename part %s\r\n", p->ref_des );
											m_dlg_log->AddLine(addl);
											m_dlg_log->UpdateWindow();
											p->ref_des = newref;
											int d = m_nlist->PartRefChanged(&key,&newref);
											if(d)
												AfxMessageBox(sERROR,MB_ICONERROR);
										}
										else
											AfxMessageBox(sERROR,MB_ICONERROR);
										break;
									}
									else
									{
										key += "#";// special character to avoid duplication when renaming
										p = m_plist->GetPart(key);
									}
								}
							}
							for( cpart * p=m_plist->GetFirstPart(); p; p=m_plist->GetNextPart(p) )
							{
								CString _old = p->ref_des;
								CString _new = p->ref_des;
								while( _new.Right(1) == "#" )
									_new.Delete( _new.GetLength()-1 );
								if( _old.Compare(_new) )
								{
									CString addl;
									addl.Format( "  Rename part %s to %s\r\n", p->ref_des, _new );
									//m_dlg_log->AddLine(addl);
									m_dlg_log->UpdateWindow();
									int d = 0;
									cpart * found = m_plist->GetPart( _new );
									if( found )
									{
										CString rename = found->ref_des + "?";
										d = m_nlist->PartRefChanged( &found->ref_des, &rename );
										if( d == 0 )
											found->ref_des = rename;
									}
									if( d == 0 )
										d = m_nlist->PartRefChanged( &_old, &_new );
									if(d)
										AfxMessageBox(G_LANGUAGE == 0 ? 
											"Warning! Duplication of " + _new + " reference designation rejected":
											"Внимание! Дублирование обозначения " + _new + " отклонено", MB_ICONERROR);
									else
										p->ref_des = _new;
								}
							}
						}
					}
					else
					{
						// DEBUG
						//AfxMessageBox( "Rename file is empty", MB_ICONINFORMATION );
					}
				}
				else if( m_renumbering.GetSize() )
				{
					// DEBUG
					//AfxMessageBox( "Error. Message does not meet the requirements\nmessage: \n\t"+instr, MB_ICONERROR );
				}
				if( err )
					m_file.Close();
			}	
			//
			// Change message AFTER file save ! (and not before)
			if( instr.GetLength() == 0 || instr.Left(instr.GetLength() ) == NETLIST_UPDATED )
			{
				err = m_file.Open( LPCSTR(messg), CFile::modeCreate | CFile::modeWrite, NULL );
				if( err )
				{
					m_file.WriteString( NETLIST_WARNING );
					m_file.Close();
				}
			}
			// show log dialog
			CWnd * WND = AfxGetMainWnd();
			if( WND )
				SetForegroundWindow( WND->GetSafeHwnd() );
			m_dlg_log->ShowWindow( SW_SHOW );
			m_dlg_log->BringWindowToTop();
			m_dlg_log->UpdateWindow();

			// import the netlist file
			CString line;
			//int m_format = PADSPCB;
			//if( m_format == PADSPCB )
			{
				line.Format( "Reading netlist file \"%s\":\r\n", m_netlist_full_path ); 
				m_dlg_log->AddLine( line );
				int err = ImportPADSPCBNetlist( &file, m_import_flags, &pl, &nl );
				if( err == NOT_PADSPCB_FILE )
				{
					m_dlg_log->ShowWindow( SW_HIDE );
					CString mess = "WARNING: This does not appear to be a legal PADS-PCB netlist file\n";
					mess += "It does not contain the string \"*PADS-PCB*\" in the first few lines\n";
					if (G_LANGUAGE)
					{
						mess = "ВНИМАНИЕ: это, похоже, недопустимый файл списка соединений PADS-PCB. ";
						mess += "Он не содержит строку \"*PADS-PCB*\" в первых нескольких строках\n";
					}
					int ret = AfxMessageBox( mess, MB_OK );
					bCompleted = TRUE;
					return;
				}
			}
			if( m_import_flags & IMPORT_PARTS )
			{
				line = "\r\nImporting parts into project:\r\n";
				m_dlg_log->AddLine( line );
				m_plist->ImportPartListInfo( &pl, m_import_flags, m_dlg_log );
			}
			if( m_import_flags & IMPORT_NETS )
			{
				CNetList old_nlist( NULL, m_plist ); //ok
				old_nlist.Copy( m_nlist );
				line = "\r\nImporting nets into project:\r\n";
				m_dlg_log->AddLine( line );
				m_nlist->ImportNetListInfo( &nl, m_import_flags, m_dlg_log, 0, 0, 0 );
				line = "\r\nMoving traces and copper areas whose nets have changed:\r\n";
				m_dlg_log->AddLine( line );
				m_nlist->RestoreConnectionsAndAreas( &old_nlist, m_import_flags, m_dlg_log );
				old_nlist.SetPartList( NULL );
				// rehook all parts to nets after destroying old_nlist
				for( cnet * net=m_nlist->GetFirstNet(); net; net=m_nlist->GetNextNet(/*LABEL*/) )
					m_nlist->RehookPartsToNet( net );
			}
			// clean up
			CString str = "\r\n";
			m_nlist->CleanUpAllConnections( &str );
			m_dlg_log->AddLine( str );
			line = "\r\n************** DONE ****************\r\n";
			m_dlg_log->AddLine( line );
			// finish up
			m_nlist->OptimizeConnections( FALSE );
			if( filename == &file_str )
				m_view->OnViewAllElements();
			//
			m_view->Invalidate( FALSE );
			// make sure log is visible
			m_dlg_log->ShowWindow( SW_SHOW );
			m_dlg_log->BringWindowToTop();
			m_dlg_log->UpdateWindow();
		}
	}
	bCompleted = TRUE;
}

int GetSessionLayer( CString * ses_str )
{
	if( *ses_str == "Top" )
		return LAY_TOP_COPPER;
	else if( *ses_str == "Bottom" )
		return LAY_BOTTOM_COPPER;
	else if( ses_str->Left(6) == "Inner_" )
	{
		return( LAY_BOTTOM_COPPER + my_atoi( &(ses_str->Right(1)) ) );
	}
	return -1;
}

// import session file from autorouter
//
void CFreePcbDoc::ImportSessionFile( CString * filepath, CDlgLog * log, BOOL bVerbose )
{
	// process session file
	enum STATE {	// state machine, sub-states indented
	IDLE,
	  PLACEMENT,
	    COMPONENT,
	  ROUTES,
	    PARSER,
	    LIBRARY_OUT,
	      PADSTACK,
	        SHAPE,
	    NETWORK_OUT,
	      NET,
	        VIA,
	        WIRE,
	          PATH
	};
	#define ENDSTATE (field[0] == ")")

	CStdioFile file;
	if( !file.Open( *filepath, CFile::modeRead ) )
	{
		CString mess;
		mess.Format(G_LANGUAGE == 0 ? "Unable to open session file \"%s\"":"Невозможно открыть файл сеанса \"%s\"", filepath);
		if( log )
			log->AddLine( mess + "\r\n" );
		else
			AfxMessageBox( mess );
		return;
	}
	CArray<CString> field;
	CString instr, units_str, mult_str, footprint_name;
	int mult = 254; // default = 0.01 mil in nm.
	CString net_name, layer_str, width_str, via_name, via_x_str, via_y_str;
	BOOL bNewViaName = FALSE;
	CArray<cnode> nodes;	// array of nodes in net
	CArray<cpath> paths;	// array of paths in net
	CMapStringToPtr via_map;
	STATE state = IDLE;
	while( file.ReadString( instr ) )
	{
		instr.Trim();
		int nf = ParseStringFields( &instr, &field );
		if( nf )
		{
			// IDLE
			if( state == IDLE )
			{
				if( field[0] == "(placement" )
					state = PLACEMENT;
				else if( field[0] == "(routes" )
					state = ROUTES;
			}
			// IDLE -> PLACEMENT
			else if( state == PLACEMENT )
			{
				if( ENDSTATE )
					state = IDLE;
				else if( field[0] == "(component" )
				{
					state = COMPONENT;
					footprint_name = field[1];
				}
				else if( field[0] == "(resolution" )
				{
					units_str = field[1];
					mult_str = field[2];
					if( units_str == "mil" )
					{
						mult = my_atoi( &mult_str );
						mult = 25400/mult;
					}
					else
						ASSERT(0);
				}
			}
			// IDLE -> PLACEMENT -> COMPONENT
			else if( state == COMPONENT )
			{
				if( ENDSTATE )
					state = PLACEMENT;
				else if( field[0] == "(place" )
				{
				}
			}
			// IDLE -> ROUTES
			else if( state == ROUTES )
			{
				if( ENDSTATE )
					state = IDLE;
				else if( field[0] == "(resolution" )
				{
					units_str = field[1];
					mult_str = field[2];
					if( units_str == "mil" )
					{
						mult = my_atoi( &mult_str );
						mult = 25400/mult;
					}
					else
						ASSERT(0);
				}
				else if( field[0] == "(parser" )
					state = PARSER;
				else if( field[0] == "(library_out" )
					state = LIBRARY_OUT;
				else if( field[0] == "(network_out" )
					state = NETWORK_OUT;
			}
			// IDLE -> ROUTES -> PARSER
			else if( state == PARSER )
			{
				if( ENDSTATE )
					state = ROUTES;
			}
			// IDLE -> ROUTES -> LIBRARY_OUT
			else if( state == LIBRARY_OUT )
			{
				if( ENDSTATE )
					state = ROUTES;
				else if( field[0] == "(padstack" )
				{
					state = PADSTACK;
					via_name = field[1];
					bNewViaName = TRUE;
				}
			}
			// IDLE -> ROUTES -> LIBRARY_OUT -> PADSTACK
			else if( state == PADSTACK )
			{
				if( ENDSTATE )
					state = LIBRARY_OUT;
				else if( field[0] == "(shape" )
					state = SHAPE;
			}
			// IDLE -> ROUTES -> LIBRARY_OUT -> PADSTACK -> SHAPE
			else if( state == SHAPE )
			{
				if( ENDSTATE )
					state = PADSTACK;
				else if( field[0] == "(circle" && bNewViaName )
				{
					// add via definition to via_map
					CString via_w_str = field[2];
					int via_w = mult * my_atoi( &via_w_str );
					via_map.SetAt( via_name, (void*)via_w );
					bNewViaName = FALSE;
				}
			}
			// IDLE -> ROUTES -> NETWORK_OUT
			else if( state == NETWORK_OUT )
			{
				if( ENDSTATE )
					state = ROUTES;
				else if( field[0] == "(net" )
				{
					state = NET;
					net_name = field[1];
					nodes.SetSize(0);
					paths.SetSize(0);
				}
			}
			// IDLE -> ROUTES -> NETWORK_OUT -> NET
			else if( state == NET )
			{
				if( ENDSTATE )
				{
					// end of data for this net, route project
					m_nlist->ImportNetRouting( &net_name, &nodes, &paths, mult, log, bVerbose );
					state = NETWORK_OUT;
				}
				else if( field[0] == "(via" )
				{
					// data for a via
					state = VIA;
					via_name = field[1];
					void * ptr;
					BOOL bOK = via_map.Lookup( via_name, ptr );
					if( bOK )
					{
						via_x_str = field[2];
						via_y_str = field[3];
						int inode = nodes.GetSize();
						nodes.SetSize(inode+1);
						nodes[inode].type = NVIA;
						nodes[inode].x = mult * my_atoi( &via_x_str );
						nodes[inode].y = mult * my_atoi( &via_y_str );
						nodes[inode].layer = LAY_PAD_THRU;
						nodes[inode].via_w = (int)ptr;
						nodes[inode].bUsed = FALSE;
					}
					else
						ASSERT(0);
				}
				else if( field[0] == "(wire" )
				{
					state = WIRE;
				}
			}
			// IDLE -> ROUTES -> NETWORK_OUT -> NET -> VIA
			else if( state == VIA )
			{
				if( ENDSTATE )
					state = NET;
			}
			// IDLE -> ROUTES -> NETWORK_OUT -> NET -> WIRE
			else if( state == WIRE )
			{
				if( ENDSTATE )
					state = NET;
				else if( field[0] == "(path" )
				{
					// path data
					state = PATH;
					layer_str = field[1];
					width_str = field[2];
					int ipath = paths.GetSize();
					paths.SetSize( ipath+1 );
					paths[ipath].layer = GetSessionLayer( &layer_str );
					paths[ipath].width = mult * my_atoi( &width_str );
					paths[ipath].n_used = 0;
				}
			}
			// IDLE -> ROUTES -> NETWORK_OUT -> NET -> WIRE -> PATH
			else if( state == PATH )
			{
				if( ENDSTATE )
					state = WIRE;
				else
				{
					// path point data
					CString x_str = field[0];
					CString y_str = field[1];
					int ipath = paths.GetSize()-1;
					int ipt = paths[ipath].pt.GetSize();
					paths[ipath].pt.SetSize( ipt+1 );
					paths[ipath].pt[ipt].x = mult * my_atoi( &x_str );;
					paths[ipath].pt[ipt].y = mult * my_atoi( &y_str );;
					paths[ipath].pt[ipt].inode = -1;
				}
			}
		}
	}
	file.Close();
}

// import netlist 
// enter with file already open
//
int CFreePcbDoc::ImportNetlist( CStdioFile * file, UINT flags, 
							   partlist_info * pl, netlist_info * nl )
{
	CString instr;
	int err_flags = 0;
	int line = 0;
	BOOL not_eof;

	// find next section
	not_eof = file->ReadString( instr );
	line++;
	instr.Trim();
	while( 1 )
	{
		if( instr == "[parts]" && pl && (flags & IMPORT_PARTS) )
		{
			// read parts
			int ipart = 0;
			BOOL parts_section = FALSE;
			while( 1 )
			{
				not_eof = file->ReadString( instr );
				if( !not_eof )
				{
					// end of file
					file->Close();
					return err_flags;
				}
				line++;
				instr.Trim();
				if( instr[0] == '[' )
				{
					// next section
					break;
				}
				else if( instr.GetLength() && instr[0] != '/' )
				{
					// get ref prefix, ref number and shape
					pl->SetSize( ipart+1 );
					CString ref_str( mystrtok( instr, " \t" ) );
					CString shape_str( mystrtok( NULL, "\n\r" ) );
					shape_str.Trim();
					// find footprint, get from library if necessary
					CShape * s = GetFootprintPtr( shape_str );
					// add part to partlist_info
					(*pl)[ipart].part = NULL;
					(*pl)[ipart].ref_des = ref_str;
					if( s )
					{
						(*pl)[ipart].ref_size = s->m_ref_size;
						(*pl)[ipart].ref_width = s->m_ref_w;
					}
					else
					{
						(*pl)[ipart].ref_size = 0;
						(*pl)[ipart].ref_width = 0;
					}
					(*pl)[ipart].shape = s;
					(*pl)[ipart].x = 0;
					(*pl)[ipart].y = 0;
					(*pl)[ipart].angle = 0;
					(*pl)[ipart].side = 0;
					if( !s )
						err_flags |= FOOTPRINTS_NOT_FOUND;
					ipart++;
				}
			}
		}
		else if( instr == "[nets]" && nl && (flags & IMPORT_NETS) )
		{
			// read nets
			cnet * net = 0;
			int num_pins = 0;
			while( 1 )
			{
				not_eof = file->ReadString( instr );
				if( !not_eof )
				{
					// end of file
					file->Close();
					return err_flags;
				}
				line++;
				instr.Trim();
				if( instr[0] == '[' )
				{
					// next section
					break;
				}
				else if( instr.GetLength() && instr[0] != '/' )
				{
					int delim_pos;
					if( (delim_pos = instr.Find( ":", 0 )) != -1 )
					{
						// new net, get net name
						int inet = nl->GetSize();
						nl->SetSize( inet+1 );
						CString net_name( mystrtok( instr, ":" ) );
						net_name.Trim();
						if( net_name.GetLength() )
						{
							// add new net
							(*nl)[inet].name = net_name;
							(*nl)[inet].net = NULL;
							(*nl)[inet].modified = TRUE;
							(*nl)[inet].deleted = FALSE;
							(*nl)[inet].visible = TRUE;
							(*nl)[inet].w = 0;
							(*nl)[inet].v_w = 0;
							(*nl)[inet].v_h_w = 0;
							instr = instr.Right( instr.GetLength()-delim_pos-1 );
							num_pins = 0;
						}
						// add pins to net
						char * pin = mystrtok( instr, " \t\n\r" );
						while( pin )
						{
							CString pin_cstr( pin );
							if( pin_cstr.GetLength() > 3 )
							{
								int dot = pin_cstr.Find( ".", 0 );
								if( dot > 0 && dot < (pin_cstr.GetLength()-1) )
								{
									CString ref_des = pin_cstr.Left( dot );
									CString pin_num_cstr = pin_cstr.Right( pin_cstr.GetLength()-dot-1 );
									(*nl)[inet].ref_des.Add( ref_des );
									(*nl)[inet].pin_name.Add( pin_num_cstr );
#if 0	// TODO: check for illegal pin names
									}
									else
									{
										// illegal pin number for part
										CString mess;
										mess.Format(G_LANGUAGE == 0 ? 
											"Error in line %d of netlist file. Illegal pin number \"%s\"":
											"Ошибка в строке %d файла списка эл.цепей. Недопустимый номер контакта \"%s\"",
											line, pin_cstr );
										AfxMessageBox( mess );
										break;
									}
#endif
								}
								else
								{
									// illegal string
									break;
								}
							}
							else if( pin_cstr.GetLength() )
							{
								// illegal pin identifier
								CString mess;
								mess.Format(G_LANGUAGE == 0 ? 
									"Error in line %d of netlist file. Illegal pin identifier \"%s\"":
									"Ошибка в строке %d файла списка эл.цепей. Недопустимый идентификатор вывода \"%s\"",
									line, pin_cstr );
								AfxMessageBox( mess );
							}
							pin = mystrtok( NULL, " \t\n\r" );
						} // end while( pin )
					}
				}
			}
		}
		else if( instr == "[end]" )
		{
			// normal return
			file->Close();
			return err_flags;
		}
		else
		{
			not_eof = file->ReadString( instr );
			line++;
			instr.Trim();
			if( !not_eof)
			{
				// end of file
				file->Close();
				return err_flags;
			}
		}
	}
}

// export netlist in PADS-PCB format
// enter with file already open
// flags:
//	IMPORT_PARTS = include parts in file
//	IMPORT_NETS = include nets in file
//	IMPORT_AT = use "value@footprint" format for parts
//
int CFreePcbDoc::ExportPADSPCBNetlist( CStdioFile * file, UINT flags, 
							   partlist_info * pl, netlist_info * nl )
{
	CString str, str2;

	file->WriteString( "*PADS-PCB*\n" );
	if( flags & EXPORT_PARTS )
	{
		file->WriteString( "*PART*\n" );
		for( int i=0; i<pl->GetSize(); i++ )
		{
			part_info * pi = &(*pl)[i];
			str2 = "";
			if( flags & EXPORT_VALUES && pi->value.GetLength() )
				str2 = pi->value + "@";
			if( pi->shape )
				str2 += pi->shape->m_name;
			str.Format( "%s %s\n", pi->ref_des, str2 );
			file->WriteString( str );
		}
	}

	if( flags & EXPORT_NETS )
	{
		if( flags & IMPORT_PARTS )
			file->WriteString( "\n" );
		file->WriteString( "*NET*\n" );
		for( int i=0; i<nl->GetSize(); i++ )
		{
			net_info * ni = &(*nl)[i];
			str.Format( "*SIGNAL* %s\n", ni->name );
			file->WriteString( str );
			str = "";
			int np = ni->pin_name.GetSize();
			for( int ip=0; ip<np; ip++ )
			{
				CString pin_str;
				pin_str.Format( "%s.%s ", ni->ref_des[ip], ni->pin_name[ip] );
				str += pin_str;
				if( !((ip+1)%8) || ip==(np-1) )
				{
					str += "\n";
					file->WriteString( str );
					str = "";
				}
			}
		}
	}
	file->WriteString( "*END*\n" );
	return 0;
}

// import netlist in PADS-PCB format
// enter with file already open
//
int CFreePcbDoc::ImportPADSPCBNetlist( CStdioFile * file, UINT flags, 
							   partlist_info * pl, netlist_info * nl )
{
	CString instr, net_name, mess;
	CMapStringToPtr part_map, net_map, pin_map;
	void * ptr;
	int npins, inet;
	int err_flags = 0;
	int line = 0;
	BOOL not_eof;
	int ipart;
	if( pl )
		ipart = pl->GetSize();

	// state machine
	enum { IDLE, PARTS, NETS, SIGNAL };
	int state = IDLE;
	BOOL bLegal = FALSE;

	while( 1 )
	{
		not_eof = file->ReadString( instr );
		line++;
		instr.Trim();
		if( line > 2 && !bLegal )
		{
			file->Close();
			return NOT_PADSPCB_FILE;
		}
		if( instr.Left(5) == "*END*" || !not_eof )
		{
			// normal return
			file->Close();
			return err_flags;
		}
		else if( instr.Left(10) == "*PADS-PCB*" || instr.Left(10) == "*PADS2000*" )
			bLegal = TRUE;
		else if( instr.Left(6) == "*PART*" )
			state = PARTS;
		else if( instr.Left(5) == "*NET*" )
			state = NETS;
		else if( state == PARTS && pl && (flags & IMPORT_PARTS) )
		{
			// read parts
			if( instr.GetLength() && instr[0] != '/' )
			{
				// get ref_des and footprint
				CString ref_str( mystrtok( instr, " \t" ) );
				if( ref_str.GetLength() > MAX_REF_DES_SIZE )
				{
					CString mess;
					mess.Format( "  line %d: Reference designator \"%s\" too long, truncated\r\n",
						line, ref_str );
					m_dlg_log->AddLine( mess );
					ref_str = ref_str.Left(MAX_REF_DES_SIZE);
				}
				// check for legal ref_designator
				if( ref_str.FindOneOf( ". " ) != -1 )
				{
					mess.Format( "  line %d: Part \"%s\" illegal reference designator, ignored\r\n", 
						line, ref_str );
					m_dlg_log->AddLine( mess );
					continue;
				}
				// check for duplicate part
				if( part_map.Lookup( ref_str, ptr ) )
				{
					mess.Format( "  line %d: Part \"%s\" is duplicate, ignored\r\n", 
						line, ref_str );
					m_dlg_log->AddLine( mess );
					continue;
				}
				// new part
				pl->SetSize( ipart+1 );
				CString shape_str( mystrtok( NULL, "\n\r" ) );
				shape_str.Trim();
				// check for "ssss@ffff" format
				int pos = shape_str.Find( "@" );
				if( pos != -1 )
				{
					CString value_str;
					SplitString( &shape_str, &value_str, &shape_str, '@' );
					(*pl)[ipart].value = value_str;
				}
				else
					(*pl)[ipart].value = "";
				if( shape_str.GetLength() > CShape::MAX_NAME_SIZE )
				{
					CString mess;
					mess.Format( "  line %d: Package name \"%s\" too long, truncated\r\n",
						line, shape_str );
					m_dlg_log->AddLine( mess );
					shape_str = shape_str.Left(CShape::MAX_NAME_SIZE);
				}
				// find footprint, get from library if necessary
				CShape * s = GetFootprintPtr( shape_str );
				if( s == NULL )
				{
					mess.Format( "  line %d: Part \"%s\" footprint \"%s\" not found\r\n", 
						line, ref_str, shape_str );
					m_dlg_log->AddLine( mess );
				}
				// add part to partlist_info
				(*pl)[ipart].part = NULL;
				(*pl)[ipart].ref_des = ref_str;
				part_map.SetAt( ref_str, NULL );
				if( s )
				{
					(*pl)[ipart].ref_size = s->m_ref_size;
					(*pl)[ipart].ref_width = s->m_ref_w;
				}
				else 
				{	
					s = new CShape;
					s->selection = rect(0,0,NM_PER_MM*40,NM_PER_MM*5);
					s->m_ref_size = 0;
					s->m_value_size = 0;
					s->m_name = shape_str;
					s->m_package = "ERROR";
					s->m_padstack.RemoveAll();
					s->m_outline_poly.SetSize(1);
					id ID( ID_PART_LINES, ID_OUTLINE, 0 );
					s->m_outline_poly[0].Start( LAY_FP_SILK_TOP, NM_PER_MIL*10, NM_PER_MIL*10, 0, 0, 0, &ID, NULL );
					s->m_outline_poly[0].AppendCorner( 0, NM_PER_MM*5, 0, 0 );
					s->m_outline_poly[0].AppendCorner( NM_PER_MM*40, NM_PER_MM*5, 0, 0 );
					s->m_outline_poly[0].AppendCorner( NM_PER_MM*40, 0, 0, 0 );
					s->m_outline_poly[0].AppendCorner( 0, 0, 0, 0 );
					if( s->m_tl )
					{
						s->m_tl->RemoveAllTexts();
						CString Msg;
						Msg.Format( "FOOTPRINT %s NOT FOUND", shape_str );
						s->m_tl->AddText(NM_PER_MM,NM_PER_MM*2,0,0,0,LAY_FP_SILK_TOP,NM_PER_MM,NM_PER_MIL,&Msg,0);
					}
					m_footprint_cache_map.SetAt( s->m_name, s );
				}
							
				(*pl)[ipart].bOffBoard = TRUE;
				(*pl)[ipart].shape = s;
				(*pl)[ipart].angle = 0;
				(*pl)[ipart].side = 0;
				(*pl)[ipart].x = 0;
				(*pl)[ipart].y = 0;
				ipart++;
			}
		}
		else if( instr.Left(8) == "*SIGNAL*" && nl && (flags & IMPORT_NETS) )
		{
			state = NETS;
			net_name = instr.Right(instr.GetLength()-8);
			net_name.Trim();
			int pos = net_name.Find( " " );
			if( pos != -1 )
			{
				net_name = net_name.Left( pos );
			}
			if( net_name.GetLength() )
			{
				if( net_name.GetLength() > MAX_NET_NAME_SIZE )
				{
					mess.Format( "  line %d: Net name \"%s\" too long, truncated\r\n                    truncated to \"%s\"\r\n", 
						line, net_name, net_name.Left(MAX_NET_NAME_SIZE) );
					m_dlg_log->AddLine( mess );
					net_name = net_name.Left(MAX_NET_NAME_SIZE);
				}
				if( net_name.FindOneOf( " \"" ) != -1 )
				{
					mess.Format( "  line %d: Net name \"%s\" illegal, ignored\r\n", 
						line, net_name );
					m_dlg_log->AddLine( mess );
				}
				else
				{
					if( (flags & RENAME_NETXXXXX_NETS) ) 
					{
						if( net_name.Left(3) == "NET" )
						{
							CString str;
							int index = 0;
							BOOL bFound = TRUE;
							while( bFound )
							{
								index++;
								str.Format( "NET%.5d", index );
								void * ptr;
								if( !m_nlist->m_map.Lookup( str, ptr ) )
									if( !net_map.Lookup( str, ptr ) )
										bFound = FALSE;
							}
							if( net_name.Left(4) == "NET0" )
							{
								net_name = str;
							}
							else
							{
								CString pref;
								int net_index = ParseRef( &net_name, &pref );
								if( net_index )
								{
									net_name = str;
								}
							}
						}
					}
					if( net_map.Lookup( net_name, ptr ) )
					{
						mess.Format( "  line %d: Net name \"%s\" is duplicate, ignored\r\n", 
							line, net_name );
						m_dlg_log->AddLine( mess );
					}
					else
					{
						int vis=1;
						cnet * fnet = m_nlist->GetNetPtrByName( &net_name );
						if( fnet )
							vis = fnet->visible;
						
						// add new net
						net_map.SetAt( net_name, NULL );
						inet = nl->GetSize();
						nl->SetSize( inet+1 );
						(*nl)[inet].name = net_name;
						(*nl)[inet].net = NULL;
						(*nl)[inet].apply_trace_width = FALSE;
						(*nl)[inet].apply_via_width = FALSE;
						(*nl)[inet].modified = TRUE;
						(*nl)[inet].deleted = FALSE;
						(*nl)[inet].visible = vis;
						// mark widths as undefined
						(*nl)[inet].w = -1;
						(*nl)[inet].v_w = -1;
						(*nl)[inet].v_h_w = -1;
						npins = 0;
						state = SIGNAL;
					}
				}
			}
		}
		else if( state == SIGNAL  && nl && (flags & IMPORT_NETS) )
		{
			// add pins to net
			char * pin = mystrtok( instr, " \t\n\r" );
			while( pin )
			{
				CString pin_cstr( pin );
				if( pin_cstr.GetLength() > 2 )
				{
					int dot = pin_cstr.Find( ".", 0 );
					if( dot > 0 && dot < (pin_cstr.GetLength()-1) )
					{
						if( pin_map.Lookup( pin_cstr, ptr ) )
						{
							mess.Format( "  line %d: Net \"%s\" pin \"%s\" is duplicate, ignored\r\n", 
								line, net_name, pin_cstr );
							m_dlg_log->AddLine( mess );
						}
						else
						{
							pin_map.SetAt( pin_cstr, NULL );
							CString ref_des = pin_cstr.Left( dot );
							CString pin_num_cstr = pin_cstr.Right( pin_cstr.GetLength()-dot-1 );
							(*nl)[inet].ref_des.Add( ref_des );
							if( pin_num_cstr.GetLength() > CShape::MAX_PIN_NAME_SIZE )
							{
								CString mess;
								mess.Format( "  line %d: Pin name \"%s\" too long, truncated\r\n",
									line, pin_num_cstr );
								m_dlg_log->AddLine( mess );
								pin_num_cstr = pin_num_cstr.Left(CShape::MAX_PIN_NAME_SIZE);
							}
							(*nl)[inet].pin_name.Add( pin_num_cstr );
						}
					}
					else
					{
						// illegal pin identifier
						mess.Format( "  line %d: Pin identifier \"%s\" illegal, ignored\r\n", 
							line, pin_cstr );
						m_dlg_log->AddLine( mess );
					}
				}
				else
				{
					// illegal pin identifier
					mess.Format( "  line %d: Pin identifier \"%s\" illegal, ignored\r\n", 
						line, pin_cstr );
					m_dlg_log->AddLine( mess );
				}
				pin = mystrtok( NULL, " \t\n\r" );
			} // end while( pin )
		}
	} // end while
}

void CFreePcbDoc::OnAppExit()
{
	if( FileClose() != IDCANCEL )
	{
//		m_view->SetHandleCmdMsgFlag( FALSE );
		AfxGetMainWnd()->SendMessage( WM_CLOSE, 0, 0 );
	}
}

void CFreePcbDoc::OnFileConvert()
{
	CivexDlg dlg;
	dlg.DoModal();
}

// create undo record for moving origin
//
undo_move_origin * CFreePcbDoc::CreateMoveOriginUndoRecord( int x_off, int y_off )
{
	// create undo record 
	undo_move_origin * undo = new undo_move_origin;//ok
	undo->x_off = x_off;
	undo->y_off = y_off;
	return undo;
}

// undo operation on move origin
//
void CFreePcbDoc::MoveOriginUndoCallback( int type, void * ptr, BOOL undo )
{
	if( undo )
	{
		// restore previous origin
		undo_move_origin * un_mo = (undo_move_origin*)ptr;
		if( un_mo )
		{
			int x_off = un_mo->x_off;
			int y_off = un_mo->y_off;
			this_Doc->m_view->MoveOrigin( -x_off, -y_off );
			this_Doc->m_view->Invalidate( FALSE );
		}
	}
	delete ptr;
}


// create undo record for SM cutout
// only include closed polys
//
undo_outline_poly * CFreePcbDoc::CreateOutlinePolyUndoRecord( CPolyLine * poly, int num )
{
	// create undo record for sm cutout
	undo_outline_poly * undo;
	int ncorners = poly->GetNumCorners();
	undo = (undo_outline_poly*)malloc( sizeof(undo_outline_poly)+ncorners*sizeof(undo_corner));
	undo->layer = poly->GetLayer();
	undo->wid = poly->GetW();
	undo->closed = poly->GetClosed();
	undo->hatch_style = poly->GetHatch();
	undo->ncorners = poly->GetNumCorners();
	undo_corner * corner = (undo_corner*)((UINT)undo + sizeof(undo_outline_poly));
	for( int ic=0; ic<ncorners; ic++ )
	{
		corner[ic].x = poly->GetX( ic );
		corner[ic].y = poly->GetY( ic );
		corner[ic].num_contour = poly->GetNumContour( ic );
		if( undo->closed || ic<ncorners-1 )
			corner[ic].style = poly->GetSideStyle( ic );
	}
	undo->merge_op = poly->GetMerge();
	undo->submerge_op = poly->GetMerge(TRUE);
	undo->num = num;
	return undo;
}

// undo operation on solder mask cutout
//
void CFreePcbDoc::OutlinePolyUndoCallback( int type, void * ptr, BOOL undo )
{
	if( undo ) 
	{
		if( type == CFreePcbView::UNDO_OP_CLEAR_ALL ) 
		{
			// remove all poly's
			this_Doc->m_outline_poly.RemoveAll();
		}
		else
		{
			// restore poly from undo record
			undo_outline_poly * undo_poly = (undo_outline_poly*)ptr;	
			if( undo_poly )
			{
				int i = this_Doc->m_outline_poly.GetSize();
				int size = max( i,(undo_poly->num+1) );
				this_Doc->m_outline_poly.SetSize( size );
				if( undo_poly->num < i && this_Doc->m_outline_poly[undo_poly->num].GetNumCorners() )
				{
					size = max( (i+1),(undo_poly->num+1) );
					this_Doc->m_outline_poly.SetSize( size );
					for( int up=i-1; up>=undo_poly->num; up-- )
					{
						this_Doc->m_outline_poly[up+1].Copy( &this_Doc->m_outline_poly[up] );
					}
				}
				CPolyLine * poly = &this_Doc->m_outline_poly[undo_poly->num];
				poly->SetDisplayList( this_Doc->m_dlist );
				int st = ID_SM_CUTOUT;
				if( undo_poly->layer == LAY_BOARD_OUTLINE )
					st = ID_BOARD;
				else if( undo_poly->layer == LAY_SM_TOP || undo_poly->layer == LAY_SM_BOTTOM )
					st = ID_SM_CUTOUT;
				else 
					st = ID_GRAPHIC;
				id p_id( ID_POLYLINE, st, undo_poly->num );
				undo_corner * corner = (undo_corner*)((UINT)undo_poly + sizeof(undo_outline_poly));
				poly->Start( undo_poly->layer, undo_poly->wid, 5*NM_PER_MIL, 
					corner[0].x, corner[0].y, undo_poly->hatch_style, &p_id, NULL );
				int ic_start = 0;
				for( int ic=1; ic<undo_poly->ncorners; ic++ )
				{					
					if( corner[ic].num_contour != corner[ic-1].num_contour )
					{
						poly->Close( corner[ic-1].style, 0, 0 );
						ic_start = ic;
						poly->AppendCorner( corner[ic].x, corner[ic].y, NULL, FALSE );
					}
					else
						poly->AppendCorner( corner[ic].x, corner[ic].y, corner[ic-1].style, FALSE );
				}
				if( undo_poly->closed )
					poly->Close( corner[undo_poly->ncorners-1].style, 0 );
				poly->SetMerge( undo_poly->merge_op );
				poly->SetMerge( undo_poly->submerge_op, TRUE );
				if( poly->bDrawn == 0 )
					poly->Draw();
				if( st == ID_BOARD )
					this_Doc->m_dlist->Images.UpdateBoardOutline();
			}
		}
	}
	delete ptr;
}
BOOL CFreePcbDoc::OnFileGenerateDXFFile(UINT CMD)
{
	int hatch = 1;
	if (CMD > ID_FILE_GENERATEDXFFILE4)
	{
		hatch = 0;
		CMD -= 4;
	}
	float swell = 100.0;
	if (CMD == ID_FILE_GENERATEDXFFILE2)
		swell = 50000.0;
	else if (CMD == ID_FILE_GENERATEDXFFILE3)
		swell = 100000.0;
	int num_polylines = m_outline_poly.GetSize();
	cnet* laser_net = m_nlist->AddNet("LASER__NET", 0, 0, 0);
	RECT TR = rect(0,0,0,0);
	TR.left = TR.bottom = INT_MAX;
	TR.right = TR.top = INT_MIN;
	MarkLegalElementsForExport(this);
	int LEGAL_BOARD = -1;
	for (int i = 0; i < m_outline_poly.GetSize(); i++)
		if (m_outline_poly.GetAt(i).GetUtility())
		{
			if (m_outline_poly.GetAt(i).GetLayer() == LAY_BOARD_OUTLINE)
				LEGAL_BOARD = i;
			RECT r = m_outline_poly.GetAt(i).GetCornerBounds(0);
			SwellRect(&TR, r);
		}
	if (TR.left == INT_MAX)
		return 0;
	int iar = m_nlist->AddArea(laser_net, LAY_TOP_COPPER, TR.left, TR.bottom, hatch);
	m_nlist->AppendAreaCorner(laser_net, iar, TR.left, TR.top, 0, 0);
	m_nlist->AppendAreaCorner(laser_net, iar, TR.right, TR.top, 0, 0);
	m_nlist->AppendAreaCorner(laser_net, iar, TR.right, TR.bottom, 0, 0);
	m_nlist->CompleteArea(laser_net, iar, 0);
	CString crop_net_name = "";
	int crop_flags = 0;
	setbit(crop_flags, MC_PADS);
	setbit(crop_flags, MC_SEGS);
	setbit(crop_flags, MC_AREAS);
	setbit(crop_flags, MC_HOLES);
	setbit(crop_flags, MC_TEXTS);
	setbit(crop_flags, MC_POLYLINES);
	setbit(crop_flags, MC_BOARD);
	setbit(crop_flags, MC_OCTAGON);
	setbit(crop_flags, MC_ALL_NETS);
	setbit(crop_flags, MC_WIDTH);
	setbit(crop_flags, MC_DXF);
	int mem_crop_flags = m_crop_flags;
	m_crop_flags = crop_flags;
	if (CMD != ID_FILE_GENERATEDXFFILE4)
		CreateClearancesForCopperArea(	this,
										&crop_net_name,
										laser_net,
										iar,
										swell,
										swell,
										swell,
										swell,
										swell,
										0,
										swell,
										swell,
										50000,
										FALSE);
	MarkLegalElementsForExport(this);
	for (int ia=laser_net->nareas-1; ia>0; ia--)
	{
		int gnc = laser_net->area[ia].poly->GetNumCorners();
		int x = laser_net->area[ia].poly->GetX(gnc - 1); 
		int y = laser_net->area[ia].poly->GetY(gnc - 1);
		if(m_outline_poly.GetAt(LEGAL_BOARD).TestPointInside(x,y) == 0)
			m_nlist->RemoveArea(laser_net, ia);
	}
	for (cpart* p = m_plist->GetFirstPart(); p; p = m_plist->GetNextPart(p))
	{
		if (p->shape && p->utility)
		{
			for (int ip = 0; ip < p->shape->GetNumPins(); ip++)
			{
				if (p->shape->m_padstack[ip].hole_size)
				{
					int hs = p->shape->m_padstack[ip].hole_size;
					CPoint pt = m_plist->GetPinPoint(p, ip, p->side, p->angle);
					int ia = m_nlist->AddArea(laser_net, LAY_TOP_COPPER, pt.x - hs / 2, pt.y, hatch);
					m_nlist->AppendAreaCorner(laser_net, ia, pt.x, pt.y + hs / 2, 1, 0);
					m_nlist->AppendAreaCorner(laser_net, ia, pt.x + hs / 2, pt.y, 1, 0);
					m_nlist->AppendAreaCorner(laser_net, ia, pt.x, pt.y - hs / 2, 1, 0);
					laser_net->area[ia].poly->SetW(50000);
					m_nlist->CompleteArea(laser_net, ia, 1);
					id sel_id = laser_net->area[ia].poly->GetId();
					sel_id.sst = ID_SIDE;
					for (int i_side = 0; i_side < laser_net->area[ia].poly->GetNumSides(); i_side++)
					{
						sel_id.ii = i_side;
						m_view->NewSelect(laser_net, &sel_id, FALSE, 0, 0);
					}
				}
			}
		}
	}
	for (cnet* n = m_nlist->GetFirstNet(); n; n = m_nlist->GetNextNet())
	{
		for (int ic = 0; ic < n->nconnects; ic++)
		{
			for (int iv = 0; iv <= n->connect[ic].nsegs; iv++)
			{
				if (n->connect[ic].vtx[iv].via_hole_w)
					if (n->connect[ic].utility)
					{
						int hs = n->connect[ic].vtx[iv].via_hole_w;
						CPoint pt(n->connect[ic].vtx[iv].x, n->connect[ic].vtx[iv].y);
						int ia = m_nlist->AddArea(laser_net, LAY_TOP_COPPER, pt.x - hs / 2, pt.y, hatch);
						m_nlist->AppendAreaCorner(laser_net, ia, pt.x, pt.y + hs / 2, 1, 0);
						m_nlist->AppendAreaCorner(laser_net, ia, pt.x + hs / 2, pt.y, 1, 0);
						m_nlist->AppendAreaCorner(laser_net, ia, pt.x, pt.y - hs / 2, 1, 0);
						laser_net->area[ia].poly->SetW(50000);
						m_nlist->CompleteArea(laser_net, ia, 1);
						id sel_id = laser_net->area[ia].poly->GetId();
						sel_id.sst = ID_SIDE;
						for (int i_side = 0; i_side < laser_net->area[ia].poly->GetNumSides(); i_side++)
						{
							sel_id.ii = i_side;
							m_view->NewSelect(laser_net, &sel_id, FALSE, 0, 0);
						}
					}
			}
		}
	}
	m_view->OnGenerateDXF();
	m_view->CancelSelection(0);
	for (int i = laser_net->nareas - 1; i >= 0; i--)
		m_nlist->RemoveArea(laser_net, i);
	m_nlist->RemoveNet(laser_net);
	m_crop_flags = mem_crop_flags;
	return TRUE;
}
BOOL CFreePcbDoc::OnFileGenerateGRBLFile(UINT CMD)
{
	BOOL LASERMODE = 1;
	CStdioFile f;
	if (f.Open(m_app_dir + "\\open.gcode", CFile::modeCreate | CFile::modeWrite, NULL))
	{
		f.WriteString("%\n");
		f.WriteString("; G-code from Schemator&Platform\n");
		f.WriteString("; info: www.niconson.com/freepcb2\n");
		if (CMD == ID_FILE_GENERATEGRBLFILE6)
			Generate_GCODE(&f, 0, 0, TRUE, LASERMODE);
		else
		{
			Generate_GCODE(&f, NM_PER_MIL * 4, 0, FALSE, LASERMODE);
			Generate_GCODE(&f, NM_PER_MIL * 8, 0, FALSE, LASERMODE);
			for (UINT swell = NM_PER_MIL * 12; CMD >= ID_FILE_GENERATEGRBLFILE1; CMD--)
			{
				Generate_GCODE(&f, swell, 0, FALSE, LASERMODE);
				swell += (NM_PER_MIL * 8);
			}
		}
		f.WriteString("M30\n");
		f.Close();
	}
	ShellExecute(NULL, "open", "open.gcode", NULL, m_app_dir, SW_SHOWNORMAL);
	return 0;
}
BOOL CFreePcbDoc::OnFileGenerateHPGLFile(UINT CMD)
{
	int hatch = 1;
	if (CMD > ID_FILE_GENERATEHPGLFILE7)
	{
		hatch = 0;
		CMD -= 7;
	}
	//
	float swell = NM_PER_MIL * 2;
	if (CMD == ID_FILE_GENERATEHPGLFILE2)
		swell = NM_PER_MIL * 4;
	else if (CMD == ID_FILE_GENERATEHPGLFILE3)
		swell = NM_PER_MIL * 8;
	else if (CMD == ID_FILE_GENERATEHPGLFILE4)
		swell = NM_PER_MIL * 12;
	else if (CMD == ID_FILE_GENERATEHPGLFILE5)
		swell = NM_PER_MIL * 16;
	else if (CMD == ID_FILE_GENERATEHPGLFILE6)
		swell = NM_PER_MIL * 20;
	else if (CMD == ID_FILE_GENERATEHPGLFILE7)
		swell = NM_PER_MIL * 40;
	//
	CStdioFile f;
	if (f.Open(m_app_dir + "\\open.gcode", CFile::modeCreate | CFile::modeWrite, NULL))
	{
		Generate_GCODE(&f, swell, hatch, (BOOL)(CMD==ID_FILE_GENERATEHPGLFILE8), FALSE);
		f.WriteString("M30\n");
		f.Close();
	}
	ShellExecute(NULL, "open", "open.gcode", NULL, m_app_dir, SW_SHOWNORMAL);
	return TRUE;
}
void CFreePcbDoc::Generate_GCODE(CStdioFile* f, float swell, int hatch, BOOL bHOLES, BOOL bLASERMODE)
{
	int num_polylines = m_outline_poly.GetSize();
	cnet* laser_net = m_nlist->AddNet("LASER__NET", 0, 0, 0);
	RECT TR = rect(0, 0, 0, 0);
	TR.left = TR.bottom = INT_MAX;
	TR.right = TR.top = INT_MIN;
	MarkLegalElementsForExport(this);
	int LEGAL_BOARD = -1;
	for (int i = 0; i < m_outline_poly.GetSize(); i++)
		if (m_outline_poly.GetAt(i).GetUtility())
		{
			if (m_outline_poly.GetAt(i).GetLayer() == LAY_BOARD_OUTLINE)
				LEGAL_BOARD = i;
			RECT r = m_outline_poly.GetAt(i).GetCornerBounds(0);
			SwellRect(&TR, r);
		}
	if (TR.left == INT_MAX)
		return;
	int iar = m_nlist->AddArea(laser_net, LAY_TOP_COPPER, TR.left, TR.bottom, hatch);
	m_nlist->AppendAreaCorner(laser_net, iar, TR.left, TR.top, 0, 0);
	m_nlist->AppendAreaCorner(laser_net, iar, TR.right, TR.top, 0, 0);
	m_nlist->AppendAreaCorner(laser_net, iar, TR.right, TR.bottom, 0, 0);
	m_nlist->CompleteArea(laser_net, iar, 0);
	CString crop_net_name = "";
	int crop_flags = 0;
	setbit(crop_flags, MC_PADS);
	setbit(crop_flags, MC_SEGS);
	setbit(crop_flags, MC_AREAS);
	setbit(crop_flags, MC_HOLES);
	setbit(crop_flags, MC_TEXTS);
	setbit(crop_flags, MC_POLYLINES);
	setbit(crop_flags, MC_BOARD);
	setbit(crop_flags, MC_OCTAGON);
	setbit(crop_flags, MC_ALL_NETS);
	setbit(crop_flags, MC_WIDTH);
	setbit(crop_flags, MC_DXF);
	int mem_crop_flags = m_crop_flags;
	m_crop_flags = crop_flags;
	if (bHOLES == 0)
		CreateClearancesForCopperArea(this,
			&crop_net_name,
			laser_net,
			iar,
			_2540,
			_2540,
			_2540,
			_2540,
			_2540,
			0,// board
			_2540,
			_2540,
			swell,
			FALSE);
	int iLegalBoard = MarkLegalElementsForExport(this);
	float convert = NM_PER_MM;
	if (m_units == MIL)
		convert = NM_PER_MM * 254 / 10;

	CString s;
	CString ToolUp = "G00 Z3.0\n";
	CString ToolZero = "G00 Z0.0\n";
	if (m_units == MIL)
		ToolUp = "G00 Z0.12\n";
	if (bLASERMODE == 0)
	{
		f->WriteString("%\n");
		f->WriteString("; G-code from Schemator&Platform\n");
		f->WriteString("; info: www.niconson.com/freepcb2\n");
		if (bHOLES == 0)
		{
			s.Format("; Tool d = %.1f nanometers,\n", swell);
			f->WriteString(s);
		}
		else
			f->WriteString("; Through drilling tool.\n");
		f->WriteString(";-------------IMPORTANT INFO-------------\n");
		f->WriteString("; The Z axis is set so that at Z=0 the tool\n");
		f->WriteString("; touches the surface of the workpiece !\n");
		f->WriteString(";----------------------------------------\n");
	}
	f->WriteString("G17\n");
	if (m_units == MIL)
		f->WriteString("G20\n");
	else
		f->WriteString("G21\n");
	f->WriteString("G40\n");
	f->WriteString("G49\n");
	f->WriteString("G53\n");
	f->WriteString("G80\n");
	f->WriteString("G90\n");
	f->WriteString("G94\n");
	if (bLASERMODE == 0)
	{
		if (m_units == MIL)
			f->WriteString("F12\n");
		else
			f->WriteString("F300\n");
		f->WriteString("M3 S500\n");
		f->WriteString("G4 P2000\n");
	}
	else
		f->WriteString("M3 S0\n");
	RECT BR = m_outline_poly.GetAt(iLegalBoard).GetCornerBounds(0);
	f->WriteString(";----------------------\n; Left-Bottom Corner:\n");
	f->WriteString(ToolUp);
	s.Format("G00 X%.4f Y%.4f\n", BR.left / convert, BR.bottom / convert);
	f->WriteString(s);
	///f->WriteString("G01 Z0.1\n");
	if (m_units == MIL)
		f->WriteString("G00 Z0.01\n");
	else
		f->WriteString("G00 Z0.1\n");
	f->WriteString("G4 P2000\n");
	f->WriteString(";----------------------\n; Right-Top Corner:\n");
	f->WriteString(ToolUp);
	s.Format("G00 X%.4f Y%.4f\n", BR.right / convert, BR.top / convert);
	f->WriteString(s);
	///f->WriteString("G01 Z0.1\n");
	if (m_units == MIL)
		f->WriteString("G00 Z0.01\n");
	else
		f->WriteString("G00 Z0.1\n");
	f->WriteString("G4 P2000\n");
	f->WriteString(";----------------------\n; Right-Bottom Corner:\n");
	f->WriteString(ToolUp);
	s.Format("G00 X%.4f Y%.4f\n", BR.right / convert, BR.bottom / convert);
	f->WriteString(s);
	///f->WriteString("G01 Z0.1\n");
	if (m_units == MIL)
		f->WriteString("G00 Z0.01\n");
	else
		f->WriteString("G00 Z0.1\n");
	f->WriteString("G4 P2000\n");
	f->WriteString(";----------------------\n; Left-Top Corner:\n");
	f->WriteString(ToolUp);
	s.Format("G00 X%.4f Y%.4f\n", BR.left / convert, BR.top / convert);
	f->WriteString(s);
	///f->WriteString("G01 Z0.1\n");
	if (m_units == MIL)
		f->WriteString("G00 Z0.01\n");
	else
		f->WriteString("G00 Z0.1\n");
	f->WriteString("G4 P2000\n");
	f->WriteString(";----------------------\n");
	if (bHOLES)
	{
		// none
	}
	else for (int area = laser_net->nareas - 1; area >= 0; area--)
	{
		int gnc = laser_net->area[area].poly->GetNumCorners();
		int x = laser_net->area[area].poly->GetX(gnc - 1);
		int y = laser_net->area[area].poly->GetY(gnc - 1);
		if (m_outline_poly.GetAt(LEGAL_BOARD).TestPointInside(x, y))
		{
			for (int ia = 0; ia < laser_net->area[area].poly->GetNumCorners(); ia++)
			{
				float fx = laser_net->area[area].poly->GetX(ia);
				float fy = laser_net->area[area].poly->GetY(ia);
				int numc = laser_net->area[area].poly->GetNumContour(ia);
				if (laser_net->area[area].poly->GetContourStart(numc) == ia)
				{
					f->WriteString(ToolUp);
					s.Format("G00 X%.4f Y%.4f\n", fx / convert, fy / convert);
					f->WriteString(s);
					f->WriteString(ToolZero);
					if (bLASERMODE)
						f->WriteString("S1000\n");
					if (m_units == MIL)
						f->WriteString("G01 Z-0.004\n");
					else
						f->WriteString("G01 Z-0.1\n");
				}
				else
				{
					s.Format("G01 X%.4f Y%.4f\n", fx / convert, fy / convert);
					f->WriteString(s);
				}
				if (laser_net->area[area].poly->GetContourEnd(numc) == ia)
				{
					int cst = laser_net->area[area].poly->GetContourStart(numc);
					fx = laser_net->area[area].poly->GetX(cst);
					fy = laser_net->area[area].poly->GetY(cst);
					s.Format("G01 X%.4f Y%.4f\n", fx / convert, fy / convert);
					f->WriteString(s);
					if (bLASERMODE)
						f->WriteString("S0\n");
				}
			}
			CPolyLine* p = laser_net->area[area].poly;
			if (p->GetHatch() == 1)
			{
				int nh = p->GetHatchSize();
				for (int ic = 0; ic < nh; ic++)
				{
					dl_element* GetH = p->GetHatchLoc(ic);
					CArray<CPoint>* pA = GetH->dlist->Get_Points(GetH, NULL, 0);
					int np = pA->GetSize();
					CPoint* P = new CPoint[np];//new012
					GetH->dlist->Get_Points(GetH, P, &np);
					for (int ip = 0; ip + 1 < np; ip += 2)
					{
						if (m_units == MIL)
						{
							if (ip == 0)
								f->WriteString("G00 Z0.08\n");
							else
								f->WriteString("G00 Z0.04\n");
						}
						else if (ip == 0)
							f->WriteString("G00 Z2.0\n");
						else
							f->WriteString("G00 Z1.0\n");
						s.Format("G00 X%.4f Y%.4f\n", (float)P[ip].x / convert, (float)P[ip].y / convert);
						f->WriteString(s);
						f->WriteString(ToolZero);
						if (bLASERMODE)
							f->WriteString("S1000\n");
						if (m_units == MIL)
							f->WriteString("G01 Z-0.004\n");
						else
							f->WriteString("G01 Z-0.1\n");
						s.Format("G01 X%.4f Y%.4f\n", (float)P[ip + 1].x / convert, (float)P[ip + 1].y / convert);
						f->WriteString(s);
						if (bLASERMODE)
							f->WriteString("S0\n");
					}
					delete P;//new012
				}
			}
		}
	}
	int DIAM;
	do
	{
		DIAM = 0;
		for (cpart* p = m_plist->GetFirstPart(); p; p = m_plist->GetNextPart(p))
		{
			if (p->shape && p->utility)
			{
				for (int ip = 0; ip < p->shape->GetNumPins(); ip++)
				{
					if (p->shape->m_padstack[ip].hole_size && p->pin[ip].utility == 0)
					{
						if (DIAM == 0)
						{
							DIAM = p->shape->m_padstack[ip].hole_size;
							if (bLASERMODE == 0)
							{
								if (m_units == MIL)
									f->WriteString("G00 Z2\n");
								else
									f->WriteString("G00 Z50\n");

								f->WriteString("M5\n");
								f->WriteString("M01\n");
								f->WriteString(";----------------------\n");
								s.Format("; New diameter = %.4f\n", (float)DIAM / convert);
								f->WriteString(s);
								f->WriteString(";----------------------\n");
								f->WriteString("M3 S500\n");
								f->WriteString("G4 P2000\n");
							}
						}
						if (p->shape->m_padstack[ip].hole_size != DIAM)
							continue;
						p->pin[ip].utility = 1;
						int hs = p->shape->m_padstack[ip].hole_size;
						CPoint pt = m_plist->GetPinPoint(p, ip, p->side, p->angle);
						if (bHOLES && bLASERMODE == 0)
						{
							f->WriteString(ToolUp);
							s.Format("G00 X%.4f Y%.4f\n", (float)pt.x / convert, (float)pt.y / convert);
							f->WriteString(s);
							f->WriteString(ToolZero);
							if (m_units == MIL)
								f->WriteString("G01 Z-0.12\n");
							else
								f->WriteString("G01 Z-3.0\n");
						}
						else if (hs <= swell)
						{
							f->WriteString(ToolUp);
							s.Format("G00 X%.4f Y%.4f\n", (float)pt.x / convert, (float)pt.y / convert);
							f->WriteString(s);
							f->WriteString(ToolZero);
							if (m_units == MIL)
								f->WriteString("G01 Z-0.004\n");
							else
								f->WriteString("G01 Z-0.1\n");
						}
						else
						{
							int shift = (hs - swell) / 2;
							f->WriteString(ToolUp);
							s.Format("G00 X%.4f Y%.4f\n", (float)pt.x / convert, (float)(pt.y + shift) / convert);
							f->WriteString(s);
							f->WriteString(ToolZero);
							if (bLASERMODE)
								f->WriteString("S1000\n");
							if (m_units == MIL)
								f->WriteString("G01 Z-0.004\n");
							else
								f->WriteString("G01 Z-0.1\n");
							do
							{
								s.Format("G01 X%.4f Y%.4f\n", (float)pt.x / convert, (float)(pt.y + shift) / convert);
								f->WriteString(s);
								s.Format("G02 X%.4f Y%.4f I0.0 J%.4f\n",
									(float)pt.x / convert,
									(float)(pt.y + shift) / convert,
									(float)(-shift) / convert);
								f->WriteString(s);
								shift -= (swell * 6 / 7);
								if (hatch == 0)
									break;
							} while (shift > 0);
							if (bLASERMODE)
								f->WriteString("S0\n");
						}
					}
				}
			}
		}
		for (cnet* n = m_nlist->GetFirstNet(); n; n = m_nlist->GetNextNet())
		{
			for (int ic = 0; ic < n->nconnects; ic++)
			{
				for (int iv = 0; iv <= n->connect[ic].nsegs; iv++)
				{
					if (n->connect[ic].utility)
						if (n->connect[ic].vtx[iv].via_hole_w && n->connect[ic].vtx[iv].utility == 0)
						{
							if (DIAM == 0)
							{
								DIAM = n->connect[ic].vtx[iv].via_hole_w;
								if (m_units == MIL)
									f->WriteString("G00 Z2\n");
								else
									f->WriteString("G00 Z50\n");

								if (bLASERMODE == 0)
									f->WriteString("M5\n");

								f->WriteString("M01\n");
								f->WriteString(";----------------------\n");
								s.Format("; New diameter = %.4f\n", (float)DIAM / convert);
								f->WriteString(s);
								f->WriteString(";----------------------\n");
								if (bLASERMODE == 0)
								{
									f->WriteString("M3 S500\n");
									f->WriteString("G4 P2000\n");
								}
							}
							if (n->connect[ic].vtx[iv].via_hole_w != DIAM)
								continue;
							n->connect[ic].vtx[iv].utility = 1;
							int hs = n->connect[ic].vtx[iv].via_hole_w;
							CPoint pt(n->connect[ic].vtx[iv].x, n->connect[ic].vtx[iv].y);
							if (bHOLES && bLASERMODE == 0)
							{
								f->WriteString(ToolUp);
								s.Format("G00 X%.4f Y%.4f\n", (float)pt.x / convert, (float)pt.y / convert);
								f->WriteString(s);
								f->WriteString(ToolZero);
								if (m_units == MIL)
									f->WriteString("G01 Z-0.12\n");
								else
									f->WriteString("G01 Z-3.0\n");
							}
							else if (hs <= swell)
							{
								f->WriteString(ToolUp);
								s.Format("G00 X%.4f Y%.4f\n", (float)pt.x / convert, (float)pt.y / convert);
								f->WriteString(s);
								f->WriteString(ToolZero);
								if (m_units == MIL)
									f->WriteString("G01 Z-0.004\n");
								else
									f->WriteString("G01 Z-0.1\n");
							}
							else
							{
								int shift = (hs - swell) / 2;
								f->WriteString(ToolUp);
								s.Format("G00 X%.4f Y%.4f\n", (float)pt.x / convert, (float)(pt.y + shift) / convert);
								f->WriteString(s);
								f->WriteString(ToolZero);
								if (bLASERMODE)
									f->WriteString("S1000\n");
								if (m_units == MIL)
									f->WriteString("G01 Z-0.004\n");
								else
									f->WriteString("G01 Z-0.1\n");
								do
								{
									s.Format("G01 X%.4f Y%.4f\n", (float)pt.x / convert, (float)(pt.y + shift) / convert);
									f->WriteString(s);
									s.Format("G02 X%.4f Y%.4f I0.0 J%.4f\n",
										(float)pt.x / convert,
										(float)(pt.y + shift) / convert,
										(float)(-shift) / convert);
									f->WriteString(s);
									shift -= (swell * 6 / 7);
									if (hatch == 0)
										break;
								} while (shift > 0);
								if (bLASERMODE)
									f->WriteString("S0\n");
							}
						}
				}
			}
		}
	} while (DIAM);
	f->WriteString(ToolUp);
	f->WriteString("M5\n");
	
	m_view->CancelSelection(0);
	for (int i = laser_net->nareas - 1; i >= 0; i--)
		m_nlist->RemoveArea(laser_net, i);
	m_nlist->RemoveNet(laser_net);
	m_crop_flags = mem_crop_flags;
}
// call dialog to create Gerber and drill files
void CFreePcbDoc::OnFileGenerateCadFiles()
{
	if (theApp.m_view_mode == theApp.FOOTPRINT)
		return;
	if( m_outline_poly.GetSize() == 0 )
	{
		AfxMessageBox(G_LANGUAGE == 0 ? "A board outline must be present for CAM file generation":"Для генерации файла ГЕРБЕР необходимо наличие контура платы.");
		return;
	}
	int mem_validate = m_project_validated;
	CDlgCAD dlg;
	dlg.Initialize( m_version,
		&m_cam_full_path, 
		&m_path_to_folder,
		&m_app_dir,
		&m_pcb_filename,
		&m_png_settings,
		m_num_copper_layers, 
		m_cam_units,
		m_bSMT_copper_connect,
		m_fill_clearance, 
		m_mask_clearance,
		m_thermal_width,
		m_pilot_diameter,
		m_min_silkscreen_stroke_wid,
		m_highlight_wid,
		m_hole_clearance,
		m_thermal_clearance,
		m_annular_ring_pins,
		m_annular_ring_vias,
		m_paste_shrink,
		m_n_x, m_n_y, m_space_x, m_space_y,
		m_cam_flags,
		m_cam_layers,
		m_cam_drill_file,
		&m_outline_poly, 
		&m_bShowMessageForClearance,
		m_plist, 
		m_nlist, 
		m_tlist, 
		m_dlist,
		m_mlist,
		m_dlg_log,
		m_panel_fields,
		m_panel_holes,
		m_panel_ref_count,
		m_panel_reference,
		m_panel_scribing,
		m_panel_text,
		m_panel_frame_for_paste);
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		int maxw = 0;
		// update parameters
		ProjectModified( TRUE );
		///
		m_panel_fields[0] = dlg.m_panel.m_fields[0];
		m_panel_fields[1] = dlg.m_panel.m_fields[1];
		m_panel_holes[0] = dlg.m_panel.m_holes[0];
		m_panel_holes[1] = dlg.m_panel.m_holes[1];
		m_panel_ref_count = dlg.m_panel.m_ref_count;
		m_panel_reference = dlg.m_panel.m_reference;
		m_panel_scribing = dlg.m_panel.m_scribing;
		m_panel_text[0] = dlg.m_panel.m_text[0];
		m_panel_text[1] = dlg.m_panel.m_text[1];
		m_panel_text[2] = dlg.m_panel.m_text[2];
		m_panel_text[3] = dlg.m_panel.m_text[3];
		m_png_settings = dlg.m_png_settings;
		m_cam_full_path = dlg.m_folder;
		m_cam_units = dlg.m_units;
		m_fill_clearance = dlg.m_fill_clearance;
		m_mask_clearance = dlg.m_mask_clearance;
		m_thermal_width = dlg.m_thermal_width;
		m_thermal_clearance = dlg.m_thermal_clearance;
		m_min_silkscreen_stroke_wid = dlg.m_min_silkscreen_width;
		m_highlight_wid = dlg.m_highlight_width;
		m_pilot_diameter = dlg.m_pilot_diameter;
		m_hole_clearance = dlg.m_hole_clearance;
		m_annular_ring_pins = dlg.m_annular_ring_pins;
		m_annular_ring_vias = dlg.m_annular_ring_vias;
		m_plist->SetPinAnnularRing( m_annular_ring_pins );
		m_nlist->SetViaAnnularRing( m_annular_ring_vias );
		m_paste_shrink = dlg.m_paste_shrink;
		m_cam_flags = dlg.m_flags;
		m_cam_layers = dlg.m_layers;
		m_cam_drill_file = dlg.m_drill_file;
		m_n_x = dlg.m_n_x;
		m_n_y = dlg.m_n_y;
		m_space_x = dlg.m_space_x;
		m_space_y = dlg.m_space_y;
		m_bShowMessageForClearance = dlg.m_bShowMessageForClearance;
		m_plist->Set_default_mask_clearance( m_mask_clearance );
		m_plist->Set_default_paste_clearance( m_paste_shrink );
		for( cpart * p=m_plist->GetFirstPart(); p; p=m_plist->GetNextPart(p) )
			m_plist->DrawPart(p);
		GetGerberPathes(m_pcb_full_path);
	}
	if( dlg.m_gerber_created )
		if( getbit( m_view->m_protected, PROTECT_ON_GERBER ) )
		{
			CDlgProtection dlg;
			dlg.Ini( this );
			dlg.ExtProtection( TRUE );
		}
	m_project_validated = mem_validate;
}

void CFreePcbDoc::OnToolsFootprintwizard()
{
	CDlgWizQuad dlg;
	dlg.Initialize( &m_footprint_cache_map, &m_footlibfoldermap, TRUE, m_dlg_log );
	dlg.DoModal();
}

void CFreePcbDoc::MakeLibraryMaps( CString * fullpath )
{
	m_footlibfoldermap.SetDefaultFolder( fullpath );
	m_footlibfoldermap.AddFolder( fullpath, NULL );
}

void CFreePcbDoc::OnProjectOptions()
{
	CDlgProjectOptions dlg;
	if( m_name.GetLength() == 0 )
		m_name = m_pcb_filename;
	CString name;
	if( m_name.Right(4).MakeLower() == ".fpc" )
		name = m_name.Left( m_name.GetLength()-4 );
	else
		name = m_name;
	dlg.Init( FALSE, &name, &m_path_to_folder, &m_full_lib_dir, &m_app_dir,
		m_num_copper_layers, m_bSMT_copper_connect, m_view->m_merge_show, m_default_glue_w,
		m_trace_w, m_via_w, m_via_hole_w,
		m_auto_interval, m_auto_ratline_disable, m_auto_ratline_min_pins,
		&m_w, &m_v_w, &m_v_h_w );
	int ret = dlg.DoModal();
	if( ret == IDOK )  
	{
		// rename project
		if( name != dlg.GetName() )
		{
			CString old_n = m_pcb_full_path;
			m_name = dlg.GetName();
			if( m_name.Right(4).MakeLower() != ".fpc" )
				m_name = m_name + ".fpc";
			m_pcb_filename = m_name;
			m_pcb_full_path = m_pcb_full_path.Left( m_pcb_full_path.ReverseFind('\\')+1 ) + m_pcb_filename;
			//
			rename( old_n, m_pcb_full_path );
			CString cds = old_n.Left(old_n.GetLength()-3)+"cds";
			struct _stat buf;
			int err = _stat( cds, &buf );
			if( err == 0 )
			{
				err = AfxMessageBox(G_LANGUAGE == 0 ? 
					"Found a schema file with the same name. Do you want to rename it at the same time?":
					"Найден файл схемы с таким же именем. Хотите переименовать его одновременно?", MB_YESNO);
				if( err == IDYES )
					rename( cds, m_pcb_full_path.Left(m_pcb_full_path.GetLength()-3)+"cds" );
			}
			m_window_title = PROGRAM_CAP + m_pcb_filename;
			CWnd* pMain = AfxGetMainWnd();
			pMain->SetWindowText( m_window_title );
			ProjectModified( FALSE );
		}
		// set options from dialog
		m_auto_ratline_disable = dlg.GetAutoRatlineDisable();
		m_auto_ratline_min_pins = dlg.GetAutoRatlineMinPins();
		//
		BOOL bResetAreaConnections = (m_bSMT_copper_connect != dlg.m_bSMT_connect_copper);
		BOOL bResetMergeShow = (m_view->m_merge_show != dlg.m_bShow_merges );
		m_bSMT_copper_connect = dlg.m_bSMT_connect_copper;
		m_nlist->SetSMTconnect( m_bSMT_copper_connect );
		m_view->m_merge_show = dlg.m_bShow_merges;
		if( bResetMergeShow )
			if( m_view->m_merge_show )
				m_view->ShowMerges();
			else
				m_dlist->CancelHighLight(0,1);
		//
		m_default_glue_w = dlg.GetGlueWidth();
		// deal with decreased number of layers
		if( m_num_copper_layers > dlg.GetNumCopperLayers() )
		{
			// decreasing number of layers, offer to reassign them
			CDlgReassignLayers rel_dlg;
			rel_dlg.Initialize( m_num_copper_layers, dlg.GetNumCopperLayers() );
			int ret = rel_dlg.DoModal();
			if( ret == IDOK )
			{
				// reassign copper layers
				m_nlist->ReassignCopperLayers( dlg.GetNumCopperLayers(), rel_dlg.new_layer );
				m_tlist->ReassignCopperLayers( dlg.GetNumCopperLayers(), rel_dlg.new_layer );
				m_num_copper_layers = dlg.GetNumCopperLayers();
				m_num_layers = m_num_copper_layers + LAY_TOP_COPPER;
			}
			// clear clipboard
			ClipClear();
		}
		else if( m_num_copper_layers < dlg.GetNumCopperLayers() )
		{
			// increasing number of layers, don't reassign
			for( int il=m_num_copper_layers; il<dlg.GetNumCopperLayers(); il++ )
				m_vis[LAY_TOP_COPPER+il] = 1;
			m_num_copper_layers = dlg.GetNumCopperLayers();
			m_num_layers = m_num_copper_layers + LAY_TOP_COPPER;
		}
		m_nlist->SetNumCopperLayers( m_num_copper_layers );
		m_plist->SetNumCopperLayers( m_num_copper_layers );

		m_name = dlg.GetName();
		if( m_full_lib_dir != dlg.GetLibFolder() )
		{
			m_full_lib_dir = dlg.GetLibFolder();
			m_footlibfoldermap.SetDefaultFolder( &m_full_lib_dir );		
			m_footlibfoldermap.SetLastFolder( &m_full_lib_dir );		
		}
		m_trace_w = dlg.GetTraceWidth();
		m_via_w = dlg.GetViaWidth();
		m_via_hole_w = dlg.GetViaHoleWidth();
		m_nlist->SetWidths( abs(m_trace_w), abs(m_via_w), abs(m_via_hole_w) );
		m_auto_interval = dlg.GetAutoInterval();
		m_auto_ratline_disable = dlg.GetAutoRatlineDisable();

		if( m_vis[LAY_RAT_LINE] && !m_auto_ratline_disable )
			m_nlist->OptimizeConnections();
		m_view->InvalidateLeftPane();
		m_view->Invalidate( FALSE );
		m_project_open = TRUE;

		// force redraw of function key text
		m_view->m_cursor_mode = 999;
		m_view->CancelSelection();
		ProjectModified( TRUE );
		ResetUndoState();
		for( cpart * p=m_plist->GetFirstPart(); p; p=m_plist->GetNextPart(p) )
			m_plist->DrawPart(p);
	}
}

// come here from MainFrm on timer event
//
void CFreePcbDoc::OnTimer()
{
	if( m_project_modified_since_autosave )
	{
		m_auto_elapsed += TIMER_PERIOD;
		if( m_view && m_auto_interval && m_auto_elapsed > m_auto_interval )
		{
			if( !m_view->CurDragging() )
				AutoSave();
		}
	}
}



void CFreePcbDoc::OnToolsCheckPartsAndNets()
{
	// open log
	m_dlg_log->ShowWindow( SW_SHOW );
	m_dlg_log->UpdateWindow();
	m_dlg_log->BringWindowToTop();
	m_dlg_log->Clear();
	m_dlg_log->UpdateWindow();
	CString str;
	int nerrors = m_plist->CheckPartlist( &str );
	str += "\r\n";
	nerrors += m_nlist->CheckNetlist( &str );
	m_dlg_log->AddLine( str );
}

void CFreePcbDoc::OnToolsDrc()
{
	DlgDRC dlg;
	do{
		if( m_vis[LAY_RAT_LINE] && !m_auto_ratline_disable )
			m_nlist->OptimizeConnections();
		m_drelist->Clear();
		dlg.Initialize( m_units, 
						&m_dr,
						m_plist,
						m_nlist,
						m_tlist,
						m_drelist,
						m_num_copper_layers,
						&m_outline_poly,
						m_annular_ring_pins,
						m_annular_ring_vias,
						m_dlg_log, m_pcb_filename );
		int ret = dlg.DoModal();
		m_annular_ring_pins = dlg.m_CAM_annular_ring_pins;
		m_annular_ring_vias = dlg.m_CAM_annular_ring_vias;
		ProjectModified( TRUE );
		m_view->BringWindowToTop();
		//
		if( dlg.m_repeat_drc )
		{
			// show log dialog
			m_dlg_log->ShowWindow( SW_SHOW );
			m_dlg_log->BringWindowToTop();
			m_dlg_log->Clear();
			m_dlg_log->UpdateWindow();
			DRC();
			m_dlg_log->BringWindowToTop();
		}
		break;//debug mode
	}while( dlg.m_repeat_drc );
	m_view->Invalidate( FALSE );
}

void CFreePcbDoc::OnToolsClearDrc()
{
	if( m_view->m_cursor_mode == CUR_DRE_SELECTED )
	{
		m_view->CancelSelection();
		m_view->SetCursorMode( CUR_NONE_SELECTED );
	}
	m_drelist->Clear();
	m_view->Invalidate( FALSE );
}

void CFreePcbDoc::OnToolsShowDRCErrorlist()
{
	// TODO: Add your command handler code here
}


void CFreePcbDoc::OnToolsCheckConnectivity()
{
	// open log
	m_dlg_log->ShowWindow( SW_SHOW );
	m_dlg_log->UpdateWindow();
	m_dlg_log->BringWindowToTop();
	m_dlg_log->Clear();
	m_dlg_log->UpdateWindow();
	CString str;
	int nerrors = m_nlist->CheckConnectivity( &str );
	m_dlg_log->AddLine( str );
	if( !nerrors )
	{
		str.Format( "********* NO UNROUTED CONNECTIONS ************\r\n" );
		m_dlg_log->AddLine( str );
	}
}

void CFreePcbDoc::OnViewLog()
{
	m_dlg_log->ShowWindow( SW_SHOW );
	m_dlg_log->UpdateWindow();
	m_dlg_log->BringWindowToTop();
}

BOOL CFreePcbDoc::RemovingZeroLengthOrColinearSides( CPolyLine * ap )
{
	BOOL reDr = 0;
	int ccont = ap->GetNumContours();
	for (int icont = ccont - 1; icont >= 0; icont--)
	{
		int gst = ap->GetContourStart(icont);
		for (int i = ap->GetContourEnd(icont); i >= gst; i--)
		{
			if (ap->GetContourEnd(icont) - gst < 3)
				break;
			int ib = ap->GetIndexCornerBack(i);
			int in = ap->GetIndexCornerNext(i);
			int x = ap->GetX(i);
			int y = ap->GetY(i);
			int xb = ap->GetX(ib);
			int yb = ap->GetY(ib);
			int xn = ap->GetX(in);
			int yn = ap->GetY(in);
			int sstyle1 = ap->GetSideStyle(i);
			int sstyle2 = ap->GetSideStyle(ib);
			if ((Colinear(xb, yb, x, y, xn, yn) && sstyle1 == CPolyLine::STRAIGHT && sstyle2 == CPolyLine::STRAIGHT) ||
				Distance(xb, yb, x, y) < _2540)
			{
				reDr = 1;
				ap->DeleteCorner(i, 1, 1, 0);
				CString xs, ys;
				::MakeCStringFromDimension(&xs, x, m_units, TRUE, TRUE, FALSE, (m_units == MIL ? 0 : 3));
				::MakeCStringFromDimension(&ys, y, m_units, TRUE, TRUE, FALSE, (m_units == MIL ? 0 : 3));
				CString str;
				str.Format("    removing zero length or colinear sides x=%s y=%s\r\n", xs, ys);
				m_dlg_log->AddLine(str);
				m_dlg_log->UpdateWindow();
			}
		}
	}
	return reDr;
}

void CFreePcbDoc::OnToolsCheckCopperAreas()
{
	CString str;
    m_view->CancelSelection();
	m_dlg_log->ShowWindow( SW_SHOW );   
	m_dlg_log->UpdateWindow();
	m_dlg_log->BringWindowToTop();
	m_dlg_log->Clear();
	m_dlg_log->UpdateWindow();
	static int bMesBox = 0;
	cnet * net = m_nlist->GetFirstNet(); 
	BOOL new_event = TRUE; 
	int Total_num = 0, Deleted_num = 0, nerrors = 1;
	while( net ) 
	{
		if( net->nareas > 0 )
		{
			str.Format( "\r\nnet \"%s\": %d areas\r\n", net->name, net->nareas ); 
			m_dlg_log->AddLine( str );
			m_view->SaveUndoInfoForAllAreasInNet( net, new_event, m_undo_list ); 
			new_event = FALSE;
			//
			// removing zero length or colinear sides
			str.Format( "  checking for zero length or colinearity\r\n");
			m_dlg_log->AddLine( str );
			m_dlg_log->UpdateWindow();
			for( int ia=0; ia<net->nareas; ia++ )
			{
				CPolyLine * ap = net->area[ia].poly;
				Total_num++;
				BOOL reDraw = RemovingZeroLengthOrColinearSides(ap);
				if (reDraw)
				{
					m_nlist->SetAreaHatch(net, ia); // ap->Draw();
					new_event = TRUE;
					Deleted_num++;
				}
			}
			
			// check intersecting (in contour)
			str.Format( "  checking for intersections of outline sides\r\n");
			m_dlg_log->AddLine( str );
			m_dlg_log->UpdateWindow();
			for( int ia=0; ia<net->nareas; ia++ )
			{
				CPolyLine * ap = net->area[ia].poly;
				int nco = ap->GetNumContours();
				int x,y;
				if( ap->GetNumCorners() > 3 )
				{
					for( int ico=0; ico<nco; ico++ )
					{
						int i,xi,yi,xf,yf,side_style_1;
						int min_i = ap->GetContourStart(ico);
						int max_i = ap->GetContourEnd(ico);
						for( int i = min_i; i<(max_i-2); i++ )
						{
							xi = ap->GetX(i);
							yi = ap->GetY(i);
							side_style_1 = ap->GetSideStyle(i);
							xf = ap->GetX(i+1);
							yf = ap->GetY(i+1);
							for(int i2=i+2; i2<max_i; i2++ )
							{
								int x2i = ap->GetX(i2);
								int y2i = ap->GetY(i2);
								int side_style_2 = ap->GetSideStyle(i2);
								int x2f = ap->GetX(i2+1);
								int y2f = ap->GetY(i2+1);	
								int d = GetClearanceBetweenSegments( xi, yi, xf, yf, side_style_1, 0,
											x2i, y2i, x2f, y2f, side_style_2, 0, m_pcbu_per_wu*2, &x, &y );
								if( i2 == i+2 )
								{
									CPoint pb(xi,yi);
									CPoint p(xf,yf);
									CPoint pn(x2i,y2i);
									float an = Angle(pb,p,pn);
									if( d < m_pcbu_per_wu )
									{
										new_event = TRUE; 
										Deleted_num++;									
										if(/*( an > -1.0 && an < 1.0 ) ||*/ an < -179 || an > 179 )
											ap->DeleteCorner(i+1,1,1,0);
										else
											ap->DeleteCorner(i+2,1,1,0);
										i2--;
										max_i--;
										CString xs,ys;
										::MakeCStringFromDimension( &xs, x, m_units, TRUE, TRUE, FALSE, (m_units==MIL?0:3) );
										::MakeCStringFromDimension( &ys, y, m_units, TRUE, TRUE, FALSE, (m_units==MIL?0:3) );
										str.Format( "    removing corner of colinear sides x=%s y=%s\r\n", xs, ys );
										m_dlg_log->AddLine( str );	
										m_dlg_log->UpdateWindow();
									}
									else if( an < -179 || an > 179 )
									{
										new_event = TRUE; 
										Deleted_num++;
										ap->DeleteCorner(i+1,1,1,0);
										i2--;
										max_i--;
										CString xs,ys;
										::MakeCStringFromDimension( &xs, xf, m_units, TRUE, TRUE, FALSE, (m_units==MIL?0:3) );
										::MakeCStringFromDimension( &ys, yf, m_units, TRUE, TRUE, FALSE, (m_units==MIL?0:3) );
										str.Format( "    removing bad corner x=%s y=%s\r\n", xs, ys );
										m_dlg_log->AddLine( str );	
										m_dlg_log->UpdateWindow();
									}
								}
								else if( d < m_pcbu_per_wu )
								{
									CString xs,ys;
									::MakeCStringFromDimension( &xs, x, m_units, TRUE, TRUE, FALSE, (m_units==MIL?0:3) );
									::MakeCStringFromDimension( &ys, y, m_units, TRUE, TRUE, FALSE, (m_units==MIL?0:3) );
									str.Format( "    Warning: intersecting area sides x=%s y=%s\r\n", xs, ys );
									m_dlg_log->AddLine( str );
									m_dlg_log->UpdateWindow();
								}
							}
						}
						i = max_i;
						xi = ap->GetX(max_i);
						yi = ap->GetY(max_i);
						side_style_1 = ap->GetSideStyle(max_i);
						xf = ap->GetX(min_i);
						yf = ap->GetY(min_i);
						for(int i2=min_i+1; i2<(max_i-1); i2++ )
						{
							int x2i = ap->GetX(i2);
							int y2i = ap->GetY(i2);
							int side_style_2 = ap->GetSideStyle(i2);
							int x2f = ap->GetX(i2+1);
							int y2f = ap->GetY(i2+1);
							int d = GetClearanceBetweenSegments( xi, yi, xf, yf, side_style_1, 0,
								x2i, y2i, x2f, y2f, side_style_2, 0, m_pcbu_per_wu*2, &x, &y );
							if( d < m_pcbu_per_wu )
							{
								if( i2 == min_i+1 )
								{
									new_event = TRUE; 
									Deleted_num++;
									CPoint pb(xi,yi);
									CPoint p(xf,yf);
									CPoint pn(x2i,y2i);
									float an = Angle(pb,p,pn);
									if( an < -179 || an > 179 )
										ap->DeleteCorner(min_i,1,1,0);
									else
										ap->DeleteCorner(min_i+1,1,1,0);
									i2--;
									max_i--;
									CString xs,ys;
									::MakeCStringFromDimension( &xs, x, m_units, TRUE, TRUE, FALSE, (m_units==MIL?0:3) );
									::MakeCStringFromDimension( &ys, y, m_units, TRUE, TRUE, FALSE, (m_units==MIL?0:3) );
									str.Format( "    removing corner of colinear sides x=%s y=%s\r\n", xs, ys );
									m_dlg_log->AddLine( str );
								}
								else
								{
									CString xs,ys;
									::MakeCStringFromDimension( &xs, x, m_units, TRUE, TRUE, FALSE, (m_units==MIL?0:3) );
									::MakeCStringFromDimension( &ys, y, m_units, TRUE, TRUE, FALSE, (m_units==MIL?0:3) );
									str.Format( "    Warning: intersecting area sides x=%s y=%s\r\n", xs, ys );
									m_dlg_log->AddLine( str );
								}
								m_dlg_log->UpdateWindow();
							}
						}
					}
				}
				m_nlist->SetAreaHatch( net, ia ); // redraw
			}
			// check for minimum number of corners and closed contours
			for( int ia=0; ia<net->nareas; ia++ )
			{
				int nc = net->area[ia].poly->GetNumCorners();
				if( nc < 3 )
				{
					str.Format( "    area %d has only %d corners\r\n", ia+1, nc );
					m_dlg_log->AddLine( str );
					m_dlg_log->UpdateWindow();
				}
				else
				{
					if( !net->area[ia].poly->GetClosed() )
					{
						str.Format( "    area %d is not closed\r\n", ia+1 );
						m_dlg_log->AddLine( str );
						m_dlg_log->UpdateWindow();
					}
				}
			}
			// check all areas in net for self-intersection
			str.Format( "  checking all areas in net for self-intersection\r\n");
			m_dlg_log->AddLine( str );
			m_dlg_log->UpdateWindow();
			for( int ia=0; ia<net->nareas; ia++ )
			{
				BOOL noMess = 1;
				str.Format( "    area %d ", ia+1 );
				m_dlg_log->AddLine( str );
				m_dlg_log->UpdateWindow();
				int ret = m_nlist->ClipAreaPolygon( net, ia, -1, FALSE, FALSE, TRUE );
				if( ret == 1 )
				{
					str.Format( "\r\n    area %d is self-intersecting, areas will be renumbered", ia+1 );
					m_dlg_log->AddLine( str );
					noMess = 0;
				}
				//excl areas
				int bUndoA = 0;
				int na = net->nareas;
				int mem_hatch = net->area[ia].poly->GetHatch();
				int mem_wid = net->area[ia].poly->GetW();
				if( mem_hatch == CPolyLine::NO_HATCH && mem_wid == 0 )
				{//
				}//
				else if( mem_hatch == CPolyLine::DIAGONAL_FULL )
				{//
				}//
				else	
				{
					int crop_flags = 0;
					setbit(	crop_flags, MC_PADS );
					setbit(	crop_flags, MC_SEGS );
					setbit(	crop_flags, MC_AREAS );
					setbit(	crop_flags, MC_HOLES );
					setbit(	crop_flags, MC_TEXTS );
					setbit(	crop_flags, MC_ALL_NETS );
					setbit(	crop_flags, MC_VALIDATE );
					{
						AddBoardHoles(); // valid
						bUndoA = 1;
					}
					m_view->SaveUndoInfoForArea( net, ia, CNetList::UNDO_AREA_MODIFY, TRUE, m_undo_list );
					if (mem_hatch != CPolyLine::NO_HATCH)
						net->area[ia].poly->SetHatch(CPolyLine::NO_HATCH);
					if (mem_wid == 0)
						net->area[ia].poly->SetW(NM_PER_MIL);
					m_nlist->AddCutoutsForArea( net,
												ia, 
												NULL,
												m_fill_clearance + m_dr.trace_width/2, 
												m_fill_clearance + m_dr.trace_width/2, 
												m_fill_clearance + m_dr.trace_width/2,
												m_hole_clearance + m_dr.trace_width/2,
												m_fill_clearance + m_dr.trace_width/2,
												m_fill_clearance + m_dr.trace_width/2,
												m_fill_clearance + m_dr.trace_width/2,
												m_thermal_clearance,
												m_thermal_width,
												m_bSMT_copper_connect,
												m_mlist, 
												m_cam_flags,
												crop_flags);
					
				}
				int nAreas = 0;
				ret = m_nlist->ClipAreaPolygon( net, ia, -1, FALSE, FALSE, TRUE, &nAreas );
				if( ret == INT_MAX )
				{
					str.Format( ": incomplete check" );
					m_dlg_log->AddLine( str );
					m_dlg_log->BringWindowToTop();
					m_dlg_log->UpdateWindow();
					CWnd* wnd = AfxGetMainWnd();
					if (wnd)
						wnd->UpdateWindow();
				}
				if( ret == -1 )
				{
					str.Format( "\r\n    area %d is self-intersecting with arcs", ia+1 );
					m_dlg_log->AddLine( str );
					noMess = 0;
				}
				if( nAreas > 1 )
				{
					int Cmin = net->area[ia].poly->GetNumCorners();
					int x = net->area[ia].poly->GetX(0);
					int y = net->area[ia].poly->GetY(0);
					int min_in = 0;
					for( int in=na; in<net->nareas; in++ )
						if( Cmin > net->area[in].poly->GetNumCorners() )
						{
							Cmin = net->area[in].poly->GetNumCorners();
							x = net->area[in].poly->GetX(0);
							y = net->area[in].poly->GetY(0);
							min_in = in;
						}
					CString xs,ys;
					::MakeCStringFromDimension(&xs,x,m_units,1,1,1,1);
					::MakeCStringFromDimension(&ys,y,m_units,1,1,1,1);
					str.Format( "\r\n    WARNING: area %d of net \"%s\" is torn into %d islands x=%s, y=%s", ia+1, net->name, nAreas, xs, ys );
					noMess = 0;
					id id_a = net->id;
					id_a.st = ID_AREA;
					id_a.i = min_in;
					id_a.sst = ID_SIDE;
					id_a.ii = 0;
					DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREA_TORN, &str,
						&net->name, &net->name, id_a, id_a, x, y, x, y, 0, 0 );
					if( dre )
					{
						if( m_dlg_log )
							m_dlg_log->AddLine( str );
					}	
					int OldNumRatlines = m_nlist->GetNumRatlines( net );
					m_nlist->OptimizeConnections( net, -1, FALSE, 0, FALSE );
					int ratx, raty;
					CString pinNames="";
					cpart * Part_1 = NULL;
					cpart * Part_2 = NULL;
					id id1;
					id id2;
					if( m_nlist->GetNumRatlines( net, &ratx, &raty, &pinNames, &Part_1, &Part_2, &id1, &id2 ) != OldNumRatlines )
					{
						if( Part_1 && Part_2 )
						{
							str.Format( "\r\n    ERROR %d: The pin connection is broken (%s)", nerrors, pinNames );
							noMess = 0;
							DRError * dre = m_drelist->Add( nerrors, DRError::PAD_PAD, &str,
								&Part_1->ref_des, &Part_2->ref_des, id1, id2, ratx, raty, ratx, raty, 0, LAY_TOP_COPPER );
							if( dre )
							{
								nerrors++;
								if( m_dlg_log )
									m_dlg_log->AddLine( str );
							}
						}
					}
				}
				m_dlg_log->UpdateWindow();
				if( bUndoA )
				{
					OnEditUndo();		// undo the area change first
					CancelBoardHoles();	  
				}
				m_nlist->SetAreaHatch( net, ia ); // net->area[ia].poly->Draw(m_dlist);
				for( int i=net->nareas; i>na; i-- )
					m_nlist->RemoveArea( net, i-1 );
				if( noMess && ret != INT_MAX )
				{
					str.Format( " is OK\r\n" );
					m_dlg_log->AddLine( str );
				}
				else
				{
					str.Format( "\r\n" );
					m_dlg_log->AddLine( str );
				}
				m_dlg_log->BringWindowToTop();
				m_dlg_log->UpdateWindow();
				CWnd * wnd = AfxGetMainWnd();
				if(wnd)
					wnd->UpdateWindow();
			}
			// check all areas in net for intersection
			if( net->nareas > 1 )
			{
				str.Format( "  checking all areas in net for intersection\r\n");
				m_dlg_log->AddLine( str );
				m_dlg_log->UpdateWindow();
				for( int ia1=0; ia1<net->nareas-1; ia1++ ) 
				{
					str.Format( "    area %d ", ia1+1 );
					m_dlg_log->AddLine( str );
					m_dlg_log->UpdateWindow();
					BOOL mod_ia1 = FALSE;
					for( int ia2=net->nareas-1; ia2 > ia1; ia2-- )
					{
						if( net->area[ia1].poly->GetLayer() == net->area[ia2].poly->GetLayer() &&
							net->area[ia1].poly->GetHatch() == net->area[ia2].poly->GetHatch() && 
							net->area[ia1].poly->GetW() == net->area[ia2].poly->GetW() &&
							(net->area[ia1].poly->GetHatch() || net->area[ia1].poly->GetW() ) )
						{
							// check ia2 against 1a1 
							int ret = m_nlist->TestAreaIntersection( net, ia1, ia2 );
							//if( ret == 2 ) 
							//{
							//	str.Format( "    areas %d and %d have an intersecting arc, can't be combined\r\n", ia1+1, ia2+1 );
							//	m_dlg_log->AddLine( str );
							//}
							//else if( ret == 1 && net->area[ia1].utility2 == -1 )
							//{
							//	str.Format( "    areas %d and %d intersect but can't be combined due to self-intersecting arcs in area %d\r\n", 
							//		ia1+1, ia2+1, ia1+1 );
							//	m_dlg_log->AddLine( str );
							//}
							//else if( ret == 1 && net->area[ia2].utility2 == -1 )
							//{
							//	str.Format( "    areas %d and %d intersect but can't be combined due to self-intersecting arcs in area %d\r\n", 
							//		ia1+1, ia2+1, ia2+1 );
							//	m_dlg_log->AddLine( str );
							//}
							//else 
							if( ret > 0 )
							{
								if( bMesBox == 0 )
									bMesBox = AfxMessageBox(G_LANGUAGE == 0 ? 
										"Crossing copper areas of similar style were found. Should they be combined for optimization?":
										"Обнаружены пересекающиеся медные полигоны похожего стиля. Следует ли их объединить для оптимизации?", MB_YESNO);
								if( bMesBox == IDYES )
								{
									new_event = TRUE; 
									ret = m_nlist->CombineAreas( net, ia1, ia2 );
									if( ret == 1 )
									{
										str.Format( "\r\n    areas %d and %d intersect and have been combined", ia1+1, ia2+1 );
										m_dlg_log->AddLine( str );
										m_dlg_log->UpdateWindow();
										mod_ia1 = TRUE;
									}
								}
							}
						}
					}
					if( mod_ia1 )
					{
						ia1--;		// if modified, we need to check it again
						str.Format( "\r\n" );
						m_dlg_log->AddLine( str );
					}
					else 
					{
						str.Format( " is OK\r\n" );
						m_dlg_log->AddLine( str );
					}
				}
			}
		}
		net = m_nlist->GetNextNet(/*LABEL*/); 
	}
	str.Format( "Total number of corners = %d\r\n", Total_num );
		m_dlg_log->AddLine( str );
	if( Deleted_num )
	{
		str.Format( "Number of deleted corners = %d\r\n", Deleted_num );
			m_dlg_log->AddLine( str );
	}
	str.Format( "*******  DONE *******\r\n" ); 
	m_dlg_log->AddLine( str );
	if( m_vis[LAY_RAT_LINE] && !m_auto_ratline_disable )
		m_nlist->OptimizeConnections();
	ProjectModified( TRUE );
	m_view->Invalidate( FALSE );
	bMesBox = 0;
}

void CFreePcbDoc::OnToolsCheckTraces()
{
	CString str;
	ResetUndoState();
	m_view->CancelSelection();
	m_dlg_log->ShowWindow( SW_SHOW );   
	m_dlg_log->UpdateWindow();
	m_dlg_log->BringWindowToTop();
	m_dlg_log->Clear();
	m_dlg_log->UpdateWindow();
	m_dlg_log->AddLine( "Checking traces for zero-length or colinear segments:\r\n" );
	m_nlist->CleanUpAllConnections( &str );
	m_dlg_log->AddLine( str );
	m_dlg_log->AddLine( "\r\n*******  DONE *******\r\n" );
}

void CFreePcbDoc::OnEditSelectAll()
{
	if (theApp.m_view_mode == theApp.FOOTPRINT)
		return;
	m_view->CancelSelection();
	id _id( ID_PART_DEF );
	for( cpart * p=m_plist->GetFirstPart(); p; p=m_plist->GetNextPart(p) )
		if( p->shape )
			m_view->NewSelect( p, &_id, 0, 0 );
	for( cnet * n=m_nlist->GetFirstNet(); n; n=m_nlist->GetNextNet(/*LABEL*/) )
	{
		_id.Set( ID_NET, ID_CONNECT, 0, ID_SEG, 0 );
		for( _id.i=0; _id.i<n->nconnects; (_id.i)++ )
			for( _id.ii=0; _id.ii<n->connect[_id.i].nsegs; (_id.ii)++ )
				m_view->NewSelect( n, &_id, 0, 0 );
		_id.Set( ID_NET, ID_AREA, 0, ID_SIDE, 0 );
		for( _id.i=0; _id.i<n->nareas; (_id.i)++ )
			for( _id.ii=0; _id.ii<n->area[_id.i].poly->GetNumCorners(); (_id.ii)++ )
				m_view->NewSelect( n, &_id, 0, 0 );
	}
	int it=0;
	_id.Set(ID_TEXT_DEF);
	for( CText * t=m_tlist->GetFirstText(); t; t=m_tlist->GetNextText(&it) )
		m_view->NewSelect( t, &_id, 0, 0 );
	for( int i=0; i<m_outline_poly.GetSize(); i++ )
	{
		_id = m_outline_poly[i].GetId();
		_id.sst = ID_SIDE;
		_id.i = i;
		int nc = m_outline_poly[_id.i].GetNumCorners();
		if( m_outline_poly[_id.i].GetClosed() == 0 )
			nc--;
		for( int ii=0; ii<nc; ii++ )
		{
			_id.ii = ii;
			m_view->NewSelect( NULL, &_id, 0, 0 );
		}
	}
	m_view->SetCursorMode( CUR_GROUP_SELECTED );
	m_dlist->HighlightAll();
	m_view->Invalidate(FALSE);
}

void CFreePcbDoc::OnEditPasteFromFile()
{
	// force old-style file dialog by setting size of OPENFILENAME struct
	CWnd * WND = theApp.GetMainWnd();
	CString filename = RunFileDialog( 1, "pas" ); 
	if ( filename.GetLength() )
	{ 
		PasteFromFile(filename, FALSE);
	}
}

void CFreePcbDoc::PasteFromFile( CString pathname, BOOL bwDialog )
{
	BOOL FPC = 1;
	if( pathname.GetLength() < 4 )
		FPC = 0;
	else if( pathname.Right(4).MakeLower() != ".fpc" && pathname.Right(6).MakeLower() != ".fpc.b" )
		FPC = 0;
	//
	if( !FPC )
	{
		// error opening project file
		CString mess;
		mess.Format(G_LANGUAGE == 0 ? "Currently only FPC files are supported.":"В настоящее время поддерживаются только файлы FPC.");
		AfxMessageBox( mess );
		return;
	}
	// read project file
	ResetUndoState();
	CStdioFile pcb_file;
	int err = pcb_file.Open( pathname, CFile::modeRead, NULL );
	if( !err )
	{
		// error opening project file
		CString mess;
		mess.Format(G_LANGUAGE == 0 ? "Unable to open file %s":"Невозможно открыть файл %s", pathname);
		AfxMessageBox( mess );
		return;
	}
	// clear clipboard objects to hold group
	ClipClear();
	CMapStringToPtr cache_map;		// incoming footprints
	CString key;
	void * ptr;
	CShape * s;
	try
	{
		// get layers
		int fpos = 0;
		CString in_str = "";
		float ver = m_version;
		int n_copper_lrs = 32;
		while( in_str.Left(2) != "[f" )
		{
			fpos = pcb_file.GetPosition();
			pcb_file.ReadString( in_str );
			//
			if( in_str.Left(16) == "n_copper_layers:" )
			{
				n_copper_lrs = atoi( in_str.Right( in_str.GetLength()-16 ) );
				n_copper_lrs = min(14, n_copper_lrs);
			}
			else if( in_str.Left(13) == "file_version:" )
			{
				ver = atof( in_str.Right( in_str.GetLength()-13 ) );
				if( ver < 2.022 )
				{
					AfxMessageBox(G_LANGUAGE == 0 ? 
						"You are trying to insert data from a file created in a previous version of this program. File version should not be lower than 2.022. Save this file in the latest version of this program and try again.":
						"Вы пытаетесь вставить данные из файла, созданного в предыдущей версии этой программы. Версия файла не должна быть ниже 2.022. Сохраните этот файл в последней версии этой программы и попробуйте еще раз.", MB_OK);
					pcb_file.Close();
					return;
				}
			}
		}		
		if( n_copper_lrs > m_num_copper_layers )
		{
			CString mess = "The group file that you are pasting has more layers than the current project.\n\n";
			mess += "This is not allowed.\n\n";
			mess += "You can reduce the number of layers in the group file by editing it in FreePCB.";
			if (G_LANGUAGE)
			{
				mess = "Вставляемый групповой файл содержит больше слоев, чем текущий проект..\n\n";
				mess += "Это является недопустимым.\n\n";
				mess += "Вы можете уменьшить количество слоев в групповом файле, отредактировав его в ПлатФорм.";
			}
			AfxMessageBox( mess, MB_OK );
			pcb_file.Close();
			return;
		}
		int u = m_units;
		CMainFrame * pMain = (CMainFrame*) AfxGetApp()->m_pMainWnd;
		if( !pMain ) 
		{
			pcb_file.Close();
			return;
		}
		CString str;
		// read footprints
		str.Format( "Reading footprints");
		pMain->DrawStatus( 3, &str );
		while( in_str.Left(12) != "[footprints]" )
		{
			fpos = pcb_file.GetPosition();
			pcb_file.ReadString( in_str );
		}
		pcb_file.Seek( fpos, CFile::begin );
		ReadFootprints( &pcb_file, &cache_map );

		// copy footprints to project cache if necessary
		CString diff_footprints="",shift_footprints="";
		for( POSITION pos = cache_map.GetStartPosition(); pos != NULL; )
		{
			cache_map.GetNextAssoc( pos, key, ptr );
			s = (CShape*)ptr;
			if( !m_footprint_cache_map.Lookup( s->m_name, ptr ) )
			{
				// copy shape to project cache
				m_footprint_cache_map.SetAt( s->m_name, s );
				// RemoveKey
				cache_map.RemoveKey( key );
			}
			else
			{
				CShape * sh = (CShape*)ptr;
				int CSH = s->ComparePins(sh);
				if( CSH == 0 )
				{
					if( diff_footprints.GetLength() )
						diff_footprints += ", ";
					diff_footprints += s->m_name;
				}
				else if( CSH > 1 )
				{
					if( shift_footprints.GetLength() )
						shift_footprints += ", ";
					shift_footprints += s->m_name;
				}
			}
		}

		// remove cache map
		for( POSITION pos = cache_map.GetStartPosition(); pos != NULL; )
		{
			cache_map.GetNextAssoc( pos, key, ptr );
			s = (CShape*)ptr;
			delete s;
			cache_map.RemoveKey( key );
		}
		cache_map.RemoveAll();

		//
		if( diff_footprints.GetLength() )
		{
			CString mess = "Library conflict! The group file that you are pasting contains modified footprints (different pin names and / or their number). ";
			mess += "This is not allowed. ";
			mess += "You can prepare this (or that) project for panelizing using the 'Footprint Library Manager' application from the Utilities menu.\n";
			mess += "List of Modified Footprints:\n";
			if (G_LANGUAGE)
			{
				mess = "Конфликт библиотек! Файл группы, который вы вставляете, содержит измененные футпринты (разные имена выводов и/или их количество). ";
				mess += "Это не разрешено. ";
				mess += "Вы можете подготовить тот (или иной) проект для панелизации с помощью приложения «Менеджер библиотек» из меню «Утилиты».\n";
				mess += "Список измененных футпринтов:\n";
			}
			mess += diff_footprints;
			AfxMessageBox( mess, MB_OK );
			pcb_file.Close();
			return;
		}
		if( shift_footprints.GetLength() )
		{
			CString mess = "WARNING! The group file that you are pasting contains modified footprints. ";
			mess += "Offset footprint list: ";
			mess += shift_footprints;
			mess += "\n\nThe file will be inserted into the project, but FreePcb-2 does not guarantee the correct location of these parts on the board!";
			mess += "\n\n(You can prepare this (or that) project for panelizing using the 'Footprint Library Manager' application from the Utilities menu.)";
			if (G_LANGUAGE)
			{
				mess = "Внимание! Групповой файл содержит изменённые футпринты. ";
				mess += "А именно: ";
				mess += shift_footprints;
				mess += "\n\nФайл будет вставлен в проект, но ПлатФорм не гарантирует правильное расположение этих деталей на плате!";
				mess += "\n\n(Подготовить тот (или иной) проект к панелизации можно с помощью приложения «Менеджер библиотек» из меню «Утилиты»..)";
			}
			AfxMessageBox( mess, MB_OK );
		}
		// read board outline
		str.Format( "Reading board outline");
		pMain->DrawStatus( 3, &str );
		ReadBoardOutline( &pcb_file, &clip_outline_poly );

		// read sm_cutouts
		str.Format( "Reading solder mask cutouts");
		pMain->DrawStatus( 3, &str );
		ReadSolderMaskCutouts( &pcb_file, &clip_outline_poly );

		// read graphics
		str.Format( "Reading graphics");
		pMain->DrawStatus( 3, &str );
		ReadGraphics( &pcb_file, &clip_outline_poly );

		// read parts, 
		str.Format( "Reading parts");
		pMain->DrawStatus( 3, &str );
		clip_plist->ReadParts( &pcb_file );

		// nets 
		str.Format( "Reading nets");
		pMain->DrawStatus( 3, &str );
		clip_nlist->ReadNets( &pcb_file, m_file_version );

		// and texts
		str.Format( "Reading texts");
		pMain->DrawStatus( 3, &str );
		clip_tlist->ReadTexts( &pcb_file, m_file_version );

		// Read Merges
		ReadMerges( &pcb_file, clip_mlist );
		pcb_file.Close();
		str.Format( "Complete");
		pMain->DrawStatus( 3, &str );
	}
	catch( CString * err_str )
	{
		// parsing error
		AfxMessageBox( *err_str );
		delete err_str;
		pcb_file.Close();
		return;
	}
	m_view->OnGroupPaste(bwDialog, TRUE);
	ClipClear();
}

// Purge footprunts from local cache unless they are used in
// partlist or clipboard
//
void CFreePcbDoc::PurgeFootprintCache()
{
	POSITION pos;
	CString key;
	void * ptr;

	for( pos = m_footprint_cache_map.GetStartPosition(); pos != NULL; )
	{
		m_footprint_cache_map.GetNextAssoc( pos, key, ptr );
		CShape * shape = (CShape*)ptr;
		if( m_plist->GetNumFootprintInstances( shape ) == 0
			&& clip_plist->GetNumFootprintInstances( shape ) == 0 )
		{
			// purge this footprint
			delete shape;
			m_footprint_cache_map.RemoveKey( key );
		}
	}
}

void CFreePcbDoc::OnFileGerbV(CString G, CString app)
{
	CString ALL_STR = "";
	CFileFind m_find_dir;
	BOOL bWorking = m_find_dir.FindFile(G+"\\*.*");  	
	while  (bWorking)  
	{  	
		bWorking = m_find_dir.FindNextFile();
		if( !m_find_dir.IsDots() && !m_find_dir.IsDirectory())   
		{  
			CString m_gName = m_find_dir.GetFileName();
			if( m_gName.Right(4).MakeLower() == ".gbr" || m_gName.Right(4).MakeLower() == ".drl" )
				ALL_STR += "\"" + m_find_dir.GetFilePath() + "\" ";
		}			
	}
	// TODO: Add your command handler code here
	SHELLEXECUTEINFO info = {0};
	CString fn;
	CString ps;
	fn.Format("\"%s\"", app);
	if( app.Find("ViewMate") > 0 )
		ps.Format("\"%s\"", G); 
	else
		ps = ALL_STR;		
	info.cbSize = sizeof(SHELLEXECUTEINFO);
    info.fMask = NULL;
    info.hwnd = NULL;
    info.lpVerb = NULL;
    info.lpFile = fn;
    info.lpParameters = ps;
    info.lpDirectory = NULL;
    info.nShow = SW_SHOW;//SW_MAXIMIZE; //SW_HIDE
    info.hInstApp = NULL;
	int INF = ShellExecuteEx(&info);
	if (INF == 0)
	{
		if (G_LANGUAGE == 0)
			AfxMessageBox("There is a 'Shortcut' folder in the FreePcb directory. Put there a shortcut *.lnk referring to a Gerber file viewer program (for example Pentalogix's ViewMate).");
		else 
			AfxMessageBox("В каталоге ПлатФорм есть папка с названием \"Shortcut\". Поместите туда ярлык *.lnk, ссылающийся на программу просмотра файлов Gerber (например, ViewMate от Pentalogix).");
	}
}

void CFreePcbDoc::OnFileExportDsn()
{
	AfxMessageBox(G_LANGUAGE == 0 ? 
		"Sorry, this option is temporarily not working":
		"Извините, эта опция временно не работает");
	return;
	if( m_project_modified )
	{
		CString mess = "This function creates a .dsn file from the last saved project file.\n";
		mess += "However, your project has changed since it was last saved.\n\n";
		mess += "Do you want to save the project now ?";
		if (G_LANGUAGE)
		{
			mess = "Эта функция создает файл .dsn из последнего сохраненного файла проекта. ";
			mess += "Однако ваш проект изменился с момента последнего сохранения.\n\n";
			mess += "Вы хотите сохранить проект сейчас?";
		}
		int ret = AfxMessageBox( mess, MB_YESNOCANCEL );
		if( ret == IDCANCEL )
			return;
		else if( ret == IDYES )
			OnFileSave();
	}
	CDlgExportDsn dlg;
	CString dsn_filepath = m_pcb_full_path;
	int dot_pos = dsn_filepath.ReverseFind( '.' );
	if( dot_pos != -1 )
		dsn_filepath = dsn_filepath.Left( dot_pos );
	dsn_filepath += ".dsn";
	int num_polys = m_outline_poly.GetSize();
	if( m_dsn_signals_poly >= num_polys )
		m_dsn_signals_poly = 0;
	if( m_dsn_bounds_poly >= num_polys )
		m_dsn_bounds_poly = 0;
	dlg.Initialize( &dsn_filepath, GetNumBoards(), 
						m_dsn_bounds_poly, m_dsn_signals_poly, m_dsn_flags );
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		m_dlg_log->ShowWindow( SW_SHOW );   
		m_dlg_log->UpdateWindow();
		m_dlg_log->BringWindowToTop();
		m_dlg_log->Clear();
		m_dlg_log->UpdateWindow(); 
		//
		m_dsn_flags = dlg.m_flags;
		m_dsn_bounds_poly = dlg.m_bounds_poly;
		m_dsn_signals_poly = dlg.m_signals_poly;
		//OnFileSave();
		m_dlg_log->AddLine( "Saving project file: \"" + m_pcb_full_path + "\"\r\n" );  
		m_dlg_log->AddLine( "Creating .dsn file: \"" + dsn_filepath + "\"\r\n" );  
		CString commandLine = "\"" + m_app_dir + "\\fpcroute.exe\"";
		int from_to = m_dsn_flags & CDlgExportDsn::DSN_FROM_TO_MASK;
		if( from_to == CDlgExportDsn::DSN_FROM_TO_ALL )
			commandLine += " -F3";
		else if( from_to == CDlgExportDsn::DSN_FROM_TO_LOCKED )
			commandLine += " -F1";
		else if( from_to == CDlgExportDsn::DSN_FROM_TO_NET_LOCKED )
			commandLine += " -F2";
		if( m_dsn_flags & CDlgExportDsn::DSN_VERBOSE )
			commandLine += " -V"; 
		if( m_dsn_flags & CDlgExportDsn::DSN_INFO_ONLY )
			commandLine += " -I";
		if( m_dsn_bounds_poly != 0 || m_dsn_signals_poly != 0 ) 
		{
			CString str;
			str.Format( " -U%d,%d", m_dsn_bounds_poly+1, m_dsn_signals_poly+1 );
			commandLine += str;
		}
		commandLine += " \"" + m_pcb_full_path + "\"";
//		CString commandLine = "C:/freepcb/bin/RTconsole.exe  C:/freepcb/bin/fpcroute.exe -V C:/freepcb/bin/test";
		m_dlg_log->AddLine( "Run: " + commandLine + "\r\n" );  
		RunConsoleProcess( commandLine, m_dlg_log );
#if 0
		HANDLE hOutput, hProcess;
		hProcess = SpawnAndRedirect(commandLine, &hOutput, NULL); 
		if (!hProcess) 
		{
			m_dlg_log->AddLine( "Failed!\r\n" );
			return;
		}

		// if necessary, this could be put in a separate thread so the GUI thread is not blocked
		BeginWaitCursor();
		CHAR buffer[65];
		DWORD read;
		while (ReadFile(hOutput, buffer, 64, &read, NULL))
		{
			buffer[read] = '\0';
			m_dlg_log->AddLine( buffer );
		}
		CloseHandle(hOutput);
		CloseHandle(hProcess);
		EndWaitCursor();
#endif
	}
}

void CFreePcbDoc::OnFileImportSes()
{
	CDlgImportSes dlg;
	dlg.Initialize( &m_ses_full_path, &m_pcb_full_path, this );
	int ret = dlg.DoModal(); 
	if( ret == IDOK )
	{
		m_dlg_log->ShowWindow( SW_SHOW );   
		m_dlg_log->UpdateWindow();
		m_dlg_log->BringWindowToTop(); 
		m_dlg_log->Clear();
		m_dlg_log->UpdateWindow(); 
		// save current project if modified (including dialog parameters)
		if( dlg.m_ses_filepath != m_ses_full_path )
		{
			m_ses_full_path = dlg.m_ses_filepath;
			ProjectModified( TRUE );
		}
		if( m_project_modified )
		{
			int ret = AfxMessageBox(G_LANGUAGE == 0 ? 
				"Project modified, save before import (recommended) ?":
				"Проект изменен, сохранить перед импортом (рекомендуется) ?", MB_YESNO);
			if( ret == IDYES )
			{
				OnFileSave();
			}
			else
				ProjectModified( FALSE );
		}
		CString temp_file_name = "~temp$$$.fpc";   
		CString temp_routed_file_name = "~temp$$$_routed.fpc";
		CString temp_file_path = m_path_to_folder + "\\" + temp_file_name;
		CString temp_routed_file_path = m_path_to_folder + "\\" + temp_routed_file_name;
		struct _stat buf;
		int err = _stat( temp_file_path, &buf );
		if( !err )
		{
			m_dlg_log->AddLine( "Delete: " + temp_file_path + "\r\n" );  
			remove( temp_file_path );
		}
		err = _stat( dlg.m_routed_pcb_filepath, &buf );
		if( !err )
		{
			m_dlg_log->AddLine( "Delete: " + dlg.m_routed_pcb_filepath + "\r\n" );  
			remove( dlg.m_routed_pcb_filepath );
		}
		m_ses_full_path = dlg.m_ses_filepath;

		// save project as temporary file
		m_dlg_log->AddLine( "Save: " + temp_file_path + "\r\n" );
		CString old_pcb_filename = m_pcb_filename;
		CString old_pcb_full_path = m_pcb_full_path;
		m_pcb_filename = temp_file_name;
		m_pcb_full_path = temp_file_path;
		OnFileSave();

		// import session file
		CString verbose = "";
		if( dlg.m_bVerbose )
			verbose = "-V ";
		CString commandLine = "\"" + m_app_dir + "\\fpcroute.exe\" -B " + verbose + "\"" +
			temp_file_path + "\" \"" + m_ses_full_path + "\""; 
		m_dlg_log->AddLine( "Run: " + commandLine + "\r\n" );
		RunConsoleProcess( commandLine, m_dlg_log );
		err = _stat( temp_routed_file_path, &buf );
		if( err )
		{
			m_dlg_log->AddLine( "\r\nFpcROUTE failed to create routed project file: \"" + temp_routed_file_path + "\"\r\n" );  
			return;
		}
		m_dlg_log->AddLine( "\r\nRename: \"" + temp_routed_file_path + "\" to \"" + dlg.m_routed_pcb_filepath + "\"\r\n" );  
		err = rename( temp_routed_file_path, dlg.m_routed_pcb_filepath ); 
		if( err )
		{
			m_dlg_log->AddLine( "\r\nRenaming project file from " + temp_routed_file_path
				+ " to " + dlg.m_routed_pcb_filepath + " failed:\r\n" );
		}
		CString old_ses_full_path = m_ses_full_path;
		m_dlg_log->AddLine( "\r\nLoad: " + dlg.m_routed_pcb_filepath + "\r\n" );  
		OnFileAutoOpen( dlg.m_routed_pcb_filepath );
		m_ses_full_path = old_ses_full_path;
		m_dlg_log->AddLine( "Re-import: " + m_ses_full_path + "\r\n" );  
		ImportSessionFile( &m_ses_full_path, m_dlg_log, dlg.m_bVerbose );
		m_dlg_log->AddLine( "\r\n*********** Done ***********\r\n" );  
		ProjectModified( TRUE );
	}
}

void CFreePcbDoc::OnEditUndo()
{
	if( m_undo_list->m_num_items > 0 )
	{
		// undo last operation unless dragging something
		if( !m_view->CurDragging() )
		{		
			while( m_undo_list->Pop() )
			{
			}
			m_view->CancelSelection( FALSE );
			m_nlist->SetAreaConnections();
			m_view->SetDrawLayer( DISABLE_CHANGE_DRAW_LAYER );//OnEditUndo;
			m_view->Invalidate(FALSE);
		}
		if( m_view->m_merge_show )
		{
			m_dlist->CancelHighLight(0,1);
			m_view->ShowMerges();
			m_view->HighlightGroup();
		}
		m_bLastPopRedo = FALSE;
		ProjectModified( TRUE, FALSE );
	}
}

void CFreePcbDoc::OnEditRedo()
{
	if( m_redo_list->m_num_items > 0 )
	{
		// redo last operation unless dragging something
		m_bLastPopRedo = TRUE;
		if( !m_view->CurDragging() )
		{
			while( m_redo_list->Pop() )
			{
			}
			m_view->CancelSelection();
			m_nlist->SetAreaConnections();
			m_view->SetDrawLayer( DISABLE_CHANGE_DRAW_LAYER );//OnEditRedo;
			m_view->Invalidate();
		}
		if( m_view->m_merge_show )
		{
			m_dlist->CancelHighLight(0,1);
			m_view->ShowMerges();
			m_view->HighlightGroup();
		}
		m_bLastPopRedo = TRUE;
		ProjectModified( TRUE, FALSE );
	}
}

void CFreePcbDoc::ResetUndoState()
{
	m_undo_list->Clear();
	m_redo_list->Clear();
	m_bLastPopRedo = FALSE;
}


void CFreePcbDoc::OnRepeatDrc()
{
	if (theApp.m_view_mode == theApp.FOOTPRINT)
		return;
	m_nlist->OptimizeConnections(0,0,0);
	m_drelist->Clear();
	m_dlg_log->ShowWindow( SW_SHOW );
	m_dlg_log->UpdateWindow();
	m_dlg_log->BringWindowToTop(); 
	m_dlg_log->Clear();
	m_dlg_log->UpdateWindow(); 
	DRC();
	m_view->Invalidate( FALSE );
}

void CFreePcbDoc::OnFileGenerate3DFile()
{
	if (bNoFilesOpened)
	{
		return;
	}
	if (theApp.m_view_mode == theApp.FOOTPRINT)
	{
		return;
	}
	if( m_project_modified )
	{
		AfxMessageBox(G_LANGUAGE == 0 ? 
			"Project modified. To continue, you need to save the changes!":
			"Проект изменен. Чтобы продолжить, необходимо сохранить изменения!");
		return;
	}
	
	CString path = m_path_to_folder + "\\related_files\\openscad";
	struct _stat buf;
	int err = _stat( path, &buf );
	if( err )
	{
		_mkdir( path );
	}
	CString moduleName = m_name;
	CStringToLegalFileName( &moduleName );
	path += "\\" + moduleName + ".lib";
	CStdioFile file;
	double mu = (m_units==MM?NM_PER_MM:NM_PER_MIL);
	int ok = file.Open( path, CFile::modeCreate | CFile::modeWrite );
	if( ok )
	{
		CString str;
		int Mark = 1;
		m_plist->MarkAllParts(0);
		CArray<CString> foots;
		CArray<CShape*> shapes;
		foots.SetSize(0);
		shapes.SetSize(0);
		file.WriteString( "/* ___________________\n  |                   |\n  |     FOOTPRINTS    |\n  |___________________|\n*/\n");
		for( cpart * p=m_plist->GetFirstPart(); p; p=m_plist->GetNextPart(p) )
		{
			if( p->shape && p->utility != Mark )
			{
				CString nm = m_name + "_" + p->shape->m_name;
				CString full_path = p->shape->GenerateOpenscadFileA( &nm, 0 );
				
				int f = full_path.ReverseFind('\\');
				if( f < 0 )
					continue;
				//----------------
				nm = full_path.Mid( f+1, full_path.GetLength() - f - 1 );
				str.Format( "include <%s>\n", nm );
				file.WriteString( str );
				//----------------
				f = nm.Find(".");
				if( f < 0 )
					continue;
				nm.Truncate(f);
				foots.Add( nm );
				shapes.Add( p->shape );
				//----------------
				for( cpart * pp=m_plist->GetFirstPart(); pp; pp=m_plist->GetNextPart(pp) )
					if( p->shape == pp->shape )
						pp->utility = Mark;
			}
		}
		file.WriteString( "\n" );
		file.WriteString( "\n" );
		file.WriteString( "/* ___________________\n  |                   |\n  |       PARTS       |\n  |___________________|\n*/\n" );
		//
		// открываем  pcb module
		//
		str.Format( "module Pcb_%s (bAll=0)\n{\n", moduleName );
		file.WriteString( str );

		for( int i=0; i<foots.GetSize(); i++ )
		{
			CString fname = foots.GetAt(i);
			str.Format( "    if( bAll != 0 )\n      Draw_%s();\n", fname);
			file.WriteString(str);
			str.Format( "    else if( enable_draw_%s != 0 )\n      Draw_%s();\n", fname, fname);
			file.WriteString(str);
		}
		str.Format( "    if( bAll != 0 )\n      Draw_BO_%s(1);\n", moduleName);
		file.WriteString(str);
		str.Format( "    else if( enable_draw_board_outline != 0 )\n      Draw_BO_%s(0);\n", moduleName );
		file.WriteString( str );
		//
		// закрываем  pcb module
		//
		file.WriteString( "}\n" );
		file.WriteString( "\n" );
		file.WriteString( "\n" );
		str.Format( "/* ___________________\n  |                   |\n  |   BOARD OUTLINE   |\n  |___________________|\n*/\nmodule Draw_BO_%s (bAll=0)\n{\n", moduleName );
		file.WriteString( str );

		
		AddBoardHoles(); // valid
		MarkLegalElementsForExport(this);
		for( int i=0; i<m_outline_poly.GetSize(); i++ )
		{
			CPolyLine * bp = &m_outline_poly.GetAt(i);
			if (bp->GetUtility() == 0)
				continue;
			if( bp->GetLayer() == LAY_BOARD_OUTLINE )
			{
				str.Format( "    color( \"green\" )\n" );
				file.WriteString( str );
				str.Format("     render( convexity=3 )\n");
				file.WriteString(str);
				str.Format( "      translate([ 0.0, 0.0, -board_h/2.0 ])\n" );
				file.WriteString( str );
				str.Format( "        difference()\n        {\n" );
				file.WriteString( str );
				file.WriteString( "          $fn=20;\n" );
				CString PolyPts = bp->GetOpenscadPolyPts( m_units, 20, 21, 0, 0, 0 );
				BOOL Flag = 0;
				do
				{
					if( Flag )
						str.Format( "          linear_extrude( board_h*2.0, center=true )\n" );
					else
						str.Format( "          linear_extrude( board_h, center=true )\n" ); 
					Flag = TRUE;
					file.WriteString( str );
					str.Format( "            polygon([" );
					file.WriteString( str );
					file.WriteString( PolyPts );
					file.WriteString( "]);\n" );
					PolyPts = bp->GetOpenscadPolyPts( m_units, 20, 21, 0, 0 );
				} while( PolyPts.GetLength() );
				//
				// пишем отверстия
				//
				str.Format( "          if( enable_draw_holes != 0 )\n          {\n" );
				file.WriteString( str );
				for( cpart * p=m_plist->GetFirstPart(); p; p=m_plist->GetNextPart(p) )
				{
					if( p->shape )
					{
						RECT thru;
						int np = m_plist->GetPartThruPadsRect( p, &thru );
						if( np == 0 || thru.left == INT_MAX )
							continue;
						BOOL ok1 = -1;
						for(int sh=0; sh<shapes.GetSize(); sh++)
						{
							if( p->shape == shapes.GetAt(sh) )
							{
								ok1 = sh;
								break;
							}
						}
						if( ok1 == -1 )
							continue;
						for( int ipin=0; ipin<p->shape->GetNumPins(); ipin++ )
						{
							if( p->shape->m_padstack[ipin].hole_size )
							{
								CPoint pinPoint = m_plist->GetPinPoint( p, ipin, p->side, p->angle );
								double pinX = pinPoint.x / mu;
								double pinY = pinPoint.y / mu;
								
								if( p->shape->m_padstack[ipin].top.shape == PAD_NONE &&
									p->shape->m_padstack[ipin].bottom.shape == PAD_NONE )
								{
									double HoleSize = (p->shape->m_padstack[ipin].hole_size) / mu;
									str.Format( "           translate([ %.3f, %.3f, 0.0 ])\n              cylinder( d=%.3f, h=board_h*2.0, center=true );\n", pinX, pinY, HoleSize );
									file.WriteString( str );
								}
								else
								{
									double HoleSize = ((double)p->shape->m_padstack[ipin].hole_size*cos(22.5*M_PI/180.0)-100000) / mu;
									CString fname = foots.GetAt(ok1);
									str.Format( "           if( bAll != 0 )\n");
									file.WriteString(str);
									str.Format( "            translate([ %.3f, %.3f, 0.0 ])\n              cube([ %.3f, %.3f, board_h*2.0 ], center=true );\n", pinX, pinY, HoleSize, HoleSize);
									file.WriteString(str);
									str.Format( "           else if( enable_draw_%s != 0 )\n", fname );
									file.WriteString( str );
									str.Format( "            translate([ %.3f, %.3f, 0.0 ])\n              cube([ %.3f, %.3f, board_h*2.0 ], center=true );\n", pinX, pinY, HoleSize, HoleSize );
									file.WriteString( str );
									str.Format( "           else\n            translate([ %.3f, %.3f, 0.0 ])\n              cylinder( d=%.3f, h=board_h*2.0, center=true );\n", pinX, pinY, HoleSize );
									file.WriteString( str );
								}
							}
						}
					}
				}
				//
				// закрываем diff
				//
				file.WriteString( "          }\n" );
				file.WriteString( "        }\n" );
			}
		}
		//
		// закрываем BO module
		//
		file.WriteString( "}\n" );
		file.WriteString( "\n" );
		file.WriteString( "\n" );
		file.WriteString( "/* ___________________\n  |                   |\n  |      MODULES      |\n  |___________________|\n*/\n" );
		for( int i=0; i<foots.GetSize(); i++ )
		{
			CString fname = foots.GetAt(i);
			str.Format( "module Draw_%s ()\n{\n", fname);
			file.WriteString( str );
			for( cpart * pp=m_plist->GetFirstPart(); pp; pp=m_plist->GetNextPart(pp) )
			{
				if (pp->utility == 0)
					continue;
				if( shapes.GetAt(i) == pp->shape )
				{
					double px = pp->x / mu;
					double py = pp->y / mu;
					double rot = pp->angle;
					if( pp->side )
						str.Format( "    translate([ %.3f, %.3f, -board_h ])\n      rotate([ 0.0, 180.0, 0.0 ])\n        rotate([ 0.0, 0.0, %.3f ])\n          F%s();\n", px, py, rot, fname);
					else
						str.Format( "    translate([ %.3f, %.3f, 0.0 ])\n      rotate([ 0.0, 0.0, %.3f ])\n        F%s();\n", px, py, -rot, fname);
					file.WriteString( str );
				}
			}
			file.WriteString( "}\n" );
		}
		// lib file close..
		file.Close(); 

		BOOL bShellEx = FALSE;
		int maxlen = 13;
		for(int i=0; i<foots.GetSize(); i++)
			maxlen = max( maxlen, foots.GetAt(i).GetLength() );
		CString newpath = path.Left( path.GetLength()-4 ) + ".scad";
		err = _stat( newpath, &buf );
		if( err )
		{
			CStdioFile Scadfile;
			ok = Scadfile.Open( newpath, CFile::modeCreate | CFile::modeWrite );
			if( ok )
			{
				str.Format( "include <%s>\n", (moduleName+".lib") );
				Scadfile.WriteString( str );
				str.Format( "Convexity = 2;\n" );
				Scadfile.WriteString( str );
				double bh = 1500000.0 / mu;
				str.Format( "board_h = %.3f;\n", bh );
				Scadfile.WriteString( str );
				Scadfile.WriteString( "\n// Drawing control\n" );
				str.Format( "E = 1;\n" );
				Scadfile.WriteString( str );
				CString spc = "";
				for( int isp=13; isp<maxlen; isp++ )
					spc += " ";
				str.Format( "enable_draw_board_outline%s = E;\n", spc );
				Scadfile.WriteString( str );
				spc = "";
				for( int isp=5; isp<maxlen; isp++ )
					spc += " ";
				str.Format( "enable_draw_holes%s = E;\n", spc );
				Scadfile.WriteString( str );
				spc = "";
				for( int isp=4; isp<maxlen; isp++ )
					spc += " ";
				str.Format( "enable_draw_pads%s = E;\n", spc );
				Scadfile.WriteString( str );
				for(int i=0; i<foots.GetSize(); i++)
				{
					spc = "";
					for( int isp=foots.GetAt(i).GetLength(); isp<maxlen; isp++ )
						spc += " ";
					str.Format( "enable_draw_%s%s = E;\n", foots.GetAt(i), spc );
					Scadfile.WriteString( str );
				}
				str.Format( "Pcb_%s ();", moduleName );
				Scadfile.WriteString( str );
				Scadfile.Close();
				bShellEx = TRUE;
			}
		}
		else
		{
			CString edata = "";
			CStdioFile Scadfile;
			ok = 0; 
			for( int iter=0; (iter<10)&&(ok==0); iter++ )
			{
				Sleep(50);
				ok = Scadfile.Open( newpath, CFile::modeRead, NULL );	
			}
			if( ok )
			{
				while( Scadfile.ReadString( str ) )
				{
					if( str.Find( "enable_draw_" ) >= 0 )
						edata += str;
				}
				Scadfile.Close();
			}
			else
			{
				AfxMessageBox(G_LANGUAGE == 0 ? ("Unable to open file: \"" + newpath + "\"") : ("Невозможно открыть файл: \"" + newpath + "\""));
			}
			ok = 0; 
			for( int iter=0; (iter<10)&&(ok==0); iter++ )
			{
				Sleep(50);
				ok = Scadfile.Open( newpath, CFile::modeWrite );
			}
			if( ok )
			{
				Scadfile.SeekToEnd();
				for(int i=0; i<foots.GetSize(); i++)
				{
					CString spc = "";
					for( int isp=foots.GetAt(i).GetLength(); isp<maxlen; isp++ )
						spc += " ";
					str.Format( "enable_draw_%s ", foots.GetAt(i) );
					if( edata.Find( str ) < 0 )
					{
						str.Format( "\nenable_draw_%s%s = E; // was added to the PCB", foots.GetAt(i), spc );
						Scadfile.WriteString( str );
					}
				}
				Scadfile.WriteString( " " ); // openscad not work without this
				Scadfile.Close();
			}
			else
			{
				AfxMessageBox(G_LANGUAGE == 0 ? ("Unable to open file: \"" + newpath + "\""):("Невозможно открыть файл: \"" + newpath + "\""));
			}
			HWND wnd = FindWindow( NULL, moduleName + ".scad - OpenSCAD" );
			if( wnd == NULL )
				wnd = FindWindow( NULL, moduleName + ".scad* - OpenSCAD" );
			if( wnd )
			{
				WINDOWPLACEMENT placement;
				placement.length = sizeof(placement);
				//
				if( GetWindowPlacement(wnd, &placement) )
				{
					if( placement.showCmd & SW_SHOWMINIMIZED) 
					{
						placement.showCmd = SW_SHOWNORMAL;
						SetWindowPlacement(wnd, &placement);
					}
				}
				SetForegroundWindow( wnd );
			}
			else
				bShellEx = TRUE;
		}
		CancelBoardHoles();
		if( bShellEx )
			ShellExecute(	NULL, "open", newpath, NULL, NULL, SW_SHOWNORMAL);
	}
	ResetUndoState();
	ProjectModified( FALSE );
}

void CFreePcbDoc::OnFileGenerateReportFile()
{
	if( getbit( m_view->m_sel_flags, m_view->FLAG_SEL_PART ) == 0 )
		OnEditSelectAll();
	CDlgReport dlg;
	dlg.Initialize( this ); 
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		m_report_flags = dlg.m_flags;	// update flags
		int ip = m_pcb_full_path.ReverseFind('\\');
		if( ip > 0 )
		{
			CString report = m_path_to_folder + "\\related_files\\reports\\report.txt";
			ShellExecute(	NULL, "open", "\"" + report + "\"", NULL, m_path_to_folder, SW_SHOWNORMAL);
			if (!(m_report_flags & dlg.NO_PARTS_LIST))
			{
				report = m_path_to_folder + "\\related_files\\reports\\report.csv";
				ShellExecute(NULL, "open", "\"" + m_app_dir + "\\CSVFileView.exe\"", "\"" + report + "\"", m_path_to_folder, SW_SHOWNORMAL);
			}
		}
	}
}

int CFreePcbDoc::GetNumBoards()
{
	int nbo = 0;
	for( int ib= m_outline_poly.GetSize()-1; ib>=0; ib-- )
	{
		id bid = m_outline_poly[ib].GetId();
		if( bid.st == ID_BOARD )
			nbo++;
	}
	return nbo;
}
int CFreePcbDoc::GetNumSMCutouts()
{
	int no = 0;
	for( int ib= m_outline_poly.GetSize()-1; ib>=0; ib-- )
	{
		id bid = m_outline_poly[ib].GetId();
		if( bid.st == ID_SM_CUTOUT )
			no++;
	}
	return no;
}
int CFreePcbDoc::GetNumGraphics()
{
	int no = 0;
	for( int ib= m_outline_poly.GetSize()-1; ib>=0; ib-- )
	{
		id bid = m_outline_poly[ib].GetId();
		if( bid.st == ID_GRAPHIC )
			no++;
	}
	return no;
}
void CFreePcbDoc::OPRefreshID()
{
	//ids..
	for( int ipo=0; ipo<m_outline_poly.GetSize(); ipo++ )
	{
		CPolyLine * poly = &m_outline_poly[ipo];
		id gid = poly->GetId();
		if( gid.i == ipo )
			continue;
		gid.i = ipo;
		poly->SetId( &gid );
		poly->Undraw();
		poly->Draw( m_dlist );
	}
}
int CFreePcbDoc::CombineBoardOutlines( int ib1, int ib2 )
{
	CPolyLine * poly1 = &m_outline_poly[ib1];
	CPolyLine * poly2 = &m_outline_poly[ib2];

	// polygons intersect, combine them
	int COUNT_CORNERS = poly1->GetNumCorners() + poly2->GetNumCorners();
	CArray<CArc> arc_array1;
	CArray<CArc> arc_array2;
	poly1->MakeGpcPoly( -1, &arc_array1 );
	poly2->MakeGpcPoly( -1, &arc_array2 );
	int n_ext_cont1 = 0;
	for( int ic=0; ic<poly1->GetGpcPoly()->num_contours; ic++ )
		if( !((poly1->GetGpcPoly()->hole)[ic]) )
			n_ext_cont1++;
	int n_ext_cont2 = 0;
	for( int ic=0; ic<poly2->GetGpcPoly()->num_contours; ic++ )
		if( !((poly2->GetGpcPoly()->hole)[ic]) )
			n_ext_cont2++;

	gpc_polygon * union_gpc = new gpc_polygon;//ok
	gpc_polygon_clip( GPC_UNION, poly1->GetGpcPoly(), poly2->GetGpcPoly(), union_gpc );

	// get number of outside contours
	int n_union_ext_cont = 0;
	for( int ic=0; ic<union_gpc->num_contours; ic++ )
		if( !((union_gpc->hole)[ic]) )
			n_union_ext_cont++;

	// if no intersection, free new gpc and return
	if( n_union_ext_cont == n_ext_cont1 + n_ext_cont2 )
	{
		gpc_free_polygon( union_gpc );
		delete union_gpc;
		return 0;
	}

	// intersection, replace ia1 with combined areas and remove ia2
	int hatch = poly1->GetHatch();
	int m_b_merge = poly1->GetMerge();
	id b_id = poly1->GetId();
	int layer = poly1->GetLayer();
	int w = poly1->GetW();
	int sel_box = poly1->GetSelBoxSize();
	if( ib1 > ib2 )
	{
		m_outline_poly[ib1].Undraw();
		m_outline_poly.RemoveAt(ib1,1);
		m_outline_poly[ib2].Undraw();
		m_outline_poly.RemoveAt(ib2,1);
	}
	else
	{
		m_outline_poly[ib2].Undraw();
		m_outline_poly.RemoveAt(ib2,1);
		m_outline_poly[ib1].Undraw();
		m_outline_poly.RemoveAt(ib1,1);
	}

	// create area with external contour
	int sz = m_outline_poly.GetSize();
	b_id.i = sz;
	for( int ic=0; ic<union_gpc->num_contours; ic++ )
	{
		if( !(union_gpc->hole)[ic] )
		{
			// external contour, replace this poly
			for( int i=0; i<union_gpc->contour[ic].num_vertices; i++ )
			{
				int x = ((union_gpc->contour)[ic].vertex)[i].x;
				int y = ((union_gpc->contour)[ic].vertex)[i].y;
				if( i==0 )
				{
					m_outline_poly.SetSize( sz+1 );
					b_id.i = sz;
					m_outline_poly[sz].SetDisplayList(m_dlist);
					m_outline_poly[sz].Start( layer, w, 20*NM_PER_MIL, x, y, hatch, &b_id, NULL );
					m_outline_poly[sz].SetMerge( m_b_merge );
				}
				else
					m_outline_poly[sz].AppendCorner( x, y, CPolyLine::STRAIGHT, FALSE );
			}
			m_outline_poly[sz].Close(CPolyLine::STRAIGHT);
		}
	}
	// add holes
	for( int ic=0; ic<union_gpc->num_contours; ic++ )
	{
		if( (union_gpc->hole)[ic] )
		{
			// hole
			for( int i=0; i<union_gpc->contour[ic].num_vertices; i++ )
			{
				int x = ((union_gpc->contour)[ic].vertex)[i].x;
				int y = ((union_gpc->contour)[ic].vertex)[i].y;
				m_outline_poly[sz].AppendCorner( x, y, CPolyLine::STRAIGHT, FALSE );
			}
			m_outline_poly[sz].Close(CPolyLine::STRAIGHT);
		}
	}
	m_outline_poly[sz].SetUtility(1);
	m_outline_poly[sz].RestoreArcs( &arc_array1 ); 
	m_outline_poly[sz].RestoreArcs( &arc_array2 );
	for( int c=(m_outline_poly[sz].GetNumContours()-1); c>=0; c-- )
		m_outline_poly[sz].RecalcRectC(c);
	gpc_free_polygon( union_gpc );
	delete union_gpc;
	OPRefreshID();
	return 1;
}


void CFreePcbDoc::ClipOP ( int i )
{
	int lay_op = m_outline_poly[i].GetLayer();
	int mer = m_outline_poly[i].GetMerge();
	CArray<CPolyLine*> * pa = new CArray<CPolyLine*>;//ok
	int n_poly = m_outline_poly[i].NormalizeWithGpc( pa, 1 );
	m_outline_poly[i].SetMerge(mer);
	if( n_poly > 1 )
	{
		for( int ip=1; ip<n_poly; ip++ )
		{
			// create new copper area and copy poly into it
			CPolyLine * new_p = (*pa)[ip-1];
			int szb = m_outline_poly.GetSize();
			m_outline_poly.SetSize(szb+1);
			id bid = new_p->GetId();
			// remove the poly that was automatically created for the new area
			// and replace it with a poly from NormalizeWithGpc
			m_outline_poly[szb].Copy(new_p);
			m_outline_poly[szb].SetMerge(mer);
			m_outline_poly[szb].SetDisplayList( m_dlist );
			m_outline_poly[szb].SetLayer( lay_op );
			m_outline_poly[szb].SetId(&bid);
			for( int c=(m_outline_poly[szb].GetNumContours()-1); c>=0; c-- )
				m_outline_poly[szb].RecalcRectC(c);
			m_outline_poly[szb].Draw();
			delete new_p;
		}
	}
	m_outline_poly[i].Draw();
	delete pa;
} 

void CFreePcbDoc::OnProjectCombineBoard()
{
	ProjectCombineBoard( LAY_BOARD_OUTLINE );
	ProjectCombineBoard( LAY_REFINE_TOP );
	ProjectCombineBoard( LAY_REFINE_BOT );
	ProjectCombineBoard( LAY_SILK_TOP );
	ProjectCombineBoard( LAY_SILK_BOTTOM );
	ProjectCombineBoard( LAY_SM_TOP );
	ProjectCombineBoard( LAY_SM_BOTTOM );
	m_view->Invalidate(FALSE);
}

void CFreePcbDoc::ProjectCombineBoard( int layer )
{
	if( m_outline_poly.GetSize() > 0 )
	{
		m_view->SaveUndoInfoForOutlinePoly( m_view->UNDO_OP, TRUE, m_undo_list );
		// start by testing all polygons to set utility flags
		for( int ib=m_outline_poly.GetSize()-1; ib>=0; ib-- )
		{
			if( m_outline_poly[ib].GetLayer() != layer )
				continue;
			int ret = m_outline_poly[ib].TestPolygonIntersection( -1, -1 );
			if( ret )
				ClipOP(ib);
		}
		// now loop through all combinations
		BOOL message_shown = FALSE;
		BOOL CC;
		do
		{
			CC = FALSE;
			for( int i1=m_outline_poly.GetSize()-1; i1>=0; i1-- ) 
			{
				if( m_outline_poly[i1].GetLayer() != layer )
					continue;
				if( m_outline_poly[i1].GetClosed() == 0 )
					continue;
				//
				// legal polygon
				int htch = m_outline_poly[i1].GetHatch();
				int wid1 = m_outline_poly[i1].GetW();
				RECT b1 = m_outline_poly[i1].GetCornerBounds(0);
				BOOL mod_i1 = FALSE;
				for( int i2=m_outline_poly.GetSize()-1; i2 > i1; i2-- )
				{
					if( m_outline_poly[i2].GetClosed() == 0 )
						continue;
					if( m_outline_poly[i2].GetHatch() != htch )
						continue;
					if( m_outline_poly[i2].GetW() != wid1 )
						continue;
					if( m_outline_poly[i1].GetUtility() != -1 && 
						m_outline_poly[i2].GetUtility() != -1 )
					{
						RECT b2 = m_outline_poly[i2].GetCornerBounds(0);
						if( !( b1.left > b2.right || b1.right < b2.left
							|| b1.bottom > b2.top || b1.top < b2.bottom ) )
						{
							int ret = m_outline_poly[i1].TestPolygonIntersection( &m_outline_poly[i2] );
							if( ret == 1 || ret == 2 )
								ret = CombineBoardOutlines( i1, i2 );
							if( ret == 1 || ret == 2 )
							{
								CC = TRUE;
								CString str;
								if( layer == LAY_BOARD_OUTLINE )
									str.Format( "Board outlines %d and %d intersect and will be combined.\n",
									i1+1, i2+1 );
								else str.Format( "Polylines %d and %d intersect and will be combined.\n",
									i1+1, i2+1 );
								str += "If they are complex, this may take a few seconds.";
								//CDlgMyMessageBox dlg;
								//dlg.Initialize( str );
								//dlg.DoModal();
								CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;
								if (pMain)
								{
									pMain->DrawStatus(3, &str);
									pMain->UpdateWindow();
								}
								mod_i1 = TRUE;
							}				
						}
					}
				}
				if( mod_i1 )
					i1--;		// if modified, we need to check it again
			}
		}while(CC);
		OPRefreshID();
		ProjectModified( TRUE );
	}
}


void CFreePcbDoc::OnProjectCombineNets()
{
	ProjectCombineNets(m_nlist);
}

BOOL CFreePcbDoc::ProjectCombineNets( CNetList * nl )
{
	if( !m_view )
		return FALSE;
	if( m_netlist_completed )
	{
		if( m_view->g_bShow_nl_lock_Warning )
		{
			CString str = "Netlist is protected. You can remove protection through the menu Project-->Nets-->Netlist Protected";
			CDlgMyMessageBox dlg;
			dlg.Initialize( str );
			dlg.DoModal();
			m_view->g_bShow_nl_lock_Warning = !dlg.bDontShowBoxState;
		}
		return FALSE;
	}
	CDlgNetCombine dlg;
	dlg.Initialize( nl, m_plist );
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		OnEditSelectAll();
		m_view->SaveUndoInfoForGroup( CFreePcbView::UNDO_GROUP_MODIFY, m_undo_list );
		m_view->CancelSelection();

		// copy existing netlist
		CNetList * old_nlist = new CNetList( NULL, m_plist );	// save to fix traces //ok
		old_nlist->Copy( m_nlist );

		// combine nets under new name
		CString c_name = dlg.m_new_name;
		if( c_name.GetLength() == 0 )
			ASSERT(0);
		CArray<CString> * names = &dlg.m_names;
		netlist_info nl_info;
		m_nlist->ExportNetListInfo( &nl_info );

		// now combine the nets
		// first, find the net and index for the combined net
		int c_index = -1;
		cnet * c_net = NULL;
		for( int in=0; in<nl_info.GetSize(); in++ )
		{
			CString nl_name = nl_info[in].name;
			if( nl_name == c_name )
			{
				c_index = in;
				c_net = nl_info[in].net;
				break;
			}
		}
		if( c_index == -1 )
			ASSERT(0);

		// now, combine the other nets
		for( int i=0; i<names->GetSize(); i++ )
		{
			CString name = (*names)[i];		// net name to combine
			//
			cnet * snet = m_nlist->GetNetPtrByName(&name);
			if( snet )
			{
				m_view->SaveUndoInfoForAllAreasInNet( snet, FALSE, m_undo_list );
				m_view->SaveUndoInfoForNet( snet, CNetList::UNDO_NET_MODIFY, FALSE, m_undo_list );
			}

			//
			int nl_index = -1;
			if( name != c_name )
			{
				// combine this net
				for( int in=0; in<nl_info.GetSize(); in++ )
				{
					CString nl_name = nl_info[in].name;
					if( nl_name == name )
					{
						nl_index = in;
						break;
					}
				}
				if( nl_index == -1 )
					ASSERT(0);
				for( int ip=0; ip<nl_info[nl_index].pin_name.GetSize(); ip++ )
				{
					CString * pname = &nl_info[nl_index].pin_name[ip];
					CString * pref = &nl_info[nl_index].ref_des[ip];
					int ipp = nl_info[c_index].pin_name.GetSize();
					nl_info[c_index].pin_name.SetAtGrow( ipp, *pname );
					nl_info[c_index].ref_des.SetAtGrow( ipp, *pref );
					nl_info[c_index].modified = TRUE;
				}
				nl_info[nl_index].modified = TRUE;
				nl_info[nl_index].pin_name.RemoveAll();
				nl_info[nl_index].ref_des.RemoveAll();
			}
		}
		// show log dialog
		m_dlg_log->ShowWindow( SW_SHOW );
		m_dlg_log->UpdateWindow();
		m_dlg_log->BringWindowToTop();
		m_dlg_log->Clear();
		m_dlg_log->UpdateWindow();
		//
		//
		m_nlist->ImportNetListInfo( &nl_info, 0, m_dlg_log, 0, 0, 0 );
		int flags = IMPORT_PARTS | IMPORT_NETS | KEEP_TRACES | KEEP_STUBS | KEEP_AREAS	| KEEP_PARTS_AND_CON;
		m_nlist->RestoreConnectionsAndAreas( old_nlist, flags, m_dlg_log );
		old_nlist->SetPartList( NULL );
		delete old_nlist;

		ProjectModified(TRUE);
	}
	return TRUE;
}

void CFreePcbDoc::OnFileLoadLibrary()
{
	if( FileClose() == IDCANCEL )
		return;

	m_view->CancelSelection();
	InitializeNewProject();		// set defaults

	// get project file name
	// force old-style file dialog by setting size of OPENFILENAME struct (for Win98)
	//
	CString filename = RunFileDialog( 1, "fpc" ); 
	if ( filename.GetLength() )
	{
		// read project file
		//CString pathname = dlg.GetPathName();
		FileLoadLibrary( filename );
	}
	else
	{
		// CANCEL or error
		DWORD dwError = ::CommDlgExtendedError();
		if( dwError )
		{
			CString str;
			str.Format(G_LANGUAGE == 0 ? "File Open Dialog error code = %ulx\n":"Код ошибки диалога открытия файла = %ulx\n", (unsigned long)dwError);
			AfxMessageBox( str );
		}
	}
}
void CFreePcbDoc::FileLoadLibrary( LPCTSTR pathname )
{
	BOOL bOK = FileOpen( pathname, TRUE );
	if( bOK )
	{
		// now add one instance of each footprint in cache
		POSITION pos;
		CString key;
		void * ptr;
		LPCSTR p;
		CShape *shape;
		CString ref;
		int i=1, x=0, y=0, max_height=0;
		for( pos = m_footprint_cache_map.GetStartPosition(); pos != NULL; )
		{
			m_footprint_cache_map.GetNextAssoc( pos, key, ptr );
			p = (LPCSTR)key;
			shape = (CShape*)ptr;
			ref.Format( "LIB_%d", i );
			cpart * part = m_plist->Add( shape, &ref, x, y, /*side=*/0, /*ang=*/0,/*vis=*/1,/*glued=*/0 );
			// get bounding rectangle of pads and outline
			RECT shape_r;
			shape_r	= part->shape->GetBounds(1);
			int height = shape_r.top - shape_r.bottom;
			int width = shape_r.right - shape_r.left;
			// get dimensions of bounding rectangle for value text
			m_plist->SetValue( part, &shape->m_name, 
				shape_r.left, shape_r.top + part->m_ref_w, 0, 
				part->m_ref_size, part->m_ref_w, 1 );
			RECT vr;
			m_plist->GetValueBoundingRect( part, &vr );
			int value_width = vr.right - vr.left;
			// see if we can fit part between x and 8 inches
			int max_width = max( width, value_width );
			BOOL bFits = (x + max_width) < (8000*NM_PER_MIL);
			if( !bFits ) 
			{
				// start new row
				x = 0;
				y -= max_height;
				max_height = 0;
			}
			// move part so upper-left corner is at x,y
			m_plist->Move( part, x - shape_r.left, 
				y - shape_r.top - 2*part->m_ref_size, 0, 0 );
			// make ref invisible
			m_plist->ResizeRefText( part, part->m_ref_size, part->m_ref_w, 0 );
			// move value to top of part
			m_plist->SetValue( part, &shape->m_name, 
				shape_r.left, shape_r.top + part->m_ref_w, 0, 
				part->m_ref_size, part->m_ref_w, 1 );
			m_plist->DrawPart( part );
			i++;
			x += max_width + 200*NM_PER_MIL;	// step right .2 inches
			max_height = max( max_height, height + 2*part->m_ref_size );
		}
		if( m_pcb_filename.Right(4) == ".fpl" )
		{
			int len = m_pcb_filename.GetLength();
			m_pcb_filename.SetAt(len-1, 'c');
			len = m_pcb_full_path.GetLength();
			m_pcb_full_path.SetAt(len-1, 'c');
		}
		else
		{
			m_pcb_filename = m_pcb_filename + ".fpc";
			m_pcb_full_path = *pathname + ".fpc";
		}
		if(G_LANGUAGE==0)
			m_window_title = "FreePCB library project - " + m_pcb_filename;
		else 
			m_window_title = "Библиотека ПлатФорм - " + m_pcb_filename;
		CWnd* pMain = AfxGetMainWnd();
		pMain->SetWindowText( m_window_title );
		m_view->OnViewAllElements();
		ProjectModified( FALSE );
	}
}

void CFreePcbDoc::OnFileSaveLibrary()
{
	/*CDlgSaveLib dlg;
	CArray<CString> names;
	cpart * part = m_plist->GetFirstPart();
	int i = 0;
	while( part )
	{
		names.SetAtGrow( i, part->value );
		part = m_plist->GetNextPart( part );
		i++;
	}
	dlg.Initialize( &names );
	int ret = dlg.DoModal();*/
	CString S = RunFileDialog(0, "fpl");
	if( S.GetLength() )
	{
		if( S.GetLength() < 5 )
			S += ".fpl";
		else if( S.Right(4) != ".fpl" )
			S += ".fpl";
		CStdioFile pcb_file;
		int err = pcb_file.Open( LPCSTR(S), CFile::modeCreate | CFile::modeWrite, NULL );
		if( !err )
		{
			// error opening file
			return;
		}
		else
		{
			// write project to file
			try
			{
				WriteFootprints( &pcb_file,NULL,0 );
				pcb_file.WriteString( "[end]\n" );
				pcb_file.Close();
			}
			catch( CString * err_str )
			{
				// error
				AfxMessageBox( *err_str );
				delete err_str;
				CDC * pDC = m_view->GetDC();
				m_view->OnDraw( pDC ) ;
				m_view->ReleaseDC( pDC );
				return;
			}
		}
	}
}

void CFreePcbDoc::RemoveOrphanMerges()
{
	Merge NewMergesList;
	NewMergesList.Clear();
	for( cpart * p=m_plist->GetFirstPart(); p; p=m_plist->GetNextPart(p) )
	{
		if( p->m_merge >= 0 )
		{
			CString m_name = m_mlist->GetMerge(p->m_merge);
			int clrn = m_mlist->GetClearance(p->m_merge);
			p->m_merge = NewMergesList.AddNew( m_name, clrn );
		}
		if( p->sub_merge >= 0 )
		{
			CString m_name = m_mlist->GetMerge(p->sub_merge);
			int clrn = m_mlist->GetClearance(p->sub_merge);
			p->sub_merge = NewMergesList.AddNew( m_name, clrn );
		}
	}
	int it = 0;
	for( CText * t=m_tlist->GetFirstText(); t; t=m_tlist->GetNextText(&it) )
	{
		if( t->m_merge >= 0 )
		{
			CString m_name = m_mlist->GetMerge(t->m_merge);
			t->m_merge = NewMergesList.GetIndex( m_name );
		}
		if( t->m_submerge >= 0 )
		{
			CString m_name = m_mlist->GetMerge(t->m_submerge);
			t->m_submerge = NewMergesList.GetIndex( m_name );
		}
	}
	for( int i=m_outline_poly.GetSize()-1; i>=0; i-- )
	{
		int im = m_outline_poly[i].GetMerge();
		if( im >= 0 )
		{
			CString m_name = m_mlist->GetMerge( im );
			im = NewMergesList.GetIndex( m_name );
			m_outline_poly[i].SetMerge( im );
		}
		im = m_outline_poly[i].GetMerge(TRUE);
		if( im >= 0 )
		{
			CString m_name = m_mlist->GetMerge( im );
			im = NewMergesList.GetIndex( m_name );
			m_outline_poly[i].SetMerge( im, TRUE );
		}
	}
	for( cnet * n = m_nlist->GetFirstNet(); n; n = m_nlist->GetNextNet(/*LABEL*/) )
		for( int ia=0; ia<n->nareas; ia++ )
		{
			int im = n->area[ia].poly->GetMerge();
			if( im >= 0 )
			{
				CString m_name = m_mlist->GetMerge( im );
				im = NewMergesList.GetIndex( m_name );
				n->area[ia].poly->SetMerge( im );
			}
			im = n->area[ia].poly->GetMerge(TRUE);
			if( im >= 0 )
			{
				CString m_name = m_mlist->GetMerge( im );
				im = NewMergesList.GetIndex( m_name );
				n->area[ia].poly->SetMerge( im, TRUE );
			}
		}
	m_mlist->Clear();
	m_mlist->CopyFrom( &NewMergesList );

	// update all connections and areas
	//m_nlist->OptimizeConnections(0,0,0);  ?
	//m_nlist->SetAreaConnections();  ?
	//for( cnet * n=m_nlist->GetFirstNet(); n; n=m_nlist->GetNextNet(/*LABEL*/) )  ?
	//{  ?
	//	m_nlist->DrawConnections(n);  ?
	//	m_nlist->DrawAreas(n);  ?
	//}  ?
}

void CFreePcbDoc::DRC()
{
	const int MAXERRORS = 499;
	AddBoardHoles(); // valid
	CString PrevValueStr = "__";
	CString d_str, x_str, y_str;
	CString str;
	CString str2;
	CString TooCloseToViaHole = "";
	CString TooCloseToPadHole = "";
	CString TooCloseToHole = "";
	CString TooCloseToPad = "";
	long nerrors = 0;
	int TraceW =	DEFAULT,
		PadPad =	DEFAULT,
		PadPadF =	DEFAULT,
		PadTrace =	DEFAULT,
		TraceTrace =DEFAULT,
		HoleCopper =DEFAULT,
		HoleCopperF=DEFAULT,
		ViaHoleToPadSameNet=DEFAULT,
		HoleHole =	DEFAULT,
		HoleHoleF =	DEFAULT,
		arPins =	DEFAULT,
		arVias =	DEFAULT,
		BoardCopper=DEFAULT,
		BoardHole = DEFAULT,
		AreaArea =	DEFAULT,
		AreaCopperHsFull=DEFAULT,
		PadPadTooClose=		DEFAULT,
		HoleCopperTooClose=	DEFAULT,
		HoleHoleTooClose=	DEFAULT;
	int MAX_CL = 0;
	int WARNING_ADDED = 1;
	MAX_CL = max( m_dr.trace_trace, MAX_CL );
	MAX_CL = max( m_dr.pad_trace, MAX_CL );
	MAX_CL = max( m_dr.pad_pad, MAX_CL );
	MAX_CL = max( m_dr.hole_hole, MAX_CL );
	MAX_CL = max( m_dr.hole_copper, MAX_CL );
	MAX_CL = max( m_dr.copper_copper, MAX_CL );
	MAX_CL = max( m_dr.board_edge_hole, MAX_CL );
	MAX_CL = max( m_dr.board_edge_copper, MAX_CL );
	MAX_CL *= 2;
	CArray<int> ArHoles;
	ArHoles.SetSize(0);
	// iterate through parts, checking pads and setting DRC params
	str.Format( "Checking parts:\r\n" );
	if( m_dlg_log )
		m_dlg_log->AddLine( str );
	for( cpart * part = m_plist->GetFirstPart(); part; part = m_plist->GetNextPart( part ) )
	{
		CShape * s = part->shape;
		if( nerrors > MAXERRORS )
		{
			goto cancel_verification;
		}
		if( s )
		{
			if (s->m_outline_poly.GetSize())
				if (s->m_outline_poly[s->m_outline_poly.GetSize() - 1].GetLayer() == LAY_FP_VISIBLE_GRID)
					continue; // this is system footprint, ignore
				else if (s->m_outline_poly[0].GetLayer() == LAY_FP_VISIBLE_GRID)
					continue; // this is system footprint, ignore
			//
			if(s->m_package.Compare("ERROR") == 0 )
			{
				CString err_foot = s->m_name;//.Left( s->m_name.GetLength() - 4 );
				str.Format( "%ld: Footprint %s is missing from the library\r\n", nerrors+1, err_foot );
				id id1( ID_PART_DEF );
				id id2( ID_PART_DEF );
				DRError * dre = m_drelist->Add( nerrors, DRError::PAD_PAD, &str,
					&part->ref_des, NULL, id1, id2, part->x, part->y, 0, 0, 20*NM_PER_MIL, 0 );
				if( dre )
				{
					nerrors++;
					if( m_dlg_log )
						m_dlg_log->AddLine( str );
				}
				///continue;
			}
			part->layers = 0;
			// get hole flag
			part->hole_flag = part->shape->GetHoleFlag();
			// get part bounds
			RECT br;
			m_plist->GetPartBoundingRect( part, &br );
			part->min_x = br.left;
			part->max_x = br.right;
			part->min_y = br.bottom;
			part->max_y = br.top;
			int PART_LENGTH = max( br.right-br.left, br.top-br.bottom ) + MAX_CL;
			part->utility = 0;
			// iterate through pins in test_part
			for( int ip=0; ip<s->GetNumPins(); ip++ )
			{
				id id1 = part->m_id;
				id1.st = ID_PAD;
				id1.i = ip;
				part->pin[ip].drc.layers = 0;
				// get pad rect
				RECT padr;
				if( !m_plist->GetPadBounds(part,ip,&padr) )
				{
					continue;
				}
				part->pin[ip].drc.min_x = padr.left;
				part->pin[ip].drc.max_x = padr.right;
				part->pin[ip].drc.min_y = padr.bottom;
				part->pin[ip].drc.max_y = padr.top;
				// pad or hole present
				if( s->m_padstack[ip].hole_size )
				{
					int hole = s->m_padstack[ip].hole_size;
					if( part->utility < PART_LENGTH )
					{
						// get test pad info
						int x = part->pin[ip].x;
						int y = part->pin[ip].y;
		
						// test clearance to board edge
						part->utility = INT_MAX;
						for( int ib=0; ib<m_outline_poly.GetSize(); ib++ )
						{
							CPolyLine * b = &(m_outline_poly[ib]);
							if( b->GetLayer() != LAY_BOARD_OUTLINE )
								continue;
							for( int ibc=0; ibc<b->GetNumSides(); ibc++ )
							{
								int x1 = b->GetX(ibc);
								int y1 = b->GetY(ibc);
								int x2 = b->GetX(b->GetIndexCornerNext(ibc));
								int y2 = b->GetY(b->GetIndexCornerNext(ibc));
								int xBounds = max( (padr.left - max(x1,x2)), (min(x1,x2) - padr.right) );
								int yBounds = max( (padr.bottom - max(y1,y2)), (min(y1,y2) - padr.top) );
								int maxBounds = max( xBounds, yBounds );
								part->utility = min( part->utility, maxBounds );
								if(padr.left - MAX_CL > max(x1,x2))
									continue;
								if(padr.right + MAX_CL < min(x1,x2))
									continue;
								if(padr.top + MAX_CL < min(y1,y2))
									continue;
								if(padr.bottom - MAX_CL > max(y1,y2))
									continue;
								int errx, erry;
								int d = ::GetClearanceBetweenSegments( x1, y1, x2, y2, b->GetSideStyle(ibc), 0,
									x, y, x+10, y+10, 0, hole, MAX_CL, &errx, &erry );
								BoardHole = min( BoardHole, d );
								if( d < m_dr.board_edge_hole )
								{
									// BOARDEDGE_PADHOLE error
									::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
									::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
									::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
									str.Format( "%ld: %s.%s pad hole to board edge = %s, x=%s, y=%s\r\n",  
										nerrors+1, part->ref_des, s->m_padstack[ip].name, d_str, x_str, y_str );
									id id2( ID_POLYLINE, ID_BOARD, ib, ID_SIDE, ibc );
									DRError * dre = m_drelist->Add( nerrors, DRError::BOARDEDGE_PADHOLE, &str,
										&part->ref_des, NULL, id1, id2, errx, erry, 0, 0, hole+20*NM_PER_MIL, 0 );
									if( dre )
									{
										nerrors++;
										if( m_dlg_log )
											m_dlg_log->AddLine( str );
									}
								}
							}
						}
					}
					BOOL F = 0;
					for( int ibox=0; ibox<ArHoles.GetSize(); ibox++ )
						if( ArHoles.GetAt(ibox) == hole )
							F = 1;
					if( F == 0 )
						ArHoles.Add(hole);
				}
				// iterate through copper layers
				for( int il=0; il<m_num_copper_layers; il++ )
				{
					if( !part->hole_flag && il > 1 )
						break;
					int layer = LAY_TOP_COPPER + il;

					// get test pad info
					int x, y, w, l, r, type, hole, connect, angle;
					cnet * net;
					BOOL bPad = m_plist->GetPadDrawInfo( part, ip, layer, 0, 0, 0, 0,
						&type, &x, &y, &w, &l, &r, &hole, &angle,
						&net, &connect );
					if( bPad )
					{
						// mask lay
						part->pin[ip].drc.layers = part->pin[ip].drc.layers|(1<<il);
						part->layers = part->layers|(1<<il);
						if( type != PAD_NONE )
						{
							int wid = w;
							int len = l;
							if( type == PAD_NONE || type == PAD_ROUND || type == PAD_SQUARE || type == PAD_OCTAGON )
								len = wid;
							if( hole && part->pin[ip].net )
							{
								// test annular ring
								int d = (w - hole)/2;
								if( type == PAD_RECT || type == PAD_RRECT || type == PAD_OVAL )
									d = (min(w,l) - hole)/2;
								arPins = min( arPins, d );
								if( d < m_dr.annular_ring_pins )
								{
									// RING_PAD
									::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
									::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
									::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
									str.Format( "%ld: %s.%s annular ring = %s, x=%s, y=%s\r\n",  
										nerrors+1, part->ref_des, s->m_padstack[ip].name, d_str, x_str, y_str );
									DRError * dre = m_drelist->Add( nerrors, DRError::RING_PAD, &str,
										&part->ref_des, NULL, id1, id1, x, y, x, y, w+20*NM_PER_MIL, 0 );
									if( dre )
									{
										nerrors++;
										if( m_dlg_log )
											m_dlg_log->AddLine( str );
									}
								}
							}
							//
							// test clearance to board edge
							SwellRect(&padr, m_dr.board_edge_copper);
							if( part->utility < PART_LENGTH )
							{
								part->utility = INT_MAX;
								for( int ib=0; ib<m_outline_poly.GetSize(); ib++ )
								{
									CPolyLine * b = &(m_outline_poly[ib]);
									if( b->GetLayer() != LAY_BOARD_OUTLINE )
										continue;
									for( int ibc=0; ibc<b->GetNumSides(); ibc++ )
									{
										int icontour = b->GetContour(ibc);
										RECT brect = b->GetCornerBounds(icontour);
										if( brect.right < padr.right &&
											brect.left > padr.left &&
											brect.top < padr.top &&
											brect.bottom > padr.bottom )
										{
											ibc = b->GetContourEnd(icontour);
											continue;
										}
										int x1 = b->GetX(ibc);
										int y1 = b->GetY(ibc);
										int x2 = b->GetX(b->GetIndexCornerNext(ibc));
										int y2 = b->GetY(b->GetIndexCornerNext(ibc));
										int xBounds = max( (padr.left - max(x1,x2)), (min(x1,x2) - padr.right) );
										int yBounds = max( (padr.bottom - max(y1,y2)), (min(y1,y2) - padr.top) );
										int maxBounds = max( xBounds, yBounds );
										part->utility = min( part->utility, maxBounds );
										if(padr.left - MAX_CL > max(x1,x2))
											continue;
										if(padr.right + MAX_CL < min(x1,x2))
											continue;
										if(padr.top + MAX_CL < min(y1,y2))
											continue;
										if(padr.bottom - MAX_CL > max(y1,y2))
											continue;
										// for now, only works for straight board edge segments
										int cnt;
										CPoint arcs[N_SIDES_APPROX_ARC*10+1];
										cnt = Generate_Arc(	x1, y1, x2, y2, b->GetSideStyle(ibc), arcs, N_SIDES_APPROX_ARC*10 ); 
										int dmin = INT_MAX;
										for (int nc=0; nc<(cnt-1); nc++)
										{
											int d = ::GetClearanceBetweenSegmentAndPad( arcs[nc].x, arcs[nc].y, arcs[nc+1].x, arcs[nc+1].y, 0,
												type, x, y, w, l, r, angle );	
											dmin = min( dmin, d );
										}
										BoardCopper = min( BoardCopper, dmin );
										if( dmin < m_dr.board_edge_copper )
										{
											// BOARDEDGE_PAD error
											::MakeCStringFromDimension( &d_str, dmin, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											str.Format( "%ld: %s.%s pad to board edge = %s, x=%s, y=%s\r\n",  
												nerrors+1, part->ref_des, s->m_padstack[ip].name, d_str, x_str, y_str );
											id id2( ID_POLYLINE, ID_BOARD, ib, ID_SIDE, ibc );
											DRError * dre = m_drelist->Add( nerrors, DRError::BOARDEDGE_PAD, &str,
												&part->ref_des, NULL, id1, id2, x, y, x, y, w+20*NM_PER_MIL, layer );
											if( dre )
											{
												nerrors++;
												if( m_dlg_log )
													m_dlg_log->AddLine( str );
											}
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// iterate through parts again, checking against all other parts
	//cpart * m_part;
	//cpart * mt_part;
	m_plist->MarkAllParts(0);
	for( cpart * t_part=m_plist->GetFirstPart(); t_part; t_part=m_plist->GetNextPart(t_part) )
	{
		CShape * t_s = t_part->shape;
		if( nerrors > MAXERRORS )
		{
			goto cancel_verification;
		}
		if( t_s )
		{
			// now iterate through parts that follow in the partlist
			for( cpart * part=t_part; part; part=m_plist->GetNextPart(part) )
			{
				CShape * s = part->shape;
				if( s )
				{
					if( PrevValueStr.Find("_"+part->value+"_") <= 0 && part != t_part )
					{
						CString modValue1 = part->value;
						CString modValue2 = t_part->value;
						// replace "."
						int check = 0;
						if( modValue1.CompareNoCase(modValue2) )
							check += 10;
						for( int vi1=modValue1.Find("."); vi1>0; vi1=modValue1.Find(".") )
						{
							modValue1.Insert(vi1,",");
							modValue1.Delete(vi1+1);
							check += 1;
						}
						for( int vi2=modValue2.Find("."); vi2>0; vi2=modValue2.Find(".") )
						{
							modValue2.Insert(vi2,",");
							modValue2.Delete(vi2+1);
							check += 1;
						}
						// test on point
						if( check > 10 )
							if( modValue1.GetLength() )
								if( modValue2.GetLength() )
									if( modValue1.CompareNoCase(modValue2) == 0 && s->m_package.Compare(t_s->m_package) == 0 )
									{
										str.Format( "is Warning: The values %s dot or comma? need to decide( %s and %s ).\r\n", 
														part->value, t_part->ref_des, part->ref_des );
										if( m_dlg_log )
											m_dlg_log->AddLine( str );
										PrevValueStr += (part->value+"_");
										PrevValueStr += (t_part->value+"_");
									}
						// replace "-"
						for( int vi1=modValue1.Find("-"); vi1>0; vi1=modValue1.Find("-") )
						{
							modValue1.Insert(vi1,"_");
							modValue1.Delete(vi1+1);
						}
						for( int vi2=modValue2.Find("-"); vi2>0; vi2=modValue2.Find("-") )
						{
							modValue2.Insert(vi2,"_");
							modValue2.Delete(vi2+1);
						}
						// replace "/"
						for( int vi1=modValue1.Find("/"); vi1>0; vi1=modValue1.Find("/") )
						{
							modValue1.Insert(vi1,"_");
							modValue1.Delete(vi1+1);
						}
						for( int vi2=modValue2.Find("/"); vi2>0; vi2=modValue2.Find("/") )
						{
							modValue2.Insert(vi2,"_");
							modValue2.Delete(vi2+1);
						}
						modValue1.Trim();
						modValue2.Trim();
						if( modValue1.GetLength() )
							if( modValue2.GetLength() )
								if( modValue1.CompareNoCase(modValue2) == 0 && s->m_package.Compare(t_s->m_package) )
								{
									str.Format( "is Warning: The values %s are same but the packages are different( %s:%s and %s:%s ).\r\n", 
													part->value, t_part->ref_des, t_s->m_package, part->ref_des, s->m_package );
									if( m_dlg_log )
										m_dlg_log->AddLine( str );
									PrevValueStr += (part->value+"_");
									PrevValueStr += (t_part->value+"_");
								}
					}
					// now see if part and t_part pads might intersect
					// get max. clearance violation
					int clr = max( m_dr.pad_pad, m_dr.hole_copper );
					clr = max( clr, m_dr.hole_hole );
					// see if pads on same layers
					//if( part->side != t_part->side )
					//{
						// no pads on same layers,check for holes
					//	if( !part->hole_flag && !t_part->hole_flag ) 
					//		continue;	// no, go to next part
					//}

					// now check for clearance of rectangles
					if( part->min_x - t_part->max_x > clr )
						continue;	// next part
					if( t_part->min_x - part->max_x > clr )
						continue;	// next part
					if( part->min_y - t_part->max_y > clr )
						continue;	// next part
					if( t_part->min_y - part->max_y > clr )
						continue;	// next part

					// no clearance, we need to test pins in these parts
					// iterate through pins in t_part
					for( int t_ip=0; t_ip<t_s->GetNumPins(); t_ip++ )
					{
						padstack * t_ps = &t_s->m_padstack[t_ip];
						part_pin * t_pin = &t_part->pin[t_ip];
						id id1 = part->m_id;
						id1.st = ID_PAD;
						id1.i = t_ip;

						// get pad rect
						RECT t_r;
						if( !m_plist->GetPadBounds(t_part,t_ip,&t_r) )
						{
							t_r.left =	 INT_MAX;
							t_r.bottom = INT_MAX;
							t_r.right =	 INT_MIN;
							t_r.top =	 INT_MIN;
						}
						// iterate through pins in part
						for( int ip=(part == t_part?t_ip+1:0); ip<s->GetNumPins(); ip++ )
						{
							if (part == t_part && ip == t_ip)
								continue;
							padstack * ps = &s->m_padstack[ip];
							part_pin * pin = &part->pin[ip];
							id id2 = part->m_id;
							id2.st = ID_PAD;
							id2.i = ip;

							// get pad rect
							RECT r;
							if( !m_plist->GetPadBounds(part,ip,&r) )
							{
								r.left =	INT_MAX;
								r.bottom =	INT_MAX;
								r.right =	INT_MIN;
								r.top =		INT_MIN;
							}
							// see if pads on same layers
							if( (pin->drc.layers & t_pin->drc.layers) == 0 )
							{
								// no, see if either has a hole
								if( ps->hole_size == 0 && t_ps->hole_size == 0 )
								{
									// no, go to next pin
									continue;
								}
							}

							// see if padstacks might intersect
							if( r.left - t_r.right > clr )
								continue;	// no, next pin
							if( t_r.left - r.right > clr )
								continue;	// no, next pin
							if( r.bottom - t_r.top > clr )
								continue;	// no, next pin
							if( t_r.bottom - r.top > clr )
								continue;	// no, next pin

							// OK, pads might be too close
							// test for hole-hole violation
							if( ps->hole_size && t_ps->hole_size )
							{
								// test for hole-to-hole violation
								int dist = Distance( pin->x, pin->y, t_pin->x, t_pin->y );
								int h_h = max( 0, dist - (ps->hole_size + t_ps->hole_size)/2 );
								if( part == t_part )
								{
									if( h_h < HoleHoleF && h_h < m_dr.hole_hole )
									{
										if( !part->utility && s->m_padstack[ip].name.Compare( t_s->m_padstack[t_ip].name ) )
										{
											str.Format( "is Warning: in the part %s hole to hole clearance less than clearance of DRC.\r\n", t_part->ref_des );
											if( m_dlg_log )
												m_dlg_log->AddLine( str );
											part->utility = WARNING_ADDED;
										}
									}
									HoleHoleF = min( HoleHoleF, h_h );
								}
								if( part->pin[ip].net != t_part->pin[t_ip].net )
								{
									// different net
									if (part != t_part)
										HoleHole = min( HoleHole, h_h );
									if( h_h < m_dr.hole_hole )
									{
										// PADHOLE_PADHOLE
										::MakeCStringFromDimension( &d_str, h_h, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &x_str, pin->x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &y_str, pin->y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										str.Format( "%ld: %s.%s pad hole to %s.%s pad hole = %s, x=%s, y=%s\r\n",  
										nerrors+1, part->ref_des, s->m_padstack[ip].name,
										t_part->ref_des, t_s->m_padstack[t_ip].name,
										d_str, x_str, y_str );
										DRError * dre = m_drelist->Add( nerrors, DRError::PADHOLE_PADHOLE, &str,
											&t_part->ref_des, &part->ref_des, id1, id2, 
											pin->x, pin->y, t_pin->x, t_pin->y, 0, 0 );
										if( dre )
										{
											nerrors++;
											if( m_dlg_log )
												m_dlg_log->AddLine( str );
										}
										break;		// go to next pin
									}
								}
								else
								{
									// same net
									if( s->m_padstack[ip].name.Compare( t_s->m_padstack[t_ip].name )  )
									{
										if ( h_h < m_dr.hole_copper )
										{
											if( h_h < HoleHoleTooClose && (!part->utility || !t_part->utility) )
											{
												// is Warning: pad hole to pad hole is too close\r\n
												str.Format( " %s.%s ", part->ref_des, s->m_padstack[ip].name );
												TooCloseToHole += str;
												//if( m_dlg_log )
												//	m_dlg_log->AddLine( str );
												part->utility = WARNING_ADDED;
												t_part->utility = WARNING_ADDED;
											}
										}
										if (part != t_part)
											HoleHoleTooClose = min(HoleHoleTooClose,h_h);
									}
								}
							}
							// check for pad clearance violations on each layer
							for( int il=0; il<m_num_copper_layers; il++ )
							{
								int layer = il + LAY_TOP_COPPER;
								int t_pad_x, t_pad_y, t_pad_w, t_pad_l, t_pad_r;
								int t_pad_type, t_pad_hole, t_pad_connect, t_pad_angle;
								cnet * t_pad_net;

								// test for pad-pad violation
								BOOL t_bPad = m_plist->GetPadDrawInfo( t_part, t_ip, layer, 0, 0, 0, 0,
									&t_pad_type, &t_pad_x, &t_pad_y, &t_pad_w, &t_pad_l, &t_pad_r, 
									&t_pad_hole, &t_pad_angle,
									&t_pad_net, &t_pad_connect );
								if( t_bPad )
								{
									// get pad info for pin
									int pad_x, pad_y, pad_w, pad_l, pad_r;
									int pad_type, pad_hole, pad_connect, pad_angle;
									cnet * pad_net;
									BOOL bPad = m_plist->GetPadDrawInfo( part, ip, layer, 0, 0, 0, 0, 
										&pad_type, &pad_x, &pad_y, &pad_w, &pad_l, &pad_r, 
										&pad_hole, &pad_angle, &pad_net, &pad_connect );
									BOOL b_T_PAD_W = ( t_pad_w > t_pad_hole && t_pad_type == PAD_ROUND ) || ( (double)t_pad_w > (double)t_pad_hole/1.41421356 );
									BOOL b_PAD_W = ( pad_w > pad_hole && pad_type == PAD_ROUND ) || ( (double)pad_w > (double)pad_hole/1.41421356 );
									if( bPad && b_T_PAD_W )
									{
										if( pad_hole )
										{
											// test for pad-padhole violation
											int dist = GetClearanceBetweenPads( t_pad_type, t_pad_x, t_pad_y, 
												t_pad_w, t_pad_l, t_pad_r, t_pad_angle,
												PAD_ROUND, pad_x, pad_y, pad_hole, 0, 0, 0 );
											if( part == t_part )
											{
												if( dist < HoleCopperF && dist < m_dr.hole_copper )
												{
													if( s->m_padstack[ip].name.Compare( t_s->m_padstack[t_ip].name ))
													{
														if( !part->utility )
														{
															str.Format( "is Warning: in the part %s pad to hole clearance less than clearance of DRC.\r\n", t_part->ref_des );
															if( m_dlg_log )
																m_dlg_log->AddLine( str );
															part->utility = WARNING_ADDED;
														}
														HoleCopperF = min( HoleCopperF, dist );
													}
												}
											}
											if( pad_net != t_pad_net )
											{
												// different net
												if (part != t_part)
													HoleCopper = min( HoleCopper, dist );
												if( dist < m_dr.hole_copper )
												{
													// PAD_PADHOLE 
													::MakeCStringFromDimension( &d_str, dist, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
													::MakeCStringFromDimension( &x_str, pad_x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
													::MakeCStringFromDimension( &y_str, pad_y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
													str.Format( "%ld: %s.%s pad hole to %s.%s pad = %s, x=%s, y=%s\r\n",  
														nerrors+1, part->ref_des, s->m_padstack[ip].name,
														t_part->ref_des, t_s->m_padstack[t_ip].name,
														d_str, x_str, y_str );
													DRError * dre = m_drelist->Add( nerrors, DRError::PAD_PADHOLE, &str, 
														&t_part->ref_des, &part->ref_des, id1, id2, 
														pad_x, pad_y, t_pad_x, t_pad_y, 0, layer );
													if( dre )
													{
														nerrors++;
														if( m_dlg_log )
															m_dlg_log->AddLine( str );
													}
													break;		// skip any more layers, go to next pin
												}
											}
											else
											{
												// same net
												if( s->m_padstack[ip].name.Compare( t_s->m_padstack[t_ip].name )  )
												{
													if ( dist < m_dr.hole_copper )
													{
														if( dist <= HoleCopperTooClose && (!part->utility || !t_part->utility) )
														{
															// is Warning: pad hole to pad is too close\r\n
															str.Format( " %s.%s ",  part->ref_des, s->m_padstack[ip].name );
															TooCloseToPadHole += str;
															//if( m_dlg_log )
															//	m_dlg_log->AddLine( str );
															part->utility = WARNING_ADDED;
															t_part->utility = WARNING_ADDED;
														}
													}
													if (part != t_part)
														HoleCopperTooClose = min(HoleCopperTooClose,dist);
												}
											}
										}
										if( pad_hole && !b_PAD_W )
											continue;
										// test for pad-pad violation
										int dist = GetClearanceBetweenPads( t_pad_type, t_pad_x, t_pad_y, 
											t_pad_w, t_pad_l, t_pad_r, t_pad_angle,
											pad_type, pad_x, pad_y, pad_w, pad_l, pad_r, pad_angle );
										if (part == t_part)
										{
											if( dist < PadPadF && s->m_padstack[ip].name.Compare(t_s->m_padstack[t_ip].name) )
											{											
												if( !part->utility || !t_part->utility )
													if( dist < m_dr.pad_pad )
													{
														str.Format( "is Warning: in the part %s pad to pad clearance less than clearance of DRC.\r\n", t_part->ref_des );
														if( m_dlg_log )
															m_dlg_log->AddLine( str );
														part->utility = WARNING_ADDED;
														t_part->utility = WARNING_ADDED;
													}
												PadPadF = min( PadPadF, dist );
											}
										}	
										if ( pad_net != t_pad_net )
										{	 
											// different net
											if (part != t_part)
												PadPad = min( PadPad, dist );
											if( dist < m_dr.pad_pad )
											{
												// Error 
												::MakeCStringFromDimension( &d_str, dist, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &x_str, pad_x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &y_str, pad_y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												str.Format( "%ld: %s.%s pad to %s.%s pad = %s, x=%s, y=%s\r\n",  
													nerrors+1, part->ref_des, s->m_padstack[ip].name,
													t_part->ref_des, t_s->m_padstack[t_ip].name,
													d_str, x_str, y_str );




												// test
												dist = GetClearanceBetweenPads( t_pad_type, t_pad_x, t_pad_y, 
											t_pad_w, t_pad_l, t_pad_r, t_pad_angle,
											pad_type, pad_x, pad_y, pad_w, pad_l, pad_r, pad_angle );





												DRError * dre = m_drelist->Add( nerrors, DRError::PAD_PAD, &str, 
													&t_part->ref_des, &part->ref_des, id1, id2, 
													pad_x, pad_y, t_pad_x, t_pad_y, 0, layer );
												if( dre )
												{
													nerrors++;
													if( m_dlg_log )
														m_dlg_log->AddLine( str );
												}
												break;		// skip any more layers, go to next pin
											}
										}
										else 
										{
											if ( dist < m_dr.pad_pad && part != t_part )
											{ 
												int rev = PadPadTooClose;
												if( part->shape->GetNumPins() == 1 || t_part->shape->GetNumPins() == 1 )
													rev = 0;
												if( dist <= rev && (!part->utility || !t_part->utility) )
												{
													// is Warning: pad to pad is too close\r\n
													str.Format( " %s.%s ",  part->ref_des, s->m_padstack[ip].name );
													TooCloseToPad += str;
													//if( m_dlg_log )
													//	m_dlg_log->AddLine( str );
													part->utility = WARNING_ADDED;
													t_part->utility = WARNING_ADDED;
													if( dist )
														PadPadTooClose = min(PadPadTooClose,dist);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	// iterate through all nets
	str.Format( "\r\nChecking nets and parts:\r\n" );
	if( m_dlg_log )
		m_dlg_log->AddLine( str );
	m_nlist->MarkAllNets(0);
	for( POSITION pos = m_nlist->m_map.GetStartPosition(); pos != NULL; )
	{
		CString name;
		cnet * net;
		if( nerrors > MAXERRORS )
		{
			goto cancel_verification;
		}
	
		void * ptr;
		m_nlist->m_map.GetNextAssoc( pos, name, ptr );
		net = (cnet*)ptr;
		// iterate through copper areas
		for( int ia=0; ia<net->nareas; ia++ )
		{
			carea * a = &net->area[ia];
			int a_w = a->poly->GetW();
			if( a->poly->GetHatch() == CPolyLine::NO_HATCH && a_w == 0 )
				continue;//  area Ghost
			//
			// iterate through contours
			int num_cont = a->poly->GetNumContours();
			if( nerrors > MAXERRORS )
			{
				goto cancel_verification;
			}
			for( int icont=0; icont<num_cont; icont++ )
			{
				// iterate through corners and sides
				int istart = a->poly->GetContourStart(icont);
				int iend = a->poly->GetContourEnd(icont);
				for( int ic=istart; ic<=iend; ic++ )
				{
					id id_a = net->id;
					id_a.st = ID_AREA;
					id_a.i = ia;
					id_a.sst = ID_SIDE;
					id_a.ii = ic;
					int x1 = a->poly->GetX(ic);
					int y1 = a->poly->GetY(ic);
					int x2, y2;
					if( ic < iend )
					{
						x2 = a->poly->GetX(ic+1);
						y2 = a->poly->GetY(ic+1);
					}
					else
					{
						x2 = a->poly->GetX(istart);
						y2 = a->poly->GetY(istart);
					}
					int style = a->poly->GetSideStyle(ic);

					// test clearance to board edge
					// iterate through board outlines
					for( int ib=0; ib<m_outline_poly.GetSize(); ib++ )
					{
						CPolyLine * b = &(m_outline_poly[ib]);
						if( b->GetLayer() != LAY_BOARD_OUTLINE )
							continue;
						// iterate through sides
						for( int ibc=0; ibc<b->GetNumSides(); ibc++ )
						{
							int bx1 = b->GetX(ibc);
							int by1 = b->GetY(ibc);
							int nxt = b->GetIndexCornerNext(ibc);
							int bx2 = b->GetX(nxt);
							int by2 = b->GetY(nxt);
							int bstyle = b->GetSideStyle(ibc);
							int x, y;
							int d = ::GetClearanceBetweenSegments( bx1, by1, bx2, by2, bstyle, 0,
								x1, y1, x2, y2, style, a_w, MAX_CL, &x, &y );
							BoardCopper = min( BoardCopper, d );
							if( d < m_dr.board_edge_copper )
							{
								// BOARDEDGE_COPPERAREA error
								::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
								::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
								::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
								str.Format( "%ld: \"%s\" copper area to board edge = %s, x=%s, y=%s\r\n",  
									nerrors+1, net->name, d_str, x_str, y_str );
								id id2( ID_POLYLINE, ID_BOARD, ib, ID_SIDE, ibc );
								DRError * dre = m_drelist->Add( nerrors, DRError::BOARDEDGE_COPPERAREA, &str,
									&net->name, NULL, id_a, id2, x, y, x, y, a_w+20*NM_PER_MIL, LAY_BOARD_OUTLINE );
								if( dre )
								{
									nerrors++;
									if( m_dlg_log )
										m_dlg_log->AddLine( str );
								}
							}
						}
					}
				}
			}
		}
		// iterate through all connections
		for( int ic=0; ic<net->nconnects; ic++ )
		{
			cconnect * c = &net->connect[ic];
			int pad_x, pad_y, pad_w, pad_l, pad_r;
			int pad_type, pad_hole, pad_connect, pad_angle;
			// test on contact
			if( c->seg[0].layer >= LAY_TOP_COPPER )
			{
				cpart * prt = net->pin[c->start_pin].part;
				CString pname = net->pin[c->start_pin].pin_name;
				int ipin=m_nlist->GetPinIndexByNameForPart( prt, pname, c->vtx[0].x, c->vtx[0].y );
				cnet * p_n;
				BOOL bP= m_plist->GetPadDrawInfo(  prt, ipin, c->seg[0].layer, 0, 0, 0, 0,
											&pad_type, &pad_x, &pad_y, &pad_w, &pad_l, &pad_r, 
											&pad_hole, &pad_angle, &p_n, &pad_connect );
				if (!bP)
				{
					// no connect?
					::MakeCStringFromDimension( &x_str, c->vtx[0].x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
					::MakeCStringFromDimension( &y_str, c->vtx[0].y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
					str.Format( "%ld: no connect? x=%s, y=%s\r\n", 
						nerrors+1, x_str, y_str );
					id IDs(ID_NET, ID_CONNECT, ic, ID_SEG, 0);
					id IDp(ID_PART, ID_PAD, ipin, 0, 0);
					DRError * dre = m_drelist->Add( nerrors, DRError::SEG_PAD, &str, 
						&net->name, &prt->ref_des, IDs, IDp, c->vtx[0].x, c->vtx[0].y, c->vtx[0].x, c->vtx[0].y, 
						c->seg[0].width+20*NM_PER_MIL, c->seg[0].layer );
					if( dre )
					{
						nerrors++;
						if( m_dlg_log )
							m_dlg_log->AddLine( str );
					}
				}
			}
			// test on contact
			if( c->seg[c->nsegs-1].layer >= LAY_TOP_COPPER && c->end_pin >= 0 && c->end_pin < c->nsegs )
			{
				cpart * prt = net->pin[c->end_pin].part;
				CString pname = net->pin[c->end_pin].pin_name;
				int ipin = m_nlist->GetPinIndexByNameForPart( prt, pname, c->vtx[c->nsegs].x, c->vtx[c->nsegs].y ); 
				cnet * p_n;
				BOOL bP = m_plist->GetPadDrawInfo(  prt, ipin, c->seg[c->nsegs-1].layer, 0, 0, 0, 0,
										&pad_type, &pad_x, &pad_y, &pad_w, &pad_l, &pad_r, 
										&pad_hole, &pad_angle, &p_n, &pad_connect );
				if (!bP)
				{
					// no connect?
					::MakeCStringFromDimension( &x_str, c->vtx[c->nsegs].x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
					::MakeCStringFromDimension( &y_str, c->vtx[c->nsegs].y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
					str.Format( "%ld: no connect? x=%s, y=%s\r\n", 
						nerrors+1, x_str, y_str );
					id IDs(ID_NET, ID_CONNECT, ic, ID_SEG, 0);
					id IDp(ID_PART, ID_PAD, ipin, 0, 0);
					DRError * dre = m_drelist->Add( nerrors, DRError::SEG_PAD, &str, 
						&net->name, &prt->ref_des, IDs, IDp, c->vtx[c->nsegs].x, c->vtx[c->nsegs].y, c->vtx[c->nsegs].x, c->vtx[c->nsegs].y, 
						c->seg[c->nsegs-1].width+20*NM_PER_MIL, c->seg[c->nsegs-1].layer );
					if( dre )
					{
						nerrors++;
						if( m_dlg_log )
							m_dlg_log->AddLine( str );
					}
				}
			}
			// get DRC info for this connection
			// iterate through all segments and vertices
			c->min_x = INT_MAX;		// bounding box for connection
			c->max_x = INT_MIN;
			c->min_y = INT_MAX;
			c->max_y = INT_MIN;
			c->vias_present = FALSE;
			c->seg_layers = 0;
			int max_trace_w = 0;	// maximum trace width for connection
			for( int is=0; is<c->nsegs; is++ )
			{
				if( c->seg[is].layer == LAY_RAT_LINE )
					continue;
				id id_seg = net->id;
				id_seg.st = ID_CONNECT;
				id_seg.i = ic;
				id_seg.sst = ID_SEG;
				id_seg.ii = is;
				int x1 = c->vtx[is].x;
				int y1 = c->vtx[is].y;
				int x2 = c->vtx[is+1].x;
				int y2 = c->vtx[is+1].y;
				int w = c->seg[is].width;
				int layer = c->seg[is].layer;
				if( c->seg[is].layer >= LAY_TOP_COPPER )
				{
					int layer_bit = c->seg[is].layer - LAY_TOP_COPPER;
					c->seg_layers |= 1<<layer_bit;
				}
				// add segment to bounding box
				int seg_min_x = min( x1, x2 );
				int seg_min_y = min( y1, y2 );
				int seg_max_x = max( x1, x2 );
				int seg_max_y = max( y1, y2 );
				c->min_x = min( c->min_x, seg_min_x - w/2 );
				c->max_x = max( c->max_x, seg_max_x + w/2 );
				c->min_y = min( c->min_y, seg_min_y - w/2 );
				c->max_y = max( c->max_y, seg_max_y + w/2 );
				// test trace width
				if (w)
				{
					TraceW = min( TraceW, w );
					if( w < m_dr.trace_width )
					{
						// TRACE_WIDTH error
						int x = (x1+x2)/2;
						int y = (y1+y2)/2;
						::MakeCStringFromDimension( &d_str, w, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
						::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
						::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
						str.Format( "%ld: \"%s\" trace width = %s, x=%s, y=%s\r\n", 
							nerrors+1, net->name, d_str, x_str, y_str );
						DRError * dre = m_drelist->Add( nerrors, DRError::TRACE_WIDTH, &str, 
							&net->name, NULL, id_seg, id_seg, x, y, x, y, w+20*NM_PER_MIL, layer );
						if( dre )
						{
							nerrors++;
							if( m_dlg_log )
								m_dlg_log->AddLine( str );
						}
					}
					// test clearance to board edge
					for( int ib=0; ib<m_outline_poly.GetSize(); ib++ )
					{
						CPolyLine * b = &(m_outline_poly[ib]);
						if( b->GetLayer() != LAY_BOARD_OUTLINE )
							continue;
						for( int ibc=0; ibc<b->GetNumSides(); ibc++ )
						{
							int bx1 = b->GetX(ibc);
							int by1 = b->GetY(ibc);
							int bx2 = b->GetX(b->GetIndexCornerNext(ibc));
							int by2 = b->GetY(b->GetIndexCornerNext(ibc));
							int bstyle = b->GetSideStyle(ibc);
							int x, y;
							int d = ::GetClearanceBetweenSegments( bx1, by1, bx2, by2, bstyle, 0,
								x1, y1, x2, y2, CPolyLine::STRAIGHT, w, MAX_CL, &x, &y );
							BoardCopper = min( BoardCopper, d );
							if( d < m_dr.board_edge_copper )
							{
								// BOARDEDGE_TRACE error
								::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
								::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
								::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
								str.Format( "%ld: \"%s\" trace to board edge = %s, x=%s, y=%s\r\n",  
									nerrors+1, net->name, d_str, x_str, y_str );
								id id2( ID_POLYLINE, ID_BOARD, ib, ID_SIDE, ibc );
								DRError * dre = m_drelist->Add( nerrors, DRError::BOARDEDGE_TRACE, &str,
									&net->name, NULL, id_seg, id2, x, y, x, y, w+20*NM_PER_MIL, layer );
								if( dre )
								{
									nerrors++;
									if( m_dlg_log )
										m_dlg_log->AddLine( str );
								}
							}
						}
					}
				}
			}
			for( int iv=0; iv<c->nsegs+1; iv++ )
			{
				cvertex * vtx = &c->vtx[iv];
				if( vtx->via_w )
				{
					// via present
					id id_via = net->id;
					id_via.st = ID_CONNECT;
					id_via.i = ic;
					id_via.sst = ID_VIA;
					id_via.ii = iv;
					c->vias_present = TRUE;
					int min_via_w = INT_MAX;	// minimum via pad diameter
					int max_via_w = 0;	// maximum via_pad diameter
					int max_hole_w = 0;
					int ann_r = INT_MAX;
					for( int il=0; il<m_num_copper_layers; il++ )
					{
						int layer = il + LAY_TOP_COPPER;
						int test;
						int pad_w;
						int hole_w;
						m_nlist->GetViaPadInfo( net, ic, iv, layer, 
							&pad_w, &hole_w, &test );
						if( pad_w )
							ann_r = min( ann_r, (pad_w-hole_w)/2 );
						min_via_w = min( min_via_w, pad_w );
						max_via_w = max( max_via_w, pad_w );
						max_hole_w = max( max_hole_w, hole_w );
					}
					if( max_via_w > 0 )
					{
						c->min_x = min( c->min_x, vtx->x - max_via_w/2 );
						c->max_x = max( c->max_x, vtx->x + max_via_w/2 );
						c->min_y = min( c->min_y, vtx->y - max_via_w/2 );
						c->max_y = max( c->max_y, vtx->y + max_via_w/2 );
						arVias = min( arVias, ann_r );
						if( ann_r < m_dr.annular_ring_vias )
						{
							// RING_VIA
							::MakeCStringFromDimension( &d_str, ann_r, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
							::MakeCStringFromDimension( &x_str, vtx->x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
							::MakeCStringFromDimension( &y_str, vtx->y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
							str.Format( "%ld: \"%s\" via annular ring = %s, x=%s, y=%s\r\n", 
								nerrors+1, net->name, d_str, x_str, y_str );
							DRError * dre = m_drelist->Add( nerrors, DRError::RING_VIA, &str, 
								&net->name, NULL, id_via, id_via, vtx->x, vtx->y, 0, 0, vtx->via_w+20*NM_PER_MIL, 0 );
							if( dre )
							{
								nerrors++;
								if( m_dlg_log )
									m_dlg_log->AddLine( str );
							}
						}
						if( max_hole_w )
						{
							BOOL F = 0;
							for( int ibox=0; ibox<ArHoles.GetSize(); ibox++ )
								if( ArHoles.GetAt(ibox) == max_hole_w )
									F = 1;
							if( F == 0 )
								ArHoles.Add(max_hole_w);
						}
					}
					else
					{
						AfxMessageBox(G_LANGUAGE == 0 ? "Via pad not found!":"Пад переходного отверстия не найден");
						ASSERT(0);
					}
					// test clearance to board edge
					for( int ib=0; ib<m_outline_poly.GetSize(); ib++ )
					{
						CPolyLine * b = &(m_outline_poly[ib]);
						if( b->GetLayer() != LAY_BOARD_OUTLINE )
							continue;
						for( int ibc=0; ibc<b->GetNumSides(); ibc++ )
						{
							int bx1 = b->GetX(ibc);
							int by1 = b->GetY(ibc);
							int bx2 = b->GetX(b->GetIndexCornerNext(ibc));
							int by2 = b->GetY(b->GetIndexCornerNext(ibc));
							//** for now, only works for straight board edge segments
							{
								int d = ::GetClearanceBetweenSegments(	bx1, by1, bx2, by2, b->GetSideStyle(ibc), 0,
																		vtx->x-10, vtx->y-10, vtx->x+10, vtx->y+10, 
																		CPolyLine::STRAIGHT, vtx->via_w, MAX_CL, 0, 0 );
								BoardCopper = min( BoardCopper, d );
								if( d < m_dr.board_edge_copper )
								{
									// BOARDEDGE_VIA error
									::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
									::MakeCStringFromDimension( &x_str, vtx->x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
									::MakeCStringFromDimension( &y_str, vtx->y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
									str.Format( "%ld: \"%s\" via to board edge = %s, x=%s, y=%s\r\n",  
										nerrors+1, net->name, d_str, x_str, y_str );
									id id2( ID_POLYLINE, ID_BOARD, ib, ID_SIDE, ibc );
									DRError * dre = m_drelist->Add( nerrors, DRError::BOARDEDGE_VIA, &str,
										&net->name, NULL, id_via, id2, vtx->x, vtx->y, 0, 0, vtx->via_w+20*NM_PER_MIL, 0 );
									if( dre )
									{
										nerrors++;
										if( m_dlg_log )
											m_dlg_log->AddLine( str );
									}
								}
								int dh = ::GetClearanceBetweenSegments(	bx1, by1, bx2, by2, b->GetSideStyle(ibc), 0,
																		vtx->x-10, vtx->y-10, vtx->x+10, vtx->y+10, 
																		CPolyLine::STRAIGHT, vtx->via_hole_w, MAX_CL, 0, 0 );
								BoardHole = min( BoardHole, dh );
								if( dh < m_dr.board_edge_hole )
								{
									// BOARDEDGE_VIAHOLE error
									::MakeCStringFromDimension( &d_str, dh, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
									::MakeCStringFromDimension( &x_str, vtx->x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
									::MakeCStringFromDimension( &y_str, vtx->y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
									str.Format( "%ld: \"%s\" via hole to board edge = %s, x=%s, y=%s\r\n",  
										nerrors+1, net->name, d_str, x_str, y_str );
									id id2( ID_POLYLINE, ID_BOARD, ib, ID_SIDE, ibc );
									DRError * dre = m_drelist->Add( nerrors, DRError::BOARDEDGE_VIAHOLE, &str,
										&net->name, NULL, id_via, id2, vtx->x, vtx->y, 0, 0, vtx->via_w+20*NM_PER_MIL, 0 );
									if( dre )
									{
										nerrors++;
										if( m_dlg_log )
											m_dlg_log->AddLine( str );
									}
								}
							}
						}
					}
				}
			}
			// iterate through all parts
			padstack * warning_ps;
			//
			for( cpart * part = m_plist->GetFirstPart(); part; part = m_plist->GetNextPart( part ) )
			{
				CShape * s = part->shape;
				// if not on same layers, can't conflict
				if( !part->hole_flag && !c->vias_present && !(part->layers & c->seg_layers) )
					continue;	// next part

				// if bounding boxes don't overlap, can't conflict
				if( part->min_x - c->max_x > m_dr.pad_trace )
					continue;	// next part
				if( c->min_x - part->max_x > m_dr.pad_trace )
					continue;	// next part
				if( part->min_y - c->max_y > m_dr.pad_trace )
					continue;	// next part
				if( c->min_y - part->max_y > m_dr.pad_trace )
					continue;	// next part

				// OK, now we have to test each pad
				for( int ip=0; ip<part->shape->GetNumPins(); ip++ )
				{
					padstack * ps = &s->m_padstack[ip];
					padstack * warn_via_ps = NULL;
					part_pin * pin = &part->pin[ip];
					drc_pin * drp = &pin->drc;
					id id_pad = part->m_id;
					id_pad.st = ID_PAD;
					id_pad.i = ip;
					// if pin and connection bounds are separated enough, skip pin
					if( drp->min_x - c->max_x > m_dr.pad_trace )
						continue;	// no, next pin
					if( c->min_x - drp->max_x > m_dr.pad_trace )
						continue;	// no, next pin
					if( drp->min_y - c->max_y > m_dr.pad_trace )
						continue;	// no, next pin
					if( c->min_y - drp->max_y > m_dr.pad_trace )
						continue;	// no, next pin

					// possible clearance violation, now test each segment and via on each layer
					int pad_x, pad_y, pad_w, pad_l, pad_r;
					int pad_type, pad_hole, pad_connect, pad_angle;
					cnet * pad_net;
					BOOL bPad;
					BOOL pin_info_valid = FALSE;
					int pin_info_layer = 0;
					for( int is=0; is<c->nsegs; is++ )
					{
						// get next segment
						cseg * seg = &(net->connect[ic].seg[is]);
						cvertex * pre_vtx = &(net->connect[ic].vtx[is]);
						cvertex * post_vtx = &(net->connect[ic].vtx[is+1]);
						int w = seg->width;
						int xi = pre_vtx->x;
						int yi = pre_vtx->y;
						int xf = post_vtx->x;
						int yf = post_vtx->y;
						int min_x = min( xi, xf ) - w/2;
						int max_x = max( xi, xf ) + w/2;
						int min_y = min( yi, yf ) - w/2;
						int max_y = max( yi, yf ) + w/2;
						// ids
						id id_seg = net->id;
						id_seg.st = ID_CONNECT;
						id_seg.i = ic;
						id_seg.sst = ID_SEG;
						id_seg.ii = is;
						id id_via = net->id;
						id_via.st = ID_CONNECT;
						id_via.i = ic;
						id_via.sst = ID_VIA;
						id_via.ii = is+1;

						// check all layers
						for( int il=0; il<m_num_copper_layers; il++ )
						{
							int layer = il + LAY_TOP_COPPER;
							int layer_bit = 1<<il;
							if( seg->layer == layer )
							{
								// check segment clearances
								cnet * pin_net = part->pin[ip].net;
								if( ps->hole_size && net != pin_net )
								{
									// pad has hole, check segment to pad_hole clearance
									if( !(pin_info_valid && layer == pin_info_layer) )
									{
										bPad = m_plist->GetPadDrawInfo( part, ip, layer, 0, 0, 0, 0,
											&pad_type, &pad_x, &pad_y, &pad_w, &pad_l, &pad_r, 
											&pad_hole, &pad_angle, &pad_net, &pad_connect );
										pin_info_valid = TRUE;
										pin_info_layer = layer;
									}
									int d = GetClearanceBetweenSegmentAndPad( xi, yi, xf, yf, w,
										PAD_ROUND, pad_x, pad_y, pad_hole, 0, 0, 0 );
									HoleCopper = min( HoleCopper, d );
									if( d < m_dr.hole_copper ) 
									{
										// SEG_PADHOLE
										::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &x_str, pad_x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &y_str, pad_y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										str.Format( "%ld: \"%s\" trace to %s.%s pad hole = %s, x=%s, y=%s\r\n", 
											nerrors+1, net->name, part->ref_des, ps->name,
											d_str, x_str, y_str );
										DRError * dre = m_drelist->Add( nerrors, DRError::SEG_PAD, &str, 
											&net->name, &part->ref_des, id_seg, id_pad, pad_x, pad_y, pad_x, pad_y, 
											max(pad_w,pad_l)+20*NM_PER_MIL, layer );
										if( dre )
										{
											nerrors++;
											if( m_dlg_log )
												m_dlg_log->AddLine( str );
										}
									}
								}
								if( layer_bit & drp->layers )
								{
									// pad is on this layer
									// get pad info for pin if necessary
									if( !(pin_info_valid && layer == pin_info_layer) )
									{
										bPad = m_plist->GetPadDrawInfo( part, ip, layer, 0, 0, 0, 0, 
											&pad_type, &pad_x, &pad_y, &pad_w, &pad_l, &pad_r,
											&pad_hole, &pad_angle, &pad_net, &pad_connect );
										pin_info_valid = TRUE;
										pin_info_layer = layer;
									}
									if( bPad )
									{
										if( pad_type != PAD_NONE )
										{
											if( net != pad_net )
											{
												// check segment to pad clearance
												int d = GetClearanceBetweenSegmentAndPad( xi, yi, xf, yf, w,
													pad_type, pad_x, pad_y, pad_w, pad_l, pad_r, pad_angle );
												PadTrace = min( PadTrace, d );
												if( d < m_dr.pad_trace ) 
												{
													// SEG_PAD
													::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
													::MakeCStringFromDimension( &x_str, pad_x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
													::MakeCStringFromDimension( &y_str, pad_y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
													str.Format( "%ld: \"%s\" trace to %s.%s pad = %s(%d), x=%s, y=%s\r\n", 
														nerrors+1, net->name, part->ref_des, ps->name,
														d_str, layer, x_str, y_str );
													DRError * dre = m_drelist->Add( nerrors, DRError::SEG_PAD, &str, 
														&net->name, &part->ref_des, id_seg, id_pad, pad_x, pad_y, pad_x, pad_y, 
														max(pad_w,pad_l)+20*NM_PER_MIL, layer );
													if( dre )
													{
														nerrors++;
														if( m_dlg_log )
															m_dlg_log->AddLine( str );
													}
												}
											}
										}
									}
								}
							}
							// get next via
							if( post_vtx->via_w )
							{
								// via exists
								int test;
								int via_w;
								int via_hole_w;
								m_nlist->GetViaPadInfo( net, ic, is+1, layer, 
									&via_w, &via_hole_w, &test );
								int w = 0;
								if( via_w )
								{
									// check via_pad to pin_pad clearance
									if( !(pin_info_valid && layer == pin_info_layer) )
									{
										bPad = m_plist->GetPadDrawInfo( part, ip, layer, 0, 0, 0, 0, 
											&pad_type, &pad_x, &pad_y, &pad_w, &pad_l, &pad_r, 
											&pad_hole, &pad_angle, &pad_net, &pad_connect );
										pin_info_valid = TRUE;
										pin_info_layer = layer;
									}
									if( bPad && pad_type != PAD_NONE && pad_net != net )
									{
										int d = GetClearanceBetweenPads( PAD_ROUND, xf, yf, via_w, 0, 0, 0,
											pad_type, pad_x, pad_y, pad_w, pad_l, pad_r, pad_angle );
										PadTrace = min( PadTrace, d );
										if( d < m_dr.pad_trace )
										{
											// VIA_RING_PAD
											::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &x_str, pad_x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &y_str, pad_y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											str.Format( "%ld: \"%s\" via pad to %s.%s pad = %s, x=%s, y=%s\r\n", 
												nerrors+1, net->name, part->ref_des, ps->name,
												d_str, x_str, y_str );
											DRError * dre = m_drelist->Add( nerrors, DRError::VIA_PAD, &str, 
												&net->name, &part->ref_des, id_via, id_pad, xf, yf, pad_x, pad_y, 0, layer );
											if( dre )
											{
												nerrors++;
												if( m_dlg_log )
													m_dlg_log->AddLine( str );
											}
											break;  // skip more layers
										}
									}
									if( ps->hole_size && pad_net != net )
									{
										// pin has a hole, check via_pad to pin_hole clearance
										int d = Distance( xf, yf, pin->x, pin->y );
										d = max( 0, d - ps->hole_size/2 - via_w/2 );
										HoleCopper = min( HoleCopper, d );
										if( d < m_dr.hole_copper )
										{
											// VIA_RING_PADHOLE
											::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &x_str, pad_x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &y_str, pad_y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											str.Format( "%ld: \"%s\" via pad to %s.%s pad hole = %s, x=%s, y=%s\r\n", 
												nerrors+1, net->name, part->ref_des, ps->name,
												d_str, x_str, y_str );
											DRError * dre = m_drelist->Add( nerrors, DRError::VIA_PAD, &str, 
												&net->name, &part->ref_des, id_via, id_pad, xf, yf, pad_x, pad_y, 0, layer );
											if( dre )
											{
												nerrors++;
												if( m_dlg_log )
													m_dlg_log->AddLine( str );
											}
											break;  // skip more layers
										}
									}
									if( bPad && pad_type != PAD_NONE )
									{
										// check via_hole to pin_pad clearance
										int d = GetClearanceBetweenPads( PAD_ROUND, xf, yf, via_hole_w, 0, 0, 0,
											pad_type, pad_x, pad_y, pad_w, pad_l, pad_r, pad_angle );
										if ( pad_net != net )
										{
											HoleCopper = min( HoleCopper, d );
											if( d < m_dr.hole_copper )
											{
												// VIAHOLE_PAD
												::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &x_str, pad_x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &y_str, pad_y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												str.Format( "%ld: \"%s\" via hole to %s.%s pad = %s, x=%s, y=%s\r\n", 
													nerrors+1, net->name, part->ref_des, ps->name,
													d_str, x_str, y_str );
												DRError * dre = m_drelist->Add( nerrors, DRError::VIA_PAD, &str, 
													&net->name, &part->ref_des, id_via, id_pad, xf, yf, pad_x, pad_y, 0, layer );
												if( dre )
												{
													nerrors++;
													if( m_dlg_log )
														m_dlg_log->AddLine( str );
												}
												break;  // skip more layers
											}	
										}
										else if( d < m_mask_clearance /*(via_w-via_hole_w)/3*/ && post_vtx->utility2 == 0 )
										{
											if( warn_via_ps != ps )
											{
												ViaHoleToPadSameNet = min(ViaHoleToPadSameNet,d);
												// is Warning: pin to via hole is too close.\r\n
												str.Format( " %s.%s ",  part->ref_des, ps->name );
												if( TooCloseToViaHole.Find(str) < 0 )
													TooCloseToViaHole += str;
												post_vtx->utility2 = WARNING_ADDED;
												//if( m_dlg_log )
												//	m_dlg_log->AddLine( str );
											}
											warn_via_ps = ps;
											break;  // skip more layers
										}
									}
									if( ps->hole_size && pad_net != net && layer == LAY_TOP_COPPER )
									{
										// pin has a hole, check via_hole to pin_hole clearance
										int d = Distance( xf, yf, pin->x, pin->y );
										d = max( 0, d - ps->hole_size/2 - via_hole_w/2 );
										HoleHole = min( HoleHole, d );
										if( d < m_dr.hole_hole )
										{
											// VIAHOLE_PADHOLE
											::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &x_str, pad_x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &y_str, pad_y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											str.Format( "%ld: \"%s\" via hole to %s.%s pad hole = %s, x=%s, y=%s\r\n", 
												nerrors+1, net->name, part->ref_des, ps->name,
												d_str, x_str, y_str );
											DRError * dre = m_drelist->Add( nerrors, DRError::VIA_PAD, &str, 
												&net->name, &part->ref_des, id_via, id_pad, xf, yf, pad_x, pad_y, 0, layer );
											if( dre )
											{
												nerrors++;
												if( m_dlg_log )
													m_dlg_log->AddLine( str );
											}
											break;  // skip more layers
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	// now check nets against other nets
	str.Format( "\r\nChecking nets:\r\n" );
	if( m_dlg_log )
		m_dlg_log->AddLine( str );
	{
		// get max clearance
		int cl = max( m_dr.hole_copper, m_dr.hole_hole );
		cl = max( cl, m_dr.copper_copper );
		cl = max( cl, m_dr.trace_trace );
		cl *= 2;
		// iterate through all nets
		for( POSITION pos = m_nlist->m_map.GetStartPosition(); pos != NULL; )
		{
			CString name;
			cnet * net;
			if( nerrors > MAXERRORS )
			{
				goto cancel_verification;
			}
		
			void * ptr;
			m_nlist->m_map.GetNextAssoc( pos, name, ptr );
			net = (cnet*)ptr;
			// iterate through all connections
			for( int ic=0; ic<net->nconnects; ic++ )
			{
				cconnect * c = &net->connect[ic];
				//
				// iterate through all nets again
				//
				POSITION pos2 = pos;
				void * ptr2;
				CString name2;
				while( pos2 != NULL )
				{
					m_nlist->m_map.GetNextAssoc( pos2, name2, ptr2 );
					cnet * net2 = (cnet*)ptr2;
					if( nerrors > MAXERRORS )
					{
						goto cancel_verification;
					}
					//
					// iterate through all areas with hsFull
					// 
					for( int iar=0; iar<net2->nareas; iar++ )
					{
						RECT arct2;
						arct2 = net2->area[iar].poly->GetBounds();
						carea * area = &net2->area[iar];

						// merge clearance
						int areaM = area->poly->GetMerge();
						int m_cl = 0;
						if( areaM >= 0 )
							m_cl = m_mlist->GetClearance( areaM );

						// look for possible clearance violations between c and arct2
						if( c->min_x     - arct2.right > cl )
							continue;	// no, next area
						if( c->min_y     - arct2.top > cl )
							continue;	// no, next area
						if( arct2.left   - c->max_x > cl )
							continue;	// no, next area
						if( arct2.bottom - c->max_y > cl )
							continue;	// no, next area
						if (area->poly->GetHatch() != CPolyLine::DIAGONAL_FULL)
							continue;	// no, next area
						if (net->name.Compare(net2->name) == 0 )
					 		continue;	// no, next area
						// now test spacing for areas hs Full
						id id_a;
						id_a.Set(ID_NET, ID_AREA, iar, ID_SIDE, 0); 
						int a_n_corners = area->poly->GetNumCorners();
						int a_layer = area->poly->GetLayer();
						int a_w = area->poly->GetW();
						// now we have to test all segments and vias in c
						for( int iseg=0; iseg<c->nsegs; iseg++ )
						{
							// get next segment and via
							cseg * s = &c->seg[iseg];
							cvertex * pre_vtx = &c->vtx[iseg];
							cvertex * post_vtx = &c->vtx[iseg+1];
							int seg_w = s->width;
							int vw = post_vtx->via_w;
							int vh = post_vtx->via_hole_w;
							int status;
							if( vw )
								m_nlist->GetViaPadInfo( net, ic, iseg+1, a_layer, &vw, &vh, &status );
							//	
							int xs1 = pre_vtx->x;
							int ys1 = pre_vtx->y;
							int xs2 = post_vtx->x;
							int ys2 = post_vtx->y;
							// ids
							id id_seg( ID_NET, ID_CONNECT, ic, ID_SEG, iseg );
							id id_via( ID_NET, ID_CONNECT, ic, ID_VIA, iseg+1 );
							//
							// test via hole inside
							//
							if ( vh )
							{
								if ( area->poly->TestPointInside(xs2, ys2) )
								{
									if( m_dr.hole_copper  > _2540 )
									{
										HoleCopper = 0;
										::MakeCStringFromDimension( &x_str, xs2, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &y_str, ys2, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										str.Format( "%ld: \"%s\" area hsFull to \"%s\" via hole = 0, x=%s, y=%s\r\n", 
											nerrors+1, net2->name, net->name,
											x_str, y_str );
										DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_VIA_INSIDE, &str, 
											&net2->name, &net->name, id_a, id_via, xs2, ys2, xs2, ys2, 
											vh+10*NM_PER_MIL, 0 );
										if( dre )
										{
											nerrors++;
											if( m_dlg_log )
												m_dlg_log->AddLine( str );
										}
									}
								}
							}
							for( int icor=0; icor<a_n_corners; icor++ )
							{
								int xc1 = area->poly->GetX(icor);
								int yc1 = area->poly->GetY(icor);
								int xc2 = area->poly->GetX(area->poly->GetIndexCornerNext(icor));
								int yc2 = area->poly->GetY(area->poly->GetIndexCornerNext(icor));
								int side_style = area->poly->GetSideStyle(icor);
								int x,y;
								id_a.ii = icor;
								//
								// test segment
								//
								if ( a_layer == s->layer )
								{
									// check clearance between net2->area side (hsFull) and net->segment
									int d = GetClearanceBetweenSegments( xc1, yc1, xc2, yc2, side_style, a_w,
										xs1, ys1, xs2, ys2, CPolyLine::STRAIGHT, seg_w, MAX_CL, &x, &y );
									AreaCopperHsFull = min( AreaCopperHsFull, d );
									if( d < (m_cl?m_cl:m_dr.copper_copper) )
									{
										::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										str.Format( "%ld: \"%s\" area hsFull to \"%s\" segment = %s, x=%s, y=%s\r\n", 
											nerrors+1, net2->name, net->name,
											d_str, x_str, y_str );
										DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_TRACE, &str, 
											&net2->name, &net->name, id_a, id_seg, x, y, x, y, 
											seg_w+10*NM_PER_MIL, 0 );
										if( dre )
										{
											nerrors++;
											if( m_dlg_log )
												m_dlg_log->AddLine( str );
										}
									}
								}
								//
								// test via
								//
								if ( vw )
								{
									// via exists
									int test = m_nlist->GetViaConnectionStatus( net, ic, iseg+1, s->layer );
									int via_w = vw;	// normal via pad
									if( s->layer > LAY_BOTTOM_COPPER && test == CNetList::VIA_NO_CONNECT )
									{
										// inner layer and no trace or thermal, so no via pad
										via_w = 0;
									}
									else if( s->layer > LAY_BOTTOM_COPPER && (test & CNetList::VIA_AREA) && !(test & CNetList::VIA_TRACE) )
									{
										// inner layer with small thermal, use annular ring
										via_w = post_vtx->via_hole_w + 2*m_dr.annular_ring_vias;
									}
									// check clearance between net2->area side (hsFull) and net->via_pad
									int d = GetClearanceBetweenSegments( xc1, yc1, xc2, yc2, side_style, a_w,
										xs2, ys2, xs2, ys2, CPolyLine::STRAIGHT, via_w, MAX_CL, &x, &y );
									AreaCopperHsFull = min( AreaCopperHsFull, d );
									if( d < (m_cl?m_cl:m_dr.copper_copper) )
									{
										::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										str.Format( "%ld: \"%s\" area hsFull to \"%s\" via pad = %s, x=%s, y=%s\r\n", 
											nerrors+1, net2->name, net->name, d_str, x_str, y_str );
										DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_VIA, &str, 
											&net2->name, &net->name, id_a, id_via, xs2, ys2, xs2, ys2, 
											via_w+10*NM_PER_MIL, 0 );
										if( dre )
										{
											nerrors++;
											if( m_dlg_log )
												m_dlg_log->AddLine( str );
										}
									}
								}
								//
								// test via hole
								//
								if ( vh )
								{
									// check clearance between net2->area side (hsFull) and net->via_hole
									int d = GetClearanceBetweenSegments( xc1, yc1, xc2, yc2, side_style, a_w,
										xs2, ys2, xs2, ys2, CPolyLine::STRAIGHT, vh, MAX_CL, &x, &y );
									HoleCopper = min( HoleCopper, d );
									if( d < (m_cl?m_cl:m_dr.hole_copper) )
									{
										::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										str.Format( "%ld: \"%s\" area hsFull to \"%s\" via hole = %s, x=%s, y=%s\r\n", 
											nerrors+1, net2->name, net->name,
											d_str, x_str, y_str );
										DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_VIA, &str, 
											&net2->name, &net->name, id_a, id_via, xs2, ys2, xs2, ys2, 
											vh+10*NM_PER_MIL, 0 );
										if( dre )
										{
											nerrors++;
											if( m_dlg_log )
												m_dlg_log->AddLine( str );
										}
									}
								}
							}
						}
					} 
					//
					// iterate through all connections
					//
					for( int ic2=0; ic2<net2->nconnects; ic2++ )
					{
						cconnect * c2 = &net2->connect[ic2];
						// look for possible clearance violations between c and c2
						if( c->min_x - c2->max_x > cl )
							continue;	// no, next connection
						if( c->min_y - c2->max_y > cl )
							continue;	// no, next connection
						if( c2->min_x - c->max_x > cl )
							continue;	// no, next connection
						if( c2->min_y - c->max_y > cl )
							continue;	// no, next connection

						// now we have to test all segments and vias in c
						for( int is=0; is<c->nsegs; is++ )
						{
							// get next segment and via
							cseg * s = &c->seg[is];
							cvertex * pre_vtx = &c->vtx[is];
							cvertex * post_vtx = &c->vtx[is+1];
							int seg_w = s->width;
							int vw = post_vtx->via_w;
							int max_w = max( seg_w, vw );
							int xi = pre_vtx->x;
							int yi = pre_vtx->y;
							int xf = post_vtx->x;
							int yf = post_vtx->y;
							// get bounding rect for segment and vias
							int min_x = min( xi, xf ) - max_w/2;
							int max_x = max( xi, xf ) + max_w/2;
							int min_y = min( yi, yf ) - max_w/2;
							int max_y = max( yi, yf ) + max_w/2;
							// ids
							id id_seg1( ID_NET, ID_CONNECT, ic, ID_SEG, is );
							id id_via1( ID_NET, ID_CONNECT, ic, ID_VIA, is+1 );

							// iterate through all segments and vias in c2
							for( int is2=0; is2<c2->nsegs; is2++ )
							{
								// get next segment and via
								cseg * s2 = &c2->seg[is2];
								cvertex * pre_vtx2 = &c2->vtx[is2];
								cvertex * post_vtx2 = &c2->vtx[is2+1];
								int seg_w2 = s2->width;
								int vw2 = post_vtx2->via_w;
								int max_w2 = max( seg_w2, vw2 );
								int xi2 = pre_vtx2->x;
								int yi2 = pre_vtx2->y;
								int xf2 = post_vtx2->x;
								int yf2 = post_vtx2->y;
								// get bounding rect for this segment and attached vias
								int min_x2 = min( xi2, xf2 ) - max_w2/2;
								int max_x2 = max( xi2, xf2 ) + max_w2/2;
								int min_y2 = min( yi2, yf2 ) - max_w2/2;
								int max_y2 = max( yi2, yf2 ) + max_w2/2;
								// ids
								id id_seg2( ID_NET, ID_CONNECT, ic2, ID_SEG, is2 );
								id id_via2( ID_NET, ID_CONNECT, ic2, ID_VIA, is2+1 );

								// see if segment bounding rects are too close
								if( min_x - max_x2 > cl )
									continue;	// no, next segment
								if( min_y - max_y2 > cl )
									continue;
								if( min_x2 - max_x > cl )
									continue;
								if( min_y2 - max_y > cl )
									continue;
								//
								// check if segments on same layer
								//
								if( s->layer == s2->layer && s->layer >= LAY_TOP_COPPER ) 
								{
									// yes, test clearances between segments
									int xx, yy; 
									int d = ::GetClearanceBetweenSegments( xi, yi, xf, yf, CPolyLine::STRAIGHT, seg_w, 
										xi2, yi2, xf2, yf2, CPolyLine::STRAIGHT, seg_w2, MAX_CL, &xx, &yy );
									TraceTrace = min( TraceTrace, d );
									if( d < m_dr.trace_trace )
									{
										// SEG_SEG
										::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &x_str, xx, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										::MakeCStringFromDimension( &y_str, yy, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
										str.Format( "%ld: \"%s\" trace to \"%s\" trace = %s, x=%s, y=%s\r\n", 
											nerrors+1, net->name, net2->name,
											d_str, x_str, y_str );
										DRError * dre = m_drelist->Add( nerrors, DRError::SEG_SEG, &str, 
											&net->name, &net2->name, id_seg1, id_seg2, xx, yy, xx, yy, 0, s->layer );
										if( dre )
										{
											nerrors++;
											if( m_dlg_log )
												m_dlg_log->AddLine( str );
										}
									}
								}
								//
								// test clearances between net->segment and net2->via
								//
								int layer = s->layer;
								if( layer >= LAY_TOP_COPPER && post_vtx2->via_w )
								{
									if( getbit( post_vtx2->layer_bit, layer ) )
									{
										// via exists
										int test = m_nlist->GetViaConnectionStatus( net2, ic2, is2+1, layer );
										int via_w2 = post_vtx2->via_w;	// normal via pad
										if( layer > LAY_BOTTOM_COPPER && test == CNetList::VIA_NO_CONNECT )
										{
											// inner layer and no trace or thermal, so no via pad
											via_w2 = 0;
										}
										else if( layer > LAY_BOTTOM_COPPER && (test & CNetList::VIA_AREA) && !(test & CNetList::VIA_TRACE) )
										{
											// inner layer with small thermal, use annular ring
											via_w2 = post_vtx2->via_hole_w + 2*m_dr.annular_ring_vias;
										}
										// check clearance
										if( via_w2 )
										{
											// check clearance between segment and via pad
											int d = GetClearanceBetweenSegmentAndPad( xi, yi, xf, yf, seg_w,
												PAD_ROUND, post_vtx2->x, post_vtx2->y, post_vtx2->via_w, 0, 0, 0 );
											TraceTrace = min( TraceTrace, d );
											if( d < m_dr.trace_trace )
											{
												// SEG_VIA
												::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &x_str, post_vtx2->x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &y_str, post_vtx2->y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												str.Format( "%ld: \"%s\" trace to \"%s\" via pad = %s, x=%s, y=%s\r\n", 
													nerrors+1, net->name, net2->name,
													d_str, x_str, y_str );
												DRError * dre = m_drelist->Add( nerrors, DRError::SEG_VIA, &str, 
													&net->name, &net2->name, id_seg1, id_via2, xf2, yf2, xf2, yf2, 0, s->layer );
												if( dre )
												{
													nerrors++;
													if( m_dlg_log )
														m_dlg_log->AddLine( str );
												}
											}
										}
										//
										// check clearance between segment and via hole
										//
										int d = GetClearanceBetweenSegmentAndPad( xi, yi, xf, yf, seg_w,
											PAD_ROUND, post_vtx2->x, post_vtx2->y, post_vtx2->via_hole_w, 0, 0, 0 );
										HoleCopper = min( HoleCopper, d );
										if( d < m_dr.hole_copper )
										{
											// SEG_VIAHOLE
											::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &x_str, post_vtx2->x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &y_str, post_vtx2->y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											str.Format( "%ld: \"%s\" trace to \"%s\" via hole = %s, x=%s, y=%s\r\n", 
												nerrors+1, net->name, net2->name,
												d_str, x_str, y_str );
											DRError * dre = m_drelist->Add( nerrors, DRError::SEG_VIAHOLE, &str, 
												&net->name, &net2->name, id_seg1, id_via2, xf2, yf2, xf2, yf2, 0, s->layer );
											if( dre )
											{
												nerrors++;
												if( m_dlg_log )
													m_dlg_log->AddLine( str );
											}
										}
									}
								}
								//
								// test clearances between net2->segment and net->via
								//
								layer = s2->layer;
								if( post_vtx->via_w )
								{
									if( getbit( post_vtx->layer_bit, layer ) )
									{
										// via exists
										int test = m_nlist->GetViaConnectionStatus( net, ic, is+1, layer );
										int via_w = post_vtx->via_w;	// normal via pad
										if( layer > LAY_BOTTOM_COPPER && test == CNetList::VIA_NO_CONNECT )
										{
											// inner layer and no trace or thermal, so no via pad
											via_w = 0;
										}
										else if( layer > LAY_BOTTOM_COPPER && (test & CNetList::VIA_AREA) && !(test & CNetList::VIA_TRACE) )
										{
											// inner layer with small thermal, use annular ring
											via_w = post_vtx->via_hole_w + 2*m_dr.annular_ring_vias;
										}
										// check clearance
										if( via_w )
										{
											// check clearance between net2->segment and net->via_pad
											if( layer >= LAY_TOP_COPPER )
											{
												int d = GetClearanceBetweenSegmentAndPad( xi2, yi2, xf2, yf2, seg_w2,
													PAD_ROUND, post_vtx->x, post_vtx->y, post_vtx->via_w, 0, 0, 0 );
												TraceTrace = min( TraceTrace, d );
												if( d < m_dr.trace_trace )
												{
													// SEG_VIA
													::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
													::MakeCStringFromDimension( &x_str, post_vtx->x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
													::MakeCStringFromDimension( &y_str, post_vtx->y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
													str.Format( "%ld: \"%s\" via pad to \"%s\" trace = %s, x=%s, y=%s\r\n", 
														nerrors+1, net->name, net2->name,
														d_str, x_str, y_str );
													DRError * dre = m_drelist->Add( nerrors, DRError::SEG_VIA, &str, 
														&net2->name, &net->name, id_seg2, id_via1, xf, yf, xf, yf, 
														post_vtx->via_w+20*NM_PER_MIL, 0 );
													if( dre )
													{
														nerrors++;
														if( m_dlg_log )
															m_dlg_log->AddLine( str );
													}
												}
											}
										}
										//
										// check clearance between net2->segment and net->via_hole
										//
										if( layer >= LAY_TOP_COPPER )
										{
											int d = GetClearanceBetweenSegmentAndPad( xi2, yi2, xf2, yf2, seg_w2,
												PAD_ROUND, post_vtx->x, post_vtx->y, post_vtx->via_hole_w, 0, 0, 0 );
											HoleCopper = min( HoleCopper, d );
											if( d < m_dr.hole_copper )
											{
												// SEG_VIAHOLE
												::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &x_str, post_vtx->x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &y_str, post_vtx->y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												str.Format( "%ld: \"%s\" trace to \"%s\" via hole = %s, x=%s, y=%s\r\n", 
													nerrors+1, net2->name, net->name,
													d_str, x_str, y_str );
												DRError * dre = m_drelist->Add( nerrors, DRError::SEG_VIAHOLE, &str, 
													&net2->name, &net->name, id_seg2, id_via1, xf, yf, xf, yf, 
													post_vtx->via_w+20*NM_PER_MIL, 0 );
												if( dre )
												{
													nerrors++;
													if( m_dlg_log )
														m_dlg_log->AddLine( str );
												}
											}
										}
										//
										// test clearances between net->via and net2->via
										//
										if( post_vtx->via_w && post_vtx2->via_w )
										{	
											for( int layer=LAY_TOP_COPPER; layer<(LAY_TOP_COPPER+m_num_copper_layers); layer++ )
											{
												if( !getbit( post_vtx->layer_bit, layer ) )
													continue;
												if( !getbit( post_vtx2->layer_bit, layer ) )
													continue;
												// get size of net->via_pad
												int test = m_nlist->GetViaConnectionStatus( net, ic, is+1, layer );
												int via_w = post_vtx->via_w;	// normal via pad
												if( layer > LAY_BOTTOM_COPPER && test == CNetList::VIA_NO_CONNECT )
												{
													// inner layer and no trace or thermal, so no via pad
													via_w = 0;
												}
												else if( layer > LAY_BOTTOM_COPPER && (test & CNetList::VIA_AREA) && !(test & CNetList::VIA_TRACE) )
												{
													// inner layer with small thermal, use annular ring
													via_w = post_vtx->via_hole_w + 2*m_dr.annular_ring_vias;
												}
												// get size of net2->via_pad
												test = m_nlist->GetViaConnectionStatus( net2, ic2, is2+1, layer );
												int via_w2 = post_vtx2->via_w;	// normal via pad
												if( layer > LAY_BOTTOM_COPPER && test == CNetList::VIA_NO_CONNECT )
												{
													// inner layer and no trace or thermal, so no via pad
													via_w2 = 0;
												}
												else if( layer > LAY_BOTTOM_COPPER && (test & CNetList::VIA_AREA) && !(test & CNetList::VIA_TRACE) )
												{
													// inner layer with small thermal, use annular ring
													via_w2 = post_vtx2->via_hole_w + 2*m_dr.annular_ring_vias;
												}
												if( via_w && via_w2 )
												{
													//check net->via_pad to net2->via_pad clearance
													int d = GetClearanceBetweenPads( PAD_ROUND, post_vtx->x, post_vtx->y, post_vtx->via_w, 0, 0, 0, 
														PAD_ROUND, post_vtx2->x, post_vtx2->y, post_vtx2->via_w, 0, 0, 0 );
													TraceTrace = min( TraceTrace, d );
													if( d < m_dr.trace_trace )
													{
														// VIA_VIA
														::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
														::MakeCStringFromDimension( &x_str, post_vtx->x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
														::MakeCStringFromDimension( &y_str, post_vtx->y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
														str.Format( "%ld: \"%s\" via pad to \"%s\" via pad = %s, x=%s, y=%s\r\n", 
															nerrors+1, net->name, net2->name,
															d_str, x_str, y_str );
														DRError * dre = m_drelist->Add( nerrors, DRError::VIA_VIA, &str, 
															&net->name, &net2->name, id_via1, id_via2, xf, yf, xf2, yf2, 0, layer );
														if( dre )
														{
															nerrors++;
															if( m_dlg_log )
																m_dlg_log->AddLine( str );
														}
													}
													//
													// check net->via to net2->via_hole clearance
													//
													d = GetClearanceBetweenPads( PAD_ROUND, post_vtx->x, post_vtx->y, post_vtx->via_w, 0, 0, 0,
														PAD_ROUND, post_vtx2->x, post_vtx2->y, post_vtx2->via_hole_w, 0, 0, 0 );
													HoleCopper = min( HoleCopper, d );
													if( d < m_dr.hole_copper )
													{
														// VIA_VIAHOLE
														::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
														::MakeCStringFromDimension( &x_str, post_vtx->x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
														::MakeCStringFromDimension( &y_str, post_vtx->y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
														str.Format( "%ld: \"%s\" via pad to \"%s\" via hole = %s, x=%s, y=%s\r\n", 
															nerrors+1, net->name, net2->name,
															d_str, x_str, y_str );
														DRError * dre = m_drelist->Add( nerrors, DRError::VIA_VIAHOLE, &str, 
															&net->name, &net2->name, id_via1, id_via2, xf, yf, xf2, yf2, 0, layer );
														if( dre )
														{
															nerrors++;
															if( m_dlg_log )
																m_dlg_log->AddLine( str );
														}
													}
													//
													// check net2->via to net->via_hole clearance
													//
													d = GetClearanceBetweenPads( PAD_ROUND, post_vtx->x, post_vtx->y, post_vtx->via_hole_w, 0, 0, 0,
														PAD_ROUND, post_vtx2->x, post_vtx2->y, post_vtx2->via_w, 0, 0, 0 );
													HoleCopper = min( HoleCopper, d );
													if( d < m_dr.hole_copper )
													{
														// VIA_VIAHOLE
														::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
														::MakeCStringFromDimension( &x_str, post_vtx->x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
														::MakeCStringFromDimension( &y_str, post_vtx->y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
														str.Format( "%ld: \"%s\" via pad to \"%s\" via hole = %s, x=%s, y=%s\r\n", 
															nerrors+1, net2->name, net->name,
															d_str, x_str, y_str );
														DRError * dre = m_drelist->Add( nerrors, DRError::VIA_VIAHOLE, &str, 
															&net2->name, &net->name, id_via2, id_via1, xf, yf, xf2, yf2, 0, layer );
														if( dre )
														{
															nerrors++;
															if( m_dlg_log )
																m_dlg_log->AddLine( str );
														}
													}
												}
											}
											//
											// check net->via_hole to net2->via_hole clearance
											//
											int d = GetClearanceBetweenPads( PAD_ROUND, post_vtx->x, post_vtx->y, post_vtx->via_hole_w, 0, 0, 0,
												PAD_ROUND, post_vtx2->x, post_vtx2->y, post_vtx2->via_hole_w, 0, 0,0  );
											HoleHole = min( HoleHole, d );
											if( d < m_dr.hole_hole )
											{
												// VIA_VIAHOLE
												::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &x_str, post_vtx->x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &y_str, post_vtx->y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												str.Format( "%ld: \"%s\" via hole to \"%s\" via hole = %s, x=%s, y=%s\r\n", 
													nerrors+1, net2->name, net->name,
													d_str, x_str, y_str );
												DRError * dre = m_drelist->Add( nerrors, DRError::VIAHOLE_VIAHOLE, &str, 
													&net->name, &net2->name, id_via1, id_via2, xf, yf, xf2, yf2, 0, 0 );
												if( dre )
												{
													nerrors++;
													if( m_dlg_log )
														m_dlg_log->AddLine( str );
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			//
			// now iterate through all areas
			//
			for( int ia=0; ia<net->nareas; ia++ )
			{
				carea * a = &net->area[ia];
				RECT aRect;
				aRect = a->poly->GetBounds();
				int a_w = a->poly->GetW();

				// ignore 
				if( a->poly->GetHatch() == CPolyLine::NO_HATCH && a_w == 0 )
					continue;//  area Ghost

				// merge clearance
				int areaM = a->poly->GetMerge();
				int m_cl = 0;
				if( areaM >= 0 )
					m_cl = m_mlist->GetClearance( areaM );

				int	a_layer = a->poly->GetLayer();
				int a_n_corners = a->poly->GetNumCorners();
				id id_a (ID_NET, ID_AREA, ia, ID_SIDE, 0); 

				// test areas in same net
				for( int ia2=0; ia2<net->nareas; ia2++ )
				{
					if( ia2 == ia )
						continue;
					carea * a2 = &net->area[ia2];
					int	a2Layer = a2->poly->GetLayer();
					
					// test for same layer
					if( a2Layer == a_layer ) 
					{
						RECT a2Rect;
						a2Rect = a2->poly->GetBounds();
						int a2_w = a2->poly->GetW();
						// ignore 
						if( a2->poly->GetHatch() == CPolyLine::NO_HATCH && a2_w == 0 )
							continue;//  area Ghost
						// see if side bounding rects are too close
						if (a2Rect.left - aRect.right > m_dr.copper_copper+a_w+a2_w)
							continue;
						if (aRect.left - a2Rect.right > m_dr.copper_copper+a_w+a2_w)
							continue;
						if (a2Rect.bottom - aRect.top > m_dr.copper_copper+a_w+a2_w)
							continue;
						if (aRect.bottom - a2Rect.top > m_dr.copper_copper+a_w+a2_w)
							continue;
						int a2Ncor = a2->poly->GetNumCorners();
						
						// test for unpoured polygons inside cutouts of filled polygon
						if( a->poly->GetHatch() == CPolyLine::DIAGONAL_FULL &&
							a2->poly->GetHatch() != CPolyLine::DIAGONAL_FULL && 
							abs(a_w) <= _2540 )
						{
							for(int aco=a->poly->GetNumContours()-1; aco>0; aco--)
							{
								int x = a2->poly->GetX(0);
								int y = a2->poly->GetY(0);
								if( a->poly->TestPointInside( x, y, aco ))
								{
									id id_a = net->id;
									id_a.st = ID_AREA;
									id_a.i = ia2;
									id_a.sst = ID_CORNER;
									id_a.ii = 0;
									str.Format( "%ld: \"%s\" unpoured polygon inside cutout of filled area with zero width( net \"%s\" )\r\n",  
										nerrors+1, net->name, net->name );
									DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREA_INSIDE_COPPERAREA, &str,
										&net->name, &net->name, id_a, id_a, x, y, x, y, 0, 0 );
									if( dre )
									{
										nerrors++;
										if( m_dlg_log )
											m_dlg_log->AddLine( str );
									}
								}
							}
						}
						if( a->poly->GetHatch() != CPolyLine::DIAGONAL_FULL &&
							a2->poly->GetHatch() == CPolyLine::DIAGONAL_FULL &&
							abs(a2_w) <= _2540 )
						{
							for(int aco=a2->poly->GetNumContours()-1; aco>0; aco--)
							{
								int x = a->poly->GetX(0);
								int y = a->poly->GetY(0);
								if( a2->poly->TestPointInside( x, y, aco ))
								{
									id id_a = net->id;
									id_a.st = ID_AREA;
									id_a.i = ia;
									id_a.sst = ID_CORNER;
									id_a.ii = 0;
									str.Format( "%ld: \"%s\" unpoured polygon inside cutout of filled area with zero width( net \"%s\" )\r\n",  
										nerrors+1, net->name, net->name );
									DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREA_INSIDE_COPPERAREA, &str,
										&net->name, &net->name, id_a, id_a, x, y, x, y, 0, 0 );
									if( dre )
									{
										nerrors++;
										if( m_dlg_log )
											m_dlg_log->AddLine( str );
									}
								}
							}
						}
					}
				}

				// iterate through all nets again
				POSITION pos2 = pos;
				void * ptr2;
				CString name2;
				while( pos2 != NULL )
				{
					m_nlist->m_map.GetNextAssoc( pos2, name2, ptr2 );
					cnet * net2 = (cnet*)ptr2;
					//
					// iterate through all connects (test area hsFull)
					// 
					if ( a->poly->GetHatch() == CPolyLine::DIAGONAL_FULL )
					{
						for( int ic=0; ic<net2->nconnects; ic++ )
						{
							cconnect * c = &net2->connect[ic];
							// look for possible clearance violations between c and arct2
							if( c->min_x     - aRect.right > cl )
								continue;	// no, next area
							if( c->min_y     - aRect.top > cl )
								continue;	// no, next area
							if( aRect.left   - c->max_x > cl )
								continue;	// no, next area
							if( aRect.bottom - c->max_y > cl )
								continue;	// no, next area
							if (a->poly->GetHatch() != CPolyLine::DIAGONAL_FULL)
								continue;	// no, next area
							if (net->name.Compare(net2->name) == 0 )
						 		continue;	// no, next area
							// now test spacing for areas hs Full
							// now we have to test all segments and vias in c
							for( int iseg=0; iseg<c->nsegs; iseg++ )
							{
								// get next segment and via
								cseg * s = &c->seg[iseg];
								cvertex * pre_vtx = &c->vtx[iseg];
								cvertex * post_vtx = &c->vtx[iseg+1];
								int seg_w = s->width;
								int vw = post_vtx->via_w;
								int vh = post_vtx->via_hole_w;
								int status;
								if( vw )
									m_nlist->GetViaPadInfo( net2, ic, iseg+1, a_layer, &vw, &vh, &status );
								//
								int xs1 = pre_vtx->x;
								int ys1 = pre_vtx->y;
								int xs2 = post_vtx->x;
								int ys2 = post_vtx->y;
								// ids
								id id_seg( ID_NET, ID_CONNECT, ic, ID_SEG, iseg );
								id id_via( ID_NET, ID_CONNECT, ic, ID_VIA, iseg+1 );
								//
								// test via hole inside
								//
								if ( vh )
								{
									if ( a->poly->TestPointInside(xs2, ys2) )
									{
										if( m_dr.hole_copper > _2540 )
										{
											HoleCopper = 0;
											::MakeCStringFromDimension( &x_str, xs2, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &y_str, ys2, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											str.Format( "%ld: \"%s\" area hsFull to \"%s\" via hole = 0, x=%s, y=%s\r\n", 
												nerrors+1, net->name, net2->name,
												x_str, y_str );
											DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_VIA_INSIDE, &str, 
												&net->name, &net2->name, id_a, id_via, xs2, ys2, xs2, ys2, 
												vh+10*NM_PER_MIL, 0 );
											if( dre )
											{
												nerrors++;
												if( m_dlg_log )
													m_dlg_log->AddLine( str );
											}
										}
									}
								}
								for( int icor=0; icor<a_n_corners; icor++ )
								{
									int xc1 = a->poly->GetX(icor);
									int yc1 = a->poly->GetY(icor);
									int xc2 = a->poly->GetX(a->poly->GetIndexCornerNext(icor));
									int yc2 = a->poly->GetY(a->poly->GetIndexCornerNext(icor));
									int side_style = a->poly->GetSideStyle(icor);
									int x,y;
									id_a.ii = icor;
									//
									// test segment
									//
									if ( a_layer == s->layer )
									{
										// check clearance between net2->area side (hsFull) and net->segment
										int d = GetClearanceBetweenSegments( xc1, yc1, xc2, yc2, side_style, a_w,
											xs1, ys1, xs2, ys2, CPolyLine::STRAIGHT, seg_w, MAX_CL, &x, &y );
										AreaCopperHsFull = min( AreaCopperHsFull, d );
										if( d < (m_cl?m_cl:m_dr.copper_copper) )
										{
											::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											str.Format( "%ld: \"%s\" area hsFull to \"%s\" segment = %s, x=%s, y=%s\r\n", 
												nerrors+1, net->name, net2->name,
												d_str, x_str, y_str );
											DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_TRACE, &str, 
												&net->name, &net2->name, id_a, id_seg, x, y, x, y, 
												seg_w+10*NM_PER_MIL, 0 );
											if( dre )
											{
												nerrors++;
												if( m_dlg_log )
													m_dlg_log->AddLine( str );
											}
										}
									}
									//
									// test via
									//
									if ( vw )
									{
										// via exists
										int test = m_nlist->GetViaConnectionStatus( net2, ic, iseg+1, s->layer );
										int via_w = vw;	// normal via pad
										if( s->layer > LAY_BOTTOM_COPPER && test == CNetList::VIA_NO_CONNECT )
										{
											// inner layer and no trace or thermal, so no via pad
											via_w = 0;
										}
										else if( s->layer > LAY_BOTTOM_COPPER && (test & CNetList::VIA_AREA) && !(test & CNetList::VIA_TRACE) )
										{
											// inner layer with small thermal, use annular ring
											via_w = post_vtx->via_hole_w + 2*m_dr.annular_ring_vias;
										}
										// check clearance between net2->area side (hsFull) and net->via_pad
										int d = GetClearanceBetweenSegments( xc1, yc1, xc2, yc2, side_style, a_w,
											xs2, ys2, xs2, ys2, CPolyLine::STRAIGHT, via_w, MAX_CL, &x, &y );
										AreaCopperHsFull = min( AreaCopperHsFull, d );
										if( d < (m_cl?m_cl:m_dr.copper_copper) )
										{
											::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											str.Format( "%ld: \"%s\" area hsFull to \"%s\" via pad = %s, x=%s, y=%s\r\n", 
												nerrors+1, net->name, net2->name, d_str, x_str, y_str );
											DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_VIA, &str, 
												&net->name, &net2->name, id_a, id_via, xs2, ys2, xs2, ys2, 
												via_w+10*NM_PER_MIL, 0 );
											if( dre )
											{
												nerrors++;
												if( m_dlg_log )
													m_dlg_log->AddLine( str );
											}
										}
									}
									//
									// test via hole
									//
									if ( vh )
									{
										// check clearance between net2->area side (hsFull) and net->via_hole
										int d = GetClearanceBetweenSegments( xc1, yc1, xc2, yc2, side_style, a_w,
											xs2, ys2, xs2, ys2, CPolyLine::STRAIGHT, vh, MAX_CL, &x, &y );
										HoleCopper = min( HoleCopper, d );
										if( d < (m_cl?m_cl:m_dr.hole_copper) )
										{
											::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											str.Format( "%ld: \"%s\" area hsFull to \"%s\" via hole = %s, x=%s, y=%s\r\n", 
												nerrors+1, net->name, net2->name,
												d_str, x_str, y_str );
											DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_VIA, &str, 
												&net->name, &net2->name, id_a, id_via, xs2, ys2, xs2, ys2, 
												vh+10*NM_PER_MIL, 0 );
											if( dre )
											{
												nerrors++;
												if( m_dlg_log )
													m_dlg_log->AddLine( str );
											}
										}
									}
								}
							}
						}
					}
					//
					// 
					//
					for( int ia2=0; ia2<net2->nareas; ia2++ )
					{
						carea * a2 = &net2->area[ia2];
						RECT a2Rect;
						a2Rect = a2->poly->GetBounds();
						int	a2Layer = a2->poly->GetLayer();
						int a2Ncor = a2->poly->GetNumCorners();
						int a2_w = a2->poly->GetW();
						// ignore 
						if( a2->poly->GetHatch() == CPolyLine::NO_HATCH && a2_w == 0 )
							continue;//  area Ghost
						//
						// see if side bounding rects are too close
						if (a2Rect.left - aRect.right > m_dr.copper_copper+a_w+a2_w)
							continue;
						if (aRect.left - a2Rect.right > m_dr.copper_copper+a_w+a2_w)
							continue;
						if (a2Rect.bottom - aRect.top > m_dr.copper_copper+a_w+a2_w)
							continue;
						if (aRect.bottom - a2Rect.top > m_dr.copper_copper+a_w+a2_w)
							continue;
						// test for same layer
						if( a2Layer == a_layer ) 
						{
							// test for unpoured polygons inside cutouts of filled polygon
							if( a->poly->GetHatch() == CPolyLine::DIAGONAL_FULL &&
								a2->poly->GetHatch() != CPolyLine::DIAGONAL_FULL &&
								abs(a_w) <= _2540 )
							{
								for(int aco=a->poly->GetNumContours()-1; aco>0; aco--)
								{
									int x = a2->poly->GetX(0);
									int y = a2->poly->GetY(0);
									if( a->poly->TestPointInside( x, y, aco ))
									{
										id id_a = net2->id;
										id_a.st = ID_AREA;
										id_a.i = ia2;
										id_a.sst = ID_CORNER;
										id_a.ii = 0;
										str.Format( "%ld: \"%s\" unpoured polygon inside cutout of filled area with zero width( net \"%s\" )\r\n",  
											nerrors+1, net2->name, net->name );
										DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREA_INSIDE_COPPERAREA, &str,
											&net2->name, &net->name, id_a, id_a, x, y, x, y, 0, 0 );
										if( dre )
										{
											nerrors++;
											if( m_dlg_log )
												m_dlg_log->AddLine( str );
										}
									}
								}
							}
							if( a->poly->GetHatch() != CPolyLine::DIAGONAL_FULL &&
								a2->poly->GetHatch() == CPolyLine::DIAGONAL_FULL &&
								abs(a2_w) <= _2540 )
							{
								for(int aco=a2->poly->GetNumContours()-1; aco>0; aco--)
								{
									int x = a->poly->GetX(0);
									int y = a->poly->GetY(0);
									if( a2->poly->TestPointInside( x, y, aco ))
									{
										id id_a = net->id;
										id_a.st = ID_AREA;
										id_a.i = ia;
										id_a.sst = ID_CORNER;
										id_a.ii = 0;
										str.Format( "%ld: \"%s\" unpoured polygon inside cutout of filled area with zero width( net \"%s\" )\r\n",  
											nerrors+1, net->name, net2->name );
										DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREA_INSIDE_COPPERAREA, &str,
											&net->name, &net2->name, id_a, id_a, x, y, x, y, 0, 0 );
										if( dre )
										{
											nerrors++;
											if( m_dlg_log )
												m_dlg_log->AddLine( str );
										}
									}
								}
							}
							// test for points inside one another
							for( int ic=0; ic<a_n_corners; ic++ )
							{
								int x = a->poly->GetX(ic);
								int y = a->poly->GetY(ic);
								if( a2->poly->TestPointInside( x, y ) )
								{
									// COPPERAREA_COPPERAREA error
									int dis;
									dis = max(0,-a_w);
									AreaArea = min(AreaArea,dis);
									if (a->poly->GetHatch() == CPolyLine::DIAGONAL_FULL)
										AreaCopperHsFull = min(AreaCopperHsFull,dis);
									if ( dis < (m_cl?m_cl:m_dr.copper_copper) )
									{
										id id_a = net->id;
										id_a.st = ID_AREA;
										id_a.i = ia;
										id_a.sst = ID_CORNER;
										id_a.ii = ic;
										str.Format( "%ld: \"%s\" copper area inside \"%s\" inside copper area\r\n",  
											nerrors+1, net->name, net2->name );
										DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREA_INSIDE_COPPERAREA, &str,
											&net->name, &net2->name, id_a, id_a, x, y, x, y, 0, 0 );
										if( dre )
										{
											nerrors++;
											if( m_dlg_log )
												m_dlg_log->AddLine( str );
										}
									}
								}
							}
							for( int ic2=0; ic2<a2Ncor; ic2++ )
							{
								int x = a2->poly->GetX(ic2);
								int y = a2->poly->GetY(ic2);
								if( a->poly->TestPointInside( x, y ) )
								{
									// COPPERAREA_COPPERAREA error
									int dis;
									dis = max(0,-a2_w);
									AreaArea = min(AreaArea,dis);
									if (a->poly->GetHatch() == CPolyLine::DIAGONAL_FULL)
										AreaCopperHsFull = min(AreaCopperHsFull,dis);
									if ( dis < (m_cl?m_cl:m_dr.copper_copper) )
										{
										id id_a = net2->id;
										id_a.st = ID_AREA;
										id_a.i = ia2;
										id_a.sst = ID_CORNER;
										id_a.ii = ic2;
										str.Format( "%ld: \"%s\" copper area inside \"%s\" copper area\r\n",  
											nerrors+1, net2->name, net->name );
										DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREA_INSIDE_COPPERAREA, &str,
											&net2->name, &net->name, id_a, id_a, x, y, x, y, 0, 0 );
										if( dre )
										{
											nerrors++;
											if( m_dlg_log )
												m_dlg_log->AddLine( str );
										}
									}
								}
							}
							// now test spacing between areas
							for( int icont=0; icont<a->poly->GetNumContours(); icont++ )
							{
								int ic_start = a->poly->GetContourStart( icont );
								int ic_end = a->poly->GetContourEnd( icont );
								for( int ic=ic_start; ic<=ic_end; ic++ ) 
								{
									id id_a = net->id;
									id_a.st = ID_AREA;
									id_a.i = ia;
									id_a.sst = ID_SIDE;
									id_a.ii = ic;
									int ax1 = a->poly->GetX(ic);
									int ay1 = a->poly->GetY(ic);
									int ax2 = a->poly->GetX(a->poly->GetIndexCornerNext(ic));
									int ay2 = a->poly->GetY(a->poly->GetIndexCornerNext(ic));
									//
									int astyle = a->poly->GetSideStyle(ic);
									for( int icont2=0; icont2<a2->poly->GetNumContours(); icont2++ )
									{
										int ic_start2 = a2->poly->GetContourStart( icont2 );
										int ic_end2 = a2->poly->GetContourEnd( icont2 );
										for( int ic2=ic_start2; ic2<=ic_end2; ic2++ )
										{
											id id_b = net2->id;
											id_b.st = ID_AREA;
											id_b.i = ia2;
											id_b.sst = ID_SIDE;
											id_b.ii = ic2;
											int bx1 = a2->poly->GetX(ic2);
											int by1 = a2->poly->GetY(ic2);
											int bx2 = a2->poly->GetX(a2->poly->GetIndexCornerNext(ic2));
											int by2 = a2->poly->GetY(a2->poly->GetIndexCornerNext(ic2));
											//
											int bstyle = a2->poly->GetSideStyle(ic2);
											int x, y;
											int d = ::GetClearanceBetweenSegments( bx1, by1, bx2, by2, bstyle, a2_w,
												ax1, ay1, ax2, ay2, astyle, a_w, MAX_CL, &x, &y );
											if ( net->name.Compare( net2->name ) )
											{
												AreaArea = min( AreaArea, d );
												if (a->poly->GetHatch() == CPolyLine::DIAGONAL_FULL)
													AreaCopperHsFull = min( AreaCopperHsFull, d );
											}
											if( d < (m_cl?m_cl:m_dr.copper_copper) )
											{
												// COPPERAREA_COPPERAREA error
												::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &x_str, x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &y_str, y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												str.Format( "%ld: \"%s\" copper area to \"%s\" copper area = %s, x=%s, y=%s\r\n",  
													nerrors+1, net->name, net2->name, d_str, x_str, y_str );
												DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREA_COPPERAREA, &str,
													&net->name, &net2->name, id_a, id_b, x, y, x, y, 0, 0 );
												if( dre )
												{
													nerrors++;
													if( m_dlg_log )
														m_dlg_log->AddLine( str );
												}
											}
										}
									}
								}
							}
						}
					}
				}
				if (a->poly->GetHatch() == CPolyLine::DIAGONAL_FULL)
				{
					int nerrs = nerrors;
					for (int icont = 1; icont < a->poly->GetNumContours(); icont++)
					{
						int arx = a->poly->GetX(a->poly->GetContourStart(icont));
						int ary = a->poly->GetY(a->poly->GetContourStart(icont));
						for (int icont2 = 1; icont2 < a->poly->GetNumContours(); icont2++)
						{
							if (icont == icont2)
								continue;
							if (a->poly->TestPointInside(arx, ary, icont2))
							{
								::MakeCStringFromDimension(&x_str, arx, m_units, FALSE, TRUE, TRUE, (m_units == MIL ? 1 : 3));
								::MakeCStringFromDimension(&y_str, ary, m_units, FALSE, TRUE, TRUE, (m_units == MIL ? 1 : 3));
								str.Format("%ld: \"%s\" copper area error (cutout inside cutout), x=%s, y=%s\r\n",
									nerrors + 1, net->name, x_str, y_str);
								DRError* dre = m_drelist->Add(nerrors, DRError::COPPERAREA_TORN, &str,
									&net->name, &net->name, id_a, id_a, arx, ary, arx, ary, 0, a_layer);
								if (dre)
								{
									nerrors++;
									if (m_dlg_log)
										m_dlg_log->AddLine(str);
								}
							}
							if (nerrs != nerrors)
								break;
						}
						if (nerrs != nerrors)
							break;
					}
					for (cpart * prt = m_plist->GetFirstPart(); prt; prt = m_plist->GetNextPart(prt) )
					{
						if (prt->shape)
						{
							RECT rct;
							m_plist->GetPartBoundingRect(prt, &rct);
							if ( rct.left - aRect.right > m_dr.copper_copper+a_w )
								continue;
							if ( aRect.left - rct.right > m_dr.copper_copper+a_w )
								continue;
							if ( rct.bottom - aRect.top > m_dr.copper_copper+a_w )
								continue;
							if ( aRect.bottom - rct.top > m_dr.copper_copper+a_w )
								continue;
							int npins = prt->shape->GetNumPins();
							for (int ipin=0; ipin<npins; ipin++)
							{
								// get test pad info
								int xp, yp, wp, lp, rp, typep, holep, connectp, anglep;
								cnet * padnet;
								BOOL bPad = m_plist->GetPadDrawInfo( prt, ipin, a_layer, 0, 0, 0, 0,
								&typep, &xp, &yp, &wp, &lp, &rp, &holep, &anglep,
								&padnet, &connectp );
								if ( padnet )
									if ( net == padnet )
										continue;
								if( bPad )
								{
									id id_a, id_b;
									id_a.Set(ID_NET, ID_AREA, ia, 0, 0);
									id_b.Set(ID_PART, ID_PAD, ipin, 0, 0); 
									if (a->poly->TestPointInside(xp,yp))
									{
										// COPPERAREAFULL_COPPER error
										AreaCopperHsFull = 0;
										if( m_dr.copper_copper > _2540 )
										{
											::MakeCStringFromDimension( &x_str, xp, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &y_str, yp, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											str.Format( "%ld: \"%s\" copper area (hs full) to %s.%s pad = 0, x=%s, y=%s\r\n",  
												nerrors+1, net->name, prt->ref_des, prt->shape->m_padstack[ipin].name, x_str, y_str );	 
											DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_PAD, &str,
												&net->name, &prt->ref_des, id_a, id_b, xp, yp, xp, yp, 0, a_layer );	  
											if( dre )
											{
												nerrors++;
												if( m_dlg_log )
													m_dlg_log->AddLine( str );
											} 
										}
									}
									for (int c=0; c<a_n_corners; c++)
									{ 
										id_a.Set(ID_NET, ID_AREA, ia, ID_SIDE, c);
										int astyle = a->poly->GetSideStyle(c);
										int cnt;
										CPoint arcs[N_SIDES_APPROX_ARC+1];
										int xn = a->poly->GetX(a->poly->GetIndexCornerNext(c));
										int yn = a->poly->GetY(a->poly->GetIndexCornerNext(c));
										cnt = Generate_Arc(	a->poly->GetX(c),a->poly->GetY(c),xn,yn,astyle,arcs,N_SIDES_APPROX_ARC);
										BOOL brk = 0;
										for (int nc=0; nc<(cnt-1); nc++)
										{
											int d = ::GetClearanceBetweenSegmentAndPad(	arcs[nc].x, arcs[nc].y, arcs[nc+1].x, arcs[nc+1].y, a_w,
																						typep, xp, yp, wp,lp, rp, anglep);
											AreaCopperHsFull = min( AreaCopperHsFull, d );
											if( d < (m_cl?m_cl:m_dr.copper_copper) )
											{
												// COPPERAREAFULL_COPPER error
												::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &x_str, xp, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &y_str, yp, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												str.Format( "%ld: \"%s\" copper area (hs full) to %s.%s pad = %s, x=%s, y=%s\r\n",  
													nerrors+1, net->name, prt->ref_des, prt->shape->m_padstack[ipin].name, d_str, x_str, y_str );	 
												DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_PAD, &str,
													&net->name, &prt->ref_des, id_a, id_b, xp, yp, xp, yp, 0, a_layer );	  
												if( dre )
												{
													nerrors++;
													if( m_dlg_log )
														m_dlg_log->AddLine( str );
												} 
												brk = 1;
											}
											if (holep)
											{
												d = ::GetClearanceBetweenSegmentAndPad(	arcs[nc].x, arcs[nc].y, arcs[nc+1].x, arcs[nc+1].y, a_w,
																							PAD_ROUND, xp, yp, holep,holep, 0, 0);
												AreaCopperHsFull = min( AreaCopperHsFull, d );
												if( net != padnet )
													HoleCopper = min( HoleCopper, d );
												if( d < m_dr.hole_copper )
												{
													// COPPERAREAFULL_COPPER error
													::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
													::MakeCStringFromDimension( &x_str, xp, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
													::MakeCStringFromDimension( &y_str, yp, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
													str.Format( "%ld: \"%s\" copper area (hs full) to %s.%s hole = %s, x=%s, y=%s\r\n",  
														nerrors+1, net->name, prt->ref_des, prt->shape->m_padstack[ipin].name, d_str, x_str, y_str );	 
													DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_PAD, &str,
														&net->name, &prt->ref_des, id_a, id_b, xp, yp, xp, yp, 0, a_layer );	  
													if( dre )
													{
														nerrors++;
														if( m_dlg_log )
															m_dlg_log->AddLine( str );
													} 
													brk = 1;
												}
											}
											if( brk )
												break;
										}
										if( brk )
											break;
									}
								}
							}
						}
					}
				}
				else if( a->poly->GetNumContours() > 1 )
				{
					// CLEAR_THERMAL
					for (cpart * prt = m_plist->GetFirstPart(); prt; prt = m_plist->GetNextPart(prt) )
					{
						if (prt->shape)
						{
							RECT rct;
							m_plist->GetPartBoundingRect(prt, &rct);
							if ( rct.left - aRect.right > m_dr.copper_copper+a_w )
								continue;
							if ( aRect.left - rct.right > m_dr.copper_copper+a_w )
								continue;
							if ( rct.bottom - aRect.top > m_dr.copper_copper+a_w )
								continue;
							if ( aRect.bottom - rct.top > m_dr.copper_copper+a_w )
								continue;
							int npins = prt->shape->GetNumPins();
							for (int ipin=0; ipin<npins; ipin++)
							{
								// get test pad info
								int xp, yp, wp, lp, rp, typep, holep, connectp, anglep, ctype;
								cnet * padnet;
								BOOL bPad = m_plist->GetPadDrawInfo( prt, ipin, a_layer, 0, 0, 0, 0,
								&typep, &xp, &yp, &wp, &lp, &rp, &holep, &anglep,
								&padnet, &connectp, &ctype );
								if ( net != padnet )
									continue;
								BOOL bP = 0;
								if( ctype == PAD_CONNECT_THERMAL )
									bP = 1;
								if( (ctype & PAD_CONNECT_DEFAULT) && !holep && !(m_cam_flags & GERBER_NO_SMT_THERMALS) )
									bP = 1;
								if( (ctype == PAD_CONNECT_DEFAULT) && holep && !(m_cam_flags & GERBER_NO_PIN_THERMALS) )
									bP = 1;
								if( bPad && bP && (connectp & CPartList::AREA_CONNECT) )
								{
									id id_a, id_b;
									id_b.Set(ID_PART, ID_PAD, ipin, 0, 0);
									int cst=a_n_corners;
									cst = a->poly->GetContourStart(1);
									for (int c=cst; c<a_n_corners; c++)
									{ 
										id_a.Set(ID_NET, ID_AREA, ia, ID_SIDE, c);
										int cnt;
										CPoint arcs[N_SIDES_APPROX_ARC+1];
										int ax = a->poly->GetX(c);
										int ay = a->poly->GetY(c);
										if( Distance( ax,ay,xp,yp ) < min(wp,lp)/2 )
										{						
											// error
											::MakeCStringFromDimension( &x_str, xp, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											::MakeCStringFromDimension( &y_str, yp, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
											str.Format( "%ld: \"%s\" Copper area has an additional cutout in addition to the thermal barrier %s.%s, x=%s, y=%s\r\n",  
												nerrors+1, net->name, prt->ref_des, prt->shape->m_padstack[ipin].name, x_str, y_str );	 
											DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_PAD, &str,
												&net->name, &prt->ref_des, id_a, id_b, xp, yp, xp, yp, 0, a_layer );	  
											if( dre )
											{
												nerrors++;
												if( m_dlg_log )
													m_dlg_log->AddLine( str );
											} 
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	// now check for unrouted connections, if requested
	if( m_dr.bCheckUnrouted )
	{
		for( POSITION pos = m_nlist->m_map.GetStartPosition(); pos != NULL; )
		{
			CString name;
			void * ptr;
			m_nlist->m_map.GetNextAssoc( pos, name, ptr );
			cnet * net = (cnet*)ptr;
			// iterate through all connections
			// now check connections
			for( int ic=0; ic<net->connect.GetSize(); ic++ )
			{
				if( net->connect[ic].nsegs == 1 )
					if( net->connect[ic].end_pin_shape >= 0 && net->connect[ic].end_pin >= 0 )
					{
						cpart * sp = net->pin[net->connect[ic].start_pin].part;
						cpart * ep = net->pin[net->connect[ic].end_pin].part;
						CPoint SP = m_plist->GetPinPoint( sp, net->connect[ic].start_pin_shape, sp->side, sp->angle );
						CPoint EP = m_plist->GetPinPoint( ep, net->connect[ic].end_pin_shape, ep->side, ep->angle );
						if( SP.x == EP.x && SP.y == EP.y && 
							m_plist->GetPinLayer( sp, net->connect[ic].start_pin_shape ) == 
							m_plist->GetPinLayer( ep, net->connect[ic].end_pin_shape ) )
							continue;
					}
				// check for unrouted or partially routed connection
				for( int is=0; is<net->connect[ic].nsegs; is++ )
				{
					if( net->connect[ic].seg[is].layer == LAY_RAT_LINE )
					{
						// unrouted or partially routed connection
						CString start_pin;
						int istart = net->connect[ic].start_pin;
						cpart * start_part = net->pin[istart].part;
						start_pin = net->pin[istart].ref_des + "." + net->pin[istart].pin_name;
						CPoint pt;
						pt.x = net->connect[ic].vtx[is].x;
						pt.y = net->connect[ic].vtx[is].y;
						pt.x += net->connect[ic].vtx[is+1].x;
						pt.y += net->connect[ic].vtx[is+1].y;
						pt.x /= 2;
						pt.y /= 2;
						str.Format( "%ld: \"%s\": partially routed trace from %s\r\n",
							nerrors+1, net->name, start_pin );
						id id_a( ID_NET, ID_CONNECT, ic, ID_SEG, is );
						DRError * dre = m_drelist->Add( nerrors, DRError::UNROUTED, &str,
							&net->name, &net->name, id_a, id_a, pt.x, pt.y, pt.x, pt.y, 0, 0 );
						if( dre )
						{
							nerrors++;
							if( m_dlg_log )
								m_dlg_log->AddLine( str );
						}
						break;
					}
				}
			}
		}
	}
	// texts
	if( m_tlist )
	{
		if( m_dlg_log )
			m_dlg_log->AddLine( "\r\nChecking texts:\r\n" );
		int ipo = m_pcb_filename.ReverseFind('.');
		if( ipo > 0 )
		{
			int noName = 1;
			CString fs = m_pcb_filename.Left(ipo);
			int txt = 0;
			for( CText * it=m_tlist->GetFirstText(); it; it=m_tlist->GetNextText(&txt) )
			{
				int fsl = fs.GetLength();
				int strl = it->m_str.GetLength();
				int min_L = min(fsl,strl);
				if( min_L > 3 )
				{
					int FI = 0;
					CString T = it->m_str;
					for( int ic=1; ic<=min_L; ic++ )
					{
						if( fs.MakeLower().Left(ic) != T.MakeLower().Left(ic) )
						{
							FI = ic;
							break;
						}
					}
					if(FI == 0 && fsl == strl)
					{
						noName = 0;
						//break;! no break
					}
					else if( FI > min_L/2 || (FI == 0 && fsl != strl))	
					{
						noName = 0;
						CString str, x_s, y_s;
						::MakeCStringFromDimension( &x_s, it->m_x, m_units, TRUE, TRUE, TRUE, 3 );
						::MakeCStringFromDimension( &y_s, it->m_y, m_units, TRUE, TRUE, TRUE, 3 );
						str.Format( "is Warning: The text is similar to the PCB-file name, but slightly different from it.( %s   X=%s Y=%s )\r\n", it->m_str, x_s, y_s );
						if( m_dlg_log )
							m_dlg_log->AddLine( str );
					}
				}
			}
			POSITION pos;
			CString key;
			void * ptr;
			for( pos = m_footprint_cache_map.GetStartPosition(); pos != NULL; )
			{
				m_footprint_cache_map.GetNextAssoc( pos, key, ptr );
				CShape * shape = (CShape*)ptr;
				if( shape == NULL)
					continue;
				int it = -1;
				for( CText * tn=shape->m_tl->GetNextText(&it); tn; tn=shape->m_tl->GetNextText(&it) )
				{
					int fsl = fs.GetLength();
					int strl = tn->m_str.GetLength();
					int min_L = min(fsl,strl);
					if( min_L > 3 )
					{
						int FI = 0;
						CString T = tn->m_str;
						for( int ic=1; ic<=min_L; ic++ )
						{
							if( fs.MakeLower().Left(ic) != T.MakeLower().Left(ic) )
							{
								FI = ic;
								break;
							}
						}
						if(FI == 0 && fsl == strl)
						{
							noName = 0;
							//break;! no break
						}
						else if( FI > min_L/2 || (FI == 0 && fsl != strl))	
						{
							noName = 0;
							CString str, x_s, y_s;
							::MakeCStringFromDimension( &x_s, tn->m_x, m_units, TRUE, TRUE, TRUE, 3 );
							::MakeCStringFromDimension( &y_s, tn->m_y, m_units, TRUE, TRUE, TRUE, 3 );
							str.Format( "is Warning: The text is similar to the PCB-file name, but slightly different from it.( %s   X=%s Y=%s )\r\n", tn->m_str, x_s, y_s );
							if( m_dlg_log )
								m_dlg_log->AddLine( str );
						}
					}
				}
			}
			if( noName )
			{
				str.Format( "is Warning: The board name is missing or it does not match the project file name.\r\n");
				if( m_dlg_log )
					m_dlg_log->AddLine( str );
			}
		}
		int tx = 0;
		for( CText * it=m_tlist->GetFirstText(); it; it=m_tlist->GetNextText(&tx) )
		{
			if( it->m_layer == LAY_TOP_COPPER || it->m_layer == LAY_BOTTOM_COPPER )
			{
				id GID;
				int d=0, xx=0, yy=0, pad_wng=0;
				cpart * badP;
				CText * badT;
				it->net_Ptr = NULL;
				cnet * badN = NULL;
				cnet * tn = DrcTestforDlElement( it->dl_el, &GID, &d, &xx, &yy, &pad_wng, &badP, &badT, &badN );
				if( tn )
				{
					it->net_Ptr = tn;
					::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
					::MakeCStringFromDimension( &x_str, it->m_x, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
					::MakeCStringFromDimension( &y_str, it->m_y, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
					if( badN )
						str.Format( "%ld: text clearance on the net \"%s\" and \"%s\" is less than specified in the design rules, d <= %s, x = %s, y = %s\r\n", 
						nerrors+1, tn->name, badN->name, d_str, x_str, y_str );
					else
						str.Format( "%ld: text clearance on the net \"%s\" is less than specified in the design rules, d <= %s, x = %s, y = %s\r\n", 
						nerrors+1, tn->name, d_str, x_str, y_str );
					id id_t(ID_TEXT_DEF);
					id_t.i = it->m_x;
					id_t.ii = it->m_y;
					DRError * dre=NULL;
					if( GID.type == ID_NET )
					{
						dre = m_drelist->Add( nerrors, DRError::SEG_OP, &str, 
											&tn->name, &it->m_str, 
											GID, id_t, xx, yy, xx, yy, 0, LAY_DRC_ERROR );
						//
						if( GID.st == ID_AREA )
							AreaCopperHsFull = min( AreaCopperHsFull, d );
						else if( GID.st == ID_CONNECT )
							TraceTrace = min( TraceTrace, d );
					}
					else if( GID.type == ID_PART )
					{
						dre = m_drelist->Add( nerrors, DRError::SEG_OP, &str, 
											&badP->ref_des, &it->m_str, 
											GID, id_t, xx, yy, xx, yy, 0, LAY_DRC_ERROR );
						if( GID.sst == ID_HOLE )
							HoleCopper = min( HoleCopper, d );
						else 
							PadTrace = min( PadTrace, d );
					}	
					else if( GID.type == ID_TEXT )
					{
						dre = m_drelist->Add( nerrors, DRError::SEG_OP, &str, 
											&badT->m_str, &it->m_str, 
											GID, id_t, xx, yy, xx, yy, 0, LAY_DRC_ERROR );
						PadTrace = min( PadTrace, d );
					}	
					else
						dre = m_drelist->Add( nerrors, DRError::SEG_OP, &str, 
											&it->m_str, &it->m_str,
											id_t, id_t, it->m_x, it->m_y, it->m_x, it->m_y, 0, LAY_DRC_ERROR );
					if( dre )
					{
						nerrors++;
						if( m_dlg_log )
							m_dlg_log->AddLine( str );
					}
				}
			}
			if( it->m_mirror == 0 )
			{
				if( it->m_layer == LAY_BOTTOM_COPPER ||
					it->m_layer == LAY_SILK_BOTTOM ||
					it->m_layer == LAY_REFINE_BOT )
				{
					CString x_s, y_s;
					::MakeCStringFromDimension( &x_s, it->m_x, m_units, TRUE, TRUE, TRUE, 3 );
					::MakeCStringFromDimension( &y_s, it->m_y, m_units, TRUE, TRUE, TRUE, 3 );
					str.Format( "is Warning: The text has a mirror image.( %s   X=%s Y=%s )\r\n", it->m_str, x_s, y_s );
					if( m_dlg_log )
						m_dlg_log->AddLine( str );
				}
			}
			if( it->m_mirror == 1 )
			{
				if( it->m_layer == LAY_TOP_COPPER ||
					it->m_layer == LAY_SILK_TOP ||
					it->m_layer == LAY_REFINE_TOP )
				{
					CString x_s, y_s;
					::MakeCStringFromDimension( &x_s, it->m_x, m_units, TRUE, TRUE, TRUE, 3 );
					::MakeCStringFromDimension( &y_s, it->m_y, m_units, TRUE, TRUE, TRUE, 3 );
					str.Format( "is Warning: The text has a mirror image.( %s   X=%s Y=%s )\r\n", it->m_str, x_s, y_s );
					if( m_dlg_log )
						m_dlg_log->AddLine( str );
				}
			}
		}
	}
	str.Format( "\r\nChecking silkscreen on pads:\r\n" );
	if( m_dlg_log )
		m_dlg_log->AddLine( str );
	for( dl_element * el1=m_dlist->Get_Start()->next; el1->next; el1=el1->next )
	{
		if( el1->visible == 0 )
			continue;
		if( getbit( el1->layers_bitmap, LAY_SILK_TOP ) == 0 &&
			getbit( el1->layers_bitmap, LAY_SILK_BOTTOM ) == 0 &&
			getbit( el1->layers_bitmap, LAY_SM_TOP ) == 0 &&
			getbit( el1->layers_bitmap, LAY_SM_BOTTOM ) == 0 )
			continue;
		for( dl_element * el2=el1->next; el2->next; el2=el2->next )
		{
			if( el1 == el2 )
				continue;
			if( el2->visible == 0 )
				continue;
			BOOL el_silk_top = (getbit( el1->layers_bitmap, LAY_SILK_TOP ) && 
								getbit( el2->layers_bitmap, LAY_SILK_TOP ) &&
								(el1->gtype == DL_LINES_ARRAY || el2->gtype == DL_LINES_ARRAY) );

			BOOL el_silk_bot = (getbit( el1->layers_bitmap, LAY_SILK_BOTTOM ) && 
								getbit( el2->layers_bitmap, LAY_SILK_BOTTOM ) &&
								(el1->gtype == DL_LINES_ARRAY || el2->gtype == DL_LINES_ARRAY) );
			if( el1->id.sst == ID_HATCH || el2->id.sst == ID_HATCH )
			{
				el_silk_top = 0;
				el_silk_bot = 0;
			}
			if((getbit( el2->layers_bitmap, LAY_SM_TOP ) && getbit( el1->layers_bitmap, LAY_SILK_TOP )) ||
			   (getbit( el2->layers_bitmap, LAY_SILK_TOP ) && getbit( el1->layers_bitmap, LAY_SM_TOP )) ||
			   (getbit( el2->layers_bitmap, LAY_SILK_BOTTOM ) && getbit( el1->layers_bitmap, LAY_SM_BOTTOM )) ||
			   (getbit( el2->layers_bitmap, LAY_SM_BOTTOM ) && getbit( el1->layers_bitmap, LAY_SILK_BOTTOM )) ||
				el_silk_top || el_silk_bot )
			{
				if( m_dlist->Intersection( el1, el2 ) )
				{
					RECT r1, r2;
					m_dlist->Get_Rect( el1, &r1 );
					m_dlist->Get_Rect( el2, &r2 );
					CString str1="", str2="";
					//-----------------------------
					if( el1->id.type == ID_PART || el1->id.type == ID_PART_LINES )
					{
						if( cpart * part = (cpart*)el1->ptr )
							str1 = part->ref_des;
					}
					else if( el1->id.type == ID_TEXT )
					{
						if( CText * txt = (CText*)el1->ptr )
							str1 = txt->m_str;
					}
					//-----------------------------
					if( el2->id.type == ID_PART || el2->id.type == ID_PART_LINES )
					{
						if( cpart * part = (cpart*)el2->ptr )
							str2 = part->ref_des;
					}
					else if( el2->id.type == ID_TEXT )
					{
						if( CText * txt = (CText*)el2->ptr )
							str1 = txt->m_str;
					}
					//-----------------------------
					int layer = (getbit( el2->layers_bitmap, LAY_SM_TOP ) &&
								 getbit( el1->layers_bitmap, LAY_SILK_TOP ) )?LAY_SM_TOP:LAY_SM_BOTTOM;
					if( el_silk_top || el_silk_bot)
						str.Format( "%ld: Silkscreen intersects with text", nerrors+1 );
					else
						str.Format( "%ld: Silkscreen intersects with mask", nerrors+1 );
					DRError * dre = m_drelist->Add( nerrors, DRError::SEG_SEG, &str,
						&str1, &str2, el1->id, el2->id, (r1.left+r1.right)/2, (r1.top+r1.bottom)/2,
						(r2.left+r2.right)/2, (r2.top+r2.bottom)/2, 0, layer );
					if( dre )
					{
						nerrors++;
						if( m_dlg_log )
							m_dlg_log->AddLine( str+"\r\n" );
						if( nerrors > MAXERRORS )
						{
							goto cancel_verification;
						}
					}
				}
			}
		}
	}
	str.Format( "\r\nChecking copper lines:\r\n" );
	if( m_dlg_log )
		m_dlg_log->AddLine( str );
	
	for( cpart * part = m_plist->GetFirstPart(); part; part = m_plist->GetNextPart( part ) )
	{
		CShape * s = part->shape;
		if( nerrors > MAXERRORS )
		{
			goto cancel_verification;
		}
		//for this part we are looking for all intersections with 1) connections, 2) polygons, 3) pads 
		//and assign lines to the net, and also put a mark utility on the part
		part->utility = 0;
		if( s && part->drawn )
		{
			int gsz = part->m_outline_stroke.GetSize();
			part->NetPtr.SetSize(gsz);
			for( int io=0; io<gsz; io++ )
			{
				int s_w = part->m_outline_stroke[io]->dlist->Get_el_w(part->m_outline_stroke[io]);
				int s_layer = part->m_outline_stroke[io]->layers_bitmap;
				int lay_top_copper = 0;
				setbit(lay_top_copper, LAY_TOP_COPPER);
				int lay_bottom_copper = 0;
				setbit(lay_bottom_copper, LAY_BOTTOM_COPPER);
				if (s_w < (NM_PER_MIL / 10) && (s_layer == lay_top_copper || s_layer == lay_bottom_copper))
					continue;
				id GID;
				int d=0, xx=0, yy=0, pad_wng=0;
				cpart * badP = part;
				cnet *  badN = NULL;
				CText * badT = NULL;
				part->NetPtr[io] = DrcTestforDlElement( part->m_outline_stroke[io], &GID, &d, &xx, &yy, &pad_wng, &badP, &badT, &badN );
				if( part->NetPtr[io] )
					part->utility = 1;
				if(pad_wng)
				{
					// WARNING
					str.Format( "is Warning: The polyline connects unconnected pin to net \"%s\".\r\n", part->NetPtr[io]->name );
					if( m_dlg_log )
						m_dlg_log->AddLine( str );
				}
				if( GID.type != ID_NONE )
				{
					::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
					::MakeCStringFromDimension( &x_str, xx, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
					::MakeCStringFromDimension( &y_str, yy, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
					str.Format( "%ld: the polyline connects two different nets. d = %s, x = %s, y = %s\r\n", 
						nerrors+1, d_str, x_str, y_str );
					id id_op(ID_PART, ID_OUTLINE, io, ID_SIDE, io);
					DRError * dre=NULL;
					if( GID.type == ID_NET )
					{
						dre = m_drelist->Add( nerrors, DRError::SEG_OP, &str, 
											&part->NetPtr[io]->name, &part->ref_des, 
											GID, id_op, xx, yy, xx, yy, 0, LAY_DRC_ERROR );
						//
						if( GID.st == ID_AREA )
							AreaCopperHsFull = min( AreaCopperHsFull, d );
						else if( GID.st == ID_CONNECT )
							TraceTrace = min( TraceTrace, d );
					}
					else if( GID.type == ID_PART )
					{
						dre = m_drelist->Add( nerrors, DRError::SEG_OP, &str, 
											&badP->ref_des, &part->ref_des, 
											GID, id_op, xx, yy, xx, yy, 0, LAY_DRC_ERROR );
						if( GID.sst == ID_HOLE )
							HoleCopper = min( HoleCopper, d );
						else 
							PadTrace = min( PadTrace, d );
					}	
					else if( GID.type == ID_TEXT )
					{
						dre = m_drelist->Add( nerrors, DRError::SEG_OP, &str, 
											&badT->m_str, &part->ref_des, 
											GID, id_op, xx, yy, xx, yy, 0, LAY_DRC_ERROR );
						PadTrace = min( PadTrace, d );
					}	
					else
						ASSERT(0);
					if( dre )
					{
						nerrors++;
						if( m_dlg_log )
							m_dlg_log->AddLine( str );
					}
				}
			}
		}
	}
	{
		BOOL bPOLYLINE_WAS_FOUND;
		do{
			bPOLYLINE_WAS_FOUND = 0;
			for( cpart * part = m_plist->GetFirstPart(); part; part = m_plist->GetNextPart( part ) )
			{
				if( part->utility )
				{
					for( int io=0; io<part->m_outline_stroke.GetSize(); io++ )
					{
						if( part->NetPtr[io] )
						{
							int LTop = getbit( part->m_outline_stroke[io]->layers_bitmap, LAY_TOP_COPPER );
							int LBot = getbit( part->m_outline_stroke[io]->layers_bitmap, LAY_BOTTOM_COPPER );
							if( LTop || LBot )
							{
								RECT RCT;
								m_dlist->Get_Rect( part->m_outline_stroke[io], &RCT );
								SwellRect( &RCT, m_dr.trace_trace );
								for( cpart * Gpart = m_plist->GetFirstPart(); Gpart; Gpart = m_plist->GetNextPart( Gpart ) )
								{
									if( Gpart->min_x - part->max_x > m_dr.trace_trace )
										continue;
									if( part->min_x - Gpart->max_x > m_dr.trace_trace )
										continue;
									if( Gpart->min_y - part->max_y > m_dr.trace_trace )
										continue;
									if( part->min_y - Gpart->max_y > m_dr.trace_trace )
										continue;
									//
									CArray <CPoint> * dl_els = m_dlist->Get_Points( part->m_outline_stroke[io], NULL, 0 );
									int np = dl_els->GetSize();
									if( np )
									{
										int Lw = m_dlist->Get_el_w( part->m_outline_stroke[io] );
										CPoint * P = new CPoint[np];//ok
										m_dlist->Get_Points( part->m_outline_stroke[io], P, &np );
										for(int ipt=0; (ipt+1)<np; ipt++ )
										{
											int Lx1 = P[ipt].x;
											int Ly1 = P[ipt].y;
											int Lx2 = P[ipt+1].x;
											int Ly2 = P[ipt+1].y;
											if( part->m_outline_stroke[io]->gtype == DL_LINES_ARRAY )
												ipt++;
											RECT LR = rect( Lx1, Ly1, Lx2, Ly2 );
											SwellRect( &LR, (Lw/2)+m_dr.trace_trace );
											CShape * Gs = Gpart->shape;
											if( Gs && Gpart->drawn )
											{
												for( int io2=0; io2<Gpart->m_outline_stroke.GetSize(); io2++ )
												{
													RECT RCT2;
													m_dlist->Get_Rect( Gpart->m_outline_stroke[io2], &RCT2 );
													if(RectsIntersection( RCT, RCT2 ) >= 0 )
													{
														if( part->NetPtr[io] != Gpart->NetPtr[io2] )
														{
															if( part->m_outline_stroke[io]->layers_bitmap == Gpart->m_outline_stroke[io2]->layers_bitmap )
															{
																dl_els = m_dlist->Get_Points( Gpart->m_outline_stroke[io2], NULL, 0 );
																int np2 = dl_els->GetSize();
																if( np2 )
																{
																	int Aw = m_dlist->Get_el_w( Gpart->m_outline_stroke[io2] );
																	CPoint * P2 = new CPoint[np2];//ok
																	m_dlist->Get_Points( Gpart->m_outline_stroke[io2], P2, &np2 );
																	for(int ipt2=0; (ipt2+1)<np2; ipt2++ )
																	{
																		int Ax1 = P2[ipt2].x;
																		int Ay1 = P2[ipt2].y;
																		int Ax2 = P2[ipt2+1].x;
																		int Ay2 = P2[ipt2+1].y;
																		if( Gpart->m_outline_stroke[io2]->gtype == DL_LINES_ARRAY )
																			ipt2++;
																		RECT AR = rect( Ax1, Ay1, Ax2, Ay2 );
																		SwellRect( &AR, Aw/2 );
																		int xx, yy;
																		if( RectsIntersection( AR, LR ) >= 0 )
																		{
																			int d = ::GetClearanceBetweenSegments( Lx1, Ly1, Lx2, Ly2, CPolyLine::STRAIGHT, Lw, 
																				Ax1, Ay1, Ax2, Ay2, CPolyLine::STRAIGHT, Aw, m_dr.trace_trace, &xx, &yy );
																			if( d < m_dr.trace_trace )
																			{
																				if( Gpart->NetPtr[io2] && Gpart->NetPtr[io2] != part->NetPtr[io] )
																				{
																					if( !getbit(part->m_outline_stroke[io]->layers_bitmap,LAY_HILITE) ||
																						!getbit(Gpart->m_outline_stroke[io2]->layers_bitmap,LAY_HILITE))
																					{
																						m_dlist->HighLight( part->m_outline_stroke[io] );
																						m_dlist->HighLight( Gpart->m_outline_stroke[io2] );
																						TraceTrace = min( TraceTrace, d );
																						// OP_OP
																						::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
																						::MakeCStringFromDimension( &x_str, xx, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
																						::MakeCStringFromDimension( &y_str, yy, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
																						str.Format( "%ld: \"%s\" polyline side to \"%s\" polyline side = %s, x=%s, y=%s\r\n", 
																									nerrors+1, part->NetPtr[io]->name,
																									Gpart->NetPtr[io2]->name,
																									d_str, x_str, y_str );
																						id id1(ID_PART, ID_OUTLINE, io, ID_SIDE, io);
																						id id2(ID_PART, ID_OUTLINE, io2, ID_SIDE, io2);
																						int l;
																						if( LTop )
																							l = LAY_TOP_COPPER;
																						else
																							l = LAY_BOTTOM_COPPER;
																						DRError * dre = m_drelist->Add( nerrors, DRError::COPPERAREAFULL_OP, &str, 
																							&part->ref_des, &Gpart->ref_des, id1, id2, xx, yy, xx, yy, 0, l );
																						if( dre )
																						{
																							nerrors++;
																							if( m_dlg_log )
																								m_dlg_log->AddLine( str );
																						}
																					}
																				}
																				else
																				{
																					Gpart->NetPtr[io2] = part->NetPtr[io];
																					Gpart->utility = TRUE;
																					bPOLYLINE_WAS_FOUND = TRUE;
																				}
																				break;
																			}
																		}
																	}
																	delete P2;
																}
															}
														}
													}
												}
											}
										}
										delete P;
									}
								}
							}
						}
					}
				}
			}
		}while( bPOLYLINE_WAS_FOUND );
	}
	//
	if( m_dr.board_edge_copper )
		for(int ib=0; ib<m_outline_poly.GetSize(); ib++)
		{
			if( m_outline_poly[ib].GetLayer() != LAY_BOARD_OUTLINE )
				continue;
			int Bw = m_outline_poly[ib].GetW();
			RECT RCT_B = m_outline_poly[ib].GetBounds();
			if( nerrors > MAXERRORS )
			{
				goto cancel_verification;
			}
			for(int ibs=0; ibs<m_outline_poly[ib].GetNumCorners(); ibs++)
			{
				for( cpart * part = m_plist->GetFirstPart(); part; part = m_plist->GetNextPart( part ) )
				{
					if( part->utility )
					{
						for( int io=0; io<part->m_outline_stroke.GetSize(); io++ )
						{
							if( part->NetPtr[io] )
							{
								RECT RCT;
								m_dlist->Get_Rect( part->m_outline_stroke[io], &RCT );
								SwellRect( &RCT, m_dr.trace_trace );
								if( RectsIntersection(RCT_B,RCT) >= 0 )
								{
									CArray <CPoint> * dl_els = m_dlist->Get_Points( part->m_outline_stroke[io], NULL, 0 );
									int np = dl_els->GetSize();
									if( np )
									{
										int Bx1 = m_outline_poly[ib].GetX(ibs);
										int By1 = m_outline_poly[ib].GetY(ibs);
										int inext = m_outline_poly[ib].GetIndexCornerNext(ibs);
										int Bx2 = m_outline_poly[ib].GetX(inext);
										int By2 = m_outline_poly[ib].GetY(inext);
										int sst = m_outline_poly[ib].GetSideStyle(ibs);
										int Lw = m_dlist->Get_el_w( part->m_outline_stroke[io] );
										CPoint * P = new CPoint[np];//ok
										m_dlist->Get_Points( part->m_outline_stroke[io], P, &np );
										for(int ipt=0; (ipt+1)<np; ipt++ )
										{
											int Lx1 = P[ipt].x;
											int Ly1 = P[ipt].y;
											int Lx2 = P[ipt+1].x;
											int Ly2 = P[ipt+1].y;
											if( part->m_outline_stroke[io]->gtype == DL_LINES_ARRAY )
												ipt++;
											int errx, erry;
											int d = ::GetClearanceBetweenSegments( Lx1, Ly1, Lx2, Ly2, CPolyLine::STRAIGHT, Lw,
												Bx1, By1, Bx2, By2, sst, 0, MAX_CL, &errx, &erry );
											BoardHole = min( BoardHole, d );
											if( d < m_dr.board_edge_copper )
											{
												// BOARDEDGE_OP error
												::MakeCStringFromDimension( &d_str, d, m_units, TRUE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &x_str, errx, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												::MakeCStringFromDimension( &y_str, erry, m_units, FALSE, TRUE, TRUE, (m_units==MIL?1:3) );
												str.Format( "%ld: \"%s\" polyline to board edge = %s, x=%s, y=%s\r\n",  
													nerrors+1, part->NetPtr[io]->name, d_str, x_str, y_str );
												id id1( ID_PART, ID_OUTLINE, io, ID_SIDE, io);
												id id2( ID_POLYLINE, ID_BOARD, ib, ID_SIDE, ibs );
												DRError * dre = m_drelist->Add( nerrors, DRError::BOARDEDGE_TRACE, &str,
													&part->ref_des, NULL, id1, id2, errx, erry, 0, 0, Lw+20*NM_PER_MIL, 0 );
												if( dre )
												{
													nerrors++;
													if( m_dlg_log )
														m_dlg_log->AddLine( str );
												}
												break;
											}
										}
										delete P;
									}
								}
							}
						}
					}
				}
			}
		}
	if( TooCloseToViaHole.GetLength() )
	{
		str = "\r\nis Warning - pin to via hole is too close:";
		str += TooCloseToViaHole;	
		if( m_dlg_log )
			m_dlg_log->AddLine( str );
	}
	if( TooCloseToPadHole.GetLength() )
	{
		str = "\r\nis Warning - pin to pad hole is too close:";
		str += TooCloseToPadHole;
		if( m_dlg_log )
			m_dlg_log->AddLine( str );
	}
	if( TooCloseToHole.GetLength() )
	{
		str = "\r\nis Warning - pin to hole is too close:";
		str += TooCloseToHole;	
		if( m_dlg_log )
			m_dlg_log->AddLine( str );
	}
	if( TooCloseToPad.GetLength() )
	{
		str = "\r\nis Warning - pin to pad is too close:";
		str += TooCloseToPad;
		if( m_dlg_log )
			m_dlg_log->AddLine( str );
	}
	str = "\r\n\r\nResult:\r\n";
	if( m_dlg_log )
		m_dlg_log->AddLine( str );
	{
		int dis = 3000;
		CString maxStr;
		::MakeCStringFromDimension( &maxStr, MAX_CL, m_units, TRUE, TRUE, TRUE, 3 );
		if ( TraceW < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, TraceW, m_units, TRUE, TRUE, TRUE, 3 );
			str.Format( "Minimum traces width: %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( PadPadTooClose < DEFAULT )
		{
			::MakeCStringFromDimension( &d_str, PadPadTooClose, m_units, TRUE, TRUE, TRUE, 3 );
			str.Format( "Minimum distance pad to pad (same net): %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( PadPad < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, PadPad, m_units, TRUE, TRUE, TRUE, 3 );
			if( PadPad > MAX_CL-m_pcbu_per_wu )
				str.Format( "Minimum distance pad to pad (different net): >%s\r\n", maxStr );
			else
				str.Format( "Minimum distance pad to pad (different net): %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( PadPadF < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, PadPadF, m_units, TRUE, TRUE, TRUE, 3 );
			if( PadPadF > MAX_CL-m_pcbu_per_wu )
				str.Format( "Minimum distance pad to pad (in footprints): >%s\r\n", maxStr );
			else
				str.Format( "Minimum distance pad to pad (in footprints): %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( PadTrace < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, PadTrace, m_units, TRUE, TRUE, TRUE, 3 );
			if( PadTrace > MAX_CL-m_pcbu_per_wu )	
				str.Format( "Minimum distance pad to Trace: >%s\r\n", maxStr );
			else
				str.Format( "Minimum distance pad to Trace: %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( TraceTrace < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, TraceTrace, m_units, TRUE, TRUE, TRUE, 3 );
			if( TraceTrace > MAX_CL-m_pcbu_per_wu )
				str.Format( "Minimum distance Trace to Trace: >%s\r\n", maxStr );
			else
				str.Format( "Minimum distance Trace to Trace: %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( HoleCopperTooClose < DEFAULT )
		{
			::MakeCStringFromDimension( &d_str, HoleCopperTooClose, m_units, TRUE, TRUE, TRUE, 3 );
			str.Format( "Minimum distance Hole to Copper (same net): %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( HoleCopper < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, HoleCopper, m_units, TRUE, TRUE, TRUE, 3 );
			if( HoleCopper > MAX_CL-m_pcbu_per_wu )
				str.Format( "Minimum distance Hole to Copper (different net): >%s\r\n", maxStr );
			else
				str.Format( "Minimum distance Hole to Copper (different net): %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( HoleCopperF < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, HoleCopperF, m_units, TRUE, TRUE, TRUE, 3 );
			if( HoleCopperF > MAX_CL-m_pcbu_per_wu )
				str.Format( "Minimum distance Hole to Copper (in footprints): >%s\r\n", maxStr );
			else
				str.Format( "Minimum distance Hole to Copper (in footprints): %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( ViaHoleToPadSameNet < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, ViaHoleToPadSameNet, m_units, TRUE, TRUE, TRUE, 3 );
			if( ViaHoleToPadSameNet > MAX_CL-m_pcbu_per_wu )
				str.Format( "Minimum distance Via Hole to Pad (same net): >%s\r\n", maxStr );
			else
				str.Format( "Minimum distance Via Hole to Pad (same net): %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( HoleHoleTooClose < DEFAULT )
		{
			::MakeCStringFromDimension( &d_str, HoleHoleTooClose, m_units, TRUE, TRUE, TRUE, 3 );
			str.Format( "Minimum distance Hole to Hole (same net): %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( HoleHole < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, HoleHole, m_units, TRUE, TRUE, TRUE, 3 );
			if( HoleHole > MAX_CL-m_pcbu_per_wu )
				str.Format( "Minimum distance Hole to Hole (different net): >%s\r\n", maxStr );
			else
				str.Format( "Minimum distance Hole to Hole (different net): %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( HoleHoleF < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, HoleHoleF, m_units, TRUE, TRUE, TRUE, 3 );
			if( HoleHoleF > MAX_CL-m_pcbu_per_wu )
				str.Format( "Minimum distance Hole to Hole (in footprints): >%s\r\n", maxStr );
			else
				str.Format( "Minimum distance Hole to Hole (in footprints): %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( BoardCopper < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, BoardCopper, m_units, TRUE, TRUE, TRUE, 3 );
			if( BoardCopper > MAX_CL-m_pcbu_per_wu )
				str.Format( "Minimum distance Board to Copper: >%s\r\n", maxStr );
			else
				str.Format( "Minimum distance Board to Copper: %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( BoardHole < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, BoardHole, m_units, TRUE, TRUE, TRUE, 3 );
			if( BoardHole > MAX_CL-m_pcbu_per_wu )
				str.Format( "Minimum distance Board to Hole: >%s\r\n", maxStr );
			else
				str.Format( "Minimum distance Board to Hole: %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if (AreaArea < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, AreaArea, m_units, TRUE, TRUE, TRUE, 3 );
			if( AreaArea > MAX_CL-m_pcbu_per_wu )
				str.Format( "Minimum distance copper area to copper area (G36): >%s\r\n", maxStr );
			else
				str.Format( "Minimum distance copper area to copper area (G36): %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if ( AreaCopperHsFull < DEFAULT)
		{
			::MakeCStringFromDimension( &d_str, AreaCopperHsFull, m_units, TRUE, TRUE, TRUE, 3 );
			str.Format( "Minimum distance copper area (hs Full) to copper: %s\r\n", d_str );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
		if( ArHoles.GetSize() )
		{
			str.Format( "Number of different hole diameters: %d\r\nUse InfoBox (Ctrl+F) to see them on the PCB\r\n(in the settings menu, you must enable the vias)\r\n", ArHoles.GetSize() );
			if( m_dlg_log )
				m_dlg_log->AddLine( str );
		}
	}

cancel_verification:
	CString noN = "__UNCONNECTED__";
	cnet * virtual_net_unc = m_nlist->GetNetPtrByName( &noN );
	if( virtual_net_unc )
		m_nlist->RemoveNet( virtual_net_unc );
	CancelBoardHoles();
	m_project_validated = 1;
	if( nerrors > MAXERRORS )
	{
		if( m_dlg_log )
			m_dlg_log->AddLine( "\r\n***** cancel verification *****\r\n" );
	}
	else
	{
		if( m_dlg_log )
			m_dlg_log->AddLine( "\r\n***** DONE *****\r\n" );
		if ( nerrors == 0 )
			m_project_validated = 2;
	}
}


int CFreePcbDoc::GetGerberPathes(CString Path)
{
	CString shortcut[NUM_SHORTCUTS];
	CFileFind m_find_dir; 	
	CString szFavorite_path = m_app_dir + "\\Shortcut";  
	BOOL bWorking = 0; 
	int num_shortcut = 0;
	DWORD dwAttr = GetFileAttributes(szFavorite_path);
	if(dwAttr == 0xffffffff)  
	{  
		DWORD dwError = GetLastError();  
		if(dwError == ERROR_FILE_NOT_FOUND)  
		{  
			AfxMessageBox(G_LANGUAGE == 0 ? 
				"Shortcut path not found":
				"Путь ярлыка не найден", MB_OK);
		}  
	}	  
	else if( Path.GetLength() )
	{  
		bWorking = m_find_dir.FindFile(szFavorite_path+"\\*.*");  	
		while  (bWorking)  
		{  	
			bWorking = m_find_dir.FindNextFile();
			if( !m_find_dir.IsDots() && !m_find_dir.IsDirectory())   
			{  
				CString m_gName = m_find_dir.GetFileName();
				if( m_gName.Right(4).MakeLower() == ".lnk" )
				{
					m_cam_shortcut[num_shortcut] = m_find_dir.GetFilePath();
					shortcut[num_shortcut] = m_gName;
					num_shortcut++;
					if( num_shortcut >= NUM_SHORTCUTS )
						break;
				}
			}			
		}
	}
	CWnd* pMain = AfxGetMainWnd();
	CMenu* pMenu = pMain->GetMenu();
	CMenu* submenu = pMenu->GetSubMenu(0);

	//delete old menu	
	static char * menu1 = NULL;
	static char * menu2 = NULL;
	static char * menu3 = NULL;
	if(menu1)
	{
		submenu->DeleteMenu(ID_FILE_GERBER_VIEWER1,0);
		delete[] menu1;
		menu1 = NULL;
	}
	if(menu2)
	{
		submenu->DeleteMenu(ID_FILE_GERBER_VIEWER2,0);
		delete[] menu2;
		menu2 = NULL;
	}
	if(menu3)
	{
		submenu->DeleteMenu(ID_FILE_GERBER_VIEWER3,0);
		delete[] menu3;
		menu3 = NULL;
	}
	//out
	if( num_shortcut == 0 )
		return 0;
	
	// create menu
	MENUITEMINFO MenuItem1;
	if( num_shortcut > 0 )
	{
		CString shc;
		shc = shortcut[0].Left(shortcut[0].ReverseFind('.'));
	    MenuItem1.cbSize=sizeof(MENUITEMINFO);
	    MenuItem1.fMask=MIIM_STATE|MIIM_TYPE|MIIM_SUBMENU|MIIM_ID;
	    MenuItem1.fType=MFT_STRING;
	    MenuItem1.fState=MFS_ENABLED;		
		menu1 = new char[shc.GetLength()+1]; //??????????????
		for( int ii=0; ii<shc.GetLength(); ii++ )
			menu1[ii] = shc[ii];
		menu1[shc.GetLength()] = '\0';
		MenuItem1.dwTypeData = menu1;
		MenuItem1.cch = shc.GetLength()+1;
	    MenuItem1.wID = ID_FILE_GERBER_VIEWER1;//ПОПРАВИТЬ НА НУЖНЫЙ ID
	    MenuItem1.hSubMenu=CreatePopupMenu();
	}
	MENUITEMINFO MenuItem2;
	if( num_shortcut > 1 )
	{
		CString shc;
		shc = shortcut[1].Left(shortcut[1].ReverseFind('.'));   
	    MenuItem2.cbSize=sizeof(MENUITEMINFO);
	    MenuItem2.fMask=MIIM_STATE|MIIM_TYPE|MIIM_SUBMENU|MIIM_ID;
	    MenuItem2.fType=MFT_STRING;
	    MenuItem2.fState=MFS_ENABLED;		
		menu2 = new char[shc.GetLength()+1]; //??????????????
		for( int ii=0; ii<shc.GetLength(); ii++ )
			menu2[ii] = shc[ii];
		menu2[shc.GetLength()] = '\0';
		MenuItem2.dwTypeData = menu2;
		MenuItem2.cch = shc.GetLength()+1;
	    MenuItem2.wID = ID_FILE_GERBER_VIEWER2;//ПОПРАВИТЬ НА НУЖНЫЙ ID
	    MenuItem2.hSubMenu=CreatePopupMenu();
	}
	MENUITEMINFO MenuItem3;
	if( num_shortcut > 2 )
	{
		CString shc;
		shc = shortcut[2].Left(shortcut[2].ReverseFind('.'));	    
	    MenuItem3.cbSize=sizeof(MENUITEMINFO);
	    MenuItem3.fMask=MIIM_STATE|MIIM_TYPE|MIIM_SUBMENU|MIIM_ID;
	    MenuItem3.fType=MFT_STRING;
	    MenuItem3.fState=MFS_ENABLED;		
		menu3 = new char[shc.GetLength()+1]; //??????????????
		for( int ii=0; ii<shc.GetLength(); ii++ )
			menu3[ii] = shc[ii];
		menu3[shc.GetLength()] = '\0';
		MenuItem3.dwTypeData = menu3;
		MenuItem3.cch = shc.GetLength()+1;
	    MenuItem3.wID = ID_FILE_GERBER_VIEWER3;//ПОПРАВИТЬ НА НУЖНЫЙ ID
	    MenuItem3.hSubMenu=CreatePopupMenu();
	}
	//
	// 
	struct _stat buf;
	if( _stat( m_cam_full_path, &buf ) )
		szFavorite_path = m_pcb_full_path.Left(m_pcb_full_path.ReverseFind('\\'));
	else
		szFavorite_path = m_cam_full_path.Left(m_cam_full_path.ReverseFind('\\'));
	//
	int imenu = 0; //number of menu items
	bWorking = 0; 
	BOOL b_cam_present = 0;
	dwAttr = GetFileAttributes(szFavorite_path);
	if(dwAttr == 0xffffffff)  
	{  
		DWORD dwError = GetLastError();  
		if(dwError == ERROR_FILE_NOT_FOUND)  
		{  
			//AfxMessageBox("Gerber path not found", MB_OK);  
		}  
	}	  
    else  
	{  
		bWorking = m_find_dir.FindFile(szFavorite_path+"\\*.*");  	
		while  (bWorking)  
		{  	
			bWorking = m_find_dir.FindNextFile(); 
			if ( !m_find_dir.IsDots() && m_find_dir.IsDirectory() )
			{
				CFileFind m_find_g_file; 
				CString CAM_F = m_find_dir.GetFileName();
				CString path2 = m_find_dir.GetFilePath(); 
				BOOL bWorking2 = m_find_g_file.FindFile(path2+"\\*.*");
				while  (bWorking2)  
				{
					bWorking2 = m_find_g_file.FindNextFile();
					if( !m_find_g_file.IsDots() && !m_find_g_file.IsDirectory())   
					{  
						CString m_gName = m_find_g_file.GetFileName();
						if( m_gName.Right(4).MakeLower() == ".gbr" && imenu < NUM_CAM_FOLDERS )
						{
							if( b_cam_present == 0 )
								InsertMenuItem(submenu->GetSafeHmenu(),ID_FILE_GENERATEREPORTFILE, 0, &MenuItem1);
							AppendMenu(MenuItem1.hSubMenu,MFT_STRING,ID_FILE_CAM1+imenu,CAM_F);
							if( num_shortcut > 1 )
							{
								if( b_cam_present == 0 )
									InsertMenuItem(submenu->GetSafeHmenu(),ID_FILE_GENERATEREPORTFILE, 0, &MenuItem2);
								AppendMenu(MenuItem2.hSubMenu,MFT_STRING,ID_FILE_CAM8+imenu,CAM_F);
							}
							if( num_shortcut > 2 )
							{
								if( b_cam_present == 0 )
									InsertMenuItem(submenu->GetSafeHmenu(),ID_FILE_GENERATEREPORTFILE, 0, &MenuItem3);
								AppendMenu(MenuItem3.hSubMenu,MFT_STRING,ID_FILE_CAM15+imenu,CAM_F);
							}
							b_cam_present = 1;
							CAM[imenu] = path2;
							imenu++;
							break;
						}
					}
				}
			}
		}
	}
	return imenu;
}

cnet * CFreePcbDoc::DrcTestforDlElement( dl_element * el, id * ID, int * dist, int * m_cx, int * m_cy, int * wFLAG, cpart ** badP, CText ** badT, cnet ** badN )
{
	cpart * part_el = *badP; //  dl_element belongs to this part
	cpart * prev_part = NULL;
	CString noN = "__UNCONNECTED__";
	cnet * virtual_net_unc = m_nlist->GetNetPtrByName( &noN );
	if( virtual_net_unc == NULL )
		virtual_net_unc = m_nlist->AddNet( noN, 0,0,0 );
	//
	int MAX_CL = max( m_dr.trace_trace, m_dr.copper_copper );
	MAX_CL = max( MAX_CL, m_dr.hole_copper );
	MAX_CL = max( MAX_CL, m_dr.pad_trace );
	*wFLAG = 0;
	ID->type = ID_NONE;
	cnet * NetPtr = NULL;
	if( el )
	{
		int LTop = getbit( el->layers_bitmap, LAY_TOP_COPPER );
		int LBot = getbit( el->layers_bitmap, LAY_BOTTOM_COPPER );
		if( LTop || LBot )
		{
			CArray <CPoint> * dl_els = m_dlist->Get_Points( el, NULL, 0 );
			int np = dl_els->GetSize();
			if( np )
			{
				int Lw = m_dlist->Get_el_w( el );
				RECT LRECT;
				m_dlist->Get_Rect( el, &LRECT );
				CPoint * P = new CPoint[np];//ok
				m_dlist->Get_Points( el, P, &np );

				if (el->gtype == DL_ARC_CW || el->gtype == DL_ARC_CCW ||
					el->gtype == DL_CURVE_CW || el->gtype == DL_CURVE_CCW)
				{
					ASSERT(0); //no test for arc elements
				}

				for(int ipt=0; (ipt+1)<np; ipt++ )
				{
					int Lx1 = P[ipt].x;
					int Ly1 = P[ipt].y;
					int Lx2 = P[ipt+1].x;
					int Ly2 = P[ipt+1].y;
					if( el->gtype == DL_LINES_ARRAY )
						ipt++;
					RECT LR = rect( Lx1, Ly1, Lx2, Ly2 );
					SwellRect( &LR, (Lw/2)+m_dr.trace_trace );
					// scanning connects
					for( cnet * n = m_nlist->GetFirstNet(); n; n = m_nlist->GetNextNet() ) 
					{
						for( int ic=0; ic<n->nconnects; ic++ )
						{
							if( n->connect[ic].min_x - LRECT.right > m_dr.trace_trace )
								continue;
							if( LRECT.left - n->connect[ic].max_x > m_dr.trace_trace )
								continue;
							if( n->connect[ic].min_y - LRECT.top > m_dr.trace_trace )
								continue;
							if( LRECT.bottom - n->connect[ic].max_y > m_dr.trace_trace )
								continue;
							for( int iv=0; iv<n->connect[ic].nsegs; iv++ )
							{
								int CLay = n->connect[ic].seg[iv].layer; 
								if( ( LTop && CLay == LAY_TOP_COPPER ) ||
									( LBot && CLay == LAY_BOTTOM_COPPER ) ||
									( n->connect[ic].vtx[iv+1].via_hole_w ))
								{
									int Cx1 = n->connect[ic].vtx[iv].x;
									int Cy1 = n->connect[ic].vtx[iv].y;
									int Cx2 = n->connect[ic].vtx[iv+1].x;
									int Cy2 = n->connect[ic].vtx[iv+1].y;
									int Cw = n->connect[ic].seg[iv].width;
									int vW = n->connect[ic].vtx[iv+1].via_w;
									RECT CR = rect( Cx1, Cy1, Cx2, Cy2 );
									SwellRect( &CR, Cw/2 );
									if(vW)
									{
										RECT vR = rect( Cx2-vW/2,Cy2-vW/2,Cx2+vW/2,Cy2+vW/2 );
										SwellRect( &CR, vR );
									}
									if( RectsIntersection( LR, CR ) >= 0 )
									{
										// test seg
										int xx, yy;  
										int d = MAX_CL;
										if( ( LTop && CLay == LAY_TOP_COPPER ) ||
											( LBot && CLay == LAY_BOTTOM_COPPER ) )
											d = ::GetClearanceBetweenSegments( Lx1, Ly1, Lx2, Ly2, CPolyLine::STRAIGHT, Lw, 
												Cx1, Cy1, Cx2, Cy2, CPolyLine::STRAIGHT, Cw, MAX_CL, &xx, &yy );
										if( vW )
										{	// test via
											int d2 = ::GetClearanceBetweenSegments( Lx1, Ly1, Lx2, Ly2, CPolyLine::STRAIGHT, Lw, 
											Cx2, Cy2, Cx2+10, Cy2+10, CPolyLine::STRAIGHT, vW, MAX_CL, &xx, &yy );
											d = min(d,d2);
											if( el->gtype == DL_POLYGON )
											{
												if( TestPolygon( Cx2, Cy2, P, np ))
													d = 0;
											}
										}
										if( d < m_dr.trace_trace )
										{
											if( NetPtr )
											{
												if( NetPtr != n )
												{
													// ERROR
													m_nlist->CancelNextNet();
													ID->Set(ID_NET, ID_CONNECT, ic, ID_SEG, iv);
													*m_cx = xx;
													*m_cy = yy;
													*dist = d;
													delete P;
													*badN = n;
													return NetPtr;
												}
											}
											else
											{
												*m_cx = xx;
												*m_cy = yy;
												*dist = d;
												NetPtr = n;
												break;
											}
										}
									}
								}
							}
							if( NetPtr == n )
								break;
						}
						if( NetPtr != n )
						{
							for( int ia=0;ia<n->nareas;ia++ )
							{
								CPolyLine * po = n->area[ia].poly;
								if( po->GetHatch() != CPolyLine::DIAGONAL_FULL )
									continue;

								// merge clearance
								int areaM = po->GetMerge();
								int m_cl = 0;
								if( areaM >= 0 )
									m_cl = m_mlist->GetClearance( areaM );

								int AL = po->GetLayer();
								if( ( LTop && AL == LAY_TOP_COPPER ) ||
									( LBot && AL == LAY_BOTTOM_COPPER ) )
								{
									RECT PR = po->GetBounds();
									if( RectsIntersection( LR, PR ) >= 0 )
									{
										for( int ico=0; ico<po->GetNumCorners(); ico++ )
										{
											int Ax1 = po->GetX(ico);
											int Ay1 = po->GetY(ico);
											int Ax2 = po->GetX(po->GetIndexCornerNext(ico));
											int Ay2 = po->GetY(po->GetIndexCornerNext(ico));
											int Aw = po->GetW();
											int st = po->GetSideStyle(ico);
											int xx, yy; 
											int d = ::GetClearanceBetweenSegments( Lx1, Ly1, Lx2, Ly2, CPolyLine::STRAIGHT, Lw, 
												Ax1, Ay1, Ax2, Ay2, st, Aw, MAX_CL, &xx, &yy );
											if( d < (m_cl?m_cl:m_dr.copper_copper) )
											{
												if( NetPtr )
												{
													if( NetPtr != n )
													{
														// ERROR
														m_nlist->CancelNextNet();
														ID->Set(ID_NET, ID_AREA, ia, ID_SIDE, ico);
														*m_cx = xx;
														*m_cy = yy;
														*dist = d;
														delete P;
														*badN = n;
														return NetPtr;
													}
												}
												else
												{
													*m_cx = xx;
													*m_cy = yy;
													*dist = d;
													NetPtr = n;
													break;
												}
											}
										}
									}
								}
								if( NetPtr == n )
									break;
							}
						}
					}
					for( cpart * Gpart = m_plist->GetFirstPart(); Gpart; Gpart = m_plist->GetNextPart( Gpart ) )
					{
						CShape * Gs = Gpart->shape;
					  	if( Gs && Gpart->drawn )
						{
							if( Gpart->min_x - LRECT.right > MAX_CL )
								continue;
							if( LRECT.left - Gpart->max_x > MAX_CL )
								continue;
							if( Gpart->min_y - LRECT.top > MAX_CL )
								continue;
							if( LRECT.bottom - Gpart->max_y > MAX_CL )
								continue;
							for( int ip=0; ip<Gs->GetNumPins(); ip++ )
							{
								// get pad rect
								RECT padr;
								if( !m_plist->GetPadBounds(Gpart,ip,&padr) )
								{
									continue;
								}
								SwellRect( &padr, MAX_CL );
								if( RectsIntersection( padr, LR ) < 0 )
								{
									continue;
								}
								// get test pad info
								int x, y, w, l, r, type, hole, connect, angle, lay;
								cnet * net=NULL;
								if( LTop )
									lay = LAY_TOP_COPPER;
								else
									lay = LAY_BOTTOM_COPPER;
								BOOL bPad = m_plist->GetPadDrawInfo( Gpart, ip, lay, 0, 0, 0, 0,
									&type, &x, &y, &w, &l, &r, &hole, &angle, &net, &connect );
								if( bPad )
								{
									if( !net )
										net = virtual_net_unc;
									if( hole )
									{
										int d = ::GetClearanceBetweenSegmentAndPad( Lx1,Ly1,Lx2,Ly2, Lw,
										PAD_ROUND, x, y, hole, hole, 0, 0 );
										//
										if( d < m_dr.hole_copper )
										{
											if( NetPtr )
											{
												if( NetPtr != net ||
													( NetPtr == virtual_net_unc && (Gpart != prev_part || Gpart != part_el) ))
												{
													//if( net == 0 )
													//{
														// WARNING
														//str.Format( "is Warning: Polyline connects pin %s.%s to the net \"%s\".\r\n", 
														//	Gpart->ref_des, Gs->m_padstack[ip].name, part->NetPtr[io]->name );
														//if( m_dlg_log )
														//	m_dlg_log->AddLine( str );
													//	*wFLAG = TRUE;
													//	continue; // next pin
													//}
													//else
													//{
														// ERROR
														ID->Set(ID_PART, ID_PAD, ip, ID_HOLE, 0);
														*m_cx = x;
														*m_cy = y;
														*dist = d;
														*badP = Gpart;
														delete P;
														*badN = net;
														return NetPtr;
													//}
												}
											}
											else
											{
												*m_cx = x;
												*m_cy = y;
												*dist = d;
												NetPtr = net;
												prev_part = Gpart;
											}
										}
									}
									if( type != PAD_NONE )
									{
										int d = ::GetClearanceBetweenSegmentAndPad( Lx1,Ly1,Lx2,Ly2, Lw,
											type, x, y, w, l, r, angle );
										//
										if( d < m_dr.pad_trace )
										{
											if( NetPtr )
											{
												if( NetPtr != net ||
													( NetPtr == virtual_net_unc && (Gpart != prev_part || Gpart != part_el) ))
												{
													//if( net == 0 )
													//{
														// WARNING
														//str.Format( "is Warning: Polyline connects pin %s.%s to the net \"%s\".\r\n", 
														//	Gpart->ref_des, Gs->m_padstack[ip].name, part->NetPtr[io]->name );
														//if( m_dlg_log )
														//	m_dlg_log->AddLine( str );
													//	*wFLAG = TRUE;
													//}
													//else
													//{
														// ERROR
														ID->Set(ID_PART, ID_PAD, ip, 0, 0);
														*m_cx = x;
														*m_cy = y;
														*dist = d;
														*badP = Gpart;
														delete P;
														*badN = net;
														return NetPtr;
													//}
												}
											}
											else
											{
												*m_cx = x;
												*m_cy = y;
												*dist = d;
												NetPtr = net;
												prev_part = Gpart;
											}
										}
									}
								}
							}
						}
					}
					int j=0;
					for( CText * t=m_tlist->GetFirstText(); t; t=m_tlist->GetNextText(&j) )
					{
						if( t->dl_el )
							if( el != t->dl_el )
								if( ( t->m_layer == LAY_TOP_COPPER && LTop ) ||
									( t->m_layer == LAY_BOTTOM_COPPER && LBot ))
							 	{
									RECT tr;
									m_dlist->Get_Rect( t->dl_sel, &tr );
									if( RectsIntersection( LR, tr ) >= 0 )
									{
										int np = 4;
										CPoint tp[4];
										m_dlist->Get_Points( t->dl_sel, tp, &np );
										if( np == 4 )
										{
											int x = (tr.left + tr.right)/2;
											int y = (tr.top + tr.bottom)/2;
											int w = Distance(tp[0].x,tp[0].y,tp[1].x,tp[1].y);
											int l = Distance(tp[0].x,tp[0].y,tp[3].x,tp[3].y);
											int d = ::GetClearanceBetweenSegmentAndPad( Lx1,Ly1,Lx2,Ly2, Lw,
												PAD_RECT, x, y, w, l, 0, t->m_angle );
											//
											if( d < m_dr.trace_trace )
											{
												// ERROR
												ID->Set(ID_TEXT_DEF);
												ID->i = t->m_x;
												ID->ii = t->m_y;
												*m_cx = x;
												*m_cy = y;
												*dist = d;
												*badT = t;
												delete P;
												*badN = NULL;
												return NetPtr;
											}
										}
									}
								}
					}
				}
				delete P;
			}
		}
	}
	*badN = NULL;
	return NetPtr;
}

int CFreePcbDoc::CheckUpdates()
{
	CStdioFile url_file;
	CString m_last_upd="data::????????", 
			enable="1", 
			time_out="2",
			m_user_name="xxxxxxxx",
			m_user_psw="xxxxxxxx",
			m_proxy="xx.xx.xx.xx",
			m_port="xxxx";
	CString fn = m_app_dir + "\\" + "user.cfg";
	int err = url_file.Open( fn, CFile::modeRead, NULL );
	if( err )
	{
		// read 
		try
		{
			//
			url_file.ReadString( enable );
			enable = enable.Right(1);
			//
			url_file.ReadString( time_out );
			time_out = time_out.Right(1);
			//
			url_file.ReadString( m_last_upd );
			//
			CString s;
			url_file.ReadString( s );
			s = s.Right(s.GetLength()-10);
			s = s.Trim();
			if( s.GetLength() )
				m_user_name = s;
			//
			url_file.ReadString( s );
			s = s.Right(s.GetLength()-9);
			s = s.Trim();
			if( s.GetLength() )
				m_user_psw = s;
			//
			url_file.ReadString( s );
			s = s.Right(s.GetLength()-6);
			s = s.Trim();
			if( s.GetLength() )
				m_proxy = s;
			//
			url_file.ReadString( s );
			s = s.Right(s.GetLength()-5);
			s = s.Trim();
			if( s.GetLength() )
				m_port = s;
			url_file.Close();
		}
		catch( CString * err_str )
		{
			*err_str = "CFreePcbDoc::CheckUpdates()\n" + *err_str;
			AfxMessageBox(*err_str);
			delete err_str;
		}
	}
	if( enable.Compare("1") == 0 )
	{
		CString commandLine; 
		if( m_proxy.Left(2) != "xx" )
		{
			if( m_user_name.Left(2) != "xx" )
				commandLine.Format( "\"%s\\cURL\\curl.exe\" --connect-timeout %s -x %s:%s@%s:%s \"https://github.com/Duxah/FreePCB-2/blob/master/message_to_users.md\"", m_app_dir, time_out, m_user_name, m_user_psw, m_proxy, m_port );
			else
				commandLine.Format( "\"%s\\cURL\\curl.exe\" --connect-timeout %s -x %s:%s \"https://github.com/Duxah/FreePCB-2/blob/master/message_to_users.md\"", m_app_dir, time_out, m_proxy, m_port );
		}
		else
		{
			if( m_user_name.Left(2) != "xx" )
				commandLine.Format( "\"%s\\cURL\\curl.exe\" --connect-timeout %s -u %s:%s \"https://github.com/Duxah/FreePCB-2/blob/master/message_to_users.md\"", m_app_dir, time_out, m_user_name, m_user_psw );
			else
				commandLine.Format( "\"%s\\cURL\\curl.exe\" --connect-timeout %s \"https://github.com/Duxah/FreePCB-2/blob/master/message_to_users.md\"", m_app_dir, time_out );
		}
		m_dlg_log->AddLine( "Run: " + commandLine + "\r\n" );
		RunConsoleProcess( commandLine, m_dlg_log );
		CString Mess, m_get_upd="data::00000000";
		m_dlg_log->m_edit_log.GetWindowTextA(Mess);
		int f = Mess.Find("curl:");
		if( f > 0 )
		{
			f += 4;
			Mess = "Warning" + Mess.Right(Mess.GetLength()-f) + "\r\nCheck your internet connection otherwise you will not be able to receive news from the site.\r\n(Proxy settings are in the user.cfg file in the Application folder)";
		}
		f = Mess.Find("data::");
		if( f > 0 )
		{
			Mess = Mess.Right(Mess.GetLength()-f);
		}
		f = Mess.Find("msg::");
		if( f > 0 )
		{
			f += 5;
			m_get_upd = Mess.Left(14);
			Mess = Mess.Right(Mess.GetLength()-f);
			f = Mess.Find("</p>");
			if( f > 0 )
			{
				Mess = Mess.Left(f);	
			}
		}
		m_dlg_log->Clear();
		//
		if( m_get_upd.Compare(m_last_upd) == 0 )
		{
			m_dlg_log->ShowWindow( SW_HIDE );
		}
		else if( m_get_upd.Right(8) != "00000000" )
		{
			int OK = 0;
			CString new_data = m_get_upd.Right(8);
			CString old_data = m_last_upd.Right(8);
			if (my_atoi(&new_data) < my_atoi(&old_data))
				AfxMessageBox(G_LANGUAGE == 0 ?
					"You have a newer version of this program installed than on the website. You will receive a notification when this version on the site is updated." :
					"У вас установлена более новая версия этой программы, чем на сайте. Вы получите уведомление, когда эта версия на сайте обновится");
			else if( my_atoi(&old_data) == 0 )
				OK = 1;
			else 
			{
				Mess += (G_LANGUAGE == 0 ? 
					"\n\nWant to go to the download page now?":
					"\n\nХотите перейти на страницу загрузки прямо сейчас?");
				if( AfxMessageBox(Mess, MB_YESNO) == IDYES )
					OK = 2;
			}
			if( OK )
			{
				if( OK == 2 )
					ShellExecute( NULL,"open","https://github.com/Duxah/FreePCB-2/blob/master/Download.md", NULL, NULL, SW_SHOWNORMAL);
				int err = url_file.Open( LPCSTR(fn), CFile::modeCreate | CFile::modeWrite, NULL );
				if( !err )
				{
					// error opening file
					CString mess;
					mess.Format(G_LANGUAGE == 0 ? "Unable to open file \"%s\"" : "Невозможно открыть файл %s", fn );
					AfxMessageBox( mess );
					return 0;
				}
				else
				{
					// write 
					try
					{
						CString line;
						line.Format( "allow_check_news: 1\n" );
						url_file.WriteString( line );
						line.Format( "time_out: %s\n", time_out );
						url_file.WriteString( line );
						line.Format( "%s\n", m_get_upd );
						url_file.WriteString( line );
						line.Format( "user_name: %s\n", m_user_name );
						url_file.WriteString( line );
						line.Format( "user_psw: %s\n", m_user_psw );
						url_file.WriteString( line );
						line.Format( "proxy: %s\n", m_proxy );
						url_file.WriteString( line );
						line.Format( "port: %s\n", m_port );
						url_file.WriteString( line );
					}
					catch( CString * err_str )
					{
						*err_str = "CFreePcbDoc::CheckUpdates()\n" + *err_str;
						AfxMessageBox(*err_str);
						delete err_str;
					}
				}
				url_file.Close();
			}
		}
		else
		{
			m_dlg_log->ShowWindow( SW_SHOW );
			m_dlg_log->AddLine(Mess);
		}
	}
	return 0;
}

void CFreePcbDoc::EnsureNotMinimized( HWND hWnd, BOOL bSwToFile )
{
	// Timer Off
	CMainFrame * frm = (CMainFrame*)AfxGetMainWnd();
	if( frm )
		frm->SetTimer( JUMPING_TIMER, INT_MAX, 0 );
	//
	WINDOWPLACEMENT placement;
	placement.length = sizeof(placement);
	//
	if( GetWindowPlacement(hWnd, &placement) )
	{
		if( placement.showCmd & SW_SHOWMINIMIZED) 
		{
			placement.showCmd = SW_SHOWNORMAL;
			SetWindowPlacement(hWnd, &placement);
		}
	}
	CString data = "\""+m_pcb_filename+"\"";
	if( bSwToFile )
		m_view->OnSendMess( "pcb_file: " + data, hWnd );
	if( m_view->m_sel_id.st == ID_PAD && m_view->m_sel_part )
	{
		data = m_view->m_sel_part->ref_des;
		data += " ";
		data += m_view->m_sel_part->shape->GetPinNameByIndex( m_view->m_sel_id.i );
		if( m_view->m_cursor_mode == CUR_PAD_SELECTED )
		{
			SetForegroundWindow(hWnd);
			m_view->OnSendMess( "pin: " + data, hWnd );
		}
		else
			m_view->OnSendMess( "*pin: " + data, hWnd );
	}
	else
	{
		SetForegroundWindow(hWnd);
		m_plist->GetSelParts( &data );
		m_view->OnSendMess( "parts: " + data, hWnd );
	}
}

CString CFreePcbDoc::FindSchematicFile()
{
	int rf = m_pcb_full_path.ReverseFind('\\');
	CString pr_folder = m_pcb_full_path.Left( rf );
	CString first_f = "\\*.cds";
	CString search_str = pr_folder + first_f;
	CFileFind finder;
	BOOL bWorking = finder.FindFile( search_str );
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		CString fn = finder.GetFileName();
		if( !finder.IsDirectory() && !finder.IsDots() )
		{
			// found a file
			if( bWorking ) 
				if(G_LANGUAGE==0)
					AfxMessageBox("You cannot store more than one schematic "\
						"file in one project folder. Schematic Constructor automatically "\
						"cleans the related_files folder from unused image files that "\
						"you import into the project. If you ignore this rule, "\
						"then you will most likely have problems with indexing the "\
						"images of the project, or an error when jumping from the PCB "\
						"to the circuit. You can attach up to 8 PCB files to one schematic file. "\
						"This is the concept behind this software", MB_ICONWARNING);
				else
					AfxMessageBox("Вы не должны хранить более одного файла схемы "\
						"в одной папке проекта. Конструктор схем автоматически "\
						"очищает папку related_files от неиспользуемых файлов изображений, которые "\
						"вы импортируете в проект. Если вы проигнорируете данное правило, "\
						"то у вас, скорее всего, возникнут проблемы с изображениями, "\
						"они все перепутаются. Также возникнет ошибка при переходе от печатной платы "\
						"к схеме. Вы можете прикрепить до 8 файлов печатной платы к одному файлу схемы, но не наоборот. "\
						"Это концепция, лежащая в основе этого программного обеспечения", MB_ICONWARNING);
			return finder.GetFileName();
		}
	}
	return "";
}

void CFreePcbDoc::SwitchTo__ECDS()
{
	SwitchTo_ECDS();
}

void CFreePcbDoc::SwitchTo_ECDS( BOOL standby )
{
	if (bNoFilesOpened)
	{
		CString FreeCds = m_app_dir + "\\СхемАтор.exe";
		if (G_LANGUAGE == 0)
			FreeCds = m_app_dir + "\\FreeCds.exe";
		if ((UINT)ShellExecute(NULL, "open", "\"" + FreeCds + "\"", "", "\"" + m_app_dir + "\"", SW_SHOWNORMAL) > 32)
		{
		}
		return;
	}
	for( int STEP=0; STEP<2; STEP++ )
	{
		CString name = PROGRAM_CAP2 + m_cds_filename;
		HWND wnd = FindWindow(NULL,name);
		if( wnd )
			EnsureNotMinimized(wnd);
		else
		{
			name += "*";
			wnd = FindWindow(NULL,name);
			if( wnd )
				EnsureNotMinimized(wnd);
			else if( standby )
				return;
			else
			{
				if( STEP == 0 )
				{
					m_cds_filename = FindSchematicFile();
					continue;
				}
				else if( m_cds_filename.GetLength() )
				{
					int rf = m_pcb_full_path.ReverseFind( '\\' );
					CString cds_file = m_pcb_full_path.Left(rf) + "\\" + m_cds_filename;
					CString FreeCds = m_app_dir + "\\СхемАтор.exe";
					if (G_LANGUAGE == 0)
						FreeCds = m_app_dir + "\\FreeCds.exe";
					if ( (UINT)ShellExecute(	NULL,"open", "\""+FreeCds+"\"", "\""+cds_file+"\"", "\""+m_app_dir+"\"", SW_SHOWNORMAL) > 32 )
					{
						CMainFrame * frm = (CMainFrame*)AfxGetMainWnd();
						if( frm )
							frm->SetTimer( JUMPING_TIMER, 2000, 0 );
					}
					return;
				}
				int rf = m_pcb_full_path.ReverseFind( '.' );
				CString cds_file = m_pcb_full_path.Left(rf) + ".cds";
				{
					CStdioFile defF;
					CString def_file = m_app_dir + "\\default_cds.cfg";
					int op1 = defF.Open( def_file, CFile::modeRead, NULL );
					if( op1 )
					{
						CStdioFile cdsF;
						int op2 = cdsF.Open( cds_file, CFile::modeCreate | CFile::modeWrite, NULL );
						if( op2 )
						{
							CString in_str;
							while( defF.ReadString(in_str) )
							{
								in_str.Trim();
								if( in_str.Left(13) == "project_name:" )
								{
									CString cds_name = m_name;
									if( m_name.Right(4) == ".fpc" )
										cds_name = m_name.Left( m_name.GetLength()-4 );
									cdsF.WriteString("project_name: \""+cds_name+".cds\"\n");
									continue;
								}
								else if( in_str.Compare("[end]") == 0 )
								{
									cdsF.WriteString("pcb_name: \""+m_name+".fpc\" 1\n");
									cdsF.WriteString("[graphics]\n");
								}
								cdsF.WriteString(in_str);
								cdsF.WriteString("\n\n");
							}
							defF.Close();
							cdsF.Close();
							Sleep(500);
						}
					}
				}
				CString FreeCds = m_app_dir + "\\СхемАтор.exe";
				if(G_LANGUAGE==0)
					FreeCds = m_app_dir + "\\FreeCds.exe";
				if ( (UINT)ShellExecute(	NULL,"open", "\""+FreeCds+"\"", "\""+cds_file+"\"", "\""+m_app_dir+"\"", SW_SHOWNORMAL) > 32 )
				{
				}
			}
		}
		if( wnd )
			break;
	}
}


int CFreePcbDoc::ReadMessageFromSchematic( CString * file, BOOL SHOW_MESSAGE )
{
	clrbit( m_view->m_protected, PROTECT );
	int ifo = file->ReverseFind('\\');
	CString name = file->Right( file->GetLength() - ifo - 1 );
	CString mod_n = file->Left(ifo) + freeasy_netlist + name + ".txt";
	CStdioFile fmess;
	int err = fmess.Open( mod_n, CFile::modeRead, NULL );
	if( err )
	{
		CString in_str;
		fmess.ReadString( in_str );
		fmess.Close();
		if( in_str.Compare( FILE_PROTECTED ) == 0 )
		{
			setbit( m_view->m_protected, PROTECT );
		}
		else if( in_str.GetLength() )
		{
			if( in_str.Compare( NETLIST_UPDATED ) == 0 )
			{
				m_netlist_full_path = file->Left(ifo) + freeasy_netlist + name + ".net";
				return 2;
			}
			else if( SHOW_MESSAGE )
				AfxMessageBox( in_str );
			return 1;
		}
		else if( getbit( m_view->m_protected, PROTECT_ARCHIVED ) )
		{
			CDlgProtection dlg;
			dlg.Ini( this );
			if( dlg.FindArchive() )
				dlg.ExtProtection( TRUE );
		}
	}
	return 0;
}


void CFreePcbDoc::AddViaGrid()
{
	static int static_space_x=0;
	static int static_space_y=0;
	static int static_via_w=0;
	static int static_hole_w=0;
	if( m_view )
	{
		if( m_view->m_cursor_mode != CUR_AREA_SIDE_SELECTED )
		{
			AfxMessageBox(G_LANGUAGE == 0 ? 
				"This option adds a grid of vias to the copper area. First select the side of the copper area and then try again.":
				"Эта опция добавляет сетку переходных отверстий на медный полигон. Сначала выберите сторону медного полигона, кликнув мышью, а затем попробуйте снова.");
			return;
		}
		CDlgViaGrig dlg;
		if( static_space_x )
			dlg.Initialize( m_units==MM?-abs(static_via_w):abs(static_via_w), abs(static_hole_w), static_space_x, static_space_y );
		else
			dlg.Initialize( m_units==MM?-abs(m_via_w):abs(m_via_w), abs(m_via_hole_w) );
		int ok = dlg.DoModal();
		if( ok == IDOK )
		{
			static_space_x = dlg.m_out_x;
			static_space_y = dlg.m_out_y;
			static_via_w = dlg.m_def_via_w;
			static_hole_w = dlg.m_def_hole_w;
			CShape * footprint = new CShape;
			CString str_id;
			str_id.Format("ID%d", clock() );
			footprint->m_name = str_id;
			m_footprint_cache_map.SetAt( str_id, footprint );
			padstack pstack;
			pstack.hole_size = dlg.m_def_hole_w;
			pstack.top.shape = PAD_ROUND;
			pstack.top.size_X = dlg.m_def_via_w;
			pstack.top.size_Y = dlg.m_def_via_w;
			pstack.top.radius = 0;
			pstack.top.connect_flag = PAD_CONNECT_NOTHERMAL;
			pstack.inner.shape = PAD_ROUND;
			pstack.inner.size_X = dlg.m_def_via_w;
			pstack.inner.size_Y = dlg.m_def_via_w;
			pstack.inner.radius = 0;
			pstack.inner.connect_flag = PAD_CONNECT_NOTHERMAL;
			pstack.bottom.shape = PAD_ROUND;
			pstack.bottom.size_X = dlg.m_def_via_w;
			pstack.bottom.size_Y = dlg.m_def_via_w;
			pstack.bottom.radius = 0;
			pstack.bottom.connect_flag = PAD_CONNECT_NOTHERMAL;
			pstack.top_mask.shape = PAD_NONE;
			pstack.bottom_mask.shape = PAD_NONE;
			pstack.top_mask.size_X = 0;
			pstack.top_mask.size_Y = 0;
			pstack.bottom_mask.size_X = 0;
			pstack.bottom_mask.size_Y = 0;
			pstack.top_paste.size_X = 0;
			pstack.top_paste.size_Y = 0;
			pstack.bottom_paste.size_X = 0;
			pstack.bottom_paste.size_Y = 0;
			pstack.name = "1";
			if( dlg.as_part == 0 )
				footprint->m_padstack.Add( pstack );
			footprint->selection = rect(-dlg.m_def_via_w,-dlg.m_def_via_w,dlg.m_def_via_w,dlg.m_def_via_w);
			id aid = m_view->m_sel_id;
			CPolyLine * ap = m_view->m_sel_net->area[aid.i].poly;
			RECT totalRect = ap->GetBounds();
			int apLay = ap->GetLayer();
			int num = 1;
			int count = 0;
			int Line = 0;
			int number = 0;
			int X_start_value = ( totalRect.left+dlg.m_def_via_w/2+_2540*10 );
			int x_max_step_count = ( totalRect.right-dlg.m_def_via_w/2 - X_start_value )/dlg.m_out_x + 1;
			cpart * pStart = NULL;
			for( int currX=X_start_value; currX<totalRect.right-dlg.m_def_via_w/2; currX+=dlg.m_out_x )
			{
				Line++;
				int Y_start_value = ( (Line%2&&dlg.chess==1)?(totalRect.top-dlg.m_def_via_w/2-dlg.m_out_y/2):(totalRect.top-dlg.m_def_via_w/2-_2540*2) );
				int y_max_step_count = ( Y_start_value - (totalRect.bottom+dlg.m_def_via_w/2) )/dlg.m_out_y + 1;
				int max_num_vias = abs(x_max_step_count*y_max_step_count);
				BOOL fail = 0;
				for( int currY=Y_start_value; currY>totalRect.bottom+dlg.m_def_via_w/2; currY-=((fail&&dlg.chess==2)?(dlg.m_out_y/2):dlg.m_out_y) )
				{
					number++;
					{
						CMainFrame * pMain = (CMainFrame*) AfxGetApp()->m_pMainWnd;
						if( pMain )
						{
							CString s;
							s.Format( "via %d from %d", number, max_num_vias ); 
							pMain->DrawStatus( 3, &s );
							if( number%10 == 0 )
								pMain->UpdateWindow();
						}
					}
					if( ap->TestPointInside( currX, currY ) )
					{
						fail = 0;
						for( int icr=0; icr<ap->GetNumSides(); icr++ )
						{
							int inxt = ap->GetIndexCornerNext(icr);
							int ax1 = ap->GetX(icr);
							int ay1 = ap->GetY(icr);
							int ax2 = ap->GetX(inxt);
							int ay2 = ap->GetY(inxt);
							int xc=0, yc=0;
							int d = GetClearanceBetweenSegments( ax1, ay1, ax2, ay2, ap->GetSideStyle(icr), ap->GetW(), 
																 currX, currY, currX+10, currY+10, 0, 0, INT_MAX/10, &xc, &yc );
							if( d < abs(dlg.m_def_via_w/2-ap->GetW()) )
							{
								fail = 1;
								break;
							}
						}
						RECT viaRect = rect( currX, currY, currX, currY );
						SwellRect( &viaRect, dlg.m_def_via_w/2 );
						for( cpart * p=m_plist->GetFirstPart(); p; p=m_plist->GetNextPart(p) )
						{
							RECT pRect = rect(0,0,0,0);
							m_plist->GetPartBoundingRect( p, &pRect );
							if( RectsIntersection( viaRect, pRect ) == -1 )
								continue;
							if( p->shape )
							{
								for( int ipad=0; ipad<p->shape->GetNumPins(); ipad++ )
								{
									if( p->shape->m_padstack[ipad].bottom.shape == 0 &&
										p->shape->m_padstack[ipad].top.shape == 0 &&
										p->shape->m_padstack[ipad].hole_size == 0 )
										continue;
									//
									int padRND = 0;
									RECT padRect;
									m_plist->GetPadBounds( p, ipad, &padRect );
									if( apLay > LAY_BOTTOM_COPPER )
									{
										if( p->shape->m_padstack[ipad].inner.shape == PAD_ROUND ||
											p->shape->m_padstack[ipad].inner.shape == PAD_OCTAGON )
											padRND = p->shape->m_padstack[ipad].inner.size_X;
									}
									else if( p->side == 0 )
									{
										if( apLay == LAY_TOP_COPPER )
											if( p->shape->m_padstack[ipad].top.shape == PAD_ROUND ||
												p->shape->m_padstack[ipad].top.shape == PAD_OCTAGON )
												padRND = p->shape->m_padstack[ipad].top.size_X;
										if( apLay == LAY_BOTTOM_COPPER )
											if( p->shape->m_padstack[ipad].bottom.shape == PAD_ROUND ||
												p->shape->m_padstack[ipad].bottom.shape == PAD_OCTAGON )
												padRND = p->shape->m_padstack[ipad].bottom.size_X;
									}
									else
									{
										if( apLay == LAY_TOP_COPPER )
											if( p->shape->m_padstack[ipad].bottom.shape == PAD_ROUND ||
												p->shape->m_padstack[ipad].bottom.shape == PAD_OCTAGON )
												padRND = p->shape->m_padstack[ipad].bottom.size_X;
										if( apLay == LAY_BOTTOM_COPPER )
											if( p->shape->m_padstack[ipad].top.shape == PAD_ROUND ||
												p->shape->m_padstack[ipad].top.shape == PAD_OCTAGON )
												padRND = p->shape->m_padstack[ipad].top.size_X;
									}
									if( padRND )
									{
										CPoint pinpoint = m_plist->GetPinPoint( p, ipad, p->side, p->angle );
										int dis = Distance( pinpoint.x, pinpoint.y, currX, currY );
										if( dis < (padRND/2 + dlg.m_def_via_w/2) )
											fail = 1;
										if( p->pin[ipad].net != m_view->m_sel_net )
											if( dis < (padRND/2 + dlg.m_def_via_w/2 + m_dr.pad_pad) )
												fail = 1;
									}
									else if( p->pin[ipad].net != m_view->m_sel_net )
									{
										SwellRect( &padRect, m_dr.pad_pad );
										if( RectsIntersection( viaRect, padRect ) >= 0 )
											fail = 1;
									}
									else if( RectsIntersection( viaRect, padRect ) >= 0 )
									{
										dl_element * pin_el = p->pin[ipad].dl_sel;
										int npts = 4;
										CPoint PTS[4];
										m_dlist->Get_Points( pin_el, PTS, &npts );
										if( npts == 4 )
										{
											for(int ipp=0; ipp<npts; ipp++ )
											{
												int xc=0, yc=0;
												int d;
												if( ipp == npts-1 )
													d= GetClearanceBetweenSegments(PTS[ipp].x, PTS[ipp].y, PTS[0].x, PTS[0].y, CPolyLine::STRAIGHT, 0, 
																		currX, currY, currX+10, currY+10, CPolyLine::STRAIGHT, dlg.m_def_via_w, 
																		m_dr.pad_trace*2, &xc, &yc );
												else
													d= GetClearanceBetweenSegments(PTS[ipp].x, PTS[ipp].y, PTS[ipp+1].x, PTS[ipp+1].y, CPolyLine::STRAIGHT, 0, 
																		currX, currY, currX+10, currY+10, CPolyLine::STRAIGHT, dlg.m_def_via_w, 
																		m_dr.pad_trace*2, &xc, &yc );
												if( d <= 0 )
													fail = 1;
											}
											if( fail == 0 )
												if( TestPolygon( currX, currY, PTS, npts ) )
													fail = 1;
										}
										else 
											fail = 1;
									}
									if( fail )
										break;
								}
							}
							if( fail )
								break;
						}
						for( cnet * n = m_nlist->GetFirstNet(); n; n = m_nlist->GetNextNet() )
						{
							if( n != m_view->m_sel_net )
								for( int iar=0; iar<n->nareas; iar++ )
								{
									CPolyLine * ap = n->area[iar].poly;
									if( ap->GetHatch() != CPolyLine::DIAGONAL_FULL )
										continue;

									// merge clearance
									int areaM = ap->GetMerge();
									int m_cl = 0;
									if( areaM >= 0 )
										m_cl = m_mlist->GetClearance( areaM );

									int w = ap->GetW();
									for( int icr=0; icr<ap->GetNumCorners(); icr++ )
									{
										int ss = ap->GetSideStyle(icr);
										int x1 = ap->GetX(icr);
										int y1 = ap->GetY(icr);
										int nxt = ap->GetIndexCornerNext(icr);
										int x2 = ap->GetX(nxt);
										int y2 = ap->GetY(nxt);
										int xc=0, yc=0;
										int d = GetClearanceBetweenSegments(x1, y1, x2, y2, ss, w, 
																			currX, currY, currX+10, currY+10, CPolyLine::STRAIGHT, dlg.m_def_via_w, 
																			m_dr.pad_trace*2, &xc, &yc );
										if( d < (m_cl?m_cl:m_dr.copper_copper) )
											fail = 1;
										if( fail == 0 )
											if( ap->TestPointInside( currX, currY ) )
												fail = 1;
									}
								}
							for( int icon=0; icon<n->nconnects; icon++ )
							{
								for( int iseg=0; iseg<n->connect[icon].nsegs; iseg++ )
								{
									int x1 = n->connect[icon].vtx[iseg].x;
									int y1 = n->connect[icon].vtx[iseg].y;
									int x2 = n->connect[icon].vtx[iseg+1].x;
									int y2 = n->connect[icon].vtx[iseg+1].y;
									int w = n->connect[icon].seg[iseg].width;
									if( n != m_view->m_sel_net )
									{
										int xc=0, yc=0;
										int d = GetClearanceBetweenSegments(x1, y1, x2, y2, CPolyLine::STRAIGHT, w, 
																			currX, currY, currX+10, currY+10, CPolyLine::STRAIGHT, dlg.m_def_via_w, 
																			m_dr.pad_trace*2, &xc, &yc );
										if( d < m_dr.pad_trace )
											fail = 1;
									}
									if( n->connect[icon].vtx[iseg+1].via_w )
									{
										int lim = n->connect[icon].vtx[iseg+1].via_w/2 + dlg.m_def_via_w/2;
										int d = Distance( currX, currY, x2, y2 );
										if( n != m_view->m_sel_net )
										{
											if( d < (lim + m_dr.pad_trace) )
												fail = 1;
										}
										else if( d < lim )
											fail = 1;
									}
									if( fail )
										break;
								}
								if( fail )
									break;
							}
							if( fail )
							{
								m_nlist->CancelNextNet();
								break;
							}
						}
						if( fail )
							continue;
						if( dlg.as_part == 0 )
						{
							CString refDes;
							do	{
								refDes.Format( "VIA%d", num );
								num++;
							} while( m_plist->GetPart( refDes ) );
							cpart * new_p = m_plist->Add( footprint, &refDes, currX, currY, 0, 0, 1, 0 );
							if( new_p )
							{
								count++;
								m_plist->ResizeRefText( new_p, 0, 0, 0, 0 );
								m_plist->ResizeValueText( new_p, 0, 0, 0, 0 );
								m_plist->DrawPart( new_p );
								if( pStart == NULL )
									pStart = new_p;
							}
						}
						else
						{
							count++;
							pstack.x_rel = currX - totalRect.left;
							pstack.y_rel = currY - totalRect.top;
							footprint->m_padstack.Add( pstack );
						}
					}
				}
			}
			if( count > 0 && dlg.as_part )
			{
				CString refDes;
				do	{
					refDes.Format( "VIA%d", num );
					num++;
				} while( m_plist->GetPart( refDes ) );
				cpart * new_p = m_plist->Add( footprint, &refDes, totalRect.left, totalRect.top, 0, 0, 1, 0 );
				if( new_p )
				{
					m_plist->ResizeRefText( new_p, 0, 0, 0, 0 );
					m_plist->ResizeValueText( new_p, 0, 0, 0, 0 );
					m_plist->DrawPart( new_p );
					pStart = new_p;
				}
			}
			if( pStart )
			{
				cnet * snet = m_view->m_sel_net;
				m_view->CancelSelection();
				ProjectModified( TRUE );
				int merge = -1;
				if( dlg.as_part == 0 )
					merge = m_mlist->AddNew( str_id, 0 );
				for( cpart * p=pStart; p; p=m_plist->GetNextPart(p) )
				{
					m_nlist->AddNetPin( snet, &p->ref_des, &pstack.name );
					id partId(ID_PART_DEF);
					m_view->NewSelect( p, &partId, FALSE, 0, 0 );
					p->m_merge = merge;
				}
				m_view->SaveUndoInfoForGroup( m_view->UNDO_GROUP_ADD, m_undo_list );
				m_view->SetCursorMode( CUR_GROUP_SELECTED );
				m_view->HighlightGroup();
			}
			else
				AfxMessageBox(G_LANGUAGE == 0 ? "No space for vias!":"Нет места для переходных отверстий!");
		}
		m_view->OnRangeCmds(NULL);
	}
}

void CFreePcbDoc::AddSymmetricalBlank()
{
	for (cpart* p = m_plist->GetFirstPart(); p; p = m_plist->GetNextPart(p))
	{
		if (p->ref_des.Find("|") >= 0)
		{
			AfxMessageBox(G_LANGUAGE ? "Нельзя сделать симметризацию, "\
				"если в проекте присутствуют детали в обозначении которых "\
				"используется символ скрытого текста - вертикальная черта" : \
				"Symmetrization cannot be performed if the project contains "\
				"parts in the designation of which the hidden text symbol - a vertical bar - is used.");
			return;
		}
	}
	CDlgAddSymmetricalBlank dlg;
	if (m_symmetric_x == 0 && m_symmetric_y == 0)
	{
		m_symmetric_x = m_space_x;
		m_symmetric_y = m_space_y;
	}
	dlg.Initialize(2, m_symmetric_x, m_symmetric_y, m_units);
	int ret = dlg.DoModal();
	if (ret == IDOK)
	{
		m_symmetric_x = dlg.m_dx;
		m_symmetric_y = dlg.m_dy;

		if (dlg.m_dx == 0)
			dlg.m_dx = 100;
		if (dlg.m_dy == 0)
			dlg.m_dy = 100;
		int mem_nl_comp = m_netlist_completed;
		int mem_pr_int = m_auto_interval; // autosave disable
		m_netlist_completed = 0;
		m_auto_interval = 0;
		//
		RECT pcbr = GetBoardRect();
		MarkLegalElementsForExport(this);
		SelectLegalElements(this);
		CString m1 = "pcb-1";
		CString m2 = "pcb-2";
		int merge0 = m_mlist->GetIndex(m1);
		if(merge0 == -1)
			merge0 = m_mlist->AddNew(m1, 0);
		m_view->MergeGroup(merge0);
		if (dlg.m_var == 2)
		{
			m_view->MoveOrigin(-pcbr.right-(dlg.m_dx/2), -pcbr.top-(dlg.m_dy/2));
			m_view->OnViewAllElements();
			m_view->UpdateWindow();
			m_view->NewSelectM(NULL, merge0);
			m_view->OnGroupCopy();
			m_view->OnGroupPaste(2, 1);
			m_view->TurnGroup();
			m_view->OnViewAllElements();
			m_view->UpdateWindow();
		}
		else if (dlg.m_var == 3)
		{
			m_view->RotateGroup(-90, 0);
			pcbr = GetBoardRect();
			m_view->MoveOrigin(-pcbr.right - (dlg.m_dy / 2), -pcbr.top - (dlg.m_dx / 2));
			m_view->OnViewAllElements();
			m_view->UpdateWindow();
			m_view->NewSelectM(NULL, merge0);
			m_view->OnGroupCopy();
			m_view->OnGroupPaste(2, 1);
			m_view->TurnGroup();
			m_view->OnViewAllElements();
			m_view->UpdateWindow();
			m_view->NewSelectM(NULL, merge0);
			int merge1 = m_mlist->GetIndex(m1);
			if (merge1 == -1)
				ASSERT(0);
			m_view->NewSelectM(NULL, merge1);
			m_view->RotateGroup(90,0);
			m_view->OnViewAllElements();
			m_view->UpdateWindow();
		}
		else if (dlg.m_var == 4)
		{
			m_view->MoveOrigin(-pcbr.right - (dlg.m_dx / 2), -pcbr.top - (dlg.m_dy / 2));
			m_view->OnViewAllElements();
			m_view->UpdateWindow();
			m_view->NewSelectM(NULL, merge0);
			m_view->OnGroupCopy();
			m_view->OnGroupPaste(2, 1);
			m_view->RotateGroup(-180, 0);
			m_view->OnViewAllElements();
			m_view->UpdateWindow();
			m_view->MoveGroup(0, pcbr.top - pcbr.bottom + dlg.m_dy,0);
			m_view->OnViewAllElements();
			m_view->UpdateWindow();
			m_view->NewSelectM(NULL, merge0);
			int merge1 = m_mlist->GetIndex(m1);
			if (merge1 == -1)
				ASSERT(0);
			m_view->NewSelectM(NULL, merge1);
			m_view->OnGroupCopy();
			m_view->OnGroupPaste(2, 1);
			m_view->TurnGroup();
			m_view->OnViewAllElements();
			m_view->UpdateWindow();
		}
		// restore 
		m_netlist_completed = mem_nl_comp;
		m_auto_interval = mem_pr_int;
	}
	m_view->OnRangeCmds(NULL);
}

void CFreePcbDoc::ChannelDuplication()
{
	if( m_view->m_sel_count == 0 )
	{
		AfxMessageBox(G_LANGUAGE == 0 ? 
			"First, select a group of parts (channel 1) that is already routed. We will duplicate it. In the dialog box, enter the designation suffix by which FreePcb2 will find the parts on the board. For example, if parts of channel 1 are designated R1A, R2A, D3A, and parts of channel 2 are designated R1B, R2B, D3B, then enter the suffix B":
			"Сначала выберите группу деталей (канал 1), которые уже трассированы, чтобы сообщить программе какую группу хотите продублировать. В диалоговом окне введите суффикс обозначений, по которому ПлатФорм будет находить детали на плате. Например, если детали трассированного канала 1 обозначены R1A, R2A, D3A, а детали канала 2 обозначены R1B, R2B, D3B, то введите суффикс B", MB_ICONINFORMATION);
		return;
	}
	CDlgEnterStr dlg;
	CString win_str = "Duplicate channel";
	CString ini_str = "Enter suffix of RefDes";
	dlg.Initialize( &win_str, &ini_str );
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		m_plist->ChannelDuplication( &dlg.m_str, &m_outline_poly, m_tlist );
		if( m_view->m_merge_show )
		{
			m_dlist->CancelHighLight(0,1);
			m_view->ShowMerges();
		}
		m_view->OnRangeCmds(NULL);
		ResetUndoState();
		m_nlist->OptimizeConnections();
	}
}

void CFreePcbDoc::OnFilePrint()
{
	CDlgPDFLayers dlg;
	dlg.Initialize( m_num_layers, m_pdf_vis, m_pdf_rgb, m_pdf_pin1, m_system_colors, m_pdf_use_font1, m_pdf_use_font2, m_pdf_use_font3 );
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		m_system_colors = dlg.m_sys_colors;
		m_pdf_use_font1 = dlg.m_use_font1;
		m_pdf_use_font2 = dlg.m_use_font2;
		m_pdf_use_font3 = dlg.m_use_font3;
		m_pdf_pin1 = dlg.m_margin;
		m_pdf_pin1 = min( m_pdf_pin1, 1.0 );

		RECT r_dsp = rect(0,0,0,0);
		if( m_view )
			if( m_view->m_sel_flags != PART_ONLY )
				if( m_view->m_cursor_mode == CUR_GROUP_SELECTED )
					r_dsp = m_dlist->GetHighlightedBounds(NULL);
		if( r_dsp.left || r_dsp.right )
			FilePrint( dlg.m_use_font1, dlg.m_use_font2, dlg.m_use_font3, FALSE, FALSE, &r_dsp );
		else
			FilePrint( dlg.m_use_font1, dlg.m_use_font2, dlg.m_use_font3, FALSE, FALSE, NULL );
		SaveOptions();
	}
}

void CFreePcbDoc::FilePrint( int m_height1, int m_height2, int m_height3, int m_no_hatch, int m_dsp_clrs, RECT * region )
{
	int m_height = max( m_height1, m_height2 );
	m_height = max( m_height, m_height3 );

	int rgb[MAX_LAYERS][3];
	int vis[MAX_LAYERS];
	if( m_dsp_clrs )
	{
		for( int layer=0; layer<MAX_LAYERS; layer++ )
		{
			rgb[layer][0] = m_rgb[layer][0];
			rgb[layer][1] = m_rgb[layer][1];
			rgb[layer][2] = m_rgb[layer][2];
			vis[layer] = m_vis[layer];
		}
	}
	else
	{
		for( int layer=0; layer<MAX_LAYERS; layer++ )
		{
			rgb[layer][0] = m_pdf_rgb[layer][0];
			rgb[layer][1] = m_pdf_rgb[layer][1];
			rgb[layer][2] = m_pdf_rgb[layer][2];
			vis[layer] = m_pdf_vis[layer];
		}
	}
	int m_pdf_font_i = 1;
	double PageWidth = 210.0/25.4;	
	double PageHeight = 297.0/25.4;
	CPDFdoc *pdf;
	pdf = cpdf_open(0, NULL);
	cpdf_init(pdf);
	cpdf_setTitle(pdf,m_name.GetBuffer());
	int mode;
	for( int page=0; page<2; page++ )
	{
		RECT r_dsp;
		if( region == NULL )
		{
			m_dlist->HighlightAll();
			r_dsp = m_dlist->GetHighlightedBounds(NULL);
			m_dlist->CancelHighLight();
			m_view->HighlightGroup();
		}
		else
			r_dsp = *region;
		if( r_dsp.right  - r_dsp.left > r_dsp.top - r_dsp.bottom )
			mode = LANDSCAPE;
		else
			mode = PORTRAIT;
		double k_page_2 = (float)(r_dsp.right + r_dsp.left)/(float)m_pcbu_per_wu;
		cpdf_pageInit(pdf, page+1, mode, A4, A4);		// page orientation 
		cpdf_setlinecap( pdf, 1 );	// round end-caps
		const double clr_pdf = 1.0/255.0;
		float gap = 0.1;
		{
			cpdf_setrgbcolorFill( pdf,	clr_pdf*(float)rgb[LAY_BACKGND][0], 
										clr_pdf*(float)rgb[LAY_BACKGND][1], 
										clr_pdf*(float)rgb[LAY_BACKGND][2] );
			cpdf_setrgbcolorStroke(pdf, clr_pdf*(float)rgb[LAY_BACKGND][0], 
										clr_pdf*(float)rgb[LAY_BACKGND][1], 
										clr_pdf*(float)rgb[LAY_BACKGND][2] );
			cpdf_setlinewidth( pdf, 1.0 );
			cpdf_newpath( pdf );
			cpdf_moveto( pdf, gap, gap );
			cpdf_lineto( pdf, gap, PageHeight - gap );
			cpdf_lineto( pdf, PageWidth - gap, PageHeight - gap );
			cpdf_lineto( pdf, PageWidth - gap, gap );
			cpdf_lineto( pdf, gap, gap );
			cpdf_fill( pdf );
			cpdf_closepath( pdf );	
		}
		double pdf_w = PageWidth - 2*gap;
		double pdf_h = PageHeight - 2*gap;
		const double k_pdf = 1.0/2555.0;
		
		// rectangles
		float cx_pdf = pdf_w/2.0 + gap;
		float cy_pdf = pdf_h/2.0 + gap;
		float cx_dsp = ((float)r_dsp.left + (float)r_dsp.right)/2.0/(float)m_pcbu_per_wu;
		float cy_dsp = ((float)r_dsp.top + (float)r_dsp.bottom)/2.0/(float)m_pcbu_per_wu;
		float max_x_pdf = PageWidth - gap;
		float max_y_pdf = PageHeight - gap;
		float max_x_dsp = (float)r_dsp.right/(float)m_pcbu_per_wu;
		float max_y_dsp = (float)r_dsp.top/(float)m_pcbu_per_wu;
		double k1, k2;
		if( mode == LANDSCAPE )
		{	
			k1 = (max_y_dsp - cy_dsp)/(max_x_pdf - cx_pdf);
			k2 = (max_x_dsp - cx_dsp)/(max_y_pdf - cy_pdf);
		}
		else
		{
			k1 = (max_x_dsp - cx_dsp)/(max_x_pdf - cx_pdf);
			k2 = (max_y_dsp - cy_dsp)/(max_y_pdf - cy_pdf);
		}
		float format = 297.0/210.0 - 1;
		float swell = max(k1,k2)/min(k1,k2) - 1;
		k1 = max( k1, k2 );
		//
		// draw dl_elements
		BOOL pdf_use_font1 = (m_height1>0);
		BOOL pdf_use_font2 = (m_height2>0);
		BOOL pdf_use_font3 = (m_height3>0);
		//
		RectArray RectA;
		RectA.Clear();
		RectA.SetStep( max( m_part_grid_spacing, NM_PER_MIL ) );
		//
		for( int order=(MAX_LAYERS-1); order>=0; order-- )
		{
			int color_layer;
			int layer = m_dlist->GetPDFLayer( order, page, &color_layer );
			if( layer == LAY_SELECTION )
				continue;
			if( m_pdf_vis[color_layer] == 0 )
				continue;
			//
			float r = clr_pdf*(float)rgb[color_layer][0];
			float g = clr_pdf*(float)rgb[color_layer][1];
			float b = clr_pdf*(float)rgb[color_layer][2];
			float r_tone = clr_pdf*(float)rgb[LAY_BOARD_OUTLINE][0]*0.8;
			float g_tone = clr_pdf*(float)rgb[LAY_BOARD_OUTLINE][1]*0.8;
			float b_tone = clr_pdf*(float)rgb[LAY_BOARD_OUTLINE][2]*0.8;
			if(( layer == LAY_SM_TOP && page == 0 ) || ( layer == LAY_SM_BOTTOM && page == 1 ))
			{
				r = r_tone;
				g = g_tone;
				b = b_tone;
			}
			cpdf_setrgbcolorFill( pdf,	r, g, b );
			cpdf_setrgbcolorStroke(pdf, r, g, b );
			for(int step=0; step<2; step++ )
			{
				dl_element * el;
				dl_element * substitution = NULL;
				float rpad;
				float gpad;
				float bpad;
				for( dl_element * c_el=m_dlist->Get_Start()->next; c_el->next; c_el=(substitution?c_el:c_el->next) )
				{
					el = c_el;
					if( el->visible == 0 )
						continue;
					if( getbit( el->layers_bitmap, layer ) == 0 )
						continue;
					if( el == m_dlist->Get_End() )
						continue;
					if( el->id.type == ID_DRC )
						continue;
					if( el->id.type == ID_MERGE && page )
						continue;
					if( m_no_hatch && el->id.sst == ID_HATCH )
						continue;
					if( layer == LAY_HILITE )
					{
						if( el->id.type == ID_MERGE )
							continue;
						else if( el->map_orig_layer )
							if( getbit( el->map_orig_layer, LAY_SM_TOP+page ) == 0 )
								if( getbit( el->map_orig_layer, LAY_TOP_COPPER+page ) == 0 )
									continue;
					}
					if( region )
					{
						RECT el_r;
						m_dlist->Get_Rect( el, &el_r );
						if(( mode == LANDSCAPE && swell > format ) || 
						   ( mode == PORTRAIT && swell < format ) )
						{
							double k3 = (region->top-region->bottom);
							el_r.top += (k3*swell/2.0);
							el_r.bottom -= (k3*swell/2.0);
						}
						else
						{
							double k3 = (region->right-region->left);
							el_r.left -= (k3*swell/2.0);
							el_r.right += (k3*swell/2.0);
						}
						if( RectsIntersection( *region, el_r ) == -1 )
							continue;
					}
					if( substitution )
					{
						el = substitution;
						substitution = NULL;	
						if( m_pdf_vis[LAY_SM_TOP] )
						{
							cpdf_setrgbcolorFill( pdf,	rpad, gpad, bpad );
							cpdf_setrgbcolorStroke(pdf, rpad, gpad, bpad );
						}
					}
					// PAD
					else if( el->id.st == ID_PAD && ((layer == LAY_TOP_COPPER && page == 0) || (layer == LAY_BOTTOM_COPPER && page == 1)) )
					{
						if( step == 0 )
							continue;
						//
						rpad = clr_pdf*(float)rgb[LAY_SM_TOP][0];
						gpad = clr_pdf*(float)rgb[LAY_SM_TOP][1];
						bpad = clr_pdf*(float)rgb[LAY_SM_TOP][2];
						if( m_pdf_vis[LAY_SM_TOP] )
						{
							cpdf_setrgbcolorFill( pdf,	rpad, gpad, bpad );
							cpdf_setrgbcolorStroke(pdf, rpad, gpad, bpad );
						}
						if( el->ptr )
						{
							cpart * get_part = (cpart*)el->ptr;
							if( get_part )
								if( get_part->shape )
								{
									pad * Pad = NULL;
									pad * OppositePad = NULL;
									if( ( layer == LAY_TOP_COPPER && get_part->side == 0 ) ||
										( layer == LAY_BOTTOM_COPPER && get_part->side == 1 ) )
									{
										Pad = &get_part->shape->m_padstack[el->id.i].top_mask;
										OppositePad = &get_part->shape->m_padstack[el->id.i].bottom_mask;
									}
									else
									{
										Pad = &get_part->shape->m_padstack[el->id.i].bottom_mask;
										OppositePad = &get_part->shape->m_padstack[el->id.i].top_mask;
									}
									if( Pad->shape == PAD_NONE )
									{
										cpdf_setrgbcolorFill( pdf,	r, g, b );
										cpdf_setrgbcolorStroke(pdf, r, g, b );
									}
									else if( Pad->shape != PAD_DEFAULT )
									{
										cpdf_setrgbcolorFill( pdf,	r, g, b );
										cpdf_setrgbcolorStroke(pdf, r, g, b );
										if( ( layer == LAY_TOP_COPPER ))//&& get_part->side == 0 ) ||
										//( layer == LAY_BOTTOM_COPPER && get_part->side == 1 ) )
										{
											if( get_part->pin[el->id.i].dl_els[1] )
												substitution = get_part->pin[el->id.i].dl_els[1];
										}
										else if( get_part->pin[el->id.i].dl_els.GetSize() > 2 )
										{
											if( OppositePad->shape == PAD_NONE )
												if( get_part->pin[el->id.i].dl_els[2] )
													substitution = get_part->pin[el->id.i].dl_els[2];
											if( OppositePad->shape != PAD_NONE && get_part->pin[el->id.i].dl_els.GetSize() > 3 )
												if( get_part->pin[el->id.i].dl_els[3] )
													substitution = get_part->pin[el->id.i].dl_els[3];
										}
										if( substitution )
										{
											RECT rct_1=rect(0,0,0,0), rct_2=rect(0,0,0,0);
											m_dlist->Get_Rect( el, &rct_1 );
											m_dlist->Get_Rect( substitution, &rct_2 );
											if( rct_1.right-rct_1.left < rct_2.right-rct_2.left )
											{
												dl_element * swap_el = el;
												el = substitution;
												substitution = swap_el;
												cpdf_setrgbcolorFill( pdf,	r_tone, g_tone, b_tone );
												cpdf_setrgbcolorStroke(pdf, r_tone, g_tone, b_tone );
											}
										}
									}
									if( m_pdf_pin1 > 0.01 )// draw firs
									{
										int Ex2Pin = 0;
										if( get_part->shape->GetNumPins( 2+Ex2Pin ) > (1+Ex2Pin) )
										{
											CString * pin_name = &get_part->shape->m_padstack[el->id.i].name;
											BOOL isPIN1 = FALSE;
											if( pin_name->GetLength() == 1 )
												if( pin_name->FindOneOf( "1Aa" ) == 0 )
													isPIN1 = TRUE;
											if( pin_name->Compare("A1") == 0 )
												isPIN1 = TRUE;
											if( isPIN1 )
											{
												if( substitution )
												{
													rpad *= m_pdf_pin1;
													gpad *= m_pdf_pin1;
													bpad *= m_pdf_pin1;
												}
												else
												{
													cpdf_setrgbcolorFill( pdf,	rpad*m_pdf_pin1, gpad*m_pdf_pin1, bpad*m_pdf_pin1 );
													cpdf_setrgbcolorStroke(pdf, rpad*m_pdf_pin1, gpad*m_pdf_pin1, bpad*m_pdf_pin1 );
												}
											}
										}
									}
								}
						}
					}
					else if( step == 1 )
						continue;
					//
					int eR = (pdf_use_font1 == 0 || el->id.st != ID_REF_TXT);
					int eV = (pdf_use_font2 == 0 || el->id.st != ID_VALUE_TXT);
					bool EN_TXT = (eR && eV);
					float w = (float)el->el_w*(70.0)/k1;
					cpdf_setlinewidth( pdf, w );
					CArray<CPoint> * PTS = m_dlist->Get_Points( el, NULL, 0 );
					if( el->gtype == DL_LINE || (el->gtype == DL_LINES_ARRAY && EN_TXT) )
					{
						if( el->id.st != ID_BOARD )
						{
							int sz = PTS->GetSize();			
							for( int ii=0; ii+1<sz; ii+=2 )
							{
								double xi = PTS->GetAt(ii).x - cx_dsp;
								double xf = PTS->GetAt(ii+1).x - cx_dsp;
								double yi = PTS->GetAt(ii).y - cy_dsp;
								double yf = PTS->GetAt(ii+1).y - cy_dsp;
								if( page )
								{
									xi = (float)k_page_2 - (float)PTS->GetAt(ii).x - cx_dsp;
									xf = (float)k_page_2 - (float)PTS->GetAt(ii+1).x - cx_dsp;
								}
								if( PTS->GetAt(ii).x == PTS->GetAt(ii+1).x && PTS->GetAt(ii).y == PTS->GetAt(ii+1).y )
									continue;
								xi /= k1;
								xf /= k1;
								yi /= k1;
								yf /= k1;
								if( mode == LANDSCAPE )
								{
									xi = -xi;
									xf = -xf;
									xi += cy_pdf;
									xf += cy_pdf;
									yi += cx_pdf;
									yf += cx_pdf;
								}
								else
								{
									xi += cx_pdf;
									xf += cx_pdf;
									yi += cy_pdf;
									yf += cy_pdf;
								}	
								cpdf_newpath( pdf );
								if( mode == LANDSCAPE )
								{	
									cpdf_moveto( pdf, yi, xi );
									cpdf_lineto( pdf, yf, xf );
								}
								else
								{
									cpdf_moveto( pdf, xi, yi );
									cpdf_lineto( pdf, xf, yf );
								}
								cpdf_stroke( pdf );
								cpdf_closepath( pdf );	
							}
						}
					}
					if( el->gtype == DL_CIRC || el->gtype == DL_HOLLOW_CIRC || (el->gtype == DL_HOLE && layer == LAY_PAD_THRU) )
					{
						RECT el_r;
						m_dlist->Get_Rect( el, &el_r );
						float r = (float)(el_r.right - el_r.left)/2.0/(float)m_pcbu_per_wu;
						double x = (float)(el_r.right + el_r.left)/2.0/(float)m_pcbu_per_wu - cx_dsp;
						double y = (float)(el_r.top + el_r.bottom)/2.0/(float)m_pcbu_per_wu - cy_dsp;
						if( page )
							x = (float)k_page_2 - (float)(el_r.right + el_r.left)/2.0/(float)m_pcbu_per_wu - cx_dsp;
						x /= k1;
						y /= k1;
						r /= k1;
						if( mode == LANDSCAPE )
						{
							x = -x;
							x += cy_pdf;
							y += cx_pdf;
						}
						else
						{
							x += cx_pdf;
							y += cy_pdf;
						}	
						cpdf_newpath( pdf );
						if( mode == LANDSCAPE )
							cpdf_circle( pdf, y, x, r );
						else
							cpdf_circle( pdf, x, y, r );
						if( el->gtype == DL_HOLLOW_CIRC )
							cpdf_stroke( pdf );
						else
							cpdf_fill( pdf );
						cpdf_closepath( pdf );	
					}
					else if( el->gtype == DL_RECT || el->gtype == DL_HOLLOW_RECT )
					{
						RECT el_r;
						m_dlist->Get_Rect( el, &el_r );
						double x = (float)(el_r.right)/(float)m_pcbu_per_wu - cx_dsp;
						double y = (float)(el_r.bottom)/(float)m_pcbu_per_wu - cy_dsp;
						if( page )
							x = (float)k_page_2 - (float)(el_r.left)/(float)m_pcbu_per_wu - cx_dsp;
						double w = (float)(el_r.right - el_r.left)/(float)m_pcbu_per_wu;
						double h = (float)(el_r.top - el_r.bottom)/(float)m_pcbu_per_wu;
						x /= k1;
						y /= k1;
						w /= k1;
						h /= k1;
						if( mode == LANDSCAPE )
						{
							x = -x;
							x += cy_pdf;
							y += cx_pdf;
							w = w+h;
							h = w-h;
							w = w-h;
						}
						else
						{
							x = (float)(el_r.left)/(float)m_pcbu_per_wu - cx_dsp;
							if( page )
								x = (float)k_page_2 - (float)(el_r.right)/(float)m_pcbu_per_wu - cx_dsp;
							x /= k1;
							x += cx_pdf;
							y += cy_pdf;
						}	
						cpdf_newpath( pdf );
						if( mode == LANDSCAPE )
							cpdf_rect( pdf, y, x, w, h );
						else
							cpdf_rect( pdf, x, y, w, h );
						if( el->gtype == DL_HOLLOW_RECT )
							cpdf_stroke( pdf );
						else
							cpdf_fill( pdf );
						cpdf_closepath( pdf );	
					}
					else if( el->gtype == DL_RRECT || el->gtype == DL_HOLLOW_RRECT )
					{
						RECT el_r;
						m_dlist->Get_Rect( el, &el_r );
						double x = (float)(el_r.right + el_r.left)/2.0/(float)m_pcbu_per_wu - cx_dsp;
						double y = (float)(el_r.top + el_r.bottom)/2.0/(float)m_pcbu_per_wu - cy_dsp;
						if( page )
							x = (float)k_page_2 - (float)(el_r.right + el_r.left)/2.0/(float)m_pcbu_per_wu - cx_dsp;
						double w = (float)(el_r.right - el_r.left)/(float)m_pcbu_per_wu;
						double h = (float)(el_r.top - el_r.bottom)/(float)m_pcbu_per_wu;
						double r = (el->el_w);
						x /= k1;
						y /= k1;
						w /= k1;
						h /= k1;
						r /= k1;
						if( mode == LANDSCAPE )
						{
							x = -x;
							x += cy_pdf;
							y += cx_pdf;
						}
						else
						{
							w = w+h;
							h = w-h;
							w = w-h;
							x += cx_pdf;
							y += cy_pdf;
						}	
						cpdf_newpath( pdf );
						if( mode == LANDSCAPE )
						{
							cpdf_moveto( pdf, y-h/2.0, x+w/2.0-r );
							cpdf_arc( pdf, y-h/2.0+r, x+w/2.0-r, r, 180.0, 90.0, 0 );
							cpdf_lineto( pdf, y+h/2.0-r, x+w/2.0 );
							cpdf_arc( pdf, y+h/2.0-r, x+w/2.0-r, r, 90.0, 0.0, 0 );
							cpdf_lineto( pdf, y+h/2.0, x-w/2.0+r );
							cpdf_arc( pdf, y+h/2.0-r, x-w/2.0+r, r, 360.0, 270.0, 0 );
							cpdf_lineto( pdf, y-h/2.0+r, x-w/2.0 );
							cpdf_arc( pdf, y-h/2.0+r, x-w/2.0+r, r, 270.0, 180.0, 0 );
						}
						else
						{
							cpdf_moveto( pdf, x-h/2.0, y+w/2.0-r );
							cpdf_arc( pdf, x-h/2.0+r, y+w/2.0-r, r, 180.0, 90.0, 0 );
							cpdf_lineto( pdf, x+h/2.0-r, y+w/2.0 );
							cpdf_arc( pdf, x+h/2.0-r, y+w/2.0-r, r, 90.0, 0.0, 0 );
							cpdf_lineto( pdf, x+h/2.0, y-w/2.0+r );
							cpdf_arc( pdf, x+h/2.0-r, y-w/2.0+r, r, 360.0, 270.0, 0 );
							cpdf_lineto( pdf, x-h/2.0+r, y-w/2.0 );
							cpdf_arc( pdf, x-h/2.0+r, y-w/2.0+r, r, 270.0, 180.0, 0 );
						}
						cpdf_closepath( pdf );
						if( el->gtype == DL_HOLLOW_RRECT )
							cpdf_stroke( pdf );
						else
							cpdf_fill( pdf );
					}
					else if( el->gtype == DL_POLYLINE || el->gtype == DL_POLYGON )
					{
						float r0 = clr_pdf*255.0;
						float g0 = clr_pdf*255.0;
						float b0 = clr_pdf*255.0;
						if( el->id.st == ID_BOARD && el->id.sst == ID_HOLE )
							cpdf_setrgbcolorFill( pdf,	r0, g0, b0 );
						cpdf_newpath( pdf );
						int sz = PTS->GetSize();
						float f1=0,f2=0;
						for( int ii=0; ii<sz; ii++ )
						{
							double xi = (float)PTS->GetAt(ii).x - cx_dsp;
							double yi = (float)PTS->GetAt(ii).y - cy_dsp;
							if( page )
								xi = (float)k_page_2 - (float)PTS->GetAt(ii).x - cx_dsp;
							xi /= k1;
							yi /= k1;
							if( mode == LANDSCAPE )
							{
								xi = -xi;
								xi += cy_pdf;
								yi += cx_pdf;
							}
							else
							{
								xi += cx_pdf;
								yi += cy_pdf;
							}		
							if( mode == LANDSCAPE )
							{
								if( ii == 0 )
									cpdf_moveto( pdf, yi, xi );
								else
								{
									cpdf_lineto( pdf, yi, xi );
									cpdf_moveto( pdf, yi, xi );
								}
								if( ii == 0 )
								{
									f1 = yi;
									f2 = xi;
								}
							}
							else
							{
								if( ii == 0 )
									cpdf_moveto( pdf, xi, yi );
								else
								{
									cpdf_lineto( pdf, xi, yi );	
									cpdf_moveto( pdf, xi, yi );
								}
								if( ii == 0 )
								{
									f1 = xi;
									f2 = yi;
								}
							}	
						}
						if( el->gtype == DL_POLYGON )
							cpdf_lineto( pdf, f1, f2 );
						cpdf_stroke( pdf );
						if( el->gtype == DL_POLYGON )
						{
							for( int ii=0; ii<sz; ii++ )
							{
								double xi = (float)PTS->GetAt(ii).x - cx_dsp;
								double yi = (float)PTS->GetAt(ii).y - cy_dsp;
								if( page )
									xi = (float)k_page_2 - (float)PTS->GetAt(ii).x - cx_dsp;
								xi /= k1;
								yi /= k1;
								if( mode == LANDSCAPE )
								{
									xi = -xi;
									xi += cy_pdf;
									yi += cx_pdf;
								}
								else
								{
									xi += cx_pdf;
									yi += cy_pdf;
								}		
								if( mode == LANDSCAPE )
								{
									if( ii == 0 )
										cpdf_moveto( pdf, yi, xi );
									else
										cpdf_lineto( pdf, yi, xi );
								}
								else
								{
									if( ii == 0 )
										cpdf_moveto( pdf, xi, yi );
									else
										cpdf_lineto( pdf, xi, yi );
								}	
							}
							cpdf_fill( pdf );
						}
						cpdf_closepath( pdf );
						if( el->id.st == ID_BOARD && el->id.sst == ID_HOLE )
							cpdf_setrgbcolorFill( pdf,	r, g, b );
					}
					else if(( el->gtype == DL_ARC_CW || el->gtype == DL_ARC_CCW ) && el->id.st != ID_BOARD )
					{
						int gTYPE = el->gtype;
						if( page )
							if( el->gtype == DL_ARC_CW )
								gTYPE = DL_ARC_CCW;
							else
								gTYPE = DL_ARC_CW;
						const double MagicBezier = 0.2761423749154;
						int sz = PTS->GetSize();			
						for( int ii=0; ii+1<sz; ii+=2 )
						{
							double xi = PTS->GetAt(ii).x - cx_dsp;
							double xf = PTS->GetAt(ii+1).x - cx_dsp;
							if( page )
							{
								xi = (float)k_page_2 - (float)PTS->GetAt(ii).x - cx_dsp;
								xf = (float)k_page_2 - (float)PTS->GetAt(ii+1).x - cx_dsp;
							}
							double yi = PTS->GetAt(ii).y - cy_dsp;
							double yf = PTS->GetAt(ii+1).y - cy_dsp;
							if( PTS->GetAt(ii).x == PTS->GetAt(ii+1).x && PTS->GetAt(ii).y == PTS->GetAt(ii+1).y )
								continue;
							xi /= k1;
							xf /= k1;
							yi /= k1;
							yf /= k1;
							if( mode == LANDSCAPE )
							{
								xi = -xi;
								xf = -xf;
								xi += cy_pdf;
								xf += cy_pdf;
								yi += cx_pdf;
								yf += cx_pdf;
							}
							else
							{
								xi += cx_pdf;
								xf += cx_pdf;
								yi += cy_pdf;
								yf += cy_pdf;
							}	
							// ellipse quadrant, clockwise, start vertical
							double x1 = xi;
							double y1 = yi + (yf - yi)*2.0*MagicBezier;
							double x2 = xf - (xf - xi)*2.0*MagicBezier;
							double y2 = yf;
							if	(
								(((xf>xi && yf<yi) || (xf<xi && yf>yi) ) && gTYPE-mode == DL_ARC_CW) ||
								(((xf>xi && yf>yi) || (xf<xi && yf<yi) ) && gTYPE+mode == DL_ARC_CCW)
								)
							{
								// ellipse quadrant, clockwise, start horizontal
								x1 = xi + (xf - xi)*2.0*MagicBezier;
								y1 = yi;
								x2 = xf;
								y2 = yf - (yf - yi)*2.0*MagicBezier;
							}
							cpdf_newpath( pdf );
							if( mode == LANDSCAPE )
							{	
								cpdf_moveto( pdf, yi, xi );
								cpdf_curveto( pdf, y1, x1, y2, x2, yf, xf );
							}
							else
							{
								cpdf_moveto( pdf, xi, yi );
								cpdf_curveto( pdf, x1, y1, x2, y2, xf, yf );
							}
							cpdf_stroke( pdf );
							cpdf_closepath( pdf );	
						}
					}
					if( el->id.st == ID_PAD )
					{
						cpdf_setrgbcolorFill( pdf,	r, g, b );
						cpdf_setrgbcolorStroke(pdf, r, g, b );
					}
				}
				BOOL b = ((layer == LAY_TOP_COPPER && page == 0) || (layer == LAY_BOTTOM_COPPER && page == 1));
				if( !b )
					break;
			}
			
		}
		// draw texts
		//( m_pdf_use_font1 || m_pdf_use_font2 )
		{
			cpdf_setrgbcolorFill( pdf,	clr_pdf*1.0, 
										clr_pdf*1.0, 
										clr_pdf*1.0 );
			cpdf_setrgbcolorStroke(pdf, clr_pdf*1.0, 
										clr_pdf*1.0, 
										clr_pdf*1.0 );
			//
			float TextHeightPts = (float)m_height/(float)m_pcbu_per_wu/k1*100.0;
			cpdf_setFont(pdf, cpdf_fontnamelist[m_pdf_font_i], "UniCNS-UCS-2-H", TextHeightPts);
			for( cpart * part=m_plist->GetFirstPart(); part; part=m_plist->GetNextPart(part) )
			{
				if( page && part->side == 0 )
					continue;
				if( page == 0 && part->side )
					continue;
				if( part->shape == NULL )
					continue;
				if( part->shape->GetNumPins() == 1 )
					continue;

				int cnt=0;
				if( pdf_use_font1 && (part->m_ref_vis || part->m_ref_size) )
					cnt++;
				if( pdf_use_font2 && (part->m_value_vis || part->m_value_size) && part->value.GetLength() )
					cnt++;
				if( pdf_use_font3 && part->shape->m_package.GetLength() )
					cnt++;

				int sh_ini = 0;
				if( cnt == 1 )
					sh_ini = -m_height/3;
				else if( cnt == 2 )
					sh_ini = m_height/2 - m_height/5;
				else if( cnt == 3 )
					sh_ini = m_height;

				int real_step = 0;
				for( int Step=0; Step<3; Step++ )
				{
					CString str = part->ref_des;
					if( str.Left(3) == "VIA" )
						break;
					if( Step == 1 )
						str = part->value;
					else if( Step == 2 )
						str = part->shape->m_package;

					if( Step == 0 )
					{
						if( part->m_ref_size == 0 && part->m_ref_vis == 0 )
							continue;
					}
					if( Step == 1 ) 
					{
						if( part->m_value_size == 0 && part->m_value_vis == 0 )
							continue;
						if( part->value.GetLength() == 0 )
							continue;
					}
					if( Step == 2 ) 
					{
						if( part->shape->m_package.GetLength() == 0 )
							continue;
					}
					// set text 
					// visible
					if( ( pdf_use_font1 && Step == 0 ) || 
						( pdf_use_font2 && Step == 1 ) ||
						( pdf_use_font3 && Step == 2 ))
						cpdf_setTextRenderingMode(pdf, TEXT_FILL);
					else
						cpdf_setTextRenderingMode(pdf, TEXT_INVISIBLE);	
					if( Step == 0 )
					{
						if( pdf_use_font1 )
							real_step++;
						cpdf_beginText(pdf, pdf_use_font1?TEXT_FILL:TEXT_INVISIBLE);
					}
					else if( Step == 1 )
					{
						if( pdf_use_font2 )
							real_step++;
						cpdf_beginText(pdf, pdf_use_font2?TEXT_FILL:TEXT_INVISIBLE);
					}
					else 
					{
						if( pdf_use_font3 )
							real_step++;
						cpdf_beginText(pdf, pdf_use_font3?TEXT_FILL:TEXT_INVISIBLE);
					}
					//
					//
					int ip = str.Find("|");
					if( ip > 0 )
						str = str.Left(ip);
					//
					RECT partR;
					m_plist->GetPartBoundingRect( part, &partR );
					//
					int m_shift1 = m_height*9/20*str.GetLength();
					int m_shift2 = sh_ini - ((m_height*3/2)*(real_step-1));//
					//
					double x, y;
					float midX = (partR.left+partR.right)/2;
					float midY = (partR.top+partR.bottom)/2;
					float m_angle;			
					if( (partR.right-partR.left) < (partR.top-partR.bottom) )
					{
						// rectangle
						RECT r = rect( midX-m_shift2, midY-m_shift1, midX-m_height-m_shift2, midY+m_shift1 );
						if( page )
							r = rect( midX+m_shift2, midY-m_shift1, midX+m_height+m_shift2, midY+m_shift1 );
						SwellRect( &r, NM_PER_MIL );
						CPoint Correct(0,0);
						if( ( pdf_use_font1 && Step == 0 ) || 
							( pdf_use_font2 && Step == 1 ) ||
							( pdf_use_font3 && Step == 2 ) )
							Correct = RectA.CorrectAdd( &r );

						if( ( Step == 0 && pdf_use_font1 == 0 ) ||
							( Step == 1 && pdf_use_font2 == 0 ) ||
							( Step == 2 && pdf_use_font3 == 0 ))
							Correct.SetPoint(m_height*Step,m_height*Step);

						if( page )
							x = (float)k_page_2 - (float)(midX+m_shift2+Correct.x)/(float)m_pcbu_per_wu - cx_dsp;
						else
							x = (float)(midX-m_shift2+Correct.x)/(float)m_pcbu_per_wu - cx_dsp;
						y = (float)(midY-m_shift1+Correct.y)/(float)m_pcbu_per_wu - cy_dsp;
						m_angle = 270.0;
					}
					else
					{
						// rectangle
						RECT r = rect( midX-m_shift1, midY+m_shift2, midX+m_shift1, midY+m_height+m_shift2 );
						//if( page )
						//	r = rect( midX+m_shift1, midY+m_shift2, midX-m_shift1, midY+m_height+m_shift2 );
						SwellRect( &r, NM_PER_MIL );
						CPoint Correct(0,0);
						if( ( pdf_use_font1 && Step == 0 ) || 
							( pdf_use_font2 && Step == 1 ) ||
							( pdf_use_font3 && Step == 2 ) )
							Correct = RectA.CorrectAdd( &r );

						if( ( Step == 0 && pdf_use_font1 == 0 ) ||
							( Step == 1 && pdf_use_font2 == 0 ) ||
							( Step == 2 && pdf_use_font3 == 0 ))
							Correct.SetPoint(m_height*Step,m_height*Step);

						if( page )
							x = (float)k_page_2 - (float)(midX+m_shift1+Correct.x)/(float)m_pcbu_per_wu - cx_dsp;
						else
							x = (float)(midX-m_shift1+Correct.x)/(float)m_pcbu_per_wu - cx_dsp;
						y = (float)(midY+m_shift2+Correct.y)/(float)m_pcbu_per_wu - cy_dsp;
						m_angle = 0.0;
					}
					x /= k1;
					y /= k1;
					if( mode == LANDSCAPE )
					{
						x = -x;
						x += cy_pdf;
						y += cx_pdf;
					}
					else
					{
						x += cx_pdf;
						y += cy_pdf;
					}	
					///cpdf_newpath( pdf );
					if( mode == LANDSCAPE )
						cpdf_text(pdf, y, x, 270.0-m_angle, str );
					else
						cpdf_text(pdf, x, y, 360.0-m_angle, str );
					//
					///cpdf_closepath( pdf );
					cpdf_endText(pdf);
				}
			}	
		}
	}
	cpdf_finalizeAll(pdf);
	int rf = m_pcb_full_path.ReverseFind('\\');
	if( rf <= 0 )
		rf = m_pcb_full_path.GetLength();
	CString path = m_pcb_full_path.Left(rf);
	CString pdf_file = path + "\\related_files\\" +  m_name + ".pdf";
	int err = cpdf_savePDFmemoryStreamToFile(pdf, pdf_file );
	if( err == -1 )
	{
		if( !m_dlg_log )
		{
			AfxMessageBox(G_LANGUAGE == 0 ? 
				"Error: Unable to write file\nIt may be read-only or open in another application":
				"Ошибка: Невозможно записать файл. Возможно, он доступен только для чтения или открыт в другом приложении", MB_OK);
		}
		else
		{
			CString log_message = "*** Error: unable to write file ***\r\n";
			m_dlg_log->AddLine( log_message );
		}
	}
	cpdf_close(pdf);
	ShellExecute(	NULL,"open", pdf_file, NULL, m_path_to_folder, SW_SHOWNORMAL );
}

void CFreePcbDoc::OnProtection()
{
	CDlgProtection dlg;
	dlg.Ini( this );
	dlg.DoModal();
}

void CFreePcbDoc::OnInvertColors()
{
	m_dlist->Images.InvertColors();
	m_view->OnRangeCmds(NULL);
}

void CFreePcbDoc::OnSwapImages()
{
	m_dlist->Images.Mirror();
	m_view->OnRangeCmds(NULL);
}

void CFreePcbDoc::OnAddTopImage()
{
	CString filename = RunFileDialog( 1, "img" ); 
	if ( filename.GetLength() )
	{
		CString new_path = m_path_to_folder + "\\related_files";
		_mkdir( new_path );
		new_path += "\\pictures";
		_mkdir( new_path );
		new_path += "\\" + m_pcb_filename + "1";
		CopyFile( filename, new_path, 0 );
		m_dlist->Images.Load( &new_path, 0 );
		m_dlist->Images.UpdateBoardOutline();
		m_view->OnRangeCmds(NULL);
	}
}

void CFreePcbDoc::OnAddBottomImage()
{
	CString filename = RunFileDialog( 1, "img" ); 
	if ( filename.GetLength() )
	{
		CString new_path = m_path_to_folder + "\\related_files";
		_mkdir( new_path );
		new_path += "\\pictures";
		_mkdir( new_path );
		new_path += "\\" + m_pcb_filename + "2";
		CopyFile( filename, new_path, 0 );
		m_dlist->Images.Load( &new_path, 1 );
		m_dlist->Images.UpdateBoardOutline();
		m_view->OnRangeCmds(NULL);
	}
}

void CFreePcbDoc::OnDeleteTopImage()
{
	if( AfxMessageBox(G_LANGUAGE == 0 ? 
		"Are you sure you want to unpin the picture? (this action cannot be undone)":
		"Вы уверены, что хотите открепить изображение? (это действие нельзя отменить)", MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		m_dlist->Images.Load( NULL, 0 );
		CString path = m_path_to_folder + "\\related_files\\pictures\\" + m_pcb_filename + "1";
		DeleteFile( path );
	}
	m_view->OnRangeCmds(NULL);
}

void CFreePcbDoc::OnDeleteBottomImage()
{
	if( AfxMessageBox(G_LANGUAGE == 0 ? 
		"Are you sure you want to unpin the picture? (this action cannot be undone)":
		"Вы уверены, что хотите открепить изображение? (это действие нельзя отменить)", MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		m_dlist->Images.Load( NULL, 1 );
		CString path = m_path_to_folder + "\\related_files\\pictures\\" + m_pcb_filename + "2";
		DeleteFile( path );
	}
	m_view->OnRangeCmds(NULL);
}

RECT CFreePcbDoc::AddBoardHoles( BOOL bCANCEL, POINT * MakePanel )
{
	static CArray<CPolyLine> mem_polylines;
	RECT BOARD;
	BOARD.left = BOARD.right = BOARD.bottom = BOARD.top = 0;

	if (m_outline_poly.GetSize() == 0 && mem_polylines.GetSize() == 0)
		return BOARD;

	if( bCANCEL && mem_polylines.GetSize() == 0 )
		ASSERT(0);
	if( bCANCEL == 0 && mem_polylines.GetSize() )
		ASSERT(0);

	if( bCANCEL == 0 )
	{
		// save all polylines
		mem_polylines.SetSize( m_outline_poly.GetSize() );
		for( int i=0; i<m_outline_poly.GetSize(); i++ )
			mem_polylines[i].Copy( &m_outline_poly.GetAt(i) );
	}
	else
	{
		m_outline_poly.RemoveAll();
		m_outline_poly.SetSize( mem_polylines.GetSize() );
		for( int i=0; i<mem_polylines.GetSize(); i++ )
		{
			m_outline_poly[i].Copy( &mem_polylines.GetAt(i) );
			m_outline_poly[i].Draw();
		}
		mem_polylines.RemoveAll();
		return BOARD;
	}
	int bW = 0;
	RECT op_rect = GetBoardRect(&bW);
	BOARD = op_rect;
	// test bounds
	{
		long long bW = BOARD.right - BOARD.left;
		long long bH = BOARD.top - BOARD.bottom;
		if (bW * (long long)m_n_x > INT_MAX / 2 || bH * (long long)m_n_y > INT_MAX / 2)
		{
			AfxMessageBox(G_LANGUAGE?"Один из размеров панели печатных плат выходит за допустимые рамки":"One of the PCB panel dimensions is out of tolerance", MB_ICONERROR);
			return BOARD;
		}
	}
	///m_view->SaveUndoInfoForOutlinePoly( m_view->UNDO_OP, TRUE, m_undo_list ); n.u.
	if (MakePanel) 
		if(MakePanel->x > 1 || MakePanel->y > 1)
		{
			RECT totalRect;
			totalRect.left = op_rect.left - m_panel_fields[0];
			totalRect.right = op_rect.left + ((op_rect.right - op_rect.left) * m_n_x) + (m_space_x * (m_n_x - 1)) + m_panel_fields[0];
			totalRect.bottom = op_rect.bottom - m_panel_fields[1];
			totalRect.top = op_rect.bottom + ((op_rect.top - op_rect.bottom) * m_n_y) + (m_space_y * (m_n_y - 1)) + m_panel_fields[1];
			int sz = m_outline_poly.GetSize();
			m_outline_poly.SetSize(sz + 1);
			id bid(ID_POLYLINE, ID_BOARD, sz);
			m_outline_poly[sz].Start(LAY_BOARD_OUTLINE, bW, NM_PER_MIL, totalRect.left, totalRect.bottom, 0, &bid, NULL);
			m_outline_poly[sz].AppendCorner(totalRect.right, totalRect.bottom, 0, 0);
			m_outline_poly[sz].AppendCorner(totalRect.right, totalRect.top, 0, 0);
			m_outline_poly[sz].AppendCorner(totalRect.left, totalRect.top, 0, 0);
			m_outline_poly[sz].Close();
			for (int ib = 0; ib < sz; ib++)
			{
				id gid = m_outline_poly[ib].GetId();
				if (gid.st != ID_BOARD)
					continue;
				if (m_outline_poly[ib].GetNumContours() < 2)
					continue;
				int start = m_outline_poly[ib].GetContourStart(1);
				for (int icont = start; icont < m_outline_poly[ib].GetNumCorners(); icont++)
				{
					m_outline_poly[sz].AppendCorner(m_outline_poly[ib].GetX(icont), m_outline_poly[ib].GetY(icont), m_outline_poly[ib].GetSideStyle(m_outline_poly[ib].GetIndexCornerBack(icont)), 0);
					if (m_outline_poly[ib].GetContourEnd(m_outline_poly[ib].GetNumContour(icont)) == icont)
						m_outline_poly[sz].Close(m_outline_poly[ib].GetSideStyle(icont));
				}
			}
			sz--;
			while (sz >= 0)
			{
				if (m_outline_poly[sz].GetLayer() == LAY_BOARD_OUTLINE)
				{
					m_outline_poly[sz].Undraw();
					m_outline_poly.RemoveAt(sz);
				}
				sz--;
			}
		}
	BOOL CUT_PRESENT = 0;
	for (cpart* p = m_plist->GetFirstPart(); p; p = m_plist->GetNextPart(p))
	{
		for( int io=0; io<p->m_outline_stroke.GetSize(); io++ )
		{
			if( getbit( p->m_outline_stroke[io]->layers_bitmap, LAY_PAD_THRU ) )
			{
				CArray<CPoint> * arr = m_dlist->Get_Points( p->m_outline_stroke[io], NULL, 0 );
				int np = arr->GetSize();
				CPoint * GET = new CPoint[np];// ok
				m_dlist->Get_Points( p->m_outline_stroke[io], GET, &np );
				for( int i_op=0; i_op<m_outline_poly.GetSize(); i_op++ )
				{
					if( m_outline_poly[i_op].GetLayer() == LAY_BOARD_OUTLINE )
					{
						BOOL bInside = 0;
						for( int gp=0; gp<np; gp++ )
						{
							if( m_outline_poly[i_op].TestPointInside( GET[gp].x, GET[gp].y ) )
							{
								bInside = 1;
								CUT_PRESENT = TRUE;
								break;
							}
						}
						if( bInside )
						{
							for( int gp=0; gp<np; gp++ )
							{
								m_outline_poly[i_op].AppendCorner( GET[gp].x, GET[gp].y, 0, 0 );
							}
							m_outline_poly[i_op].Close();
						}
					}
				}
				delete GET;
			}
		}
	}
	ProjectCombineBoard( LAY_BOARD_OUTLINE );
	if (MakePanel)
		if (MakePanel->x > 1 || MakePanel->y > 1)
		{
			int iPANEL = m_outline_poly.GetSize() - 1;
			if (m_outline_poly[iPANEL].GetNumContours() > 1)
			{
				int start = m_outline_poly[iPANEL].GetContourStart(1);
				int end = m_outline_poly[iPANEL].GetNumCorners();
				for (int ix = 0; ix < m_n_x; ix++)
				{
					int x_offset = ix * (BOARD.right - BOARD.left + m_space_x);
					for (int iy = 0; iy < m_n_y; iy++)
					{
						if (ix == 0 && iy == 0)
							continue;
						int y_offset = iy * (BOARD.top - BOARD.bottom + m_space_y);
						for (int ic = start; ic < end; ic++)
						{
							m_outline_poly[iPANEL].AppendCorner(m_outline_poly[iPANEL].GetX(ic) + x_offset,
								m_outline_poly[iPANEL].GetY(ic) + y_offset,
								m_outline_poly[iPANEL].GetSideStyle(m_outline_poly[iPANEL].GetIndexCornerBack(ic)), 0);
							if (m_outline_poly[iPANEL].GetContourEnd(m_outline_poly[iPANEL].GetNumContour(ic)) == ic)
								m_outline_poly[iPANEL].Close(m_outline_poly[iPANEL].GetSideStyle(ic));
						}
					}
				}
			}
			else if (CUT_PRESENT)
				AfxMessageBox(G_LANGUAGE ? "Неверный размер полей при наличии фрезерного контура! С такими параметрами контур мультизаготовки создать невозможно. Необходимо увеличить размер полей" : "Incorrect edge field with milling contour! It is impossible to create a multi-blank contour with such parameters. It is necessary to increase the board edge field");
			m_view->UpdateWindow();
			ProjectCombineBoard(LAY_BOARD_OUTLINE);
			int gAng = 0;
			for( cpart* BRD_PART = m_plist->GetFirstPart(); BRD_PART; BRD_PART= m_plist->GetNextPart(BRD_PART) )
				if (BRD_PART->shape)
				{
					for (int i = 0; i < BRD_PART->shape->m_outline_poly.GetSize(); i++)
					{
						CPolyLine* pp = &BRD_PART->shape->m_outline_poly[i];
						if (pp->GetLayer() == LAY_FP_VISIBLE_GRID)
						{
							gAng |= BRD_PART->angle;
							int x_offset = BRD_PART->x;
							int y_offset = BRD_PART->y;
							int sz = m_outline_poly.GetSize();
							m_outline_poly.SetSize(sz + 1);
							id bid(ID_POLYLINE, ID_BOARD, sz);
							m_outline_poly[sz].Start(LAY_FP_VISIBLE_GRID, bW, NM_PER_MIL, pp->GetX(0)+x_offset, pp->GetY(0)+y_offset, 0, &bid, NULL);
							for (int ic = 1; ic < pp->GetNumCorners(); ic++)
							{
								m_outline_poly[sz].AppendCorner(pp->GetX(ic)+x_offset, pp->GetY(ic)+y_offset, pp->GetSideStyle(pp->GetIndexCornerBack(ic)), 0);
								if (pp->GetContourEnd(pp->GetNumContour(ic)) == ic)
									m_outline_poly[sz].Close(pp->GetSideStyle(ic), FALSE);
							}
							m_outline_poly[sz].Draw();
						}
					}
				}
			if (gAng)
				AfxMessageBox(G_LANGUAGE ? "Системный футпринт с фрезерным контуром для панелизации должен быть размещён с нулевым углом!" : "The system footprint with the milling contour for panelization must be placed with a zero angle!", MB_ICONERROR);
			m_view->UpdateWindow();
			ProjectCombineBoard(LAY_FP_VISIBLE_GRID);
			for (int ipo = m_outline_poly.GetSize()-1; ipo >= 0; ipo--)
			{
				if (m_outline_poly[ipo].GetLayer() != LAY_FP_VISIBLE_GRID)
					continue;
				SimplifyPoly(&m_outline_poly[ipo], NM_PER_MIL * 10);
				m_outline_poly[ipo].SetLayer(LAY_BOARD_OUTLINE);
				for (int ix = 0; ix < m_n_x; ix++)
				{
					int x_offset = ix * (BOARD.right - BOARD.left + m_space_x);
					for (int iy = 0; iy < m_n_y; iy++)
					{
						int y_offset = iy * (BOARD.top - BOARD.bottom + m_space_y);
						if (ix == 0 && iy == 0)
							continue;
						int sz = m_outline_poly.GetSize();
						m_outline_poly.SetSize(sz + 1);
						id bid(ID_POLYLINE, ID_BOARD, sz);
						CPolyLine* pp = &m_outline_poly[ipo];
						m_outline_poly[sz].Start(LAY_BOARD_OUTLINE, bW, NM_PER_MIL, pp->GetX(0) + x_offset, pp->GetY(0) + y_offset, 0, &bid, NULL);
						for (int ic = 1; ic < pp->GetNumCorners(); ic++)
						{
							m_outline_poly[sz].AppendCorner(pp->GetX(ic) + x_offset, pp->GetY(ic) + y_offset, pp->GetSideStyle(pp->GetIndexCornerBack(ic)), 0);
							if (pp->GetContourEnd(pp->GetNumContour(ic)) == ic)
								m_outline_poly[sz].Close(pp->GetSideStyle(ic),FALSE);
						}
						m_outline_poly[sz].Draw();
					}
				}
				m_outline_poly[ipo].Draw();
			}
			m_view->UpdateWindow();
			ProjectCombineBoard(LAY_BOARD_OUTLINE);
		}
	return BOARD;
}

void CFreePcbDoc::CancelBoardHoles( BOOL bUNDO )
{
	///if( m_outline_poly.GetSize() > 0 )
	///{
	///	OnEditUndo(); // !Cancel board combining
	///	OnEditUndo(); // !Cancel cutouts
	///}
	if( bUNDO )
		OnEditUndo(); // !Cancel board combining
	AddBoardHoles( TRUE );
}

void CFreePcbDoc::ClipClear()
{
	clip_nlist->RemoveAllNets();
	clip_plist->RemoveAllParts();
	clip_tlist->RemoveAllTexts();
	clip_outline_poly.RemoveAll();
	clip_mlist->Clear();
}

void CFreePcbDoc::OnSelectProjectFolder()
{
	SelectFolder( this );
}

void CFreePcbDoc::OnReloadMenu()
{
	CMenu* pMenu = &theApp.m_main;
	CMenu* smenu = pMenu->GetSubMenu(0); // file menu
	CWnd * WND = theApp.GetMainWnd();
	CRect wRect;
	if( WND && smenu )
	{
		WND->GetWindowRect( wRect );
	}
	//
	ClearSpeedFiles( this );
	LoadSpeedFiles( this );
	pMenu = &theApp.m_main;
	smenu = pMenu->GetSubMenu(0); // file menu
	if( smenu )
	{
		smenu->TrackPopupMenu(TPM_LEFTALIGN, wRect.left+9, wRect.top+50, WND);
	}
}

BOOL CFreePcbDoc::OnSpeedFile( UINT CMD )
{
	RunSpeedFile( this, CMD );
	return 1;
}

RECT CFreePcbDoc::GetBoardRect( int * Width )
{
	RECT op_rect;
	op_rect.left = op_rect.bottom = INT_MAX;
	op_rect.right = op_rect.top = INT_MIN;
	// get boundaries of board outline (in nm)
	int bW = NM_PER_MIL;
	for (int ib = 0; ib < m_outline_poly.GetSize(); ib++)
	{
		id gid = m_outline_poly[ib].GetId();
		if (gid.st != ID_BOARD)
			continue;
		bW = m_outline_poly[ib].GetW();
		m_outline_poly[ib].RecalcRectC(0);
		RECT gr = m_outline_poly[ib].GetCornerBounds(0);
		SwellRect(&op_rect, gr);
	}
	if (op_rect.left == INT_MAX)
		op_rect = rect(0, 0, 0, 0);
	if (Width)
		*Width = bW;
	return op_rect;
}