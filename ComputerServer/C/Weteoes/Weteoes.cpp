
// Weteoes.cpp : 定义应用程序的类行为。
//
#include "stdafx.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//DeBug
BOOL DeBug_Weteoes = false;

//Weteoes
BOOL Get_Weteoes(std::string text);
LPCUWSTR Get_LPCUWSTR(std::string text);
void Shortcut_Key(std::string text);
byte Get_Key(std::string text);
std::string GetString_lower(std::string text);

void Shortcut_Key(std::string text) {
	try {
		std::string a = text.substr(text.find("_") + 1);
		std::string ctrl = a.substr(0, 1);
		std::string alt_all = a.substr(a.find("_") + 1);
		std::string alt = alt_all.substr(0, 1);
		std::string key_all = alt_all.substr(a.find("_") + 1);
		std::string key = key_all.substr(0);
		std::string mess = "ctrl:" + ctrl + "\nalt:" + alt + "\nkey:" + key;
		byte keys = Get_Key(key);
		if (ctrl == "1") {
			keybd_event(VK_CONTROL, 0, 0, 0);
		}
		if (alt == "1") {
			keybd_event(VK_MENU, 0, 0, 0);
		}
		keybd_event(keys, 0, 0, 0);
		if (ctrl == "1") {
			keybd_event(VK_CONTROL, 0, 2, 0);
		}
		if (alt == "1") {
			keybd_event(VK_MENU, 0, 2, 0);
		}
		keybd_event(keys, 0, 2, 0);
	}
	catch (std::exception cuowu) {
		keybd_event(VK_CONTROL, 0, 2, 0);
		keybd_event(VK_MENU, 0, 2, 0);
		std::string cuowu_text = "Shortcut_Key()错误";
		if(DeBug_Weteoes)
			MessageBox(NULL, Get_LPCUWSTR(cuowu_text), _T(""), MB_OK);
	}
}
std::string GetString_lower(std::string text) {
	try {
		for (unsigned int i = 0; i < text.size(); i++) {
			text[i] = tolower(text[i]);
		}
		return text;
	}
	catch(std::string cuowu){
		std::string cuowu_text = "GetString_lower()错误:\n" + cuowu;
		if(DeBug_Weteoes)
			MessageBox(NULL, Get_LPCUWSTR(cuowu_text), _T(""), MB_OK);
		return NULL;
	}
}
std::string GetString_upper(std::string text) {
	try {
		for (unsigned int i = 0; i < text.size(); i++) {
			text[i] = toupper(text[i]);
		}
		return text;
	}
	catch (std::string cuowu) {
		std::string cuowu_text = "GetString_upper()错误:\n" + cuowu;
		if(DeBug_Weteoes)
			MessageBox(NULL, Get_LPCUWSTR(cuowu_text), _T(""), MB_OK);
		return NULL;
	}
}
#include <iostream>
byte Get_Key(std::string text) {
	try {
		text = GetString_upper(text);
		std::string key = GetString_lower(text);
		if (key == GetString_lower("F1"))
			return VK_F1;
		else if (key == GetString_lower("F2"))
			return VK_F2;
		else if (key == GetString_lower("F3"))
			return VK_F3;
		else if (key == GetString_lower("F4"))
			return VK_F4;
		else if (key == GetString_lower("F5"))
			return VK_F5;
		else if (key == GetString_lower("F6"))
			return VK_F6;
		else if (key == GetString_lower("F7"))
			return VK_F7;
		else if (key == GetString_lower("F8"))
			return VK_F8;
		else if (key == GetString_lower("F9"))
			return VK_F9;
		else if (key == GetString_lower("F10"))
			return VK_F10;
		else if (key == GetString_lower("F11"))
			return VK_F11;
		else if (key == GetString_lower("F12"))
			return VK_F12;
		else if (key == GetString_lower("1"))
			return VK_NUMPAD1;
		else if (key == GetString_lower("2"))
			return VK_NUMPAD2;
		else if (key == GetString_lower("3"))
			return VK_NUMPAD3;
		else if (key == GetString_lower("4"))
			return VK_NUMPAD4;
		else if (key == GetString_lower("5"))
			return VK_NUMPAD5;
		else if (key == GetString_lower("6"))
			return VK_NUMPAD6;
		else if (key == GetString_lower("7"))
			return VK_NUMPAD7;
		else if (key == GetString_lower("8"))
			return VK_NUMPAD8;
		else if (key == GetString_lower("9"))
			return VK_NUMPAD9;
		else if (key == GetString_lower("0"))
			return VK_NUMPAD0;
		else if (key == GetString_lower("{top}"))
			return VK_UP;
		else if (key == GetString_lower("{down}"))
			return VK_DOWN;
		else if (key == GetString_lower("{left}"))
			return VK_LEFT;
		else if (key == GetString_lower("{right}"))
			return VK_RIGHT;
		else return text[0];
	}
	catch(std::string cuowu){
		std::string cuowu_text = "Get_Key()错误:\n" + cuowu;
		if(DeBug_Weteoes)
			MessageBox(NULL, Get_LPCUWSTR(cuowu_text), _T(""), MB_OK);
		return NULL;
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
		if(DeBug_Weteoes)
			MessageBox(NULL, Get_LPCUWSTR(cuowu_text), _T(""), MB_OK);
		return NULL;
	}
}






// CWeteoesApp

BEGIN_MESSAGE_MAP(CWeteoesApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWeteoesApp 构造

CWeteoesApp::CWeteoesApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CWeteoesApp 对象
CWeteoesApp theApp;

// CWeteoesApp 初始化
BOOL CWeteoesApp::InitInstance()
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
	//if (Get_Weteoes(code)) {
		Shortcut_Key(code);
	//}
	return FALSE;
}



