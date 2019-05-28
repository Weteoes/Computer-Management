#ifndef ConfigClass__
#define ConfigClass__
#include <Loading.h>

class ConfigClass
{
public:
	static char* Socket_Header; //Socket Header String
public:
	std::string GetConfig(std::string*, std::string = "_"); //获取配置(返回配置，减去源内容)
	std::string StrToLower(std::string); //String到小写

};
#endif // ConfigClass__