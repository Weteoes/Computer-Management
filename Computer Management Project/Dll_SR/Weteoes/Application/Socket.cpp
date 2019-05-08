#include "Socket.h"

//Dll
#include <Dll/WeteoesDll.h>
#include <Dll/Client.h>
#include <Dll/Config.h>
#include <Dll/Management.h>

//App
#include <Application/AppConfig.h>
#include <Application/RSA.h>

#include <thread>

bool SocketClass::SocketStopFlac = false;

char* SocketClass::Entrance() {
	SocketStart();
	return (char*)"ok";
}
SOCKADDR_IN SocketClass::Socket_Initialization() {
	SOCKADDR_IN server;
	memset(&server, 0, sizeof(SOCKADDR_IN)); //初始化(先将保存地址的server置为全0)

	if (!ManagementDll().Loading()) { return server; }
	std::string URL_Socket = ManagementDll::Get((char*)"URL_Socket");
	int Socket_Port = atoi(ManagementDll::Get((char*)"Socket_Port"));
	if (URL_Socket.empty() || Socket_Port <= 0) { return server; }
	server.sin_family = PF_INET; //声明地址格式是TCP/IP地址格式
	server.sin_port = htons(Socket_Port); //指明连接服务器的端口号
	/* 解析域名 */
	getDomainIp:
	std::string ServerIp = GetIpByName(URL_Socket); //因为是域名要转换
	if (ServerIp == "") { Sleep(3000); goto getDomainIp; }
	inet_pton(AF_INET, ServerIp.c_str(), &server.sin_addr.S_un.S_addr);//字符串变成网路地址
	return server;
}
void SocketClass::SocketStart() {
	WSADATA wsaData;   
	WSAStartup(0x0202, &wsaData);

	SOCKET sClient; //Socket
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //创建客户端套节字
	SOCKADDR_IN server = Socket_Initialization();

	////设置非堵塞Socket
	//int ioctlsocket_ = 1;
	//result = ioctlsocket(sClient, FIONBIO, (u_long FAR*)&ioctlsocket_);
	//if (result == SOCKET_ERROR) { return; }

	/* Timeout */
	//int timeout = 3000; //3s
	//result = setsockopt(sClient, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));
	//if (result == SOCKET_ERROR) { return; }
	//result = setsockopt(sClient, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
	//if (result == SOCKET_ERROR) { return; }

	/* Connect */
	int result; //返回
	while (!SocketStopFlac) {
		result = connect(sClient, (struct sockaddr *) &server, sizeof(SOCKADDR_IN)); //连接
		if (result == SOCKET_ERROR) {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK || err == WSAEINVAL) {
				Sleep(3000);
				continue;
			}
			else if (err == WSAEISCONN) { break; } //处于连接状态
			else {
				Sleep(3000);
				continue;
			}
		}
	}

	/* Flag */
	bool SocketReset = false; //Reset Socket

	/* Send */
	std::string SendStr = GetConfig(); //获取用户字符串(加入分割符)
	if (!Send_Socket(sClient, SendStr)) { SocketReset = true; }

	/* While Recv */
	std::thread RecvSocket(&SocketClass::Recv_Socket_While, this, sClient); RecvSocket.detach(); //循环Send

	/* While Send */
	while (!SocketStopFlac) {
		if (!Send_Socket(sClient, ConfigClass::Socket_Hello)) {
			SocketReset = true;
			break;
		}
		::Sleep(1000 * 60);
	}

	/* Reset Socket */
	if (SocketReset) { //如果需要重新连接
		SocketReset = false;
		SocketStart();
	}

	/* Stop Socket */
	SocketStop(sClient); 
}
void SocketClass::Recv_Socket_While(SOCKET socket) {
	std::string Recv_Cache = ""; //TEMP
	while (!SocketStopFlac) {
		Recv_Cache = Recv_Socket(socket);
		if (Recv_Cache == ConfigClass::Socket_Error) { break; } //Recv Error
		if (Recv_Cache.empty()) { continue; }
		std::thread Socket(&SocketClass::Socket_RunShell, this, Recv_Cache); Socket.detach(); //执行动作
		Recv_Cache = ""; // Clear TEMP
	}
}
std::string SocketClass::Recv_Socket(SOCKET socket) {
	/* Initialization */
	int result; //recv result
	int ConfigCache = ConfigClass::Socket_Cache; //配置的缓存大小
	char *result_byte = new char[ConfigCache]; //缓存数据byte
	std::string AllResult = ""; //已经接收数据
	ULONG MoreLen; //剩下的数据大小

	/* While Reve */
	W_recv:
	while (true) {
		result = recv(socket, result_byte, ConfigCache - 1, 0); //接收数据(需要添加结束标记所以-1)
		if (result == SOCKET_ERROR) {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK) {
				continue;
			}
			else { //接收失败
				return ConfigClass::Socket_Error;
			}
		}
		/* Recv */
		result_byte[result] = 0x00; //添加结束标记
		AllResult += result_byte; //Cache >> AllResult
		memset(result_byte, 0, ConfigCache); //清空之前的数据
		ioctlsocket(socket, FIONREAD, &MoreLen); //检查剩下的数据
		if (MoreLen == 0) { //接收完毕
			return AllResult;
		}
		goto W_recv;
	}
}
bool SocketClass::Send_Socket(SOCKET socket,std::string data) {
	data = RSAClass().A_PublicEncode(data) + "|"; //加密数据和分隔符
	int result; //send result
	while (true) {
		result = send(socket, data.c_str(), (int)strlen(data.c_str()), 0); //发送数据
		if (result == SOCKET_ERROR) {
			int err = WSAGetLastError();
			if (err == WSAEWOULDBLOCK) {
				Sleep(100);
				continue;
			}
			else { //发送失败
				return false;
			}
		}
		return true;
	}
}
void SocketClass::SocketStop(SOCKET socket) {
	//释放连接和进行结束工作      
	closesocket(socket);
	WSACleanup();
}
void SocketClass::Socket_RunShell(std::string data) { //执行动作
	std::string re = RSAClass().B_PrivateUnEncode(data); //解密数据
	if (re == "") { return; } //解密失败
	if (re == ConfigClass::Socket_Error) { //如果是Error(密码错误)
		SocketStopFlac = true;
		RebootSoftware();
		return;
	}
	else if (re == ConfigClass::Socket_OK) { //如果是Success
		return;
	}
	else { //是其他的话
		if (!ClientDll::Client_Entrance((char*)re.c_str())) { //执行，如果不是合法信息
			return;
		}
	}
}

