// CDlgCrop.cpp : implementation file
//

#include "stdafx.h"
#include "FreePcb.h"
#include "DlgCrop.h"
#include ".\dlgcrop.h"


// CDlgCrop dialog

IMPLEMENT_DYNAMIC(CDlgCrop, CDialog)
CDlgCrop::CDlgCrop(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCrop::IDD, pParent)
{
	m_cur_sel = -1;
}

CDlgCrop::~CDlgCrop()
{
}

void CDlgCrop::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ADD_NEW,		m_check_prev);
	DDX_Control(pDX, IDC_CHECK_DEL_ISLAND,	m_check_islands);
	DDX_Control(pDX, IDC_CHECK_ADD_THRML,	m_check_add_thrml);
	DDX_Control(pDX, IDC_CHECK_NO_THRML,	m_check_no_thrml);
	DDX_Control(pDX, IDC_CHECK_ANY_LAYER,	m_check_all_layers);
	DDX_Control(pDX, IDC_CHECK_OCTAGON,		m_check_octagon);
	DDX_Control(pDX, IDC_CHECK_NET_SEL,		m_check_net);
	DDX_Control(pDX, IDC_CHECK_WID,			m_check_width);
	DDX_Control(pDX, IDC_CHECK_PADS,		m_check_pads);
	DDX_Control(pDX, IDC_CHECK_SEGS,		m_check_segs);
	DDX_Control(pDX, IDC_CHECK_AREAS,		m_check_areas);
	DDX_Control(pDX, IDC_CHECK_HOLES,		m_check_holes);
	DDX_Control(pDX, IDC_CHECK_TEXTS,		m_check_texts);
	DDX_Control(pDX, IDC_CHECK_BOARD,		m_check_board);
	DDX_Control(pDX, IDC_CHECK_POLYLINES,	m_check_polylines);
	DDX_Control(pDX, IDC_COMBO_NET_SEL,		m_combo_net);
	DDX_Control(pDX, IDC_EDIT_W,			m_edit_width);
	DDX_Control(pDX, IDC_CLR_PADS,			m_edit_pad);
	DDX_Control(pDX, IDC_CLR_SEGS,			m_edit_seg);
	DDX_Control(pDX, IDC_CLR_AREAS,			m_edit_area);
	DDX_Control(pDX, IDC_CLR_HOLES,			m_edit_hole);
	DDX_Control(pDX, IDC_CLR_TEXTS,			m_edit_text);
	DDX_Control(pDX, IDC_CLR_BOARD,			m_edit_board);
	DDX_Control(pDX, IDC_CLR_POLYLINES,		m_edit_polyline);
	DDX_Control(pDX, IDC_CLR_THERMAL,		m_edit_thermal);
	//
	DDX_Control(pDX, IDC_EDIT_NEW_NAME,		m_edit_new_name);
	DDX_Control(pDX, IDC_COMBO_SETTINGS,	m_combo_settings);
	DDX_Control(pDX, IDC_BUTTON_DELETE_SETTING,		m_delete_setting);
	DDX_Control(pDX, IDC_BUTTON_SAVE,		m_save);
	//
	if( !pDX->m_bSaveAndValidate )
	{
		// incoming
		for( int c=0; c<nets.GetSize(); c++ )
			m_combo_net.AddString(nets[c]);	
		//
		CString key;
		CArray<CString> arr;
		for( int item=0; item<m_crop_data->GetSize(); item++ )
		{
			int np = ParseKeyString( &m_crop_data->GetAt(item), &key, &arr );
			if( np == 13 )
				m_combo_settings.AddString(arr[10]);
		}
		LoadCropData(0);
		OnBnClickedThrml();
		OnChange();
	}
	else
	{
		// outgoing
		SaveCropData( FALSE );
		int isel = m_combo_settings.GetCurSel();
		if( isel > 0 )
		{		
			CString s = m_crop_data->GetAt(isel);
			m_crop_data->InsertAt(0,s);
			m_crop_data->RemoveAt(isel+1);
			m_combo_settings.GetLBText(isel,s);
			m_combo_settings.InsertString(0,s);
			m_combo_settings.DeleteString(isel+1);
		}
	}
}


