#include "Client.h"

//App
#include <Application/Config.h>
#include <Application/Action/Cmd.h>
#include <Application/Action/Music.h>
#include <Application/Action/System.h>

bool ClientClass::Entrance(char* data) { //Music_163|F5
	ConfigClass ConfigClass_;
	std::string data_s = data;
	std::string header = ConfigClass_.GetConfig(&data_s); //ͷ����Ϣ
	if (header != ConfigClass::Socket_Header) { //ͷ����һ��
		return false;
	}
	std::string app = ConfigClass_.GetConfig(&data_s);
	std::string shell = data_s;
	if (app.empty() || shell.empty()) { return false; } //���Ϊ�����˳�
	if (ConfigClass_.StrToLower(app) == ConfigClass_.StrToLower("CMD")) { CmdClass().Run(shell); }
	else if (ConfigClass_.StrToLower(app) == ConfigClass_.StrToLower("Music")) { MusicClass().Entrance(shell); }
	else if (ConfigClass_.StrToLower(app) == ConfigClass_.StrToLower("System")) { SystemClass().Entrance(shell); }
	return true;
}
