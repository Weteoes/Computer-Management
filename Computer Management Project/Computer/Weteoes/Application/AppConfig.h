#include <pch.h>

#ifndef AppConfigClass_H
#define AppConfigClass_H

class AppConfigClass
{
private:
	static std::string SoftwareTitle;
	static std::string Version;

public:
	static std::string Get_SoftwareTitle();		// ��ȡ�������
	static std::string Get_Version();			// ��ȡ�汾
	static std::string Get_TempPath();			// ��ȡ��ʱ����λ��
};

#endif