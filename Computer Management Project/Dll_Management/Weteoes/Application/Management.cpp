#include <Weteoes/Application/Management.h>
#include <Weteoes/Application/Config.h>

std::string ManagementClass::Get(char* a) {
	std::string a_s = a;
	if		(a_s == "Software_UI_Port") { return Config_UI_Port; }  //客户端UI端口
	else if (a_s == "URL_Update") { return Config_URL; } // Update
	else if (a_s == "URL_Socket") { return Config_URL; }  // Socket
	else if (a_s == "Socket_Port") { return Config_Socket_Port; }  // Socket端口
	else if (a_s == "Software_Title") { return Config_Software_Title; }  // 程序窗口名称
	else if (a_s == "Software_Name") { return Config_Software_Name; }  // 程序进程名称
	else if (a_s == "Version") { return Config_Version; }  // Version
	return "";
}