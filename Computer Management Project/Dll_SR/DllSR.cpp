#include <Loading.h>

//App
#include <Application/RSA.h>
#include <Application/Socket.h>

//Dll
#include <Dll/WeteoesDll.h>
#include <Dll/Client.h>

bool Loading() {
	if (!WeteoesDll().Loading()) { return false; }
	if (!ClientDll().Loading()) { return false; }
	return true;
}
static std::string TEMP_S;
extern "C" _declspec(dllexport) char* Socket_Entrance() {
	if (!Loading()) { return NULL; }
	return SocketClass().Entrance();
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