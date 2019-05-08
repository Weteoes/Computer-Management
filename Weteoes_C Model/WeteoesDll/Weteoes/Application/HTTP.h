#ifdef HTTPClass_
#else
#define HTTPClass_
#include <Loading.h>
#pragma comment(lib,"Wininet.lib")
#include "Wininet.h"

//App
#include <Application/Convert.h>

class HTTPClass {
public:
	char* HttpRequest(char* Url, short Port, char * lpUrl, char * Method, char * lpPostData, int nPostDataLen); //HTTP����
};

//ģ�����������HTTP������
char* HTTPClass::HttpRequest(char* Url, short Port, char * lpUrl, char * Method, char * lpPostData, int nPostDataLen)
{
	HINTERNET hInternet = NULL, hConnect = NULL, hRequest = NULL;
	BOOL bRet;
	std::string strResponse;
	hInternet = (HINSTANCE)InternetOpen("User-Agent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if (!hInternet) { goto Ret0; }
	hConnect = (HINSTANCE)InternetConnect(hInternet, Url, Port, NULL, "HTTP/1.1", INTERNET_SERVICE_HTTP, 0, 0);
	if (!hConnect) { goto Ret0; }
	{
		DWORD flac = {
			INTERNET_FLAG_KEEP_CONNECTION |
			INTERNET_FLAG_NO_AUTO_REDIRECT | //���Զ�����HTTP�����ض���ֻ
			//INTERNET_FLAG_NO_COOKIES | //�����Զ����Cookie��ͷ������Ҳ�����Զ���ӷ��ص�Cookie��HTTP�����Cookie���ݿ�
			INTERNET_FLAG_NO_AUTH | //������HTTP�����Զ������֤
			INTERNET_FLAG_RESTRICTED_ZONE |
			//INTERNET_FLAG_CACHE_IF_NET_FAIL | //�������ʧ�ܣ��򷵻ػ����ļ�
			INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP | //����sslģʽ�µ�https->http��ת
			INTERNET_FLAG_IGNORE_CERT_CN_INVALID | //����sslģʽ�µ�֤�����ƴ���
			INTERNET_FLAG_NO_UI | //����cookie�ĶԻ���
			0
		};
		if (Port == 443) { flac = flac | INTERNET_FLAG_SECURE; } //����sslģʽ
		hRequest = (HINSTANCE)HttpOpenRequest(hConnect, Method, lpUrl, "HTTP/1.1", NULL, NULL, flac, 0);
		if (!hRequest) { goto Ret0; }
	}
	//bRet = HttpAddRequestHeaders(hRequest,"Content-Type: application/x-www-form-urlencoded",Len(FORMHEADERS),HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
	//if(!bRet) { goto Ret0; }
	bRet = HttpSendRequest(hRequest, NULL, 0, lpPostData, nPostDataLen);
	while (TRUE)
	{
		char cReadBuffer[4096];
		unsigned long lNumberOfBytesRead;
		bRet = InternetReadFile(hRequest, cReadBuffer, sizeof(cReadBuffer) - 1, &lNumberOfBytesRead);
		if (!bRet || !lNumberOfBytesRead) { break; }
		cReadBuffer[lNumberOfBytesRead] = 0;
		strResponse = strResponse + cReadBuffer;
	}
Ret0:
	if (hInternet) { InternetCloseHandle(hInternet); }
	if (hConnect) { InternetCloseHandle(hConnect); }
	if (hRequest) { InternetCloseHandle(hRequest); }
	char *result = ConvertClass().GetChars(strResponse);
	return result;
}
#endif // HTTPClass_