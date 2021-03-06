#include <Weteoes/Loading.h>
#include <Weteoes/Application/WUpdate.h>

// UpdateDlg.h: 头文件
//



// CUpdateDlg 对话框
class CUpdateDlg : public CDialogEx
{
public:
	void DownloadLoading(LPVOID); //加载下载列表

private:
	void Download(list<WUpdateClass::OnlyPathFile>, LPVOID);
	void Loading(); //初始化
	void Close(bool); //关闭
	std::string GetSavePath();
	std::string GetSoftwareName();
	void LoadingDownload(); //Initialization Download

// 构造
public:
	CUpdateDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
