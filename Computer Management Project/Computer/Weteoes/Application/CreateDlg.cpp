#include "pch.h"
#include "CreateDlg.h"
#include <Weteoes/Dlg/BrowserDlg.h>
#include <resource.h>

void CreateDlgClass::Browser(string url, bool minimize) {
	BrowserDlg a;
	a.configCEFUrl = url;
	if (minimize) {
		// Òþ±ÎÆô¶¯
		a.Create(IDD_Dlg_Browser);
		a.ShowWindow(SW_HIDE);
		a.RunModalLoop();
	}
	else {
		a.DoModal();
	}
}

void CreateDlgClass::Login() {
	VariableClass::appDlgClass.Minimize();
	string url = VariableClass::appCefClass.GetUrl("/computerManagement/ui/0/login");
	Browser(url);
}

void CreateDlgClass::Main(bool minimize) {
	VariableClass::appDlgClass.Minimize();
	VariableClass::appClass.LoginSuccess();
	ConfigDll::Struct_ComputerConfig a = ConfigDll::Config_ReadComputer();
	string url = VariableClass::appCefClass.GetUrl("/computerManagement/ui/0/main?Language=" + string(a.Language));
	Browser(url, minimize);
}
