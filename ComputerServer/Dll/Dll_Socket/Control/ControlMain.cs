using System;
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
                string data_string = System.Text.Encoding.ASCII.GetString(data);
                if (data_string.Length < 6) { return true; }
                string w_f = data_string.Substring(0, 6);
                //if (data_string.Length > 100) {
                //    controlSocketClass.WriteMessage("MainClass::debug " + data_string.Substring(0, 10) + " "+ data_string.Substring(data_string.Length-10, 10) + " len:" + data_string.Length + " w_f:" + w_f);
                //}
                //else controlSocketClass.WriteMessage("MainClass::debug " + data_string + " len:" + data_string.Length + " w_f:"+w_f);
                //{
                //    int i = 0;
                //    if (data_string.IndexOf("|end|") != -1) { i++; }
                //    if (i != 1) { controlSocketClass.WriteMessage("MainClass::debug IndexOf:" + i); }
                //}
                

                if ((w_f == "Server" || w_f == "Client") && (!controlSocketList.TryGetValue(socket, out user))) { // Socket查询用户,失败就说明没有验证过身份
                    int function = getFunction(ref data_string); // 获取操作类型
                    controlSocketClass.WriteMessage("MainClass::11 " + data_string);
                    /* Sign_in */
                    if (!Login(socket, ref data_string, out user)) {
                        controlSocketClass.WriteMessage("MainClass::socketEntrance " + w_f + ": 捕捉到非法用户访问，身份信息不一致");
                        return false;
                    }
                    computerName = appConfigClass.GetConfig(ref data_string, "|w|");
                    switch (function) {
                        case 1: // Server
                            controlSocketList.Add(socket, user); // 添加Socket对应用户列表
                            Server(socket, user, computerName);
                            controlSocketClass.sendSocket(socket, controlSocketClass.flac_Start + controlSocketClass.flac_Success + controlSocketClass.flac_End);
                            break;
                        case 2: // Client
                            controlSocketList.Add(socket, user); // 添加Socket对应用户列表
                            if (!Client(socket, user, computerName)) { controlSocketClass.WriteMessage("Entrance 被控端未上线"); return false; } // 被控端未上线
                            controlSocketClass.sendSocket(socket, controlSocketClass.flac_Start + controlSocketClass.flac_Success + controlSocketClass.flac_End);
                            break;
                        default:
                            controlSocketClass.WriteMessage("Entrance 捕捉到非法访问 Data:" + data_string);
                            break;
                    }
                    goto flac_result;
                }
                ForwardData(socket, data); // 转发数据
            flac_result:
                return true;
            }
            catch(System.Exception error) { controlSocketClass.WriteMessage(error.Message); return false; }   
        }
        private bool Server(Socket socket, string user, string computerName) {
            try {
                List<controlStruct> tempControlStructList;
                if (!controlComputerList.TryGetValue(user, out tempControlStructList)) {  // 没获取到就初始化List空间
                    tempControlStructList = new List<controlStruct>();
                }
                for (int i = tempControlStructList.Count - 1; i >= 0; i--) {
                    if (tempControlStructList[i].computerName.Equals(computerName)) { tempControlStructList.RemoveAt(i); }
                }
                //List<controlStruct> removeControlStructList = new List<controlStruct>();
                //foreach (controlStruct i in tempControlStructList) {
                //    // 如果有相同的电脑名称，那就删掉他
                //    if (i.computerName.Equals(computerName)) { removeControlStructList.Add(i); }
                //}
                //foreach (controlStruct i in removeControlStructList) { tempControlStructList.Remove(i); }

                // 添加控制列表
                controlStruct tempControlStruct = new controlStruct() { computerName = computerName, socket = socket };
                tempControlStructList.Add(tempControlStruct);
                controlComputerList[user] = tempControlStructList; // 添加用户Control列表
                controlSocketClass.WriteMessage("Computer:" + computerName + " login.");
                return true;
            }
            catch(System.Exception error) { controlSocketClass.WriteMessage(error.Message); return false; }
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
            try {
                Socket a;
                //string bb = System.Text.Encoding.ASCII.GetString(data);
                //if (bb.Length > 20) bb = bb.Substring(0, 20);
                byte[] sendData = System.Text.Encoding.ASCII.GetBytes(controlSocketClass.flac_Start);
                int sendDataHeaderLen = sendData.Length; // 记录头部长度
                Array.Resize(ref sendData, sendDataHeaderLen + data.Length); // 修改byte大小
                Array.Copy(data, 0, sendData, sendDataHeaderLen, data.Length);

                //string aaa = System.Text.Encoding.ASCII.GetString(sendData);
                //controlSocketClass.WriteMessage("MainClass::debug " + aaa.Substring(0, 10) + " " + aaa.Substring(aaa.Length - 10, 10) + " len:" + aaa.Length);
                if (!controlConnectList.TryGetValue(socket, out a)) { return; }

                a.Send(sendData);
            }
            catch { }
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
