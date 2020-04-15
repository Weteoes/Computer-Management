#include <pch.h>
#include "CEF_Init_V8Handler.h"

bool CEF_Init_V8Handler::Execute(
	const CefString& name,                        //JavaScript���õ�C++��������
	CefRefPtr<CefDictionaryValue> arguments,              //JavaScript���ݵĲ���
	CefRefPtr<CefV8Value>& retval,                //��Ҫ���ظ�JavaScript��ֵ���ø��������
	CefString& exception)                         //֪ͨ�쳣��Ϣ��JavaScript	
{
	if (name == "ShowMainDlg") {
		std::thread a(&CEF_Init_V8Handler::ShowMainDlg, this); a.detach(); //Create Thread
		return true;
	}
	return false;
}

void CEF_Init_V8Handler::ShowMainDlg() {
	VariableClass::createDlgClass.main();
}