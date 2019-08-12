#ifndef ControlClass_H
#define ControlClass_H
#include <Weteoes/Loading.h>
class ControlClass
{
public:
	void Entrance(std::string);
private:
	void Start();
	void Stop();
};

#endif // !ControlClass_H

#ifndef ControlClass_CPP
#define ControlClass_CPP
#include <Weteoes/Dll/WeteoesDll.h>

void ControlClass::Entrance(std::string data) {
	if (ConfigClass::use.StrToLower(data) == ConfigClass::use.StrToLower("Start")) { Start(); }
	if (ConfigClass::use.StrToLower(data) == ConfigClass::use.StrToLower("Stop")) { Start(); }
}
void ControlClass::Start() {
	WeteoesDll::CMD_Run((char*)"sc start ComputerControl");
}
void ControlClass::Stop() {
	WeteoesDll::CMD_Run((char*)"sc stop ComputerControl");
}
#endif