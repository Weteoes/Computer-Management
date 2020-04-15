#include <pch.h>
#include "CreateXMLConfig.h"
#include <Weteoes/Application/ConfigFile.h>
#include <Weteoes/Application/XML.h>

bool CreateXMLConfigClass::CreateXML(string xmlFile) {
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, xmlFile, true)) {
		return false;
	}
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) {
		// 找不到root节点
		root = xml.NewElement(VariableClass::xmlClass.RootElementName.c_str());
	}
	xml.InsertEndChild(root);
	return VariableClass::xmlClass.SaveXML(xml, xmlFile);
}

bool CreateXMLConfigClass::UserConfig(const char* w) {
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::UserConfig;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, a, true)) {
		return false;
	}
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) {
		// 找不到root节点
		root = xml.NewElement(VariableClass::xmlClass.RootElementName.c_str());
	}
	tinyxml2::XMLElement* w_ = xml.NewElement("w");
	w_->SetText(w);
	root->InsertEndChild(w_);
	xml.InsertEndChild(root);
	return VariableClass::xmlClass.SaveXML(xml, a);
}

bool CreateXMLConfigClass::ComputerConfig(const char* ComputerName, const char* Language) {
	std::string a = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::ComputerConfig;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, a, true)) {
		return false;
	}
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) {
		// 找不到root节点
		root = xml.NewElement(VariableClass::xmlClass.RootElementName.c_str());
	}
	tinyxml2::XMLElement* XML_ComputerName = xml.NewElement("ComputerName"); XML_ComputerName->SetText(ComputerName);
	tinyxml2::XMLElement* XML_Language = xml.NewElement("Language"); XML_Language->SetText(Language);
	root->InsertEndChild(XML_ComputerName);
	root->InsertEndChild(XML_Language);
	xml.InsertEndChild(root);
	return VariableClass::xmlClass.SaveXML(xml, a);
}