#include <Weteoes/Loading.h>
#include <Weteoes/Dll/ManagementDll.h>

class ConfigClass
{
public:
	void Loading();
	static std::string ConfigPath; // 服务目录
	static std::string StartTime; // 启动时间
	static std::string ServiceName; // 服务名称
private:
	std::string loadingStartTime(); // 初始化启动时间
	std::string loadingServicePath(); // 初始化服务目录
};
