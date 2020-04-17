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
		if (!w.empty()) {
			result = ConfigDll::Config_CreateUser(w.c_str());
		}
		retval = CefV8Value::CreateBool(result);
		return true;
	} 
	else if (name == "createMainDlg") {
		thread a(&CEF_Login_V8Handler::createMainDlg, this);
		a.detach();
	}
	return false;
}

void CEF_Login_V8Handler::createMainDlg() {
	VariableClass::createDlgClass.main();
}