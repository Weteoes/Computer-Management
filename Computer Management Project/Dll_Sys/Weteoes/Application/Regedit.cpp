//App
#include <Application/Regedit.h>

//Dll
#include <Dll/WeteoesDll.h>

void RegeditClass::Loading() {
	WeteoesDll().Loading();
}
void RegeditClass::CreateRegedit(std::list<RegeditMainPathArray> MainPathArray) //递归创建注册表
{
	Loading();
	for (std::list<RegeditMainPathArray>::const_iterator i = MainPathArray.begin(); i != MainPathArray.end(); i++) {
		RegeditMainPathArray OnlyPathArray = (RegeditMainPathArray)*i;
		HKEY ServicesKey;
		if ((ServicesKey = WeteoesDll::Regedit_CreateRegFile(OnlyPathArray.MainPath, OnlyPathArray.Path)) == 0) {
			//MessageClass::WriteFileLog("Error:RegeditClass::CreateRegedit 无权限访问 0");
			RegCloseKey(ServicesKey);
			continue;
		}
		RegeditListValue(OnlyPathArray.ValueArray, ServicesKey); //递归Valule
		RegeditListPath(OnlyPathArray.MainArray, ServicesKey); //递归Path
	}
}
void RegeditClass::RegeditListPath(std::list<RegeditMainArray> RegeditMain, HKEY Key) { //用于注册表递归Path
	if (RegeditMain.size() == 0) { return; }
	for (std::list<RegeditMainArray>::const_iterator path = RegeditMain.begin(); path != RegeditMain.end(); path++) { //循环文件夹
		RegeditMainArray OnlyRegeditMainArray = (RegeditMainArray)*path;
		HKEY PathKey = WeteoesDll::Regedit_CreateRegFile(Key, OnlyRegeditMainArray.FileTitle); //创建文件夹
		RegeditListValue(OnlyRegeditMainArray.ValueArray, PathKey); //递归Valule
		if (OnlyRegeditMainArray.MainArray.size() > 0) { RegeditListPath(OnlyRegeditMainArray.MainArray, PathKey); }  //递归Path
	}
	RegCloseKey(Key);
}
void RegeditClass::RegeditListValue(std::list<RegeditValueArray> RegeditValue, HKEY Key) { //用于注册表递归Value
	if (RegeditValue.size() == 0) { return; }
	for (std::list<RegeditValueArray>::const_iterator value = RegeditValue.begin(); value != RegeditValue.end(); value++) //循环内容
	{
		RegeditValueArray OnlyRegeditValueArray = (RegeditValueArray)*value;
		std::string old;
		switch (OnlyRegeditValueArray.Weteoes)
		{
		case 0: //跳过
			old = WeteoesDll::Regedit_QueryRegValue(Key, OnlyRegeditValueArray.title, OnlyRegeditValueArray.type, OnlyRegeditValueArray.IsNum);
			if (!old.empty()) { break; }
			WeteoesDll::Regedit_CreateRegValue(Key, OnlyRegeditValueArray.title, OnlyRegeditValueArray.value, OnlyRegeditValueArray.type, OnlyRegeditValueArray.IsNum);
			break;
		case 1: //替换
			WeteoesDll::Regedit_CreateRegValue(Key, OnlyRegeditValueArray.title, OnlyRegeditValueArray.value, OnlyRegeditValueArray.type, OnlyRegeditValueArray.IsNum);
			break;
		case 2: //追加
			WeteoesDll::Regedit_QueryAddValue(Key, OnlyRegeditValueArray.title, OnlyRegeditValueArray.value, OnlyRegeditValueArray.type, OnlyRegeditValueArray.IsNum);
			break;
		}
	}
}