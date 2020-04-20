#include <pch.h>
#include "SetXMLConfig.h"
#include <Weteoes/Application/ConfigFile.h>
#include <Weteoes/Application/XML.h>

bool SetXMLConfigClass::ComputerConfig(const char* element, const char* data) {
	std::string XmlFile = WeteoesDll::Basics_GetNowFilePath() + ConfigFileClass::ComputerConfig;
	tinyxml2::XMLDocument xml;
	if (!VariableClass::xmlClass.GetXmlDocument(xml, XmlFile)) {
		return false;
	}
	tinyxml2::XMLElement* root = xml.RootElement();
	if (root == NULL) {
		// 找不到root节点
		return false;
	}
	VariableClass::xmlClass.SetElementValue(xml, root, element, data);
	VariableClass::xmlClass.SaveXML(xml, XmlFile);
	return true;
}
