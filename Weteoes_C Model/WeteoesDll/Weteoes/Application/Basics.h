#ifdef BasicsClass_
#else
#define BasicsClass_
#include <Loading.h>

//App
#include <Application/Convert.h>

class BasicsClass {
public:
	char* Replace(char* str, char* oldChar, char* newChar); //替换字符串
	void Replace_C(char** str, char oldChar, char newChar); //替换字符串 char(Only)
	bool IsNum(char* str); //判断是否是数字
	char* GetNowFilePath(); //获取当前文件位置
	char* CharToUL(char*, bool); //Char*到大小写
};
void BasicsClass::Replace_C(char** str, char oldChar, char newChar)
{
	char *str_ = *str;
	int a = (int)strlen(str_);
	for (int i = 0; i < a; i++) {
		if (str_[i] == oldChar) {
			str_[i] = newChar;
		}
	}
}
char* BasicsClass::Replace(char* str, char* oldChar, char* newChar)
{
	std::string a = str, SoldChar = oldChar, SnewChar;
	if (newChar == NULL) { SnewChar = std::string("\0", 1); }
	else { SnewChar = newChar; }
	std::string::size_type nPos = 0;
	std::string::size_type nsrclen = SoldChar.size();
	std::string::size_type ndstlen = SnewChar.size();
	while (nPos = a.find(oldChar, nPos))
	{
		if (nPos == std::string::npos) { break; }
		a.replace(nPos, nsrclen, SnewChar);
		nPos += ndstlen;
	}
	char *result = ConvertClass().GetChars(a);
	return result;
}
#include <sstream>
bool BasicsClass::IsNum(char* str) {
	std::stringstream sin(str);
	double d;
	char c;
	if (!(sin >> d)) { return false; }
	if (sin >> c) { return false; }
	return true;
}
#include <atlstr.h> 
char* BasicsClass::GetNowFilePath() {
	LPSTR b = (LPSTR)malloc(sizeof(LPSTR) * MAX_PATH);
	HMODULE a = _AtlBaseModule.GetModuleInstance();
	GetModuleFileName(a, b, MAX_PATH);
	std::string c = b;
	c = c.substr(0, c.find_last_of("\\")) + "\\";
	char *result = ConvertClass().GetChars(c);
	return result;
}
char* BasicsClass::CharToUL(char *s, bool ToUpper) {
	char* result = s;
	int len = (int)strlen(result);
	for (int i = 0; i < len; i++) {
		if (ToUpper) { result[i] = toupper(result[i]); }
		else { result[i] = tolower(result[i]); }
	}
	return result;
}
#endif