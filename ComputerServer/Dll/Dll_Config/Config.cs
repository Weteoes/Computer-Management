namespace Weteoes
{
    public class ConfigClass
    {
        public static string startPath = global::System.Windows.Forms.Application.StartupPath;
        public static string socket_Header = "Weteoes"; //Data Header
        public static string socket_Hello = "[Hello_Weteoes]"; //socketHello
        public static string socket_NoRule = "|Weteoes_NoRule|"; //�����Ϲ�����ַ���
        public static string socket_Success = "[Weteoes_OK]"; //�ɹ��󷵻�����
        public static string socket_Error = "[Weteoes_Error]"; //ʧ�ܺ󷵻�����
        public static string socket_End = "|end|"; // Socket���ֽ�����ʶ
        public static string socket_SuccessUser = null; //�ɹ����Զ��巵������
        public static int serverPort = 6666; //Ĭ�϶˿�
        public static int controlServerPort = 10001; //Զ�̿���(control)Ĭ�϶˿�
        public static string URL_up = "https://computer.weteoes.cn/operating/User/get?w={0}"; //�ж��û����URL
        //public static string URL_up = "http://127.0.0.1/operating/User/get?w={0}"; //�ж��û����URL
    }
}
