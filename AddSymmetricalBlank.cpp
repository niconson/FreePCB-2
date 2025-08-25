// DlgAddMaskCutout.cpp : implementation file
//

#include "stdafx.h"
#include "FreePcb.h"
#include "AddSymmetricalBlank.h"


// CDlgAddMaskCutout dialog

IMPLEMENT_DYNAMIC(CDlgAddSymmetricalBlank, CDialog)
CDlgAddSymmetricalBlank::CDlgAddSymmetricalBlank(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddSymmetricalBlank::IDD, pParent)
{
}

CDlgAddSymmetricalBlank::~CDlgAddSymmetricalBlank()
{
}

void CDlgAddSymmetricalBlank::Initialize(int var, int dx, int dy, int units)
{
	m_var = var;
	m_dx = dx;
	m_dy = dy;
	m_units = units;
	if (m_var == 1)
		m_var1 = 1;
	else if (m_var == 2)
		m_var2 = 1;
	else if (m_var == 3)
		m_var3 = 1;
	else if (m_var == 4)
		m_var4 = 1;
}
void CDlgAddSymmetricalBlank::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_X, m_combo_dx);
	DDX_Control(pDX, IDC_COMBO_Y, m_combo_dy);
	DDX_Check(pDX, IDC_RADIO1, m_var1);
	DDX_Check(pDX, IDC_RADIO2, m_var2);
	DDX_Check(pDX, IDC_RADIO3, m_var3);
	DDX_Check(pDX, IDC_RADIO4, m_var4);
	if (!pDX->m_bSaveAndValidate)
	{
		// incoming
		m_combo_dx.AddString("1mm (39mil)");
		m_combo_dx.AddString("1.5mm (59mil)");
		m_combo_dx.AddString("2mm (79mil)");
		m_combo_dx.AddString("2.5mm (99mil)");
		m_combo_dx.AddString("3mm (119mil)");
		m_combo_dx.AddString("3.5mm (139mil)");
		m_combo_dx.AddString("4mm (159mil)");
		m_combo_dx.AddString("4.5mm (179mil)");
		m_combo_dx.AddString("5mm (199mil)");
		//
		m_combo_dy.AddString("1mm (39mil)");
		m_combo_dy.AddString("1.5mm (59mil)");
		m_combo_dy.AddString("2mm (79mil)");
		m_combo_dy.AddString("2.5mm (99mil)");
		m_combo_dy.AddString("3mm (119mil)");
		m_combo_dy.AddString("3.5mm (139mil)");
		m_combo_dy.AddString("4mm (159mil)");
		m_combo_dy.AddString("4.5mm (179mil)");
		m_combo_dy.AddString("5mm (199mil)");
		CString str;
		::MakeCStringFromDimension(&str, m_dx, m_units, 1, 1, 0, 1);
		m_combo_dx.SetWindowTextA(str);
		::MakeCStringFromDimension(&str, m_dy, m_units, 1, 1, 0, 1);
		m_combo_dy.SetWindowTextA(str);
	}
	else
	{
		// outgoing
		if (m_var1)
			m_var = 1;
		else if (m_var2)
			m_var = 2;
		else if (m_var3)
			m_var = 3;
		else if (m_var4)
			m_var = 4;
		CString str;
		//double dx, dy;
		m_combo_dx.GetWindowTextA(str);
		int i = str.Find("(");
		if (i > 0)
			str.Truncate(i);
		str = str.TrimRight();
		m_dx = my_atof(&str);
		m_combo_dy.GetWindowTextA(str);
		i = str.Find("(");
		if (i > 0)
			str.Truncate(i);
		str = str.TrimRight();
		m_dy = my_atof(&str);
	}
}


BEGIN_MESSAGE_MAP(CDlgAddSymmetricalBlank, CDialog)
END_MESSAGE_MAP()


