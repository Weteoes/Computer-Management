#include <Loading.h>

class AppClass {
public:
	void Login_Success(); //��¼���
	void Start_SR(); //����SR����
private:
	void SR_(); //SR������߳�
	void Dlg_Main_Start(); //Main���ڶ��߳�
	void PD_Config(); //�ж������ļ��Ƿ����
	std::string Random_Character(int len); //����ַ�
};