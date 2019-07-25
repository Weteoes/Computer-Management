#include <Windows.h>

#ifdef SRDll_
#else
#define SRDll_
class SRDll
{
private:
	typedef int(__stdcall *Socket_Entrance_)();
	typedef char*(__stdcall *RSA_Encode_)(char* data, char* key);
	typedef char*(__stdcall *RSA_UnEncode_)(char* data, char* key);

public:
	bool Loading();
	static Socket_Entrance_ Socket_Entrance; //Socket入口
	static RSA_Encode_ RSA_Encode; //加密
	static RSA_UnEncode_ RSA_UnEncode; //解密
};
#endif