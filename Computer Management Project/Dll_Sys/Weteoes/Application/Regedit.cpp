//App
#include <Application/Regedit.h>

//Dll
#include <Dll/WeteoesDll.h>

void RegeditClass::Loading() {
	WeteoesDll().Loading();
}
void RegeditClass::CreateRegedit(std::list<RegeditMainPathArray> MainPathArray) //�ݹ鴴��ע���
{
	Loading();
	for (std::list<RegeditMainPathArray>::const_iterator i = MainPathArray.begin(); i != MainPathArray.end(); i++) {
		RegeditMainPathArray OnlyPathArray = (RegeditMainPathArray)*i;
		HKEY ServicesKey;
		if ((ServicesKey = WeteoesDll::Regedit_CreateRegFile(OnlyPathArray.MainPath, OnlyPathArray.Path)) == 0) {
			//MessageClass::WriteFileLog("Error:RegeditClass::CreateRegedit ��Ȩ�޷��� 0");
			RegCloseKey(ServicesKey);
			continue;
		}
		RegeditListValue(OnlyPathArray.ValueArray, ServicesKey); //�ݹ�Valule
		RegeditListPath(OnlyPathArray.MainArray, ServicesKey); //�ݹ�Path
	}
}
void RegeditClass::RegeditListPath(std::list<RegeditMainArray> RegeditMain, HKEY Key) { //����ע���ݹ�Path
	if (RegeditMain.size() == 0) { return; }
	for (std::list<RegeditMainArray>::const_iterator path = RegeditMain.begin(); path != RegeditMain.end(); path++) { //ѭ���ļ���
		RegeditMainArray OnlyRegeditMainArray = (RegeditMainArray)*path;
		HKEY PathKey = WeteoesDll::Regedit_CreateRegFile(Key, OnlyRegeditMainArray.FileTitle); //�����ļ���
		RegeditListValue(OnlyRegeditMainArray.ValueArray, PathKey); //�ݹ�Valule
		if (OnlyRegeditMainArray.MainArray.size() > 0) { RegeditListPath(OnlyRegeditMainArray.MainArray, PathKey); }  //�ݹ�Path
	}
	RegCloseKey(Key);
}
void RegeditClass::RegeditListValue(std::list<RegeditValueArray> RegeditValue, HKEY Key) { //����ע���ݹ�Value
	if (RegeditValue.size() == 0) { return; }
	for (std::list<RegeditValueArray>::const_iterator value = RegeditValue.begin(); value != RegeditValue.end(); value++) //ѭ������
	{
		RegeditValueArray OnlyRegeditValueArray = (RegeditValueArray)*value;
		std::string old;
		switch (OnlyRegeditValueArray.Weteoes)
		{
		case 0: //����
			old = WeteoesDll::Regedit_QueryRegValue(Key, OnlyRegeditValueArray.title, OnlyRegeditValueArray.type, OnlyRegeditValueArray.IsNum);
			if (!old.empty()) { break; }
			WeteoesDll::Regedit_CreateRegValue(Key, OnlyRegeditValueArray.title, OnlyRegeditValueArray.value, OnlyRegeditValueArray.type, OnlyRegeditValueArray.IsNum);
			break;
		case 1: //�滻
			WeteoesDll::Regedit_CreateRegValue(Key, OnlyRegeditValueArray.title, OnlyRegeditValueArray.value, OnlyRegeditValueArray.type, OnlyRegeditValueArray.IsNum);
			break;
		case 2: //׷��
			WeteoesDll::Regedit_QueryAddValue(Key, OnlyRegeditValueArray.title, OnlyRegeditValueArray.value, OnlyRegeditValueArray.type, OnlyRegeditValueArray.IsNum);
			break;
		}
	}
}