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
	// SetForegroundOpenscadWindow
	CString name = theApp.m_Doc->m_name + "_" + m_fp->m_name;
	if (theApp.m_Doc->m_project_open == 0)
		name = "open";
	m_fp->m_scad_created = m_fp->GenerateOpenscadFileA(&name, 1, 1);
	int rf = m_fp->m_scad_created.ReverseFind('\\');
	if (rf == -1)
		return;
	rf = m_fp->m_scad_created.GetLength() - rf - 1;
	CWnd* wnd = FindWindow(NULL, m_fp->m_scad_created.Right(rf) + " - OpenSCAD");
	if (wnd == NULL)
		wnd = FindWindow(NULL, m_fp->m_scad_created.Right(rf) + "* - OpenSCAD");
	if (wnd)
	{
		WINDOWPLACEMENT placement;
		placement.length = sizeof(placement);
		//
		if (wnd->GetWindowPlacement(&placement))
		{
			if (placement.showCmd & SW_SHOWMINIMIZED)
			{
				placement.showCmd = SW_SHOWNORMAL;
				wnd->SetWindowPlacement(&placement);
			}
		}
		wnd->SetForegroundWindow();
	}
}
BEGIN_MESSAGE_MAP(CDlgAddHole, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDlgAddHole::OnBnClickedCancel)
	ON_EN_SETFOCUS(IDC_CODE, &CDlgAddHole::OnEnSetfocusCode)
	ON_BN_CLICKED(IDOK, &CDlgAddHole::OnBnClickedOk)
	ON_EN_CHANGE(IDC_CODE, &CDlgAddHole::OnEnChangeCode)
	ON_BN_CLICKED(IDC_SCAD_TRANSLATE, &CDlgAddHole::OnBnClickedScadTranslate)
	ON_BN_CLICKED(IDC_SCAD_ROTATE, &CDlgAddHole::OnBnClickedScadRotate)
	ON_BN_CLICKED(IDC_SCAD_CUBE, &CDlgAddHole::OnBnClickedScadCube)
	ON_BN_CLICKED(IDC_SCAD_CYLINDER, &CDlgAddHole::OnBnClickedScadCylinder)
	ON_BN_CLICKED(IDC_SCAD_YELLOW, &CDlgAddHole::OnBnClickedScadYellow)
	ON_BN_CLICKED(IDC_SCAD_CRIMSON, &CDlgAddHole::OnBnClickedScadCrimson)
	ON_BN_CLICKED(IDC_SCAD_AQUA, &CDlgAddHole::OnBnClickedScadAqua)
	ON_BN_CLICKED(IDC_SCAD_ROSY, &CDlgAddHole::OnBnClickedScadRosy)
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
	/*CString str;
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
		m_code.SetSel(str.GetLength(), str.GetLength());*/
}


void CDlgAddHole::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	Outgoing();
}


void CDlgAddHole::OnEnChangeCode()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the CDialog::OnInitDialog()
	// функция и вызов CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Добавьте код элемента управления
	static CString prev_str = "0";
	if (prev_str.GetLength() == 0)
		return;
	CString str;
	m_code.GetWindowTextA(str);
	int curStart = 0;
	int curEnd = 0;
	m_code.GetSel(curStart, curEnd);
	str.Truncate(curEnd);
	int count = 0;
	int pos = 0;
	// Ищем символ, начиная с текущей позиции pos
	while ((pos = str.Find("{", pos)) != -1)
	{
		count++;
		pos++; // Сдвигаемся на один символ вперед, чтобы не зациклиться
	}
	CString space = "";
	for (int i = 0; i < count; i++)
		space += "    ";
	if (space.GetLength() == 0)
		return;
	pos = 0;
	while ((pos = prev_str.Find("}", pos)) != -1)
	{
		count--;
		pos++; // Сдвигаемся на один символ вперед, чтобы не зациклиться
	}
	if (count > 0)
	{
		space.Truncate(count * 4);
	}
	if (str.Right(1) == "\n" && prev_str.Right(2) != "\n ")
	{
		prev_str = "";
		if (count > 0)
			m_code.ReplaceSel(space);
	}
	else if (str.Right(1) == "}" && prev_str.Right(space.GetLength()) == space)
	{
		prev_str = "";
		m_code.SetSel(curEnd - 5, curEnd);
		m_code.ReplaceSel("}");
	}
	m_code.GetWindowTextA(prev_str);
	m_code.GetSel(curStart, curEnd);
	prev_str.Truncate(curEnd);
}


void CDlgAddHole::OnBnClickedScadTranslate()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("translate([0,0,0])");
}


void CDlgAddHole::OnBnClickedScadRotate()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("rotate([0,0,0])");
}


void CDlgAddHole::OnBnClickedScadCube()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("cube([10,10,10], center = true);");
}


void CDlgAddHole::OnBnClickedScadCylinder()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("cylinder(h=10, d1=10, d2=10, center = true);");
}


void CDlgAddHole::OnBnClickedScadYellow()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("linear_extrude(0.5)text(\"txt\",size=10,font=\"arial\",direction=\"ltr\",language=\"en\",script=\"latin\",halign=\"left\",valign=\"center\",spacing=1.0);");
}


void CDlgAddHole::OnBnClickedScadCrimson()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("color(\"Crimson\")");
}


void CDlgAddHole::OnBnClickedScadAqua()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("color(\"Aquamarine\")");
}


void CDlgAddHole::OnBnClickedScadRosy()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("color(\"RosyBrown\")");
}
