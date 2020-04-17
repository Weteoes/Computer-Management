#include "pch.h"
#include "CreateDlg.h"
#include <Weteoes/Dlg/Init_Dlg.h>
#include <Weteoes/Dlg/Dlg_Main.h>
#include <resource.h>

void CreateDlgClass::browser(string url, bool minimize) {
	Dlg_Main a;
	a.configCEFUrl = url;
	if (minimize) {
		// Òþ±ÎÆô¶¯
		a.Create(IDD_Dlg_Main);
		a.ShowWindow(SW_HIDE);
		a.RunModalLoop();
	}
	else {
		a.DoModal();
	}
}

void CreateDlgClass::login() {
	VariableClass::appDlgClass.Minimize();
	string url = VariableClass::appCefClass.GetUrl("/computerManagement/ui/0/login");
	browser(url);
}

void CreateDlgClass::main(bool minimize) {
	VariableClass::appDlgClass.Minimize();
	VariableClass::appClass.LoginSuccess();
	ConfigDll::Struct_ComputerConfig a = ConfigDll::Config_ReadComputer();
	string url = VariableClass::appCefClass.GetUrl("/computerManagement/ui/0/main?Language=" + string(a.Language));
	browser(url, minimize);
}