std::string SocketClass::GetConfig()
{
	if (!ConfigDll().Loading()) { return ""; }
	ConfigDllStruct::UserConfig_ UserConfig = ConfigDll::Config_ReadUser();
	ConfigDllStruct::ComputerConfig_ ComputerConfig = ConfigDll::Config_ReadComputer();
	std::string b = "Weteoes_Server_";
	b += std::string(UserConfig.w) + "|" + std::string(ComputerConfig.ComputerName);
	return b;
}

std::string SocketClass::GetIpByName(std::string a) {
	std::string result = "";
	struct addrinfo hints;
	struct addrinfo *res;
	struct sockaddr_in *addr;
	char ipbuf[16];
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET; /* Allow IPv4 */
	hints.ai_flags = AI_PASSIVE; /* For wildcard IP address */
	hints.ai_protocol = 0; /* Any protocol */
	hints.ai_socktype = SOCK_STREAM;
	int i = getaddrinfo(a.c_str(), NULL, &hints, &res);
	if (i == -1) { return ""; }
	if (res == NULL) { return ""; }
	addr = (struct sockaddr_in *)res->ai_addr;
	return inet_ntop(AF_INET, &addr->sin_addr, ipbuf, 16);
}
void SocketClass::RebootSoftware() {
	WeteoesDll().Loading();
	ConfigDll().Loading();
	ManagementDll().Loading();
	ConfigDll::Config_CreateUser((char*)""); //清空配置
	std::string Software_Name = ManagementDll::Get((char*)"Software_Name");
	if (Software_Name.empty()) { return; }
	std::string ApplictionPath = WeteoesDll::Basics_GetNowFilePath(); 
	std::string a = ApplictionPath + Software_Name +".exe";
	WeteoesDll::CMD_Run((char*)a.c_str()); //重新启动
	exit(0x51);
}