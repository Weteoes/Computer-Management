#include "Config.h"

char* ConfigClass::Socket_Header = (char*)"Weteoes";

std::string ConfigClass::GetConfig(std::string* data, std::string flag) {
	int a = (int)data->find(flag);
	if (a != -1) {
		std::string b = data->substr(0, a);
		std::string c = data->substr(b.length() + 1);
		*data = b;
		return c;
	}
	return "";
}

#include <algorithm>
std::string ConfigClass::StrToLower(std::string str)
{
	std::string strTmp = str;
	transform(strTmp.begin(), strTmp.end(), strTmp.begin(), tolower);
	return strTmp;
}