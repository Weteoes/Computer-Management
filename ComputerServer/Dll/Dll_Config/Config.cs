namespace Weteoes
{
    public class ConfigClass
    {
        public static string startPath = global::System.Windows.Forms.Application.StartupPath;
        public static string socket_Header = "Weteoes"; //Data Header
        public static string socket_Hello = "[Hello_Weteoes]"; //socketHello
        public static string socket_NoRule = "|Weteoes_NoRule|"; //不符合规则的字符串
        public static string socket_Success = "[Weteoes_OK]"; //成功后返回内容
        public static string socket_Error = "[Weteoes_Error]"; //失败后返回内容
        public static string socket_End = "|end|"; // Socket文字结束标识
        public static string socket_SuccessUser = null; //成功后自定义返回内容
        public static int serverPort = 6666; //默认端口
        public static int controlServerPort = 10001; //远程控制(control)默认端口
        public static string URL_up = "https://computer.weteoes.cn/operating/User/get?w={0}"; //判断用户身份URL
        //public static string URL_up = "http://127.0.0.1/operating/User/get?w={0}"; //判断用户身份URL
    }
}
