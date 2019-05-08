#include "json.h"
#pragma comment(lib,"Weteoes/More/Json/lib/json_vc71_libmtd.lib")

class WJsonClass
{
public:
	static Json::Value GetJson(char*);

};
Json::Value WJsonClass::GetJson(char* data) {
	Json::CharReaderBuilder b;
	Json::CharReader* reader(b.newCharReader());
	Json::Value root;
	JSONCPP_STRING error;
	if (reader->parse(data, data + strlen(data), &root, &error)) {
		return root; 
	}
	return NULL;
}