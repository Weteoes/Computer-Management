#include <Weteoes/Loading.h>
#include <Weteoes/Application/Main.h>
#include <Weteoes/Application/Config.h>
#include <Weteoes/Application/Message.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/ManagementDll.h>

void MainClass::Entrance() {
	char buf[256] = "";
	DWORD rlen = 0;
	while (true) {
		// ������ȫ�ļ���������û�ͨ�ţ�
		SECURITY_DESCRIPTOR sd;
		if (0 == InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION) || 
			0 == SetSecurityDescriptorDacl(&sd, TRUE, static_cast<PACL>(0), FALSE)
		){
			return; 
		}
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = &sd;
		sa.bInheritHandle = FALSE;
		// PIPE
		HANDLE hPipe = CreateNamedPipe(
		TEXT("\\\\.\\Pipe\\Weteoes_Computer"),						//�ܵ���
		PIPE_ACCESS_DUPLEX,									//�ܵ����� 
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,	//�ܵ�����
		PIPE_UNLIMITED_INSTANCES,							//�ܵ��ܴ��������ʵ������
		0,													//������������� 0��ʾĬ��
		0,													//���뻺�������� 0��ʾĬ��
		NMPWAIT_WAIT_FOREVER,								//��ʱʱ��
		&sa);													//ָ��һ��SECURITY_ATTRIBUTES�ṹ,���ߴ�����ֵ.
	if (INVALID_HANDLE_VALUE == hPipe) { return;  }
		MessageClass::WriteFileLog("-------------------");
		MessageClass::WriteFileLog("Listen Pipe success");
		ConnectNamedPipe(hPipe, NULL); // �����ȴ��ͻ�������
		MessageClass::WriteFileLog("Client Connect Pipe");
		bool result = ReadFile(hPipe, buf, 256, &rlen, NULL);  // ���ܿͻ��˷��͹���������
		if (!result) { MessageClass::WriteFileLog("error"); return; }
		std::string resultData = buf;
		MessageClass::WriteFileLog("Accept:"+ resultData);
		pipeEntrance(resultData); //PIPE�¼�
	}
}
void MainClass::pipeEntrance(std::string data) {
	if (data == "restart") {
		stopSoftware();
		Sleep(1000); // ��ֹstop�ӳ�
		startSoftware();
	}
}
void MainClass::stopSoftware() {
	std::string Software_Name = ManagementDll::Get((char*)"Software_Name");
	if (Software_Name.empty()) { return; }
	std::string shell = "cmd.exe /c taskkill /F /IM " + Software_Name + ".exe";
	WeteoesDll::CMD_Run((char*)shell.c_str());
}
#include <Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")

void MainClass::startSoftware() {
	/* Management */
	std::string SoftwareName = ManagementDll::Get((char*)"Software_Name") + std::string(".exe");

	/* Regedit */
	HKEY a = WeteoesDll::Regedit_OpenRegFile(HKEY_LOCAL_MACHINE, (char*)"SOFTWARE\\Weteoes\\Computer");
	std::string Path = WeteoesDll::Regedit_QueryRegValue(a, (char*)"Path", REG_SZ, false);

	/* Log */
	MessageClass::WriteFileLog("Path is " + Path);
	MessageClass::WriteFileLog("SoftwareName is " + SoftwareName);

	std::string Appliction = Path + SoftwareName;

	/* Operting */
	if (WeteoesDll::IO_Exists((char*)Appliction.c_str())) { //�ļ�����
		/* Log */
		MessageClass::WriteFileLog("Application is Find\nStart up to Application");

		std::string result; //���
		while (true) {
			result = WeteoesDll::Process_AsUser((char*)Appliction.c_str(), (char*)SoftwareName.c_str());
			MessageClass::WriteFileLog("Process_AsUser is " + result);
			if (result == "Success" || result == "Find Process") { break; }
			else { Sleep(1000); }
		}
	}
	else { MessageClass::WriteFileLog("Application is Not Find");  }
}