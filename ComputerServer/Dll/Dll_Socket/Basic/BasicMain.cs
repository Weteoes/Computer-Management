namespace Weteoes
{
    public class BasicMainClass
    {
        public int socketEntrance(string data, ref System.Net.Sockets.Socket socket) {
            try
            {
                data = new RSAClass().Accept_PrivateUnEncode(data); //解密 Weteoes_Client （Weteoes_Client_1_1|ComputerName1|shell1）
                if (data == ConfigClass.socket_Hello) { return 0; } //如果为Hello

                /* AppConfig */
                AppConfigClass AppConfig = new AppConfigClass();
                string socket_Header = AppConfig.GetConfig(ref data);
                if (socket_Header != ConfigClass.socket_Header) { return -3; } //Header

                /* Function */
                int Function = getFunction(ref data);

                /* Sign_in */
                if (!(new UserClass().Sign_in(ref data))) { Function = 3; } //判断身份，获取真实命令（去掉user和pass）

                /* Function Switch */
                switch (Function)
                {
                    case 1:
                        new ServerClass().entrance(data, ref socket);
                        return 0;
                    case 2:
                        new ClientClass().entrance(data);
                        return 0;
                    case 3:
                        new MessageClass().writeLog("MainClass::socketEntrance 捕捉到非法用户访问，身份信息不一致");
                        return -2;
                    default:
                        new MessageClass().writeLog("MainClass::socketEntrance 捕捉到非法访问 Data:" + data);
                        return -1;
                }
            }
            catch {
                return -5;
            }   
        }
        private int getFunction(ref string data) {
            /* AppConfig */
            AppConfigClass AppConfig = new AppConfigClass();
            string Function = AppConfig.GetConfig(ref data);
            switch (Function)
            {
                case "Server": return 1;
                case "Client": return 2;
            }
            return -1;
        }
    }
}
