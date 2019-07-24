#ifndef ControlClass_H
#define ControlClass_H
#include <Weteoes/Loading.h>
class ControlClass
{
public:
	void Entrance(std::string);
private:
	void Login(std::string);
};

#endif // !ControlClass_H

#ifndef ControlClass_CPP
#define ControlClass_CPP
void ControlClass::Entrance(std::string data) {
	std::string shell = ConfigClass::use.GetConfig(&data);
	if (ConfigClass::use.StrToLower(shell) == ConfigClass::use.StrToLower("Login")) { Login(data); }
}
void ControlClass::Login(std::string data) {
	std::string user = ConfigClass::use.GetConfig(&data, "|");
	std::string pass = data;
}
#endif