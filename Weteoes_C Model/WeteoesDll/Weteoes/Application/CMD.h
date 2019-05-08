#ifdef CMDClass_
#else
#define CMDClass_
#include <Loading.h>

class CMDClass {
public:
	void Run(char*); //÷¥––CMD√¸¡Ó
};

#include <processthreadsapi.h>
void CMDClass::Run(char* shell) {
	std::string shell_s = shell;
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;//CREATE_NEW_CONSOLE
	CreateProcess(NULL, (LPSTR)shell_s.c_str(), NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}
#endif // CMDClass_