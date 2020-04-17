#include <pch.h>

#ifndef AppConfigClass_Cpp
#define AppConfigClass_Cpp

#include "AppConfig.h"

std::string AppConfigClass::SoftwareTitle;
std::string AppConfigClass::Version;

std::string AppConfigClass::Get_SoftwareTitle() {
	if (!SoftwareTitle.empty()) { return SoftwareTitle; }
	AppConfigClass::SoftwareTitle = ManagementDll::Get("Software_Title");
	return SoftwareTitle;
}

std::string AppConfigClass::Get_Version() {
	if (!Version.empty()) { return Version; }
	AppConfigClass::Version = ManagementDll::Get("Version");
	return Version;
}

std::string AppConfigClass::Get_TempPath() {
	char Temp[MAX_PATH];
	GetTempPath(sizeof(Temp), Temp);
	std::string TempHome = (std::string)Temp + "Weteoes\\" + Get_SoftwareTitle() + "\\";
	return TempHome;
}
#endif