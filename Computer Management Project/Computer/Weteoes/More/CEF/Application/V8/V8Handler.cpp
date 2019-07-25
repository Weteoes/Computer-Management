#include "V8Handler.h"
#include <Weteoes/Application/Dlg.h>
#include <Weteoes/Application/App.h>
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Dll/ConfigDll.h>

bool V8Handler_Class::Execute(
	const CefString& name,                        //JavaScript调用的C++方法名字
	CefRefPtr<CefV8Value> object,                 //JavaScript调用者对象
	const CefV8ValueList& arguments,              //JavaScript传递的参数
	CefRefPtr<CefV8Value>& retval,                //需要返回给JavaScript的值设置给这个对象
	CefString& exception)                         //通知异常信息给JavaScript	
{
	if (name == "SystemMenu_Exit") { //退出按钮
		DlgClass().Dlg_Close();
		return true;
	}
	else if (name == "SystemMenu_Mini") { //最小化
		DlgClass().Dlg_Mini();
		return true;
	}
	else if (name == "Login") { //登录成功
		std::string w = arguments[0]->GetStringValue();
		ConfigDll().Loading();
		if (ConfigDll().Config_CreateUser((char*)w.c_str())) {
			AppClass().Login_Success();
		}
		else { //保存失败
			DlgClass().Dlg_Close();
		}
		return true;
	}
	if (AppConfigClass::IsLogin) { //如果已经登录
		if (name == "Get_w") {
			ConfigDll().Loading();
			std::string w = ConfigDll::Config_ReadUser().w;
			retval = CefV8Value::CreateString(w);
			return true;
		}
		else if (name == "Set_Language") { //修改电脑名称
			std::string name = arguments[0]->GetStringValue();
			ConfigDll().Loading();
			ConfigDll::Config_SetComputer("Language", (char*)name.c_str());
			return true;
		}
		else if (name == "Get_ComputerName") { //修改电脑名称
			ConfigDll().Loading();
			std::string ComputerName = ConfigDll::Config_ReadComputer().ComputerName;
			retval = CefV8Value::CreateString(ComputerName);
			return true;
		}
		else if (name == "Set_ComputerName") { //修改电脑名称
			std::string name = arguments[0]->GetStringValue();
			ConfigDll().Loading();
			ConfigDll::Config_SetComputer("ComputerName", (char*)name.c_str());
			return true;
		}
		else if (name == "Get_Version") { //获取版本号
			std::string Version = AppConfigClass().Get_Version();
			retval = CefV8Value::CreateString(Version);
			return true;
		}
	}
	return false;
}