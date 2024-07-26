#include "stdafx.h"
#include "FreePcb.h"
#include "Dlg_OpenScad.h"
#include "math.h"
extern CFreePcbApp theApp;

 

IMPLEMENT_DYNAMIC(CDlg_OpenScad, CDialog)
CDlg_OpenScad::CDlg_OpenScad(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg_OpenScad::IDD, pParent)
{
	L_EXTRUDE = "linear_extrude";
	R_EXTRUDE = "rotate_extrude";
	CLR = "color";
	ROTATE = "rotate(";
	TRANSLATE = "translate";
	MATRIX = "matrix:";
	ISHOLE = "it's a hole" ;
	UMIL = "units=MIL" ;
	CLW = "Consider line width" ;
	RAW = "Display transparent";
	MINK = "minkowski";
	GROT = "Global rotation";
	GLIFT = "Global lift";
	HULL = "hull()/*fill the space*/";
	LCAP = "Like a cap";
}

CDlg_OpenScad::~CDlg_OpenScad()
{
}

void CDlg_OpenScad::DoDataExchange(CDataExchange* pDX)
{
	s_global_z.Replace("mm"," mm");
	s_global_z.Replace("mil"," mil");

	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_RADIO_HOLE, m_obj_type);
	DDX_CBIndex(pDX, IDC_COMBO_UNITS, theApp.m_Doc->m_units);
	DDX_CBIndex(pDX, IDC_COMBO_RESOLUTION, m_resolution);
	DDX_Check(pDX, IDC_CORNER_ROUNDING, m_rnd_vtx);
	DDX_Check(pDX, IDC_ROT_VTX1, m_dsp_transparent);
	DDX_Check(pDX, IDC_LIKE_CAP, m_like_cap);
	DDX_Check(pDX, IDC_HULL, m_fill_space);
	DDX_Text(pDX, IDC_EXTRUSION_VALUE, s_extrusion_val);
	DDX_Text(pDX, IDC_EXTRUSION_SCALE, s_extrusion_scale);
	DDX_Text(pDX, IDC_EXTRUSION_ROT, s_extrusion_rot);
	DDX_Text(pDX, IDC_GLOBAL_ROT, s_global_rot);
	DDX_Text(pDX, IDC_LIFT, s_global_z);
	DDX_Text(pDX, IDC_ROT_X, s_ang_x);
	DDX_Text(pDX, IDC_ROT_Y, s_ang_y);
	DDX_Text(pDX, IDC_ROT_Z, s_ang_z);
	DDX_Text(pDX, IDC_MOV_X, s_mov_x);
	DDX_Text(pDX, IDC_MOV_Y, s_mov_y);
	DDX_Text(pDX, IDC_MOV_Z, s_mov_z);
	DDX_Text(pDX, IDC_MATRIX_X, s_matrix_x);
	DDX_Text(pDX, IDC_MATRIX_Y, s_matrix_y);
	DDX_Text(pDX, IDC_MATRIX_Z, s_matrix_z);
	DDX_Text(pDX, IDC_MATRIX_DX, s_matrix_dx);
	DDX_Text(pDX, IDC_MATRIX_DY, s_matrix_dy);
	DDX_Text(pDX, IDC_MATRIX_DZ, s_matrix_dz);
	if( !pDX->m_bSaveAndValidate )
	{
		// incoming
		if( CWnd * wnd = this->GetDlgItem( IDC_COMBO_UNITS ) )
		{
			CComboBox * u = (CComboBox*)wnd;
			if( u )
			{
				u->AddString("NM");
				u->AddString("MM");
				u->AddString("MIL");
				u->SetCurSel( theApp.m_Doc->m_units );
				u->EnableWindow(0);
			}
		}
		if( CWnd * wnd = this->GetDlgItem( IDC_COMBO_CLR ) )
		{
			CComboBox * u = (CComboBox*)wnd;
			if( u )
			{
				u->AddString("Lavender");
				u->AddString("Violet");
				u->AddString("Purple");
				u->AddString("Indigo");
				u->AddString("Pink");
				u->AddString("Aqua");
				u->AddString("SkyBlue");
				u->AddString("Blue");
				u->AddString("Navy");
				u->AddString("Salmon");
				u->AddString("Red");
				u->AddString("Crimson");
				u->AddString("Lime");
				u->AddString("Green");
				u->AddString("Olive");
				u->AddString("Teal");
				u->AddString("Coral");
				u->AddString("Tomato");
				u->AddString("Orange");
				u->AddString("Gold");
				u->AddString("Yellow");
				u->AddString("Cornsilk");
				u->AddString("Tan");
				u->AddString("Peru");
				u->AddString("Chocolate");
				u->AddString("Brown");
				u->AddString("Maroon");
				u->AddString("White");
				u->AddString("Azure");
				u->AddString("Silver");
				u->AddString("Gray");
				u->AddString("DimGray");
				u->AddString("Black");
				
				int cur = u->FindStringExact( 0, m_color );
				if( cur > 0 )
					u->SetCurSel( cur );
				else
				{
					u->SetCurSel( -1 );
					u->SetWindowTextA( m_color );
				}
			}
		}
		if( m_obj_type == 0 )
			if( CWnd * wnd = this->GetDlgItem( IDC_RADIO_BODY ) )
			{
				CButton * u = (CButton*)wnd;
				if( u )
				{
					u->SetCheck( TRUE );
				}
			}
		if( CWnd * wnd = this->GetDlgItem( IDC_COMBO_RESOLUTION ) )
		{
			CComboBox * u = (CComboBox*)wnd;
			if( u )
			{
				u->AddString("5");
				u->AddString("8");
				u->AddString("12");
				u->AddString("16");
				u->AddString("20");
				u->AddString("30");
				u->AddString("40");
				u->AddString("50");
				u->AddString("70");
				u->AddString("100");
				u->AddString("150");
				u->AddString("200");
				CString res;
				res.Format( "%d", m_resolution );
				int cur = u->FindStringExact( 0, res );
				if( cur >= 0 )
					u->SetCurSel( cur );
				else
					u->SetCurSel( 4 );
			}
		}
		OnEnChangeMatrixX();
		OnEnChangeMatrixY();
		OnEnChangeMatrixZ();
		OnEnChangeExtrusionRot();
		OnEnChangeExtrusionValue();
	}
	else
	{
		// outgoing


		// remove space character
		s_global_z.Replace(" ","");

		m_extrusion_val = my_atof( &s_extrusion_val );
		m_extrusion_rot = my_atof( &s_extrusion_rot );
		if( abs(m_extrusion_val) < BY_ZERO && abs(m_extrusion_rot) < BY_ZERO )
		{
			int ret = AfxMessageBox(G_LANGUAGE == 0 ? 
				"You have not entered an extrusion value!\n\nDo you really want to remove the extrusion of this polyline?":
				"Вы не ввели значение выдавливания!\n\nВы действительно хотите удалить выдавливание этой полилинии?", MB_ICONQUESTION | MB_YESNO);
			if( ret == IDNO )
				pDX->Fail();
		}
		m_extrusion_scale = my_atof( &s_extrusion_scale );
		m_global_rot = my_atof( &s_global_rot );
		m_global_z = my_atof( &s_global_z )/(double)(theApp.m_Doc->m_units==MM?NM_PER_MM:NM_PER_MIL);
		m_ang_x = my_atof( &s_ang_x );
		m_ang_y = my_atof( &s_ang_y );
		m_ang_z = my_atof( &s_ang_z );
		m_mov_x = my_atof( &s_mov_x );
		m_mov_y = my_atof( &s_mov_y );
		m_mov_z = my_atof( &s_mov_z );
		m_matrix_x = my_atoi( &s_matrix_x );
		m_matrix_y = my_atoi( &s_matrix_y );
		m_matrix_z = my_atoi( &s_matrix_z );
		m_matrix_dx = my_atof( &s_matrix_dx );
		m_matrix_dy = my_atof( &s_matrix_dy );
		m_matrix_dz = my_atof( &s_matrix_dz );

		if( CWnd * wnd = this->GetDlgItem( IDC_COMBO_CLR ) )
		{
			CComboBox * u = (CComboBox*)wnd;
			if( u )
				u->GetWindowTextA( m_color );
		}
		if( m_resolution >= 0 )
		{
			if( CWnd * wnd = this->GetDlgItem( IDC_COMBO_RESOLUTION ) )
			{
				CComboBox * u = (CComboBox*)wnd;
				if( u )
				{
					CString str;
					u->GetLBText( m_resolution, str );
					m_resolution = my_atoi( &str );
				}
			}
		}
		else
			m_resolution = 10;
	}
}


