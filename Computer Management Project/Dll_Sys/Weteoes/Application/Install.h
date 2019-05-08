#include <Loading.h>

//App
#include <Application/Regedit.h>

//Dll
#include <Dll/WeteoesDll.h>

class InstallClass
{
public:
	void Install(); //安装

private:
	std::list<RegeditClass::RegeditMainPathArray> MainPathArray; //保存注册表配置
	void RegeditListLoading(); //初始化RegeditList
	void Regedit(); //注册表
	void Service(); //安装服务
};
