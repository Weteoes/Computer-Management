
// shutdown_exe.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "shutdown_exe.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cshutdown_exeApp
BEGIN_MESSAGE_MAP(Cshutdown_exeApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

// Cshutdown_exeApp 构造
Cshutdown_exeApp::Cshutdown_exeApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}
Cshutdown_exeApp theApp;

//Weteoes
BOOL Get_Weteoes(std::string text);
LPCUWSTR Get_LPCUWSTR(std::string text);
void Shutdown_exe(std::string);
BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam);


BOOL Cshutdown_exeApp::InitInstance()
{
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	LPWSTR *szArglist = NULL;
	int nArgs = 0;
	CString str;
	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if (nArgs >  1)
	{
		str = szArglist[1];
	}
	LocalFree(szArglist);//取得参数后，释放CommandLineToArgvW申请的空间   
	std::string code = (CStringA)str;
	if (Get_Weteoes(code)) {
		MessageBox(NULL, _T("1"), _T(""), MB_OK);
		Shutdown_exe(code);
	}
	return FALSE;
}
void Shutdown_exe(std::string) {
	EnumWindows(lpEnumFunc, NULL);
	/*HWND hWnd = ::FindWindow(_T("cloudmusic.exe"), NULL);
	if (NULL != hWnd) {
		::SendMessage(hWnd, WM_CLOSE, 0, 0);
		MessageBox(NULL, _T("OK"),_T(""),MB_OK);
	}*/
}
std::string process_name[100];
int process_i = 0;
BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam)
{
	char a[100];
	LPWSTR b = NULL;
	GetWindowText(hwnd, (LPWSTR)a, 100);
	process_name[process_i++] = a;
	return 1;
}
BOOL Get_Weteoes(std::string text) {
	try {
		std::string code = text.substr(0, text.find("_"));
		if (code == "Weteoes") {
			return true;
		}
		return false;
	}
	catch (std::string cuowu) {
		std::string cuowu_text = "获取标识失败:\n" + cuowu;
		MessageBox(NULL, Get_LPCUWSTR(cuowu_text), _T(""), MB_OK);
		return false;
	}
}
LPCUWSTR Get_LPCUWSTR(std::string text) {
	try {
		size_t size = text.length();
		wchar_t *buffer = new wchar_t[size + 1];
		MultiByteToWideChar(CP_ACP, 0, text.c_str(), size, buffer, size * sizeof(wchar_t));
		buffer[size] = 0;
		return buffer;
	}
	catch (std::string cuowu) {
		std::string cuowu_text = "Get_LPCUWSTR()错误:\n" + cuowu;
		MessageBox(NULL, Get_LPCUWSTR(cuowu_text), _T(""), MB_OK);
		return NULL;
	}
}
