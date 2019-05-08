#ifdef ConvertClass_
#else
#define ConvertClass_
#include <Windows.h>
#include <Loading.h>
#include <sstream>

class ConvertClass
{
public:
	LPCUWSTR CharToLpcuwstr(char* text);
	bool CharToBool(char* text);
	char* GetChars(std::string); //std::string to char*
private:
	void ConvertError(std::string error);
};

LPCUWSTR ConvertClass::CharToLpcuwstr(char* text) {
	try {
		size_t size = strlen(text);
		wchar_t *buffer = new wchar_t[size + 1];
		MultiByteToWideChar(CP_ACP, 0, text, (int)size, buffer, (int)size * sizeof(wchar_t));
		buffer[size] = 0;
		return buffer;
	}
	catch (std::string error) {
		std::string errorData = "Error:ConvertClass::StringToLpcuwstr \n" + error;
		ConvertError(errorData);
		return NULL;
	}
}
bool ConvertClass::CharToBool(char* text) {
	try {
		bool a;
		std::istringstream(text) >> a;
		return a;
	}
	catch (std::string error) {
		std::string errorData = "Error:ConvertClass::ToString \n" + error;
		ConvertError(errorData);
		return NULL;
	}
}
char* ConvertClass::GetChars(std::string data_s) { //std::string to char* 不能public因为std::string
	int len = (int)data_s.length();
	char *result = (char*)malloc(sizeof(char) * len + 1);
	for (int i = 0; i < len; i++) {
		result[i] = data_s[i];
	}
	result[len] = '\0';
	return result;
}
void ConvertClass::ConvertError(std::string error) {

}
#endif // ConvertClass_