
// Cairo_Line3_SimulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Cairo_Line3_Simulator.h"
#include "Cairo_Line3_SimulatorDlg.h"
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


// CCairo_Line3_SimulatorDlg dialog




CCairo_Line3_SimulatorDlg::CCairo_Line3_SimulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCairo_Line3_SimulatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCairo_Line3_SimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MEMO, m_LMemo);
}

BEGIN_MESSAGE_MAP(CCairo_Line3_SimulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_TEST, &CCairo_Line3_SimulatorDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_INIT, &CCairo_Line3_SimulatorDlg::OnBnClickedBtnInit)
END_MESSAGE_MAP()


// CCairo_Line3_SimulatorDlg message handlers

BOOL CCairo_Line3_SimulatorDlg::OnInitDialog()
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

void CCairo_Line3_SimulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCairo_Line3_SimulatorDlg::OnPaint()
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
HCURSOR CCairo_Line3_SimulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCairo_Line3_SimulatorDlg::PrintMsg(LPCTSTR _str) {
	int t_Idx = m_LMemo.InsertString(-1, _str);
	m_LMemo.SetCurSel(t_Idx);
}

void CCairo_Line3_SimulatorDlg::OnBnClickedBtnTest()
{
	PrintMsg(L"TEST BTN");
}

void CCairo_Line3_SimulatorDlg::OnBnClickedBtnInit()
{
	// Common
	CString tempStr;

	// Start Init Routine
	PrintMsg(L"Init Start");

	u_long local_addr = inet_addr(LOCAL_IP);
	u_long mcast_addr = inet_addr(MULTICAST_IP);
	u_long mcast_port = MULTICAST_PORT;

	tempStr = L"Local IP : ";
	tempStr += inet_ntoa(*(struct in_addr*)&local_addr);
	PrintMsg(tempStr);

	tempStr = L"Multicast Addr : ";
	tempStr += inet_ntoa(*(struct in_addr*)&mcast_addr);
	PrintMsg(tempStr);

	tempStr.Format(L"Multicast Port : %d", mcast_port);
	PrintMsg(tempStr);





	// End Init Routine
	PrintMsg(L"Init Complete");
}
