#include <pch.h>

#ifndef CreateXMLConfigClass_H
#define CreateXMLConfigClass_H

#include <Weteoes/More/tinyxml2/tinyxml2.h>

class CreateXMLConfigClass {
public:
	bool CreateXML(string xmlFile); // ���������ļ�
	bool UserConfig(const char* w); // �û�session�����ļ�
	bool ComputerConfig(const char* ComputerName, const char* Language); // �ͻ��������ļ�
};
#endif 