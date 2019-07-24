#include <Weteoes/Loading.h>
#include <Weteoes/Application/RSA.h>
#include <Weteoes/Application/Sockets/ServerSocket.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/ManagementDll.h>
#include <Weteoes/Dll/ConfigDll.h>
#include <Weteoes/Dll/ClientDll.h>

bool Loading() {
	if (!WeteoesDll().Loading()) { return false; }
	if (!ClientDll().Loading()) { return false; }
	if (!ConfigDll().Loading()) { return false; }
	if (!ManagementDll().Loading()) { return false; }
	return true;
}
static std::string TEMP_S;
extern "C" _declspec(dllexport) int Socket_Entrance() {
	if (!Loading()) { return NULL; }
	return ServerSocketClass::use.Entrance();
}
extern "C" _declspec(dllexport) char* RSA_Encode(char* data, char* key) {
	if (!Loading()) { return NULL; }
	TEMP_S = RSAClass().Encode(data, key);
	return (char*)TEMP_S.c_str();
}
extern "C" _declspec(dllexport) char* RSA_UnEncode(char* data, char* key) {
	if (!Loading()) { return NULL; }
	TEMP_S = RSAClass().UnEncode(data, key);
	return (char*)TEMP_S.c_str();
}