BEGIN_MESSAGE_MAP(CDlgCrop, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_SETTINGS, OnChange)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_SETTING, OnBnClickedDelete)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedSave)
	ON_BN_CLICKED(IDC_CHECK_ADD_THRML, OnBnClickedThrml)
	ON_BN_CLICKED(IDC_CHECK_NO_THRML, OnBnClickedThrml)
	ON_BN_CLICKED(IDCANCEL, &CDlgCrop::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgFindPart message handlers

void CDlgCrop::Initialize( CArray<CString> * crop_data, int crop_flags )
{
	m_crop_data = crop_data;
	m_crop_flags = crop_flags;
}


void CDlgCrop::LoadCropData( int item )
{
	CString key;
	CArray<CString> arr;
	int np = ParseKeyString( &m_crop_data->GetAt(item), &key, &arr );
	if( np == 13 )
	{
		m_edit_width.SetWindowTextA(arr[0]);
		m_edit_pad.SetWindowTextA(arr[1]);
		m_edit_seg.SetWindowTextA(arr[2]);
		m_edit_area.SetWindowTextA(arr[3]);
		m_edit_hole.SetWindowTextA(arr[4]);
		m_edit_text.SetWindowTextA(arr[5]);
		m_edit_board.SetWindowTextA(arr[6]);
		m_edit_polyline.SetWindowTextA(arr[7]);
		m_edit_thermal.SetWindowTextA(arr[8]);
		int inet = m_combo_net.FindStringExact(0,arr[9]);
		if( inet >= 0 )
			m_combo_net.SetCurSel(inet);
		key = arr[10];
		inet = m_combo_settings.FindStringExact(0,key);
		if( inet >= 0 )
		{
			m_combo_settings.SetCurSel(inet);
			m_cur_sel = inet;
		}
		m_crop_flags = my_atoi( &arr[11] );
	}
	else
	{
		m_edit_width.SetWindowTextA("0.0");
		m_edit_pad.SetWindowTextA("0.0");
		m_edit_seg.SetWindowTextA("0.0");
		m_edit_area.SetWindowTextA("0.0");
		m_edit_hole.SetWindowTextA("0.0");
		m_edit_text.SetWindowTextA("0.0");
		m_edit_board.SetWindowTextA("0.0");
		m_edit_polyline.SetWindowTextA("0.0");
		m_edit_thermal.SetWindowTextA("0.0");
		m_combo_net.SetCurSel(-1);
		m_combo_settings.SetCurSel(-1);
		m_cur_sel = -1;
		m_crop_flags = 0;
	}
	//
	//
	//
	if( getbit(m_crop_flags, MC_REMOVE_PREV) )
		m_check_prev.SetCheck(1);
	else
	{
		m_check_prev.SetCheck(0);
		//m_check_prev.EnableWindow(0);
	}
	//
	if( getbit(m_crop_flags, MC_NO_ISLANDS) )
		m_check_islands.SetCheck(1);
	else
		m_check_islands.SetCheck(0);
	//
	if( getbit(m_crop_flags, MC_THERMAL) )
		m_check_add_thrml.SetCheck(1);
	else
		m_check_add_thrml.SetCheck(0);
	//
	if( getbit(m_crop_flags, MC_NO_THERMAL) )
		m_check_no_thrml.SetCheck(1);
	else		
		m_check_no_thrml.SetCheck(0);
	//
	if( getbit(m_crop_flags, MC_ALL_LAYERS) )
		m_check_all_layers.SetCheck(1);
	else		
		m_check_all_layers.SetCheck(0);
	//
	if( getbit(m_crop_flags, MC_OCTAGON) )
		m_check_octagon.SetCheck(1);
	else		
		m_check_octagon.SetCheck(0);
	//
	if( getbit(m_crop_flags, MC_ALL_NETS) == 0 )
		m_check_net.SetCheck(1);
	else		
		m_check_net.SetCheck(0);
	//
	if( getbit(m_crop_flags, MC_WIDTH) )
		m_check_width.SetCheck(1);
	else		
		m_check_width.SetCheck(0);
	//
	if( getbit(m_crop_flags, MC_PADS) )
		m_check_pads.SetCheck(1);
	else		
		m_check_pads.SetCheck(0); 
	//
	if( getbit(m_crop_flags, MC_SEGS) )
		m_check_segs.SetCheck(1);
	else		
		m_check_segs.SetCheck(0);
	//
	if( getbit(m_crop_flags, MC_AREAS) )
		m_check_areas.SetCheck(1);
	else		
		m_check_areas.SetCheck(0);
	//
	if( getbit(m_crop_flags, MC_HOLES) )
		m_check_holes.SetCheck(1);
	else		
		m_check_holes.SetCheck(0);
	//
	if( getbit(m_crop_flags, MC_TEXTS) )
		m_check_texts.SetCheck(1);
	else		
		m_check_texts.SetCheck(0);
	//
	if( getbit(m_crop_flags, MC_BOARD) )
		m_check_board.SetCheck(1);
	else		
		m_check_board.SetCheck(0);
	//
	if( getbit(m_crop_flags, MC_POLYLINES) )
		m_check_polylines.SetCheck(1);
	else		
		m_check_polylines.SetCheck(0);
}

void CDlgCrop::SaveCropData( int new_event )
{
	CString m_crop_dat = "crop_data: ";
	CString str;
	m_edit_width.GetWindowTextA(str);
	m_width = my_atof(&str);
	if( str.GetLength() == 0 )
		m_crop_dat += "0.0 ";
	else
		m_crop_dat += ("\"" + str + "\" ");
	m_edit_pad.GetWindowTextA(str);
	m_pad_clearance = my_atof(&str);
	if( str.GetLength() == 0 )
		m_crop_dat += "0.0 ";
	else
		m_crop_dat += ("\"" + str + "\" ");
	m_edit_seg.GetWindowTextA(str);
	m_seg_clearance = my_atof(&str);
	if( str.GetLength() == 0 )
		m_crop_dat += "0.0 ";
	else
		m_crop_dat += ("\"" + str + "\" ");
	m_edit_area.GetWindowTextA(str);
	m_area_clearance = my_atof(&str);
	if( str.GetLength() == 0 )
		m_crop_dat += "0.0 ";
	else
		m_crop_dat += ("\"" + str + "\" ");
	m_edit_hole.GetWindowTextA(str);
	m_hole_clearance = my_atof(&str);
	if( str.GetLength() == 0 )
		m_crop_dat += "0.0 ";
	else
		m_crop_dat += ("\"" + str + "\" ");
	m_edit_text.GetWindowTextA(str);
	m_text_clearance = my_atof(&str);
	if( str.GetLength() == 0 )
		m_crop_dat += "0.0 ";
	else
		m_crop_dat += ("\"" + str + "\" ");
	m_edit_board.GetWindowTextA(str);
	m_board_clearance = my_atof(&str);
	if( str.GetLength() == 0 )
		m_crop_dat += "0.0 ";
	else
		m_crop_dat += ("\"" + str + "\" ");
	m_edit_polyline.GetWindowTextA(str);
	m_polyline_clearance = my_atof(&str);
	if( str.GetLength() == 0 )
		m_crop_dat += "0.0 ";
	else
		m_crop_dat += ("\"" + str + "\" ");
	m_edit_thermal.GetWindowTextA(str);
	m_th_clearance = my_atof(&str);
	if( str.GetLength() == 0 )
		m_crop_dat += "0.0 ";
	else
		m_crop_dat += ("\"" + str + "\" ");
	//
	int i = m_combo_net.GetCurSel();
	if( i >= 0 )
		m_combo_net.GetWindowTextA(m_net_name);
	else if( m_combo_net.GetCount() )
		m_combo_net.GetLBText(0,m_net_name);
	else
		m_net_name = "GND";
	m_crop_dat += ("\"" + m_net_name + "\" ");
	if( m_check_net.GetCheck() == 0 )
		m_net_name = "";
	//
	int isel = m_combo_settings.GetCurSel();
	if( new_event )
	{
		m_edit_new_name.GetWindowTextA(str);
		m_edit_new_name.SetWindowTextA("");
		m_crop_dat += ("\"" + str + "\" ");
		m_combo_settings.InsertString(0,str);
		m_combo_settings.SetCurSel(0);
		m_cur_sel = 0;
	}
	else
	{
		if( isel >= 0 )
			m_combo_settings.GetWindowTextA(str);
		else
			ASSERT(0);
		m_crop_dat += ("\"" + str + "\" ");
	}
	//
	//
	//
	m_crop_flags = 0;
	if( m_check_prev.GetCheck() )
		setbit( m_crop_flags, MC_REMOVE_PREV );
	if( m_check_islands.GetCheck() )
		setbit( m_crop_flags, MC_NO_ISLANDS );
	if( m_check_add_thrml.GetCheck() )
		setbit( m_crop_flags, MC_THERMAL );
	if( m_check_no_thrml.GetCheck() )
		setbit( m_crop_flags, MC_NO_THERMAL );
	if( m_check_all_layers.GetCheck() )
		setbit( m_crop_flags, MC_ALL_LAYERS );
	if( m_check_octagon.GetCheck() )
		setbit( m_crop_flags, MC_OCTAGON );
	if( m_check_net.GetCheck() == 0 )
		setbit( m_crop_flags, MC_ALL_NETS );
	if( m_check_width.GetCheck() )
		setbit( m_crop_flags, MC_WIDTH );
	if( m_check_pads.GetCheck() )
		setbit( m_crop_flags, MC_PADS );
	if( m_check_segs.GetCheck() )
		setbit( m_crop_flags, MC_SEGS );
	if( m_check_areas.GetCheck() )
		setbit( m_crop_flags, MC_AREAS );
	if( m_check_holes.GetCheck() )
		setbit( m_crop_flags, MC_HOLES );
	if( m_check_texts.GetCheck() )
		setbit( m_crop_flags, MC_TEXTS );
	if( m_check_board.GetCheck() )
		setbit( m_crop_flags, MC_BOARD );
	if( m_check_polylines.GetCheck() )
		setbit( m_crop_flags, MC_POLYLINES );
	//
	str.Format("%d", m_crop_flags );
	m_crop_dat += ("\"" + str + "\" ");
	//
	if( new_event )
	{
		m_crop_data->InsertAt(0,m_crop_dat);
		m_combo_settings.SetCurSel(0);
		m_cur_sel = 0;
	}
	else
		m_crop_data->SetAt(isel,m_crop_dat);
}

void CDlgCrop::OnChange()
{
	int i = m_combo_settings.GetCurSel();
	if( m_cur_sel >= 0 )
	{
		m_combo_settings.SetCurSel( m_cur_sel );
		SaveCropData( FALSE );
	}	
	if( i >= 0 )
	{
		m_combo_settings.SetCurSel( i );
		if( m_combo_settings.GetCount() != m_crop_data->GetSize() )
			ASSERT(0);
		LoadCropData(i);
		m_cur_sel = i;
	}
}

void CDlgCrop::OnBnClickedDelete()
{
	if( m_combo_settings.GetCount() > 1 )
	{
		int r = AfxMessageBox(G_LANGUAGE == 0 ? "Confirm deletion...":"Подтвердите удаление...", MB_YESNO);
		if( r == IDYES )
		{
			int isel = m_combo_settings.GetCurSel();
			m_combo_settings.DeleteString(isel);
			m_crop_data->RemoveAt(isel);
			LoadCropData(0);
		}
	}
	else
		AfxMessageBox(G_LANGUAGE == 0 ? "You can't delete all of them":"Вы не можете удалить их все", MB_ICONERROR);
}

void CDlgCrop::OnBnClickedSave()
{
	CString s;
	m_edit_new_name.GetWindowTextA(s);
	if( s.GetLength() == 0 )
		AfxMessageBox(G_LANGUAGE == 0 ? "First enter new name":"Сначала введите новое имя", MB_ICONERROR);
	else
	{
		if( m_combo_settings.FindStringExact(-1,s) >= 0 )
			AfxMessageBox(G_LANGUAGE == 0 ? "This name already used":"Это имя уже использовалось", MB_ICONERROR);
		else
		{
			SaveCropData(TRUE);
			AfxMessageBox(G_LANGUAGE == 0 ? "Setting saved successfully":"Настройка успешно сохранена", MB_ICONINFORMATION);
		}
	}
}

void CDlgCrop::OnBnClickedThrml()
{
	m_check_add_thrml.EnableWindow(1);
	m_check_no_thrml.EnableWindow(1);
	if( m_check_add_thrml.GetCheck() )
		m_check_no_thrml.EnableWindow(0);
	else if( m_check_no_thrml.GetCheck() )
		m_check_add_thrml.EnableWindow(0);
}

void CDlgCrop::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnOK();
	CDialog::OnCancel();
}
