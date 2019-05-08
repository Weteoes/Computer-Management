#include "App.h"
#include <thread>

#include "../../stdafx.h"
#include "../../Resource.h"

//App
#include <Application/Dlg.h>
#include <Application/AppConfig.h>

//Dll
#include <Dll/SR.h>
#include <Dll/Config.h>

//Dlg
#include <Dlg/Dlg_Main.h>

void AppClass::Login_Success() {
	AppConfigClass::IsLogin = true;
	PD_Config(); //先判断配置是否存在
	DlgClass().Dlg_Mini();
	std::thread Main(&AppClass::Dlg_Main_Start, this); Main.detach(); //Create Thread
}
void AppClass::Start_SR() {
	std::thread SR(&AppClass::SR_, this); SR.detach();
}


void AppClass::SR_() {
	if (!SRDll().Loading()) { DlgClass().Dlg_Close(); }
	while (1) {
		SRDll::Socket_Entrance();
		Sleep(1000);
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