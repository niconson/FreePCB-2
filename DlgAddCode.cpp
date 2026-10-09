#include "stdafx.h"
#include "FreePcb.h"
#include "DlgAddCode.h"
#include "math.h"
extern CFreePcbApp theApp;
CString separator_str = "    //-------------------";
 

IMPLEMENT_DYNAMIC(CDlgAddCode, CDialog)
CDlgAddCode::CDlgAddCode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddCode::IDD, pParent)
{
	m_font.CreateFont( 16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_DONTCARE, "Courier New" );
}

CDlgAddCode::~CDlgAddCode()
{
}

void CDlgAddCode::CodeTextIni()
{
	if (m_code_text->GetSize() == 0)
	{
		// ini code
		m_code_text->Add("translate([0,0,0]) // (automatic adjustment when moving the footprint origin)");
		m_code_text->Add("scale([1,1,1])     // (automatic adjustment when changing the project units)");
		m_code_text->Add("{");
		m_code_text->Add(separator_str);
		m_code_text->Add("    // add your code here, for example:");
		m_code_text->Add("    // color(`Aqua`)");
		m_code_text->Add("    // translate([0,0,0])");
		m_code_text->Add("    // rotate([0,0,0])");
		m_code_text->Add("    // import(`knob.stl`);");
		m_code_text->Add(separator_str);
		m_code_text->Add("}");
	}
}

void CDlgAddCode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODE, m_code);
	if( !pDX->m_bSaveAndValidate )
	{
		// incoming
		m_code.SetFont( &m_font );
		// ini code
		CodeTextIni();
		for( int i=0; i<m_code_text->GetSize(); i++ )
		{
			CString s = m_code_text->GetAt(i)+"\r\n";
			s.Replace("`","\"");
			m_code.ReplaceSel( s );
		}
	}
	else
	{
		Outgoing();
	}
}

void CDlgAddCode::Outgoing()
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
	m_fp->m_scad_created = m_fp->GenerateOpenscadFileA(&name, 1);
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
BEGIN_MESSAGE_MAP(CDlgAddCode, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDlgAddCode::OnBnClickedCancel)
	ON_EN_SETFOCUS(IDC_CODE, &CDlgAddCode::OnEnSetfocusCode)
	ON_BN_CLICKED(IDOK, &CDlgAddCode::OnBnClickedOk)
	ON_EN_CHANGE(IDC_CODE, &CDlgAddCode::OnEnChangeCode)
	ON_BN_CLICKED(IDC_SCAD_TRANSLATE, &CDlgAddCode::OnBnClickedScadTranslate)
	ON_BN_CLICKED(IDC_SCAD_ROTATE, &CDlgAddCode::OnBnClickedScadRotate)
	ON_BN_CLICKED(IDC_SCAD_CUBE, &CDlgAddCode::OnBnClickedScadCube)
	ON_BN_CLICKED(IDC_SCAD_CYLINDER, &CDlgAddCode::OnBnClickedScadCylinder)
	ON_BN_CLICKED(IDC_SCAD_YELLOW, &CDlgAddCode::OnBnClickedScadYellow)
	ON_BN_CLICKED(IDC_SCAD_CRIMSON, &CDlgAddCode::OnBnClickedScadCrimson)
	ON_BN_CLICKED(IDC_SCAD_AQUA, &CDlgAddCode::OnBnClickedScadAqua)
	ON_BN_CLICKED(IDC_SCAD_ROSY, &CDlgAddCode::OnBnClickedScadRosy)
END_MESSAGE_MAP()

void CDlgAddCode::Initialize(CShape* fp, CArray <CString> * iniCode)
{
	m_fp = fp;
	m_code_text = &fp->m_openscad_code;
	if (iniCode)
		if (iniCode->GetSize())
		{
			// ini code
			CodeTextIni();
			m_code_text->InsertAt(3, iniCode);
		}
}


void CDlgAddCode::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnOK();
}


void CDlgAddCode::OnEnSetfocusCode()
{
	// TODO: добавьте свой код обработчика уведомлений
	/*CString str;
	m_code.GetWindowTextA( str );
	int f =str.Find("    // add your code" );
	if( f > 0 )
	{
		int fe = str.Find( separator_str, f+1 );
		if( fe > 0 )
			m_code.SetSel( f, fe-1, 1 );
		else
			m_code.SetSel( str.GetLength(), str.GetLength() );
	}
	else
		m_code.SetSel( str.GetLength(), str.GetLength() );*/
}


void CDlgAddCode::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	Outgoing();
}


void CDlgAddCode::OnEnChangeCode()
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
	for (int i=0; i<count; i++)
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


void CDlgAddCode::OnBnClickedScadTranslate()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("translate([0,0,0])");
}


void CDlgAddCode::OnBnClickedScadRotate()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("rotate([0,0,0])");
}


void CDlgAddCode::OnBnClickedScadCube()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("cube([10,10,10], center = true);");
}


void CDlgAddCode::OnBnClickedScadCylinder()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("cylinder(h=10, d1=10, d2=10, center = true);");
}


void CDlgAddCode::OnBnClickedScadYellow()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("linear_extrude(0.5)text(\"txt\",size=10,font=\"arial\",direction=\"ltr\",language=\"en\",script=\"latin\",halign=\"left\",valign=\"center\",spacing=1.0);");
}


void CDlgAddCode::OnBnClickedScadCrimson()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("color(\"Crimson\", 1.0)");
}


void CDlgAddCode::OnBnClickedScadAqua()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("color(\"Aquamarine\", 1.0)");
}


void CDlgAddCode::OnBnClickedScadRosy()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("color(\"RosyBrown\", 1.0)");
}
