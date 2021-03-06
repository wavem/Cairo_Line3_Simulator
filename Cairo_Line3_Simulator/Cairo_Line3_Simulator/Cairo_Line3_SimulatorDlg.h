
// Cairo_Line3_SimulatorDlg.h : header file
//

#pragma once

#define LOCAL_IP "192.168.0.51"
#define LOCAL_IP_2 "192.168.0.51"
#define MULTICAST_IP "239.255.93.18"
#define MULTICAST_PORT 50101

// CCairo_Line3_SimulatorDlg dialog
class CCairo_Line3_SimulatorDlg : public CDialogEx
{
// Construction
public:
	CCairo_Line3_SimulatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CAIRO_LINE3_SIMULATOR_DIALOG };

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
	afx_msg void OnBnClickedBtnTest();
	CListBox m_LMemo;


public:
	void PrintMsg(LPCTSTR _str);
	afx_msg void OnBnClickedBtnInit();
	afx_msg void OnClose();
	CWinThread *m_pThread;
	static UINT Send(LPVOID param);
	bool m_isWorking;
	int m_sd;
	struct sockaddr_in groupSock;
};
