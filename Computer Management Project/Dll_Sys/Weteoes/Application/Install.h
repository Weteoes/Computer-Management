#include <Weteoes/Loading.h>
#include <Weteoes/Application/Regedit.h>
#include <Weteoes/Dll/WeteoesDll.h>

class InstallClass
{
public:
	void Install(); //��װ

private:
	std::list<RegeditClass::RegeditMainPathArray> MainPathArray; //����ע�������
	void RegeditListLoading(); //��ʼ��RegeditList
	void Regedit(); //ע���
	void Service(); //��װ����
};
