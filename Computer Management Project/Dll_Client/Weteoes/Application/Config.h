#ifndef ConfigClass__
#define ConfigClass__
#include <Loading.h>

class ConfigClass
{
public:
	static char* Socket_Header; //Socket Header String
public:
	std::string GetConfig(std::string*, std::string = "_"); //��ȡ����(�������ã���ȥԴ����)
	std::string StrToLower(std::string); //String��Сд

};
#endif // ConfigClass__