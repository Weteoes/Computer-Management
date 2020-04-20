#include "App.h"
#include <thread>
#include <pch.h>
#include <Resource.h>
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/SRWDll.h>
#include <Weteoes/Dll/ConfigDll.h>

void AppClass::LoginSuccess() {
	PD_Config(); // 如果是第一次初始化配置
	VariableClass::app_Dll_SWR.Start(1); // socket启动
}

void AppClass::PD_Config() {
	std::string ComputerName = ConfigDll::Config_ReadComputer().ComputerName; //随便取一个值，看看是否存在
	if (ComputerName == "") {
		std::string a = Random_Character(10);
		ConfigDll::Config_CreateComputer(a.c_str(),"Default");
	}
}

std::string AppClass::Random_Character(int len) {
	std::string result = "";
	srand((unsigned int)time(NULL));
	for (int i = 0; i < len; ++i)
	{
		switch ((rand() % 3))
		{
		case 1:
			result += 'A' + rand() % 26;
			break;
		case 2:
			result += 'a' + rand() % 26;
			break;
		default:
			result += '0' + rand() % 10;
			break;
		}
	}
	return result;
}