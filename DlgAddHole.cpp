#include "stdafx.h"
#include "FreePcb.h"
#include "DlgAddHole.h"
#include "math.h"
extern CFreePcbApp theApp;
CString sep_str = "    //-------------------";


IMPLEMENT_DYNAMIC(CDlgAddHole, CDialog)
CDlgAddHole::CDlgAddHole(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddHole::IDD, pParent)
{
	m_font.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Courier New");
}

CDlgAddHole::~CDlgAddHole()
{
}

void CDlgAddHole::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODE, m_code);
	if (!pDX->m_bSaveAndValidate)
	{
		// incoming
		m_code.SetFont(&m_font);
		if (m_code_text->GetSize() == 0)
		{
			// ini code
			m_code_text->Add("translate([0,0,0]) // (automatic adjustment when moving the footprint origin)");
			m_code_text->Add("scale([1,1,1])     // (automatic adjustment when changing the project units)");
			m_code_text->Add("{");
			m_code_text->Add(sep_str);
			m_code_text->Add("    // add your code here, for example:");
			m_code_text->Add("    color(`Brown`)");
			///m_code_text->Add("    rotate([0,0,0])");
			m_code_text->Add("    translate([0,0,0])");
			m_code_text->Add("    rotate([0,0,0])");
			m_code_text->Add("    sphere(10);");
			m_code_text->Add(sep_str);
			m_code_text->Add("}");
		}
		for (int i = 0; i < m_code_text->GetSize(); i++)
		{
			CString s = m_code_text->GetAt(i) + "\r\n";
			s.Replace("`", "\"");
			m_code.ReplaceSel(s);
		}
	}
	else
	{
		Outgoing();
	}
}

void CDlgAddHole::Outgoing()
{
	m_code_text->RemoveAll();
	CString s, str;
	m_code.GetWindowTextA(str);
	str += "\n";
	int ip = 0;
	for (int i = str.Find("\n"); i > 0; i = str.Find("\n", ip))
	{
		s = str.Tokenize("\n", ip);
		s.Replace("\n", "");
		s.Replace("\r", "");
		s.Replace("\"", "`");
		ip = i + 1;
		if (s.GetLength())
			m_code_text->Add(s);
	}
	CString name = theApp.m_Doc->m_name + "_" + m_fp->m_name;
	m_fp->GenerateOpenscadFileA(&name, 1);
}
BEGIN_MESSAGE_MAP(CDlgAddHole, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDlgAddHole::OnBnClickedCancel)
	ON_EN_SETFOCUS(IDC_CODE, &CDlgAddHole::OnEnSetfocusCode)
	ON_BN_CLICKED(IDOK, &CDlgAddHole::OnBnClickedOk)
END_MESSAGE_MAP()

void CDlgAddHole::Initialize(CShape* fp)
{
	m_fp = fp;
	m_code_text = &fp->m_openscad_hole;
}


void CDlgAddHole::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnOK();
}


void CDlgAddHole::OnEnSetfocusCode()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString str;
	m_code.GetWindowTextA(str);
	int f = str.Find("    // add your code");
	if (f > 0)
	{
		int fe = str.Find(sep_str, f + 1);
		if (fe > 0)
			m_code.SetSel(f, fe - 1, 1);
		else
			m_code.SetSel(str.GetLength(), str.GetLength());
	}
	else
		m_code.SetSel(str.GetLength(), str.GetLength());
}


void CDlgAddHole::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	Outgoing();
}
