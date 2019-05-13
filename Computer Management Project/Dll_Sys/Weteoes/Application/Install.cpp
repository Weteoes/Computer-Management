// App
#include <Application/Install.h>
#include <Application/Config.h>
#include <Application/Message.h>
#include <Application/Regedit.h>

// Dll
#include <Dll/Management.h>

// 安装
void InstallClass::Install() {
	if (!WeteoesDll().Loading()) { return; }
	if (!ManagementDll().Loading()) { return; }
	Service(); // 安装服务
}

// 安装服务
void InstallClass::Service() {
	// 目录
	std::string ApplicationPath = WeteoesDll::Basics_GetNowFilePath();
	std::string ServerDllPath = (std::string)ConfigClass::ConfigPath + "\\Sys\\";

	// 创建服务需要加空格，例如a= 1
	std::string a = "sc create " + ConfigClass::ServiceName + " binPath= \"" + ServerDllPath + " -k Weteoes -p -s Computer\" type= share";
	std::string b = "sc start " + ConfigClass::ServiceName;
	std::string c = "sc stop " + ConfigClass::ServiceName;
	std::string d = "sc delete " + ConfigClass::ServiceName;

	/* Stop Service */
	WeteoesDll::CMD_Run((char*)c.c_str());
	MessageClass::WriteFileLog("Stop Service OK");
	Sleep(300);

	/* Remove Service */
	WeteoesDll::CMD_Run((char*)d.c_str());
	MessageClass::WriteFileLog("Remove Service OK");
	Sleep(300);

	/* Copy File */
	WeteoesDll::IO_CreatePath((char*)ServerDllPath.c_str());

	CopyFile((ApplicationPath + "Sys.dll").c_str(), (ServerDllPath + "Sys.dll").c_str(), FALSE);
	CopyFile((ApplicationPath + "WeteoesDll.dll").c_str(), (ServerDllPath + "WeteoesDll.dll").c_str(), FALSE);
	CopyFile((ApplicationPath + "Management.dll").c_str(), (ServerDllPath + "Management.dll").c_str(), FALSE);
	MessageClass::WriteFileLog("Copy File OK");

	/* Install Service */
	WeteoesDll::CMD_Run((char*)a.c_str());
	MessageClass::WriteFileLog("Install Service OK");
	Sleep(300);

	/* Modify Service */
	Regedit(); // Regedit
	MessageClass::WriteFileLog("Modify Service OK");
	Sleep(300);

	/* Start Service */
	WeteoesDll::CMD_Run((char*)b.c_str());
	MessageClass::WriteFileLog("Start Service OK");
	MessageClass::WriteFileLog("----------------");
}

// Regedit
void InstallClass::Regedit()
{
	RegeditListLoading(); // 初始化RegeditList
	RegeditClass().CreateRegedit(MainPathArray);
}

// 初始化RegeditList
void InstallClass::RegeditListLoading() {
	static std::string ServicDll_ = ConfigClass::ConfigPath + "\\Sys\\Sys.dll";
	RegeditClass::RegeditMainArray Parameters({ (char*)"Parameters",{},{ { (char*)"ServiceDll", (char*)ServicDll_.c_str(),REG_EXPAND_SZ ,false,1 } } });

	static std::string SvchostName = "Weteoes_Computer";

	static std::string ImagePath_ = "%SystemRoot%\\System32\\svchost.exe -k " + SvchostName + " -p -s " + ConfigClass::ServiceName;
	RegeditClass::RegeditMainArray Service({ (char*)ConfigClass::ServiceName.c_str() ,{ Parameters },{
		{ (char*)"DisplayName",(char*)ConfigClass::ServiceName.c_str(),REG_SZ ,false,1 },
		{ (char*)"ErrorControl",(char*)"1",REG_DWORD ,true,1},
		{ (char*)"ImagePath",(char*)ImagePath_.c_str(),REG_EXPAND_SZ , false, 1 },
		{ (char*)"ObjectName",(char*)"LocalSystem",REG_SZ ,false, 1 },
		{ (char*)"Start",(char*)"2",REG_DWORD ,true ,1 },
		{ (char*)"Description",(char*)"Computer Management Running",REG_SZ, false, 1 }
		}
	});
	MainPathArray.push_back({ HKEY_LOCAL_MACHINE,(char*)"SYSTEM\\CurrentControlSet\\Services",{ Service } });

	RegeditClass::RegeditMainArray SvcHost({ (char*)SvchostName.c_str() ,{},{
		{ (char*)"AuthenticationCapabilities",(char*)"12320",REG_DWORD ,true ,1},
		{ (char*)"CoInitializeSecurityAllowComCapability",(char*)"1",REG_DWORD ,true ,1},
		{ (char*)"CoInitializeSecurityAllowInteractiveUsers",(char*)"1",REG_DWORD ,true,1 },
		{ (char*)"CoInitializeSecurityAllowLowBox",(char*)"1",REG_DWORD,true,1 },
		{ (char*)"CoInitializeSecurityParam",(char*)"1",REG_DWORD,true ,1},
		}
	});
	MainPathArray.push_back({ HKEY_LOCAL_MACHINE,(char*)"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Svchost",{ SvcHost }, {
		{(char*)SvchostName.c_str(),(char*)ConfigClass::ServiceName.c_str(),REG_MULTI_SZ, false, 1 }
	}});

	static std::string Software_Reg = "SOFTWARE\\Weteoes\\" + ConfigClass::ServiceName;
	ManagementDll().Loading();
	static std::string Application = WeteoesDll::Basics_GetNowFilePath() + std::string(ManagementDll::Get((char*)"Software_Name")) + ".exe";
	MainPathArray.push_back({ HKEY_LOCAL_MACHINE,(char*)Software_Reg.c_str(),{}, {
		{(char*)"Application",(char*)Application.c_str() ,REG_SZ, false, 1 }
	} });
}
