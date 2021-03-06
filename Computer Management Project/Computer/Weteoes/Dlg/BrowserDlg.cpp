// BrowserDlg.cpp: 实现文件
//

#include <pch.h>
#include "framework.h"
#include <Computer.h>
#include "BrowserDlg.h"
#include "afxdialogex.h"
#include <Resource.h>
#include <Weteoes/Application/App.h>
#include <Weteoes/Dll/ConfigDll.h>
#include <Weteoes/More/CEF/Application/CEF_Handler.h> // CEF_Handler

// BrowserDlg 对话框

IMPLEMENT_DYNAMIC(BrowserDlg, CDialogEx)

BrowserDlg::BrowserDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_Browser, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

BrowserDlg::~BrowserDlg()
{
}

void BrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BrowserDlg, CDialogEx)
	ON_WM_ACTIVATE()
	ON_WM_SIZE()
	ON_WM_HELPINFO()
END_MESSAGE_MAP()


BOOL BrowserDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	Ready();
	return TRUE;
}

void BrowserDlg::Ready() {
	ReadyDlg();
	ReadyCEF();
}

void BrowserDlg::ReadyDlg() {
	// 初始化变量
	dlg_CEF = IDC_Browser_CEF;
	dlg_HWND = this->m_hWnd;

	// 设置窗口标题(用于Dll获取主窗口句柄) Title
	SetWindowText("Browser");

	//设置窗口大小
	int width = 1, height = 1;
	SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE);
	GetDlgItem(dlg_CEF)->SetWindowPos(0, 0, 0, width, height, NULL);

	//阴影
	SetClassLong(dlg_HWND, GCL_STYLE, GetClassLong(dlg_HWND, GCL_STYLE) | CS_DROPSHADOW);
}

void BrowserDlg::ReadyVariable() {
	VariableClass::dlg_CEF = dlg_CEF;
	VariableClass::dlg_HWND = dlg_HWND;
}

void BrowserDlg::ReadyCEF() {
	CefRefPtr<CEF_Handler> CEF_handler = CEF_Handler::GetInstance();
	if (CEF_handler == NULL) {
		CEF_handler = new CEF_Handler(false);
	}
	browserListIndex = CEF_handler->GetBrowserListIndex();
	CRect CEF_CRect;
	GetDlgItem(dlg_CEF)->GetClientRect(&CEF_CRect);
	CefBrowserSettings browser_settings;
	CefWindowInfo window_info;
	window_info.SetAsChild(GetSafeHwnd(), CEF_CRect);
	CefBrowserHost::CreateBrowser(window_info, CEF_handler, configCEFUrl, browser_settings, NULL, NULL);
	thread a(&BrowserDlg::ReadyCEFVariable, this); a.detach();
}

void BrowserDlg::ReadyCEFVariable() {
	CefRefPtr<CEF_Handler> CEF_handler = CEF_Handler::GetInstance();
	CefRefPtr<CefBrowser> browser = CEF_handler->GetBrowserbyIndex(browserListIndex);
	if (browser) {
		this->browser = browser;
	}
	else {
		Sleep(100);
		ReadyCEFVariable();
	}
}

void BrowserDlg::OnCancel() {
	CString a;
	GetWindowText(a);
	if (a == "Close") {
		CDialogEx::OnCancel();
	}
	else {
		// 如果不等于close就不关闭
		VariableClass::appDlgClass.Minimize();
	}
}


void BrowserDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) {
	if (nState != 0) {
		ReadyVariable();
	}
	if (browser) {
		string a = VariableClass::appCefBasicClass.GetJavaScriptNamebyDlg("OnActivate");
		int len = (int)a.length() + 1;
		char* b = new char[len];
		sprintf_s(b, len, a.c_str(), nState);
		VariableClass::appCefBasicClass.ExecJavaScript(browser, b);
		delete[] b;
	}
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
}


void BrowserDlg::OnSize(UINT nType, int cx, int cy) {
	CDialogEx::OnSize(nType, cx, cy);
	if (browser) {
		CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
		//因为浏览器对于对话框是子窗口，所以浏览器的左上角坐标是相于父窗口的客户区的左上角而言的
		::MoveWindow(hwnd, 0, 0, cx, cy, TRUE);
	}
}


BOOL BrowserDlg::OnHelpInfo(HELPINFO* pHelpInfo) {
	return 0;
}
