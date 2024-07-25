// DlgAddArea.cpp : implementation file
//

#include "stdafx.h"
#include "FreePcb.h"
#include "DlgAddArea.h"
#include "layers.h"

// globals
int gHatch = CPolyLine::NO_HATCH;

// CDlgAddArea dialog

IMPLEMENT_DYNAMIC(CDlgAddArea, CDialog)
CDlgAddArea::CDlgAddArea(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddArea::IDD, pParent)
{
}

CDlgAddArea::~CDlgAddArea()
{
}

void CDlgAddArea::DoDataExchange(CDataExchange* pDX)
{
	CString str;
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_NET, m_combo_net);
	DDX_Control(pDX, IDC_AREA_WIDTH, m_area_width);
	DDX_Control(pDX, IDC_LIST_LAYER, m_list_layer);
	DDX_Control(pDX, IDC_RADIO_NONE, m_radio_none);
	DDX_Control(pDX, IDC_RADIO_FULL, m_radio_full);
	DDX_Control(pDX, IDC_RADIO_EDGE, m_radio_edge);
	if( !pDX->m_bSaveAndValidate )
	{
		// incoming, initialize net list
		cnet * net = m_nlist->GetFirstNet();
		while( net )
		{
			m_combo_net.AddString( net->name );
			net = m_nlist->GetNextNet(/*LABEL*/); 
		}
		if( m_net )
		{
			bNewArea = FALSE;
			int i = m_combo_net.SelectString( -1, m_net->name );
			if( i == CB_ERR )
				ASSERT(0);
		}
		else
			bNewArea = TRUE;

		// initialize layers
		m_num_layers = m_num_layers-LAY_TOP_COPPER;
		for( int il=0; il<m_num_layers; il++ )
		{
			m_list_layer.InsertString( il, &layer_str[il+LAY_TOP_COPPER][0] );
		}
		m_list_layer.SetCurSel( max(m_layer,LAY_TOP_COPPER) - LAY_TOP_COPPER );
		if( m_hatch == -1 )
			m_hatch = gHatch;	
		if( m_hatch == CPolyLine::NO_HATCH && m_width == 0 )
		{
			m_area_width.EnableWindow( 0 );
			m_radio_none.SetCheck( 1 );
		}
		else if( m_hatch == CPolyLine::DIAGONAL_FULL )
			m_radio_full.SetCheck( 1 );	 
		else
			m_radio_edge.SetCheck( 1 );
		::MakeCStringFromDimension( &str, m_width, m_units, FALSE, FALSE, FALSE, m_units==MIL?0:2 );
		m_area_width.SetWindowTextA( str );
	}
	else
	{
		// outgoing
		m_layer = m_list_layer.GetCurSel() + LAY_TOP_COPPER;
		m_combo_net.GetWindowText( m_net_name );

		POSITION pos;
		CString name;
		void * ptr;
		m_net = m_nlist->GetNetPtrByName( &m_net_name );
		if( !m_net )
		{
			AfxMessageBox(G_LANGUAGE == 0 ? "Illegal net name":"Недопустимое имя эл.цепи");
			pDX->Fail();
		}
		m_area_width.GetWindowText( str );
		double mult = NM_PER_MIL;
		if( m_units == MM )
			mult = 1000000.0;
		m_width = mult*atof( str ); 
		if( m_radio_none.GetCheck() )
		{
			m_width = 0;
			m_hatch = CPolyLine::NO_HATCH;
		}
		else if( m_radio_full.GetCheck() )
		{
			if( m_width <= NM_PER_MIL )
			{
				AfxMessageBox(G_LANGUAGE == 0 ? "Illegal fill width":"Недопустимое значение толщины контурной линии");
				pDX->Fail();
			}
			m_hatch = CPolyLine::DIAGONAL_FULL;
		}
		else if( m_radio_edge.GetCheck() && m_width == 0 )
			m_hatch = CPolyLine::DIAGONAL_EDGE;
		else 
			m_hatch = CPolyLine::NO_HATCH;
		if( bNewArea )
			gHatch = m_hatch;
	}
}


