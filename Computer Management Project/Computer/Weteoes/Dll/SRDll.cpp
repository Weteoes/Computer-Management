#include "SRDll.h"

SRDll::Socket_Entrance_ SRDll::Socket_Entrance;
SRDll::RSA_Encode_ SRDll::RSA_Encode;
SRDll::RSA_UnEncode_ SRDll::RSA_UnEncode;
bool SRDll::Loading()
{
	HMODULE dll = LoadLibrary(TEXT("SR.dll"));//º”‘ÿdll
	if (!dll) { MessageBox(NULL, TEXT("º”‘ÿSR-DLL ß∞‹ code:-1"), TEXT(""), MB_OK); return false; }
	Socket_Entrance =
		(Socket_Entrance_)GetProcAddress(dll, "Socket_Entrance");
	RSA_Encode =
		(RSA_Encode_)GetProcAddress(dll, "RSA_Encode");
	RSA_UnEncode =
		(RSA_UnEncode_)GetProcAddress(dll, "RSA_UnEncode");
	return true;
}