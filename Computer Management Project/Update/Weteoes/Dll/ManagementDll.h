#include <Windows.h>

#ifdef ManagementDll_
#else
#define ManagementDll_
class ManagementDll
{
private:
	typedef char*(__stdcall *Get_)(char*);

public:
	bool Loading();
	static Get_ Get;
};
#endif