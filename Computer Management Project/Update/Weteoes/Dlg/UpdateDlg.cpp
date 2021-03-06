
// UpdateDlg.cpp: 实现文件
//

#include "../../stdafx.h"
#include "../../Update.h"
#include "afxdialogex.h"
#include <thread>
#include <Weteoes/Dlg/UpdateDlg.h>
#include <Weteoes/Application/AppConfig.h>
#include <Weteoes/Dll/WeteoesDll.h>
#include <Weteoes/Dll/ManagementDll.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUpdateDlg 对话框



CUpdateDlg::CUpdateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UPDATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUpdateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CUpdateDlg::OnPaint()
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
HCURSOR CUpdateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CUpdateDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1) { return -1; }
	return 0;
}

// CUpdateDlg 消息处理程序

BOOL CUpdateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Loading();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
CProgressCtrl* ProgressNow = (CProgressCtrl*)malloc(sizeof(CProgressCtrl)); //进度条
string ApplictionPath; //保存软件位置
void CUpdateDlg::Loading() { //初始化
	if (!WeteoesDll().Loading()) { exit(1); }

	ModifyStyle(m_hWnd, WS_THICKFRAME, 0, 0); //禁止变化大小
	ProgressNow = (CProgressCtrl*)GetDlgItem(UI_ProgressNow); //全局进度条
	ProgressNow->SetBarColor(RGB(48, 192, 73)); //进度条颜色

	/* 设置窗口标题(用于Dll获取主窗口句柄) Title */
	AfxGetMainWnd()->SetWindowText(AppConfigClass::SoftwareName.c_str());

	/* Download */
	LoadingDownload();
}
void CUpdateDlg::LoadingDownload() //Initialization Download
{
	DownloadLoading(this);
}
std::string CUpdateDlg::GetSavePath() {
	std::string result = WeteoesDll::Basics_GetNowFilePath(), //一开始为当前路径
		PD = result + std::string("Update.txt");
	if (WeteoesDll::IO_Exists((char*)PD.c_str())) {
		char* data;
		int dataLen = WeteoesDll::IO_ReadFile((char*)PD.c_str(), data);
		string a(data, dataLen);
		//WeteoesDll::IO_Remove((char*)PD.c_str()); //删除位置txt，防止二次使用
		WeteoesDll::IO_CreatePath((char*)a.c_str()); //防止文件夹不存在
		CString b = a.c_str();
		b.Replace("\n", "");
		result = b;
	}
	return result;
}
void CUpdateDlg::DownloadLoading(LPVOID _this) {
	/* 设置路径 */
	ApplictionPath = GetSavePath(); //保存软件位置
	WUpdateClass::ApplicationPath = ApplictionPath; //设置检查更新的文件路径

	/* 检查更新 */
	list<WUpdateClass::OnlyPathFile> DownloadFilesList; //保存下载文件列表
	bool result = WUpdateClass().DetectionUpdate(&DownloadFilesList);
	if (result == true) {
		//if (MessageBox("发现更新，是否需要立即更新", "", MB_YESNO) == IDNO) { //不需要更新
		//	Close(false); 
		//	return;
		//}
		//else { //需要更新
			std::string Software_Name = GetSoftwareName(), Software_Name_ = "computer"; //备用
			if (!Software_Name.empty()) { //Not Empty
				Software_Name_ = Software_Name;
			}
			std::string shell = "cmd.exe /c taskkill /F /IM " + Software_Name_ + ".exe";
			WeteoesDll::CMD_Run((char*)shell.c_str());
			Sleep(1000);
			
			/* Download Thread */
			std::thread DownloadThread(&CUpdateDlg::Download,this, DownloadFilesList, _this);
			DownloadThread.detach();
			//Download(DownloadFilesList, _this);
		//}
	}
	else { Close(false); }
}
void CUpdateDlg::Download(list<WUpdateClass::OnlyPathFile> FileList, LPVOID _this) {
	CUpdateDlg *__this = (CUpdateDlg*)malloc(sizeof(CUpdateDlg)); __this = (CUpdateDlg*)_this; //窗口句柄
	CProgressCtrl* ProgressNowTemp = (CProgressCtrl*)malloc(sizeof(CProgressCtrl)); ProgressNowTemp = ProgressNow; //进度条
	HWND StaticText = ::GetDlgItem(__this->m_hWnd, UI_DownloadMsg); //文本
	int now = 1; //当前更新位置
	for (list<WUpdateClass::OnlyPathFile>::const_iterator i = FileList.begin(); i != FileList.end(); i++)
	{									 
		WUpdateClass::OnlyPathFile Only = (WUpdateClass::OnlyPathFile)*i;
		char temp[512]; sprintf_s(temp, sizeof(temp), "Now Updateing is(%d/%d):%s", now, (int)FileList.size(), Only.FileName);
		::SetWindowText(StaticText, temp); //显示文字
		ProgressNowTemp->SetPos((int)((float)now/(float)FileList.size())*100); //进度条
		string down = ApplictionPath + string(Only.FileName);
		WeteoesDll::IO_CreatePath((char*)down.c_str());
		URLDownloadToFile(0, Only.FileDownload, down.c_str(), 0, 0);
		now++; //修改当前更新位置
	}
	//更新完毕
	Close(true);
}
void CUpdateDlg::Close(bool ReStart) {
	if (ReStart) {
		std::string Software_Name = GetSoftwareName();
		if (!Software_Name.empty()) { //Not Empty
			string a = GetSavePath() + Software_Name + ".exe";
			WinExec(a.c_str(), SW_SHOWMAXIMIZED);
		}
	}
	ExitProcess(0); //退出
}
std::string CUpdateDlg::GetSoftwareName() {
	if (ManagementDll().Loading()) { //success
		std::string Software_Name = ManagementDll::Get("Software_Name");
		if (!Software_Name.empty()) { //Not Empty
			return Software_Name;
		}
	}
	return "";
}