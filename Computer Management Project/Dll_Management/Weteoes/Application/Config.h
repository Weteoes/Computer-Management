//#define w_Debug
#ifdef w_Debug
#define Config_URL "127.0.0.1"
#define Config_Socket_Port "6666"
#define Config_UI_URL "http://127.0.0.1:80"
#else
#define Config_URL "Computer.Weteoes.cn"
#define Config_Socket_Port "6666"
#define Config_UI_Port "23330"
#endif // w_Debug

#define Config_Software_Title "Computer Management"
#define Config_Software_Name "Computer" // 主程序运行进程名称
#define Config_Version "4.1.20204.1820"