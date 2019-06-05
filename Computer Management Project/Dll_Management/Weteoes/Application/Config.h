//#define w_Debug
#ifdef w_Debug
#define Config_URL "127.0.0.1"
#define Config_URL_Type "http://"
#define Config_Socket_Port "1"
#else
#define Config_URL "Computer.Weteoes.cn"
#define Config_URL_Type "https://"
#define Config_Socket_Port "6666"
#endif // w_Debug

#define Config_Software_Title "Computer Management"
#define Config_Software_Name "Computer"
#define Config_Version "3.3.190605.1602"