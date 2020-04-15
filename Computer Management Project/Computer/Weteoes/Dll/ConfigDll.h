#ifdef ConfigDll_
#else
#define ConfigDll_
#include <Windows.h>

class ConfigDll
{
public:
	struct Struct_UserConfig {
		char w[256];
	};
	struct Struct_ComputerConfig {
		char ComputerName[256];
		char Language[10];
	};

private:
	typedef bool						(__stdcall* Config_CreateUser_)							(const char* user);
	typedef bool						(__stdcall* Config_CreateComputer_)						(const char* ComputerName, const char* Language);
	typedef Struct_UserConfig			(__stdcall* Config_ReadUser_)							();
	typedef Struct_ComputerConfig		(__stdcall* Config_ReadComputer_)						();
	typedef bool						(__stdcall* Config_SetComputer_)						(const char* element, const char* data);
	typedef bool						(__stdcall* Set_Variable_)								(const char* key, const char* value);

public:
	bool Loading();
	static Config_CreateUser_		Config_CreateUser;
	static Config_CreateComputer_	Config_CreateComputer;
	static Config_ReadUser_			Config_ReadUser;
	static Config_ReadComputer_		Config_ReadComputer;
	static Config_SetComputer_		Config_SetComputer;
	static Set_Variable_			Set_Variable;		// Dll全局变量保存

};
#endif

