#pragma once
#include <pch.h>
#ifndef AppCefBasicClass_H
#define AppCefBasicClass_H
class AppCefBasicClass {
public:
	void ExecJavaScript(CefRefPtr<CefBrowser> browser, std::string js);
	std::string GetJavaScriptNamebyDlg(std::string dlgFun);
};
#endif