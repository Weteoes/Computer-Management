#include <pch.h>
#include <Weteoes/Application/Dlg.h>
#include <Weteoes/Application/Icon.h>
#include <Weteoes/Application/AppConfig.h>
#include <atltypes.h>

HWND DlgClass::Dlg_HWND;
HINSTANCE DlgClass::Dlg_HINSTANCE;
DlgClass::Dlg DlgClass::Dlg_ = { 0,0,300,400 }; //记录窗口坐标

void DlgClass::Dlg_Close() { 
	Dlg_Icon_Remove();
	exit(0x40);
}
void DlgClass::Dlg_Mini() {
	if (!AppConfigClass::IsLogin) { //还没登陆
		ShowWindow(Dlg_HWND, SW_MINIMIZE);
	}
	else { //已经登录
		Dlg_SetNowRect(); //保存现在的窗口信息

		//移动窗口位置
		int nFullWidth = GetSystemMetrics(SM_CXSCREEN), //获取屏幕大小
			nFullHeight = GetSystemMetrics(SM_CYSCREEN);
		SetWindowPos(Dlg_HWND, NULL, nFullWidth, nFullHeight, 0, 0, SWP_NOSIZE);  //设置0像素,移到最角落,不然会存在阴影

		ShowWindow(Dlg_HWND, SW_HIDE);
	}
}
#include <Weteoes/Application/App.h>
void DlgClass::Dlg_Show(bool first) {
	if (!first) { //不是窗口创建后调用的
		if (!AppConfigClass::IsLogin) { //还没登陆
			ShowWindow(Dlg_HWND, SW_RESTORE);
		}
		else { //已经登录
			Dlg a = Dlg_GetRect(); //获取保存的窗口信息
			SetWindowPos(Dlg_HWND, NULL, a.x, a.y, 0, 0, SWP_NOSIZE);  //设置0像素,移到最角落
			ShowWindow(Dlg_HWND, SW_SHOW);
		}
	}
	else { //窗口创建后调用
		AppClass().Start_SRW(0); // 启动UI服务
	}
}
void DlgClass::Dlg_Icon_Add() {
	IconClass().Icon_Add(Dlg_HWND, Dlg_HINSTANCE); // 待修改
}
void DlgClass::Dlg_Icon_Remove() { 
	IconClass().Icon_Remove();
}
void DlgClass::Dlg_SetNowRect(bool SetWH) {
	CRect DlgCRect;
	GetWindowRect(Dlg_HWND, &DlgCRect); //获取在屏幕中的坐标
	Dlg_.x = DlgCRect.left;
	Dlg_.y = DlgCRect.top;
	if (SetWH) { //设置宽高
		Dlg_.width = DlgCRect.right - DlgCRect.left;
		Dlg_.height = DlgCRect.bottom - DlgCRect.top;
	}
}
DlgClass::Dlg DlgClass::Dlg_GetRect() {
	Dlg a;
	if (Dlg_.x == 0 || Dlg_.y == 0) { //不存在值
		int width = GetSystemMetrics(SM_CXSCREEN),
			height = GetSystemMetrics(SM_CYSCREEN); //获取屏幕分辨率
		a.x = (width - Dlg_.width) / 2;
		a.y = (height - Dlg_.height) / 2 - 20;
	}
	else {
		a.x = Dlg_.x;
		a.y = Dlg_.y;
	}
	Dlg_.width == 0 ? a.width = 300 : a.width = Dlg_.width;
	Dlg_.height == 0 ? a.height = 400 : a.height = Dlg_.height;
	return a;
}