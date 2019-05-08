#ifdef RegeditClass_
#else
#define RegeditClass_
#include <Loading.h>

//App
#include <Application/Basics.h>

class RegeditClass
{
public:
	HKEY CreateRegFile(HKEY Key, char* FileName); //注册表创建子键
	bool CreateRegValue(HKEY Key, char* KeyName, char* KeyValue, DWORD KeyType, bool WriteIsNum); //注册表创建Value
	std::string QueryRegValue(HKEY Key, char* KeyName, DWORD KeyType, bool ReadIsNum); //注册表读取Value
	bool QueryAddValue(HKEY Key, char* KeyName, char* KeyValue, DWORD KeyType, bool ReadIsNum); //注册表追加Value
	HKEY OpenRegFile(HKEY MainPath, char* FileName); //注册表打开子键
};

HKEY RegeditClass::CreateRegFile(HKEY Key, char* FileName) { //创建子键
	HKEY a;
	DWORD b;
	if (RegCreateKeyEx(Key, FileName, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &a, &b) == ERROR_SUCCESS) { //创建成功
		return a;
	}
	return 0;
}
bool RegeditClass::CreateRegValue(HKEY Key, char* KeyName, char* KeyValue, DWORD KeyType, bool WriteIsNum) { //创建Value
	LPCSTR Name = KeyName;
	char* Value = (char*)KeyValue;
	int Value_i; //用于数字值
	if (WriteIsNum) {
		Value_i = atoi(KeyValue);
	}
	else { Value = (char*)_T(KeyValue); }

	DWORD Length = MAX_PATH;
	if (KeyType == REG_DWORD) {
		if (RegSetValueExA(Key, Name, 0, KeyType, (LPBYTE)&Value_i, 4) == ERROR_SUCCESS) {
			return true;
		}
		return false;
	}
	switch (KeyType)
	{
	case REG_BINARY:
		Length = 4;
		break;
	case REG_SZ:
		Length = lstrlenA(KeyValue);
		break;
	case REG_MULTI_SZ:
		Length = (int)strlen(KeyValue);
		break;
	}
	if (RegSetValueExA(Key, Name, 0, KeyType, (LPBYTE)Value, Length) == ERROR_SUCCESS) {
		return true;
	}
	return false;
}
std::string RegeditClass::QueryRegValue(HKEY Key, char* KeyName, DWORD KeyType, bool ReadIsNum) { //读取Value
	DWORD Size = sizeof(DWORD); //读取大小
	string result = "";
	RegQueryValueExA(Key, KeyName, 0, &KeyType, NULL, &Size); //获取长度
	if (Size == 0) { return result; }
	switch (KeyType)
	{
	case REG_BINARY:
		Size = 4;
		break;
	}
	if (ReadIsNum) {
		DWORD a;
		RegQueryValueExA(Key, KeyName, 0, &KeyType, (LPBYTE)&a, &Size);
		long Value = (long)a;
		result = to_string(Value);
	}
	else {
		LPTSTR a = (LPTSTR)malloc(Size);
		RegQueryValueExA(Key, KeyName, 0, &KeyType, (LPBYTE)a, &Size);
		string Value = "";
		for (; '\0' != *a; a += _tcslen(a)) {
			string i = a;
			if (KeyType == REG_MULTI_SZ) { i += "\n"; }
			Value += i;
		}
		result = Value;
	}
	return result;
}
bool RegeditClass::QueryAddValue(HKEY Key, char* KeyName, char* KeyValue, DWORD KeyType, bool ReadIsNum) { //追加Value
	string old = QueryRegValue(Key, KeyName, KeyType, ReadIsNum);
	if (ReadIsNum) {
		if (old.empty()) { old = "0"; }
		int old_i = atoi(old.c_str());
		int add_i = atoi(KeyValue);
		int new_i = old_i + add_i;
		if (CreateRegValue(Key, KeyName, (char*)to_string(new_i).c_str(), KeyType, ReadIsNum)) { return true; }
	}
	else {
		if (old.empty()) { old = ""; }
		string new_i = old + KeyValue;
		char* new_i_c = (char*)new_i.c_str();
		BasicsClass().Replace_C(&new_i_c, '\n', '\0');
		if (CreateRegValue(Key, KeyName, new_i_c, KeyType, ReadIsNum)) { return true; }
	}
	return false;
}
HKEY RegeditClass::OpenRegFile(HKEY MainPath, char* FileName) { //打开子键
	HKEY a;
	if (RegOpenKeyExA(MainPath, FileName, 0, KEY_ALL_ACCESS, &a) == ERROR_SUCCESS) { //是否有权限访问
		return a;
	}
	return 0;
}
#endif // RegeditClass_