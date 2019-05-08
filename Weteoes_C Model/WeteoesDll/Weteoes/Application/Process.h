#ifdef ProcessClass_
#else
#define ProcessClass_
#include <Loading.h>

class ProcessClass
{
public:
	char* AsUser(char* file, char* SoftwareName); //通过管理员启动某程序
	int* GetProcessidFromName(char* name,int* count); //检查某进程是否存在
	bool SoftwareExist(char* name,char* title); //检查软件是否运行中(通过进程名和标题)
private:
	HANDLE GetToken(DWORD dwProcessID);
	bool createProcessWithAdmin(const std::string&);
};

//App
#include <Application/Convert.h>
#include <WtsApi32.h>
#pragma comment(lib, "WtsApi32.lib") //WTSQueryUserToken
/*
	通过管理员启动某程序
	ReStart = true 启动失败时重试，直到启动
*/
#include <UserEnv.h>
#pragma comment(lib, "Userenv.lib")
char* ProcessClass::AsUser(char* file, char* SoftwareName) {
	std::string result_s = "Error";
	bool OK = false; //启动结果

	/* 是否已经存在进程 */
	int GPFN;
	GetProcessidFromName(SoftwareName,&GPFN);
	if (GPFN != 0) { result_s = "Find Process"; goto w_result; }
	{
		/* 尝试启动 */
		if (createProcessWithAdmin(file)) {
			int GPFN;
			Sleep(600);
			GetProcessidFromName(SoftwareName, &GPFN);
			if (GPFN != 0) { OK = true; }
		}
	}

	/* 检查结果 */
	if (OK) { //Success
		result_s = "Success";
		goto w_result;
	}
	else { //!OK
		result_s = "CreateProcessAsUser is Error";
		goto w_result; 
	} 

w_result:
	char* result = ConvertClass().GetChars(result_s);
	return result;
}

bool ProcessClass::createProcessWithAdmin(const std::string& process_name)
{
	HANDLE hToken = NULL;
	HANDLE hTokenDup = NULL;

	if (process_name.empty()) { return false; }
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken)) { return false; }

	if (!DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, NULL, SecurityAnonymous, TokenPrimary, &hTokenDup)) {
		CloseHandle(hToken);
		return false;
	}
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	LPVOID pEnv = NULL;
	DWORD dwSessionId = NULL;
	do {
		// 不等于NULL说明不是第一次执行
		if (dwSessionId != NULL) { Sleep(100); }
		// 获取sessionID
		dwSessionId = WTSGetActiveConsoleSessionId();
	} while (dwSessionId <= 0); //0为SYSTEM
	WTSQueryUserToken(dwSessionId, &pEnv);

	if (!SetTokenInformation(hTokenDup, TokenSessionId, &dwSessionId, sizeof(DWORD)))
	{
		CloseHandle(hToken);
		CloseHandle(hTokenDup);
		return false;
	}

	si.cb = sizeof(STARTUPINFO);
	//si.lpDesktop = (LPSTR)"WinSta0\\Default";
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW;

	if (!CreateEnvironmentBlock(&pEnv, hTokenDup, FALSE))
	{
		CloseHandle(hToken);
		CloseHandle(hTokenDup);
		return false;
	}

	if (!CreateProcessAsUser(hTokenDup, process_name.c_str(), NULL, NULL, NULL, FALSE,
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT,
		pEnv, NULL, &si, &pi))
	{
		CloseHandle(hToken);
		CloseHandle(hTokenDup);
		return false;
	}

	if (pEnv) { DestroyEnvironmentBlock(pEnv); }

	CloseHandle(hToken);
	CloseHandle(hTokenDup);
	return true;
}

