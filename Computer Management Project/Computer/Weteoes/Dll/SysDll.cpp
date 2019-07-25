#include "SysDll.h"

SysDll::Fun1 SysDll::Install;
SysDll::Fun2 SysDll::getInstall;

bool SysDll::Loading()
{
	HMODULE dll_WUpdate = LoadLibrary(TEXT("Sys.dll"));//º”‘ÿdll
	if (!dll_WUpdate) { MessageBox(NULL, TEXT("º”‘ÿSys.dll ß∞‹ code:-1"), TEXT(""), MB_OK); return false; }
	Install =
		(Fun1)GetProcAddress(dll_WUpdate, "Install");
	getInstall =
		(Fun2)GetProcAddress(dll_WUpdate, "getInstall");
	return true;
}