#include "Client.h"

//App
#include <Weteoes/Application/Action/Cmd.h>
#include <Weteoes/Application/Action/Music.h>
#include <Weteoes/Application/Action/System.h>
#include <Weteoes/Application/Action/School.h>
#include <Weteoes/Application/Action/Control.h>

bool ClientClass::Entrance(char* data_c) { //Weteoes_Music_163|F5
	std::string data = data_c;
	std::string header = ConfigClass::use.GetConfig(&data); // ȥ��ͷ����Ϣ
	if (header != ConfigClass::Socket_Header) { return false; } // ͷ����һ��
	
	std::string app = ConfigClass::use.GetConfig(&data);
	if (app.empty()) { return false; } //���Ϊ�����˳�
	if (ConfigClass::use.StrToLower(app) == ConfigClass::use.StrToLower("CMD")) { CmdClass().Run(data); }
	else if (ConfigClass::use.StrToLower(app) == ConfigClass::use.StrToLower("Music")) { MusicClass().Entrance(data); }
	else if (ConfigClass::use.StrToLower(app) == ConfigClass::use.StrToLower("System")) { SystemClass().Entrance(data); }
	else if (ConfigClass::use.StrToLower(app) == ConfigClass::use.StrToLower("School")) { SchoolClass().Entrance(data); }
	else if (ConfigClass::use.StrToLower(app) == ConfigClass::use.StrToLower("Control")) { ControlClass().Entrance(data); }
	return true;
}
