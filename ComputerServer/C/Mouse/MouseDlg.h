
// MouseDlg.h : ͷ�ļ�
//

#pragma once


// CMouseDlg �Ի���
class CMouseDlg : public CDialogEx
{
// ����
public:
	CMouseDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOUSE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnLbnDblclkList1();
	void Stop_xy();
	afx_msg void OnBnClickedButtonStarttwo();
	void Loading();
};
