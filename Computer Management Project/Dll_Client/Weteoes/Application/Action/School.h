#ifndef SchoolClass__
#define SchoolClass__
#include <Loading.h>
#include <Application/Config.h>
#include <Dll/WeteoesDll.h>

class SchoolClass {
public:
	void entrance(std::string); // 入口
private:
	void closeProcess(std::string); // 关闭进程
	std::string ReplaceString(std::string); // 替换关键字

	void operating_YiStart_Close(); // 解除学生端
	void operating_YiStart_Start(std::string); // 启动学生端
};

void SchoolClass::entrance(std::string data) {
	ConfigClass ConfigClass_;
	std::string shell = ConfigClass_.GetConfig(&data, "|"); // 获取指令
	if (ConfigClass_.StrToLower(data) == ConfigClass_.StrToLower("YiStart_Close")) { operating_YiStart_Close();  return; }
	if (ConfigClass_.StrToLower(data) == ConfigClass_.StrToLower("YiStart_Start")) { operating_YiStart_Start(shell);  return; }
}

void SchoolClass::closeProcess(std::string process) {
	int ProcessCount;
	WeteoesDll::Process_GetProcessidFromName((char*)process.c_str(), &ProcessCount);
	// 进程存在，再进行操作
	if (ProcessCount > 0) {
		std::string a = WeteoesDll::Basics_GetNowFilePath();
		a += "ntsd.exe -c q -pn " + process;
		WeteoesDll::CMD_Run((char*)a.c_str());
	}
}

// Operating
void SchoolClass::operating_YiStart_Close() {
	closeProcess("Nmdeputy.exe");
	closeProcess("YiStart.exe");
}

void SchoolClass::operating_YiStart_Start(std::string file) {
	if (file.empty()) { return; }
	file = ReplaceString(file);
	WeteoesDll::CMD_Run((char*)file.c_str());
}

std::string SchoolClass::ReplaceString(std::string data) {
	data = WeteoesDll::Basics_Replace((char*)data.c_str(), (char*)"[w,w]", (char*)"，");
	return data;
}
#endif // SchoolClass__