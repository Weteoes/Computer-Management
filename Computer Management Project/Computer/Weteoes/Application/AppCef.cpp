#include "AppCef.h"
#include <More/CEF/Config.h> //CEF-Config

//App
#include <application/AppConfig.h>

//Dll
#include <Dll/WeteoesDll.h>
#include <Dll/Management.h>

#include <cstring>

std::string AppCefClass::Url;

CefSettings AppCefClass::GetSetting()
{
	std::string CEF_Path = WeteoesDll::Basics_GetNowFilePath();
	CefSettings settings;
	settings.no_sandbox = true;
	settings.multi_threaded_message_loop = true;
#ifdef _DEBUG
#else
	settings.log_severity = LOGSEVERITY_DISABLE;
#endif // _DEBUG
	CefString(&settings.cache_path) = AppConfigClass::Get_TempPath() + "CEF\\";
	CefString(&settings.resources_dir_path) = ToUnicode((char*)(CEF_Path + "CEF\\Resources").c_str());
	CefString(&settings.locales_dir_path) = ToUnicode((char*)(CEF_Path + "CEF\\locales").c_str());
	return settings;
}

std::string AppCefClass::GetUrl(std::string url) {
	if (!ManagementDll().Loading()) { return url; }
	std::string URL_Client = ManagementDll::Get("URL_Client");
	if (URL_Client.empty()) { return url; }
	url = URL_Client + url;
	return url;
}

wchar_t* AppCefClass::ToUnicode(char* ansiStr)
{
	int len = MultiByteToWideChar(CP_ACP, 0, ansiStr, -1, NULL, 0);  // 先取得转换后的UNICODE字符串所需的长度
	wchar_t* buf1 = (wchar_t*)calloc(len, sizeof(wchar_t));         // 分配缓冲区
	MultiByteToWideChar(CP_ACP, 0, ansiStr, -1, buf1, len);    // 开始转换
	return buf1;
}