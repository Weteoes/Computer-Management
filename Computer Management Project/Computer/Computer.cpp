
// Computer.cpp: 定义应用程序的类行为。
//

#include <pch.h>
#include "framework.h"
#include "Computer.h"

#include <thread>
#include <winsvc.h> //service
#include <Weteoes/Dlg/initDlg.h>
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/ConfigDll.h>
#include <Weteoes/Dll/ManagementDll.h>
#include <Weteoes/Dll/SysDll.h>




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CComputerApp

BEGIN_MESSAGE_MAP(CComputerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CComputerApp 构造

CComputerApp::CComputerApp() {
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
}


// 唯一的 CComputerApp 对象

CComputerApp theApp;


// CComputerApp 初始化
void CComputerApp::Loading() {
	// 是否有管理员权限
	bool isAdmin = IsUserAnAdmin();
	if (!Loading_Dll()) { exit(0x10); }
	if (!OnlySoftware()) { exit(0x11); }
	// 获取是否第一次运行
	bool pdFirst = PdFirst();
	// 第一次运行且有管理员
	if (pdFirst && isAdmin) { First_Init(); }
	// 第一次运行但没管理员
	if (pdFirst && !isAdmin) { MessageBox(NULL, "第一次运行需要授予管理员", "", MB_OK); exit(0x12); }
	// 如果没有管理员就通过PIPE重新启动(因为需要检查更新，所以堵塞当前线程等待提权完毕)
	if (!isAdmin) { std::thread RestartAtPIPE_(&CComputerApp::RestartAtPIPE, this); RestartAtPIPE_.join(); exit(0x13); }
	// 检查更新(因为需要结束当前进程，需要和当前进程相同权限，所以在权限提权完毕后判断)
	std::thread Update(&CComputerApp::PdUpdate, this); Update.detach();
}

// 判断是不是第一次运行
bool CComputerApp::PdFirst() {
	if (!SysDll().Loading()) { exit(0x200); }
	// 未安装服务
	if(!SysDll::getInstall()) { return true; }
	return false;
}

// 第一次运行初始化
void CComputerApp::First_Init() {
	if (!IsUserAnAdmin()) { MessageBox(NULL, "重新初始化需要授予管理员", "", MB_OK); return; }
	// 安装服务和注册表
	if (!SysDll().Loading()) { exit(0x201); }
	SysDll::Install();
	// 安装control服务
	std::string controlServer = WeteoesDll::Basics_GetNowFilePath() + std::string("ComputerControl.exe");
	std::string controlServerName = "ComputerControl";
	controlServer =
		"cmd /c "
		"(sc stop " + controlServerName + "|| echo 0)&&"
		"(sc delete " + controlServerName + "|| echo 1)&&"
		"(sc create " + controlServerName + " binPath=\""+ controlServer + "\"" + "|| echo 2)&&"
		"(sc description " + controlServerName + " \"Computer Control Server\"" + "|| echo 3)";
	WeteoesDll::CMD_Run((char*)controlServer.c_str());
	StartAtComputerOnStart(); // 设置开机启动
}	

// 判断是否有更新
void CComputerApp::PdUpdate() {
	std::string TempHome = AppConfigClass::Get_TempPath() + "Update\\";
	WeteoesDll::IO_CreatePath((char*)TempHome.c_str());
	char* ApplicationPath = WeteoesDll::Basics_GetNowFilePath();
	int ApplicationPathLen = (int)string(ApplicationPath).length();

	/* Update Software */
	CopyFile(((std::string)ApplicationPath + "WeteoesDll.dll").c_str(), (TempHome + "WeteoesDll.dll").c_str(), FALSE);
	CopyFile(((std::string)ApplicationPath + "Management.dll").c_str(), (TempHome + "Management.dll").c_str(), FALSE);
	CopyFile(((std::string)ApplicationPath + "Update.exe").c_str(), (TempHome + "Update.exe").c_str(), FALSE);

	/* Update.txt Path */
	WeteoesDll().Loading();
	std::string UpdateFile = TempHome + "Update.txt";
	// 删除原先文件
	WeteoesDll::IO_Remove((char*)UpdateFile.c_str());
	WeteoesDll::IO_WriteFile((char*)UpdateFile.c_str(), ApplicationPath, ApplicationPathLen);

	/* Run */
	WeteoesDll::CMD_Run((char*)((std::string)TempHome + "Update.exe").c_str());
}

// 设置开机自启
void CComputerApp::StartAtComputerOnStart() {
	// 创建文件夹
	std::string a = AppConfigClass::Get_TempPath() + "StartAtComputerOnStart\\"; 
	WeteoesDll::IO_CreatePath((char*)a.c_str());
	// 获取软件位置 
	HKEY hkey = WeteoesDll::Regedit_OpenRegFile(HKEY_LOCAL_MACHINE, (char*)"SOFTWARE\\Weteoes\\Computer");
	if (hkey == NULL) { MessageBox(NULL, "获取注册表失败", "", MB_OK); exit(0x30); }
	std::string reg_Path = WeteoesDll::Regedit_QueryRegValue(hkey, (char*)"Path", REG_SZ, false);
	std::string reg_Application = WeteoesDll::Regedit_QueryRegValue(hkey, (char*)"Application", REG_SZ, false);
	std::string softwarFile = reg_Path + reg_Application;
	// 创建配置XML
	std::string xml_TEMP_FileName = a + std::string("TEMP");
	std::string xml_TEMP = "<?xml version='1.0' encoding='UTF-16'?><Task version='1.2' xmlns='http://schemas.microsoft.com/windows/2004/02/mit/task'><Triggers><LogonTrigger><Enabled>true</Enabled></LogonTrigger></Triggers><Principals><Principal id='Author'><LogonType>InteractiveToken</LogonType><RunLevel>LeastPrivilege</RunLevel></Principal></Principals><Settings><MultipleInstancesPolicy>IgnoreNew</MultipleInstancesPolicy><DisallowStartIfOnBatteries>false</DisallowStartIfOnBatteries><StopIfGoingOnBatteries>true</StopIfGoingOnBatteries><AllowHardTerminate>false</AllowHardTerminate><StartWhenAvailable>false</StartWhenAvailable><RunOnlyIfNetworkAvailable>false</RunOnlyIfNetworkAvailable><IdleSettings><StopOnIdleEnd>true</StopOnIdleEnd><RestartOnIdle>false</RestartOnIdle></IdleSettings><AllowStartOnDemand>true</AllowStartOnDemand><Enabled>true</Enabled><Hidden>false</Hidden><RunOnlyIfIdle>false</RunOnlyIfIdle><WakeToRun>false</WakeToRun><ExecutionTimeLimit>PT0S</ExecutionTimeLimit><Priority>7</Priority></Settings><Actions Context='Author'><Exec><Command>\"" + softwarFile + "\"</Command></Exec></Actions></Task>";
	WeteoesDll::IO_Remove((char*)xml_TEMP_FileName.c_str());
	WeteoesDll::IO_WriteFile((char*)xml_TEMP_FileName.c_str(), (char*)xml_TEMP.c_str(), (int)xml_TEMP.length());
	// 创建启动任务
	std::string startName = "Computer Management";
	std::string runCmd = 
		"cmd /c "
		"(SCHTASKS /delete /tn \"" + startName + "\" /f || echo 0) && "
		"(SCHTASKS /Create /xml \"" + xml_TEMP_FileName + "\" /tn \"" + startName + "\" || echo 1)";
	WeteoesDll::CMD_Run((char*)runCmd.c_str());
}

// 通过PIPE重新启动
void CComputerApp::RestartAtPIPE() {
	// 服务存在,进行PIPE
	std::string data = "restart";
	LPCSTR pipe = TEXT("\\\\.\\Pipe\\Weteoes_Computer");
	BOOL bRet = WaitNamedPipe(pipe, NMPWAIT_WAIT_FOREVER);
	if (!bRet) { return; }
	HANDLE hPipe = CreateFile(			// 管道属于一种特殊的文件
		pipe,	// 创建的文件名
		GENERIC_READ | GENERIC_WRITE,	// 文件模式
		0,								// 是否共享
		NULL,							// 指向一个SECURITY_ATTRIBUTES结构的指针
		OPEN_EXISTING,					// 创建参数
		FILE_ATTRIBUTE_NORMAL,			// 文件属性(隐藏,只读)NORMAL为默认属性
		NULL							// 模板创建文件的句柄
	);
	if (INVALID_HANDLE_VALUE == hPipe) { return; }
	DWORD wlen = 0;
	WriteFile(hPipe, data.c_str(), (DWORD)data.length(), &wlen, 0); // 向服务器发送内容
	CloseHandle(hPipe); // 关闭管道
}

bool CComputerApp::OnlySoftware() {
	/* Management */
	std::string Software_Name = ManagementDll::Get("Software_Name") + string(".exe"); // 进程名
	std::string Software_Title = VariableClass::appConfigClass.Get_SoftwareTitle();
	if (Software_Name.empty() || Software_Title.empty()) {
		return true;
	}
	bool result = WeteoesDll::Process_SoftwareExist((char*)Software_Name.c_str(), (char*)Software_Title.c_str());
	if (result) { return false; }
	return true;
}

bool CComputerApp::Loading_Dll() {
	if (!WeteoesDll().Loading()) { return false; }
	if (!ConfigDll().Loading()) { return false; }
	if (!ManagementDll().Loading()) { return false; }
	if (!SRWDll().Loading()) { return false; }
	return true;
}

BOOL CComputerApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	//必须在SetRegistryKey之前
	Loading();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	// SetRegistryKey
	SetRegistryKey(_T("Weteoes"));

	initDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse;
	nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	 //删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

