// DlgCAD.cpp : implementation file
//

#include "stdafx.h"
#include "FreePcb.h"
#include "DlgCAD.h"
#include "Gerber.h"
#include "DlgLog.h"
#include "DlgMyMessageBox2.h"
#include "PathDialog.h"
#include "RTcall.h"
#include ".\dlgcad.h"

// CDlgCAD dialog

IMPLEMENT_DYNAMIC(CDlgCAD, CDialog)
CDlgCAD::CDlgCAD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCAD::IDD, pParent)
	, m_n_x(0)
	, m_n_y(0)
{
	m_gerber_created = 0;
	m_dlg_log = NULL;
	m_folder = "";
}

CDlgCAD::~CDlgCAD()
{
}
 
void CDlgCAD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FOLDER, m_edit_folder);
	DDX_Control(pDX, IDC_EDIT_FILL, m_edit_fill);
	DDX_Control(pDX, IDC_EDIT_MASK, m_edit_mask);
	DDX_Control(pDX, IDC_CHECK_DRILL, m_check_drill);
	DDX_Control(pDX, IDC_CHECK_TOP_SILK, m_check_top_silk);
	DDX_Control(pDX, IDC_CHECK_BOTTOM_SILK, m_check_bottom_silk);
	DDX_Control(pDX, IDC_CHECK_TOP_SOLDER, m_check_top_solder);
	DDX_Control(pDX, IDC_CHECKBOTTOM_SOLDER_MASK, m_check_bottom_solder);
	DDX_Control(pDX, IDC_CHECK_TOP_COPPER, m_check_top_copper);
	DDX_Control(pDX, IDC_CHECK_BOTTOM_COPPER, m_check_bottom_copper);
	DDX_Control(pDX, IDC_CHECK_INNER1, m_check_inner1);
	DDX_Control(pDX, IDC_CHECK_INNER2, m_check_inner2);
	DDX_Control(pDX, IDC_CHECK_INNER3, m_check_inner3);
	DDX_Control(pDX, IDC_CHECK_INNER4, m_check_inner4);
	DDX_Control(pDX, IDC_CHECK_INNER5, m_check_inner5);
	DDX_Control(pDX, IDC_CHECK_INNER6, m_check_inner6);
	DDX_Control(pDX, IDC_CHECK_INNER7, m_check_inner7);
	DDX_Control(pDX, IDC_CHECK_INNER8, m_check_inner8);
	DDX_Control(pDX, IDC_CHECK_INNER9, m_check_inner9);
	DDX_Control(pDX, IDC_CHECK_INNER10, m_check_inner10);
	DDX_Control(pDX, IDC_CHECK_INNER11, m_check_inner11);
	DDX_Control(pDX, IDC_CHECK_INNER12, m_check_inner12);
	DDX_Control(pDX, IDC_CHECK_INNER13, m_check_inner13);
	DDX_Control(pDX, IDC_CHECK_INNER14, m_check_inner14);
	DDX_Control(pDX, IDC_CHECK_SCRIBING, m_check_scribing);
	DDX_Control(pDX, IDC_CHECK_REFINETOP, m_check_refinetop);
	DDX_Control(pDX, IDC_CHECK_REFINEBOT, m_check_refinebot);
	DDX_Control(pDX, IDC_BOARD_OUTLINE, m_check_outline);
	DDX_Control(pDX, IDC_MOIRES, m_check_moires);
	DDX_Control(pDX, IDC_LAYER_DESC, m_check_layer_text);
	DDX_Control(pDX, IDC_CHECK_HILITE, m_check_hilite);
	DDX_Control(pDX, IDC_COMBO_CAD_UNITS, m_combo_units);
	DDX_Control(pDX, IDC_EDIT_CAD_PILOT_DIAM, m_edit_pilot_diam);
	DDX_Control(pDX, IDC_CHECK_CAD_PILOT, m_check_pilot);
	DDX_Control(pDX, IDC_EDIT_CAD_MIN_SSW, m_edit_min_ss_w);
	DDX_Control(pDX, IDC_EDIT_CAD_HIGH_W, m_edit_high_w);
	DDX_Control(pDX, IDC_EDIT_CAD_THERMALWID, m_edit_thermal_width);
	DDX_Control(pDX, IDC_EDIT_CAD_THERMALCL, m_edit_thermal_clearance);
	DDX_Text( pDX, IDC_EDIT_FOLDER, m_folder );
	DDX_Control(pDX, IDC_EDIT_CAD_HOLE_CLEARANCE, m_edit_hole_clearance);
	DDX_Control(pDX, IDC_EDIT_CAD_ANN_PINS, m_edit_ann_pins);
	DDX_Control(pDX, IDC_EDIT_CAD_ANN_VIAS, m_edit_ann_vias);
	DDX_Control(pDX, IDC_CHECK1, m_check_thermal_pins);
	DDX_Control(pDX, IDC_CHECK2, m_check_thermal_vias);
	DDX_Control(pDX, IDC_CHECK3, m_check_mask_vias);
	DDX_Control(pDX, IDC_CHECK_BD, m_check_board);
	DDX_Control(pDX, IDC_CHECK_TOP_PASTE, m_check_top_paste);
	DDX_Control(pDX, IDC_CHECK_BOTTOM_PASTE, m_check_bottom_paste);
	DDX_Control(pDX, IDC_EDIT_SP_X, m_edit_space_x);
	DDX_Control(pDX, IDC_EDIT_SP_Y, m_edit_space_y);
	DDX_Control(pDX, IDC_EDIT_N_X, m_edit_n_x);
	DDX_Control(pDX, IDC_EDIT_N_Y, m_edit_n_y);
	DDX_Text(pDX, IDC_EDIT_N_X, m_n_x ); 
	DDX_Text(pDX, IDC_EDIT_N_Y, m_n_y );
	DDV_MinMaxUInt(pDX, m_n_x, 1, 99);
	DDV_MinMaxUInt(pDX, m_n_y, 1, 99); 
	DDX_Control(pDX, IDC_EDIT_CAD_SHRINK_PASTE, m_edit_shrink_paste);
	DDX_Control(pDX, IDC_CHECK_90, m_check_90);
	DDX_Control(pDX, IDC_CHECK_ALL_GERBERS, m_check_render_all);
	DDX_Control(pDX, IDC_CHECK_MIRROR_BOTTOM, m_check_mirror_bottom);
	DDX_Control(pDX, IDC_EDIT_DPI, m_dpi);
	DDX_Control(pDX, IDC_EDIT_PNG_AA, m_png_aa);
	DDX_Control(pDX, IDC_CHECK_SMT_THERMALS, m_check_smt_thermals);
	if( !pDX->m_bSaveAndValidate )
	{
		// entry
		//
		struct _stat buf;
		int STAT = _stat( m_folder, &buf );
		if( m_folder.GetLength() == 0 || STAT )
			OnBnClickedButtonDef();
		//
		m_combo_units.InsertString( 0, "MIL" );
		m_combo_units.InsertString( 1, "MM" );
		if( m_units == MIL )
			m_combo_units.SetCurSel( 0 );
		else
			m_combo_units.SetCurSel( 1 );
		SetFields();
		// enable checkboxes for valid gerber layers
		if( m_num_copper_layers < 2 )
			m_check_bottom_copper.EnableWindow( FALSE );
		if( m_num_copper_layers < 3 )
			m_check_inner1.EnableWindow( FALSE );
		if( m_num_copper_layers < 4 )
			m_check_inner2.EnableWindow( FALSE );
		if( m_num_copper_layers < 5 )
			m_check_inner3.EnableWindow( FALSE );
		if( m_num_copper_layers < 6 )
			m_check_inner4.EnableWindow( FALSE );
		if( m_num_copper_layers < 7 )
			m_check_inner5.EnableWindow( FALSE );
		if( m_num_copper_layers < 8 )
			m_check_inner6.EnableWindow( FALSE );
		if( m_num_copper_layers < 9 )
			m_check_inner7.EnableWindow( FALSE );
		if( m_num_copper_layers < 10 )
			m_check_inner8.EnableWindow( FALSE );
		if( m_num_copper_layers < 11 )
			m_check_inner9.EnableWindow( FALSE );
		if( m_num_copper_layers < 12 )
			m_check_inner10.EnableWindow( FALSE );
		if( m_num_copper_layers < 13 )
			m_check_inner11.EnableWindow( FALSE );
		if( m_num_copper_layers < 14 )
			m_check_inner12.EnableWindow( FALSE );
		if( m_num_copper_layers < 15 )
			m_check_inner13.EnableWindow( FALSE );
		if( m_num_copper_layers < 16 )
			m_check_inner14.EnableWindow( FALSE );

		// load saved settings
		SetFields();
		for( int i=0; i<27; i++ )
		{
			if( i<(m_num_copper_layers+4) || i>19 )
			{
				switch(i)
				{
				case 0: m_check_top_silk.SetCheck(m_layers & (1<<i)); break;
				case 1: m_check_bottom_silk.SetCheck(m_layers & (1<<i)); break;
				case 2: m_check_top_solder.SetCheck(m_layers & (1<<i)); break;
				case 3: m_check_bottom_solder.SetCheck(m_layers & (1<<i)); break;
				case 4: m_check_top_copper.SetCheck(m_layers & (1<<i)); break;
				case 5: m_check_bottom_copper.SetCheck(m_layers & (1<<i)); break;
				case 6: m_check_inner1.SetCheck(m_layers & (1<<i)); break;
				case 7: m_check_inner2.SetCheck(m_layers & (1<<i)); break; 
				case 8: m_check_inner3.SetCheck(m_layers & (1<<i)); break;
				case 9: m_check_inner4.SetCheck(m_layers & (1<<i)); break;
				case 10: m_check_inner5.SetCheck(m_layers & (1<<i)); break;
				case 11: m_check_inner6.SetCheck(m_layers & (1<<i)); break;
				case 12: m_check_inner7.SetCheck(m_layers & (1<<i)); break;
				case 13: m_check_inner8.SetCheck(m_layers & (1<<i)); break;
				case 14: m_check_inner9.SetCheck(m_layers & (1<<i)); break;
				case 15: m_check_inner10.SetCheck(m_layers & (1<<i)); break;
				case 16: m_check_inner11.SetCheck(m_layers & (1<<i)); break;
				case 17: m_check_inner12.SetCheck(m_layers & (1<<i)); break;
				case 18: m_check_inner13.SetCheck(m_layers & (1<<i)); break;
				case 19: m_check_inner14.SetCheck(m_layers & (1<<i)); break;
				case 20: m_check_board.SetCheck(m_layers & (1<<i)); break;
				case 21: m_check_top_paste.SetCheck(m_layers & (1<<i)); break;
				case 22: m_check_bottom_paste.SetCheck(m_layers & (1<<i)); break;
				case 23: m_check_scribing.SetCheck(m_layers & (1<<i)); break;
				case 24: m_check_refinetop.SetCheck(m_layers & (1<<i)); break;
				case 25: m_check_refinebot.SetCheck(m_layers & (1<<i)); break;
				case 26: {
						m_check_hilite.SetCheck(m_layers & (1<<i)); 
						//if( m_dl->Get_Selected() == 0 )
						//	m_check_hilite.EnableWindow(0);
						break;
						 }
				default: break;
				}
			}
		}
		m_dpi.SetWindowTextA( m_dpi_str );
		m_png_aa.SetWindowTextA( m_png_aa_str );
		m_check_drill.SetCheck( m_drill_file );
		m_check_outline.SetCheck( m_flags & GERBER_BOARD_OUTLINE );
		m_check_moires.SetCheck( m_flags & GERBER_AUTO_MOIRES );
		m_check_layer_text.SetCheck( m_flags & GERBER_LAYER_TEXT );
		m_check_thermal_pins.SetCheck( !(m_flags & GERBER_NO_PIN_THERMALS) );
		m_check_thermal_vias.SetCheck( !(m_flags & GERBER_NO_VIA_THERMALS) );
		m_check_mask_vias.SetCheck( !(m_flags & GERBER_MASK_VIAS) );
		m_check_90.SetCheck( m_flags & GERBER_90_THERMALS );
		m_check_pilot.SetCheck( m_flags & GERBER_PILOT_HOLES );
		m_check_render_all.SetCheck( m_flags & GERBER_RENDER_ALL );
		m_check_mirror_bottom.SetCheck( m_flags & GERBER_MIRROR_BOTTOM_PNG );
		m_check_smt_thermals.EnableWindow( m_bSMT_connect );
		m_check_smt_thermals.SetCheck( !(m_flags & GERBER_NO_SMT_THERMALS) );
		OnBnClickedThermalPins();
		OnBnClickedCheckCadPilot();
		OnBnClickedRenderAllGerbers();
	}
	else
	{
		m_dpi.GetWindowTextA( m_dpi_str );
		m_png_aa.GetWindowTextA( m_png_aa_str );
		m_png_settings = m_dpi_str + " " + m_png_aa_str;
	}
}


