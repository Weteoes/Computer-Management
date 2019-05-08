#include <Loading.h>

class WUpdateClass
{
public:
	struct OnlyPathFile {
		char FileName[128];
		char FileMD5[128];
		char FileDownload[512];
	};
	bool DetectionUpdate(std::list<OnlyPathFile>*);
protected:
	std::list<OnlyPathFile> GetInternetList();
	std::list<OnlyPathFile> GetNeedUpdateList(std::list<OnlyPathFile> InternetList);
public:
	static std::string ApplicationPath; //本地文件位置
};