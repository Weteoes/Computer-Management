#include <Loading.h>

class AppClass {
public:
	void Login_Success(); //登录完毕
	void Start_SR(); //启动SR服务
private:
	void SR_(); //SR服务多线程
	void Dlg_Main_Start(); //Main窗口多线程
	void PD_Config(); //判断配置文件是否存在
	std::string Random_Character(int len); //随机字符
};