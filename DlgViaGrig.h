#pragma once


// CDlgViaGrig dialog

class CDlgViaGrig : public CDialog
{
	DECLARE_DYNAMIC(CDlgViaGrig)

public:
	CDlgViaGrig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgViaGrig();
	void Initialize( int def_v, int def_h, int sp_x=0, int sp_y=0 );
	void GetFields();
	void SetFields();
	void OnCbnSelchangeComboUnits();

// Dialog Data
	enum { IDD = IDD_VIAS_GRID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_units;
	CEdit m_space_x;
	CEdit m_space_y;
	CEdit m_via_size;
	CEdit m_hole_size;
	CButton m_as_part;
	CButton m_chess;
	int m_def_via_w;
	int m_def_hole_w;
	int m_out_x;
	int m_out_y;
	int m_u;
	BOOL as_part;
	int chess;
};