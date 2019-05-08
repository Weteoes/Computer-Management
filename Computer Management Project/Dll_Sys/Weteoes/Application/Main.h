#include <Loading.h>

class MainClass
{
public:
	void Entrance();
private:
	void startSoftware(); //启动软件
	void stopSoftware(); //关闭软件
	void pipeEntrance(std::string); //PIPE事件
};