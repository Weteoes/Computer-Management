#pragma once
#ifndef VariableClass_H
#define VariableClass_H

#include <Weteoes/Application/Config.h>
#include <Weteoes/Application/Security/RSA.h>
#include <Weteoes/Application/Security/SecurityAES.h>
#include <Weteoes/Application/Web/WebBasic.h>

class VariableClass {
public:
	static ConfigClass configClass;
	static RSAClass rsaClass;
	static ConfigDll configDll;
	static WebBasicClass webBasicClass;
	static SecurityAESClass securityAESClass;

private:
	static map<string, string> variable_map;
public: 
	static string getVariable(string key);
	static bool setVariable(string key, string value);
};
#endif