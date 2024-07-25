// CDlgEnterStr.cpp : implementation file
//

#include "stdafx.h"
#include "FreePcb.h"
#include "DlgEnterStr.h"


// dialog

IMPLEMENT_DYNAMIC(CDlgEnterStr, CDialog)
CDlgEnterStr::CDlgEnterStr(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEnterStr::IDD, pParent)
{
	m_win_str = "Enter name";
	m_str = "?";
}  

CDlgEnterStr::~CDlgEnterStr()
{
}

void CDlgEnterStr::Initialize( CString * win_str, CString * ini_str )
{
	m_win_str = *win_str;
	m_str = *ini_str;
}

void CDlgEnterStr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STR, m_edit);
	if( pDX->m_bSaveAndValidate )
	{
		m_edit.GetWindowText(m_str);
		if (m_str.Find("\"",0) >= 0)
		{
			AfxMessageBox(G_LANGUAGE == 0 ? 
				"Illegal name. The name can not contain the quote character!":
				"Неверное имя. Имя не может содержать кавычку!");
			pDX->Fail();
		}
		if (m_str.Find(" ",0) >= 0)
		{
			AfxMessageBox(G_LANGUAGE == 0 ? 
				"Illegal name. The name can not contain a space character!":
				"Неверное имя. Имя не может содержать символ пробела!");
			pDX->Fail();
		}
		m_str = m_str.Left(CShape::MAX_NAME_SIZE);
	}
	else
	{
		HWND wnd = CDialog::GetSafeHwnd();
		::SetWindowText( wnd, m_win_str );
		m_edit.SetWindowText( m_str );
		//int len = m_str.GetLength();
		//m_edit.SetSel(0,len-1);
		//m_edit.SetFocus();
	}
}


BEGIN_MESSAGE_MAP(CDlgEnterStr, CDialog)
END_MESSAGE_MAP()


// CDlgEnterStr message handlers
