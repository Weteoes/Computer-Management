#include <Weteoes/Loading.h>

class AppConfigClass
{
public:
	static bool IsLogin;				// 是否已登录
	static bool IsMiniStartMain;		// 启动Main时是否Mini启动
	static std::string SoftwareName;	// SoftwareName(通过Dll获取)
public:
	static std::string Get_Version();			// 获取版本
	static std::string Get_TempPath();			// 获取临时数据位置
};
