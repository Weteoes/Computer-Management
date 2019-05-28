#include "Client.h"

//App
#include <Application/Config.h>
#include <Application/Action/Cmd.h>
#include <Application/Action/Music.h>
#include <Application/Action/System.h>
#include <Application/Action/School.h>

bool ClientClass::Entrance(char* data) { //Music_163|F5
	ConfigClass ConfigClass_;
	std::string header = data;
	std::string app = ConfigClass_.GetConfig(&header); //ȥ��ͷ����Ϣ
	// ͷ����һ��
	if (header != ConfigClass::Socket_Header) { return false; }
	// ��ȡ����
	std::string shell = ConfigClass_.GetConfig(&app);
	if (app.empty() || shell.empty()) { return false; } //���Ϊ�����˳�
	if (ConfigClass_.StrToLower(app) == ConfigClass_.StrToLower("CMD")) { CmdClass().Run(shell); }
	else if (ConfigClass_.StrToLower(app) == ConfigClass_.StrToLower("Music")) { MusicClass().Entrance(shell); }
	else if (ConfigClass_.StrToLower(app) == ConfigClass_.StrToLower("System")) { SystemClass().Entrance(shell); }
	else if (ConfigClass_.StrToLower(app) == ConfigClass_.StrToLower("School")) { SchoolClass().entrance(shell); }
	return true;
}
