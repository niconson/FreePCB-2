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
	CString name = theApp.m_Doc->m_name + "_" + m_fp->m_name;
	m_fp->m_scad_created = m_fp->GenerateOpenscadFileA(&name, 1);
}
BEGIN_MESSAGE_MAP(CDlgAddModule, CDialog)
	ON_BN_CLICKED(IDCANCEL, &CDlgAddModule::OnBnClickedCancel)
	ON_EN_SETFOCUS(IDC_CODE, &CDlgAddModule::OnEnSetfocusCode)
	ON_BN_CLICKED(IDOK, &CDlgAddModule::OnBnClickedOk)
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
