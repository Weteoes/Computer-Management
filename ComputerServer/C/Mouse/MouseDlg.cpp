
// MouseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Mouse.h"
#include "MouseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMouseDlg 对话框



CMouseDlg::CMouseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MOUSE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMouseDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Start, &CMouseDlg::OnBnClickedStart)
	ON_LBN_DBLCLK(IDC_LIST1, &CMouseDlg::OnLbnDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON_Start_two, &CMouseDlg::OnBnClickedButtonStarttwo)
END_MESSAGE_MAP()


// CMouseDlg 消息处理程序

BOOL CMouseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMouseDlg::OnPaint()
{
	Loading();
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		//使图标在工作区矩形中居中
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
HCURSOR CMouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#include <string>
//Weteoes.h
LPCUWSTR Get_LPCUWSTR(std::string text, int ch = 0);

BOOL Time_xy_start = false;
DWORD WINAPI Time_xy(LPVOID lpParamter) {
	CListBox* list = (CListBox*)lpParamter;
	while (Time_xy_start) {
		POINT a;
		GetCursorPos(&a);
		std::string text = "当前鼠标坐标212 x:" + std::to_string(a.x) + " y:" + std::to_string(a.y);
		list->AddString(Get_LPCUWSTR(text, 6));
		list->SetCurSel(list->GetCount() - 1);
		Sleep(1000);
	}
	return 0;
}
void CMouseDlg::OnBnClickedStart()
{
	if (!Time_xy_start) {
		Time_xy_start = true;
		CListBox* a = (CListBox*)GetDlgItem(IDC_LIST1);
		if (a->GetCount() > 0) {
			if (MessageBox(_T("清空历史坐标数据"), _T(""), MB_YESNO) == IDYES) {
				a->ResetContent();
			}
		};
		CreateThread(NULL, 0, Time_xy, a, 0, NULL);
		CButton* b = (CButton*)GetDlgItem(IDC_Start);
		b->SetWindowText(_T("暂停"));
	}
	else {
		Stop_xy();
	}
}
void CMouseDlg::Stop_xy() {
	Time_xy_start = false;
	CButton* b = (CButton*)GetDlgItem(IDC_Start);
	b->SetWindowText(_T("捕捉鼠标坐标"));
}
std::string GetText(std::string text, std::string a) {
	std::string b = text.substr(text.find(a) + a.length());
	std::string c = b.substr(0, b.find(" "));
	return c;
}
void CMouseDlg::Loading() {
	CEdit* xy_int = (CEdit*)GetDlgItem(IDC_EDIT_int);
	CEdit* xy_yanchi = (CEdit*)GetDlgItem(IDC_EDIT_yanchi);
	xy_int->SetWindowText(_T("1"));
	xy_yanchi->SetWindowText(_T("100"));
}
void CMouseDlg::OnLbnDblclkList1()
{
	Stop_xy();
	CEdit* x = (CEdit*)GetDlgItem(IDC_EDIT1);
	CEdit* y = (CEdit*)GetDlgItem(IDC_EDIT2);
	CListBox* a = (CListBox*)GetDlgItem(IDC_LIST1);
	CString b;
	a->GetText(a->GetCurSel(), b);
	std::string c = CT2A(b.GetBuffer());
	std::string c_x = GetText(c, "x:"), c_y = GetText(c, "y:");
	x->SetWindowText(Get_LPCUWSTR(c_x));
	y->SetWindowText(Get_LPCUWSTR(c_y));
}

int Get_Windows(std::string a) {
	HDC hDC = ::GetDC(HWND(NULL));                 // 得到屏幕DC  
	int pm_x = ::GetDeviceCaps(hDC, HORZRES);      // 屏幕宽  
	int pm_y = ::GetDeviceCaps(hDC, VERTRES);      // 屏幕高   
	::ReleaseDC(HWND(NULL), hDC);                  // 释放DC
	if (a._Equal("x"))
		return pm_x;
	else if (a._Equal("y"))
		return pm_y;
	return 0;
}


void CMouseDlg::OnBnClickedButtonStarttwo()
{
	Stop_xy();
	CEdit* x = (CEdit*)GetDlgItem(IDC_EDIT1);
	CEdit* y = (CEdit*)GetDlgItem(IDC_EDIT2);
	CEdit* xy_int = (CEdit*)GetDlgItem(IDC_EDIT_int);
	CEdit* xy_yanchi = (CEdit*)GetDlgItem(IDC_EDIT_yanchi);
	CString W_x, W_y, W_int, W_yanchi;
	x->GetWindowText(W_x);
	y->GetWindowText(W_y);
	xy_int->GetWindowText(W_int);
	xy_yanchi->GetWindowText(W_yanchi);
	std::string a_x = CT2A(W_x.GetBuffer()), a_y = CT2A(W_y.GetBuffer()), a_int = CT2A(W_int.GetBuffer()), a_yanchi = CT2A(W_yanchi.GetBuffer());
	if (a_x == "" || a_y == "" || a_int == "" || a_yanchi == "") {
		MessageBox(_T("数据不能为空"), _T(""), MB_OK);
		return;
	}
	int b_x, b_y, b_int, b_yanchi;
	try {
		b_x = std::stoi(a_x), b_y = std::stoi(a_y), b_int = std::stoi(a_int), b_yanchi = std::stoi(a_yanchi);
	}
	catch (std::exception) {
		MessageBox(_T("数据有误"), _T(""), MB_OK);
		return;
	}
	SetCursorPos(b_x, b_y);
	for (int i = 0; i < b_int; i++) {
		mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, NULL);
		Sleep(b_yanchi);
	}
}
