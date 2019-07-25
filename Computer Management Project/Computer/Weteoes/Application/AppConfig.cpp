#include "AppConfig.h"
#include <Weteoes/Dll/ManagementDll.h>

bool AppConfigClass::IsLogin = false;
bool AppConfigClass::IsMiniStartMain = true;
std::string AppConfigClass::SoftwareName;

// ��ȡ�汾
std::string AppConfigClass::Get_Version() {
	if (!ManagementDll().Loading()) { return ""; }
	std::string Version = ManagementDll::Get("Version");
	if (Version.empty()) { return ""; }
	return Version;
}

// ��ȡ��ʱ����λ��
std::string AppConfigClass::Get_TempPath() {
	char Temp[MAX_PATH];
	GetTempPath(MAX_PATH, Temp);
	std::string TempHome = (std::string)Temp + "Weteoes\\Computer Management\\";
	return TempHome;
}