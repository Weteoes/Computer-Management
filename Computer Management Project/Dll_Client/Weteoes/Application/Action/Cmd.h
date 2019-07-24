#ifndef CmdClass_H
#define CmdClass_H
#include <Weteoes/Loading.h>

class CmdClass
{
public:
	void Run(std::string); //÷¥––CMD√¸¡Ó
};
void CmdClass::Run(std::string shell) {
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	CreateProcess(NULL, (LPSTR)shell.c_str(), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
#endif