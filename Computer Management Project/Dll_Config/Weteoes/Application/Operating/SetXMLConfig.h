#include <pch.h>
#ifndef SetXMLConfigClass_H
#define SetXMLConfigClass_H

#include <Weteoes/More/tinyxml2/tinyxml2.h>

class SetXMLConfigClass {
public:
	bool ComputerConfig(const char* element, const char* data); // 更具char*修改ComputerConfig中的任意配置
};
#endif 