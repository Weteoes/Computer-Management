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
	void GetHandle(); //��ȡ���
	bool Loading(); //��ʼ��
	void play();
	void last();
	void next();
	void like();
};
HWND Music_163_Window; //���ھ��
BOOL GetHandleMain(HWND hwnd, LPARAM lParam) { //��ȡ�Ӵ��ھ��
	char *ClassName = (char*)malloc(sizeof(char) * MAX_CLASS_NAME); //��������
	GetClassName(hwnd, ClassName, MAXCHAR); //��ȡClassName
	std::string ClassNameS = ClassName; //תΪstd::string����
	if (ClassNameS == "Chrome_RenderWidgetHostHWND") {
		Music_163_Window = hwnd; //������
	}
	return true;
}
void Music_163::GetHandle() {
	HWND a = FindWindow("OrpheusBrowserHost", NULL); //��ȡ���
	EnumChildWindows(a, &GetHandleMain, 0); //��ȡ�Ӵ��ھ��
}
bool Music_163::Loading() {
	GetHandle();
	if (!Music_163_Window) { return false; }
	return true;
}
void Music_163::play() {
	if (!Loading()) { return; };
	RECT a; GetWindowRect(Music_163_Window, &a); //��ȡ������������
	int height = a.bottom - a.top, width = a.right - a.left; //��������ڴ�С
	UINT x = 100, y = (UINT)height - 15; //���λ��
	UINT xy = (y << 16) | x; //���ֵ
	PostMessage(Music_163_Window, WM_LBUTTONDOWN, 0, xy);
	PostMessage(Music_163_Window, WM_LBUTTONUP, 0, xy);
}
void Music_163::last() {
	if (!Loading()) { return; };
	RECT a; GetWindowRect(Music_163_Window, &a); //��ȡ������������
	int height = a.bottom - a.top, width = a.right - a.left; //��������ڴ�С
	UINT x = 43, y = (UINT)height - 15; //���λ��
	UINT xy = (y << 16) | x; //���ֵ
	PostMessage(Music_163_Window, WM_LBUTTONDOWN, 0, xy);
	PostMessage(Music_163_Window, WM_LBUTTONUP, 0, xy);
}
void Music_163::next() {
	if (!Loading()) { return; };
	RECT a; GetWindowRect(Music_163_Window, &a); //��ȡ������������
	int height = a.bottom - a.top, width = a.right - a.left; //��������ڴ�С
	UINT x = 155, y = (UINT)height - 15; //���λ��
	UINT xy = (y << 16) | x; //���ֵ
	PostMessage(Music_163_Window, WM_LBUTTONDOWN, 0, xy);
	PostMessage(Music_163_Window, WM_LBUTTONUP, 0, xy);
}
void Music_163::like() {
	if (!Loading()) { return; };
	RECT a; GetWindowRect(Music_163_Window, &a); //��ȡ������������
	int height = a.bottom - a.top, width = a.right - a.left; //��������ڴ�С
	UINT x = 180, y = (UINT)height - 88; //���λ��
	UINT xy = (y << 16) | x; //���ֵ
	PostMessage(Music_163_Window, WM_LBUTTONDOWN, 0, xy);
	PostMessage(Music_163_Window, WM_LBUTTONUP, 0, xy);
}
#endif // !Music_163

#ifndef MusicClass_H
#define MusicClass_H
class MusicClass {
public:
	void Entrance(std::string); //���
	int GetAction(std::string); //��ȡ����
};
#endif

#ifndef MusicClass_CPP
#define MusicClass_CPP

void MusicClass::Entrance(std::string data) { //163|F5
	std::string app = ConfigClass::use.GetConfig(&data, "|");
	if (app.empty()) { return; } //���Ϊ�����˳�
	int Action = GetAction(data); //��ȡ����
	if (Action == -1) { return; } //�����ڵĶ������˳�
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