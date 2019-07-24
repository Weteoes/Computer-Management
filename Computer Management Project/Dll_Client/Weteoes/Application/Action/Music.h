#ifndef Music_Basics
#include <Weteoes/Loading.h>
class Music_Basics {
public:
	void play();
	void last();
	void next();
};
void Music_Basics::play() {
	keybd_event(179, 0, 0, 0);
	keybd_event(179, 0, 2, 0);
}
void Music_Basics::last() {
	keybd_event(177, 0, 0, 0);
	keybd_event(177, 0, 2, 0);
}
void Music_Basics::next() {
	keybd_event(176, 0, 0, 0);
	keybd_event(176, 0, 2, 0);
}
#endif // !Music_Basics

#ifndef Music_163
class Music_163 {
public:
	void GetHandle(); //获取句柄
	bool Loading(); //初始化
	void play();
	void last();
	void next();
	void like();
};
HWND Music_163_Window; //窗口句柄
BOOL GetHandleMain(HWND hwnd, LPARAM lParam) { //获取子窗口句柄
	char *ClassName = (char*)malloc(sizeof(char) * MAX_CLASS_NAME); //创建变量
	GetClassName(hwnd, ClassName, MAXCHAR); //获取ClassName
	std::string ClassNameS = ClassName; //转为std::string类型
	if (ClassNameS == "Chrome_RenderWidgetHostHWND") {
		Music_163_Window = hwnd; //保存句柄
	}
	return true;
}
void Music_163::GetHandle() {
	HWND a = FindWindow("OrpheusBrowserHost", NULL); //获取句柄
	EnumChildWindows(a, &GetHandleMain, 0); //获取子窗口句柄
}
bool Music_163::Loading() {
	GetHandle();
	if (!Music_163_Window) { return false; }
	return true;
}
void Music_163::play() {
	if (!Loading()) { return; };
	RECT a; GetWindowRect(Music_163_Window, &a); //获取窗口上下左右
	int height = a.bottom - a.top, width = a.right - a.left; //计算出窗口大小
	UINT x = 100, y = (UINT)height - 15; //点击位置
	UINT xy = (y << 16) | x; //算出值
	PostMessage(Music_163_Window, WM_LBUTTONDOWN, 0, xy);
	PostMessage(Music_163_Window, WM_LBUTTONUP, 0, xy);
}
void Music_163::last() {
	if (!Loading()) { return; };
	RECT a; GetWindowRect(Music_163_Window, &a); //获取窗口上下左右
	int height = a.bottom - a.top, width = a.right - a.left; //计算出窗口大小
	UINT x = 43, y = (UINT)height - 15; //点击位置
	UINT xy = (y << 16) | x; //算出值
	PostMessage(Music_163_Window, WM_LBUTTONDOWN, 0, xy);
	PostMessage(Music_163_Window, WM_LBUTTONUP, 0, xy);
}
void Music_163::next() {
	if (!Loading()) { return; };
	RECT a; GetWindowRect(Music_163_Window, &a); //获取窗口上下左右
	int height = a.bottom - a.top, width = a.right - a.left; //计算出窗口大小
	UINT x = 155, y = (UINT)height - 15; //点击位置
	UINT xy = (y << 16) | x; //算出值
	PostMessage(Music_163_Window, WM_LBUTTONDOWN, 0, xy);
	PostMessage(Music_163_Window, WM_LBUTTONUP, 0, xy);
}
void Music_163::like() {
	if (!Loading()) { return; };
	RECT a; GetWindowRect(Music_163_Window, &a); //获取窗口上下左右
	int height = a.bottom - a.top, width = a.right - a.left; //计算出窗口大小
	UINT x = 180, y = (UINT)height - 88; //点击位置
	UINT xy = (y << 16) | x; //算出值
	PostMessage(Music_163_Window, WM_LBUTTONDOWN, 0, xy);
	PostMessage(Music_163_Window, WM_LBUTTONUP, 0, xy);
}
#endif // !Music_163

#ifndef MusicClass_H
#define MusicClass_H
class MusicClass {
public:
	void Entrance(std::string); //入口
	int GetAction(std::string); //获取动作
};
#endif

#ifndef MusicClass_CPP
#define MusicClass_CPP

void MusicClass::Entrance(std::string data) { //163|F5
	std::string app = ConfigClass::use.GetConfig(&data, "|");
	if (app.empty()) { return; } //如果为空则退出
	int Action = GetAction(data); //获取动作
	if (Action == -1) { return; } //不存在的动作，退出
	if (ConfigClass::use.StrToLower(app) == ConfigClass::use.StrToLower("163")) {
		Music_163 a;
		switch (Action)
		{
		case 0: a.play(); break;
		case 1: a.last(); break;
		case 2: a.next(); break;
		case 3: a.like(); break;
		default: break;
		}
	}
	else {
		Music_Basics a;
		switch (Action)
		{
		case 0: a.play(); break;
		case 1: a.last(); break;
		case 2: a.next(); break;
		default: break;
		}
	}
}

int MusicClass::GetAction(std::string data) {
	if (ConfigClass::use.StrToLower(data) == ConfigClass::use.StrToLower("P")) { return 0; }
	else if (ConfigClass::use.StrToLower(data) == ConfigClass::use.StrToLower("S")) { return 1; }
	else if (ConfigClass::use.StrToLower(data) == ConfigClass::use.StrToLower("N")) { return 2; }
	else if (ConfigClass::use.StrToLower(data) == ConfigClass::use.StrToLower("Like")) { return 3; }
	else { return -1; }
}
#endif