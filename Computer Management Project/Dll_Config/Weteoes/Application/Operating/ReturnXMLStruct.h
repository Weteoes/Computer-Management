#ifndef ReturnXMLStruct_H
#define ReturnXMLStruct_H
class ReturnXMLStruct //�û��Զ�������
{
public:
	struct UserConfig {
		char w[256];
	};
	struct ComputerConfig {
		char ComputerName[256];
		char Language[10];
	};

public:
	static ReturnXMLStruct::UserConfig userConfig;
	static ReturnXMLStruct::ComputerConfig computerConfig;
};
#endif
