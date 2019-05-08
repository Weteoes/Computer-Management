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
	char* HttpRequest(char* Url, short Port, char * lpUrl, char * Method, char * lpPostData, int nPostDataLen); //HTTP访问
};

//模拟浏览器发送HTTP请求函数
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
			INTERNET_FLAG_NO_AUTO_REDIRECT | //不自动处理HTTP请求重定向只
			//INTERNET_FLAG_NO_COOKIES | //不会自动添加Cookie标头的请求，也不会自动添加返回的Cookie的HTTP请求的Cookie数据库
			INTERNET_FLAG_NO_AUTH | //不尝试HTTP请求自动身份验证
			INTERNET_FLAG_RESTRICTED_ZONE |
			//INTERNET_FLAG_CACHE_IF_NET_FAIL | //如果请求失败，则返回缓存文件
			INTERNET_FLAG_IGNORE_REDIRECT_TO_HTTP | //忽略ssl模式下的https->http跳转
			INTERNET_FLAG_IGNORE_CERT_CN_INVALID | //忽略ssl模式下的证书名称错误
			INTERNET_FLAG_NO_UI | //禁用cookie的对话框。
			0
		};
		if (Port == 443) { flac = flac | INTERNET_FLAG_SECURE; } //启用ssl模式
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