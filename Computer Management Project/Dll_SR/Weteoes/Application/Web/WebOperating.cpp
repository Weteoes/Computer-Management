#include <pch.h>
#ifdef NoBuild
#include "WebOperating.h"
#include <Weteoes/Application/Config.h>

bool WebOperatingClass::Entrance(string operatingUrl, string &result) {
	// 判断是否登录
	string LoginIn = VariableClass::getVariable("LoginIn");
	if (LoginIn == "" || LoginIn == "0") {
		// 如果未登录，不执行
		return false;
	}
	string operatingName, operatingData;
	if (operatingUrl.find("?") != -1) {
		// 如果有参数
		operatingName = VariableClass::configClass.GetConfig(operatingUrl, "?");
		operatingData = operatingUrl;
	}
	else {
		// 没有参数
		operatingName = operatingUrl;
	}
	// 如果为空
	if (operatingName.empty()) { return false; }
	// 判断操作
	if (operatingName == "/operating/browser/del") {
		result = operating_operating_browser_del(operatingData);
		return true;
	}
	return false;
}


string WebOperatingClass::operating_operating_browser_del(string data) {
	string Host = VariableClass::webBasicClass.get_HtmlConfig(data, "Host");
	char* result_c = new char[100];
	string result_format_s = "{\"Code\":%d}";
	int code = 1;
	if (Host.empty()) {
		goto result;
	}
	else {
		// 解码
		Host = VariableClass::webBasicClass.UrlDecode(Host);
	}
result:
	sprintf_s(result_c, 100, result_format_s.c_str(), code);
	return result_c;
}
#endif