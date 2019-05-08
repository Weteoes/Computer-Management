#include <Loading.h>
#include "ReturnXMLStruct.h"

class ReadXMLConfigClass
{
public:
	ReturnXMLStruct::UserConfig_ User();
	ReturnXMLStruct::ComputerConfig_ Computer();
private:
	std::string ReadFile(std::string);
};

