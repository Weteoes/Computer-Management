#ifndef SchoolClass__
#define SchoolClass__
#include <Loading.h>
#include <Application/Config.h>
#include <Dll/WeteoesDll.h>

class SchoolClass {
public:
	void entrance(std::string); // ���
private:
	void closeProcess(std::string); // �رս���
	std::string ReplaceString(std::string); // �滻�ؼ���

	void operating_YiStart_Close(); // ���ѧ����
	void operating_YiStart_Start(std::string); // ����ѧ����
};

void SchoolClass::entrance(std::string data) {
	ConfigClass ConfigClass_;
	std::string shell = ConfigClass_.GetConfig(&data, "|"); // ��ȡָ��
	if (ConfigClass_.StrToLower(data) == ConfigClass_.StrToLower("YiStart_Close")) { operating_YiStart_Close();  return; }
	if (ConfigClass_.StrToLower(data) == ConfigClass_.StrToLower("YiStart_Start")) { operating_YiStart_Start(shell);  return; }
}

void SchoolClass::closeProcess(std::string process) {
	int ProcessCount;
	WeteoesDll::Process_GetProcessidFromName((char*)process.c_str(), &ProcessCount);
	// ���̴��ڣ��ٽ��в���
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
	data = WeteoesDll::Basics_Replace((char*)data.c_str(), (char*)"[w,w]", (char*)"��");
	return data;
}
#endif // SchoolClass__