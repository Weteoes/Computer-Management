#include <Windows.h>

#ifdef SysDll_
#else
#define SysDll_
class SysDll
{
private:
	typedef void(__stdcall* Fun1)();
	typedef bool(__stdcall * Fun2)();

public:
	bool Loading();
	static Fun1 Install; // 安装服务
	static Fun2 getInstall; // 获取服务是否安装
};
#endif