
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
	ON_WM_CLOSE()
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
	m_sd = 0;

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

	if(m_sd == 0) {
		PrintMsg(L"Socket isn't initialized");
		return;
	}


	if(m_isWorking == false) {
		m_isWorking = true;
		m_pThread = NULL;
		//m_pThread = AfxBeginThread(Send, this);
		m_pThread = AfxBeginThread(Send, this);
	} else {
		m_isWorking = false;
		m_pThread = NULL;
	}
	
	
}

void CCairo_Line3_SimulatorDlg::OnBnClickedBtnInit()
{
	// Common
	CString tempStr;

	// ETC
	m_isWorking = false;

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

	
	// Init Socket
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		PrintMsg(L"WSAStartup Failed.");
		return;
		//exit(EXIT_FAILURE);
	}
	PrintMsg(L"Initialize Winsock.");


	// Create a datagram socket on which tonsend.
	//int sd;
	m_sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_sd < 0) {
		PrintMsg(L"Could not create socket");
		return;
		//exit(1);
	}
	tempStr.Format(L"Socket created : %d \r\n", m_sd);
	PrintMsg(tempStr);


	local_addr = inet_addr(LOCAL_IP_2);
	struct in_addr localInterface;
	struct sockaddr_in t_sockaddr;


	int t_opt_reuse = 1;
	if(setsockopt(m_sd, SOL_SOCKET, SO_REUSEADDR,(char *)&t_opt_reuse, sizeof(t_opt_reuse)) == SOCKET_ERROR)
	{
		PrintMsg(L"Fail to set REUSE - CREATE");
	//	return false;
	}

	
	t_sockaddr.sin_family = AF_INET;
	//t_sockaddr.sin_addr.s_addr = htonl(local_addr);
	//t_sockaddr.sin_addr.S_un.S_addr = htonl(local_addr);
	t_sockaddr.sin_addr.S_un.S_addr = local_addr;
	//t_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	t_sockaddr.sin_port = htons(MULTICAST_PORT);
	if(bind(m_sd, (struct sockaddr*)&t_sockaddr, sizeof(t_sockaddr))) {
		PrintMsg(L"Fail to bind multicast socket _ CREATE");
		//return false;
	}




	
	// Initialize the group sockaddr structure
	//struct sockaddr_in groupSock;
	memset((char *) &groupSock, 0, sizeof(groupSock));
	groupSock.sin_family = AF_INET;
	groupSock.sin_addr.s_addr = mcast_addr;
	groupSock.sin_port = htons(mcast_port);
	// Disable loopback so you do not receive your own datagrams.
	{
		char loopch=1; // Loopback disable
		if (setsockopt(m_sd, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch)) < 0) 
		{
				PrintMsg(L"setting IP_MULTICAST_LOOP:");
				closesocket(m_sd);
				//exit(1);
				return;
		}
	}
		





	// Set local interface for outbound multicast datagrams.
	//struct in_addr localInterface;
	localInterface.s_addr = local_addr;
	if (setsockopt(m_sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0) 
	{
			PrintMsg(L"setting local interface");
			closesocket(m_sd);
			//exit(1);
			return;
	}

	//if (setsockopt(m_sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&localInterface, sizeof(localInterface)) < 0) 
	//{
	//		PrintMsg(L"Fail to ADD MEMBERSHIP");
	//		closesocket(m_sd);
	//		//exit(1);
	//		return;
	//}



	

	// End Init Routine
	PrintMsg(L"Init Complete");
}


void CCairo_Line3_SimulatorDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	// Before Closing Window

	CDialogEx::OnClose();
	
	// After Closing Window
	closesocket(m_sd);
	WSACleanup();
}