BEGIN_MESSAGE_MAP(CDlgAddArea, CDialog)
	ON_BN_CLICKED(ID_Q1, &CDlgAddArea::OnBnClickedQ1)
	ON_BN_CLICKED(ID_Q2, &CDlgAddArea::OnBnClickedQ2)
	ON_BN_CLICKED(ID_Q3, &CDlgAddArea::OnBnClickedQ3)
	ON_BN_CLICKED(IDC_RADIO_NONE, &CDlgAddArea::OnBnClickedRadioNone)
	ON_BN_CLICKED(IDC_RADIO_EDGE, &CDlgAddArea::OnBnClickedRadioEdge)
	ON_BN_CLICKED(IDC_RADIO_FULL, &CDlgAddArea::OnBnClickedRadioFull)
END_MESSAGE_MAP()


// CDlgAddArea message handlers

void CDlgAddArea::Initialize( CNetList * nl, int nlayers, 
							 cnet * net, int layer, int hatch, int width, int units, BOOL EN_W )
{
	m_nlist = nl;
	m_num_layers = nlayers;
	m_net = net;
	m_layer = layer;
	if( m_layer < LAY_TOP_COPPER )
		m_layer += 2; // when sm layer is active
	m_hatch = hatch;
	m_width = width;
	m_units = units;
	m_en_w = EN_W;
}


void CDlgAddArea::OnBnClickedQ1()
{
	// TODO: добавьте свой код обработчика уведомлений
	if(G_LANGUAGE==0)
		AfxMessageBox("This type of copper area is a contour line that needs to be filled. "\
			"It does not interact with any project objects. Select the side of this area and press F4 to fill it.", MB_ICONINFORMATION);
	else
		AfxMessageBox("Этот тип полигона представляет собой контурную линию для будущей заливки. Он не взаимодействует ни с какими объектами проекта. Выберите сторону этого полигона и нажмите F4, чтобы залить его", MB_ICONINFORMATION);
}


void CDlgAddArea::OnBnClickedQ2()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (G_LANGUAGE == 0)
		AfxMessageBox("This type of copper area takes on its final appearance in gerber files. "\
				  "In the project, it is displayed as a contour line of the copper area. "\
				  "It is convenient to use where there are fewer copper traces and other objects, "\
				  "for example, in the inner layers of a printed circuit board. Copper area "\
				  "side width of this type can be any value, including 0. \nIf you are using this "\
				  "type of copper area, then at the end, do a test \n(DRC >> Check Copper Areas) "\
				  "for tearing into pieces.", MB_ICONINFORMATION);
	else
		AfxMessageBox("Этот тип полигонов приобретает свой окончательный вид в файлах Gerber, где присутствуют все необходимые зазоры. "\
			"В проекте он отображается в виде контурной линии участка меди. Удобно использовать там, "\
			"где меньше медных дорожек и других предметов, например, во внутренних слоях печатной платы. "\
			"Толщина контурной линии полигона этого типа может иметь любое значение, включая 0. \nЕсли вы "\
			"используете этот тип медной области, то в конце выполните проверку (Тестирование >> Проверка медных полигонов) для предупреждения разрыва на островки из-за зазоров, присутствующих в гербер-файле.", MB_ICONINFORMATION);
}


void CDlgAddArea::OnBnClickedQ3()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (G_LANGUAGE == 0)
		AfxMessageBox("Copper fill object. You can add it manually, or create it automatically "\
			"from a copper area like \"Ghost\".", MB_ICONINFORMATION);
	else
		AfxMessageBox("Объект медной заливки. Можно добавлять его вручную или создавать автоматически из полигона типа «Призрак».", MB_ICONINFORMATION);
}


void CDlgAddArea::OnBnClickedRadioNone()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_area_width.EnableWindow( 0 );
}


void CDlgAddArea::OnBnClickedRadioEdge()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_area_width.EnableWindow( 1 );
}


void CDlgAddArea::OnBnClickedRadioFull()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_area_width.EnableWindow( 1 );
}
