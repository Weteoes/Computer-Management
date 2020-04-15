#include <pch.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/SRWDll.h>

bool Loading() {
	if (!WeteoesDll().Loading()) { return false; }
	if (!SRWDll().Loading()) { return false; }
	VariableClass::setVariable("AES_Password", "aisdjf213adhfkjs2dcawd55ni"); 
	return true;
}

extern "C" _declspec(dllexport) bool Config_CreateUser(const char* user) {
	if (!Loading()) { return false; }
	return VariableClass::createXMLConfigClass.UserConfig(user);
}

extern "C" _declspec(dllexport) bool Config_CreateComputer(const char* ComputerName, const char* Language) {
	if (!Loading()) { return false; }
	return VariableClass::createXMLConfigClass.ComputerConfig(ComputerName, Language);
}

extern "C" _declspec(dllexport) ReturnXMLStruct::UserConfig Config_ReadUser() {
	if (!Loading()) { return ReturnXMLStruct::userConfig; }
	return VariableClass::readXMLConfigClass.UserConfig();
}

extern "C" _declspec(dllexport) ReturnXMLStruct::ComputerConfig Config_ReadComputer() {
	if (!Loading()) { return ReturnXMLStruct::computerConfig; }
	return VariableClass::readXMLConfigClass.ComputerConfig();
}

extern "C" _declspec(dllexport) bool Config_SetComputer(const char* element, const char* data) {
	if (!Loading()) { return false; }
	return VariableClass::setXMLConfigClass.ComputerConfig(element, data);
}

extern "C" _declspec(dllexport) bool Set_Variable(const char* key, const char* value) {
	if (!Loading()) { return false; }
	VariableClass::setVariable(key, value);
	return true;
}