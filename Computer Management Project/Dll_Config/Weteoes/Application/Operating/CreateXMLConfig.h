#include <pch.h>

#ifndef CreateXMLConfigClass_H
#define CreateXMLConfigClass_H

#include <Weteoes/More/tinyxml2/tinyxml2.h>

class CreateXMLConfigClass {
public:
	bool CreateXML(string xmlFile); // 创建配置文件
	bool UserConfig(const char* w); // 用户session配置文件
	bool ComputerConfig(const char* ComputerName, const char* Language); // 客户端配置文件
};
#endif 