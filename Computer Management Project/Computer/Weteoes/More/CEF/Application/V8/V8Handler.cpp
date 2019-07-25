#include "V8Handler.h"
#include <Weteoes/Application/Dlg.h>
#include <Weteoes/Application/App.h>
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Dll/ConfigDll.h>

bool V8Handler_Class::Execute(
	const CefString& name,                        //JavaScript���õ�C++��������
	CefRefPtr<CefV8Value> object,                 //JavaScript�����߶���
	const CefV8ValueList& arguments,              //JavaScript���ݵĲ���
	CefRefPtr<CefV8Value>& retval,                //��Ҫ���ظ�JavaScript��ֵ���ø��������
	CefString& exception)                         //֪ͨ�쳣��Ϣ��JavaScript	
{
	if (name == "SystemMenu_Exit") { //�˳���ť
		DlgClass().Dlg_Close();
		return true;
	}
	else if (name == "SystemMenu_Mini") { //��С��
		DlgClass().Dlg_Mini();
		return true;
	}
	else if (name == "Login") { //��¼�ɹ�
		std::string w = arguments[0]->GetStringValue();
		ConfigDll().Loading();
		if (ConfigDll().Config_CreateUser((char*)w.c_str())) {
			AppClass().Login_Success();
		}
		else { //����ʧ��
			DlgClass().Dlg_Close();
		}
		return true;
	}
	if (AppConfigClass::IsLogin) { //����Ѿ���¼
		if (name == "Get_w") {
			ConfigDll().Loading();
			std::string w = ConfigDll::Config_ReadUser().w;
			retval = CefV8Value::CreateString(w);
			return true;
		}
		else if (name == "Set_Language") { //�޸ĵ�������
			std::string name = arguments[0]->GetStringValue();
			ConfigDll().Loading();
			ConfigDll::Config_SetComputer("Language", (char*)name.c_str());
			return true;
		}
		else if (name == "Get_ComputerName") { //�޸ĵ�������
			ConfigDll().Loading();
			std::string ComputerName = ConfigDll::Config_ReadComputer().ComputerName;
			retval = CefV8Value::CreateString(ComputerName);
			return true;
		}
		else if (name == "Set_ComputerName") { //�޸ĵ�������
			std::string name = arguments[0]->GetStringValue();
			ConfigDll().Loading();
			ConfigDll::Config_SetComputer("ComputerName", (char*)name.c_str());
			return true;
		}
		else if (name == "Get_Version") { //��ȡ�汾��
			std::string Version = AppConfigClass().Get_Version();
			retval = CefV8Value::CreateString(Version);
			return true;
		}
	}
	return false;
}