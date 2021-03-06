#pragma once
#ifndef AppDlgClass_H
#define AppDlgClass_H
class AppDlgClass {

public:
	void Exit(); // 退出程序
	void Close(); // 关闭窗口
	void Minimize(); // 最小化窗口
	void Show(bool moveCenter = false); // 显示窗口
	void SetSize(int width, int height); // 设置窗口大小
	void MoveCenter(); // 移动窗口到中间

private:
	HWND dlg_HWND;

private:
	//记录窗口信息
	void Dlg_SetNowRect(bool = false); // 设置Dlg变量
	struct Dlg {
		int x, y;
		int width, height;
	};
	static Dlg Dlg_;
	AppDlgClass::Dlg Dlg_GetRect();  // 获取Dlg记录
};
#endif