BEGIN_MESSAGE_MAP(CDlg_OpenScad, CDialog)
	ON_STN_CLICKED(IDC_STATIC_LAYER_1, &CDlg_OpenScad::OnStnClickedStaticLayer1)
	ON_EN_CHANGE(IDC_MATRIX_X, &CDlg_OpenScad::OnEnChangeMatrixX)
	ON_EN_CHANGE(IDC_MATRIX_Y, &CDlg_OpenScad::OnEnChangeMatrixY)
	ON_EN_CHANGE(IDC_MATRIX_Z, &CDlg_OpenScad::OnEnChangeMatrixZ)
	ON_EN_CHANGE(IDC_EXTRUSION_VALUE, &CDlg_OpenScad::OnEnChangeExtrusionValue)
	ON_EN_CHANGE(IDC_EXTRUSION_ROT, &CDlg_OpenScad::OnEnChangeExtrusionRot)
	ON_CBN_SELCHANGE(IDC_COMBO_RESOLUTION, &CDlg_OpenScad::OnCbnSelchangeComboResolution)
	ON_EN_CHANGE(IDC_EXTRUSION_SCALE, &CDlg_OpenScad::OnEnChangeExtrusionScale)
END_MESSAGE_MAP()

void CDlg_OpenScad::Initialize( CString * Descriptor, CString * global_r, CString * global_z, BOOL bFILL )
{
	m_resolution = 15;
	m_obj_type = 0; 
	m_units = 0; 
	m_extrusion_val = 0.0; 
	m_extrusion_rot = 0.0; 
	m_extrusion_scale = 1.0;
	m_global_rot = 0.0;
	m_global_z = 0.0;
	s_global_rot = *global_r;
	s_global_z = *global_z;

	// move, rotate
	m_ang_x = 0.0; 
	m_ang_y = 0.0; 
	m_ang_z = 0.0; 
	m_mov_x = 0.0; 
	m_mov_y = 0.0; 
	m_mov_z = 0.0;

	// matrix
	m_matrix_x = 1;
	m_matrix_y = 1;
	m_matrix_z = 1;
	m_matrix_dx = 0.0;
	m_matrix_dy = 0.0;
	m_matrix_dz = 0.0;

	//checkbox
	m_rnd_vtx = 0;
	m_fill_space = bFILL;
	m_dsp_transparent = 0;
	m_like_cap = 0;

	// color
	m_color = "[0.5,0.5,0.5]";

	// InterpretDescriptor установит 
	// во все строки нужные значения
	m_openscad_data = *Descriptor;
	CString sep = "|";
	InterpretDescriptor( &sep );
}

