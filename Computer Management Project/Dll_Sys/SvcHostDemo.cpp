#include <Weteoes/Loading.h>
#include <Weteoes/Application/Message.h>
#include <Weteoes/Application/Config.h>
#include <Weteoes/Application/Install.h>
#include <Weteoes/Application/Main.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/ManagementDll.h>

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    return true;
}

SERVICE_STATUS_HANDLE g_serviceStatusHandle = nullptr;

SERVICE_STATUS g_serviceStatus = 
{
    SERVICE_WIN32_SHARE_PROCESS,
    SERVICE_START_PENDING,
    SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE
};

DWORD WINAPI HandlerEx(
    DWORD dwControl,
    DWORD dwEventType,
    LPVOID lpEventData,
    LPVOID lpContext
)
{
    switch (dwControl)
    {
    case SERVICE_CONTROL_STOP:
    case SERVICE_CONTROL_SHUTDOWN:
        g_serviceStatus.dwCurrentState = SERVICE_STOPPED;
        break;
    case SERVICE_CONTROL_PAUSE:
        g_serviceStatus.dwCurrentState = SERVICE_PAUSED;
        break;
    case SERVICE_CONTROL_CONTINUE:
        g_serviceStatus.dwCurrentState = SERVICE_RUNNING;
        break;
    case SERVICE_CONTROL_INTERROGATE:
        break;
    default:
        break;
    };

    SetServiceStatus(g_serviceStatusHandle, &g_serviceStatus);

    return NO_ERROR;
}
void Loading(int i) {
	// 先设置Dll读取位置
	ConfigClass().Loading();
	std::string DllPath = ConfigClass::ConfigPath + "\\sys"; //Dll Path
	SetCurrentDirectory(DllPath.c_str());
	// Dll
	WeteoesDll().Loading();
	ManagementDll().Loading();
	switch (i)
	{
	case 0:
		MessageClass::WriteFileLog("Service");
		break;
	case 1:
		MessageClass::WriteFileLog("Service Install");
		break;
	}
}
extern "C" __declspec(dllexport) VOID WINAPI ServiceMain(DWORD dwArgc, LPCWSTR* lpszArgv)
{
    g_serviceStatusHandle = RegisterServiceCtrlHandlerExW(L"Weteoes", HandlerEx, nullptr);
    if (!g_serviceStatusHandle)
    {
        return;
    }
	g_serviceStatus.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(g_serviceStatusHandle, &g_serviceStatus);
	Loading(0);
	MainClass().Entrance();
}

extern "C" __declspec(dllexport) void Install() // 安装服务
{
	Loading(1);
	InstallClass().Install();
}

extern "C" __declspec(dllexport) bool getInstall() // 获取服务是否安装
{
	Loading(2);
	return WeteoesDll::IO_Exists((char*)ConfigClass::ConfigPath.c_str());
}
