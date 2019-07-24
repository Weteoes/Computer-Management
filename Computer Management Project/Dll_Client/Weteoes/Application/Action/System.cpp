#ifndef SystemClass_CPP
#define SystemClass_CPP
#include "System.h"
#include <Weteoes/Dll/Management.h>

void SystemClass::Entrance(std::string data) {
	if (ConfigClass::use.StrToLower(data) == ConfigClass::use.StrToLower("Up")) { System_Volume(1); return; }
	else if (ConfigClass::use.StrToLower(data) == ConfigClass::use.StrToLower("Down")) { System_Volume(-1); return; }
}
void SystemClass::System_Volume(int i) {
	if (!ManagementDll().Loading()) { return; }
	std::string Software_Title = ManagementDll::Get((char*)"Software_Title");
	HWND a = FindWindow(NULL, Software_Title.c_str());
	switch (i)
	{
	case 1: //Up
		SendMessage(a, WM_APPCOMMAND, 0x30292, APPCOMMAND_VOLUME_UP * 0x10000);
		break;
	case -1: //Down
		SendMessage(a, WM_APPCOMMAND, 0x30292, APPCOMMAND_VOLUME_DOWN * 0x10000);
		break;
	}
}
#endif