void CDlg_OpenScad::SetFields()
{
	//m_combo_units.SetCurSel( 0 );
	//m_edit_y.EnableWindow( TRUE );

	//m_combo_angle.SetCurSel( m_angle/90 );
	//::MakeCStringFromDimension( &str, m_x, m_units, FALSE, FALSE, FALSE, 3 );
	//m_edit_x.SetWindowText( str );
	//::MakeCStringFromDimension( &str, m_y, m_units, FALSE, FALSE, FALSE, 3 );
	//m_edit_y.SetWindowText( str );
}

void CDlg_OpenScad::GetFields()
{
	//CString str;
	//m_edit_x.GetWindowText( str );
	//m_x = ::GetDimensionFromString( &str, m_units );
	//m_edit_y.GetWindowText( str );
	//m_y = ::GetDimensionFromString( &str, m_units );
	//m_angle = 90 * m_combo_angle.GetCurSel();
}

CString * CDlg_OpenScad::GenerateOpenscadData( CString * Separator )
{
	m_openscad_data = "";

	// test
	if( m_extrusion_val < BY_ZERO && m_extrusion_val > -BY_ZERO )
		if( m_extrusion_rot < BY_ZERO && m_extrusion_rot > -BY_ZERO )
			return &m_openscad_data;
	//---------------------
	CString s, ddSPACE="    ";
	CString sep = "\n";
	if( Separator )
		sep = *Separator;
	CString new_string = "";
	if( m_units == MIL )
		m_openscad_data += ("// "+UMIL+" //"+sep);
	if( m_obj_type )
		m_openscad_data += ("// "+ISHOLE+" //"+sep);
	if( m_rnd_vtx )
		m_openscad_data += ("// "+CLW+" //"+sep);
	if( m_dsp_transparent )
		m_openscad_data += ("// "+RAW+" //"+sep);
	if( m_like_cap )
		m_openscad_data += ("// "+LCAP+" //"+sep);
	//---------------------
	s.Format( "// %s %.3f //%s", GROT, m_global_rot, sep );
	m_openscad_data += s;
	s.Format( "// %s %.3f%s //%s", GLIFT, m_global_z, (theApp.m_Doc->m_units==MM?"mm":"mil"), sep );
	m_openscad_data += s;
	//---------------------
	BOOL bExtrusionScale = 0;
	if( m_extrusion_scale-1.0 > BY_ZERO || m_extrusion_scale-1.0 < -BY_ZERO )
		bExtrusionScale = 1;
	s_matrix_dx.Format( "%.3f", m_matrix_dx );
	s_matrix_dy.Format( "%.3f", m_matrix_dy );
	s_matrix_dz.Format( "%.3f", m_matrix_dz );
	s.Format( "// %s %s %s %s %s %s %s //%s", MATRIX, s_matrix_x, s_matrix_y, s_matrix_z, s_matrix_dx, s_matrix_dy, s_matrix_dz, sep );
	m_openscad_data += s;
	s.Format( "// resolution $fn = %d //%s", m_resolution, sep );
	m_openscad_data += s;
	//---------------------
	// set color
	{
		if( m_dsp_transparent )
			s.Format( "%s( `%s`, 0.4 )%s%s{%s", CLR, m_color, sep, new_string, sep );
		else
			s.Format( "%s( `%s` )%s%s{%s", CLR, m_color, sep, new_string, sep );
		new_string += ddSPACE;
		m_openscad_data += s;
		m_openscad_data += new_string;
	}
	int mink = -1;
	//---------------------
	// rounding
	if( m_rnd_vtx )
	{
		mink = new_string.GetLength();
		s.Format( "%s()%s%s{%s", MINK, sep, new_string, sep );
		new_string += ddSPACE;
		m_openscad_data += s;
		m_openscad_data += new_string;
		s.Format( "$fn = %d;%s%s", m_resolution, sep, new_string );
		m_openscad_data += s;
	}
	//---------------------
	// mov
	if( m_mov_x > BY_ZERO || m_mov_x < -BY_ZERO ||
		m_mov_y > BY_ZERO || m_mov_y < -BY_ZERO ||
		m_mov_z > BY_ZERO || m_mov_z < -BY_ZERO )
	{
		s.Format( "%s([ %.3f,  %.3f,  %.3f ])%s%s{%s", TRANSLATE, m_mov_x, m_mov_y, m_mov_z, sep, new_string, sep );
		new_string += ddSPACE;
		m_openscad_data += s;
		m_openscad_data += new_string;
	}
	//---------------------
	// additional mov
	{
		s.Format( "*corner1*, 0.0 ])%s%s{%s", sep, new_string, sep );
		new_string += ddSPACE;
		m_openscad_data += s;
		m_openscad_data += new_string;
	}
	//---------------------
	// rotate
	if( m_ang_x > BY_ZERO || m_ang_x < -BY_ZERO ||
		m_ang_y > BY_ZERO || m_ang_y < -BY_ZERO ||
		m_ang_z > BY_ZERO || m_ang_z < -BY_ZERO )
	{
		s.Format( "%s[ %.3f,  %.3f,  %.3f ])%s%s{%s", ROTATE, m_ang_x, m_ang_y, m_ang_z, sep, new_string, sep );
		new_string += ddSPACE;
		m_openscad_data += s;
		m_openscad_data += new_string;
	}
	//---------------------
	// rotate extrude
	if( m_extrusion_rot > BY_ZERO || m_extrusion_rot < -BY_ZERO )
	{
		s.Format( "$fn = %d;%s%s", m_resolution*2, sep, new_string );
		m_openscad_data += s;
		s.Format( "%s( angle= %.3f, convexity=Convexity ) %s%s{%s", R_EXTRUDE, m_extrusion_rot, sep, new_string, sep );
		new_string += ddSPACE;
		m_openscad_data += s;
		m_openscad_data += new_string;
	}
	//---------------------
	// additional mov
	if( bExtrusionScale )
	{
		s.Format( "*center1*, 0.0 ])%s%s{%s", sep, new_string, sep );
		new_string += ddSPACE;
		m_openscad_data += s;
		m_openscad_data += new_string;
	}
	//---------------------
	// linear extrude
	BOOL invertCap = 0;
	if( m_extrusion_val > BY_ZERO || m_extrusion_val < -BY_ZERO )
	{
		if( m_like_cap )
		{
			s.Format( "// %s( %.3f, scale= %.3f )%s%s", L_EXTRUDE, m_extrusion_val, m_extrusion_scale, sep, new_string ); //!!! данные должны оставаться
			m_openscad_data += s;
			if( m_extrusion_val > 0 )
				s.Format( "render(convexity=2) hull()%s%sfor(ang=[0:%d:90.5])%s%s%s( %.3f*(ang>0.5?sin(ang):sin(%d)/3.0), convexity=Convexity )%s%soffset(r=%.3f*(cos(ang)-1))%s%s{%s", sep, new_string, (200/m_resolution), sep, new_string, L_EXTRUDE, m_extrusion_val, (200/m_resolution), sep, new_string, (m_extrusion_val*m_extrusion_scale), sep, new_string, sep );
			else
			{
				s.Format("$fn = %d;%s", m_resolution, sep);
				m_openscad_data += s;
				m_openscad_data += new_string;
				s.Format("render(convexity=2) %s%sfor(ang=[0:%d:90.5])hull(){%s%stranslate([0,0,%.3f*(ang?sin(ang):-0.05)])%s%s    %s( 0.1, convexity=Convexity )%s%s        offset(r=%.3f*(1-cos(ang)))%s%s", sep, new_string, (200 / m_resolution), sep, new_string, abs(m_extrusion_val), sep, new_string, L_EXTRUDE, sep, new_string, abs(m_extrusion_val * m_extrusion_scale), sep, new_string);
				m_openscad_data += s;
				m_openscad_data += new_string + ddSPACE;
				m_openscad_data += ("polygon([ *content* ]);");
				m_openscad_data += sep;
				s.Format("%s%stranslate([0,0,%.3f*((ang+%d)>=90?1:sin(ang+%d))])%s%s    %s( 0.1, convexity=Convexity )%s%s        offset(r=%.3f*(1-cos(ang+%d)))%s%s", sep, new_string, abs(m_extrusion_val), (200 / m_resolution), (200 / m_resolution), sep, new_string, L_EXTRUDE, sep, new_string, abs(m_extrusion_val * m_extrusion_scale), (200 / m_resolution), sep, new_string);
			}
		}
		else
			s.Format( "%s( %.3f, scale= %.3f, convexity=Convexity )%s%s{%s", L_EXTRUDE, m_extrusion_val, m_extrusion_scale, sep, new_string, sep );
		new_string += ddSPACE;
		m_openscad_data += s;
		m_openscad_data += new_string;
	}
	//---------------------
	// content
	m_openscad_data += ("polygon([ *content* ]);");
	m_openscad_data += sep;
	int gL = ddSPACE.GetLength();
	for( int i=new_string.GetLength()-gL; i>=0; i=i-gL )
	{
		for( int ii=i; ii>0; ii-- )
			m_openscad_data += " ";
		if( mink == i )
		{
			for( int ii=4; ii>0; ii-- )
				m_openscad_data += " ";
			s.Format( "sphere( *width* );%s", sep );
			m_openscad_data += s;
			for( int ii=i; ii>0; ii-- )
				m_openscad_data += " ";
		}
		m_openscad_data += "}";
		m_openscad_data += sep;
	}
	return &m_openscad_data;
}

