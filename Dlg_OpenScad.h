#pragma once
#include "afxwin.h"

 

class CDlg_OpenScad : public CDialog
{
	DECLARE_DYNAMIC(CDlg_OpenScad)

public:
	CString L_EXTRUDE;
	CString R_EXTRUDE;
	CString CLR;
	CString ROTATE;
	CString TRANSLATE;
	CString MATRIX;
	CString ISHOLE;
	CString UMIL;
	CString CLW;
	CString RAW;
	CString MINK;
	CString GROT;
	CString GLIFT;
	CString HULL;
	CString LCAP;
	CDlg_OpenScad(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg_OpenScad();
	void Initialize( CString * Descriptor, CString * global_r, CString * global_z, BOOL bFILL );
	void SetFields();
	void GetFields();
	CString * GenerateOpenscadData( CString * Separator=NULL );

// Dialog Data
	enum { IDD = IDD_OPENSCAD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void InterpretDescriptor( CString * Separator );

	DECLARE_MESSAGE_MAP()
public:
	//CButton m_button_set;
	//CComboBox m_combo_units;
	//CEdit m_edit_x;
	int m_obj_type; 
	int m_units; 
	int m_rnd_vtx;
	int m_dsp_transparent;
	int m_fill_space;
	int m_resolution;
	int m_like_cap;
	double m_extrusion_val; 
	double m_extrusion_scale;
	double m_extrusion_rot; 
	double m_global_rot;
	double m_global_z;
	double m_ang_x; 
	double m_ang_y; 
	double m_ang_z; 
	double m_mov_x; 
	double m_mov_y; 
	double m_mov_z;
	int m_matrix_x;
	int m_matrix_y;
	int m_matrix_z;
	double m_matrix_dx;
	double m_matrix_dy;
	double m_matrix_dz;
	CString s_extrusion_val;
	CString s_extrusion_scale;
	CString s_extrusion_rot; 
	CString s_global_rot;
	CString s_global_z;
	CString s_ang_x; 
	CString s_ang_y; 
	CString s_ang_z; 
	CString s_mov_x; 
	CString s_mov_y; 
	CString s_mov_z;
	CString s_matrix_x;
	CString s_matrix_y;
	CString s_matrix_z;
	CString s_matrix_dx;
	CString s_matrix_dy;
	CString s_matrix_dz;
	CString m_openscad_data;
	CString m_color;
	afx_msg void OnStnClickedStaticLayer1();
	afx_msg void OnEnChangeMatrixX();
	afx_msg void OnEnChangeMatrixY();
	afx_msg void OnEnChangeMatrixZ();
	afx_msg void OnEnChangeExtrusionValue();
	afx_msg void OnEnChangeExtrusionRot();
	afx_msg void OnCbnSelchangeComboResolution();
	afx_msg void OnEnChangeExtrusionScale();
};
