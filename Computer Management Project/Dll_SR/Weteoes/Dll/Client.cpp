#include "Client.h"

ClientDll::Fun1 ClientDll::Client_Entrance;
bool ClientDll::Loading()
{
	HMODULE dll = LoadLibrary(TEXT("Client.dll"));//º”‘ÿdll
	if (!dll) { MessageBox(NULL, TEXT("º”‘ÿClient-DLL ß∞‹ code:-1"), TEXT(""), MB_OK); return false; }
	Client_Entrance =
		(Fun1)GetProcAddress(dll, "Client_Entrance");
	return true;
}