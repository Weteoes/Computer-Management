#ifndef BASE_64_H
#define BASE_64_H
#include <Loading.h>

class Base64Class {
private:
	std::string _base64_table;
static const char base64_pad = '='; public:
	Base64Class()
	{
		_base64_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; /*����Base64����ʹ�õı�׼�ֵ�*/
	}
	/**
	* ���������unsigned���ͣ�����������ĵ�ʱ�����
	*/
	std::string Encode(const unsigned char * str, int bytes);
	std::string Decode(const char *str, int bytes);
};
#endif