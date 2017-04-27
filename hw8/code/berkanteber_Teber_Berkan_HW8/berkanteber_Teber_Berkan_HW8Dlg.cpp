
// berkanteber_Teber_Berkan_HW8Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "berkanteber_Teber_Berkan_HW8.h"
#include "berkanteber_Teber_Berkan_HW8Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cberkanteber_Teber_Berkan_HW8Dlg dialog



Cberkanteber_Teber_Berkan_HW8Dlg::Cberkanteber_Teber_Berkan_HW8Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cberkanteber_Teber_Berkan_HW8Dlg::IDD, pParent)
	, crypt(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cberkanteber_Teber_Berkan_HW8Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO1, radioButton2);
	DDX_Control(pDX, IDC_EDIT1, text);
	DDX_Control(pDX, IDC_EDIT2, key);
	DDX_Control(pDX, IDC_COMBO1, rotate);
	DDX_Control(pDX, IDC_LIST1, output);
	DDX_Radio(pDX, IDC_RADIO1, crypt);
}

BEGIN_MESSAGE_MAP(Cberkanteber_Teber_Berkan_HW8Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &Cberkanteber_Teber_Berkan_HW8Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &Cberkanteber_Teber_Berkan_HW8Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &Cberkanteber_Teber_Berkan_HW8Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO1, &Cberkanteber_Teber_Berkan_HW8Dlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &Cberkanteber_Teber_Berkan_HW8Dlg::OnBnClickedRadio2)
END_MESSAGE_MAP()


// Cberkanteber_Teber_Berkan_HW8Dlg message handlers

BOOL Cberkanteber_Teber_Berkan_HW8Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cberkanteber_Teber_Berkan_HW8Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cberkanteber_Teber_Berkan_HW8Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cberkanteber_Teber_Berkan_HW8Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void rotateLeft1(unsigned int & num)
{
	unsigned int leftBit = (1 << 31) & num;
	num = num << 1;
	num = num | (leftBit >> 31);

	return;
}

void rotateRight1(unsigned int & num)
{
	unsigned int rightBit = num & 1;
	num = num >> 1;
	num = num | (rightBit << 31);

	return;
}


void Cberkanteber_Teber_Berkan_HW8Dlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

//#1015

	// TODO:  Add your control notification handler code here
}

void Cberkanteber_Teber_Berkan_HW8Dlg::OnEnChangeEdit2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

//#1015

	// TODO:  Add your control notification handler code here
}

int maxSize = 0;

void Cberkanteber_Teber_Berkan_HW8Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	CString myText, myKey, myRotate; 
	CString errorMessage = _T("Wrong input. Try again.");

	CDC *pDC = GetDC();
	CSize cz;

	text.GetWindowTextW(myText);
	key.GetWindowTextW(myKey);

	if (myText.GetLength() == 0 || myKey.GetLength() == 0)
	{
		output.AddString(errorMessage);
		return;
	}
	
	for (int i = 0; i < myText.GetLength(); i++)
		if (myText[i] < '0' || myText[i] > '9')
		{
			output.AddString(errorMessage);
			return;
		}

	for (int i = 0; i < myKey.GetLength(); i++)
		if (myKey[i] < '0' || myKey[i] > '9')
		{
			output.AddString(errorMessage);
			return;
		}

	unsigned int UItext = _tcstoul(myText, nullptr, 10);
	unsigned int UIkey = _tcstoul(myKey, nullptr, 10);

	rotate.GetWindowTextW(myRotate);

	CString chiphertext, plaintext, outputtext;

	if (radioButton2.GetCheck() == 1)	//encrypt
	{	
		if (myRotate == _T(""))
		{
			output.AddString(errorMessage);
			return;
		}
		else if (myRotate == _T("Rotate Left 1"))		
			rotateLeft1(UIkey);
		else if (myRotate == _T("Rotate Right 1"))
			rotateRight1(UIkey);
		else ;

		unsigned int UIchiphertext = UIkey ^ UItext;
		chiphertext.Format(_T("%u"), UIchiphertext);
		
		outputtext = chiphertext + _T(": ") + myText + _T(" encrypted with key ") + myKey + _T(" using ") + myRotate;

	//	output.AddString(chiphertext);
	}
	else								// decrypt
	{	
		if (myRotate == _T(""))
		{
			output.AddString(errorMessage);
			return;
		}
		else if (myRotate == _T("Rotate Left 1"))		
			rotateLeft1(UIkey);
		else if (myRotate == _T("Rotate Right 1"))
			rotateRight1(UIkey);
		else ;

		unsigned int UIplaintext = UIkey ^ UItext;
		plaintext.Format(_T("%u"), UIplaintext);

		outputtext = plaintext + _T(": ") + myText + _T(" decrypted with key ") + myKey + _T (" using ") + myRotate;

	//	output.AddString(plaintext);
	}

	output.AddString(outputtext);
	cz = pDC->GetTextExtent(outputtext);
	if(cz.cx > maxSize)
		maxSize = cz.cx;

	output.SetHorizontalExtent(maxSize);
}

void Cberkanteber_Teber_Berkan_HW8Dlg::OnBnClickedRadio1()
{
	// TODO: Add your control notification handler code here
}


void Cberkanteber_Teber_Berkan_HW8Dlg::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
}
