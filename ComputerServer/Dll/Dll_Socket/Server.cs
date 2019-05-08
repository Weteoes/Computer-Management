using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;

namespace Weteoes
{
    public class ServerClass
    {
        public static List<serverUser> allServerList = new List<serverUser>();
        int allServerListInt = -1; //用于addServerUserList函数临时记录位置

        public void removeFailList()
        { //移除已退出的电脑
            List<ServerClass.serverUser> all = ServerClass.allServerList;
            foreach (ServerClass.serverUser only in all)
            {
                List<ServerClass.serverComputer> all_computer = only.server; //循环列表
                List<object> result_all = new List<object>(); //需要返回的列表
                //循环获取在线数量
                for (int i = all_computer.Count - 1; i >= 0; i--)
                {
                    ServerClass.serverComputer only_computer = all_computer[i];
                    try {
                        only_computer.socket.Send(Encoding.Default.GetBytes(""));
                        
                    }
                    catch { //失效Socket
                        all_computer.Remove(only_computer);
                        continue;
                    }
                }
            }
        }
        public void entrance(string data,ref Socket socket) { //Weteoes_Server_Weteoes|Home|1
            serverUser a = new serverUser();
            if (!getServerList(data, ref a,ref socket)) { return; }
            switch (PDserverList(a)) {
                case 0:
                    new MessageClass().writeLine(String.Format("Server user:{0} name:{1} Join in", a.user, a.server[0].name));
                    allServerList.Add(a);
                    break;
                case 1:
                    addServerUserList(a); //某用户添加客户端
                    break;
                case 2:
                    new MessageClass().writeLine(String.Format("Server user:{0} name:{1} Join in", a.user, a.server[0].name));
                    break;
            }
        }
        private void addServerUserList(serverUser server) {
            try
            {
                if (allServerListInt == -1) { return; }
                serverComputer b = server.server[0];
                allServerList[allServerListInt].server.Add(b);
                allServerListInt = -1;
                new MessageClass().writeLine(String.Format("Server user:{0} name:{1} Join in", server.user, server.server[0].name));
            }
            catch (Exception error) {
                new MessageClass().writeLog("Server::addServerUserList Error:" + error.Message);
            }
        }
        private int PDserverList(serverUser server) {
            try
            {
                for (int i = 0; i < allServerList.Count; i++) {
                    string user = allServerList[i].user;
                    if (server.user.Equals(user)) {
                        List<serverComputer> nowUserList = allServerList[i].server;
                        for (int ii = 0; ii < nowUserList.Count; ii++)
                        {
                            var oldList = nowUserList[ii];
                            string oldName = oldList.name;
                            var newList = server.server[0];
                            if (oldName.Equals(newList.name))
                            {
                                oldList.socket.Close(); oldList.socket.Dispose(); //关闭原先连接
                                allServerList[i].server.Remove(oldList); //删除原先配置
                                allServerList[i].server.Add(newList); //添加新的
                                return 2;
                            }
                        }
                        allServerListInt = i; //用于addServerUserList函数临时记录位置
                        return 1;
                    }
                }
                return 0; //不存在该用户，直接添加
            }
            catch (Exception error)
            {
                new MessageClass().writeLog("Server::PDserverList Error:" + error.Message);
                return 0;
            }
        }
        private bool getServerList(string data, ref serverUser server,ref Socket socket) {
            try
            {
                /* AppConfig */
                AppConfigClass AppConfig = new AppConfigClass();
                string user = AppConfig.GetConfig(ref data, "_"); //执行完毕后data为电脑名称
                if (user == "") { return false; }

                server.user = user;
                serverComputer b = new serverComputer() { name = data, socket = socket };
                server.server.Add(b);
                return true;
            }
            catch (Exception error)
            {
                new MessageClass().writeLog("Server::getServerList Error:" + error.Message);
                return false;
            }
        }
        public class serverUser
        {
            public string user; /* 用户 */
            public List<serverComputer> server = new List<serverComputer>(); /* 电脑 */
        }
        public class serverComputer //客户端和服务端公用结构体
        {
            public string name; /* 电脑名称 */
            public string data; /* 手机使用发送内容 */
            public Socket socket;
        }
    }
}
