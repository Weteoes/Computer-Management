#include <pch.h>
#include "ReadXMLConfig.h"
#include <Weteoes/Application/ConfigFile.h>
#include <Weteoes/Application/XML.h>
#include "ReturnXMLStruct.h"

ReturnXMLStruct::UserConfig ReadXMLConfigClass::UserConfig() {
	ReturnXMLStruct::UserConfig result = ReturnXMLStruct::userConfig;
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserConfig;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, a)) {
		return result;
	}
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) {
		// 找不到root节点
		return result;
	}
	tinyxml2::XMLElement* w_ = root->FirstChildElement("w");
	if (w_ && w_->FirstChild() != NULL) { strcpy_s(result.w, w_->GetText()); }
	return result;
}

ReturnXMLStruct::ComputerConfig ReadXMLConfigClass::ComputerConfig() {
	ReturnXMLStruct::ComputerConfig result = ReturnXMLStruct::computerConfig;
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::ComputerConfig;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, a)) {
		return result;
	}
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) {
		// 找不到root节点
		return result;
	}
	tinyxml2::XMLElement* XML_ComputerName = root->FirstChildElement("ComputerName");
	if (XML_ComputerName && XML_ComputerName->FirstChild() != NULL) { strcpy_s(result.ComputerName, XML_ComputerName->GetText()); }
	tinyxml2::XMLElement* XML_Language = root->FirstChildElement("Language");
	if (XML_Language && XML_Language->FirstChild() != NULL) { strcpy_s(result.Language, XML_Language->GetText()); }
	return result;
}
