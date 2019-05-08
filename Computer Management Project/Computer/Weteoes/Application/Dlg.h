#include <Loading.h>
#include <Windows.h>

class DlgClass {

public:
	static HWND Dlg_HWND;  //���ھ�� �߳����
	static HINSTANCE Dlg_HINSTANCE;  //���ھ�� �ں����

public:
	struct Dlg {
		int x, y;
		int width, height;
	};
private:
	static Dlg Dlg_; //��¼������Ϣ

public:
	void Dlg_Close(); //ͳһ�رմ����¼�
	void Dlg_Mini(); //��С�������¼�
	void Dlg_Show(bool = false); //��ʾ�����¼�������������Ҳ����ã������bool=trueΪ������������
	void Dlg_Icon_Add();  //�������
	void Dlg_Icon_Remove(); //ɾ������
	void Dlg_SetNowRect(bool = false); //����Dlg����
	Dlg Dlg_GetRect(); //��ȡDlg����
};