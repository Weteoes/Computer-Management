#include "App.h"
#include <thread>
#include <stdafx.h>
#include <Resource.h>
#include <Weteoes/Application/Dlg.h>
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dlg/Dlg_Main.h>
#include <Weteoes/Dll/SRWDll.h>
#include <Weteoes/Dll/ConfigDll.h>

void AppClass::Login_Success() {
	AppConfigClass::IsLogin = true;
	PD_Config(); //先判断配置是否存在
	DlgClass().Dlg_Mini();
	std::thread Main(&AppClass::Dlg_Main_Start, this); Main.detach(); //Create Thread
}
void AppClass::Start_SRW() {
	if (!SRWDll().Loading()) { DlgClass().Dlg_Close(); }
	std::thread web(&AppClass::SRW, this, 0); web.detach(); // 启动UI
	std::thread socket(&AppClass::SRW, this, 1); socket.detach(); // 启动Socket
}

void AppClass::SRW(int type) {
	switch (type) {
		case 0: { // UI 服务
			std::string a = WeteoesDll::Basics_GetNowFilePath() + std::string("UI");
			SRWDll::Web_Entrance(a.c_str());
			break;
		}
		case 1: { // Socket 服务
			while (1) {
				SRWDll::Socket_Entrance();
				Sleep(1000);
			}
			break;
		}
	}
}
void AppClass::Dlg_Main_Start() {
	Dlg_Main dlg;
	if (AppConfigClass::IsMiniStartMain) {
		dlg.Create(IDD_Dlg_Main);
		dlg.ShowWindow(SW_HIDE);
		dlg.RunModalLoop();
	}
	else {
		dlg.DoModal();
	}
}
void AppClass::PD_Config() {
	ConfigDll().Loading();

	//Computer
	std::string ComputerName = ConfigDll::Config_ReadComputer().ComputerName; //随便取一个值，看看是否存在
	if (ComputerName == "") {
		std::string a = Random_Character(10);
		ConfigDll::Config_CreateComputer((char*)a.c_str(),"Default");
	}
}
std::string AppClass::Random_Character(int len)
{
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