BEGIN_MESSAGE_MAP(CDlgCAD, CDialog)
	ON_BN_CLICKED(ID_GO, OnBnClickedGo)
	ON_CBN_SELCHANGE(IDC_COMBO_CAD_UNITS, OnCbnSelchangeComboCadUnits)
	ON_BN_CLICKED(IDC_CHECK_CAD_PILOT, OnBnClickedCheckCadPilot)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_DEF, OnBnClickedButtonDef)
	ON_BN_CLICKED(IDC_BUTTON_FOLDER, OnBnClickedButtonFolder)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedThermalPins)
	ON_BN_CLICKED(IDC_CHECK2, OnBnClickedThermalVias)
	ON_BN_CLICKED(IDC_CHECK_ALL_GERBERS, OnBnClickedRenderAllGerbers)
	ON_BN_CLICKED(IDC_BUTTON_DONE, OnBnClickedButtonDone)
END_MESSAGE_MAP()

void CDlgCAD::Initialize( double version, 
						 CString * folder, 
						 CString * project_folder,
						 CString * app_folder,
						 CString * file_name,
						 CString * png_settings,
						 int num_copper_layers, int units, BOOL bSMTconnect,
						 int fill_clearance, int mask_clearance, int thermal_width,
						 int pilot_diameter, int min_silkscreen_wid, int highlight_width, 
						 int hole_clearance, int thermal_clearance,
						 int annular_ring_pins, int annular_ring_vias, int shrink_paste,
						 int n_x, int n_y, int space_x, int space_y,
						 int flags, int layers, int drill_file,
						 CArray<CPolyLine> * op,
						 BOOL * bShowMessageForClearance,
						 CPartList * pl, CNetList * nl, CTextList * tl, CDisplayList * dl, Merge * ml,
						 CDlgLog * log )
{
	m_bShowMessageForClearance = *bShowMessageForClearance;
	m_bSMT_connect = bSMTconnect;
	m_version = version;
	m_folder = *folder;
	m_project_folder = *project_folder;
	m_app_folder = *app_folder;
	m_f_name = (*file_name).Left((*file_name).GetLength()-4);
	m_units = units;
	m_fill_clearance = fill_clearance;
	m_mask_clearance = mask_clearance;
	m_thermal_width = thermal_width;
	m_thermal_clearance = thermal_clearance;
	m_pilot_diameter = pilot_diameter;
	m_min_silkscreen_width = min_silkscreen_wid;
	m_highlight_width = highlight_width;
	m_num_copper_layers = num_copper_layers;
	m_flags = flags;
	m_layers = layers;
	m_drill_file = drill_file;
	m_op = op;
	m_pl = pl;
	m_nl = nl;
	m_tl = tl;
	m_dl = dl;
	m_ml = ml;
	m_hole_clearance = hole_clearance;
	m_annular_ring_pins = annular_ring_pins;
	m_annular_ring_vias = annular_ring_vias;
	m_paste_shrink = shrink_paste;
	m_n_x = n_x; 
	m_n_y = n_y;
	m_space_x = space_x;
	m_space_y = space_y;
	m_dlg_log = log;
	//
	m_png_settings = *png_settings;
	CArray<CString> arr;
	ParseKeyString( &m_png_settings, &m_dpi_str, &arr );
	if( arr.GetSize() > 0 )
		m_png_aa_str = arr[0];
	if( m_dpi_str.GetLength() == 0 )
		m_dpi_str = "600";
	if( m_png_aa_str.GetLength() == 0 )
		m_png_aa_str = "0.04";
}

