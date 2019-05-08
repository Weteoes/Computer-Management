#include <Loading.h>
#include <More/CEF/include/cef_app.h>

class AppCefClass
{
public:
	static std::string Url; //CEF≥ı ºªØURL
public:
	CefSettings GetSetting();
	std::string GetUrl(std::string);
private:
	wchar_t* ToUnicode(char*);
};