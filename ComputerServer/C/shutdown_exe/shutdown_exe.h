
// shutdown_exe.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif


// Cshutdown_exeApp: 
// �йش����ʵ�֣������ shutdown_exe.cpp
//

class Cshutdown_exeApp : public CWinApp
{
public:
	Cshutdown_exeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cshutdown_exeApp theApp;
