#pragma once
#include "afxwin.h"


// CDlgFindPart dialog

class CDlgCrop : public CDialog
{
	DECLARE_DYNAMIC(CDlgCrop)

public:
	CDlgCrop(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCrop();

// Dialog Data
	enum { IDD = IDD_CROP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton m_check_prev;
	CButton m_check_islands;
	CButton m_check_add_thrml;
	CButton	m_check_no_thrml;
	CButton	m_check_all_layers;
	CButton	m_check_octagon;
	CButton	m_check_net;
	CButton	m_check_width;
	CButton	m_check_pads;
	CButton	m_check_segs;
	CButton	m_check_areas;
	CButton	m_check_holes;
	CButton	m_check_texts;
	CButton	m_check_board;
	CButton	m_check_polylines;
	CButton	m_delete_setting;
	CButton	m_save;
	CComboBox m_combo_net;
	CComboBox m_combo_settings;
	CEdit m_edit_new_name;
	CEdit m_edit_width;
	CEdit m_edit_pad;
	CEdit m_edit_seg;
	CEdit m_edit_area;
	CEdit m_edit_hole;
	CEdit m_edit_text;
	CEdit m_edit_board;
	CEdit m_edit_polyline;
	CEdit m_edit_thermal;
	//
	int m_crop_flags;
	int m_cur_sel;
	//
	float m_width;
	float m_pad_clearance;
	float m_seg_clearance;
	float m_area_clearance;
	float m_hole_clearance;
	float m_text_clearance;
	float m_board_clearance;
	float m_polyline_clearance;
	float m_th_clearance;
	//
	CArray<CString> nets;
	CString m_net_name;
	CArray<CString> * m_crop_data;
	void Initialize( CArray<CString> * crop_data, int crop_flags );
	void LoadCropData( int item );
	void SaveCropData( int new_event );
	void OnChange();
	void OnBnClickedDelete();
	void OnBnClickedSave();
	void OnBnClickedThrml();
	afx_msg void OnBnClickedCancel();
};