void CDlg_OpenScad::InterpretDescriptor( CString * Separator )
{
	if( !Separator )
		return;
	CString ini_str = "0.0";
	s_extrusion_val = ini_str;
	s_extrusion_rot = ini_str;
	s_extrusion_scale = "1.0";
	s_ang_x = ini_str;
	s_ang_y = ini_str; 
	s_ang_z = ini_str; 
	s_mov_x = ini_str; 
	s_mov_y = ini_str; 
	s_mov_z = ini_str;
	s_matrix_x = "1";
	s_matrix_y = "1";
	s_matrix_z = "1";
	s_matrix_dx = ini_str;
	s_matrix_dy = ini_str;
	s_matrix_dz = ini_str;

	CString str, key;
	CArray<CString> arr;
	//----------------
	if( m_openscad_data.Find( ISHOLE ) > 0 )
		m_obj_type = 1;
	else
		m_obj_type = 0;
	//----------------
	if( m_openscad_data.Find( UMIL ) > 0 )
		m_units = MIL;
	else
		m_units = MM;
	//----------------
	if( m_openscad_data.Find( CLW ) > 0 )
		m_rnd_vtx = 1;
	else
		m_rnd_vtx = 0;
	//----------------
	if( m_openscad_data.Find( RAW ) > 0 )
		m_dsp_transparent = 1;
	else
		m_dsp_transparent = 0;
	//----------------
	if( m_openscad_data.Find( LCAP ) > 0 )
		m_like_cap = 1;
	else
		m_like_cap = 0;
	//----------------
	int f =  m_openscad_data.Find( CLR );
	if( f > 0 )
	{
		int e = m_openscad_data.Find( *Separator, f );
		str = m_openscad_data.Mid( f, e-f );
		str.Replace("`","\"");
		arr.RemoveAll();
		int np = ParseKeyString( &str, &key, &arr );
		if( np >= 2 )
			m_color = arr[0];
	}
	//----------------
	f =  m_openscad_data.Find( "$fn" );
	if( f > 0 )
	{
		int e = m_openscad_data.Find( *Separator, f );
		str = m_openscad_data.Mid( f, e-f );
		arr.RemoveAll();
		int np = ParseKeyString( &str, &key, &arr );
		if( np >= 3 )
			m_resolution = my_atoi( &arr[1] );
	}
	//----------------
	f =  m_openscad_data.Find( MATRIX );
	if( f > 0 )
	{
		int e = m_openscad_data.Find( *Separator, f );
		str = m_openscad_data.Mid( f, e-f );
		arr.RemoveAll();
		int np = ParseKeyString( &str, &key, &arr );
		if( np >= 7 )
		{
			s_matrix_x = arr[0];
			s_matrix_y = arr[1];
			s_matrix_z = arr[2];
			s_matrix_dx = arr[3];
			s_matrix_dy = arr[4];
			s_matrix_dz = arr[5];
		}
	}
	//----------------
	f =  m_openscad_data.Find( L_EXTRUDE );
	if( f > 0 )
	{
		int e = m_openscad_data.Find( *Separator, f );
		str = m_openscad_data.Mid( f, e-f );
		arr.RemoveAll();
		int np = ParseKeyString( &str, &key, &arr );
		if( np >= 2 )
			s_extrusion_val = arr[0];
		if( np >= 4 )
			s_extrusion_scale = arr[2];
	}
	//----------------
	f =  m_openscad_data.Find( R_EXTRUDE );
	if( f > 0 )
	{
		int e = m_openscad_data.Find( *Separator, f );
		str = m_openscad_data.Mid( f, e-f );
		arr.RemoveAll();
		int np = ParseKeyString( &str, &key, &arr );
		if( np >= 2 )
			s_extrusion_rot = arr[1];
	}
	//----------------
	f =  m_openscad_data.Find( ROTATE );
	if( f > 0 )
	{
		int e = m_openscad_data.Find( *Separator, f );
		str = m_openscad_data.Mid( f, e-f );
		str.Replace( ",", " " );
		arr.RemoveAll();
		int np = ParseKeyString( &str, &key, &arr );
		if( np >= 4 )
		{
			s_ang_x = arr[0];
			s_ang_y = arr[1];
			s_ang_z = arr[2];
		}
	}
	//----------------
	f =  m_openscad_data.Find( TRANSLATE );
	if( f > 0 )
	{
		int e = m_openscad_data.Find( *Separator, f );
		str = m_openscad_data.Mid( f, e-f );
		str.Replace( ",", " " );
		arr.RemoveAll();
		int np = ParseKeyString( &str, &key, &arr );
		if( np >= 4 )
		{
			s_mov_x = arr[0];
			s_mov_y = arr[1];
			s_mov_z = arr[2];
		}
	}
	//----------------
	m_extrusion_val = my_atof( &s_extrusion_val );
	m_extrusion_rot = my_atof( &s_extrusion_rot );
	m_extrusion_scale = my_atof( &s_extrusion_scale );
	m_global_rot = my_atof( &s_global_rot );
	m_global_z = my_atof( &s_global_z );
	m_ang_x = my_atof( &s_ang_x );
	m_ang_y = my_atof( &s_ang_y );
	m_ang_z = my_atof( &s_ang_z );
	m_mov_x = my_atof( &s_mov_x );
	m_mov_y = my_atof( &s_mov_y );
	m_mov_z = my_atof( &s_mov_z );
	m_matrix_x = my_atoi( &s_matrix_x );
	m_matrix_y = my_atoi( &s_matrix_y );
	m_matrix_z = my_atoi( &s_matrix_z );
	m_matrix_dx = my_atof( &s_matrix_dx );
	m_matrix_dy = my_atof( &s_matrix_dy );
	m_matrix_dz = my_atof( &s_matrix_dz );
	if( m_units != theApp.m_Doc->m_units )
	{
		double mu = (double)NM_PER_MM/(double)NM_PER_MIL;
		if( m_units < theApp.m_Doc->m_units )
			mu = 1/mu;
		m_extrusion_val /= mu;
		m_extrusion_rot /= mu;
		m_global_rot /= mu;
		m_global_z /= (theApp.m_Doc->m_units==MM?NM_PER_MM:NM_PER_MIL);
		m_mov_x /= mu;
		m_mov_y /= mu;
		m_mov_z /= mu;
		m_matrix_dx /= mu;
		m_matrix_dy /= mu;
		m_matrix_dz /= mu;
		s_extrusion_val.Format( "%.3f", m_extrusion_val );
		s_extrusion_rot.Format( "%.3f", m_extrusion_rot );
		s_global_rot.Format( "%.3f", m_global_rot );
		s_global_z.Format( "%.3f %s", m_global_z, (theApp.m_Doc->m_units==MM?"mm":"mil") );
		s_mov_x.Format( "%.3f", m_mov_x );
		s_mov_y.Format( "%.3f", m_mov_y );
		s_mov_z.Format( "%.3f", m_mov_z );
		s_matrix_dx.Format( "%.3f", m_matrix_dx );
		s_matrix_dy.Format( "%.3f", m_matrix_dy );
		s_matrix_dz.Format( "%.3f", m_matrix_dz );
		m_units = theApp.m_Doc->m_units;
	}
}

