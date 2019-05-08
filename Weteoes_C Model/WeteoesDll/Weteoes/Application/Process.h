#ifdef ProcessClass_
#else
#define ProcessClass_
#include <Loading.h>

class ProcessClass
{
public:
	char* AsUser(char* file, char* SoftwareName); //ͨ������Ա����ĳ����
	int* GetProcessidFromName(char* name,int* count); //���ĳ�����Ƿ����
	bool SoftwareExist(char* name,char* title); //�������Ƿ�������(ͨ���������ͱ���)
private:
	HANDLE GetToken(DWORD dwProcessID);
	bool createProcessWithAdmin(const std::string&);
};

//App
#include <Application/Convert.h>
#include <WtsApi32.h>
#pragma comment(lib, "WtsApi32.lib") //WTSQueryUserToken
/*
	ͨ������Ա����ĳ����
	ReStart = true ����ʧ��ʱ���ԣ�ֱ������
*/
#include <UserEnv.h>
#pragma comment(lib, "Userenv.lib")
char* ProcessClass::AsUser(char* file, char* SoftwareName) {
	std::string result_s = "Error";
	bool OK = false; //�������

	/* �Ƿ��Ѿ����ڽ��� */
	int GPFN;
	GetProcessidFromName(SoftwareName,&GPFN);
	if (GPFN != 0) { result_s = "Find Process"; goto w_result; }
	{
		/* �������� */
		if (createProcessWithAdmin(file)) {
			int GPFN;
			Sleep(600);
			GetProcessidFromName(SoftwareName, &GPFN);
			if (GPFN != 0) { OK = true; }
		}
	}

	/* ����� */
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
		// ������NULL˵�����ǵ�һ��ִ��
		if (dwSessionId != NULL) { Sleep(100); }
		// ��ȡsessionID
		dwSessionId = WTSGetActiveConsoleSessionId();
	} while (dwSessionId <= 0); //0ΪSYSTEM
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
	std::list<int> list_id; //��ʱ����ID
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
		/* ��һ��ҪSkip����Ϊ����Prcoess */
		if (Process32Next(hSnapshot, &pe) == FALSE)
			break;

		/* �жϽ����� */
		if (strcmp(Basics.CharToUL(pe.szExeFile,true), name) == 0)
		{
			list_id.push_back(pe.th32ProcessID);
			continue;
		}
	}
	CloseHandle(hSnapshot);

	/* result */
	int *result = new int[list_id.size()];
	int id_now = 0; //��¼idд��λ��
	std::list<int>::iterator iterator = list_id.begin();
	while (iterator != list_id.end()) {
		result[id_now++] = (int)*iterator;
		*iterator++;
	}
	*count = (int)list_id.size();
	return result;
}

/* ö�ٴ��ڲ��� */
typedef struct
{
	HWND    hwndWindow = NULL;  //���ھ��
	DWORD   dwProcessID;        //����ID
	char*   Title;				//����Title
	bool	result = false;		//���
}EnumWindowsArg;
/*
	hwnd ���ھ��
	lParam struct
*/
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	EnumWindowsArg* pArg = (EnumWindowsArg*)lParam;
	/* Basics ��Сд */
	BasicsClass Basics;
	std::string Title_s = pArg->Title;
	char *Title_c = Basics.CharToUL((char*)Title_s.c_str(), true);;

	DWORD  dwProcessID = 0;
	// ͨ�����ھ��ȡ�ý���ID
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
				return false; //�ҵ��˷���FALSE
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