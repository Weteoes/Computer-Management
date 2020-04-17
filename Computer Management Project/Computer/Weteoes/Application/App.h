#include <pch.h>
#ifndef AppClass_H
#define AppClass_H
class AppClass {
public:
	void LoginSuccess(); //登录完毕

private:
	void PD_Config(); //判断配置文件是否存在
	std::string Random_Character(int len); //随机字符
};
#endif