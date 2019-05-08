
// Mouse.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Mouse.h"
#include "MouseDlg.h"
#include "Weteoes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseApp

BEGIN_MESSAGE_MAP(CMouseApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMouseApp 构造

CMouseApp::CMouseApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CMouseApp 对象

CMouseApp theApp;
#include <string>

// CMouseApp 初始化
BOOL CMouseApp::InitInstance()
{
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	LPWSTR *szArglist = NULL;
	int nArgs = 0;
	CString str;
	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (nArgs > 1) {
		str = szArglist[1];
		LocalFree(szArglist);//取得参数后，释放CommandLineToArgvW申请的空间   
		std::string code = (CStringA)str;
		std::string panduan = (CStringA)szArglist[2];//判断
		std::string x = (CStringA)szArglist[3];
		std::string y = (CStringA)szArglist[4];
		int Weteoes_x = std::atoi(x.c_str());
		int Weteoes_y = std::atoi(y.c_str());
		if (Get_Weteoes(code)) {
			if (panduan == "1") {
				SetCursorPos(Weteoes_x, Weteoes_y);
				mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, NULL);
				return false;
			}
		}
	}
	CWinApp::InitInstance();
	CShellManager *pShellManager = new CShellManager;
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	CMouseDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	if (pShellManager != NULL)
		delete pShellManager;
#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif
	return FALSE;
}

