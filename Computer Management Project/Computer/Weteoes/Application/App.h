#include <pch.h>
#ifndef AppClass_H
#define AppClass_H
class AppClass {
public:
	void LoginSuccess(); //��¼���

private:
	void PD_Config(); //�ж������ļ��Ƿ����
	std::string Random_Character(int len); //����ַ�
};
#endif