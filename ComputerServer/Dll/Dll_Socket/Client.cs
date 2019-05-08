using System;
using System.Collections.Generic;
using System.Net.Sockets;
using System.Text;

namespace Weteoes
{
    public class ClientClass
    {
        public void entrance(string data) {
            ServerClass.serverUser a = new ServerClass.serverUser();
            if (!getServerList(data, ref a)) { return; }
            addServerData(a);
        }
        private bool getServerList(string data, ref ServerClass.serverUser server)
        {
            try
            {
                /* AppConfig */
                AppConfigClass AppConfig = new AppConfigClass();

                /* user */
                string user = AppConfig.GetConfig(ref data, "_");
                if (user == "") { return false; }
                server.user = user;

                /* shell */
                string ComputerName = AppConfig.GetConfig(ref data, "|"); //执行完毕后data为shell
                if (ComputerName == "") { return false; }
                ServerClass.serverComputer b = new ServerClass.serverComputer() { name = ComputerName, data = data };

                /* Add List  */
                server.server.Add(b);
                return true;
            }
            catch (Exception error)
            {
                new MessageClass().writeLog("Client::getServerList Error:" + error.Message);
                return false;
            }
        }
        private bool addServerData(ServerClass.serverUser server)
        {
            try
            {
                MessageClass mess = new MessageClass();
                List<ServerClass.serverUser> allServerList = ServerClass.allServerList;
                for (int i = 0; i < allServerList.Count; i++)
                {
                    string user = allServerList[i].user;
                    if (server.user.Equals(user))
                    {
                        List<ServerClass.serverComputer> nowUserList = allServerList[i].server;
                        for (int ii = 0; ii < nowUserList.Count; ii++)
                        {
                            string name = server.server[0].name; //当前要控制的设备名称
                            if (name.Equals(nowUserList[ii].name))
                            {
                                ServerClass.serverComputer temp = server.server[0];
                                //ServerClass.allServerList[i].server[ii].data = temp.data; //修改列表
                                if (nowUserList[ii].socket != null)
                                {
                                    if (new SocketClass().sendSocket(nowUserList[ii].socket, temp.data)) { //客户端在线
                                        //mess.writeLine(String.Format("Client user:{0} name:{1} shell:{2}", server.user, temp.name, temp.data));
                                        return true;
                                    }
                                    else { //客户端不在线
                                        mess.writeLine(String.Format("Server user:{0} name:{1} Leave", server.user, temp.name));
                                        ServerClass.allServerList.Remove(allServerList[i]); //删除这条记录
                                        mess.writeLine(String.Format("Client user:{0} name:{1} shell:{2},客户端已下线,指令取消", server.user, temp.name, temp.data));
                                        return false;
                                    }
                                }
                                return false;
                            }
                        }
                        mess.writeLog(String.Format("Client:该用户电脑未在线,Code:1,用户:{0},电脑:{1}", server.user,server.server[0].name));
                        return false; //没有该设备
                    }
                }
                mess.writeLog(String.Format("Client:该用户电脑未在线,Code:2,用户:{0},电脑:{1}",server.user, server.server[0].name));     
                return false; //没有该用户
            }
            catch (Exception error)
            {
                new MessageClass().writeLog("Client::addServerData Error:" + error.Message);
                return true;
            }
        }
    }
}
