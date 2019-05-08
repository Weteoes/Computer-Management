#include <Loading.h>
#include <Windows.h>

class DlgClass {

public:
	static HWND Dlg_HWND;  //窗口句柄 线程相关
	static HINSTANCE Dlg_HINSTANCE;  //窗口句柄 内核相关

public:
	struct Dlg {
		int x, y;
		int width, height;
	};
private:
	static Dlg Dlg_; //记录窗口信息

public:
	void Dlg_Close(); //统一关闭窗口事件
	void Dlg_Mini(); //最小化窗口事件
	void Dlg_Show(bool = false); //显示窗口事件（窗口启动后也会调用），如果bool=true为窗口启动调用
	void Dlg_Icon_Add();  //添加托盘
	void Dlg_Icon_Remove(); //删除托盘
	void Dlg_SetNowRect(bool = false); //设置Dlg变量
	Dlg Dlg_GetRect(); //获取Dlg变量
};