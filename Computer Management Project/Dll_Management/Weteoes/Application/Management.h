#ifdef ManagementClass_
#else
#define ManagementClass_
#include <Loading.h>

class ManagementClass
{
public:
	std::string Get(char*);
private:
	std::string servicePath(); // ����װĿ¼
};
#endif //ManagementClass_