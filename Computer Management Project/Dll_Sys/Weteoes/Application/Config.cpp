#include <Weteoes/Application/Config.h>

std::string ConfigClass::ConfigPath;
std::string ConfigClass::StartTime;
std::string ConfigClass::ServiceName = "Computer";

void ConfigClass::Loading() {
	StartTime = loadingStartTime(); // 初始化启动时间
	ConfigPath = loadingServicePath(); // 初始化服务目录
}

#include <shlobj.h> // SHGetSpecialFolderPath
std::string ConfigClass::loadingServicePath() {
	TCHAR path[260];
	SHGetSpecialFolderPath(0, path, CSIDL_COMMON_APPDATA, 0);
	std::string a = path; a += "\\Weteoes\\" + ServiceName;
	return a;
}
#include <time.h>
std::string ConfigClass::loadingStartTime() {
	time_t a;
	time(&a);
	tm b;
	localtime_s(&b, &a);
	char TimeString[255];
	sprintf_s(TimeString, "%04d%02d%02d_%02d%02d%02d",
		b.tm_year + 1900,
		b.tm_mon + 1,
		b.tm_mday,
		b.tm_hour,
		b.tm_min,
		b.tm_sec
	);
	return TimeString;
}