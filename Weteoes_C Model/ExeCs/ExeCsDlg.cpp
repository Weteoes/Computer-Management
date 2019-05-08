
// ExeCsDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ExeCs.h"
#include "ExeCsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExeCsDlg 对话框



CExeCsDlg::CExeCsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXECS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExeCsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExeCsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CExeCsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CExeCsDlg 消息处理程序

BOOL CExeCsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CExeCsDlg::OnBnClickedOk();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExeCsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExeCsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


#include "Weteoes/Dll/WeteoesDll.h"
void CExeCsDlg::OnBnClickedOk()
{
	WeteoesDll().Loading();
	/* Basics */
	//std::string Basics_CharToUL1 = WeteoesDll::Basics_CharToUL("Aaasda**&&@#￥%@#￥sAdsad", true);
	//std::string Basics_CharToUL2 = WeteoesDll::Basics_CharToUL("Aaasda**&&@#￥%@#￥sAdsad", false);
	//std::string Basics_Replace = WeteoesDll::Basics_Replace("asdsad1234dfsdaf","1","2");
	//std::string Basics_GetNowFilePath = WeteoesDll::Basics_GetNowFilePath();
	//bool Basics_IsNum1 = WeteoesDll::Basics_IsNum("1");
	//bool Basics_IsNum2 = WeteoesDll::Basics_IsNum("true");

	/* Base64 */
	//std::string Base64_Encode = WeteoesDll::Base64_Encode("213123",6);
	//std::string Base64_UnEncode = WeteoesDll::Base64_UnEncode((char*)Base64_Encode.c_str(), (int)Base64_Encode.length());

	/* MD5 */
	//std::string MD5_MD5File1 = WeteoesDll::MD5_MD5File("E:\\Install\\.Net3.5_W8.1_x86_x64.exe");
	//std::string MD5_MD5File2 = WeteoesDll::MD5_MD5File("E:\\");

	/* HTTP */
	//std::string Http_HttpRequest1 = WeteoesDll::Http_HttpRequest("update.weteoes.cn", 443, "computer/update/", "post", NULL, 0);
	//std::string Http_HttpRequest2 = WeteoesDll::Http_HttpRequest("www.163.com", 80, "", "get", NULL, 0);

	/* Convert */
	//LPCUWSTR Convert_CharToLpcuwstr = WeteoesDll::Convert_CharToLpcuwstr("data12");
	//bool Convert_CharToBool1 = WeteoesDll::Convert_CharToBool("data12");
	//bool Convert_CharToBool2 = WeteoesDll::Convert_CharToBool("true");
	//bool Convert_CharToBool3 = WeteoesDll::Convert_CharToBool("false");
	//bool Convert_CharToBool4 = WeteoesDll::Convert_CharToBool("0");

	/* IO */
	//char *FilePath = "D:\\cs\\1.txt";
	//WeteoesDll::IO_CreatePath(FilePath);
	//WeteoesDll::IO_WriteFile(FilePath, "data");
	//bool IO_Exists = WeteoesDll::IO_Exists(FilePath);
	//std::string IO_ReadFile; if (IO_Exists) { IO_ReadFile = WeteoesDll::IO_ReadFile(FilePath); }
	//WeteoesDll::IO_Remove(FilePath);

	/* Regedit */
	//HKEY Regedit_CreateRegFile = WeteoesDll::Regedit_CreateRegFile(HKEY_LOCAL_MACHINE, "SOFTWARE\\Weteoes\\cs");
	//HKEY Regedit_OpenRegFile = WeteoesDll::Regedit_OpenRegFile(HKEY_LOCAL_MACHINE, "SOFTWARE\\Weteoes\\cs");
	//bool Regedit_CreateRegValue1 = WeteoesDll::Regedit_CreateRegValue(Regedit_CreateRegFile, "a", "1", REG_SZ, false); //REG_SZ所以不是数字
	//bool Regedit_CreateRegValue2 = WeteoesDll::Regedit_CreateRegValue(Regedit_CreateRegFile, "b", "b1", REG_SZ, false);
	//bool Regedit_CreateRegValue3 = WeteoesDll::Regedit_CreateRegValue(Regedit_CreateRegFile, "c", "1", REG_DWORD, false); //REG_DWORD是数字，错误示范
	//bool Regedit_CreateRegValue4 = WeteoesDll::Regedit_CreateRegValue(Regedit_CreateRegFile, "d", "1", REG_DWORD, true); //REG_DWORD是数字
	//std::string Regedit_QueryRegValue1 = WeteoesDll::Regedit_QueryRegValue(Regedit_CreateRegFile, "a", REG_SZ, false); //REG_SZ所以不是数字
	//std::string Regedit_QueryRegValue2 = WeteoesDll::Regedit_QueryRegValue(Regedit_CreateRegFile, "d", REG_DWORD, true); //REG_DWORD是数字
	//std::string Regedit_QueryRegValue3 = WeteoesDll::Regedit_QueryRegValue(Regedit_CreateRegFile, "d", REG_DWORD, false); //REG_DWORD是数字，错误示范
	//bool Regedit_QueryAddValue1 = WeteoesDll::Regedit_QueryAddValue(Regedit_CreateRegFile, "b", "-add", REG_SZ, true);  //REG_SZ不是数字，错误示范
	//bool Regedit_QueryAddValue2 = WeteoesDll::Regedit_QueryAddValue(Regedit_CreateRegFile, "b", "-add", REG_SZ, false);

	/* Process */
	std::string Process_AsUser = WeteoesDll::Process_AsUser("E:\\Tools\\WinNTSetup_3.8.7.0.exe", "WinNTSetup_3.8.7.0.exe"); //所有参数要对
	//int PGPFN;
	//int* Process_GetProcessidFromName = WeteoesDll::Process_GetProcessidFromName("cmd.exe", &PGPFN);
	//if (PGPFN == 0) { OutputDebugString("Process_GetProcessidFromName 不存在该进程"); }
	//else {
	//	for (int i = 0; i < PGPFN; i++) {
	//		std::string temp = "Process_GetProcessidFromName Process ID:" + std::to_string(Process_GetProcessidFromName[i]) + "\n";
	//		OutputDebugString(temp.c_str());
	//	}
	//}
	bool Process_SoftwareExist = WeteoesDll::Process_SoftwareExist("computer.exe", "Computer Management");

	/* CMD */
	//WeteoesDll::CMD_Run("rundll32.exe user32.dll LockWorkStation");

	CDialogEx::OnOK();
}
