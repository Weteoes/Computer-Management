
// MouseDlg.h : 头文件
//

#pragma once


// CMouseDlg 对话框
class CMouseDlg : public CDialogEx
{
// 构造
public:
	CMouseDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOUSE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnLbnDblclkList1();
	void Stop_xy();
	afx_msg void OnBnClickedButtonStarttwo();
	void Loading();
};
