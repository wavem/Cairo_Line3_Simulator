
// Cairo_Line3_SimulatorDlg.h : header file
//

#pragma once

#define LOCAL_IP "192.168.0.1"
#define MULTICAST_IP "222.222.222.222"
#define MULTICAST_PORT 20000;

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
};
