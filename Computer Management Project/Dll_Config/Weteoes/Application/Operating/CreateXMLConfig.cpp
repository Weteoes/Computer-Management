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
	VariableClass::xmlClass.SetElementValue(xml, root, "w", w);
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
	VariableClass::xmlClass.SetElementValue(xml, root, "ComputerName", ComputerName);
	VariableClass::xmlClass.SetElementValue(xml, root, "Language", Language);
	return VariableClass::xmlClass.SaveXML(xml, a);
}