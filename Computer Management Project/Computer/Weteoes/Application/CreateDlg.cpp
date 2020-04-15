#include "pch.h"
#include "CreateDlg.h"
#include <Weteoes/Dlg/Init_Dlg.h>
#include <Weteoes/Dlg/Dlg_Main.h>

void CreateDlgClass::main() {
	VariableClass::appDlgClass.Minimize();
	Dlg_Main a;
	a.configCEFUrl = VariableClass::appCefClass.GetUrl("/client/login");
	a.DoModal();
	//if (Dlg_Main::dlg_HWND != NULL) {
	//	// ÓÐ´°¿Ú
	//	VariableClass::dlg_CEF = Dlg_Main::dlg_CEF;
	//	VariableClass::dlg_HWND = Dlg_Main::dlg_HWND;
	//	VariableClass::appDlgClass.Show(true);
	//}
	//else {
	//	Dlg_Main a;
	//	a.DoModal();
	//}
}
