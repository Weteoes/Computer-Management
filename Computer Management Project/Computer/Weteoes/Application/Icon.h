#ifndef IconClass_
#define IconClass_
#include <Loading.h>
#include <Windows.h>
#define WM_IconMsg (WM_USER + 101)

class IconClass
{
public:
	static NOTIFYICONDATA m_NotifyIcon;

	bool Icon_Add(HWND, HINSTANCE);
	void Icon_Remove();
};
#endif // !IconClass_