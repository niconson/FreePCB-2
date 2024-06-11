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
	CString name = m_fp->m_name;
	m_fp->GenerateOpenscadFileA(&name, 1);
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
