#pragma once

// Dlg_Main 对话框
class Dlg_Main : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_Main)

public:
	Dlg_Main(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dlg_Main();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_Main };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	HICON m_hIcon; //Icon
private:
	void loading();
	void loading_Dlg();
	void loading_CEF();
	void loading_SR();
public:
	virtual void OnCancel();
};
