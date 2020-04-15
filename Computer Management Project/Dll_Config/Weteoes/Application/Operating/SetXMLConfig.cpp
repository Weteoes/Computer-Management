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
		// �Ҳ���root�ڵ�
		return false;
	}
	tinyxml2::XMLElement* XML_menu = root->FirstChildElement(element);
	if (!XML_menu || XML_menu->FirstChild() == NULL) { return false; } //�Ҳ�������
	XML_menu->SetText(data);
	VariableClass::xmlClass.SaveXML(xml, XmlFile);
	return true;
}