void CDlg_OpenScad::OnStnClickedStaticLayer1()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CDlg_OpenScad::OnEnChangeMatrixX()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	if( CWnd * wnd = this->GetDlgItem( IDC_MATRIX_X ) )
	{
		CEdit * u = (CEdit*)wnd;
		if( u )
		{
			CString str;
			u->GetWindowTextA( str );
			int cnt = my_atoi(&str);
			if( cnt < 1 )
			{
				AfxMessageBox(G_LANGUAGE == 0 ? "This value cannot be null":"Это значение не может быть нулевым.");
				u->SetWindowTextA( "1" );
				cnt = 1;
			}
			if( cnt == 1 )
			{
				if( wnd = this->GetDlgItem( IDC_STATIC_DX ) )
					wnd->EnableWindow(0);
				if( wnd = this->GetDlgItem( IDC_MATRIX_DX ) )
					wnd->EnableWindow(0);
			}
			else
			{
				if( wnd = this->GetDlgItem( IDC_STATIC_DX ) )
					wnd->EnableWindow(1);
				if( wnd = this->GetDlgItem( IDC_MATRIX_DX ) )
					wnd->EnableWindow(1);
			}
		}
	}
	// TODO:  Добавьте код элемента управления
}


void CDlg_OpenScad::OnEnChangeMatrixY()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	if( CWnd * wnd = this->GetDlgItem( IDC_MATRIX_Y ) )
	{
		CEdit * u = (CEdit*)wnd;
		if( u )
		{
			CString str;
			u->GetWindowTextA( str );
			int cnt = my_atoi(&str);
			if( cnt < 1 )
			{
				AfxMessageBox(G_LANGUAGE == 0 ? "This value cannot be null":"Это значение не может быть нулевым.");
				u->SetWindowTextA( "1" );
				cnt = 1;
			}
			if( cnt == 1 )
			{
				if( wnd = this->GetDlgItem( IDC_STATIC_DY ) )
					wnd->EnableWindow(0);
				if( wnd = this->GetDlgItem( IDC_MATRIX_DY ) )
					wnd->EnableWindow(0);
			}
			else
			{
				if( wnd = this->GetDlgItem( IDC_STATIC_DY ) )
					wnd->EnableWindow(1);
				if( wnd = this->GetDlgItem( IDC_MATRIX_DY ) )
					wnd->EnableWindow(1);
			}
		}
	}
	// TODO:  Добавьте код элемента управления
}


