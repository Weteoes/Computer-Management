#ifdef ManagementClass_
#else
#define ManagementClass_
#include <Loading.h>

class ManagementClass
{
public:
	std::string Get(char*);
private:
	std::string servicePath(); // 服务安装目录
};
#endif //ManagementClass_