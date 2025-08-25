#pragma once
#include "afxwin.h"


// CDlgAddSymmetricalBlank dialog

class CDlgAddSymmetricalBlank : public CDialog
{
	DECLARE_DYNAMIC(CDlgAddSymmetricalBlank)

public:
	CDlgAddSymmetricalBlank(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAddSymmetricalBlank();
	void Initialize(int var, int dx, int dy, int units);
	// Dialog Data
	enum { IDD = IDD_ADD_SYMMETRICAL_BLANK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo_dx;
	CComboBox m_combo_dy;
	int m_var;
	int m_dx;
	int m_dy;
private:
	int m_var1;
	int m_var2;
	int m_var3;
	int m_var4;
	int m_units;
};