void CDlg_OpenScad::OnEnChangeMatrixZ()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	if( CWnd * wnd = this->GetDlgItem( IDC_MATRIX_Z ) )
	{
		CEdit * u = (CEdit*)wnd;
		if( u )
		{
			CString str;
			u->GetWindowTextA( str );
			int cnt = my_atoi(&str);
			if( cnt < 1 )
			{
				AfxMessageBox(G_LANGUAGE == 0 ? "This value cannot be null":"Это значение не может быть нулевым.");
				u->SetWindowTextA( "1" );
				cnt = 1;
			}
			if( cnt == 1 )
			{
				if( wnd = this->GetDlgItem( IDC_STATIC_DZ ) )
					wnd->EnableWindow(0);
				if( wnd = this->GetDlgItem( IDC_MATRIX_DZ ) )
					wnd->EnableWindow(0);
			}
			else
			{
				if( wnd = this->GetDlgItem( IDC_STATIC_DZ ) )
					wnd->EnableWindow(1);
				if( wnd = this->GetDlgItem( IDC_MATRIX_DZ ) )
					wnd->EnableWindow(1);
			}
		}
	}
	// TODO:  Добавьте код элемента управления
}


void CDlg_OpenScad::OnEnChangeExtrusionValue()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	if( CWnd * wnd = this->GetDlgItem( IDC_EXTRUSION_VALUE ) )
	{
		CEdit * u = (CEdit*)wnd;
		CWnd * wnd2 = this->GetDlgItem( IDC_EXTRUSION_ROT );
		CEdit * u2 = (CEdit*)wnd2;
		if( u && u2 )
		{
			CString str;
			u->GetWindowTextA( str );
			double val = my_atof(&str);
			if( val > BY_ZERO )
			{
				u2->SetWindowTextA( "0.0" );
				wnd2->EnableWindow(0);
				CWnd * wnd4 = this->GetDlgItem( IDC_LIKE_CAP );
				CButton * u4 = (CButton*)wnd4;
				if( u4 )
					u4->EnableWindow(1);
			}
			else
			{
				wnd2->EnableWindow(1);
				//CWnd * wnd4 = this->GetDlgItem( IDC_LIKE_CAP );
				//CButton * u4 = (CButton*)wnd4;
				//if( u4 )
				//{
				//	u4->SetCheck(0);
				//	u4->EnableWindow(0);
				//}
			}
		}
	}
}


