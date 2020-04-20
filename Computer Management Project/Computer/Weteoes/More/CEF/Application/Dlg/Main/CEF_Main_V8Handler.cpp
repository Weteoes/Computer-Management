#include <pch.h>
#include "CEF_Main_V8Handler.h"

bool CEF_Main_V8Handler::Execute(
	const CefString& name, 
	CefRefPtr<CefDictionaryValue> arguments, 
	CefRefPtr<CefV8Value>& retval, 
	CefString& exception
	) {
	if (name == "GetSession") {
		std::string w = ConfigDll::Config_ReadUser().w;
		retval = CefV8Value::CreateString(w);
		return true;
	}
	else if (name == "SetLanguage") { // 修改语言
		std::string type = arguments->GetString("type");
		if (!type.empty()) {
			ConfigDll::Config_SetComputer("Language", type.c_str());
		}
		return true;
	}
	else if (name == "GetComputerName") { // 获取电脑名称
		std::string ComputerName = ConfigDll::Config_ReadComputer().ComputerName;
		retval = CefV8Value::CreateString(ComputerName);
		return true;
	}
	else if (name == "SetComputerName") { // 修改电脑名称
		std::string name = arguments->GetString("name");
		ConfigDll::Config_SetComputer("ComputerName", name.c_str());
		return true;
	}
	else if (name == "GetVersion") { // 获取版本号
		std::string Version = AppConfigClass().Get_Version();
		retval = CefV8Value::CreateString(Version);
		return true;
	}
	else if (name == "ControlComputer") { // 远程控制
		std::string computerName = arguments->GetString("computerName");
		if (!computerName.empty()) {
			std::string control = WeteoesDll::Basics_GetNowFilePath() + std::string("Client.exe ComputerName=") + computerName;
			WeteoesDll::CMD_Run((char*)control.c_str());
		}
		return true;
	}
	else if (name == "CreateMainDlg") {
		thread a(&CEF_Main_V8Handler::CreateMainDlg, this);
		a.detach();
	}
	return false;
}

void CEF_Main_V8Handler::CreateMainDlg() {
	VariableClass::createDlgClass.Main();
}