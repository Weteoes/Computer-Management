#include <Weteoes/Loading.h>
#include <Weteoes/Dll/ManagementDll.h>

class ConfigClass
{
public:
	void Loading();
	static std::string ConfigPath; // ����Ŀ¼
	static std::string StartTime; // ����ʱ��
	static std::string ServiceName; // ��������
private:
	std::string loadingStartTime(); // ��ʼ������ʱ��
	std::string loadingServicePath(); // ��ʼ������Ŀ¼
};
