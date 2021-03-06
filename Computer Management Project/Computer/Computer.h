
// Computer.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“pch.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CComputerApp:
// 有关此类的实现，请参阅 Computer.cpp
//

class CComputerApp : public CWinApp
{
public:
	CComputerApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现
private:
	void Loading();
	bool Loading_Dll();
	bool OnlySoftware(); // 判断重复启动

private:
	bool PdFirst();					// 判断是否第一次运行
	void PdUpdate();				// 判断是否有更新
	void RestartAtPIPE();			// 通过PIPE重新启动
	void StartAtComputerOnStart();	// 设置开机自启

public:
	void First_Init();				// 第一次运行初始化(其他窗口可以调用重新初始化)

	DECLARE_MESSAGE_MAP()
};

extern CComputerApp theApp;
