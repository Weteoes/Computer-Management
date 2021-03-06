#pragma once

// BrowserDlg 对话框
class BrowserDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BrowserDlg)

public:
	BrowserDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~BrowserDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_Browser };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

private:
	HICON m_hIcon; //Icon

private:
	void Ready();
	void ReadyVariable();
	void ReadyDlg();
	void ReadyCEF();
	void ReadyCEFVariable();

public:
	string configCEFUrl = "http://www.weteoes.cn";

public:
	HWND dlg_HWND;					// 窗口句柄
	int dlg_CEF;					// CEF句柄ID
	int browserListIndex;			// 在CEF_Handler中的浏览器ID
	CefRefPtr<CefBrowser> browser;  // 浏览器句柄

public:
	virtual void OnCancel();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
};