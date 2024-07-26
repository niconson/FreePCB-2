// CDlgViaGrig.cpp : implementation file
//

#include "stdafx.h"
#include "FreePcb.h"
#include "DlgViaGrig.h"


// dialog

IMPLEMENT_DYNAMIC(CDlgViaGrig, CDialog)
CDlgViaGrig::CDlgViaGrig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgViaGrig::IDD, pParent)
{
	m_u = 0;
	m_out_x = 0;
	m_out_y = 0;
	m_def_via_w = 0;
	m_def_hole_w = 0;
}  

CDlgViaGrig::~CDlgViaGrig()
{
}

void CDlgViaGrig::Initialize( int def_v, int def_h, int sp_x, int sp_y )
{
	if( def_v < 0 )
		m_u = 0;
	else
		m_u = 1;
	m_def_via_w = abs(def_v);
	m_def_hole_w = abs(def_h);
	if( sp_x )
	{
		m_out_x = sp_x;
		m_out_y = sp_y;
	}
	else
	{
		m_out_x = m_def_via_w*2;
		m_out_y = m_def_via_w*2;
	}
}

void CDlgViaGrig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_UNITS, m_units);
	DDX_Control(pDX, IDC_EDIT_SPACE_X, m_space_x);
	DDX_Control(pDX, IDC_EDIT_SPACE_Y, m_space_y);
	DDX_Control(pDX, IDC_EDIT_VIA_SIZE, m_via_size);
	DDX_Control(pDX, IDC_EDIT_HOLE_SIZE, m_hole_size);
	DDX_Control(pDX, IDC_CHECK_AS_PART, m_as_part);
	DDX_Control(pDX, IDC_CHECK_CHESS, m_chess);
	if( pDX->m_bSaveAndValidate )
	{
		GetFields();
		if ( m_out_x < m_def_via_w || m_out_y < m_def_via_w || m_def_via_w < NM_PER_MIL*5 || m_def_hole_w < NM_PER_MIL )
		{
			AfxMessageBox(G_LANGUAGE == 0 ? "Illegal value":"Недопустимое значение параметра");
			pDX->Fail();
		}
		as_part = m_as_part.GetCheck();
		chess = m_chess.GetCheck();
	}
	else
	{
		m_chess.SetCheck(2);
		m_units.AddString( "MM" );
		m_units.AddString( "MIL" );
		if( m_u == 1 )
			m_units.SelectString( 0, "MIL" );
		else
			m_units.SelectString( 0, "MM" );
		SetFields();
	}
}

void CDlgViaGrig::GetFields()
{
	CString sp_x, sp_y, via_w, hole_w;
	m_space_x.GetWindowText(sp_x);
	m_space_y.GetWindowText(sp_y);
	m_via_size.GetWindowText(via_w);
	m_hole_size.GetWindowText(hole_w);
	//
	float fx = my_atof( &sp_x );
	float fy = my_atof( &sp_y );
	float fv = my_atof( &via_w );
	float fh = my_atof( &hole_w );
	if( m_u == 0 )
	{
		fx *= NM_PER_MM;
		fy *= NM_PER_MM;
		fv *= NM_PER_MM;
		fh *= NM_PER_MM;
	}
	else if( m_u == 1 )
	{
		fx *= NM_PER_MIL;
		fy *= NM_PER_MIL;
		fv *= NM_PER_MIL;
		fh *= NM_PER_MIL;
	}
	else
		ASSERT(0);
	m_out_x = fx;
	m_out_y = fy;
	m_def_via_w = fv;
	m_def_hole_w = fh;
	//
	m_u = m_units.GetCurSel();
}

void CDlgViaGrig::SetFields()
{
	CString str;
	if( m_u == 0 )
	{
		float f = (float)m_def_via_w/(float)NM_PER_MM;
		str.Format( "%.2f", f );
		m_via_size.SetWindowTextA(str);
		f = (float)m_def_hole_w/(float)NM_PER_MM;
		str.Format( "%.2f", f );
		m_hole_size.SetWindowTextA(str);
		f = (float)m_out_x/(float)NM_PER_MM;
		str.Format( "%.2f", f );
		m_space_x.SetWindowTextA(str);
		f = (float)m_out_y/(float)NM_PER_MM;
		str.Format( "%.2f", f );
		m_space_y.SetWindowTextA(str);
	}
	else
	{
		str.Format( "%d", m_def_via_w/NM_PER_MIL );
		m_via_size.SetWindowTextA(str);
		str.Format( "%d", m_def_hole_w/NM_PER_MIL );
		m_hole_size.SetWindowTextA(str);
		str.Format( "%d", m_out_x/NM_PER_MIL );
		m_space_x.SetWindowTextA(str);
		str.Format( "%d", m_out_y/NM_PER_MIL );
		m_space_y.SetWindowTextA(str);
	}
}

void CDlgViaGrig::OnCbnSelchangeComboUnits()
{
	GetFields();
	m_u = !m_units.GetCurSel();
	SetFields();
}

BEGIN_MESSAGE_MAP(CDlgViaGrig, CDialog)
	ON_CBN_SELCHANGE(IDC_UNITS, OnCbnSelchangeComboUnits)
END_MESSAGE_MAP()


// CDlgViaGrig message handlers