void CDlg_OpenScad::OnEnChangeExtrusionRot()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	if( CWnd * wnd = this->GetDlgItem( IDC_EXTRUSION_ROT ) )
	{
		CEdit * u = (CEdit*)wnd;
		CWnd * wnd2 = this->GetDlgItem( IDC_EXTRUSION_VALUE );
		CEdit * u2 = (CEdit*)wnd2;
		CWnd * wnd3 = this->GetDlgItem( IDC_EXTRUSION_SCALE );
		CEdit * u3 = (CEdit*)wnd3;
		if( u && u2 && u3 )
		{
			CString str;
			u->GetWindowTextA( str );
			double val = my_atof(&str);
			if( val > BY_ZERO )
			{
				u2->SetWindowTextA( "0.0" );
				wnd2->EnableWindow(0);
				wnd3->EnableWindow(0);
				CWnd * wnd4 = this->GetDlgItem( IDC_LIKE_CAP );
				CButton * u4 = (CButton*)wnd4;
				if( u4 )
				{
					u4->SetCheck(0);
					u4->EnableWindow(0);
				}
			}
			else
			{
				wnd2->EnableWindow(1);
				wnd3->EnableWindow(1);
				CWnd * wnd4 = this->GetDlgItem( IDC_LIKE_CAP );
				CButton * u4 = (CButton*)wnd4;
				if( u4 )
					u4->EnableWindow(1);
			}
		}
	}
}


void CDlg_OpenScad::OnCbnSelchangeComboResolution()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CDlg_OpenScad::OnEnChangeExtrusionScale()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
}
