#include <pch.h>

#ifndef AppConfigClass_H
#define AppConfigClass_H

class AppConfigClass
{
private:
	static std::string SoftwareTitle;
	static std::string Version;

public:
	static std::string Get_SoftwareTitle();		// 获取软件标题
	static std::string Get_Version();			// 获取版本
	static std::string Get_TempPath();			// 获取临时数据位置
};

#endif