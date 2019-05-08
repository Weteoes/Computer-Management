//App
#include <Application/WUpdate.h>

//Dll
#include <Dll/WeteoesDll.h>
#include <Dll/Management.h>

//More
#include <More/Json/include/WJson.h>

std::string WUpdateClass::ApplicationPath;

bool WUpdateClass::DetectionUpdate(std::list<OnlyPathFile> *args) {
	std::list<OnlyPathFile> a = GetInternetList();
	if (a.size() == 0) { return false; }
	std::list<OnlyPathFile> b = GetNeedUpdateList(a);
	if (b.size() == 0) { return false; }
	if (args != NULL) { *args = b; }
	return true;
}
std::list<WUpdateClass::OnlyPathFile> WUpdateClass::GetNeedUpdateList(std::list<OnlyPathFile> InternetList) {
	std::list<OnlyPathFile> PathFile;
	std::string Path = ApplicationPath;
	for (std::list<OnlyPathFile>::const_iterator i = InternetList.begin(); i != InternetList.end(); i++) {
		OnlyPathFile Only = (OnlyPathFile)*i;
		std::string File = Path + Only.FileName;
		char *CFile = (char*)File.c_str();
		if (WeteoesDll::IO_Exists(CFile)) { //存在文件，判断MD5
			std::string NowMD5 = WeteoesDll::MD5_MD5File(CFile);
			if (NowMD5 == "" || (std::string)Only.FileMD5 != NowMD5) {
				PathFile.push_back(Only);
			}
		}
		else{ 
			PathFile.push_back(Only); 
		} //不存在,直接添加
	}
	return PathFile;
}

std::list<WUpdateClass::OnlyPathFile> WUpdateClass::GetInternetList() {
	std::list<OnlyPathFile> PathFile;
	if (!ManagementDll().Loading()) { return PathFile; }
	std::string URL_Update = std::string(ManagementDll::Get((char*)"URL_Update"));
	if (URL_Update.empty()) { return PathFile; }
	std::string result = WeteoesDll::Http_HttpRequest((char*)URL_Update.c_str(), 443, (char*)"/Computer/Update/index", (char*)"POST", NULL, 0);
	Json::Value json = WJsonClass::GetJson((char*)result.c_str());
	if (json != NULL)
	{
		int all = json.size();
		if (all == 0) { return PathFile; }
		for (int i = 0; i < all; i++)
		{
			OnlyPathFile Only;
			strncpy_s(Only.FileName, json[i]["FileName"].asString().c_str(), sizeof(Only.FileName));
			strncpy_s(Only.FileMD5, json[i]["FileMD5"].asString().c_str(), sizeof(Only.FileMD5));
			strncpy_s(Only.FileDownload, json[i]["FileDownload"].asString().c_str(), sizeof(Only.FileDownload));
			PathFile.push_back(Only);
		}
	}
	return PathFile;
}