// CDlgCAD message handlers

void CDlgCAD::OnBnClickedGo()
{
	// get CAM folder and create it if necessary
	struct _stat buf;
	m_edit_folder.GetWindowText( m_folder );
	if( m_folder.GetLength() == 0 )
		OnBnClickedButtonDef();
	if( m_folder.Right(1) == "\\" )
		m_folder = m_folder.Left(m_folder.GetLength()-1);
	int err = _stat( m_folder, &buf );
	if( err )
	{
		CString str;
		str.Format(G_LANGUAGE == 0 ? "Folder \"%s\" doesn't exist, create it ?":"Папка «%s» не существует, создать ее?", m_folder);
		int ret = AfxMessageBox( str, MB_YESNO );
		if( ret == IDYES )
		{
			err = _mkdir( m_folder );
			if( err )
			{
				str.Format(G_LANGUAGE == 0 ? "Unable to create folder \"%s\"":"Невозможно создать папку «%s»", m_folder);
				AfxMessageBox( str, MB_OK );
				return;
			}
		}
		else
			return;
	}
	GetFields();

	// warn about copper-copper clearance
	if( m_fill_clearance == 0 && m_bShowMessageForClearance )     
	{
		CDlgMyMessageBox2 dlg;
		CString mess = "WARNING: You have set the copper to copper-fill clearance to 0.";
		mess += "\nThis will disable automatic generation of clearances for pads and vias in copper areas.";
		mess += "\nAre you SURE that you don't need these clearances ?";
		dlg.Initialize( &mess );
		int ret = dlg.DoModal();
		if( ret == IDCANCEL )
			return;
		else
			m_bShowMessageForClearance = !dlg.bDontShowBoxState;
	}

	if( m_hole_clearance < m_fill_clearance )
	{
		m_hole_clearance = m_fill_clearance;
		SetFields();
	}

	// show log
	m_dlg_log->ShowWindow( SW_SHOW );
	m_dlg_log->UpdateWindow();
	m_dlg_log->BringWindowToTop();
	m_dlg_log->Clear();
	m_dlg_log->UpdateWindow();
	//
	// delete old files
	HANDLE search_file;
    WIN32_FIND_DATA aa;
    search_file = FindFirstFile(m_folder+"\\*", &aa);
    while (FindNextFile(search_file, &aa) != NULL)
    {
		CString name = aa.cFileName;
		int pos = name.ReverseFind('.');
		if( pos > 0 )
		{
			CString name2 = name.Left(pos);
			if( name2.Compare(m_f_name) == 0 ||
				name.Right(name.GetLength()-pos) == ".gbr" ||
				name.Right(name.GetLength()-pos) == ".png" ||
				name.Right(name.GetLength()-pos) == ".drl" )
				DeleteFile( m_folder + "\\" + name );
		}
    }

	BOOL errors = FALSE;	// if errors occur

	// gerber name style
	int gCASE = 0;
	// create drill file, if requested
	if( m_drill_file )
	{
		CStdioFile f;
		CString f_name;
		if( gCASE )
			f_name.Format("%s\\HOLES.drl",m_folder );
		else
			f_name.Format("%s\\%s.NCD.drl",m_folder,m_f_name); 
		int ok = f.Open( f_name, CFile::modeCreate | CFile::modeWrite ); 
		if( !ok )
		{
			CString log_message;
			log_message.Format( "ERROR: Unable to open file \"%s\"\r\n", f_name );
			m_dlg_log->AddLine( log_message );
			errors = TRUE;
		}
		else
		{
			CString log_message;
			log_message.Format( "Writing file: \"%s\"\r\n", f_name );
			m_dlg_log->AddLine( log_message );
			// unplated holes
			CPoint p_err = ::WriteDrillFile( &f, m_pl, m_nl, m_op, m_n_x, m_n_y, m_space_x, m_space_y );
			if( p_err.x || p_err.y )
			{
				CString xs, ys;
				::MakeCStringFromDimension( &xs, p_err.x, m_units, 1, 1, 1, 2 );
				::MakeCStringFromDimension( &ys, p_err.y, m_units, 1, 1, 1, 2 );
				log_message.Format( "    negative hole diameter? (fixed) x=%s y=%s\r\n", xs, ys );
				m_dlg_log->AddLine( log_message );
			}
			f.Close();
		}
		/*for(  )
		{
			if( gCASE )
				f_name.Format("%s\\HOLES.drl",m_folder );
			else
				f_name.Format("%s\\%s.DRILL",m_folder,m_f_name); 
			int ok = f.Open( f_name, CFile::modeCreate | CFile::modeWrite ); 
			if( !ok )
			{
				CString log_message;
				log_message.Format( "ERROR: Unable to open file \"%s\"\r\n", f_name );
				m_dlg_log->AddLine( log_message );
				errors = TRUE;
			}
			else
			{
				CString log_message;
				log_message.Format( "Writing file: \"%s\"\r\n", f_name );
				m_dlg_log->AddLine( log_message );
				// unplated holes
				::WriteDrillFile( &f, m_pl, m_nl, m_op, m_n_x, m_n_y, m_space_x, m_space_y );
				f.Close();
			}
		}*/
		m_drill_file = 1;
	}

	// create Gerber files for selected layers
	CArray<CString> commands;
	for( int i=0; i<27; i++ )
	{
		CString gerber_name = "";
		int layer = 0;
		if( i<(m_num_copper_layers+4) || i>19 )
		{
			switch(i)
			{
			case 0: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "TOP_SILK.gbr";
						else
							gerber_name.Format("%s.TSL.gbr",m_f_name); 
						layer = LAY_SILK_TOP; 
					} 
					break;
			case 1: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "BOTTOM_SILK.gbr";
						else
							gerber_name.Format("%s.BSL.gbr",m_f_name); 
						layer = LAY_SILK_BOTTOM; 
					} 
					break;
			case 2: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "TOP_MASK.gbr";
						else
							gerber_name.Format("%s.TML.gbr",m_f_name); 
						layer = LAY_SM_TOP; 
					} 
					break;
			case 3: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "BOTTOM_MASK.gbr";
						else
							gerber_name.Format("%s.BML.gbr",m_f_name); 
						layer = LAY_SM_BOTTOM; 
					} 
					break;
			case 4: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "TOP_COPPER.gbr";
						else
							gerber_name.Format("%s.TOP.gbr",m_f_name); 
						layer = LAY_TOP_COPPER; 
					} 
					break;
			case 5: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "BOTTOM_COPPER.gbr";
						else
							gerber_name.Format("%s.BOT.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER; 
					} 
					break;
			case 6: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "INNER_1.gbr";
						else
							gerber_name.Format("%s.INNER_1.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+1; 
					} 
					break;
			case 7: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "INNER_2.gbr";
						else
							gerber_name.Format("%s.INNER_2.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+2; 
					} 
					break;
			case 8: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "INNER_3.gbr";
						else
							gerber_name.Format("%s.INNER_3.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+3; 
					} 
					break;
			case 9: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "INNER_4.gbr";
						else
							gerber_name.Format("%s.INNER_4.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+4; 
					} 
					break;
			case 10: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "INNER_5.gbr";
						else
							gerber_name.Format("%s.INNER_5.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+5; 
					} 
					break;
			case 11: if( m_layers & (1<<i) )
					{
						if(gCASE)
							gerber_name = "INNER_6.gbr";
						else
							gerber_name.Format("%s.INNER_6.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+6; 
					} 
					break;
			case 12: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "INNER_7.gbr";
						else
							gerber_name.Format("%s.INNER_7.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+7; 
					} 
					break;
			case 13: if( m_layers & (1<<i) )
					{
						if(gCASE)
							gerber_name = "INNER_8.gbr";
						else
							gerber_name.Format("%s.INNER_8.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+8; 
					} 
					break;
			case 14: if( m_check_inner9.GetCheck() )
					{ 
						if(gCASE)
							gerber_name = "INNER_9.gbr";
						else
							gerber_name.Format("%s.INNER_9.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+9; 
					} 
					break;
			case 15: if( m_layers & (1<<i) )
					{
						if(gCASE)
							gerber_name = "INNER_10.gbr";
						else
							gerber_name.Format("%s.INNER_10.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+10; 
					} 
					break;
			case 16: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "INNER_11.gbr";
						else
							gerber_name.Format("%s.INNER_11.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+11; 
					} 
					break;
			case 17: if( m_layers & (1<<i) )
					{
						if(gCASE)
							gerber_name = "INNER_12.gbr";
						else
							gerber_name.Format("%s.INNER_12.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+12; 
					} 
					break;
			case 18: if( m_check_inner13.GetCheck() )
					{
						if(gCASE)
							gerber_name = "INNER_13.gbr";
						else
							gerber_name.Format("%s.INNER_13.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+13; 
					} 
					break;
			case 19: if( m_layers & (1<<i) )
					{ 
						if(gCASE)
							gerber_name = "INNER_14.gbr";
						else
							gerber_name.Format("%s.INNER_14.gbr",m_f_name); 
						layer = LAY_BOTTOM_COPPER+14; 
					} 
					break;
			case 20: if( m_layers & (1<<i) )
					{
						if(gCASE)
							gerber_name = "BOARD_OUTLINE.gbr";
						else
							gerber_name.Format("%s.BRD.gbr",m_f_name); 
						layer = LAY_BOARD_OUTLINE; 
					} 
					break;
			case 21: if( m_layers & (1<<i) )
					{
						if(gCASE)
							gerber_name = "TOP_PASTE.gbr";
						else
							gerber_name.Format("%s.TPL.gbr",m_f_name); 
						layer = LAY_PASTE_TOP; 
					} 
					break;
			case 22: if( m_layers & (1<<i) )
					{
						if(gCASE)
							gerber_name = "BOTTOM_PASTE.gbr";
						else
							gerber_name.Format("%s.BPL.gbr",m_f_name); 
						layer = LAY_PASTE_BOTTOM;
					} 
					break;
			case 23: if ( m_layers & (1<<i) )
					{
						if(gCASE)
							gerber_name = "V_CUTOUTS.gbr";
						else
							gerber_name.Format("%s.VCUT.gbr",m_f_name); 
						layer = LAY_SCRIBING; 
					}  
					break;
			case 24: if ( m_layers & (1<<i) )
					{
						if(gCASE)
							gerber_name = "TOP_NOTES.gbr";
						else
							gerber_name.Format("%s.TNL.gbr",m_f_name); 
						layer = LAY_REFINE_TOP; 
					}  
					break;
			case 25: if ( m_layers & (1<<i) )
					{
						if(gCASE)
							gerber_name = "BOTTOM_NOTES.gbr";
						else
							gerber_name.Format("%s.BNL.gbr",m_f_name); 
						layer = LAY_REFINE_BOT; 
					}  
					break;
			case 26: if ( m_layers & (1<<i) )
					{
						if(gCASE)
							gerber_name = "HIGHLIGHTS.gbr";
						else
							gerber_name.Format("%s.HLT.gbr",m_f_name); 
						layer = LAY_HILITE; 
					}  
					break;
			default: ASSERT(0); 
				break;
			}
		}
		if( layer )
		{
			// write the gerber file
			m_pl->SetPinAnnularRing( m_annular_ring_pins );
			m_nl->SetViaAnnularRing( m_annular_ring_vias );
			CString f_str = m_folder + "\\" + gerber_name;
			CStdioFile f;
			int ok = f.Open( f_str, CFile::modeCreate | CFile::modeWrite );
			if( !ok )
			{
				CString log_message;
				log_message.Format( "ERROR: Unable to open file \"%s\"\r\n", f_str );
				m_dlg_log->AddLine( log_message );
				errors = TRUE;
			}
			else
			{
				CString log_message;
				log_message.Format( "Writing file: \"%s\"\r\n", f_str );
				m_dlg_log->AddLine( log_message );
				CString line;
				if (G_LANGUAGE == 0)
				{
					line.Format("G04 FreePCB MFC Application*\n");
					f.WriteString(line);
					line.Format("G04 Version: FreePCB-%5.3f*\n", m_version);
					f.WriteString(line);
					line.Format("G04 WebSite: https://github.com/niconson *\n");
					f.WriteString(line);
				}
				else
				{
					line.Format("G04 \"ПлатФорм\" на русском*\n");
					f.WriteString(line);
					line.Format("G04 Version: ПлатФорм %5.3f*\n", m_version);
					f.WriteString(line);
					line.Format("G04 WebSite: https://github.com/niconson *\n");
					f.WriteString(line);
				}
				line.Format( "G04 %s*\n", f_str );
				f.WriteString( line );
				::WriteGerberFile( &f, m_flags, layer, 
					m_dlg_log, m_paste_shrink,
					m_fill_clearance, m_mask_clearance, m_pilot_diameter,
					m_min_silkscreen_width, m_highlight_width, m_thermal_width,
					m_hole_clearance, m_thermal_clearance,
					m_n_x, m_n_y, m_space_x, m_space_y,
					m_op, m_pl, m_nl, m_tl, m_dl, m_ml );
				f.WriteString( "M02*\n" );	// end of job
				f.Close();
			}
			if( m_flags & GERBER_RENDER_ALL )
			{
				// create command-line to render layer
				int nlines = commands.GetSize();
				commands.SetSize( nlines + 1 );
				CString mirror_str = "";
				if( layer == LAY_SILK_BOTTOM
					|| layer == LAY_SM_BOTTOM
					|| layer == LAY_BOTTOM_COPPER
					|| layer == LAY_MASK_BOTTOM
					|| layer == LAY_PASTE_BOTTOM
					|| layer == LAY_REFINE_BOT)
				{
					if( m_flags & GERBER_MIRROR_BOTTOM_PNG ) 
						mirror_str = "--mirror ";
				}
				m_dpi.GetWindowTextA( m_dpi_str );
				m_png_aa.GetWindowTextA( m_png_aa_str );
				CString command_str;
				command_str.Format( "%s\\GerberRender.exe -r %s -a %s %s %s %s.png", m_app_folder, m_dpi_str, m_png_aa_str, mirror_str, gerber_name, gerber_name.Left( gerber_name.GetLength()-4 ) );
				commands[nlines] = command_str;
			}
		}
	}
	if( errors )
		m_dlg_log->AddLine( "****** ERRORS OCCURRED DURING CREATION OF GERBERS ******\r\n" );
	else
	{
		m_dlg_log->AddLine( "************ ALL GERBERS CREATED SUCCESSFULLY **********\r\n" );
		m_gerber_created = 1;
	}
	if( commands.GetSize() != 0 )
	{
		_chdir( m_folder );		// change current working directory to CAM folder
		m_dlg_log->AddLine( "*********** RENDERING .PNG FILES FOR LAYERS ************\r\n" );
		for( int i=0; i<commands.GetSize(); i++ )
		{
			m_dlg_log->AddLine( "Run: " + commands[i] + "\r\n" ); 
			::RunConsoleProcess( commands[i], m_dlg_log );
			m_dlg_log->AddLine( "\r\n" ); 
		}
		m_dlg_log->AddLine( "************************* DONE *************************\r\n" ); 
		_chdir( m_app_folder );	// change back
	}
}

void CDlgCAD::GetFields()
{
	CString str;
	double mult;
	if( m_units == MIL )
		mult = NM_PER_MIL;
	else
		mult = 1000000.0;
	m_edit_fill.GetWindowText( str );
	m_fill_clearance = atof( str ) * mult;
	m_edit_mask.GetWindowText( str );
	m_mask_clearance = atof( str ) * mult;
	m_edit_pilot_diam.GetWindowText( str );
	m_pilot_diameter = atof( str ) * mult;
	m_edit_min_ss_w.GetWindowText( str );
	m_min_silkscreen_width = atof( str ) * mult;
	m_edit_high_w.GetWindowText( str );
	m_highlight_width = atof( str ) * mult;
	m_edit_thermal_width.GetWindowText( str );
	m_thermal_width = atof( str ) * mult;
	m_edit_thermal_clearance.GetWindowText( str );
	m_thermal_clearance = atof( str ) * mult;
	m_edit_hole_clearance.GetWindowText( str );
	m_hole_clearance = atof( str ) * mult;
	m_edit_ann_pins.GetWindowText( str );
	m_annular_ring_pins = atof( str ) * mult;
	m_edit_ann_vias.GetWindowText( str );
	m_annular_ring_vias = atof( str ) * mult;
	m_edit_shrink_paste.GetWindowText( str );
	m_paste_shrink = atof( str ) * mult;
	m_edit_space_x.GetWindowText( str );
	m_space_x = atof( str ) * mult;
	m_edit_space_y.GetWindowText( str );
	m_space_y = atof( str ) * mult;
	m_edit_n_x.GetWindowText( str );
	m_n_x = atoi( str );
	if( m_n_x < 1 )
	{
		m_n_x = 1;
		m_edit_n_x.SetWindowText( "1" );
	}
	m_edit_n_y.GetWindowText( str );
	m_n_y = atoi( str );
	if( m_n_y < 1 )
	{
		m_n_y = 1;
		m_edit_n_y.SetWindowText( "1" );
	}
	// get flags for Gerbers
	m_flags = 0;
	if( m_check_outline.GetCheck() )
		m_flags |= GERBER_BOARD_OUTLINE;
	if( m_check_moires.GetCheck() )
		m_flags |= GERBER_AUTO_MOIRES;
	if( m_check_layer_text.GetCheck() )
		m_flags |= GERBER_LAYER_TEXT;
	if( m_check_pilot.GetCheck() )
		m_flags |= GERBER_PILOT_HOLES;
	if( !m_check_thermal_pins.GetCheck() )
		m_flags |= GERBER_NO_PIN_THERMALS;
	if( !m_check_thermal_vias.GetCheck() )
		m_flags |= GERBER_NO_VIA_THERMALS;
	if( !m_check_mask_vias.GetCheck() )
		m_flags |= GERBER_MASK_VIAS;
	if( m_check_90.GetCheck() )
		m_flags |= GERBER_90_THERMALS;
	if( m_check_render_all.GetCheck() )
		m_flags |= GERBER_RENDER_ALL;
	if( m_check_render_all.GetCheck() && m_check_mirror_bottom.GetCheck() )
		m_flags |= GERBER_MIRROR_BOTTOM_PNG;
	if( !m_check_smt_thermals.GetCheck() )
		m_flags |= GERBER_NO_SMT_THERMALS;
	// get layers
	m_layers = 0x0;
	for( int i=0; i<27; i++ )
	{
		if( i<(m_num_copper_layers+4) || i>19 )
		{
			switch(i)
			{
			case 0: if( m_check_top_silk.GetCheck() )
						m_layers |= 1<<i;  
					break;
			case 1: if( m_check_bottom_silk.GetCheck() )
						m_layers |= 1<<i;  
					break;
			case 2: if( m_check_top_solder.GetCheck() )
						m_layers |= 1<<i;  
					break;
			case 3: if( m_check_bottom_solder.GetCheck() )
						m_layers |= 1<<i;  
					break;
			case 4: if( m_check_top_copper.GetCheck() )
						m_layers |= 1<<i;  
					break;
			case 5: if( m_check_bottom_copper.GetCheck() )
						m_layers |= 1<<i;  
					break;
			case 6: if( m_check_inner1.GetCheck() )
						m_layers |= 1<<i;  
					break;
			case 7: if( m_check_inner2.GetCheck() )
						m_layers |= 1<<i;  
					break;
			case 8: if( m_check_inner3.GetCheck() )
						m_layers |= 1<<i;  
					break;
			case 9: if( m_check_inner4.GetCheck() )
						m_layers |= 1<<i;  
					break;
			case 10: if( m_check_inner5.GetCheck() )
						m_layers |= 1<<i;  
					 break;
			case 11: if( m_check_inner6.GetCheck() )
						m_layers |= 1<<i;  
					 break;
			case 12: if( m_check_inner7.GetCheck() )
						m_layers |= 1<<i;  
					 break;
			case 13: if( m_check_inner8.GetCheck() )
						m_layers |= 1<<i;  
					 break;
			case 14: if( m_check_inner9.GetCheck() )
						m_layers |= 1<<i;  
					 break;
			case 15: if( m_check_inner10.GetCheck() )
						m_layers |= 1<<i;  
					 break;
			case 16: if( m_check_inner11.GetCheck() )
						m_layers |= 1<<i;  
					 break;
			case 17: if( m_check_inner12.GetCheck() )
						m_layers |= 1<<i;  
					 break;
			case 18: if( m_check_inner13.GetCheck() )
						m_layers |= 1<<i;  
					 break;
			case 19: if( m_check_inner14.GetCheck() )
						m_layers |= 1<<i;  
					 break;
			case 20: if( m_check_board.GetCheck() )
						m_layers |= 1<<i;  
					 break;
			case 21: if( m_check_top_paste.GetCheck() )
						m_layers |= 1<<i;  
					 break;
			case 22: if( m_check_bottom_paste.GetCheck() )
						m_layers |= 1<<i; 
					 break;
			case 23: if( m_check_scribing.GetCheck() )
						m_layers |= 1<<i; 
					 break;
			case 24: if( m_check_refinetop.GetCheck() )
						m_layers |= 1<<i; 
					 break;
			case 25: if( m_check_refinebot.GetCheck() )
						m_layers |= 1<<i; 
					 break;
			case 26: if( m_check_hilite.GetCheck() )
						m_layers |= 1<<i; 
					 break;
			default: ASSERT(0); 
				break;
			}
		}
	}
	if( m_check_drill.GetCheck() )
		m_drill_file = 1;
	else
		m_drill_file = 0;
}

void CDlgCAD::SetFields()
{
	CString str;
	double mult;
	if( m_units == MIL )
		mult = NM_PER_MIL;
	else
		mult = 1000000.0;
	MakeCStringFromDouble( &str, m_fill_clearance/mult );
	m_edit_fill.SetWindowText( str );
	MakeCStringFromDouble( &str, m_mask_clearance/mult );
	m_edit_mask.SetWindowText( str );
	MakeCStringFromDouble( &str, m_pilot_diameter/mult );
	m_edit_pilot_diam.SetWindowText( str );
	MakeCStringFromDouble( &str, m_min_silkscreen_width/mult );
	m_edit_min_ss_w.SetWindowText( str );
	MakeCStringFromDouble( &str, m_highlight_width/mult );
	m_edit_high_w.SetWindowText( str );
	MakeCStringFromDouble( &str, m_thermal_width/mult );
	m_edit_thermal_width.SetWindowText( str );
	MakeCStringFromDouble( &str, m_thermal_clearance/mult );
	m_edit_thermal_clearance.SetWindowText( str );
	MakeCStringFromDouble( &str, m_hole_clearance/mult );
	m_edit_hole_clearance.SetWindowText( str );
	MakeCStringFromDouble( &str, m_annular_ring_pins/mult );
	m_edit_ann_pins.SetWindowText( str );
	MakeCStringFromDouble( &str, m_annular_ring_vias/mult );
	m_edit_ann_vias.SetWindowText( str );
	MakeCStringFromDouble( &str, m_paste_shrink/mult );
	m_edit_shrink_paste.SetWindowText( str );
	MakeCStringFromDouble( &str, m_space_x/mult );
	m_edit_space_x.SetWindowText( str );
	MakeCStringFromDouble( &str, m_space_y/mult );
	m_edit_space_y.SetWindowText( str );
}
void CDlgCAD::OnCbnSelchangeComboCadUnits()
{
	GetFields();
	if( m_combo_units.GetCurSel() == 0 )
		m_units = MIL;
	else
		m_units = MM;
	SetFields();
}

void CDlgCAD::OnBnClickedCheckCadPilot()
{
	if( m_check_pilot.GetCheck() )
		m_edit_pilot_diam.EnableWindow( 1 );
	else
		m_edit_pilot_diam.EnableWindow( 0 );
}

void CDlgCAD::OnBnClickedCancel()
{
	OnCancel();
}

void CDlgCAD::OnBnClickedButtonDef()
{
	//CString win_t;
	m_edit_folder.GetWindowText( m_folder );
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	CString s[5];
	s[0].Format( "%s\\CAM(%s)(%d-%d-%d)", m_project_folder, m_f_name, timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_year+1900 );
	//s[1].Format( "%s\\Print(%s)", m_project_folder, m_f_name );
	//s[2].Format( "%s\\View1(%s)", m_project_folder, m_f_name );
	//s[3].Format( "%s\\View2(%s)", m_project_folder, m_f_name );
	//s[4].Format( "%s\\%s(%d-%d-%d)", m_project_folder, m_f_name, timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_year+1900 );
	//int i=0;
	//for(; i<5; i++)
	//	if( m_folder.CompareNoCase(s[i]) == 0 )
	//	{
	//		i++;
	//		if(i>4)
	//			i=0;
	//		m_folder = s[i];
	//		break;
	//	}
	//if( i == 5 )
	//{
	//	CString s2[5], s6;
	//	for(i=0; i<5; i++)
	//		s2[i] = s[i].Left(s[i].Find("("));
	//	int f = m_folder.Find("(");
	//	if( f > 0 )
	//	{
	//		s6 = m_folder.Left(f);
	//		for(i=0; i<5; i++)
	//			if( s6.CompareNoCase(s2[i]) == 0 )
	//			{
	//				m_folder = s[i];
	//				break;
	//			}
	//		if( i == 5 )
	//			m_folder = s[0];
	//	}
	//	else
	//	{
	//		m_folder = s[0];
	//	}
	//}
	m_folder = s[0];
	m_edit_folder.SetWindowText( m_folder );
}

void CDlgCAD::OnBnClickedButtonFolder()
{
	if( m_folder.GetLength() == 0 )
		OnBnClickedButtonDef();
	CPathDialog dlg(G_LANGUAGE == 0 ? "Select Folder" : "Выбор папки", 
					G_LANGUAGE == 0 ? "Set CAM output folder" : "Выберите папку", m_folder );
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		m_folder = dlg.GetPathName();
		m_edit_folder.SetWindowText( m_folder );
	}
}

void CDlgCAD::OnBnClickedThermalPins()
{
	if( m_check_thermal_pins.GetCheck() || m_check_thermal_vias.GetCheck() )
		m_check_90.EnableWindow( 1 );
	else
		m_check_90.EnableWindow( 0 );
}

void CDlgCAD::OnBnClickedThermalVias()
{
	OnBnClickedThermalPins();
}

void CDlgCAD::OnBnClickedRenderAllGerbers()
{
	m_check_mirror_bottom.EnableWindow( m_check_render_all.GetCheck() );
	m_dpi.EnableWindow( m_check_render_all.GetCheck() );
	m_png_aa.EnableWindow( m_check_render_all.GetCheck() );
}


void CDlgCAD::OnBnClickedButtonDone()
{
	GetFields();
	OnOK();
}
