
// berkanteber_Teber_Berkan_HW8Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// Cberkanteber_Teber_Berkan_HW8Dlg dialog
class Cberkanteber_Teber_Berkan_HW8Dlg : public CDialogEx
{
// Construction
public:
	Cberkanteber_Teber_Berkan_HW8Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BERKANTEBER_TEBER_BERKAN_HW8_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton radioButton2;
	CEdit text;
	CEdit key;
	CComboBox rotate;
	CListBox output;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton1();
	int crypt;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
};
