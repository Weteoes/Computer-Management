#include <Weteoes/Application/Client.h>
#include <Weteoes/Dll/WeteoesDll.h>

bool Loading() {
	if (!WeteoesDll().Loading()) { return false; }
	return true;
}
extern "C" _declspec(dllexport) bool Client_Entrance(char* data) {
	if (!Loading()) { return false; }
	return ClientClass().Entrance(data);
}