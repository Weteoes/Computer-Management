 //WeteoesDll.cpp: 定义 DLL 应用程序的导出函数。

#include <Loading.h>

//App
#include <Application/Convert.h> //所有返回调用GetChars函数
#include <Application/Basics.h>
#include <Application/Base64.h>
#include <Application/MD5.h>
#include <Application/HTTP.h>
#include <Application/IO.h>
#include <Application/Regedit.h>
#include <Application/Process.h>
#include <Application/CMD.h>

#ifndef Basics
extern "C" _declspec(dllexport) char* Basics_GetNowFilePath() { //获取当前运行位置
	return BasicsClass().GetNowFilePath();
}
extern "C" _declspec(dllexport) char* Basics_Replace(char* str, char* oldChar, char* newChar) { //替换字符串
	return BasicsClass().Replace(str, oldChar, newChar);
}
extern "C" _declspec(dllexport) bool Basics_IsNum(char* str) { //判断是否是数字
	return BasicsClass().IsNum(str);
}
extern "C" _declspec(dllexport) char* Basics_CharToUL(char* c, bool ToUpper) { //Char*到大小写
	return BasicsClass().CharToUL(c, ToUpper);
}
#endif // !Basics

#ifndef Base64
extern "C" _declspec(dllexport) char* Base64_Encode(char* data, int length) { //Base64加密
	std::string a = string(data, length);
	std::string b = Base64Class().Encode((const unsigned char*)data, (int)a.length());
	char *result = ConvertClass().GetChars(b);
	return result;
}
extern "C" _declspec(dllexport) char* Base64_UnEncode(char* data, int length) { //Base64解密
	std::string a = string(data, length);
	std::string b = Base64Class().Decode((const char*)data, (int)a.length());
	char *result = ConvertClass().GetChars(b);
	return result;
}
#endif // !Base64

#ifndef MD5
extern "C" _declspec(dllexport) char* MD5_MD5File(char* file) { //文件MD5
	std::string a = MD5().MD5File(file);
	char *result = ConvertClass().GetChars(a);
	return result;
}
#endif // !MD5

#ifndef HTTP
extern "C" _declspec(dllexport) char* Http_HttpRequest(char* Url, short Port, char * lpUrl, char * Method, char * lpPostData, int nPostDataLen) { //HTTP访问
	return HTTPClass().HttpRequest(Url, Port, lpUrl, Method, lpPostData, nPostDataLen);
}
#endif // !HTTP

#ifndef Convert
extern "C" _declspec(dllexport) LPCUWSTR Convert_CharToLpcuwstr(char* text) {
	return ConvertClass().CharToLpcuwstr(text);
}
extern "C" _declspec(dllexport) bool Convert_CharToBool(char* text) {
	return ConvertClass().CharToBool(text);
}
#endif // !Convert

#ifndef IO
extern "C" _declspec(dllexport) void IO_WriteFile(char* file, char* data) {
	IOClass().WriteFile(file, data);
}
extern "C" _declspec(dllexport) char* IO_ReadFile(char* file) {
	return IOClass().ReadFile(file);
}
extern "C" _declspec(dllexport) void IO_CreatePath(char* file) {
	IOClass().CreatePath(file);
}
extern "C" _declspec(dllexport) bool IO_Exists(char* file) {
	return IOClass().Exists(file);
}
extern "C" _declspec(dllexport) void IO_Remove(char* file) {
	IOClass().Remove(file);
}
#endif // !IO

#ifndef Regedit
extern "C" _declspec(dllexport) HKEY Regedit_CreateRegFile(HKEY Key, char* FileName) { //注册表创建子键
	return RegeditClass().CreateRegFile(Key, FileName);
}
extern "C" _declspec(dllexport) bool Regedit_CreateRegValue(HKEY Key, char* KeyName, char* KeyValue, DWORD KeyType, bool WriteIsNum) { //注册表创建Value
	return RegeditClass().CreateRegValue(Key, KeyName, KeyValue, KeyType, WriteIsNum);
}
extern "C" _declspec(dllexport) char* Regedit_QueryRegValue(HKEY Key, char* KeyName, DWORD KeyType, bool ReadIsNum) { //注册表读取Value
	std::string a = RegeditClass().QueryRegValue(Key, KeyName, KeyType, ReadIsNum);
	char *result = ConvertClass().GetChars(a);
	return result;
}
extern "C" _declspec(dllexport) bool Regedit_QueryAddValue(HKEY Key, char* KeyName, char* KeyValue, DWORD KeyType, bool ReadIsNum) { //注册表追加Value
	return RegeditClass().QueryAddValue(Key, KeyName, KeyValue, KeyType, ReadIsNum);
}
extern "C" _declspec(dllexport) HKEY Regedit_OpenRegFile(HKEY MainPath, char* FileName) { //注册表打开子键
	return RegeditClass().OpenRegFile(MainPath, FileName);
}
#endif // !Regedit

#ifndef Process
extern "C" _declspec(dllexport) char* Process_AsUser(char* file, char* SoftwareName) { //通过管理员启动某程序(只有SYSTEM用户才能使用)
	return ProcessClass().AsUser(file, SoftwareName);
}
extern "C" _declspec(dllexport) int* Process_GetProcessidFromName(char* name, int* count) { //检查某进程是否存在
	return ProcessClass().GetProcessidFromName(name, count);
}
extern "C" _declspec(dllexport) bool Process_SoftwareExist(char* name, char* title) { //检查软件是否运行中(通过进程名和标题)
	return ProcessClass().SoftwareExist(name, title);
}
#endif // !Regedit
#ifndef CMD
extern "C" _declspec(dllexport) void CMD_Run(char* shell) { //运行CMD命令
	CMDClass().Run(shell);
}
#endif // !CMD

