#include <Weteoes/Loading.h>

class AppClass {
public:
	void Login_Success(); //��¼���
	void Start_SRW(int); //����SR����
private:
	void SRW(int); //SRW������߳�
	void Dlg_Main_Start(); //Main���ڶ��߳�
	void PD_Config(); //�ж������ļ��Ƿ����
	std::string Random_Character(int len); //����ַ�
};