#include <Tlhelp32.h>
#include <list>
int* ProcessClass::GetProcessidFromName(char* name, int* count)
{
	std::list<int> list_id; //临时保存ID
	PROCESSENTRY32 pe;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hSnapshot, &pe)) {
		return 0;
	}
	/* name to UP */
	BasicsClass Basics;
	std::string Name_s = name; name = Basics.CharToUL((char*)Name_s.c_str(), true);

	/* While */
	while (1)
	{
		pe.dwSize = sizeof(PROCESSENTRY32);
		/* 第一个要Skip，因为不是Prcoess */
		if (Process32Next(hSnapshot, &pe) == FALSE)
			break;

		/* 判断进程名 */
		if (strcmp(Basics.CharToUL(pe.szExeFile,true), name) == 0)
		{
			list_id.push_back(pe.th32ProcessID);
			continue;
		}
	}
	CloseHandle(hSnapshot);

	/* result */
	int *result = new int[list_id.size()];
	int id_now = 0; //记录id写的位置
	std::list<int>::iterator iterator = list_id.begin();
	while (iterator != list_id.end()) {
		result[id_now++] = (int)*iterator;
		*iterator++;
	}
	*count = (int)list_id.size();
	return result;
}

/* 枚举窗口参数 */
typedef struct
{
	HWND    hwndWindow = NULL;  //窗口句柄
	DWORD   dwProcessID;        //进程ID
	char*   Title;				//窗口Title
	bool	result = false;		//结果
}EnumWindowsArg;
/*
	hwnd 窗口句柄
	lParam struct
*/
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	EnumWindowsArg* pArg = (EnumWindowsArg*)lParam;
	/* Basics 大小写 */
	BasicsClass Basics;
	std::string Title_s = pArg->Title;
	char *Title_c = Basics.CharToUL((char*)Title_s.c_str(), true);;

	DWORD  dwProcessID = 0;
	// 通过窗口句柄取得进程ID
	::GetWindowThreadProcessId(hwnd, &dwProcessID);
	if (dwProcessID == pArg->dwProcessID)
	{
		pArg->hwndWindow = hwnd;
		/* Title */
		if (hwnd != NULL) {
			TCHAR t[255];
			GetWindowText(hwnd, t, 255);

			/* PD */
			if (strcmp(Basics.CharToUL(t, true), Title_c) == 0) { 
				pArg->result = true;
				return false; //找到了返回FALSE
			}
		}
	}
	return true;
}

bool ProcessClass::SoftwareExist(char* name, char* title)
{
	/* Prcoess ID */
	int a;
	int *b = GetProcessidFromName(name, &a);
	if (a == 0) { return false; }

	/* For */
	for (int i = 0; i < a; i++) {
		/* Enum */
		HWND hwndRet = NULL;
		EnumWindowsArg ewa;
		ewa.dwProcessID = b[i];
		ewa.Title = title;
		EnumWindows(EnumWindowsProc, (LPARAM)&ewa);
		if (ewa.result) {
			return true;
		}
	}
	return false;
}

HANDLE ProcessClass::GetToken(DWORD dwProcessID)
{
	HANDLE hProcess = NULL;
	HANDLE hToken = NULL;
	HANDLE g_hToken = NULL;
	PSECURITY_DESCRIPTOR pSD = NULL;
	try
	{
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, dwProcessID);
		if (hProcess == NULL) { return NULL; }
		if (!OpenProcessToken(hProcess, TOKEN_ALL_ACCESS, &hToken))
		{
			CloseHandle(hProcess);
			return NULL;
		}
		pSD = (PSECURITY_DESCRIPTOR)GlobalAlloc(GPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
		if (pSD == NULL)
		{
			CloseHandle(hToken);
			CloseHandle(hProcess);
			return NULL;
		}
		if (!InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION))
		{
			GlobalFree(pSD);
			CloseHandle(hToken);
			CloseHandle(hProcess);
			return NULL;
		}
		if (!SetSecurityDescriptorDacl(pSD, TRUE, (PACL)NULL, FALSE))
		{
			GlobalFree(pSD);
			CloseHandle(hToken);
			CloseHandle(hProcess);
			return NULL;
		}
		SECURITY_ATTRIBUTES sa;
		sa.nLength = sizeof(sa);
		sa.lpSecurityDescriptor = pSD;
		sa.bInheritHandle = TRUE;
		if (!DuplicateTokenEx(hToken, TOKEN_ALL_ACCESS, &sa, SecurityImpersonation, TokenPrimary, &g_hToken))
		{
			CloseHandle(hToken);
			CloseHandle(hProcess);
			GlobalFree(pSD);
			return NULL;
		}
	}
	catch (...) {}
	CloseHandle(hToken);
	CloseHandle(hProcess);
	GlobalFree(pSD);
	return g_hToken;
}
#endif // ProcessClass_