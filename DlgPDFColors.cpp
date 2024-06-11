// DlgLayers.cpp : implementation file
//
// uses global arrays in layers.h
//
#include "stdafx.h"
#include "FreePcb.h"
#include "DlgPDFColors.h"
#include "layers.h"
#include ".\dlgPDFcolors.h"
#include "math.h"

// CDlgPDFLayers dialog

IMPLEMENT_DYNAMIC(CDlgPDFLayers, CDialog)
CDlgPDFLayers::CDlgPDFLayers(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPDFLayers::IDD, pParent)
{
}

CDlgPDFLayers::~CDlgPDFLayers()
{
}

void CDlgPDFLayers::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	if( !pDX->m_bSaveAndValidate )
	{
		// on entry
		for( int i=m_nlayers; i<NUM_DLG_LAYERS; i++ )
			GetDlgItem( IDC_CHECK_LAYER_3+i-2 )->EnableWindow( 0 );
	}
	for( int i=0; i<NUM_DLG_LAYERS; i++ )
	{
		if( i>1 )
			DDX_Check( pDX, IDC_CHECK_LAYER_3+i-2, m_vis[i] );
	}
	DDX_Control( pDX, IDC_TEXT_FONT, m_font_box );
	DDX_Control( pDX, IDC_EDIT_MARGIN, m_margin_edit );
	if( !pDX->m_bSaveAndValidate )
	{
		CString str;
		str.Format( "%d", abs(m_use_font1/NM_PER_MIL) );
		m_font_box.SetWindowTextA( str );
		if( m_use_font1 > 0 )
			m_use_font1 = 1;
		else
			m_use_font1 = 0;
		if( m_use_font2 > 0 )
			m_use_font2 = 1;
		else
			m_use_font2 = 0;
		if( m_use_font3 > 0 )
			m_use_font3 = 1;
		else
			m_use_font3 = 0;
	}
	DDX_Check( pDX, IDC_CHECK_REF, m_use_font1 );
	DDX_Check( pDX, IDC_CHECK_VALUE, m_use_font2 );
	DDX_Check( pDX, IDC_CHECK_PACKAGE, m_use_font3 );

	DDX_Check( pDX, IDC_CHECK_LAYER_SYS_CLRS, m_sys_colors );
	DDX_Check( pDX, IDC_CHECK_MARGIN, m_check_margin );
	if( pDX->m_bSaveAndValidate )
	{
		// on OK
		for( int i=0; i<NUM_DLG_LAYERS; i++ )
		{
			m_rgb_ptr[i*3] = m_rgb[i][0];
			m_rgb_ptr[i*3+1] = m_rgb[i][1];
			m_rgb_ptr[i*3+2] = m_rgb[i][2];
		}
		{
			CString mrg;
			m_margin_edit.GetWindowTextA( mrg );
			m_margin = my_atof(&mrg);
			if( m_check_margin == 0 )
				m_margin = -m_margin;
		}
		{
			int m_check1 = m_use_font1;
			int m_check2 = m_use_font2;
			int m_check3 = m_use_font3;
			CString mrg;
			m_font_box.GetWindowTextA( mrg );
			m_use_font1 = my_atoi(&mrg);
			DDV_MinMaxInt(pDX, m_use_font1, 1, 100 );
			m_use_font1 *= NM_PER_MIL;
			m_use_font2 = m_use_font1;
			m_use_font3 = m_use_font2;
			if( m_check1 == 0 )
				m_use_font1 = -m_use_font1;
			if( m_check2 == 0 )
				m_use_font2 = -m_use_font2;
			if( m_check3 == 0 )
				m_use_font3 = -m_use_font3;
		}
	}
	else
	{
		CString str;
		str.Format( "%.2f", fabs(m_margin) );
		m_margin_edit.SetWindowTextA( str );
	}
}