UINT CCairo_Line3_SimulatorDlg::Send(LPVOID param) {

	// Common
	CString tempStr;
	CCairo_Line3_SimulatorDlg* pMain = (CCairo_Line3_SimulatorDlg*)param;
	int t_Cnt = 0;

	if(pMain->m_sd == 0) {
		tempStr = L"Socket isn't initialized";
		pMain->PrintMsg(tempStr);
		//return 0;
	}
	
	
	const int BUFF_SIZE = 17;
	char databuf[BUFF_SIZE];
	memset(databuf, 0x00, sizeof(databuf));
	databuf[0] = 0xA5;
	databuf[1] = 0xA4;
	databuf[2] = 0x08;
	databuf[3] = 0x00;
	databuf[4] = 0x20;
	databuf[5] = 0x00;
	databuf[6] = 0x04;
	databuf[7] = 0x00;
	databuf[8] = 0x00;
	databuf[9] = 0x01;
	databuf[10] = 0x01;
	databuf[11] = 0x14;
	databuf[12] = 0x07;
	databuf[13] = 0x16;
	databuf[14] = 0x0A;
	databuf[15] = 0x2E;
	databuf[16] = 0x16;

	u_long local_addr = inet_addr(LOCAL_IP);
	struct in_addr localInterface;
	struct sockaddr_in t_sockaddr;

	int t_TestCnt = 0;



	int t_opt_reuse = 1;
	//if(setsockopt(pMain->m_sd, SOL_SOCKET, SO_REUSEADDR,(char *)&t_opt_reuse, sizeof(t_opt_reuse)) == SOCKET_ERROR)
	//{
	//	pMain->PrintMsg(L"Fail to set reuse");
	//	return false;
	//}
	/*
	t_sockaddr.sin_family = AF_INET;
	//t_sockaddr.sin_addr.s_addr = htonl(local_addr);
	t_sockaddr.sin_addr.S_un.S_addr = htonl(local_addr);
	//t_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	t_sockaddr.sin_port = htons(MULTICAST_PORT);
	if(bind(pMain->m_sd, (struct sockaddr*)&t_sockaddr, sizeof(t_sockaddr))) {
		pMain->PrintMsg(L"Fail to bind multicast socket");
		//return false;
	}
	*/

	while(pMain->m_isWorking) {
		if(t_TestCnt == 10) t_TestCnt = 0;
		databuf[0] = t_TestCnt;
		databuf[1] = t_Cnt++;
		//tempStr.Format(L"%d", t_Cnt++);

		for(int i = 0 ; i < BUFF_SIZE ; i++) {
			databuf[i] = 0xFF;
		}

		local_addr = inet_addr(LOCAL_IP_2);
		localInterface.s_addr = local_addr;

		if(setsockopt(pMain->m_sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0) 
		{
				pMain->PrintMsg(L"Fail to setsockopt in thread");
				//closesocket(m_sd);
				//exit(1);
				//return;
		}
		


		if(sendto(pMain->m_sd, databuf, BUFF_SIZE, 0, (struct sockaddr*)&(pMain->groupSock), sizeof(pMain->groupSock)) < 0) {
			tempStr.Format(L"ERROR : %d(%d)", t_Cnt++, GetLastError());
			pMain->PrintMsg(tempStr);
		} else {
			tempStr.Format(L"LOCAL_1 : %d", t_TestCnt++);
			pMain->PrintMsg(tempStr);
		}
		
		for(int i = 0 ; i < BUFF_SIZE ; i++) {
			databuf[i] = 0x11;
		}

		local_addr = inet_addr(LOCAL_IP_2);
		localInterface.s_addr = local_addr;
		if(setsockopt(pMain->m_sd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0) 
		{
				pMain->PrintMsg(L"Fail to setsockopt in thread");
				//closesocket(m_sd);
				//exit(1);
				//return;
		}

		if(sendto(pMain->m_sd, databuf, BUFF_SIZE, 0, (struct sockaddr*)&(pMain->groupSock), sizeof(pMain->groupSock)) < 0) {
			tempStr.Format(L"ERROR : %d(%d)", t_Cnt++, GetLastError());
			pMain->PrintMsg(tempStr);
		} else {
			tempStr.Format(L"LOCAL_2 : %d", t_TestCnt++);
			pMain->PrintMsg(tempStr);
		}



		Sleep(500);
	}
	return 0;
}
