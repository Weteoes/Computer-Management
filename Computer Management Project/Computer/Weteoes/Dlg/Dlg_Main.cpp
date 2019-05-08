// Dlg_Main.cpp: 实现文件
//

#include "../../stdafx.h"
#include "../../Computer.h"
#include "Dlg_Main.h"
#include "afxdialogex.h"

#include "../../Resource.h"

//Dlg
#include <Application/Dlg.h>

//Dll
#include <Dll/Config.h>

//App
#include <Application/AppCef.h>
#include <Application/App.h>

//Cef
#include <More/CEF/Application/simple_app.h> //app
#include <More/CEF/Application/simple_handler.h> //handler
#include <More/CEF/Config.h> //CEF-Config

// Dlg_Main 对话框

IMPLEMENT_DYNAMIC(Dlg_Main, CDialogEx)

Dlg_Main::Dlg_Main(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_Main, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

Dlg_Main::~Dlg_Main()
{
}

void Dlg_Main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dlg_Main, CDialogEx)
//	ON_WM_CLOSE()
END_MESSAGE_MAP()


BOOL Dlg_Main::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	loading();
	return TRUE;
}
void Dlg_Main::loading() {
	loading_Dlg();
	loading_CEF();
	loading_SR();
}
void Dlg_Main::loading_Dlg() {
	int width = 800, height = 450;
	SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE);
	GetDlgItem(IDC_Main_CEF_Body)->SetWindowPos(NULL, 0, 0, width, height,NULL);
	//Dlg
	DlgClass::Dlg_HWND = this->m_hWnd;
	DlgClass::Dlg_HINSTANCE = AfxGetInstanceHandle();
	DlgClass().Dlg_SetNowRect(true);
}

void Dlg_Main::loading_CEF() {
	ConfigDll().Loading();
	AppCefClass::Url =AppCefClass().GetUrl(
		std::string(Url_Main) +
		"Language=" + ConfigDll::Config_ReadComputer().Language //语言
	);  
	CefRefPtr<SimpleHandler> CEF_handler = SimpleHandler::GetInstance();
	GetDlgItem(IDC_Main_CEF_Body)->GetClientRect(&SimpleApp::CEF_CRect);
	SimpleApp::CEF_HWND = GetSafeHwnd();
	CefBrowserSettings browser_settings;
	CefWindowInfo window_info;
	window_info.SetAsChild(SimpleApp::CEF_HWND, SimpleApp::CEF_CRect);
	CefBrowserHost::CreateBrowser(window_info, CEF_handler, AppCefClass::Url, browser_settings, NULL);
}

void Dlg_Main::loading_SR() {
	AppClass().Start_SR();
}

void Dlg_Main::OnCancel()
{
	DlgClass().Dlg_Mini();
}
