#include <Loading.h>

//App
#include <Application/Regedit.h>

//Dll
#include <Dll/WeteoesDll.h>

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