BEGIN_MESSAGE_MAP(CDlgPDFLayers, CDialog)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_LAYER_1, OnBnClickedButtonLayer1)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_2, OnBnClickedButtonLayer2)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_3, OnBnClickedButtonLayer3)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_4, OnBnClickedButtonLayer4)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_5, OnBnClickedButtonLayer5)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_6, OnBnClickedButtonLayer6)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_7, OnBnClickedButtonLayer7)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_8, OnBnClickedButtonLayer8)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_9, OnBnClickedButtonLayer9)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_10, OnBnClickedButtonLayer10)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_11, OnBnClickedButtonLayer11)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_12, OnBnClickedButtonLayer12)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_13, OnBnClickedButtonLayer13)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_14, OnBnClickedButtonLayer14)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_15, OnBnClickedButtonLayer15)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_16, OnBnClickedButtonLayer16)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_17, OnBnClickedButtonLayer17)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_18, OnBnClickedButtonLayer18)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_19, OnBnClickedButtonLayer19)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_20, OnBnClickedButtonLayer20)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_21, OnBnClickedButtonLayer21)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_22, OnBnClickedButtonLayer22)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_23, OnBnClickedButtonLayer23)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_24, OnBnClickedButtonLayer24)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_25, OnBnClickedButtonLayer25)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_26, OnBnClickedButtonLayer26)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_27, OnBnClickedButtonLayer27)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_28, OnBnClickedButtonLayer28)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_29, OnBnClickedButtonLayer29)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_30, OnBnClickedButtonLayer30)
	ON_BN_CLICKED(IDC_BUTTON_LAYER_31, OnBnClickedButtonLayer31)
	ON_BN_CLICKED(IDCANCEL, OnBnCancel)
END_MESSAGE_MAP()

void CDlgPDFLayers::Initialize( int nlayers, 
								int vis[], 
								int rgb[][3], 
								float margin, 
								int sys_colors,
								int use_font1,
								int use_font2,
								int use_font3 )
{
	m_sys_colors = sys_colors;
	m_use_font1 = use_font1;
	m_use_font2 = use_font2;
	m_use_font3 = use_font3;

	m_margin = margin;
	if( m_margin > 0.01 )
		m_check_margin = 1;
	else
		m_check_margin = 0;
	m_nlayers = nlayers;
	m_vis = vis;
	m_rgb_ptr = (int*)rgb;
	for( int i=0; i<NUM_DLG_LAYERS; i++ )
	{
		m_rgb[i][0] = m_rgb_ptr[i*3];
		m_rgb[i][1] = m_rgb_ptr[i*3+1];
		m_rgb[i][2] = m_rgb_ptr[i*3+2];
	}
}


// CDlgPDFLayers message handlers
//

// set color boxes
//
HBRUSH CDlgPDFLayers::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  Change any attributes of the DC here
	// TODO:  Return a different brush if the default is not desired
	if ( pWnd->GetDlgCtrlID() >= IDC_STATIC_LAYER_1 && pWnd->GetDlgCtrlID() <= (IDC_STATIC_LAYER_1+NUM_DLG_LAYERS-1) )
	{
		int i = pWnd->GetDlgCtrlID() - IDC_STATIC_LAYER_1;
		// Set layer color
		pDC->SetTextColor(RGB(m_rgb[i][0], m_rgb[i][1], m_rgb[i][2]));
		pDC->SetBkMode(TRANSPARENT);
		m_brush.DeleteObject();
		m_brush.CreateSolidBrush( RGB(m_rgb[i][0], m_rgb[i][1], m_rgb[i][2]) );
		hbr = m_brush;
	}
	return hbr;
}

// handle edit button clicks
//
void CDlgPDFLayers::OnBnClickedButtonLayer1() { EditColor( 0 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer2() { EditColor( 1 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer3() { EditColor( 2 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer4() { EditColor( 3 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer5() { EditColor( 4 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer6() { EditColor( 5 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer7() { EditColor( 6 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer8() { EditColor( 7 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer9() { EditColor( 8 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer10() { EditColor( 9 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer11() { EditColor( 10 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer12() { EditColor( 11 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer13() { EditColor( 12 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer14() { EditColor( 13 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer15() { EditColor( 14 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer16() { EditColor( 15 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer17() { EditColor( 16 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer18() { EditColor( 17 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer19() { EditColor( 18 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer20() { EditColor( 19 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer21() { EditColor( 20 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer22() { EditColor( 21 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer23() { EditColor( 22 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer24() { EditColor( 23 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer25() { EditColor( 24 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer26() { EditColor( 25 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer27() { EditColor( 26 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer28() { EditColor( 27 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer29() { EditColor( 28 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer30() { EditColor( 29 ); }
void CDlgPDFLayers::OnBnClickedButtonLayer31() { EditColor( 30 ); }

// edit color for selected layer
//
void CDlgPDFLayers::EditColor( int layer )
{
	CColorDialog dlg( RGB(m_rgb[layer][0], m_rgb[layer][1], m_rgb[layer][2]), 
		CC_FULLOPEN | CC_ANYCOLOR );
	int ret = dlg.DoModal();
	if( ret == IDOK )
	{
		COLORREF color = dlg.GetColor();
		m_rgb[layer][0] = GetRValue( color );
		m_rgb[layer][1] = GetGValue( color );
		m_rgb[layer][2] = GetBValue( color );
		Invalidate( FALSE );
	}
}

void CDlgPDFLayers::OnBnCancel()
{
	OnOK();
	OnCancel();
}

