
// ComputerDlg.cpp: 实现文件
//

#include "../../stdafx.h"
#include "../../Computer.h"
#include "ComputerDlg.h"
#include "afxdialogex.h"
#include <list>
#include <thread> //多线程

//Weteoes Dll
#include <Dll/WeteoesDll.h>
#include <Dll/Sys.h>
#include <Dll/Config.h>
#include <Dll/Management.h>

//Dlg
#include <Application/Dlg.h>

//App
#include <Application/App.h>
#include <Application/AppConfig.h>
#include <Application/AppCef.h>

//CEF
#include "../../resource.h"
#include <More/CEF/Config.h> //CEF-Config
#include <More/CEF/Application/simple_app.h> //app
#ifdef single_process
#else
#include <More/CEF/include/cef_app.h> //CefShutdown
#endif //single_process
#ifdef DEBUG
#pragma comment(lib,"Weteoes/More/CEF/lib/Debug/libcef.lib")
#pragma comment(lib,"Weteoes/More/CEF/lib/Debug/libcef_dll_wrapper.lib")
#else
#pragma comment(lib,"Weteoes/More/CEF/lib/Release/libcef.lib") 
#pragma comment(lib,"Weteoes/More/CEF/lib/Release/libcef_dll_wrapper.lib")
#endif // !DEBUG

// CComputerDlg 对话框


void CComputerDlg::Loading() {
	Loading_Dll();
	/* initialization */
	Ready_Dlg(); //初始化窗口,要先初始化窗口后再调用CEF
	std::thread CEF(&CComputerDlg::Ready_CEF, this); CEF.join(); //CEF

	/* 判断登录 */
	if (AppConfigClass().IsLogin) { //已经登录
		AppClass().Login_Success();
	}
	else { //还没登录
		AppConfigClass::IsMiniStartMain = false; //设置本次启动Main不使用Mini启动
	}

	/* Icon */
	std::thread Icon(&CComputerDlg::Loading_Icon, this); Icon.join(); //最后启动，防止已登录过早点击出现登录界面

	/* App */
	DlgClass().Dlg_Show(true); //启动窗口完毕调用
}
void CComputerDlg::Loading_Dll() {
	if (!WeteoesDll().Loading()) { SystemMenu_Exit(); }

	//Dlg
	DlgClass::Dlg_HWND = this->m_hWnd;
	DlgClass::Dlg_HINSTANCE = AfxGetInstanceHandle();
}
void CComputerDlg::Ready_Dlg() { //初始化窗口
	/* 设置窗口标题(用于Dll获取主窗口句柄) Title */
	AfxGetMainWnd()->SetWindowText(AppConfigClass::SoftwareName.c_str());

	//设置窗口大小
	int width = 300, height = 400;
	SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE);
	GetDlgItem(IDC_Login_CEF_BODY)->SetWindowPos(0, 0, 0, width, height, NULL);

	//阴影
	SetClassLong(this->m_hWnd, GCL_STYLE, GetClassLong(this->m_hWnd, GCL_STYLE) | CS_DROPSHADOW);

	//圆角
	CRgn m_rgn; RECT rc;
	//GetWindowRect(&rc); //有边框对话框
	GetClientRect(&rc);//无边框对话框 
	m_rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 5, 5); //矩形圆角
	SetWindowRgn(m_rgn, TRUE);
}
void CComputerDlg::Ready_CEF()
{
	AppCefClass::Url = AppCefClass().GetUrl(Url_Login);
	CefMainArgs mainArgs(AfxGetInstanceHandle());
	CefRefPtr<SimpleApp> app(new SimpleApp);
	CefExecuteProcess(mainArgs, app.get(), NULL);

	CefSettings settings = AppCefClass().GetSetting();
	GetDlgItem(IDC_Login_CEF_BODY)->GetClientRect(&SimpleApp::CEF_CRect);
	SimpleApp::CEF_HWND = GetSafeHwnd();
	CefInitialize(mainArgs, settings, app.get(), NULL);
}
/* 初始化托盘 */
void CComputerDlg::Loading_Icon() {
	Icon_Add(this->m_hWnd, AfxGetInstanceHandle());
}
/* 托盘事件 */
LRESULT CComputerDlg::OnNotifyMsg(WPARAM wparam, LPARAM lparam)
{
	if (wparam != IDI_ICON1){ return -1; }
    switch (lparam) {
		case WM_LBUTTONDOWN: {
			DlgClass().Dlg_Show();
		}
		break;
		case WM_RBUTTONDOWN: {
			// 注意：菜单是弹出式菜单，菜单索引项是弹出式菜单，子菜单不是
			CMenu menu;
			menu.LoadMenu(IDR_MENU1);
			CMenu* pPopup = menu.GetSubMenu(0);  // 获取菜单句柄，参数表示菜单位置，索引值
			if (!pPopup) { MessageBox(_T("Icon 获取句柄失败"), _T(""), MB_OK); }
			SetForegroundWindow();
			POINT pt;
			GetCursorPos(&pt);
			pPopup->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this); // 其中可添加TPM_RETURNCMD  | TPM_RIGHTBUTTON 选项，返回值表示选中的菜单ID项
			pPopup->DestroyMenu(); //销毁菜单
		}
		break;
	}
	return 0;
}
/* 托盘重启事件 */
LRESULT CComputerDlg::OnTaskBarRestart(WPARAM wParam, LPARAM lParam) {
	Loading_Icon();
	return 0;
}
void CComputerDlg::InstallService() { //安装服务
	if (!SysDll().Loading()) { SystemMenu_Exit(); }
	if (SysDll::Install) {
		SysDll::Install();
	}
}
void CComputerDlg::SystemMenu_Exit() { //调用关闭-统一关闭程序
	DlgClass().Dlg_Close();
}

CComputerDlg::CComputerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dlg_Login, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CComputerDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}
/* 托盘重启 */
static UINT OnTaskBarRestart_ID = RegisterWindowMessage(TEXT("TaskbarCreated"));
BEGIN_MESSAGE_MAP(CComputerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	/* 托盘事件 */
	ON_COMMAND(ID_ICON_0, &CComputerDlg::Icon_Exit)
	ON_COMMAND(ID_ICON_1, &CComputerDlg::Icon_ReInit)
	ON_MESSAGE(WM_IconMsg, &CComputerDlg::OnNotifyMsg)
	/* 托盘重启 */
	ON_REGISTERED_MESSAGE(OnTaskBarRestart_ID, &CComputerDlg::OnTaskBarRestart)
ON_WM_CLOSE()
END_MESSAGE_MAP()


// CComputerDlg 消息处理程序

BOOL CComputerDlg::OnInitDialog()
{
	Loading();

	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CComputerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CComputerDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

// 托盘事件-退出
void CComputerDlg::Icon_Exit() {
	SystemMenu_Exit();
}

// 托盘事件-重新初始化
void CComputerDlg::Icon_ReInit() {
	theApp.First_Init();
}