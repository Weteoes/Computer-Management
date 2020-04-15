#include <Weteoes/Application/Message.h>
#include <Weteoes/Application/Config.h>
#include <Weteoes/Dll/WeteoesDll.h>

std::string WriteFileLogFile; //log�ļ�
void MessageClass::WriteFileLog(std::string data)
{
	if (WriteFileLogFile.empty()) {
		char temp[1024];
		sprintf_s(temp, sizeof(temp), "%s\\log\\%s.log", ConfigClass::ConfigPath.c_str(), ConfigClass::StartTime.c_str());
		WriteFileLogFile = temp;
	}
	else { data = "\n" + data; } //������ǵ�һ�����ݼ�\n
	WeteoesDll::IO_WriteFile((char*)WriteFileLogFile.c_str(), (char*)data.c_str(), (int)data.length());
}