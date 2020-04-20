#include <pch.h>
#include "CEF_Login_V8Handler.h"

bool CEF_Login_V8Handler::Execute(
	const CefString& name, 
	CefRefPtr<CefDictionaryValue> arguments, 
	CefRefPtr<CefV8Value>& retval, 
	CefString& exception
	) {
	if (name == "Signin") {
		string w = arguments->GetString("w");
		bool result = false;
		// ‘ –Ìø’,ø’ ««Â≥˝≈‰÷√
		result = ConfigDll::Config_CreateUser(w.c_str());
		retval = CefV8Value::CreateBool(result);
		return true;
	} 
	else if (name == "ShowLoginDlg") {
		thread a(&CEF_Login_V8Handler::CreateLoginDlg, this);
		a.detach();
	}
	return false;
}

void CEF_Login_V8Handler::CreateLoginDlg() {
	VariableClass::createDlgClass.Login();
}
