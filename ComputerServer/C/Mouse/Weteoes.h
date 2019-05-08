#include "stdafx.h"
#include <string>
LPCUWSTR Get_LPCUWSTR(std::string text,int ch = 0) {
	try {
		size_t size = text.length();
		wchar_t *buffer = new wchar_t[size + 1];
		MultiByteToWideChar(CP_ACP, 0, text.c_str(), size, buffer, size * sizeof(wchar_t));
		buffer[text.length()-ch] = 0;
		return buffer;
	}
	catch (std::string cuowu) {
		std::string cuowu_text = "Get_LPCUWSTR()错误:\n" + cuowu;
		MessageBox(NULL, Get_LPCUWSTR(cuowu_text), _T(""), MB_OK);
		return NULL;
	}
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