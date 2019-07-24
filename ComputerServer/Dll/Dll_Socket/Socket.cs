using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Text;
using System.Collections.Generic;

namespace Weteoes
{
    public class SocketClass
    {
        List<TcpListener> allTcpListener = new List<TcpListener>(); //监听ip集合
        List<SocketType> SocketTypeList = new List<SocketType>(); //Socket集合
        int SocketByteSize = 100; //设置缓存区大小
        static bool status = true; //运行状态
        public void server(int port, bool allIPAddress = false)
        {
            TcpListener b = null;
            try
            {
                new MessageClass().writeLog("初始化服务器");
                if (!allIPAddress)
                {
                    string name = Dns.GetHostName();
                    IPAddress[] ipadrlist = Dns.GetHostAddresses(name);
                    string all = "";
                    foreach (IPAddress aaaaa in ipadrlist)
                    {
                        if (all.IndexOf(aaaaa.ToString() + "|") != -1) { continue; }
                        all += aaaaa + "|";
                        IPAddress a = IPAddress.Parse(aaaaa.ToString());
                        if (aaaaa.AddressFamily == AddressFamily.InterNetwork)
                        {
                            b = new TcpListener(a, port);
                            new Thread(new ParameterizedThreadStart(serverListen)).Start(b);
                        }
                        else
                        {
                            new MessageClass().writeLog("IPv6地址：" + a + " 已跳过");
                        }
                    }
                }
                else {
                    IPAddress ip = IPAddress.Parse("0.0.0.0");
                    b = new TcpListener(ip, port);
                    new Thread(new ParameterizedThreadStart(serverListen)).Start(b);
                }
            }
            catch
            {
                new MessageClass().writeLog("初始化服务器失败");
            }
        }
        public void stop()
        {
            try
            {
                status = false;
                Thread.Sleep(300);
                foreach (TcpListener i in allTcpListener) { if (i != null) { i.Stop(); } } //关闭监听
                foreach (SocketType i in SocketTypeList) { i.SocketConnect.Close(); i.SocketConnect.Dispose(); } //关闭Socket
                new MessageClass().writeLog("关闭服务器成功");
            }
            catch
            {
                new MessageClass().writeLog("关闭服务器失败");
            }
        }
        private void serverListen(object serverIP)
        {
            TcpListener b = (TcpListener)serverIP;
            try
            {
                allTcpListener.Add(b);
                b.Start();
                new MessageClass().writeLog("线程启动,IPv4地址：" + b.LocalEndpoint);
                while (status)
                {
                    try
                    {
                        Socket c = b.AcceptSocket();
                        int SocketTypeListNow = SocketTypeList.Count; //当前添加位置
                        SocketTypeList.Add(new SocketType() { SocketConnect = c, SocketByte = new byte[SocketByteSize] }); //添加集合
                        c.BeginReceive(SocketTypeList[SocketTypeListNow].SocketByte, 0, SocketTypeList[SocketTypeListNow].SocketByte.Length, SocketFlags.None, new AsyncCallback(InternetSocketCallback), SocketTypeList[SocketTypeListNow]);
                    }
                    catch (Exception error) {
                        new MessageClass().writeLog("捕捉 Error:IPv4地址：" + b.LocalEndpoint + " ," + error.Message);
                    }
                }
            }
            catch (Exception error)
            {
                new MessageClass().writeLog("Error:IPv4地址：" + b.LocalEndpoint + " ," + error.Message);
                return;
            }
        }
        public bool sendSocket(Socket socket, string data)
        {
            try
            {
                if (!data.Equals(ConfigClass.socket_Success) && !data.Equals(ConfigClass.socket_Error)) { //如果不是系统消息了话
                    data = ConfigClass.socket_Header + "_" + data;
                }
                data = new RSAClass().Send_PublicEncode(data) + ConfigClass.socket_End;
                socket.Send(Encoding.Default.GetBytes(data));
                socket.SendTimeout = 100;
                return true;
            }
            catch
            {
                socket.Close();
                socket.Dispose();
                return false;
            }
        }
        private void InternetSocketClose(SocketType socketType) {
            socketType.SocketConnect.Close();
            socketType.SocketConnect.Dispose();
        }
        private void InternetSocketCallback_Socket() {

        }
        private void InternetSocketCallback(IAsyncResult WeteoesType)
        {
            SocketType socketType = (SocketType)WeteoesType.AsyncState;
            Socket socket = socketType.SocketConnect;
            bool IsReturn = true; //是否关闭连接
            try
            {
                /* Recv */
                string data = System.Text.Encoding.UTF8.GetString(socketType.SocketByte);
                while (socket.Available > 0)
                {
                    socketType.SocketByte = new byte[SocketByteSize];
                    socket.Receive(socketType.SocketByte, 0, socketType.SocketByte.Length, SocketFlags.None);
                    data += System.Text.Encoding.UTF8.GetString(socketType.SocketByte);
                }
                data = data.TrimEnd('\0'); data = data.Replace("\n", "");

                // 读取数据完毕，重新监听
                InternetSocketCallbackReset(socketType);

                /* Switch */
                int result = -6; //默认错误代码
                if (data.IndexOf("HTTP") != -1 && data.IndexOf("Host") != -1) /* HTTP通信 */
                {
                    if(new WebClass().entrance(data,ref socket)) result = 10; //如果为true则不断开socket连接
                }
                /* Sokcet通信 */
                else
                {

                    string[] allData = data.Split(new string[] { ConfigClass.socket_End },StringSplitOptions.None);
                    foreach (string onlyData in allData)
                    {
                        if (onlyData.Equals("")) { continue; }
                        result = new MainClass().socketEntrance(onlyData, ref socket);
                        // 如果小于0直接退出
                        if (result < 0) { break; }

                    }
                }

                /* if result */
                switch (result)
                {
                    case 0:
                        IsReturn = false; //设置不关闭Socket
                        break;
                    case -2: //非法访问，账号校验失败
                        sendSocket(socket, ConfigClass.socket_Error);
                        break;
                    case 10:
                        IsReturn = false;
                        break;
                }

                /* result send */
                if (ConfigClass.socket_SuccessUser == null)  //回复默认信息
                {
                    sendSocket(socket, ConfigClass.socket_Success);
                }
                else //回复自定义信息
                {
                    sendSocket(socket, ConfigClass.socket_SuccessUser);
                    ConfigClass.socket_SuccessUser = null; //回复完毕删除自定义
                }
            }
            catch {
                IsReturn = true;
            }
            finally {
                /* if remove */
                if (IsReturn == true)  //是否退出
                {
                    socket.Close();
                    socket.Dispose();
                    if (SocketTypeList.IndexOf(socketType) != -1)
                    {
                        SocketTypeList.Remove(socketType); //删除列表
                    }
                }
            }
        }
        private void InternetSocketCallbackReset(SocketType socketType) { //重新设置监听
            socketType.SocketByte = new byte[SocketByteSize];
            socketType.SocketConnect.BeginReceive(socketType.SocketByte, 0, socketType.SocketByte.Length, SocketFlags.None, new AsyncCallback(InternetSocketCallback), socketType);
        }
        class SocketType {
            public Socket SocketConnect;
            public byte[] SocketByte;
        }
    }
}
