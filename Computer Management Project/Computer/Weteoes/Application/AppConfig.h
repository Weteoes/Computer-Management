#include <Weteoes/Loading.h>

class AppConfigClass
{
public:
	static bool IsLogin;				// �Ƿ��ѵ�¼
	static bool IsMiniStartMain;		// ����Mainʱ�Ƿ�Mini����
	static std::string SoftwareName;	// SoftwareName(ͨ��Dll��ȡ)
public:
	static std::string Get_Version();			// ��ȡ�汾
	static std::string Get_TempPath();			// ��ȡ��ʱ����λ��
};
