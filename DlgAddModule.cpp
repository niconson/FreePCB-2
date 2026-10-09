#include "stdafx.h"
#include "FreePcb.h"
#include "DlgAddModule.h"
#include "math.h"
extern CFreePcbApp theApp;


IMPLEMENT_DYNAMIC(CDlgAddModule, CDialog)
CDlgAddModule::CDlgAddModule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAddModule::IDD, pParent)
{
	m_font.CreateFont(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Courier New");
}

CDlgAddModule::~CDlgAddModule()
{
}

void CDlgAddModule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODE, m_code);
	if (!pDX->m_bSaveAndValidate)
	{
		// incoming
		CFileFind finder;
		CString mod_prj_name = theApp.m_Doc->m_name;
		CStringToLegalFileName(&mod_prj_name);
		if (mod_prj_name.Right(3) == "fpc")
			mod_prj_name.Truncate(mod_prj_name.GetLength() - 3);
		else
			mod_prj_name += ".";
		CString search_str = theApp.m_Doc->m_path_to_folder + "\\related_files\\openscad\\*.scad";
		BOOL bWorking = finder.FindFile(search_str);
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			CString fn = finder.GetFileName();
			if (!finder.IsDirectory())
			{
				// found a file
				CString scad = fn;
				scad.Truncate(fn.GetLength() - 4);
				if(scad.CompareNoCase(mod_prj_name) == 0)
					continue;
				// loop through footprints in heading
				CFootLibFolder* libfolder = theApp.m_Doc->m_footlibfoldermap.GetFolder(&theApp.m_Doc->m_full_lib_dir, theApp.m_Doc->m_dlg_log);
				BOOL bFail = 0;
				for (int ilib = 0; ilib < libfolder->GetNumLibs(); ilib++)
					if (bFail == 0) for (int i = 0; i < libfolder->GetNumFootprints(ilib); i++)
					{
						CString* str = libfolder->GetFootprintName(ilib, i);
						CString footName = *str;
						CStringToLegalFileName(&footName);
						if (scad.Find(footName) > 0)
						{
							bFail = 1;
							break;
						}
					}
				if (bFail)
					continue;
				CString funcName = scad;
				funcName.Truncate(scad.GetLength() - 1);
				funcName = " // hint: call Pcb_" + funcName + "(1);";
				CString include = "include <" + scad + "lib>" + funcName;
				BOOL bIncludeFound = 0;
				for (int i = 0; i < m_code_text->GetSize(); i++)
				{
					CString s = m_code_text->GetAt(i);
					if (s.Find(include) >= 0)
					{
						bIncludeFound = 1;
						break;
					}
				}
				if(bIncludeFound == 0)
					m_code.ReplaceSel("// " + include + "\r\n");
			}
		}
		finder.Close();

		m_code.SetFont(&m_font);
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

void CDlgAddModule::Outgoing()
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
BEGIN_MESSAGE_MAP(CDlgAddModule, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDlgAddModule::OnBnClickedCancel)
	ON_EN_SETFOCUS(IDC_CODE, &CDlgAddModule::OnEnSetfocusCode)
	ON_BN_CLICKED(IDOK, &CDlgAddModule::OnBnClickedOk)
	ON_EN_CHANGE(IDC_CODE, &CDlgAddModule::OnEnChangeCode)
	ON_BN_CLICKED(IDC_SCAD_TRANSLATE, &CDlgAddModule::OnBnClickedScadTranslate)
	ON_BN_CLICKED(IDC_SCAD_ROTATE, &CDlgAddModule::OnBnClickedScadRotate)
	ON_BN_CLICKED(IDC_SCAD_CUBE, &CDlgAddModule::OnBnClickedScadCube)
	ON_BN_CLICKED(IDC_SCAD_CYLINDER, &CDlgAddModule::OnBnClickedScadCylinder)
	ON_BN_CLICKED(IDC_SCAD_YELLOW, &CDlgAddModule::OnBnClickedScadYellow)
	ON_BN_CLICKED(IDC_SCAD_CRIMSON, &CDlgAddModule::OnBnClickedScadCrimson)
	ON_BN_CLICKED(IDC_SCAD_AQUA, &CDlgAddModule::OnBnClickedScadAqua)
	ON_BN_CLICKED(IDC_SCAD_ROSY, &CDlgAddModule::OnBnClickedScadRosy)
END_MESSAGE_MAP()

void CDlgAddModule::Initialize(CShape* fp)
{
	m_fp = fp;
	m_code_text = &fp->m_openscad_module;
}


void CDlgAddModule::OnBnClickedCancel()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnOK();
}


void CDlgAddModule::OnEnSetfocusCode()
{
	// TODO: добавьте свой код обработчика уведомлений
	//CString str;
	//m_code.GetWindowTextA(str);
	//m_code.SetSel(str.GetLength(), str.GetLength());
}


void CDlgAddModule::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	Outgoing();
}


void CDlgAddModule::OnEnChangeCode()
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


void CDlgAddModule::OnBnClickedScadTranslate()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("translate([0,0,0])");
}


void CDlgAddModule::OnBnClickedScadRotate()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("rotate([0,0,0])");
}


void CDlgAddModule::OnBnClickedScadCube()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("cube([10,10,10], center = true);");
}


void CDlgAddModule::OnBnClickedScadCylinder()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("cylinder(h=10, d1=10, d2=10, center = true);");
}


void CDlgAddModule::OnBnClickedScadYellow()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("linear_extrude(0.5)text(\"txt\",size=10,font=\"arial\",direction=\"ltr\",language=\"en\",script=\"latin\",halign=\"left\",valign=\"center\",spacing=1.0);");
}


void CDlgAddModule::OnBnClickedScadCrimson()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("color(\"Crimson\")");
}


void CDlgAddModule::OnBnClickedScadAqua()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("color(\"Aquamarine\")");
}


void CDlgAddModule::OnBnClickedScadRosy()
{
	// TODO: добавьте свой код обработчика уведомлений
	m_code.ReplaceSel("color(\"RosyBrown\")");
}
