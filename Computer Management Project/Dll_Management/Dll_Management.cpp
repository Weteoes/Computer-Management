#include <Loading.h>

//App
#include <Application/Management.h>
#include <Application/Convert.h>

extern "C" _declspec(dllexport) char* Get(char* a) {
	std::string b = ManagementClass().Get(a);
	return ConvertClass().GetChars(b);
}