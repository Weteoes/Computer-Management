using System.Collections.Generic;
using System.Net.Sockets;

namespace Weteoes
{
    public class ControlMainClass
    {
        private static Dictionary<string, List<controlStruct>> controlComputerList = new Dictionary<string, List<controlStruct>>(); // 用户Control列表
        private static Dictionary<Socket, string> controlSocketList = new Dictionary<Socket, string>(); // Socket对应用户列表
        private static Dictionary<Socket, Socket> controlConnectList = new Dictionary<Socket, Socket>(); // Socket对应Socket列表(控制端和被控端对应表)

        private static ControlSocketClass controlSocketClass = new ControlSocketClass(); // 用于WriteMessage
        private static AppConfigClass appConfigClass = new AppConfigClass();

        public bool Entrance(byte[] data, ref Socket socket) {
            try
            {
                string user, computerName;
                if (!controlSocketList.TryGetValue(socket, out user)) { // Socket查询用户,失败就说明没有验证过身份
                    string data_string = System.Text.Encoding.UTF8.GetString(data);
                    int function = getFunction(ref data_string); // 获取操作类型
                    /* Sign_in */
                    if (!Login(socket, ref data_string, out user)) {
                        controlSocketClass.WriteMessage("MainClass::socketEntrance 捕捉到非法用户访问，身份信息不一致");
                        return false;
                    }
                    computerName = appConfigClass.GetConfig(ref data_string, "|w|");
                    switch (function) {
                        case 1: // Server
                            controlSocketList.Add(socket, user); // 添加Socket对应用户列表
                            Server(socket, user, computerName);
                            break;
                        case 2: // Client
                            controlSocketList.Add(socket, user); // 添加Socket对应用户列表
                            if (!Client(socket, user, computerName)) { controlSocketClass.WriteMessage("Entrance 被控端未上线"); return false; } // 被控端未上线
                            break;
                        default:
                            controlSocketClass.WriteMessage("Entrance 捕捉到非法访问 Data:" + data_string);
                            break;
                    }
                }
                ForwardData(socket, data); // 转发数据
                return true;
            }
            catch(System.Exception error) { return false; }   
        }
        private bool Server(Socket socket, string user, string computerName) {
            try {
                List<controlStruct> tempControlStructList;
                if (!controlComputerList.TryGetValue(user, out tempControlStructList)) {  // 没获取到就初始化List空间
                    tempControlStructList = new List<controlStruct>();
                }
                List<controlStruct> removeControlStructList = new List<controlStruct>();
                foreach (controlStruct i in tempControlStructList) {
                    // 如果有相同的电脑名称，那就删掉他
                    if (i.computerName.Equals(computerName)) { removeControlStructList.Add(i); }
                }
                foreach (controlStruct i in removeControlStructList) { tempControlStructList.Remove(i); }
                
                // 添加控制列表
                controlStruct tempControlStruct = new controlStruct() { computerName = computerName, socket = socket };
                tempControlStructList.Add(tempControlStruct);
                controlComputerList.Add(user, tempControlStructList); // 添加用户Control列表
                return true;
            }
            catch { return false; }
        }
        private bool Client(Socket socket, string user, string computerName) {
            try {
                List<controlStruct> controlStructs;
                if (!controlComputerList.TryGetValue(user, out controlStructs)) { return false; }
                foreach (controlStruct i in controlStructs) {
                    if (i.computerName.Equals(computerName)) { // 相同的电脑名称(要控制这一台)
                        // 删除原先连接 i.socket(2条记录)
                        List<Socket> removeSocketList = new List<Socket>();
                        foreach (KeyValuePair<Socket, Socket> ii in controlConnectList) { if (ii.Value == i.socket) { removeSocketList.Add(ii.Key); } }
                        foreach (Socket ii in removeSocketList) { controlConnectList.Remove(ii); }
                        controlConnectList.Remove(i.socket);

                        // 添加来回2个记录
                        controlConnectList.Add(socket, i.socket);
                        controlConnectList.Add(i.socket, socket);
                        return true;
                    }
                }
                return false;
            }
            catch { return false; }
        }
        private bool Login(Socket socket, ref string data, out string user) {
            user = ""; // 初始化out
            try {
                //if (controlSocketList.TryGetValue(socket, out user)) { return true; } // Socket查询用户,成功就说明已经验证过身份
                string w = appConfigClass.GetConfig(ref data, "|w|");
                if (new UserClass().Sign_in_w(w, out user)) { return true; } // 登录成功
                return false;
            }
            catch { return false; }
        }
        private void ForwardData(Socket socket, byte[] data) {
            Socket a;
            if (!controlConnectList.TryGetValue(socket, out a)) { controlSocketClass.WriteMessage("ForwardData -> find Socket Error"); return; }
            a.Send(data);
        }
        private int getFunction(ref string data) {
            /* AppConfig */
            string Function = appConfigClass.GetConfig(ref data, "_");
            switch (Function) {
                case "Server": return 1;
                case "Client": return 2;
            }
            return -1;
        }
        class controlStruct {
            public string computerName;
            public Socket socket;
        }
    }
}
