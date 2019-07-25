
// ComputerDlg.h: 头文件
//
#pragma once

#include <Weteoes/Application/Icon.h> // 托盘

// CComputerDlg 对话框
class CComputerDlg : public CDialogEx, public IconClass
{
// 构造
public:
	CComputerDlg(CWnd* pParent = nullptr);	// 标准构造函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_Login };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	void Loading();
	void Loading_Dll();
	void Loading_Icon();
	void InstallService();
	void Ready_CEF();
	void Ready_Dlg();
	void SystemMenu_Exit();
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnNotifyMsg(WPARAM, LPARAM);
	afx_msg LRESULT OnTaskBarRestart(WPARAM, LPARAM); //图标重启
public:
	void Icon_Exit();
	void Icon_ReInit();
};
